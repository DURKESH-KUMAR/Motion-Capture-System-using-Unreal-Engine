// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "RotationLockConfig.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FRotationLockConfig
{
	FRotationLockConfig(const FRotationLockConfig& Other)
		: bLockYaw(Other.bLockYaw),
		  bLockRoll(Other.bLockRoll),
		  bLockPitch(Other.bLockPitch)
	{
	}

	FRotationLockConfig(FRotationLockConfig&& Other) noexcept
		: bLockYaw(Other.bLockYaw),
		  bLockRoll(Other.bLockRoll),
		  bLockPitch(Other.bLockPitch)
	{
	}

	FRotationLockConfig& operator=(const FRotationLockConfig& Other)
	{
		if (this == &Other)
			return *this;
		bLockYaw = Other.bLockYaw;
		bLockRoll = Other.bLockRoll;
		bLockPitch = Other.bLockPitch;
		return *this;
	}

	FRotationLockConfig& operator=(FRotationLockConfig&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		bLockYaw = Other.bLockYaw;
		bLockRoll = Other.bLockRoll;
		bLockPitch = Other.bLockPitch;
		return *this;
	}

	friend bool operator==(const FRotationLockConfig& Lhs, const FRotationLockConfig& RHS)
	{
		return Lhs.bLockYaw == RHS.bLockYaw
			&& Lhs.bLockRoll == RHS.bLockRoll
			&& Lhs.bLockPitch == RHS.bLockPitch;
	}

	friend bool operator!=(const FRotationLockConfig& Lhs, const FRotationLockConfig& RHS)
	{
		return !(Lhs == RHS);
	}

	FRotationLockConfig(){}

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bLockYaw = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bLockRoll = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bLockPitch = false;

	bool HasLock() const
	{
		return bLockYaw || bLockRoll || bLockPitch;
	}

	bool IsLockAll() const
	{
		return bLockYaw && bLockRoll && bLockPitch;
	}
};
