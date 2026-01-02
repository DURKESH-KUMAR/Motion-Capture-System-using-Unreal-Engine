// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "BoneContainer.h"
#include "BoneIndices.h"

struct MEDIAPIPEMOTION_API FSourceBone
{
	FBoneReference BoneReference = FBoneReference();
	FTransform InitTransform = FTransform::Identity;
	FTransform InitLocalTransform = FTransform::Identity;
	FQuat BaseRotation = FQuat::Identity;
	FVector BaseLocation = FVector::ZeroVector;
	FCompactPoseBoneIndex BoneIndex = FCompactPoseBoneIndex(INDEX_NONE);
	bool Aligned = false;
};
