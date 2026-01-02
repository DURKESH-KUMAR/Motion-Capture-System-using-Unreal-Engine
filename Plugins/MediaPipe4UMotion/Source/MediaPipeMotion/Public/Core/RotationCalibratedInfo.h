// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Math/Quat.h"

struct MEDIAPIPEMOTION_API FRotationCalibratedInfo
{
	FRotationCalibratedInfo(const FRotationCalibratedInfo& Other)
		: InverseRotation(Other.InverseRotation),
		  AngleFrom(Other.AngleFrom),
		  AngleTo(Other.AngleTo),
		  Axis(Other.Axis)
	{
	}

	FRotationCalibratedInfo(FRotationCalibratedInfo&& Other) noexcept
		: InverseRotation(std::move(Other.InverseRotation)),
		  AngleFrom(Other.AngleFrom),
		  AngleTo(Other.AngleTo),
		  Axis(std::move(Other.Axis))
	{
	}

	FRotationCalibratedInfo& operator=(const FRotationCalibratedInfo& Other)
	{
		if (this == &Other)
			return *this;
		InverseRotation = Other.InverseRotation;
		AngleFrom = Other.AngleFrom;
		AngleTo = Other.AngleTo;
		Axis = Other.Axis;
		return *this;
	}

	FRotationCalibratedInfo& operator=(FRotationCalibratedInfo&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		InverseRotation = std::move(Other.InverseRotation);
		AngleFrom = Other.AngleFrom;
		AngleTo = Other.AngleTo;
		Axis = std::move(Other.Axis);
		return *this;
	}

	FRotationCalibratedInfo()
	{
		
	}

	FQuat InverseRotation = FQuat::Identity;
	float AngleFrom = 0;
	float AngleTo = 0;
	FVector Axis = FVector::ZeroVector;

	bool NeedFix(const FQuat& Rotation) const;
};
