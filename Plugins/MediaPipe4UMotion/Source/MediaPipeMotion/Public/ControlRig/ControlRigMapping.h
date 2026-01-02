// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "RigControls.h"
#include "UObject/NameTypes.h"
#include "ControlRigMapping.generated.h"

USTRUCT()
struct MEDIAPIPEMOTION_API FControlRigMapping
{
	GENERATED_BODY()

	UPROPERTY()
	FName RootIKCtrl = "body_offset_ctrl";
	UPROPERTY()
	FName BodyIKCtrl = "body_ctrl";
	UPROPERTY()
	FName SpineIKCtrl = "hips_ctrl";
	UPROPERTY()
	FName ChestIKCtrl = "chest_ctrl";
	UPROPERTY()
	FName HeadIKCtrl = "head_ik_ctrl";
	UPROPERTY()
	FName LeftHandIKCtrl = "hand_l_ik_ctrl";
	UPROPERTY()
	FName RightHandIKCtrl = "hand_r_ik_ctrl";
	UPROPERTY()
	FName LeftArmPoleIKCtrl = "arm_l_pv_ik_ctrl";
	UPROPERTY()
	FName RightArmPoleIKCtrl = "arm_r_pv_ik_ctrl";
	UPROPERTY()
	FName LeftFootIKCtrl = "foot_l_ik_ctrl";
	UPROPERTY()
	FName RightFootIKCtrl = "foot_r_ik_ctrl";
	UPROPERTY()
	FName LeftLegPoleIKCtrl = "leg_l_pv_ik_ctrl";
	UPROPERTY()
	FName RightLegPoleIKCtrl = "leg_r_pv_ik_ctrl";

	UPROPERTY()
	FName LeftThumbProximalCtrl = "thumb_01_l_ctrl";
	UPROPERTY()
	FName LeftThumbIntermediateCtrl = "thumb_02_l_ctrl";
	UPROPERTY()
	FName LeftThumbDistalCtrl = "thumb_03_l_ctrl";
	UPROPERTY()
	FName LeftIndexProximalCtrl = "index_01_l_ctrl";
	UPROPERTY()
	FName LeftIndexIntermediateCtrl = "index_02_l_ctrl";
	UPROPERTY()
	FName LeftIndexDistalCtrl  = "index_03_l_ctrl";
	UPROPERTY()
	FName LeftMiddleProximalCtrl = "middle_01_l_ctrl";
	UPROPERTY()
	FName LeftMiddleIntermediateCtrl = "middle_02_l_ctrl";
	UPROPERTY()
	FName LeftMiddleDistalCtrl  = "middle_03_l_ctrl";
	UPROPERTY()
	FName LeftRingProximalCtrl  = "ring_01_l_ctrl";
	UPROPERTY()
	FName LeftRingIntermediateCtrl = "ring_02_l_ctrl";
	UPROPERTY()
	FName LeftRingDistalCtrl = "ring_03_l_ctrl";
	UPROPERTY()
	FName LeftLittleProximalCtrl = "pinky_01_l_ctrl";
	UPROPERTY()
	FName LeftLittleIntermediateCtrl = "pinky_02_l_ctrl";
	UPROPERTY()
	FName LeftLittleDistalCtrl = "pinky_03_l_ctrl";

	UPROPERTY()
	FName RightThumbProximalCtrl = "thumb_01_r_ctrl";
	UPROPERTY()
	FName RightThumbIntermediateCtrl = "thumb_02_r_ctrl";
	UPROPERTY()
	FName RightThumbDistalCtrl = "thumb_03_r_ctrl";
	UPROPERTY()
	FName RightIndexProximalCtrl = "index_01_r_ctrl";
	UPROPERTY()
	FName RightIndexIntermediateCtrl = "index_02_r_ctrl";
	UPROPERTY()
	FName RightIndexDistalCtrl = "index_03_r_ctrl";
	UPROPERTY()
	FName RightMiddleProximalCtrl = "middle_01_r_ctrl";
	UPROPERTY()
	FName RightMiddleIntermediateCtrl = "middle_02_r_ctrl";
	UPROPERTY()
	FName RightMiddleDistalCtrl = "middle_03_r_ctrl";
	UPROPERTY()
	FName RightRingProximalCtrl  = "ring_01_r_ctrl";
	UPROPERTY()
	FName RightRingIntermediateCtrl  = "ring_02_r_ctrl";
	UPROPERTY()
	FName RightRingDistalCtrl  = "ring_03_r_ctrl";
	UPROPERTY()
	FName RightLittleProximalCtrl = "pinky_01_r_ctrl";
	UPROPERTY()
	FName RightLittleIntermediateCtrl = "pinky_02_r_ctrl";
	UPROPERTY()
	FName RightLittleDistalCtrl = "pinky_03_r_ctrl";

	const FName& GetControl(ERigControls Control) const;
	void GetMapping(TMap<ERigControls, FName>& OutMap) const;

private:
	const static FName NoneControl;

};
