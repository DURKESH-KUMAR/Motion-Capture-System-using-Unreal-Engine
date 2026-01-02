// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

class MEDIAPIPEEDITOR_API SFormTextWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SFormTextWidget) :
	_LabelWidth(0),
	_ValueWidth(0),
	_VAlign(VAlign_Top),
	_ValueAlign(HAlign_Left),
	_RightToLeft(false)
	{}

	SLATE_ATTRIBUTE(FText, Label)

	SLATE_ARGUMENT(float, LabelWidth)
	SLATE_ARGUMENT(float, ValueWidth)
	SLATE_ATTRIBUTE(FSlateFontInfo, LabelFont)

	SLATE_ATTRIBUTE( FText, Value )
	SLATE_ATTRIBUTE(FSlateFontInfo, ValueFont)
	SLATE_ATTRIBUTE( FSlateColor, ValueColorAndOpacity )
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)
	SLATE_ARGUMENT(EHorizontalAlignment, ValueAlign)
	SLATE_ARGUMENT(bool, RightToLeft)

	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs);
};
