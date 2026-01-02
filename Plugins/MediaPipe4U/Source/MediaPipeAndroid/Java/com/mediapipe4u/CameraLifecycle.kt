package com.mediapipe4u

import android.app.Activity
import android.os.Looper
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.LifecycleOwner
import androidx.lifecycle.LifecycleRegistry
import java.util.concurrent.CompletableFuture

class CameraLifecycle : LifecycleOwner {

    private var lifecycleRegistry: LifecycleRegistry = LifecycleRegistry(this)

    fun cameraOnCreate() {
        lifecycleRegistry.handleLifecycleEvent(Lifecycle.Event.ON_CREATE)
    }

    fun cameraOnStart() {
        lifecycleRegistry.handleLifecycleEvent(Lifecycle.Event.ON_START)
    }

    fun cameraOnResume() {
        lifecycleRegistry.handleLifecycleEvent(Lifecycle.Event.ON_RESUME)
    }

    fun cameraOnPause() {
        lifecycleRegistry.handleLifecycleEvent(Lifecycle.Event.ON_PAUSE)
    }

    fun cameraOnStop() {
        lifecycleRegistry.handleLifecycleEvent(Lifecycle.Event.ON_STOP)
    }

    fun cameraOnDestroyed() {
        lifecycleRegistry.handleLifecycleEvent(Lifecycle.Event.ON_DESTROY)
    }

    override fun getLifecycle(): Lifecycle {
        return lifecycleRegistry
    }

    private fun isMainThread(): Boolean {
        return Looper.getMainLooper().thread === Thread.currentThread()
    }

    fun createCamera(activity: Activity): CompletableFuture<Void> {
        val future = CompletableFuture<Void>()
        if (isMainThread()) {
            cameraOnCreate()
            cameraOnStart()
            cameraOnResume()
            future.complete(null)
        } else {
            activity.runOnUiThread {
                cameraOnCreate()
                cameraOnStart()
                cameraOnResume()
                future.complete(null)
            }
        }
        return future
    }

    fun stopCamera(activity: Activity): CompletableFuture<Void> {
        return stopCamera(activity, false)
    }


    private fun stopCamera(activity: Activity, destroy: Boolean, feature: CompletableFuture<Void>? = null): CompletableFuture<Void> {
        val f = feature ?: CompletableFuture<Void>()
        if (isMainThread()) {
            cameraOnPause()
            cameraOnStop()
            if(destroy) {
                cameraOnDestroyed()
            }
            f.complete(null)
        } else {
            activity.runOnUiThread {
                stopCamera(activity, destroy, f)
            }
        }
        return f
    }
}