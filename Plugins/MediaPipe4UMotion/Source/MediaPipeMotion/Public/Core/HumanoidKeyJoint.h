// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "HumanoidKeyJoint.generated.h"

UENUM(BlueprintType)
enum class EHumanoidBodyPart : uint8
{
	Spine,
	UpperLegs,
	LowerLegs,
	UpperArms,
	LowerArms,
	Feet,
	Hands,
	Max,
};
