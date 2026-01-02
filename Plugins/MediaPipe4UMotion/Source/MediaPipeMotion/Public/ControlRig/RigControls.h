// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "RigControls.generated.h"

UENUM(BlueprintType)
enum class ERigControls : uint8
{
	RootIKCtrl,
	BodyIKCtrl,
	SpineIKCtrl,
	ChestIKCtrl,
	HeadIKCtrl,
	LeftHandIKCtrl,
	RightHandIKCtrl,
	LeftArmPoleIKCtrl,
	RightArmPoleIKCtrl,
	LeftFootIKCtrl,
	RightFootIKCtrl,
	LeftLegPoleIKCtrl,
	RightLegPoleIKCtrl,

	LeftThumbProximalCtrl,
	LeftThumbIntermediateCtrl,
	LeftThumbDistalCtrl,
	LeftIndexProximalCtrl,
	LeftIndexIntermediateCtrl,
	LeftIndexDistalCtrl ,
	LeftMiddleProximalCtrl,
	LeftMiddleIntermediateCtrl,
	LeftMiddleDistalCtrl ,
	LeftRingProximalCtrl ,
	LeftRingIntermediateCtrl,
	LeftRingDistalCtrl,
	LeftLittleProximalCtrl,
	LeftLittleIntermediateCtrl,
	LeftLittleDistalCtrl,
	
	RightThumbProximalCtrl,
	RightThumbIntermediateCtrl,
	RightThumbDistalCtrl,
	RightIndexProximalCtrl,
	RightIndexIntermediateCtrl,
	RightIndexDistalCtrl,
	RightMiddleProximalCtrl,
	RightMiddleIntermediateCtrl,
	RightMiddleDistalCtrl,
	RightRingProximalCtrl ,
	RightRingIntermediateCtrl ,
	RightRingDistalCtrl ,
	RightLittleProximalCtrl,
	RightLittleIntermediateCtrl,
	RightLittleDistalCtrl,
};
