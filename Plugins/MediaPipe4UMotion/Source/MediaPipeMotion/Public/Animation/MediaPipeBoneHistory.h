// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "BoneIndices.h"

class MEDIAPIPEMOTION_API FMediaPipeBoneHistory
{
public:
	
	FMediaPipeBoneHistory(const FMediaPipeBoneHistory& Other)
		: BoneIndex(Other.BoneIndex),
		  BoneName(Other.BoneName),
		  Transform(Other.Transform),
		  LocalTransform(Other.LocalTransform)
	{
	}

	FMediaPipeBoneHistory(FMediaPipeBoneHistory&& Other) noexcept
		: BoneIndex(std::move(Other.BoneIndex)),
		  BoneName(std::move(Other.BoneName)),
		  Transform(std::move(Other.Transform)),
		  LocalTransform(std::move(Other.LocalTransform))
	{
	}

	FMediaPipeBoneHistory& operator=(const FMediaPipeBoneHistory& Other)
	{
		if (this == &Other)
			return *this;
		BoneIndex = Other.BoneIndex;
		BoneName = Other.BoneName;
		Transform = Other.Transform;
		LocalTransform = Other.LocalTransform;
		return *this;
	}

	FMediaPipeBoneHistory& operator=(FMediaPipeBoneHistory&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		BoneIndex = std::move(Other.BoneIndex);
		BoneName = std::move(Other.BoneName);
		Transform = std::move(Other.Transform);
		LocalTransform = std::move(Other.LocalTransform);
		return *this;
	}
	
	FMediaPipeBoneHistory(){}
	
	
	FCompactPoseBoneIndex BoneIndex = FCompactPoseBoneIndex(INDEX_NONE);
	FName BoneName = NAME_None;
	FTransform Transform = FTransform::Identity;
	FTransform LocalTransform = FTransform::Identity;
};
