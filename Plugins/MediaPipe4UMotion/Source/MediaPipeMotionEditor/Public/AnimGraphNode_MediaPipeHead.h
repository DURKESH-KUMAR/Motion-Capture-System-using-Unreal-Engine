// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include <CoreMinimal.h>
#include "EdGraph/EdGraphNode.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_MediaPipeHead.h"
#include "AnimGraphNode_MediaPipeHead.generated.h"

/**
 * 
 */
UCLASS(meta=(Keywords = "MediaPipe Hand Solver"))
class MEDIAPIPEMOTIONEDITOR_API UAnimGraphNode_MediaPipeHead  : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()
public:

	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
protected:
	virtual const FAnimNode_MediaPipeHead* GetNode() const override { return &Node; }
	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;
private:
	
	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_MediaPipeHead Node;
};