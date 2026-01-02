// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Styling/SlateTypes.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

class MEDIAPIPEEDITOR_API STabView : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(STabView)
	{}

	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs);
	const FDockTabStyle& GetCurrentStyle() const;

	void AddTab(const FText& TabHeader, TSharedRef<SWidget> Content);
	void SelectTab(int TabIndex);
private:
	TSharedPtr<SWrapBox> TabHeaders;
	TSharedPtr<SWidgetSwitcher> TabContainer;
	TArray<TSharedPtr<SBorder>> TabHeaderItems;
	const FDockTabStyle* MajorTabStyle = nullptr;
	int SelectedTabIndex = -1;
	ECheckBoxState OnTabChanged(int TabIndex) const;
	const FSlateBrush* GetImageBrush(int Index) const;
	
	FReply OnTabClick(const FGeometry& Geometry, const FPointerEvent& PointerEvent, int TabIndex);
	FMargin GetTabPadding() const;
};
