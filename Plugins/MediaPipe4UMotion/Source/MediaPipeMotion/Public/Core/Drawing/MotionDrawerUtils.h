// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "BonePose.h"
#include "Components/SkeletalMeshComponent.h"
#include "Drawing/BatchDrawer.h"

class FMotionDrawerUtils
{
public:
	// Draw a line from bone to its skeletal parent
	static void AddBone(FBatchDrawer& InDrawer, USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& Pose,
		const FCompactPoseBoneIndex& ChildBone, const FLinearColor& Color = FColor(0, 255, 255), 
		float Thickness = 1.0f, float Duration = -1.0f);

	// Draw bones from ChainStartChild to ChainEndParent. ChainStartChild must be a parent of ChainEndParent,
	// otherwise nothing will happen.
	static void AddBoneChain(FBatchDrawer& InDrawer, USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& Pose,
		const FCompactPoseBoneIndex & ChainStartChild, const FCompactPoseBoneIndex& ChainEndParent,
		const FLinearColor& Color = FColor(0, 255, 255), float Thickness = 1.0f, float Duration = -1.0f);
};
