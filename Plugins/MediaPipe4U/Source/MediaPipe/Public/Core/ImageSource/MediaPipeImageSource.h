// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "IImageConsumer.h"
#include "ResolutionLimits.h"
#include "RotationAngle.h"
#include "FrameTransform.h"
#include "Macros/ThreadSafedDeletgateMarcos.h"
#include "ump_commons.h"
#include "Engine/Texture2D.h"
#include "UObject/Interface.h"
#include "MediaPipeImageSource.generated.h"


class IMediaPipeImageSource;
 
DECLARE_THREAD_SAFE_EVENT_ThreeParams(IMediaPipeImageSource, FTextureCreatedDelegate, UTexture2D*, int, int);
DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeImageSource, FOnImageSourceOpened, const FImageSourceInfo&); 

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class  UMediaPipeImageSource : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIAPIPE_API IMediaPipeImageSource
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="MediaPipe")
	int GetFrameWidth();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="MediaPipe")
	int GetFrameHeight();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="MediaPipe")
	bool IsStaticSource();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="MediaPipe")
	bool IsFrameCreated();
	
	FTextureCreatedDelegate& OnTextureCreatedTrigger();
	FOnImageSourceOpened& OnImageSourceOpenedTrigger();
	
	virtual  IImageSource* GetImageSource() =0;
	virtual bool IsSupportHorizontalFlip() = 0;
	virtual bool IsSupportLimitResolution() = 0;
	virtual void LimitResolution(int ResolutionX, int ResolutionY) = 0;
	virtual void SetHorizontalFlip(bool bFlip) = 0;
	virtual void UnLimitResolution() = 0;
	virtual bool CorrectFrame(FFrameTransform& InOutTransform) = 0;

	virtual bool CanPauseOrResume() = 0;
	virtual bool IsPaused() = 0;
	virtual bool Pause() = 0;
	virtual bool Resume() = 0;
	virtual bool CanSeek() = 0;
	virtual bool CanGetTime() = 0;
	virtual bool SeekToPercent(float Percent) = 0;
	virtual bool GetTime(int64& TotalMills, int64& CurrentMills) = 0;
	virtual bool NextFrame() = 0;

	virtual bool IsCloseWhenMediaPipeStopped() const = 0;
	virtual void Close() = 0;
	const TOptional<FImageSourceInfo>& GetImageSourceInfo() const;
protected:
	void SetImageSourceInfo(const FImageSourceInfo& Info);
	void ClearImageSourceInfo();
	
	bool IsTextureCreatedEventBound() const { return OnTextureCreated.IsBound(); }
	bool IsImageSourceOpenedEventBound() const { return OnImageSourceOpened.IsBound(); }

	void RaiseTextureCreatedEvent(UTexture2D* Texture, int Width, int Height) const { OnTextureCreated.BroadcastIfBoundNoCheck(Texture, Width, Height); }
	void RaiseImageSourceOpenedEvent(const FImageSourceInfo& SourceInfo) const { OnImageSourceOpened.BroadcastIfBoundNoCheck(SourceInfo); } 
	
	FTextureCreatedDelegate OnTextureCreated;
	FOnImageSourceOpened OnImageSourceOpened;

	TOptional<FImageSourceInfo> ImageSourceInfo;
};
