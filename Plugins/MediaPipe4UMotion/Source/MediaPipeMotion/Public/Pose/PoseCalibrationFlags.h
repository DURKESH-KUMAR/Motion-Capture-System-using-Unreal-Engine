// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "PoseCalibrationFlags.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPoseCalibrationFlags: uint8
{
	NONE = 0 UMETA(Hidden),
	Spine = 1,
	UpperLegs = 2,
	LowerLegs = 4,
	Head = 8
};

ENUM_CLASS_FLAGS(EPoseCalibrationFlags);
