// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "AnimNode_MediaPipeBase.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_MediaPipeHand.generated.h"

/**
 * 
 */
USTRUCT(BlueprintInternalUseOnly)
struct MEDIAPIPEMOTION_API FAnimNode_MediaPipeHand : public FAnimNode_MediaPipeBase
{
	GENERATED_BODY()

	/** Whether optimize hand posture. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	bool bOptimize = true;

	/** What to do if hand loss occurs*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinShownByDefault))
	EHandLostPolicy HandLostPolicy = EHandLostPolicy::Reset;

	/** The time in seconds, no finger is found within this time , considered hand lost*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (PinHiddenByDefault, ClampMin=1.0f, ClampMax = 100.0f))
	float HandLostDuration = 2;

	/** The smoothness of the palm when it is reset to its initial state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta=(PinHiddenByDefault, ClampMin=0.0f, ClampMax = 1.0f))
	float HandResetSmooth = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta=(PinHiddenByDefault, ClampMin=0, ClampMax =2000))
	int WristStiffness = 800;
	
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
protected:
	virtual void EvaluateComponentPose_AnyThread(FComponentSpacePoseContext& Output) override;
private:
	TWeakPtr<IHandSolver> HandsSolver;
};
