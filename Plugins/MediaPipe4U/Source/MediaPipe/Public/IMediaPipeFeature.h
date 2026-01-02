// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeConnection.h"
#include "HAL/Platform.h"

enum class EMediaPipeFeatures : uint8
{
	Pose3DLandmarker,
	Hand3DLandmarker,
};


class MEDIAPIPE_API IMediaPipeFeature
{
public:
	virtual ~IMediaPipeFeature() = default;
	virtual bool IsEnabled() const = 0;
	virtual bool IsOpened() = 0;
	virtual bool Open(const FMediaPipeConnection& Connection) = 0;
	virtual void Close() = 0;
};
