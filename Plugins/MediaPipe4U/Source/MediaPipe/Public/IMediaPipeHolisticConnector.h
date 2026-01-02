// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "IMediaPipeFeature.h"
#include "IMediaPipeHolisticFeatureRegistry.h"
#include "Containers/Map.h"
#include "MediaPipeLandmark.h"
#include "MediaPipeFaceMesh.h"
#include "MediaPipeUtils.h"
#include "ump_commons.h"
#include "Macros/ThreadSafedDeletgateMarcos.h"
#include "Listener/MediaPipeHolisticListener.h"

struct FMediaPipeHolisticOptions;
typedef  TMap<FName, float> FaceBlendShapes;

class IMediaPipeHolisticConnector;

DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeHolisticConnector, FLandmarksOutputEvent, TSharedPtr<TArray<FMediaPipeLandmark>>);
DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeHolisticConnector, FFaceBlendShapesOutputEvent, TSharedPtr<FaceBlendShapes>);
DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeHolisticConnector, FFaceGeometryOutputEvent, TSharedPtr<FMediaPipeFaceMesh>);
DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeHolisticConnector, FImageSizeDetectedEvent, const FSizeInt&);
DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeHolisticConnector, FMediaPipeFailedEvent, const int64 /* Session id, from StartPipeline function */);
DECLARE_THREAD_SAFE_EVENT_OneParam(IMediaPipeHolisticConnector, FMediaPipeFrameEvent, TSharedRef<IMediaPipeOutFrame>);


class MEDIAPIPE_API IMediaPipeHolisticConnector
{
public:
	static IMediaPipeHolisticConnector& Get();
	static IMediaPipeHolisticFeatureRegistry& GetFeatureRegistry();
	 
	virtual bool ConfigureGraph(const MediaPipeGraphCnf& InConfig) const = 0;
	virtual void EnableFrameCallback(bool Enabled) = 0;

	virtual bool IsConnected(UObject* Owner) const = 0;
	virtual bool Connect(UObject* Owner) = 0;
	virtual bool Disconnect(const UObject* Owner) = 0;
	
	virtual bool StartPipeline(long long SessionId, IImageSource* ImageSource, const FMediaPipeHolisticOptions& Options) = 0;
	virtual void StopPipeline() = 0;
	virtual bool PushFrameToPipeline(TSharedRef<IMediaPipeTexture> InTexture,  int RotationDegrees) = 0;
	//events
	virtual FLandmarksOutputEvent& OnPoseLandmarksTrigger() = 0;
	virtual FLandmarksOutputEvent& OnPoseWorldLandmarksTrigger() = 0;
	virtual FLandmarksOutputEvent& OnLeftHandLandmarksTrigger() = 0;
	virtual FLandmarksOutputEvent& OnRightHandLandmarksTrigger() = 0;
	virtual FFaceBlendShapesOutputEvent& OnFaceBlendShapesTrigger() = 0;
	virtual FFaceGeometryOutputEvent& OnFaceGeometryTrigger() = 0;
	virtual FLandmarksOutputEvent& OnFaceLandmarksTrigger() = 0;
	virtual FImageSizeDetectedEvent& OnImageSizeDetectedTrigger() = 0;
	virtual FMediaPipeFailedEvent& OnMediaPipeFailedTrigger() = 0;
	virtual FMediaPipeFrameEvent& OnMediaPipeFrameTrigger() = 0;
	
	virtual bool AddListener(const TSharedPtr<FMediaPipeHolisticListener>& InListener) = 0;
	virtual bool RemoveListener(const TSharedPtr<FMediaPipeHolisticListener>& InListener) = 0;
protected:
	virtual ~IMediaPipeHolisticConnector() = default;
};
