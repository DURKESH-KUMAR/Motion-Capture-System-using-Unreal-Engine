// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-08

#pragma once
#include "MediaPipeLandmark.h"
#include "MediaPipeFaceMesh.h"
#include "Templates/SharedPointer.h"

class FMediaPipeHolisticListener
{
public:
	virtual ~FMediaPipeHolisticListener() = default;
	virtual void OnStarted() {}
	virtual void OnStopped() {}
	virtual void OnPoseWorldLandmarks(const TSharedPtr<FMediaPipeLandmarkList>& Landmarks) {}
	virtual void OnPoseLandmarks(const TSharedPtr<FMediaPipeLandmarkList>& Landmarks) {}
	virtual void OnLeftHandLandmarks(const TSharedPtr<FMediaPipeLandmarkList>& Landmarks) {}
	virtual void OnRightHandLandmarks(const TSharedPtr<FMediaPipeLandmarkList>& Landmarks) {}
	virtual void OnFaceBlendShapes(const TSharedPtr<TMap<FName, float>>& BlendShapes) {}
	virtual void OnFaceGeometry(const TSharedPtr<FMediaPipeFaceMesh>& FaceMesh) {}
	virtual void OnFaceLandmarks(const TSharedPtr<FMediaPipeLandmarkList>& Landmarks) {}
};
