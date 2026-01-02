// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"

struct MEDIAPIPEMOTION_API FHeadCorrectionEnvironment
{
	FVector HeadBoneRollAxis = FVector::ZeroVector;
	FVector NeckBoneRollAxis = FVector::ZeroVector;
	FTransform HeadInitLocalTransform = FTransform::Identity;
	bool IsReady = false;
};