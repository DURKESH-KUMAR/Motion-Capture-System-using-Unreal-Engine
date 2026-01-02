// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ETextStatus
{
	Disabled,
	Info,
	Warning,
	Error,
	Succeed,
};


/**
 * 
 */
class MEDIAPIPEEDITOR_API SStatusText : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SStatusText) :
	_Status(ETextStatus::Disabled),
	_Text(FText()),
	_FontSize(FCoreStyle::RegularTextSize),
	_UsePoint(false)
	{}

	SLATE_ATTRIBUTE(ETextStatus, Status)
	SLATE_ATTRIBUTE(FText, Text)
	SLATE_ATTRIBUTE(int, FontSize)
	SLATE_ARGUMENT(bool, UsePoint)
	SLATE_END_ARGS();

	FSlateColor GetStatusColor() const;
	FText GetStatusIcon(ETextStatus Status, bool bUsePoint) const;
	void Construct(const FArguments& InArgs);

private:
	TAttribute<ETextStatus> StatusAttribute;
};

