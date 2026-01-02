// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-07

#pragma once
#include "IMediaPipeHolisticConnector.h"
#include "Listener/MediaPipeHolisticListener.h"

class FMediaPipeConnectorBase;

DECLARE_DERIVED_EVENT(FMediaPipeConnectorBase, FLandmarksOutputEvent, FHolisticLandmarksOutputEvent);
DECLARE_DERIVED_EVENT(FMediaPipeConnectorBase, FFaceBlendShapesOutputEvent, FHolisticFaceBlendShapesOutputEvent);
DECLARE_DERIVED_EVENT(FMediaPipeConnectorBase, FFaceGeometryOutputEvent, FHolisticFaceGeometryOutputEvent); 
DECLARE_DERIVED_EVENT(FMediaPipeConnectorBase, FImageSizeDetectedEvent, FHolisticImageSizeDetectedEvent); 
DECLARE_DERIVED_EVENT(FMediaPipeConnectorBase, FMediaPipeFailedEvent, FHolisticMediaPipeFailedEvent);
DECLARE_DERIVED_EVENT(FMediaPipeConnectorBase, FMediaPipeFrameEvent, FHolisticMediaPipeFrameEvent);

/**
* Inherit this class, you can minimize defining a connector to replace google mediapipe.
* 
* This class acts as a bridge between UE MediaPipeHolisticComponent and google mediapipe pipline.
*
* Connector lifecycle:
* 
* -----------------------------------------------------------------------
*  
*       Connect >>> StartPipeline >>> StopPipeline >>> Disconnect     
*  
* -----------------------------------------------------------------------  
*/
class MEDIAPIPE_API FMediaPipeConnectorBase : public IMediaPipeHolisticConnector
{
public:
	//only mediapipe used for IMediaPipeHolisticConnector
	virtual bool ConfigureGraph(const MediaPipeGraphCnf& InConfig) const override { return true; }
	virtual void EnableFrameCallback(bool Enabled) override {  }

	//Some image source use push mode, the function for receive image frame.
	virtual bool PushFrameToPipeline(TSharedRef<IMediaPipeTexture> InTexture, int RotationDegrees) override { return true; };

	virtual bool IsConnected(UObject* Owner) const override;

	
	//events for IMediaPipeHolisticConnector
	virtual FLandmarksOutputEvent& OnPoseWorldLandmarksTrigger() final override;
	virtual FLandmarksOutputEvent& OnPoseLandmarksTrigger() final override;
	virtual FLandmarksOutputEvent& OnLeftHandLandmarksTrigger() final override;
	virtual FLandmarksOutputEvent& OnRightHandLandmarksTrigger() final override;
	virtual FFaceBlendShapesOutputEvent& OnFaceBlendShapesTrigger() final override;
	virtual FFaceGeometryOutputEvent& OnFaceGeometryTrigger() final override;
	virtual FLandmarksOutputEvent& OnFaceLandmarksTrigger() final override;
	
	virtual FImageSizeDetectedEvent& OnImageSizeDetectedTrigger() final override;
	virtual FMediaPipeFailedEvent& OnMediaPipeFailedTrigger() final override;
	virtual FMediaPipeFrameEvent& OnMediaPipeFrameTrigger() final override;

	virtual bool AddListener(const TSharedPtr<FMediaPipeHolisticListener>& InListener) final override;
	virtual bool RemoveListener(const TSharedPtr<FMediaPipeHolisticListener>& InListener) final override;
protected:
	TWeakObjectPtr<> ConnectionOwner = nullptr;
	virtual bool OnStartPipeline(int64 SessionId, IImageSource* ImageSource, const FMediaPipeHolisticOptions& Options) = 0;
	virtual void OnStopPipeline() = 0;
	
	virtual bool OnConnect(UObject* Owner) = 0;
	virtual bool OnDisconnect() = 0;

	const FSizeInt& GetImageSize() const;

	void RaiseMediaPipeFailedEvent(int64 SessionId) const;
	void RaiseMediaPipeFrameEvent(const TSharedRef<IMediaPipeOutFrame>& TextureFrame) const;

	void RaiseFaceLandmarksEvent(const TSharedPtr<TArray<FMediaPipeLandmark>>& FaceLandmarks) const;
	void RaiseFaceBlendShapesEvent(const TSharedPtr<FaceBlendShapes>& BlendShapes) const;
	void RaisePoseWorldLandmarksEvent(const TSharedPtr<TArray<FMediaPipeLandmark>>& PoseWorldLandmarks) const;
	void RaisePoseLandmarksEvent(const TSharedPtr<TArray<FMediaPipeLandmark>>& PoseLandmarks) const;
	void RaiseLeftHandLandmarksEvent(const TSharedPtr<TArray<FMediaPipeLandmark>>& HandLandmarks) const;
	void RaiseRightHandLandmarksEvent(const TSharedPtr<TArray<FMediaPipeLandmark>>& HandLandmarks) const;
	void RaiseFaceGeometryEvent(const TSharedPtr<FMediaPipeFaceMesh>& FaceMesh) const;
	void RaiseImageSizeDetectedEvent(int Width, int Height) const;

	bool IsFaceLandmarksEventBound() const { return OnFaceLandmarksEvent.IsBound(); }
	bool IsFaceBlendShapesEventBound() const { return OnFaceBlendShapesEvent.IsBound(); }
	bool IsPoseWorldLandmarksEventBound() const { return OnPoseWorldLandmarksEvent.IsBound(); }
	bool IsPoseLandmarksEventBound() const { return OnPoseLandmarksEvent.IsBound(); }
	bool IsLeftHandLandmarksEventBound() const { return OnLeftHandLandmarksEvent.IsBound(); }
	bool IsRightHandLandmarksEventBound() const { return OnRightHandLandmarksEvent.IsBound(); }
	bool IsFaceGeometryEventBound() const { return OnFaceGeometryEvent.IsBound(); }
private:
	virtual bool StartPipeline(long long SessionId, IImageSource* ImageSource, const FMediaPipeHolisticOptions& Options) final override;
	virtual void StopPipeline() final override;
	
	virtual bool Connect(UObject* Owner) override final;
	virtual bool Disconnect(const UObject* Owner) override final;
	mutable FSizeInt ImageSize;
	mutable FRWLock ListenerLock;
	mutable FCriticalSection ConnectMutex;
	bool bConnected = false;
	bool CheckOwner(const UObject* Owner) const;
	bool DoDisconnect(const UObject* Owner, bool bLock);

	
	TSet<TSharedPtr<FMediaPipeHolisticListener>> Listeners;
	FHolisticLandmarksOutputEvent OnPoseWorldLandmarksEvent;
	FHolisticLandmarksOutputEvent OnPoseLandmarksEvent;
	FHolisticLandmarksOutputEvent OnLeftHandLandmarksEvent;
	FHolisticLandmarksOutputEvent OnRightHandLandmarksEvent;
	FHolisticLandmarksOutputEvent OnFaceLandmarksEvent;
	FHolisticFaceBlendShapesOutputEvent OnFaceBlendShapesEvent;
	FHolisticFaceGeometryOutputEvent OnFaceGeometryEvent;
	FHolisticImageSizeDetectedEvent OnImageSizeDetectedEvent;
	FHolisticMediaPipeFailedEvent OnMediaPipeFailedEvent;
	FHolisticMediaPipeFrameEvent OnMediaPipeFrameEvent;
};

