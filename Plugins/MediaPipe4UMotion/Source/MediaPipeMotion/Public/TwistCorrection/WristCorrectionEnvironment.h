// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "RunTimeTypes.h"

struct MEDIAPIPEMOTION_API FWristCorrectionEnvironment
{
	EHandType HandType = EHandType::Left;
	FVector WristTwistAxis = FVector::ZeroVector;
	//手掌法线
	FVector WristUpAxis = FVector::ZeroVector;
	FVector UpperArmTwistAxis = FVector::ZeroVector;
	FVector LowerArmTwistAxis = FVector::ZeroVector;
	FTransform WristInitLocalTransform = FTransform::Identity;
	bool IsReady = false;
};
