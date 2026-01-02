// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
package com.mediapipe4u

import android.app.Activity
import android.graphics.Bitmap
import android.graphics.SurfaceTexture
import android.os.Build
import android.os.Looper
import android.util.Size
import android.view.*
import androidx.camera.core.CameraSelector
import androidx.camera.core.CameraState
import com.epicgames.unreal.GameActivity
import com.epicgames.unreal.Logger
import com.google.android.gms.common.internal.Objects
import com.google.mediapipe.components.CameraHelper.CameraFacing
import com.google.mediapipe.components.CameraXPreviewHelper
import com.google.mediapipe.components.ExternalTextureConverter
import com.google.mediapipe.framework.AndroidAssetUtil
import com.google.mediapipe.framework.GraphGlSyncToken
import com.google.mediapipe.framework.TextureFrame
import com.google.mediapipe.glutil.EglManager
import java.util.concurrent.CompletableFuture
import java.util.concurrent.Executors
import java.util.concurrent.Semaphore
import kotlin.math.abs


/**
 * Helper methods for MediaPipe4U
 */
class MediaPipeUtils {
    /** ==============================================================  */
    enum class CallThread {
        CurrentThread, Background
    }



    companion object {

        /**************** Native Static Method **************/

        @JvmStatic
        private external fun nativeOnCameraStarted(
            previewWidth: Int,
            previewHeight: Int,
            isCameraRotated: Boolean
        )

        @JvmStatic
        private external fun nativeOnCameraClosed()

        @JvmStatic
        private external fun nativeOnCameraFailed()

        @JvmStatic
        private external fun nativeCameraFailed()

        @JvmStatic
        private external fun nativeGameActivityStart()

        @JvmStatic
        private external fun nativeSetMediaPipeCacheFolder(cacheRoot: String)

        @JvmStatic
        private external fun nativeLifecycleOnStart()

        @JvmStatic
        private external fun nativeLifecycleOnStop()

        @JvmStatic
        private external fun nativeLifecycleOnPause()

        @JvmStatic
        private external fun nativeLifecycleOnResume()

        @JvmStatic
        private external fun nativeOnCameraStateChanged(int: Int)

        @JvmStatic
        private external fun nativeOnOrientationChanged(degrees: Int)

        private val TARGET_SIZE = Size(1280, 720)

        val Log = Logger("MediaPipe4U", "Utils")

        private val startStopSyncRoot = Object()

        @JvmStatic
        fun get(): MediaPipeUtils {
            return GameActivity.Get().mediaPipeUtils
        }
    }

    private var previewDisplayView: SurfaceView? = null
    private var previewFrameTexture: SurfaceTexture? = null
    private lateinit var cameraHelper: CameraXPreviewHelper
    private lateinit var eglManager: EglManager
    private var converter: ExternalTextureConverter? = null
    private var expectedWidth: Int = 0
    private var expectedHeight: Int = 0
    private var isCameraOpened: Boolean = false
    private var cameraFace: CameraFacing = CameraFacing.FRONT
    private var activityStarted: Boolean = false
    private var screenRotation: Int = 0;
    private var orientationListener: OrientationEventListener? = null
    private var cameraLifecycle: CameraLifecycle? = null
    private val startStopLock = Semaphore(1)

    /**************** Native Instance Method **************/
    private external fun nativeInitialize()
    private external fun nativeOnTextureFrame(
        textureFrame: TextureFrame,
        textureId: Int,
        width: Int,
        height: Int
    ): Boolean

    private external fun nativeOnBitmapFrame(
        bitmap: Bitmap,
        width: Int,
        height: Int
    ): Boolean

    /*****************************************************/

    private val backgroundExecutor = Executors.newFixedThreadPool(
        (Runtime.getRuntime().availableProcessors() / 2).coerceAtMost(2)
    )

    private val gameActivity: GameActivity
        get() = GameActivity.Get()

    private fun callbackCameraFault(thread: CallThread) {
        if (thread == CallThread.CurrentThread) {
            nativeCameraFailed()
        }
        if (thread == CallThread.Background) {
            backgroundExecutor.execute { callbackCameraFault(CallThread.CurrentThread) }
        }
    }

    private fun isMainThread(): Boolean {
        return Looper.getMainLooper().thread === Thread.currentThread()
    }

    private fun callbackCameraStarted(size: Size, isRotated: Boolean, thread: CallThread) {
        if (thread == CallThread.CurrentThread) {
            nativeOnCameraStarted(size.width, size.height, isRotated)
        }
        if (thread == CallThread.Background) {
            backgroundExecutor.execute {
                callbackCameraStarted(
                    size,
                    isRotated,
                    CallThread.CurrentThread
                )
            }
        }
    }

    fun initializeMediaPipe4U(activity: Activity, layout: ViewGroup) {
        System.loadLibrary("mediapipe_api")
        Log.debug("Mediapipe api library (for android) was loaded.")
        orientationListener = object : OrientationEventListener(activity) {
            override fun onOrientationChanged(degrees: Int) {
                onOrientation(degrees)
            }
        }
        nativeInitialize()
        AndroidAssetUtil.initializeNativeAssetManager(activity)
        nativeSetMediaPipeCacheFolder(activity.cacheDir.absolutePath)

        //EGL14.eglGetCurrentContext()
        eglManager = EglManager(null)
        //previewDisplayView = SurfaceView(activity)
        //setupPreviewDisplayView(layout)
    }

    private fun setupPreviewDisplayView(viewGroup: ViewGroup) {
        if (previewDisplayView != null) {
            previewDisplayView?.visibility = View.GONE
            viewGroup.addView(previewDisplayView)

            previewDisplayView?.holder?.addCallback(
                object : SurfaceHolder.Callback {
                    override fun surfaceCreated(holder: SurfaceHolder) {}
                    override fun surfaceChanged(
                        holder: SurfaceHolder,
                        format: Int,
                        width: Int,
                        height: Int
                    ) {
                        val viewSize = Size(width, height)
                        val displaySize = cameraHelper.computeDisplaySizeFromViewSize(viewSize)

                        converter?.setSurfaceTextureAndAttachToGLContext(
                            previewFrameTexture, displaySize.width, displaySize.height
                        )
                    }

                    override fun surfaceDestroyed(holder: SurfaceHolder) {}
                })
        }
    }

    private fun stopCameraInternal(lock: Boolean = true): CompletableFuture<Void> {
        if(lock) {
            startStopLock.acquire()
        }
        converter?.close()

       //val lf = cameraLifecycle
       //if(lf != null)
       //{
       //    return lf.stopCamera(gameActivity).whenComplete { _,_->
       //        //cameraHelper.release()
       //        nativeOnCameraClosed()
       //        Log.debug("[MediaPipe API] Android camera closed.")
       //        startStopLock.release()
       //    }
       //
       //}

        val camera = cpuCameraAdapter
        if(camera != null) {
            return camera.close().whenComplete { _, _ ->
                nativeOnCameraClosed()
                Log.debug("[MediaPipe API] Android camera closed.")
                if(lock) {
                    startStopLock.release()
                }
            }
        }

        val f = CompletableFuture<Void>()
        f.complete(null)
        if(lock) {
            startStopLock.release()
        }
        return f
    }


    private fun getCameraLensFacing(): Int {
        return if(cameraFace == CameraFacing.BACK)  CameraSelector.LENS_FACING_BACK else CameraSelector.LENS_FACING_FRONT
    }

    private var cpuCameraAdapter: CpuCameraAdapter? = null

    private fun onCameraStateChanged(state: CameraState.Type) {
        nativeOnCameraStateChanged(state.ordinal);
    }

    private fun startCameraInternal(lock: Boolean = true): CompletableFuture<Void> {
        val f = CompletableFuture<Void>()
        if(lock) {
            startStopLock.acquire()
        }
        cpuCameraAdapter = CpuCameraAdapter(gameActivity, cameraFace, getDisplayRotation(), this::onCameraStateChanged)
        cpuCameraAdapter?.setOnStartCompletedListener { bitmap, _ ->
            if(bitmap != null) {
                isCameraOpened = true
                val isRotated = abs(getDisplayRotation() % 180) == 90
                callbackCameraStarted(Size(bitmap.width, bitmap.height), isRotated, CallThread.CurrentThread)
            }
            if(lock) {
                startStopLock.release()
            }
            f.complete(null)
        }

        cpuCameraAdapter?.setOnFrameListener {
            bitmap->
            nativeOnBitmapFrame(bitmap, bitmap.width, bitmap.height)
        }

        cpuCameraAdapter?.open()
        return f;
//        cameraLifecycle = CameraLifecycle()
//        converter = ExternalTextureConverter(eglManager.context, 5)
//        converter?.setConsumer {
//
//            if (it != null && !nativeOnTextureFrame(it, it.textureName, it.width, it.height)) {
//                it.release()
//            }
//        }
//        cameraHelper = CameraXPreviewHelper()
//        //need create gl surface
//        previewFrameTexture = converter?.surfaceTexture
//
//        cameraHelper.setOnCameraStartedListener {
//            try {
//                val rotated = cameraHelper.isCameraRotated
//                val displaySize = cameraHelper.frameSize!!
//                isCameraOpened = true
//                val finalSize = Size(
//                    if (rotated) displaySize.height else displaySize.width,
//                    if (rotated) displaySize.width else displaySize.height,
//                )
//                updateOutputSize(displaySize.width, displaySize.height)
//                //finalSize = Size(displaySize.height, displaySize.width)
//
//                callbackCameraStarted(finalSize, rotated, CallThread.CurrentThread)
//            } finally {
//                startStopLock.release()
//            }
//        }
//        try {
//            cameraHelper.startCamera(gameActivity,cameraLifecycle, cameraFace, previewFrameTexture, Size(expectedWidth,expectedHeight))
//        }catch (ex:Exception)
//        {
//            Log.error(ex.message)
//        }finally {
//            startStopLock.release()
//        }
//
//        cameraLifecycle?.createCamera(gameActivity)
    }

    fun updateOutputSize(width: Int, height: Int) {
        val displaySize = cameraHelper.computeDisplaySizeFromViewSize(Size(width, height))
        val isCameraRotated = cameraHelper.isCameraRotated

        // Configure the output width and height as the computed
        // display size.
        converter?.setDestinationSize(
            if (isCameraRotated) displaySize.height else displaySize.width,
            if (isCameraRotated) displaySize.width else displaySize.height
        )
    }

    private fun getDisplay(): Display {
        return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            gameActivity.display!!
        } else {
            gameActivity.windowManager.defaultDisplay
        }
    }

    private fun getScreenOrientation(): ScreenOrientation {
        return if(getDisplayRotation() % 180 == 90) ScreenOrientation.LANDSCAPE else ScreenOrientation.PORTRAIT
    }

    private fun getDisplayRotation(): Int {
        return when (getDisplay().rotation) {
            Surface.ROTATION_0 -> 0
            Surface.ROTATION_90 -> 90
            Surface.ROTATION_180 -> 180
            Surface.ROTATION_270 -> 270
            else -> 0
        }
    }


    private fun onOrientation(degrees: Int) {
        if (GameActivity.Get() == null) {
            return
        }
        val newOrientation: Int = getDisplayRotation()
        if (screenRotation != newOrientation) {
            screenRotation = newOrientation
//            cpuCameraAdapter?.changeScreenOrientation(screenRotation)
            restartCamera()
            nativeOnOrientationChanged(screenRotation)
        }
    }

    fun getScreenRotationDegrees(): Int {
        return screenRotation
    }

    fun onStart() {
        if (!activityStarted) {
            nativeGameActivityStart()
            activityStarted = true
        }
        nativeLifecycleOnStart()
    }

    fun onStop() {
        nativeLifecycleOnStop()
    }

    fun onResume() {
        orientationListener?.enable();
        nativeLifecycleOnResume()
    }

    fun onPause() {
        orientationListener?.disable();
        previewDisplayView?.visibility = View.GONE
        nativeLifecycleOnPause()
    }

    fun getCameraState(cameraType: Int): Int {
        return cpuCameraAdapter?.getCameraState(cameraType) ?: CameraState.Type.CLOSED.ordinal
    }

    fun restartCamera() {
        startStopLock.acquire()
        if(isCameraOpened) {
            stopCameraInternal(false).whenComplete {
                    _, _->
                startCameraInternal(false).whenComplete { _, _ ->
                    startStopLock.release();
                }
            }
        }
    }

    fun startCamera(cameraType: Int, frameWidth: Int, frameHeight: Int, fps: Int) {
        synchronized(startStopSyncRoot) {
            cameraFace = if (cameraType == 0) CameraFacing.FRONT else CameraFacing.BACK
            //if(frameWidth < frameHeight) {
            //     expectedWidth = frameWidth
            //     expectedHeight = frameHeight
            //} else {
            //     expectedWidth = frameHeight
            //     expectedHeight = frameWidth
            //}
            expectedWidth = frameWidth
            expectedHeight = frameHeight

            startCameraInternal()
        }
    }

    fun stopCamera() {
        synchronized(startStopSyncRoot) {
            stopCameraInternal().whenComplete { _, _ ->
                isCameraOpened = false
            }
        }
    }

    fun releaseTexture(frame: TextureFrame) {
        frame.release();
    }

    fun releaseTextureWithToken(frame: TextureFrame, nativeSyncToken: Long) {
        frame.release(GraphGlSyncToken(nativeSyncToken));
    }

    fun getGLContext(): Long {
        if (!this::eglManager.isInitialized) {
            return 0
        }
        return eglManager.nativeContext
    }
}