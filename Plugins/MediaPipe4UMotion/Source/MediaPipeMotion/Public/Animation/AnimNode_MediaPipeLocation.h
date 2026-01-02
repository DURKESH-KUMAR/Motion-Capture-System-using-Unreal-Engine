// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "AnimNode_MediaPipeBase.h"
#include "ILocationSolver.h"
#include "GroundSolveSettings.h"
#include "IGroundSolver.h"
#include "AnimNode_MediaPipeLocation.generated.h"

class UAnimGraphNode_MediaPipeLocation;

/**
 * 
 */
USTRUCT(BlueprintInternalUseOnly)
struct MEDIAPIPEMOTION_API FAnimNode_MediaPipeLocation : public FAnimNode_MediaPipeBase
{
	GENERATED_BODY()
	
	FAnimNode_MediaPipeLocation();

	/** Whether to disable horizontal movement of the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bLockHorizontalMove = false;

	/** Whether to disable vertical movement of the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bLockVerticalMove = false;

	/** Whether to disable back and forth movement of the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bLockForwardMove = false;

	/** Maximum movement speed (cm/s) to prevent sudden changes in location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault, ToolTip="Maximum movement speed (cm/s) to prevent sudden changes in location."))
	float SmoothSpeed =200.0f;

	/** Whether to enable ground ik to help the foot place on the ground */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bUseGroundIK = true;

	/** The settings for ground ik. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MediaPipe", meta = (PinHiddenByDefault, EditCondition="bUseGroundIK"))
	FGroundSolveSettings GroundSolveSettings;

	/** The multiplier in the direction of movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	FVector MovementScale = FVector(1.0, 1.0, 1.0);

	/** The speed at which the camera depth changes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	float DepthInterpSpeed =0.3;

	/** Whether to calibrate the position at the end of the countdown. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bCountdownCalibrationEnabled =  true;
	
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
protected:
	virtual void EvaluateComponentPose_AnyThread(FComponentSpacePoseContext& Output) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
private:
	TWeakPtr<ILocationSolver> LocationSolver;
	TWeakPtr<IGroundSolver> GroundSolver;

	friend class UAnimGraphNode_MediaPipeLocation;
};
