// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "IMediaEventSink.h"
#include "MediaPipeImageSourceComponent.h"
#include "MediaTexture.h"
#include "Materials/Material.h"
#include "MediaSampleQueue.h"
#include "MediaPlayerImageSourceComponent.generated.h"

class IMediaClockSink;

UCLASS(ClassGroup=(MediaPipe), BlueprintType, meta=(BlueprintSpawnableComponent))
class MEDIAPIPE_API UMediaPlayerImageSourceComponent : public UMediaPipeImageSourceComponent
{
	GENERATED_BODY()

public:
	UMediaPlayerImageSourceComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media")
	TObjectPtr<UMediaPlayer> MediaPlayer = nullptr;
	
	virtual bool IsSupportHorizontalFlip() override { return false; }
	virtual bool IsSupportLimitResolution() override { return false; }

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

	virtual void TickSink();
	virtual void StartSample();
	virtual void StopSample();
	virtual void Close() override;
	virtual ELoopResult HandleInLoop() override;
private:

	void HandleMediaPlayerEvent(EMediaEvent MediaEvent);
	TSharedPtr<FMediaTextureSampleQueue, ESPMode::ThreadSafe> SampleQueue;

	TSharedPtr<IMediaClockSink, ESPMode::ThreadSafe> ClockSink;
	bool bUnsupportedWarningShowed = false;
	bool bIsSampleRunning = false;
	bool bIsOpened = false;
	TQueue<TSharedPtr<IMediaTextureSample>> SampleTasks;
};
