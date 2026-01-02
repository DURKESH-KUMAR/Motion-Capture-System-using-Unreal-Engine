// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "AnimNode_ControlRig.h"
#include "HumanoidBones.h"
#include "RigControls.h"
#include "ControlRigRemapAsset.h"
#include "SourceBone.h"
#include "Animation/AnimTypes.h"
#include "ControlRigContext.h"
#include "ControlEffect.h"
#include "Misc/EngineVersionComparison.h"
#include "MediaPipeAnimContext.h"
#include "AnimNode_ControlRigFromPose.generated.h"

/**
 * 
 */
USTRUCT(BlueprintInternalUseOnly)
struct MEDIAPIPEMOTION_API FAnimNode_ControlRigFromPose : public FAnimNode_ControlRigBase
{
	GENERATED_BODY()

	FAnimNode_ControlRigFromPose();

	virtual ~FAnimNode_ControlRigFromPose() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TSubclassOf<UControlRig> ControlRigClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta = (DisplayName = "Set Initial Transforms From Mesh"))
	bool bSetRefPoseFromSkeleton = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mapping, meta=(EditCondition="!bUseUnrealEngineControlRig"))
	TObjectPtr<UControlRigRemapAsset> ControlRigRemap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mapping)
	bool bUseUnrealEngineControlRig = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool bDebugDraw = false;

	
	virtual bool NeedsOnInitializeAnimInstance() const override;
#if UE_VERSION_OLDER_THAN(5, 2, 0)
	void HandleOnInitialized_AnyThread(UControlRig* Rig, EControlRigState ControlRigState, const FName& Name);
#else
	void HandleOnInitialized_AnyThread(URigVMHost* Rig, const FName& Name);
#endif
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
protected:
	UPROPERTY(transient)
	TObjectPtr<UControlRig> ControlRig;
	
	FControlRigMapping RigMapping;
	bool IsDrawDebugEnabled() const;
	virtual void DrawDebug(FControlRigContext& Context);
	virtual void InitializeProperties(const UObject* InSourceInstance, UClass* InTargetClass) override;
	virtual UClass* GetTargetClass() const override { return *ControlRigClass; }
	virtual UControlRig* GetControlRig() const override;
	virtual TSubclassOf<UControlRig> GetControlRigClass() const override;
	// Helper function to update the initial ref pose within the Control Rig if needed
	void UpdateControlRigRefPoseIfNeeded(const FAnimInstanceProxy* InProxy, bool bIncludePoseInHash = true);
	void SetBoneInitialTransformsFromCompactPose(UControlRig* InControlRig, FCSPose<FCompactPose>& InCompactPose);
private:
	void PrepareControlRig(const FAnimInstanceProxy*  AnimInstanceProxy);
	void DrawControlRig(const UWorld* World, const FTransform& ComponentTransform);
	void DrawRigPoints(const UWorld* World, const FTransform& ComponentTransform, bool bOnlyPoleLine);
#if WITH_EDITOR
	virtual void HandleObjectsReinstanced_Impl(UObject* InSourceObject, UObject* InTargetObject, const TMap<UObject*, UObject*>& OldToNewInstanceMap) override;
	
#endif
	bool ControlAligned = false;
	FGuid ControlRigDrawID{};
	float LeftHandPoleLength = 100;
	float RightHandPoleLength = 100;
	float LeftLegPoleLength = 100;
	float RightLegPoleLength = 100;

	FVector LeftHandPoleVector = FVector::ZeroVector;
	FVector RightHandPoleVector = FVector::ZeroVector;
	FVector LeftLegPoleVector = FVector::ZeroVector;
	FVector RightLegPoleVector = FVector::ZeroVector;
	
	TOptional<int32> RefPoseSetterHash;
	TMap<EHumanoidBones, FSourceBone> BoneMap;
	TMap<ERigControls, FName> RigControlMap;
	void BuildBoneMap(const FAnimInstanceProxy* InProxy);
	
	void AlignBoneToControl(EHumanoidBones Bone, ERigControls Control);
	bool AlignPole(EHumanoidBones Bone, ERigControls PoleControl, float& OutLength, FVector& OutPoleVector);
	void AlignAllControls();
	TOptional<FBoneTransform> GetBoneTransformFromContext(FControlRigContext& SolveContext, EHumanoidBones Bone, EBoneControlSpace BoneSpace);
	void SolveArm(FControlRigContext& Context, bool bIsLeft);
	void SolveLeg(FControlRigContext& Context, bool bIsLeft);
	void SetControlByBone(FControlRigContext& Context, EHumanoidBones Bone, ERigControls Control, EControlEffect Effect);
	FQuat MakeControlRotationByBoneRotation(EHumanoidBones Bone, const FQuat& TargetBoneRotation);
	bool ConvertBoneTransformToControlTransform(FControlRigContext& Context, EHumanoidBones Bone, FTransform& InOutTransform);
	FRigBoneElement* FindImportBoneElement(EHumanoidBones Bone);
	TWeakPtr<FMediaPipeAnimContext> SharedContext;
};
