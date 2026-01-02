// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "RotationLockConfig.h"

#include "PoseSolverLockSettings.generated.h"

USTRUCT(BlueprintType)
struct FPoseSolverLockSettings
{
	friend bool operator==(const FPoseSolverLockSettings& Lhs, const FPoseSolverLockSettings& RHS)
	{
		return Lhs.bIsLockArms == RHS.bIsLockArms
			&& Lhs.bIsLockLegs == RHS.bIsLockLegs
			&& Lhs.bIsLockElbow == RHS.bIsLockElbow
			&& Lhs.bIsLockKnee == RHS.bIsLockKnee
			&& Lhs.bIsLockFoot == RHS.bIsLockFoot
			&& Lhs.bIsLockHip == RHS.bIsLockHip
			&& Lhs.bIsLockSpine == RHS.bIsLockSpine
			&& Lhs.bIsLockChest == RHS.bIsLockChest
			&& Lhs.bIsLockHead == RHS.bIsLockHead
			&& Lhs.bIsLockHand == RHS.bIsLockHand;
	}

	friend bool operator!=(const FPoseSolverLockSettings& Lhs, const FPoseSolverLockSettings& RHS)
	{
		return !(Lhs == RHS);
	}


	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockArms = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockLegs = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockElbow = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockKnee = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockFoot = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockHip = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockSpine = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockChest = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockHead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsLockHand = false;
};
