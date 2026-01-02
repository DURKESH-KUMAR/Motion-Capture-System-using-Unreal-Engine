// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "RunTimeTypes.h"

struct MEDIAPIPEMOTION_API FLocationSolvingStaging
{
	FVector PreLeftFootInCameraLocation;
	FVector PreRightFootInCameraLocation;

	FVector TargetLeftFootInCameraLocation;
	FVector TargetRightFootInCameraLocation;
	
	FVector CalibratedRootRootLocation;

	FVector PreRootRootLocation;
	TOptional<FVector> TargetRootRootLocation;

	bool bHasPrev = false;

	FVector GetLeftVelocity(float DeltaSeconds);
	FVector GetRightVelocity(float DeltaSeconds);

	EFootType GetHighVelocityFoot(float DeltaSeconds,  float& VelocityValue);
	
	bool HasTarget();
	bool IsValid();

	void ResetState();
};
