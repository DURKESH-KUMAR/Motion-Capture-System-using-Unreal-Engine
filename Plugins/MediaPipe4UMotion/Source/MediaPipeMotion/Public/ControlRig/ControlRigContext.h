// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "ControlRig.h"
#include "BonePose.h"
#include "Animation/AnimNodeBase.h"


enum class EControlSpace
{
	WorldSpace,
	LocalSpace,
	RigSpace,
};

struct MEDIAPIPEMOTION_API FControlRigContext
{
	FCSPose<FCompactPose> CompactPose;
	FPoseContext* PoseContext = nullptr;
	TWeakObjectPtr<UControlRig> ControlRig = nullptr;
	bool IsValid() const;
	const FTransform& GetComponentTransform() const;

	UWorld* GetWorld() const;
 
	void Init(FPoseContext& Context, UControlRig* InControlRig);
};
