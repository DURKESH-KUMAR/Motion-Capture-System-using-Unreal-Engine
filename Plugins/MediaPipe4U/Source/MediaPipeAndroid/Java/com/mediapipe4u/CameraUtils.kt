// Anders Xiao Modified from CameraXPreviewHelper.
// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
package com.mediapipe4u

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Context
import android.graphics.SurfaceTexture
import android.hardware.camera2.CameraAccessException
import android.hardware.camera2.CameraCharacteristics
import android.hardware.camera2.CameraManager
import android.hardware.camera2.CameraMetadata
import android.media.CameraProfile
import android.opengl.GLES20
import android.os.Handler
import android.os.HandlerThread
import android.os.Process
import android.os.SystemClock
import android.util.Size
import android.view.Surface
import androidx.camera.core.*
import androidx.camera.core.SurfaceRequest.TransformationInfo
import androidx.camera.core.impl.utils.CameraOrientationUtil
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import com.epicgames.unreal.Logger
import com.google.common.util.concurrent.ListenableFuture
import com.google.mediapipe.components.CameraHelper
import com.google.mediapipe.glutil.EglManager
import java.io.File
import java.util.*
import java.util.concurrent.Executor
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import java.util.concurrent.RejectedExecutionException
import kotlin.math.abs

/**
 * Uses CameraX APIs for camera setup and access.
 *
 *
 * [CameraX] connects to the camera and provides video frames.
 */
class CameraUtils : CameraHelper() {
    /**
     * Provides an Executor that wraps a single-threaded Handler.
     *
     *
     * All operations involving the surface texture should happen in a single thread, and that
     * thread should not be the main thread.
     *
     *
     * The surface provider callbacks require an Executor, and the onFrameAvailable callback
     * requires a Handler. We want everything to run on the same thread, so we need an Executor that
     * is also a Handler.
     */
    private class SingleThreadHandlerExecutor internal constructor(
        threadName: String?,
        priority: Int
    ) :
        Executor {
        private val handlerThread: HandlerThread
        private val handler: Handler

        init {
            handlerThread = HandlerThread(threadName, priority)
            handlerThread.start()
            handler = Handler(handlerThread.looper)
        }

        override fun execute(command: Runnable) {
            if (!handler.post(command)) {
                throw RejectedExecutionException(handlerThread.name + " is shutting down.")
            }
        }

        fun shutdown(): Boolean {
            return handlerThread.quitSafely()
        }
    }

    private val renderExecutor =
        SingleThreadHandlerExecutor("RenderThread", Process.THREAD_PRIORITY_DEFAULT)
    private var cameraProvider: ProcessCameraProvider? = null
    private var preview: Preview? = null
    private var imageCapture: ImageCapture? = null
    private var imageCaptureBuilder: ImageCapture.Builder? = null
    private var imageCaptureExecutorService: ExecutorService? = null
    private var camera: Camera? = null
    private var textures: IntArray? = null

    // Size of the camera-preview frames from the camera.
    var frameSize: Size? = null
        private set

    // Rotation of the camera-preview frames in degrees.
    private var frameRotation = 0

    // Checks if the image capture use case is enabled.
    private var isImageCaptureEnabled = false

    private var cameraCharacteristics: CameraCharacteristics? = null

    // Focal length resolved in pixels on the frame texture. If it cannot be determined, this value
    // is Float.MIN_VALUE.
    var focalLengthPixels = Float.MIN_VALUE
        private set

    // Timestamp source of camera. This is retrieved from
    // CameraCharacteristics.SENSOR_INFO_TIMESTAMP_SOURCE. When CameraCharacteristics is not available
    // the source is CameraCharacteristics.SENSOR_INFO_TIMESTAMP_SOURCE_UNKNOWN.
    private var cameraTimestampSource = CameraCharacteristics.SENSOR_INFO_TIMESTAMP_SOURCE_UNKNOWN

    /**
     * Initializes the camera and sets it up for accessing frames, using the default 1280 * 720
     * preview size.
     */
    override fun startCamera(
        activity: Activity, cameraFacing: CameraFacing, surfaceTexture: SurfaceTexture?
    ) {
        startCamera(activity, activity as LifecycleOwner, cameraFacing, surfaceTexture, TARGET_SIZE)
    }

    /**
     * Initializes the camera and sets it up for accessing frames.
     *
     * @param targetSize the preview size to use. If set to `null`, the helper will default to
     * 1280 * 720.
     */
    fun startCamera(
        activity: Activity,
        cameraFacing: CameraFacing,
        surfaceTexture: SurfaceTexture?,
        targetSize: Size?
    ) {
        startCamera(activity, activity as LifecycleOwner, cameraFacing, surfaceTexture, targetSize)
    }

    /**
     * Initializes the camera and sets it up for accessing frames. This constructor also enables the
     * image capture use case from [CameraX].
     *
     * @param imageCaptureBuilder Builder for an [ImageCapture], this builder must contain the
     * desired configuration options for the image capture being build (e.g. target resolution).
     * @param targetSize the preview size to use. If set to `null`, the helper will default to
     * 1280 * 720.
     */
    fun startCamera(
        activity: Activity,
        imageCaptureBuilder: ImageCapture.Builder,
        cameraFacing: CameraFacing,
        targetSize: Size?,
        screenOrientation: ScreenOrientation = ScreenOrientation.PORTRAIT
    ) {
        this.imageCaptureBuilder = imageCaptureBuilder
        startCamera(activity, activity as LifecycleOwner, cameraFacing, targetSize, screenOrientation)
    }

    /**
     * Initializes the camera and sets it up for accessing frames. This constructor also enables the
     * image capture use case from [CameraX].
     *
     * @param imageCaptureBuilder Builder for an [ImageCapture], this builder must contain the
     * desired configuration options for the image capture being build (e.g. target resolution).
     * @param targetSize the preview size to use. If set to `null`, the helper will default to
     * 1280 * 720.
     */
    fun startCamera(
        activity: Activity,
        imageCaptureBuilder: ImageCapture.Builder,
        cameraFacing: CameraFacing,
        surfaceTexture: SurfaceTexture?,
        targetSize: Size?,
        screenOrientation: ScreenOrientation = ScreenOrientation.PORTRAIT
    ) {
        this.imageCaptureBuilder = imageCaptureBuilder
        startCamera(activity, activity as LifecycleOwner, cameraFacing, surfaceTexture, targetSize, screenOrientation)
    }

    /**
     * Initializes the camera and sets it up for accessing frames.
     *
     * @param targetSize a predefined constant [.TARGET_SIZE]. If set to `null`, the
     * helper will default to 1280 * 720.
     */
    fun startCamera(
        context: Context,
        lifecycleOwner: LifecycleOwner,
        cameraFacing: CameraFacing,
        targetSize: Size? = null,
        screenOrientation: ScreenOrientation = ScreenOrientation.PORTRAIT
    ) {
        startCamera(context, lifecycleOwner, cameraFacing, null, targetSize, screenOrientation)
    }

    fun release()
    {
        cameraProvider?.unbindAll()
    }

    /**
     * Initializes the camera and sets it up for accessing frames.
     *
     * @param size a predefined constant [.TARGET_SIZE]. If set to `null`, the
     * helper will default to 1280 * 720.
     */
    @SuppressLint("UnsafeOptInUsageError")
    private fun startCamera(
        context: Context,
        lifecycleOwner: LifecycleOwner,
        cameraFacing: CameraFacing,
        surfaceTexture: SurfaceTexture?,
        size: Size?,
        screenOrientation: ScreenOrientation = ScreenOrientation.PORTRAIT
    ) {
        var targetSize: Size = size ?: TARGET_SIZE
        val mainThreadExecutor = ContextCompat.getMainExecutor(context)

        val cameraProviderFuture = ProcessCameraProvider.getInstance(context)
        val isSurfaceTextureProvided = surfaceTexture != null
        val selectedLensFacing =
            if (cameraFacing == CameraFacing.FRONT) CameraMetadata.LENS_FACING_FRONT else CameraMetadata.LENS_FACING_BACK
        cameraCharacteristics = getCameraCharacteristics(context, selectedLensFacing)
        targetSize = getOptimalViewSize(targetSize) ?: TARGET_SIZE

        // According to CameraX documentation
        // (https://developer.android.com/training/camerax/configuration#specify-resolution):
        // "Express the resolution Size in the coordinate frame after rotating the supported sizes by
        // the target rotation."
        val rotatedSize = if(screenOrientation == ScreenOrientation.PORTRAIT) Size(targetSize.height, targetSize.width) else Size(targetSize.width, targetSize.height)
        cameraProviderFuture.addListener(
            {
                cameraProvider = try {
                    cameraProviderFuture.get()
                } catch (e: Exception) {
                    if (e is InterruptedException) {
                        Thread.currentThread().interrupt()
                    }
                    Log.error(
                        "Unable to get ProcessCameraProvider: $e",
                    )
                    return@addListener
                }
                preview =
                    Preview.Builder().setTargetResolution(rotatedSize).build()
                val cameraSelector =
                    if (cameraFacing == CameraFacing.FRONT) CameraSelector.DEFAULT_FRONT_CAMERA else CameraSelector.DEFAULT_BACK_CAMERA

                // Provide surface texture.
                preview!!.setSurfaceProvider(
                    renderExecutor
                ) { request: SurfaceRequest ->
                    frameSize = request.resolution
                    Log.debug("Received surface request for resolution ${frameSize!!.width}x${frameSize!!.height}")
                    val previewFrameTexture =
                        if (isSurfaceTextureProvided) surfaceTexture else createSurfaceTexture()
                    previewFrameTexture!!.setDefaultBufferSize(
                        frameSize!!.width, frameSize!!.height
                    )
                    request.setTransformationInfoListener(
                        renderExecutor
                    ) { transformationInfo: TransformationInfo ->
                        frameRotation = transformationInfo.rotationDegrees
                        updateCameraCharacteristics()
                        if (!isSurfaceTextureProvided) {
                            // Detach the SurfaceTexture from the GL context we created earlier so that
                            // the MediaPipe pipeline can attach it.
                            // Only needed if MediaPipe pipeline doesn't provide a SurfaceTexture.
                            previewFrameTexture.detachFromGLContext()
                        }
                        val listener = onCameraStartedListener
                        if (listener != null) {
                            ContextCompat.getMainExecutor(context)
                                .execute {
                                    listener.onCameraStarted(
                                        previewFrameTexture
                                    )
                                }
                        }
                    }
                    val surface =
                        Surface(previewFrameTexture)
                    Log.debug(
                        "Providing surface"
                    )
                    request.provideSurface(
                        surface,
                        renderExecutor
                    ) { result: SurfaceRequest.Result ->
                        Log.debug(
                            "Surface request result: $result"
                        )
                        if (textures != null) {
                            GLES20.glDeleteTextures(1, textures, 0)
                        }
                        // Per
                        // https://developer.android.com/reference/androidx/camera/core/SurfaceRequest.Result,
                        // the surface was either never used (RESULT_INVALID_SURFACE,
                        // RESULT_REQUEST_CANCELLED, RESULT_SURFACE_ALREADY_PROVIDED) or the surface
                        // was used successfully and was eventually detached
                        // (RESULT_SURFACE_USED_SUCCESSFULLY) so we can release it now to free up
                        // resources.
                        if (!isSurfaceTextureProvided) {
                            previewFrameTexture.release()
                        }
                        surface.release()
                    }
                }

                // If we pause/resume the activity, we need to unbind the earlier preview use case, given
                // the way the activity is currently structured.
                cameraProvider?.unbindAll()

                // Bind use case(s) to camera.
                if (imageCaptureBuilder != null) {
                    imageCapture = imageCaptureBuilder!!.build()
                    camera = cameraProvider?.bindToLifecycle(
                        lifecycleOwner, cameraSelector, preview, imageCapture
                    )
                    imageCaptureExecutorService =
                        Executors.newSingleThreadExecutor()
                    isImageCaptureEnabled = true
                } else {
                    camera = cameraProvider?.bindToLifecycle(lifecycleOwner, cameraSelector, preview)

                }
            },
            mainThreadExecutor
        )
    }

    /**
     * Captures a new still image and saves to a file along with application specified metadata. This
     * method works when [startCamera] has been called previously enabling image capture. The callback will be
     * called only once for every invocation of this method.
     *
     * @param outputFile Save location for captured image.
     * @param onImageSavedCallback Callback to be called for the newly captured image.
     */
    fun takePicture(outputFile: File?, onImageSavedCallback: ImageCapture.OnImageSavedCallback?) {
        if (isImageCaptureEnabled) {
            val outputFileOptions = ImageCapture.OutputFileOptions.Builder(
                outputFile!!
            ).build()
            imageCapture!!.takePicture(
                outputFileOptions, imageCaptureExecutorService!!, onImageSavedCallback!!
            )
        }
    }

    override fun isCameraRotated(): Boolean {
        return frameRotation % 180 == 90
    }

    override fun computeDisplaySizeFromViewSize(viewSize: Size): Size {
        // Camera target size is computed already, so just return the capture frame size.
        return frameSize!!
    }

    private fun getOptimalViewSize(targetSize: Size): Size? {
        if (cameraCharacteristics == null) {
            return null
        }
        val map = cameraCharacteristics!!.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP)
        val outputSizes = map!!.getOutputSizes(
            SurfaceTexture::class.java
        )

        // Find the best matching size. We give a large penalty to sizes whose aspect
        // ratio is too different from the desired one. That way we choose a size with
        // an acceptable aspect ratio if available, otherwise we fall back to one that
        // is close in width.
        var optimalSize: Size? = null
        val targetRatio = targetSize.width.toDouble() / targetSize.height
        Log.debug( "Camera target size ratio: $targetRatio width: ${targetSize.width}")
        var minCost = Double.MAX_VALUE
        for (size in outputSizes) {
            val aspectRatio = size.width.toDouble() / size.height
            val ratioDiff = abs(aspectRatio - targetRatio)

            val c1: Double = if (ratioDiff > ASPECT_TOLERANCE) ASPECT_PENALTY + ratioDiff * targetSize.height else 0.0

            val cost: Double = c1 + abs(size.width - targetSize.width).toDouble()
            Log.debug("Camera size candidate width: ${size.width} height: ${size.height} ratio: $aspectRatio cost: $cost")
            if (cost < minCost) {
                optimalSize = size
                minCost = cost
            }
        }
        if (optimalSize != null) {
            Log.debug("Optimal camera size width: ${optimalSize.width} height: ${optimalSize.height}")
        }
        return optimalSize
    }// This clock shares the same timebase as SystemClock.elapsedRealtimeNanos(), see

    // https://developer.android.com/reference/android/hardware/camera2/CameraMetadata.html#SENSOR_INFO_TIMESTAMP_SOURCE_REALTIME.
    // Computes the difference between the camera's clock and MONOTONIC clock using camera's
    // timestamp source information. This function assumes by default that the camera timestamp
    // source is aligned to CLOCK_MONOTONIC. This is useful when the camera is being used
    // synchronously with other sensors that yield timestamps in the MONOTONIC timebase, such as
    // AudioRecord for audio data. The offset is returned in nanoseconds.
    val timeOffsetToMonoClockNanos: Long
        get() = if (cameraTimestampSource == CameraMetadata.SENSOR_INFO_TIMESTAMP_SOURCE_REALTIME) {
            // This clock shares the same timebase as SystemClock.elapsedRealtimeNanos(), see
            // https://developer.android.com/reference/android/hardware/camera2/CameraMetadata.html#SENSOR_INFO_TIMESTAMP_SOURCE_REALTIME.
            offsetFromRealtimeTimestampSource
        } else {
            offsetFromUnknownTimestampSource
        }

    private fun updateCameraCharacteristics() {
        if (cameraCharacteristics != null) {
            // Queries camera timestamp source. It should be one of REALTIME or UNKNOWN
            // as documented in
            // https://developer.android.com/reference/android/hardware/camera2/CameraCharacteristics.html#SENSOR_INFO_TIMESTAMP_SOURCE.
            cameraTimestampSource =
                cameraCharacteristics!!.get(CameraCharacteristics.SENSOR_INFO_TIMESTAMP_SOURCE)!!
            focalLengthPixels = calculateFocalLengthInPixels()
        }
    }

    // Computes the focal length of the camera in pixels based on lens and sensor properties.
    private fun calculateFocalLengthInPixels(): Float {
        // Focal length of the camera in millimeters.
        // Note that CameraCharacteristics returns a list of focal lengths and there could be more
        // than one focal length available if optical zoom is enabled or there are multiple physical
        // cameras in the logical camera referenced here. A theoretically correct of doing this would
        // be to use the focal length set explicitly via Camera2 API, as documented in
        // https://developer.android.com/reference/android/hardware/camera2/CaptureRequest#LENS_FOCAL_LENGTH.
        val focalLengthMm =
            cameraCharacteristics!!.get(CameraCharacteristics.LENS_INFO_AVAILABLE_FOCAL_LENGTHS)!![0]
        // Sensor Width of the camera in millimeters.
        val sensorWidthMm =
            cameraCharacteristics!!.get(CameraCharacteristics.SENSOR_INFO_PHYSICAL_SIZE)!!
                .width
        return frameSize!!.width * focalLengthMm / sensorWidthMm
    }

    private fun createSurfaceTexture(): SurfaceTexture {
        // Create a temporary surface to make the context current.
        val eglManager = EglManager(null)
        val tempEglSurface =
            eglManager.createOffscreenSurface(1, 1)
        eglManager.makeCurrent(tempEglSurface, tempEglSurface)
        textures = IntArray(1)
        GLES20.glGenTextures(1, textures, 0)
        return SurfaceTexture(textures!![0])
    }

    companion object {
        private val Log = Logger("MediaPipe4U", "Camera")

        // Target frame and view resolution size in landscape.
        private val TARGET_SIZE = Size(1280, 720)
        private const val ASPECT_TOLERANCE = 0.25
        private const val ASPECT_PENALTY = 10000.0

        // Number of attempts for calculating the offset between the camera's clock and MONOTONIC clock.
        private const val CLOCK_OFFSET_CALIBRATION_ATTEMPTS = 3

        // Implementation-wise, this timestamp source has the same timebase as CLOCK_MONOTONIC, see
        // https://stackoverflow.com/questions/38585761/what-is-the-timebase-of-the-timestamp-of-cameradevice.
        private val offsetFromUnknownTimestampSource: Long
            get() =// Implementation-wise, this timestamp source has the same timebase as CLOCK_MONOTONIC, see
                // https://stackoverflow.com/questions/38585761/what-is-the-timebase-of-the-timestamp-of-cameradevice.
                0L

        // Measure the offset of the REALTIME clock w.r.t. the MONOTONIC clock. Do
        // CLOCK_OFFSET_CALIBRATION_ATTEMPTS measurements and choose the offset computed with the
        // smallest delay between measurements. When the camera returns a timestamp ts, the
        // timestamp in MONOTONIC timebase will now be (ts + cameraTimeOffsetToMonoClock).
        private val offsetFromRealtimeTimestampSource: Long
            get() {
                // Measure the offset of the REALTIME clock w.r.t. the MONOTONIC clock. Do
                // CLOCK_OFFSET_CALIBRATION_ATTEMPTS measurements and choose the offset computed with the
                // smallest delay between measurements. When the camera returns a timestamp ts, the
                // timestamp in MONOTONIC timebase will now be (ts + cameraTimeOffsetToMonoClock).
                var offset = Long.MAX_VALUE
                var lowestGap = Long.MAX_VALUE
                for (i in 0 until CLOCK_OFFSET_CALIBRATION_ATTEMPTS) {
                    val startMonoTs = System.nanoTime()
                    val realTs = SystemClock.elapsedRealtimeNanos()
                    val endMonoTs = System.nanoTime()
                    val gapMonoTs = endMonoTs - startMonoTs
                    if (gapMonoTs < lowestGap) {
                        lowestGap = gapMonoTs
                        offset = (startMonoTs + endMonoTs) / 2 - realTs
                    }
                }
                return offset
            }

        private fun getCameraCharacteristics(
            context: Context, lensFacing: Int
        ): CameraCharacteristics? {
            val cameraManager = context.getSystemService(Context.CAMERA_SERVICE) as CameraManager
            try {
                val cameraList = listOf(*cameraManager.cameraIdList)
                for (availableCameraId in cameraList) {
                    val availableCameraCharacteristics =
                        cameraManager.getCameraCharacteristics(availableCameraId)
                    val availableLensFacing =
                        availableCameraCharacteristics.get(CameraCharacteristics.LENS_FACING)
                            ?: continue
                    if (availableLensFacing == lensFacing) {
                        return availableCameraCharacteristics
                    }
                }
            } catch (e: CameraAccessException) {
                Log.error("Accessing camera ID info got error: $e")
            }
            return null
        }
    }
}