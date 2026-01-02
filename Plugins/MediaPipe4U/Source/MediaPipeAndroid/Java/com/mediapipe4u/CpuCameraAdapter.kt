package com.mediapipe4u

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Bitmap
import android.graphics.Matrix
import android.graphics.SurfaceTexture
import android.hardware.camera2.CameraAccessException
import android.hardware.camera2.CameraCharacteristics
import android.hardware.camera2.CameraManager
import android.hardware.camera2.params.StreamConfigurationMap
import android.util.Log
import android.util.Size
import androidx.camera.core.*
import androidx.camera.core.internal.CameraUseCaseAdapter
import androidx.camera.core.internal.CameraUseCaseAdapter.CameraException
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import com.epicgames.unreal.GameActivity
import com.google.mediapipe.components.CameraHelper.CameraFacing
import com.google.mediapipe.components.CameraXPreviewHelper
import com.google.mediapipe.framework.MediaPipeException
import java.util.*
import java.util.concurrent.CompletableFuture
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import kotlin.math.abs

class CpuCameraAdapter(
    private val gameActivity: GameActivity,
    private val cameraFacing: CameraFacing,
    private var rotation: Int = 0,
    private val cameraStateCallback: ((CameraState.Type)->Unit)? = null
) {
    private var cameraProvider: ProcessCameraProvider? = null
    private var imageAnalyzer: ImageAnalysis? = null
    private var camera: Camera? = null
    private var cameraAnalyzerExecutor: ExecutorService? = null
    private var onFrame: ((bitmap: Bitmap) -> Unit)? = null
    private var cameraLifecycle: CameraLifecycle? = null
    private var isStarted: Boolean = false
    private var cameraStartListener: ((bitmap: Bitmap?, e: Throwable?) -> Unit)? = null
    private var isScreenRotated: Boolean = false

    fun setOnFrameListener(listener: ((bitmap: Bitmap) -> Unit)?) {
        this.onFrame = listener
    }

    fun changeScreenOrientation(rotation: Int) {
        this.rotation = rotation
        this.isScreenRotated = rotation % 180 == 90
//        gameActivity.runOnUiThread {
//            val any = this.imageAnalyzer
//            if(any != null) {
//                any.targetRotation = rotation
//            }
//        }
    }

    private fun getCameraLensFacing(facing: CameraFacing? = null): Int {
        val f = facing ?: cameraFacing
        return if (f == CameraFacing.BACK) CameraSelector.LENS_FACING_BACK else CameraSelector.LENS_FACING_FRONT
    }

    fun setOnStartCompletedListener(listener: (bitmap: Bitmap?, e: Throwable?) -> Unit) {
        cameraStartListener = listener
    }

    fun open() {
        isStarted = false
        val cameraProviderFuture =
            ProcessCameraProvider.getInstance(gameActivity)

        val cameraLifecycle = CameraLifecycle()
        this.cameraLifecycle = cameraLifecycle
        cameraProviderFuture.addListener(
            {
                // CameraProvider
                cameraProvider = cameraProviderFuture.get()
                if(cameraProvider != null) {
                    // Build and bind the camera use cases
                    bindCameraUseCases(cameraLifecycle)
                    cameraLifecycle.createCamera(gameActivity).whenComplete { _, e ->
                        if(e != null) {
                            cameraStartListener?.invoke(null, e)
                        }
                    }
                }else {
                    cameraStartListener?.invoke(null, MediaPipeException(0, "Unable to got camera provider."))
                }

            }, ContextCompat.getMainExecutor(gameActivity)
        )
    }

    fun close(): CompletableFuture<Void> {
        cameraAnalyzerExecutor?.shutdown()
        val lifecycle = cameraLifecycle
        return if(lifecycle != null) {
            lifecycle.stopCamera(gameActivity).whenComplete { _, _ ->
                isStarted = false
            }
        }else {
            val f = CompletableFuture<Void>()
            isStarted = false
            f.complete(null)
            f
        }
    }

    fun getCameraState(cameraID: Int): Int {
        val state = camera?.cameraInfo?.cameraState?.value?.type ?: CameraState.Type.CLOSED
        return state.ordinal
    }

    private fun getCameraCharacteristics(
        context: Context,
        facing: CameraFacing
    ): CameraCharacteristics? {
        val lensFacing = getCameraLensFacing(facing)
        val cameraManager = context.getSystemService(Context.CAMERA_SERVICE) as CameraManager
        try {
            val cameraList = listOf(*cameraManager.cameraIdList)
            val var4: Iterator<*> = cameraList.iterator()
            while (var4.hasNext()) {
                val availableCameraId = var4.next() as String
                val availableCameraCharacteristics =
                    cameraManager.getCameraCharacteristics(availableCameraId)
                val availableLensFacing =
                    availableCameraCharacteristics.get(CameraCharacteristics.LENS_FACING)
                if (availableLensFacing != null && availableLensFacing == lensFacing) {
                    return availableCameraCharacteristics
                }
            }
        } catch (cameraEx: CameraAccessException) {
            MediaPipeUtils.Log.error("Accessing camera ID info got error: $cameraEx")
        }
        return null
    }

    fun getCameraViewSize(targetWidth: Int, targetHeight: Int): Size? {
        val cameraCharacteristics = getCameraCharacteristics(gameActivity, cameraFacing)?: return null
        val map = cameraCharacteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP) as StreamConfigurationMap
        val outputSizes = map.getOutputSizes(
            SurfaceTexture::class.java
        )
        var optimalSize: Size? = null
        val targetRatio = targetWidth.toDouble() / targetHeight.toDouble()
        MediaPipeUtils.Log.debug("Camera target size ratio: $targetRatio width: ${targetWidth}")
        var minCost = Double.MAX_VALUE
        val outputLen = outputSizes.size
        for (var11 in 0 until outputLen) {
            val size = outputSizes[var11]
            val aspectRatio = size.width.toDouble() / size.height.toDouble()
            val ratioDiff = abs(aspectRatio - targetRatio)
            val cost =
                (if (ratioDiff > 0.25) 10000.0 + ratioDiff * targetHeight.toDouble() else 0.0) + abs(
                    size.width - targetWidth
                ).toDouble()
            MediaPipeUtils.Log.debug("Camera size candidate width: ${size.width} height: ${size.height} ratio: $aspectRatio cost: $cost")
            if (cost < minCost) {
                optimalSize = size
                minCost = cost
            }
        }
        if (optimalSize != null) {
            MediaPipeUtils.Log.debug("Optimal camera size width: ${optimalSize.width} height: ${optimalSize.height}")
        }
        return optimalSize
    }

    @SuppressLint("UnsafeOptInUsageError", "WrongConstant", "RestrictedApi")
    private fun bindCameraUseCases(lifecycle: LifecycleOwner) {
        if (this.cameraAnalyzerExecutor == null) {
            this.cameraAnalyzerExecutor = Executors.newSingleThreadExecutor()
        }
        // CameraProvider
        val cameraProvider = cameraProvider
            ?: throw IllegalStateException("Camera initialization failed.")

        val cameraSelector =
            CameraSelector.Builder().requireLensFacing(getCameraLensFacing()).build()


        // Preview. Only using the 4:3 ratio because this is the closest to our models
//        val preview = Preview.Builder().setTargetAspectRatio(AspectRatio.RATIO_4_3)
//            .setTargetRotation(rotation)
//            .build()

        // ImageAnalysis. Using RGBA 8888 to match how our models work
        imageAnalyzer =
            ImageAnalysis.Builder().setTargetAspectRatio(AspectRatio.RATIO_4_3)
                //.setTargetRotation(rotation)
                .setBackpressureStrategy(ImageAnalysis.STRATEGY_KEEP_ONLY_LATEST)
                .setOutputImageFormat(ImageAnalysis.OUTPUT_IMAGE_FORMAT_RGBA_8888)
                .setMaxResolution(Size(1280, 1280))
                .build()
                // The analyzer can then be assigned to the instance
                .also {
                    it.setAnalyzer(cameraAnalyzerExecutor!!) { image ->
                        processFrame(image)
                    }
                }



        // Must unbind the use-cases before rebinding them
        cameraProvider.unbindAll()

        try {
            // A variable number of use-cases can be passed here -
            // camera provides access to CameraControl & CameraInfo
            camera = cameraProvider.bindToLifecycle(
                lifecycle, cameraSelector, imageAnalyzer!!
            )

            if(cameraStateCallback != null) {
                camera?.cameraInfo?.cameraState?.observe(lifecycle) { state ->
                    cameraStateCallback.invoke(state.type)
                }
            }
            // Attach the viewfinder's surface provider to preview use case
//            preview?.setSurfaceProvider(fragmentCameraBinding.viewFinder.surfaceProvider)
        } catch (exc: Exception) {
            MediaPipeUtils.Log.error("Use camera case binding failed", exc)
        }
    }

    private fun normalizeDegrees(degrees: Int): Int {
        val d = degrees % 360
        return if(d < 0) {
            360 + d
        }else {
            d
        }
    }

    private fun processFrame(
        imageProxy: ImageProxy
    ) {
        val callback = onFrame ?: return



        val bitmapBuffer =
            Bitmap.createBitmap(
                imageProxy.width,
                imageProxy.height,
                Bitmap.Config.ARGB_8888
            )

        imageProxy.use { bitmapBuffer.copyPixelsFromBuffer(imageProxy.planes[0].buffer) }
        imageProxy.close()

        val matrix = Matrix().apply {

            postRotate(imageProxy.imageInfo.rotationDegrees.toFloat())

            // flip image if user use front camera
            if (cameraFacing == CameraFacing.FRONT) {
                postScale(
                    -1f,
                    1f,
                    imageProxy.width.toFloat(),
                    imageProxy.height.toFloat()
                )
            }
        }

        val w = if(isScreenRotated) imageProxy.height else imageProxy.width
        val h = if(isScreenRotated) imageProxy.width else imageProxy.height

        val bitmap = Bitmap.createBitmap(
            bitmapBuffer, 0, 0, bitmapBuffer.width, bitmapBuffer.height,
            matrix, true
        )
        if(!isStarted) {
            cameraStartListener?.invoke(bitmap, null)
            isStarted = true
        }

        callback(bitmap)
    }
}