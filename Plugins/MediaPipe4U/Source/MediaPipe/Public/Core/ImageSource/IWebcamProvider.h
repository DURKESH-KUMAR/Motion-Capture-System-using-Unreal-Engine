// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "WebcamParams.h"
#include "FrameTransform.h"
#include "MediaPipeTexture.h"
#include "Macros/ThreadSafedDeletgateMarcos.h"


enum class EWebcamPipeline
{
	Poll,
	Push
};


class MEDIAPIPE_API IWebcamProvider
{
public:
	DECLARE_THREAD_SAFE_EVENT_TwoParams(IWebcamProvider, FOnWebcamOpenCompleted, bool, const FWebcamParams&);
	DECLARE_THREAD_SAFE_EVENT(IWebcamProvider, FOnWebcamClosed);
	DECLARE_THREAD_SAFE_EVENT_TwoParams(IWebcamProvider, FOnWebcamFramePushed,  TSharedRef<IMediaPipeTexture> /*Texture*/, int  /*RotationDegrees*/);
public:
	virtual ~IWebcamProvider() = default;
	virtual  bool Open(int DeviceId, int ResolutionX, int ResolutionY, int FPS) = 0;
	virtual  bool IsOpened() = 0;
	virtual void Close() = 0;
	virtual bool Read(MediaPipeTexture& Texture) = 0;
	virtual void UnLimitResolution() = 0;
	virtual void LimitResolution(int LimitResX, int LimitResY) = 0;
	virtual void SetHorizontalFlip(bool bFlip) = 0;
	virtual bool IsSupportResolutionLimit() = 0;
	virtual bool IsSupportHorizontalFlip() = 0;
	virtual bool ListCameras(TArray<FString>& Cameras) = 0;
	virtual EWebcamPipeline PipelineMode() = 0;
	virtual FOnWebcamOpenCompleted& OnOpenCompleted() = 0;
	virtual FOnWebcamClosed& OnClosed() = 0;
	virtual bool CorrectFrame(int DeviceId, FFrameTransform& InOutTransform) = 0;
	virtual FOnWebcamFramePushed& OnFramePushed() = 0;
};
