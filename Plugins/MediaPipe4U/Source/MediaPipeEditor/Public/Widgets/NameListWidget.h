#pragma once

DECLARE_DELEGATE_OneParam(FOnNameSelectionChanged, const FName);

class MEDIAPIPEEDITOR_API SNameListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNameListWidget):
		_MinHeight(512)
	{}

	SLATE_ARGUMENT(int, MinHeight)
	SLATE_ARGUMENT(FText, Title)
	SLATE_ARGUMENT(FName, SelectedName)
	SLATE_ARGUMENT(TArray<FName>, NameList)
	SLATE_EVENT(FOnNameSelectionChanged, OnSelectionChanged)

	SLATE_END_ARGS();

	/**
	* Construct this widget
	*
	* @param	InArgs	The declaration data for this widget
	*/
	void Construct(const FArguments& InArgs);

	/** Get the filter text widget, e.g. for focus */
	TSharedPtr<SWidget> GetFilterTextWidget();
	void SetDataSource(const TArray<FName>& InDataSource, const FName& Selected);
private:
	void RebuildFilteredList(const FName& Selected);
	void OnFilterTextChanged(const FText& Text);
	
	FOptionalSize GetHeight() const;
	void ComboBoxSelectionChanged(TSharedPtr<FName> StringItem, ESelectInfo::Type SelectInfo) const;
	TSharedRef<ITableRow> MakeListRow(TSharedPtr<FName> Name, const TSharedRef<STableViewBase, ESPMode::ThreadSafe>& TableViewBase) const;

	/** The actual list of FName values to choose from */
	TArray<FName> RawNameList;
	TArray<TSharedPtr<FName>> FilteredNameList;

	//Filter text widget
	TSharedPtr<SSearchBox> FilterTextWidget;
	TSharedPtr<SListView<TSharedPtr<FName>>> NameListView;
	FOnNameSelectionChanged OnSelectionChanged;
	// Text to filter bone tree with
	FText FilterText;
	FText Title;
	int MinHeight = 0;
	float ListItemHeight = 24;
};
