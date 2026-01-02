// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "AngularDamper.h"
#include "DampingMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "RuntimeDamper.h" 

class MEDIAPIPEMOTION_API FRuntimeAngularDamper : public RuntimeDamper<FQuat, FQuaternionSpringState>
{
public:
	FRuntimeAngularDamper()
	{
	}


	bool bIsUserDefined = false;
	float Stiffness = 450.0f;
	float Damping = 1.0f;

	void Update(const FAngularDamper& InDamper);

	bool IsPitchEnabled(const FQuat& Rotation, const FVector& PitchAxis) const;

	bool IsYawEnabled(const FQuat& Rotation, const FVector& YawAxis) const;

	bool IsRollEnabled(const FQuat& Rotation, const FVector& RollAxis) const;

	bool IsPitchEnabled(const float PitchAngleDegrees) const;

	bool IsYawEnabled(const float YawAngleDegrees) const;

	bool IsRollEnabled(const float RollAngleDegrees) const;

	FQuat InterpTo(
		const FQuat& InRotation,
		float DeltaSeconds,
		EDampingMode Mode = EDampingMode::Spring,
		const FVector& PitchAxis = FVector::ZeroVector,
		const FVector& YawAxis = FVector::ZeroVector,
		const FVector& RollAxis = FVector::ZeroVector);

private:
	float PitchSwing = 0;
	float YawSwing = 0;
	float RollSwing = 0;
};
