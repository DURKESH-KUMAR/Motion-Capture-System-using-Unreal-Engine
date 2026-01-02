// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "AnimNode_MediaPipeBase.h"
#include "SpringDampingSettings.h"
#include "PoseCalibrationFlags.h"
#include "PoseOptimizationSettings.h"
#include "AnimNode_MediaPipePose.generated.h"

class UAnimGraphNode_MediaPipePose;

USTRUCT(BlueprintInternalUseOnly)
struct MEDIAPIPEMOTION_API  FAnimNode_MediaPipePose : public FAnimNode_MediaPipeBase
{
	GENERATED_USTRUCT_BODY()

	FAnimNode_MediaPipePose();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockArms = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockLegs = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockHip = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockSpine = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockChest = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockHead = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockHand = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockElbow = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockKnee = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	bool bLockFoot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joint Locks", meta = (PinHiddenByDefault))
	FRotationLockConfig UpperBodyLocks;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IK", meta = (PinShownByDefault))
	bool bUseLegIK = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IK", meta = (PinShownByDefault))
	bool bUseArmIK = true;

	/** Whether optimize the posture of the body. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bOptimize = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	FPoseOptimizationSettings OptimizeSettings;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	FTwistCorrectionSettings TwistCorrectionSettings;

	/** Whether to calibrate the pose at the end of the countdown. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bCountdownCalibrationEnabled =  false;

	/** The part of the body to be calibrated when calibrating .*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, Bitmask, BitmaskEnum =" /Script/MediaPipe.EPoseCalibrationFlags"), Category="MediaPipe")
	uint8 Calibration =  static_cast<uint8>(EPoseCalibrationFlags::LowerLegs | EPoseCalibrationFlags::Spine | EPoseCalibrationFlags::UpperLegs | EPoseCalibrationFlags::Head);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IK", meta=(EditCondition="bUseLegIK"))
	FSpringDampingSettings FeetSpringDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IK", meta=(EditCondition="bUseLegIK"))
	FSpringDampingSettings HandsSpringDamping;

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void EvaluateComponentPose_AnyThread(FComponentSpacePoseContext& Output) override;
private:
	TWeakPtr<IPoseSolver> PoseSolver;
	friend class UAnimGraphNode_MediaPipePose;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe") TODO:fix leg
	bool bFixMediaPipePose = true;
};
