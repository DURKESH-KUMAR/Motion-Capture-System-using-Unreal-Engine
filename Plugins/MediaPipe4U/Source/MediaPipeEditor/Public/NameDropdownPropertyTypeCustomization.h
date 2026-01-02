// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

class MEDIAPIPEEDITOR_API FDropdownPropertyTypeCustomization  : public IPropertyTypeCustomization
{
public:
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
protected:
	virtual FText GetDropdownTitle() = 0;
	//virtual FName GetNamePropertyName() = 0;
	virtual TArray<FName> GetNamesForSelection() = 0;
	virtual void SetPropertyValue(const TSharedRef<IPropertyHandle>& PropertyHandle, const FName& Value) = 0;
	virtual FName GetPropertyValue(const TSharedRef<IPropertyHandle>& PropertyHandle) = 0;
	virtual bool FilterOwnerObject(UObject* OuterInstance) { return true; }
private:
	TSharedPtr<IPropertyHandle> StructPropertyHandler;
	void OnNameSelected(const FName& Name);
	TSharedPtr<IPropertyUtilities> PropertyUtilities;
};
