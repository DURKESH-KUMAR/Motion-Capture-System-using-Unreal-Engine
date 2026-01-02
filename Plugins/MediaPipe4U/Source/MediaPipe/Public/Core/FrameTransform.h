// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "RotationAngle.h"

struct MEDIAPIPE_API FFrameTransform
{
	bool FlipVertically = false;
	bool FlipHorizontally = false;
	ERotationAngle RotationDegrees = ERotationAngle::Rotation0;
};
