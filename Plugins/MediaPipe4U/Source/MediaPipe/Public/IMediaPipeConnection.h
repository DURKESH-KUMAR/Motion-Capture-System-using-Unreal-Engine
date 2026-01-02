// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeLandmark.h"
#include "Templates/SharedPointer.h"

class MEDIAPIPE_API IMediaPipeConnection
{
public:
	virtual ~IMediaPipeConnection() = default;
	virtual void PutPoseLandmarks3D(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks) = 0;
};
