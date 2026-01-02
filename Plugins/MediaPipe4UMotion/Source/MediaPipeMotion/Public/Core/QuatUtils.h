// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"

class MEDIAPIPEMOTION_API QuatUtils
{
public:
	static constexpr float RAD_TO_DEG = 57.2957801818848f;
	static constexpr float DEG_TO_RAD  =0.01745329252f;
	
	static float Dot(const FQuat& Q1, const FQuat& Q2);
	static FQuat GetAxis(const FQuat& Quat, const FVector& Axis);
	static FQuat RemoveAxis(const FQuat& TargetQuat, const FQuat& OriginQuat, const FVector& Axis);
	static FQuat LimitAxis(const FQuat& Quat, const FVector& Axis, float MinAngleDegrees, float MaxAngleDegrees);
	static double WrapAngleRad(double AngleRad);
	static double WrapAngleDegree(double AngleDegree);

	
	static FQuat RotateTowards(
	const FQuat& Current,
	const FQuat& Target,
	const float MaxAngularSpeed,
	const float DeltaTime);

	static float AngleDegrees(const FQuat& A, const FQuat& B);

	static float GetTwistAngleDegrees(const FQuat& A, const FVector& TwistAxis);
	static float GetSignedTwistAngleDegrees(const FQuat& Rotation, const FVector& Axis);

	static FQuat FindTwistBetween(const FQuat& InitRot, const FQuat& TargetRot, const FVector& TwistAxis);

	static FQuat FindBetweenVectorsOnPlane(const FVector& InitVector, const FVector& TargetVector, const FVector& PlaneNormal);

	static FRotator SpringInterpTo(FRotator Current, FRotator Target, FVector4& Velocity, float DeltaTime,
								   float InterpSpeed, float MaxVelocity);
	
	static FQuat SpringInterpTo(FQuat Current, FQuat Target, FVector4& Velocity, float DeltaTime, float InterpSpeed,
							 float MaxVelocity);

};
