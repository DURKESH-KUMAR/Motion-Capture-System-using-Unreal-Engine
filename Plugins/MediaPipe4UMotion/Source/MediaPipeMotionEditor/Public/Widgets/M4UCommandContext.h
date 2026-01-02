// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "Animation/MediaPipeAnimInstance.h"
#include "MediaPipeHolisticComponent.h"
#include "StaticImageSourceComponent.h"

/**
 * 
 */
class MEDIAPIPEMOTIONEDITOR_API FM4UCommandContext : public TSharedFromThis<FM4UCommandContext>
{
public:
	FM4UCommandContext(){}
	void ResetState();

	bool IsMediaPipeRunning() const;

	TWeakObjectPtr<UMediaPipeHolisticComponent> MediaPipeHolisticComponent = nullptr;
	TWeakObjectPtr<UStaticImageSourceComponent> StaticImageSourceInWorld = nullptr;
	TWeakObjectPtr<UMediaPipeAnimInstance> MediaPipeAnimInstance = nullptr;

	mutable TWeakObjectPtr<UWorld> World = nullptr;
};

DECLARE_DELEGATE_OneParam(FM4UActionDelegate, const TSharedRef<FM4UCommandContext>&);
DECLARE_DELEGATE_RetVal_OneParam(bool, FM4UActionCanExecuteDelegate, const TSharedRef<FM4UCommandContext>&);