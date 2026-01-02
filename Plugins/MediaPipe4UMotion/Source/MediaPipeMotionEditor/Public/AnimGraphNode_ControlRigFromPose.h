// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_CustomProperty.h"
#include "AnimNode_ControlRigFromPose.h"
#include "AnimGraphNode_ControlRigFromPose.generated.h"

/**
 * 
 */
UCLASS(meta=(Keywords = "Control Rig From Pose"))
class MEDIAPIPEMOTIONEDITOR_API UAnimGraphNode_ControlRigFromPose : public UAnimGraphNode_CustomProperty
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override; 
	virtual FLinearColor GetNodeTitleColor() const override;
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_ControlRigFromPose Node;
protected:
	virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override { return &Node; }
	virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override { return &Node; }
	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;
};
