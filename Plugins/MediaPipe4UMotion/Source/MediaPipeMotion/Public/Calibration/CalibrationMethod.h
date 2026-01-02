// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CalibrationMethod.generated.h"

UENUM(BlueprintType)
enum class ECalibrationTarget : uint8
{
	None = 0,
	Pose = 1,
	Location = 2,
	All = 255
};

UENUM(BlueprintType)
enum class ECalibrationMethod : uint8
{
	Unknown = 0,
	Countdown = 1,
	Manual = 2,
};

