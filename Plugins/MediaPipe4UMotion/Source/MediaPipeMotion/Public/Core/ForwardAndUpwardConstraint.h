// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "ForwardAndUpward.h"


class MEDIAPIPEMOTION_API FForwardAndUpwardConstraint
{
public:

	FForwardAndUpwardConstraint(const FForwardAndUpward& InitValue = FForwardAndUpward(FVector::YAxisVector, FVector::ZAxisVector));
	void ResetState();

	FForwardAndUpward FilterPitchByAngleThreshold(
	const FForwardAndUpward& Current,
	float DeltaTime,
	float PitchThresholdDegrees = 30, 
	float SmoothingSpeed = 15.0f);

	FForwardAndUpward FilterRollByAngleThreshold(
		const FForwardAndUpward& Current,
		float DeltaTime,
		float RollThresholdDegrees = 15.0f,
		float SmoothingSpeed = 15.0f);

private:
	float LastPitchAngle = 0;
	float LastRollAngle = 0;
	FVector LastForward;
	FVector LastUpward;
	FForwardAndUpward Init;
};
