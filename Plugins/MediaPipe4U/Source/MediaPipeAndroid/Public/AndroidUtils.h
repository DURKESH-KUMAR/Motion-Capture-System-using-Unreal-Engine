// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "ThreadSafedDeletgateMarcos.h"

/**
 * Same as Java define: CameraState.Type
 */
enum class EAndroidCameraState
{
	PENDING_OPEN,
	OPENING,
	OPEN,
	CLOSING,
	CLOSED
};

struct MEDIAPIPEANDROID_API FAndroidCameraInfo
{
	int PreviewWidth = 0;
	int PreviewHeight = 0;
	bool bIsCameraRotated = false; 
};


struct MEDIAPIPEANDROID_API FJavaTextureFrame
{
	void* TextureJavaObject = nullptr;
	int64 TextureId = 0;
	int Width = 0;
	int Height = 0;
	bool bIsGPU = true;
};

class FCameraNative;


class MEDIAPIPEANDROID_API FAndroidUtils
{
public:
	DECLARE_THREAD_SAFE_EVENT(FAndroidUtils, FOnAndroidGameActivityStart)
	DECLARE_THREAD_SAFE_EVENT(FAndroidUtils, FOnAndroidLifecycle)
	DECLARE_THREAD_SAFE_EVENT_OneParam(FAndroidUtils, FOnAndroidOrientationChanged, int)
	DECLARE_THREAD_SAFE_EVENT_OneParam(FAndroidUtils, FOnCameraStateChanged, int)

	static  FAndroidUtils & Get();
	void* GetJNIEnv();
	bool IsAndroid();
	static FString CameraStateToString(const EAndroidCameraState& State);
	bool IsAsset(const FString& FilePath);
	bool EnumerateAssetFiles(const FString& AssetFolder, TArray<FString>& AssetFiles);
	bool LoadAssetToString(FString& Result, const FString& FilePath);
	bool LoadAssetToBytes(TArray<uint8>& Result, const FString& FilePath);
	const FString& GetAndroidBaseFolder();
	bool ResourceToFile(const FString& ResourcePath, const FString& FileFolder, FString& OutFile);
	const FString& GetMediaPipeCacheFolder();
	void SetMediaPipeCacheFolder(const FString& Folder);
	void ReleaseTexture(void* JavaTextureFrame);
	void ReleaseTextureWithSyncToken(void* JavaTextureFrame, int64 Token);
	int64 GetGLContext();
	int GetScreenRotationDegrees();

public:
	FOnAndroidGameActivityStart& AndroidGameActivityStartEvent();
	FOnAndroidLifecycle& AndroidLifecycleOnStartEvent();
	FOnAndroidLifecycle& AndroidLifecycleOnStopEvent();
	FOnAndroidLifecycle& AndroidLifecycleOnPauseEvent();
	FOnAndroidLifecycle& AndroidLifecycleOnResumeEvent();

	FOnAndroidOrientationChanged& AndroidOrientationChangedEvent();
	FOnCameraStateChanged& AndroidCameraStateChangedEvent();
	//rasise event
	bool RaiseAndroidGameActivityStartEvent() const;
	bool RaiseAndroidLifecycleOnStartEvent() const;
	bool RaiseAndroidLifecycleOnStopEvent() const;
	bool RaiseAndroidLifecycleOnPauseEvent() const;
	bool RaiseAndroidLifecycleOnResumeEvent() const; 
	bool RaiseAndroidOrientationChangedEvent(int Degrees) const;
	void RaiseAndroidCameraStateChangedEvent(int State) const;
private:
	FString MediaPipeCacheFolder;
	FOnAndroidGameActivityStart AndroidGameActivityStart;
	FOnAndroidLifecycle AndroidLifecycleOnStart;
	FOnAndroidLifecycle AndroidLifecycleOnStop;
	FOnAndroidLifecycle AndroidLifecycleOnPause;
	FOnAndroidLifecycle AndroidLifecycleOnResume;
	FOnAndroidOrientationChanged AndroidOrientationChanged;
	FOnCameraStateChanged AndroidCameraStateChanged;

	FAndroidUtils();
	friend class FLazySingleton;
};

