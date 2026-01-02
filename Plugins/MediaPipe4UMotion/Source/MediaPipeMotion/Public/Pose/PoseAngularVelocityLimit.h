// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "PoseAngularVelocityLimit.generated.h"


USTRUCT(BlueprintType)
struct FPoseAngularVelocityLimit
{
	FPoseAngularVelocityLimit(const FPoseAngularVelocityLimit& Other)
		: bLimitationEnabled(Other.bLimitationEnabled),
		  LegLimitation(Other.LegLimitation),
		  ArmLimitation(Other.ArmLimitation),
		  SpineLimitation(Other.SpineLimitation),
		  HeadLimitation(Other.HeadLimitation)
	{
	}

	FPoseAngularVelocityLimit(FPoseAngularVelocityLimit&& Other) noexcept
		: bLimitationEnabled(Other.bLimitationEnabled),
		  LegLimitation(Other.LegLimitation),
		  ArmLimitation(Other.ArmLimitation),
		  SpineLimitation(Other.SpineLimitation),
		  HeadLimitation(Other.HeadLimitation)
	{
	}

	FPoseAngularVelocityLimit& operator=(const FPoseAngularVelocityLimit& Other)
	{
		if (this == &Other)
			return *this;
		bLimitationEnabled = Other.bLimitationEnabled;
		LegLimitation = Other.LegLimitation;
		ArmLimitation = Other.ArmLimitation;
		SpineLimitation = Other.SpineLimitation;
		HeadLimitation = Other.HeadLimitation;
		return *this;
	}

	FPoseAngularVelocityLimit& operator=(FPoseAngularVelocityLimit&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		bLimitationEnabled = Other.bLimitationEnabled;
		LegLimitation = Other.LegLimitation;
		ArmLimitation = Other.ArmLimitation;
		SpineLimitation = Other.SpineLimitation;
		HeadLimitation = Other.HeadLimitation;
		return *this;
	}

	GENERATED_BODY()
	
	FPoseAngularVelocityLimit(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation")
	bool bLimitationEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation", meta=(EditCondition = "bEnabledLimitation", ClampMin=-1, ClampMax = 2000))
	float LegLimitation = 720;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation", meta=(EditCondition = "bEnabledLimitation",  ClampMin=-1, ClampMax = 2000))
	float FootLimitation = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation", meta=(EditCondition = "bEnabledLimitation",  ClampMin=-1, ClampMax = 2000))
	float ArmLimitation = 720;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation", meta=(EditCondition = "bEnabledLimitation",  ClampMin=-1, ClampMax = 2000))
	float HandLimitation = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation",meta=(EditCondition = "bEnabledLimitation",  ClampMin=-1, ClampMax = 2000))
	float SpineLimitation = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limitation", meta=(EditCondition = "bEnabledLimitation",  ClampMin=-1, ClampMax = 2000))
	float HeadLimitation = 500;
};
