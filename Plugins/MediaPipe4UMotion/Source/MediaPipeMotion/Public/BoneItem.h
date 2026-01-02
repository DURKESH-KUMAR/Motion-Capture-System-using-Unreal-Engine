// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "BoneIndices.h"
#include "BoneContainer.h"
#include "BoneItem.generated.h"


USTRUCT()
struct FBoneItem
{
	GENERATED_BODY()

	FTransform Transform= FTransform::Identity;
	FTransform LocalTransform= FTransform::Identity;

	bool HasParent = false;

	FName BoneName = NAME_None;

	FName ParentBoneName = NAME_None;
	int ParentBoneMeshIndex = INDEX_NONE;

	int32 BoneIndex = INDEX_NONE;
};

