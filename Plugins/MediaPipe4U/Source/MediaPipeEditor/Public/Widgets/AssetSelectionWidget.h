// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "ContentBrowserDelegates.h"

class MEDIAPIPEEDITOR_API SAssetSelectionWidget :public SCompoundWidget
{
public:
	DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData& /*SelectedAsset*/);

	SLATE_BEGIN_ARGS(SAssetSelectionWidget) {}
	SLATE_ARGUMENT(UClass*, AssetType)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetOnAssetSelected(const FOnAssetSelected& InHandler);
	void CloseDialog();
protected:
	void OnAssetSelected(const FAssetData& AssetData);
	void OnAssetsActivated(const TArray<FAssetData>& SelectedAssets, EAssetTypeActivationMethod::Type ActivationType);
private:

	FReply OnConfirmClicked();
	FReply OnCancelClicked();
	
	TArray<FAssetData> CurrentlySelectedAssets;
	void DoSelectAsset(const FAssetData& SelectedAsset);
	bool bValidAssetChosen = false;
	FOnAssetSelected OnAssetSelectedHandler;
	TSharedPtr<SWidget> AssetPicker;
	FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;
};
