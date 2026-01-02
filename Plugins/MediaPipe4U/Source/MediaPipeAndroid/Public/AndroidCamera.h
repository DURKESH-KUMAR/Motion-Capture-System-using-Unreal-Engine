// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "AndroidCameraType.h"
#include "AndroidUtils.h"
#include "Async/Future.h"
#include "ThreadSafedDeletgateMarcos.h"

class FAndroidCamera;

DECLARE_THREAD_SAFE_EVENT_OneParam(FAndroidCamera, FOnAndroidCameraStateChanged, EAndroidCameraState);
DECLARE_THREAD_SAFE_EVENT(FAndroidCamera, FOnAndroidCameraError);
DECLARE_THREAD_SAFE_EVENT(FAndroidCamera, FOnAndroidCameraClosed);
DECLARE_THREAD_SAFE_EVENT_OneParam(FAndroidCamera, FOnAndroidCameraOpened, const FAndroidCameraInfo&);
DECLARE_THREAD_SAFE_EVENT_TwoParams(FAndroidCamera, FOnAndroidTextureFrame, const FJavaTextureFrame& /*TextureFrame*/, const FAndroidCameraInfo& /*CameraInfo*/);

//Need java intergration 
class MEDIAPIPEANDROID_API FAndroidCamera
{
public:
	static  FAndroidCamera& Get();

	void Start(EAndroidCameraType CameraType, int FrameWidth, int FrameHeight, int FPS);
	void Stop();

	void OnCameraOpened(int PreviewWidth, int PreviewHeight, bool bIsCameraRotated);
	void OnCameraClosed();
	void OnCameraError();
	void OnCameraStateChanged(int InState);
	bool OnCameraTextureFrame(void* TextureFrame, int64 TextureId, int FrameWidth, int FrameHeight);
	bool OnCameraBitmapFrame(void* Bitmap, int FrameWidth, int FrameHeight);
	EAndroidCameraState GetCameraState(bool bRefreshState = false);

	FOnAndroidCameraStateChanged OnStateChanged;
	FOnAndroidCameraError OnError;
	FOnAndroidCameraOpened OnOpened;
	FOnAndroidTextureFrame OnTextureFrame;
	FOnAndroidCameraClosed OnClosed;
	
private:
	bool SetState(EAndroidCameraState InState);
	FCriticalSection StateMutex;
	FCriticalSection OpenCloseMutex;
	FAndroidCameraInfo CameraInfo;
	bool bCloseRequested = false;
	EAndroidCameraState State = EAndroidCameraState::CLOSED;
	FAndroidCamera();
	TSharedPtr<TPromise<void>> OpenPromise;
	TSharedFuture<void> OpenFuture;
	TSharedPtr<TPromise<void>> ClosePromise;
	TSharedFuture<void> CloseFuture;
	EAndroidCameraType CurrentCamera;
	friend class FLazySingleton;
	
};
