// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "Styling/SlateBrush.h"
#include "Fonts/SlateFontInfo.h"
#include "Misc/EngineVersionComparison.h"
#include "Framework/Docking/WorkspaceItem.h"
#include "Materials/MaterialExpression.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Input/SComboButton.h"
#include "AssetTypeCategories.h"
#include "IAssetTypeActions.h"


#if UE_VERSION_OLDER_THAN(5, 1, 0)
typedef FName FObjectPath;
#else
typedef FSoftObjectPath FObjectPath;
#endif

enum class EIconBrush
{
	Info,
	Warning,
	Error,
};

class SButton;

class MEDIAPIPEEDITOR_API FMediaPipeEditorUtils
{
public:
	static const FName& GetMediaPipe4UStyleSetName();
	static TSharedPtr<FSlateStyleSet> GetMediaPipe4UStyleSet();
	static FSlateIcon GetImageIcon(const FName& IconName);

	static TSharedRef<SButton> CreateImageButton(TAttribute<const FSlateBrush*> Image, TAttribute<FText> Text);
	static TSharedRef<SComboButton> CreateImageComboButton(TAttribute<const FSlateBrush*> Image, TAttribute<FText> Text);
	static FToolMenuSection& ExtendMediaPipeToolkitsSection();
	static FName GetMediaPipeToolkitMenu();
	static FName CreateMediaPipeSubMenuName(const FString& Name);
	static FAssetData OpenAssetSelection(UClass* AssetType, const FText& WindowTitle = FText::FromString(TEXT("")), const FVector2D& WindowSize = FVector2D(600.0f, 500.0f));
	static UThumbnailInfo* GetBlueprintThumbnailInfo(UBlueprint* InBlueprint);
	static TSharedPtr<SWidget> CreateThumbnailOverlay();
	static const ISlateStyle& GetStyle();
	static FName GetStyleSetName();
	static FSlateFontInfo GetSmallSizeFontStyle();
	static FSlateFontInfo GetXSmallSizeFontStyle();
	static FSlateFontInfo GetBoldFontStyle(int FontSize = -1);
	static FSlateFontInfo GetDefaultFontStyle(int FontSize = -1);

	static void UnregisterAssertTypes(const TArray<TSharedPtr<IAssetTypeActions>>& InActions);
	
	static FString RichTextCreateLink(const FText& Text, const FString& Url, const FString Id = "browser");
	static TSharedRef<SRichTextBlock> NewRichTextBlock(const FString& InText, const FSlateFontInfo* FontInfo = nullptr);
	static TSharedRef<SRichTextBlock> NewHyperlink(const FText& Text, const FString& Url, const FSlateFontInfo* FontInfo = nullptr);
	/**
	 * Key is text, value is link url.
	 */
	static TSharedRef<SRichTextBlock> NewHyperlinks(const TMap<FString, FString>& Links, const FString& Separators = "\n\n", bool RemoveEndSeparators = false); 

	static FSlateFontInfo GetFontAwesomeStyle(int FontSize = -1);
	static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr);
	static FSlateFontInfo GetFontStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr);
	static const FLinearColor& GetPrimaryColor();
	static const FLinearColor& GetDangerColor();
	static FSlateColor GetDefaultForeground();
	static UMaterial* CreateTextureMaterial(const FName& MaterialName, const FName& TextureParameterName,  TObjectPtr<UTexture2D> DefaultTexture = nullptr);
	static TSharedPtr<FWorkspaceItem> GetLevelEditorRuntimeToolCategory(); 
	static TSharedPtr<FWorkspaceItem> GetLevelEditorAssetToolCategory();
	static FObjectPath GetObjectPath(const FAssetData& Data);
	static const FSlateBrush* GetIconBrush(EIconBrush Icon);
	static EAssetTypeCategories::Type GetMediaPipe4UAssetCategory();
private:
	static EAssetTypeCategories::Type MediaPipe4UAssetCategory;
	static FCriticalSection AssetCategoryCritical;
	static void AddExpressionToMaterial(UMaterial* Material, UMaterialExpression* Expression);
};
