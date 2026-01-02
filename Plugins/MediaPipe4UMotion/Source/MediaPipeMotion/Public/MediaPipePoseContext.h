// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "HumanoidBoneSettings.h"
#include "Animation/AnimNodeBase.h"

struct MEDIAPIPEMOTION_API FMediaPipePoseContext
{
	FMediaPipePoseContext(
		const TWeakPtr<FHumanoidBoneSettings>& InBoneSettings,
		FComponentSpacePoseContext& InPoseContext,
		TMap<FName, float>& InMorphTargetCurves,
		int InLOD)
	: LOD(InLOD), PoseContext(InPoseContext), BoneSettings(InBoneSettings), MorphTargetCurve(InMorphTargetCurves)
	{}

	int LOD;
	FComponentSpacePoseContext& PoseContext;
	const TWeakPtr<FHumanoidBoneSettings> BoneSettings;
	TMap<FName, float>& MorphTargetCurve;
	float DeltaSeconds = 0;
};
