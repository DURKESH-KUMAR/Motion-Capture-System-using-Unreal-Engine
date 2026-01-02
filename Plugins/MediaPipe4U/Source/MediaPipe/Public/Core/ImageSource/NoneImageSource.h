// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "MediaPipeImageSource.h"
#include "NoneImageSource.generated.h"

UCLASS(Hidden, NotPlaceable, NotBlueprintType)
class MEDIAPIPE_API UNoneImageSource : public UObject, public IMediaPipeImageSource
{
public:
	GENERATED_BODY()
	
	virtual IImageSource* GetImageSource() override;
	virtual bool IsSupportHorizontalFlip() override;
	virtual bool IsSupportLimitResolution() override;
	virtual void LimitResolution(int ResolutionX, int ResolutionY) override;
	virtual void SetHorizontalFlip(bool bFlip) override;
	virtual void UnLimitResolution() override;
	virtual bool CorrectFrame(FFrameTransform& InOutTransform) override;
	virtual bool CanPauseOrResume() override;
	virtual bool IsPaused() override;
	virtual bool Pause() override;
	virtual bool Resume() override;
	virtual bool CanSeek() override;
	virtual bool CanGetTime() override;
	virtual bool SeekToPercent(float Percent) override;
	virtual bool NextFrame() override;
	virtual bool GetTime(int64& TotalMills, int64& CurrentMills) override;
	virtual bool IsCloseWhenMediaPipeStopped() const override;
	virtual void Close() override;
};
