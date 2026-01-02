// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"

/**
 * Positive numbers are considered clockwise and negative counterclockwise, so that the maximum and minimum values are considered.
 * 
 * Chinese : 看向轴的方向，顺时针为正，逆时针为负，义词考虑最大最小值
 */
struct MEDIAPIPEMOTION_API FRotationConstraint
{
	FRotationConstraint(){}
	
	FRotationConstraint(const FVector& RotationAxis, float MinDegrees, float MaxDegrees)
		: RotationAxis(RotationAxis),
		  MaxDegrees(MaxDegrees),
		  MinDegrees(MinDegrees)
	{
	}
	
	FRotationConstraint(const FRotationConstraint& Other)
		: RotationAxis(Other.RotationAxis),
		  MaxDegrees(Other.MaxDegrees),
		  MinDegrees(Other.MinDegrees)
	{
	}

	FRotationConstraint(FRotationConstraint&& Other) noexcept
		: RotationAxis(std::move(Other.RotationAxis)),
		  MaxDegrees(Other.MaxDegrees),
		  MinDegrees(Other.MinDegrees)
	{
	}

	FRotationConstraint& operator=(const FRotationConstraint& Other)
	{
		if (this == &Other)
			return *this;
		RotationAxis = Other.RotationAxis;
		MaxDegrees = Other.MaxDegrees;
		MinDegrees = Other.MinDegrees;
		return *this;
	}

	FRotationConstraint& operator=(FRotationConstraint&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		RotationAxis = std::move(Other.RotationAxis);
		MaxDegrees = Other.MaxDegrees;
		MinDegrees = Other.MinDegrees;
		return *this;
	}


	FVector RotationAxis = FVector::ZeroVector;
	float MaxDegrees = 180;
	float MinDegrees = 0;

	bool Apply(const FQuat& InitRotation, FQuat& InOutTargetRotation, const FName& LogName = NAME_None) const;

};