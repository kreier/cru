//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "ExtensionBlockFormClass.h"
#include "DetailedResolutionFormClass.h"
#include "AddCEADataFormClass.h"
#include "TVResolutionListFormClass.h"
#include "AudioFormatListFormClass.h"
#include "SpeakerSetupFormClass.h"
#include "HDMISupportFormClass.h"
#include "HDMI2SupportFormClass.h"
#include "FreeSyncRangeFormClass.h"
#include "ColorimetryFormClass.h"
#include "VideoCapabilityFormClass.h"
#include "HDRStaticMetadataFormClass.h"
#include "StandardResolutionFormClass.h"
#include "AddDIDDataFormClass.h"
#include "DIDDetailedResolutionListFormClass.h"
#include "TiledDisplayTopologyFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TExtensionBlockForm *ExtensionBlockForm;
//---------------------------------------------------------------------------
__fastcall TExtensionBlockForm::TExtensionBlockForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
	DetailedLastItemIndex = -1;
	DetailedLastClickedItemIndex = -1;
	CEADataLastItemIndex = -1;
	CEADataLastClickedItemIndex = -1;
	StandardLastItemIndex = -1;
	StandardLastClickedItemIndex = -1;
	DIDDataLastItemIndex = -1;
	DIDDataLastClickedItemIndex = -1;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::Connect(ExtensionBlockClass &NewExtensionBlock, const DetailedResolutionClass &NewNativeResolution, const PropertiesClass &NewProperties)
{
	ExtensionBlock = &NewExtensionBlock;
	NativeResolution = NewNativeResolution;
	Properties = NewProperties;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::Refresh(void *Value, int ItemIndex)
{
	Refreshing = true;
	RefreshExtensionTypeComboBox();
	RefreshExtensionButtons();

	switch (ExtensionBlock->GetType())
	{
		case CEA_EXT:
			DetailedGroupBox->Visible = true;
			CEADataGroupBox->Visible = true;
			StandardGroupBox->Visible = false;
			DIDDataGroupBox->Visible = false;
			DefaultOutline->Visible = false;
			DefaultLabel->Visible = false;
			FormOKButton->Top = CEADataGroupBox->Top + CEADataGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case VTB_EXT:
			DetailedGroupBox->Visible = true;
			CEADataGroupBox->Visible = false;
			StandardGroupBox->Visible = true;
			DIDDataGroupBox->Visible = false;
			DefaultOutline->Visible = false;
			DefaultLabel->Visible = false;
			FormOKButton->Top = StandardGroupBox->Top + StandardGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case DISPLAYID_EXT:
		case DISPLAYID2_EXT:
			DetailedGroupBox->Visible = false;
			CEADataGroupBox->Visible = false;
			StandardGroupBox->Visible = false;
			DIDDataGroupBox->Visible = true;
			DefaultOutline->Visible = false;
			DefaultLabel->Visible = false;
			FormOKButton->Top = DIDDataGroupBox->Top + DIDDataGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case DEFAULT_EXT:
			DetailedGroupBox->Visible = false;
			CEADataGroupBox->Visible = false;
			StandardGroupBox->Visible = false;
			DIDDataGroupBox->Visible = false;
			DefaultOutline->Visible = true;
			DefaultLabel->Visible = true;
			FormOKButton->Top = DefaultOutline->Top + DefaultOutline->Height + Scale + ButtonTop;
			break;
	}

	FormCancelButton->Top = FormOKButton->Top;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;

	if (Value == NULL || Value == DetailedGroupBox)
	{
		RefreshDetailedCaption();
		RefreshDetailedListBox(ItemIndex);
		RefreshDetailedButtons();
		RefreshCEADataCaption();
		RefreshCEADataButtons();
		RefreshStandardCaption();
		RefreshStandardButtons();
	}

	if (Value == NULL || Value == CEADataGroupBox)
	{
		RefreshDetailedCaption();
		RefreshDetailedListBox(DetailedListBox->ItemIndex);
		RefreshDetailedButtons();
		RefreshCEADataCaption();
		RefreshCEADataListBox(ItemIndex);
		RefreshCEADataButtons();
	}

	if (Value == NULL || Value == StandardGroupBox)
	{
		RefreshDetailedCaption();
		RefreshDetailedListBox(DetailedListBox->ItemIndex);
		RefreshDetailedButtons();
		RefreshStandardCaption();
		RefreshStandardListBox(ItemIndex);
		RefreshStandardButtons();
	}

	if (Value == NULL || Value == DIDDataGroupBox)
	{
		RefreshDIDDataCaption();
		RefreshDIDDataListBox(ItemIndex);
		RefreshDIDDataButtons();
	}

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::InitExtensionTypeComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = ExtensionTypeComboBox->ItemIndex;
	ExtensionTypeComboBox->Items->BeginUpdate();
	ExtensionTypeComboBox->Clear();

	for (Index = 0; ExtensionBlock->GetTypeText(Index, Text, TEXTSIZE); Index++)
		ExtensionTypeComboBox->Items->Add(Text);

	ExtensionTypeComboBox->ItemIndex = ItemIndex;
	ExtensionTypeComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshExtensionTypeComboBox()
{
	ExtensionTypeComboBox->ItemIndex = ExtensionBlock->GetType();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshExtensionButtons()
{
	ExtensionCopyButton->Enabled = ExtensionBlock->ExtensionCopyPossible();
	ExtensionPasteButton->Enabled = ExtensionBlock->ExtensionPastePossible();
	ExtensionResetButton->Enabled = ExtensionBlock->ExtensionResetPossible();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshDetailedCaption()
{
	const char *Caption = " Detailed resolutions ";
	char Text[TEXTSIZE];

	ExtensionBlock->DetailedResolutions()->GetSlotsLeftText(Caption, Text, TEXTSIZE);
	DetailedGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshDetailedListBox(int ItemIndex)
{
	int Index;
	char Text[TEXTSIZE];

	if (ExtensionBlock->DetailedResolutions()->GetMaxCount() > 0)
	{
		DetailedListBox->Enabled = true;
		DetailedListBox->Color = clWindow;
		DetailedListBox->Font->Color = clWindowText;
	}
	else
	{
		DetailedListBox->Enabled = false;
		DetailedListBox->Color = clBtnFace;
		DetailedListBox->Font->Color = clGrayText;
		ItemIndex = -1;
	}

	int TopIndex = DetailedListBox->TopIndex;
	DetailedListBox->Items->BeginUpdate();
	DetailedListBox->Clear();
	DetailedResolutionClass DetailedResolution;

	for (Index = 0; ExtensionBlock->DetailedResolutions()->Get(Index, DetailedResolution); Index++)
		if (DetailedResolution.GetText(Text, TEXTSIZE, Dash()))
			DetailedListBox->Items->Add(Text);

	if (Index == 0 && ExtensionBlock->DetailedResolutions()->GetMaxCount() > 0)
		DetailedListBox->Items->Add("No detailed resolutions");

	for (Index = 0; ExtensionBlock->DetailedGetExtensionText(Index, Text, TEXTSIZE); Index++)
		DetailedListBox->Items->Add(Text);

	if (ItemIndex > 0)
		DetailedListBox->TopIndex = TopIndex;

	if (ItemIndex < ExtensionBlock->DetailedResolutions()->GetCount())
		DetailedListBox->ItemIndex = ItemIndex;

	DetailedListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshDetailedButtons()
{
	DetailedLastItemIndex = DetailedListBox->ItemIndex;
	DetailedAddButton->Enabled = ExtensionBlock->DetailedResolutions()->AddPossible();
	DetailedEditButton->Enabled = ExtensionBlock->DetailedResolutions()->EditPossible(DetailedListBox->ItemIndex);
	DetailedDeleteButton->Enabled = ExtensionBlock->DetailedResolutions()->DeletePossible(DetailedListBox->ItemIndex);
	DetailedDeleteAllButton->Enabled = ExtensionBlock->DetailedResolutions()->DeleteAllPossible();
	DetailedResetButton->Enabled = ExtensionBlock->DetailedResolutions()->UndoPossible();
	DetailedUpButton->Enabled = ExtensionBlock->DetailedResolutions()->ExchangePossible(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex - 1);
	DetailedDownButton->Enabled = ExtensionBlock->DetailedResolutions()->ExchangePossible(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshCEADataCaption()
{
	const char *Caption = " Data blocks ";
	char Text[TEXTSIZE];

	ExtensionBlock->CEAData()->GetBytesLeftText(Caption, Text, TEXTSIZE);
	CEADataGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshCEADataListBox(int ItemIndex)
{
	int Index;

	int TopIndex = CEADataListBox->TopIndex;
	CEADataListBox->Items->BeginUpdate();
	CEADataListBox->Clear();

	for (Index = 0; Index < ExtensionBlock->CEAData()->GetCount(); Index++)
		CEADataListBox->Items->Add("Text");

	if (Index == 0)
		CEADataListBox->Items->Add("No data blocks");

	if (ItemIndex > 0)
		CEADataListBox->TopIndex = TopIndex;

	if (ItemIndex < ExtensionBlock->CEAData()->GetCount())
		CEADataListBox->ItemIndex = ItemIndex;

	CEADataListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshCEADataButtons()
{
	CEADataLastItemIndex = CEADataListBox->ItemIndex;
	CEADataAddButton->Enabled = ExtensionBlock->CEAData()->AddPossible();
	CEADataEditButton->Enabled = ExtensionBlock->CEAData()->EditPossible(CEADataListBox->ItemIndex);
	CEADataDeleteButton->Enabled = ExtensionBlock->CEAData()->DeletePossible(CEADataListBox->ItemIndex);
	CEADataDeleteAllButton->Enabled = ExtensionBlock->CEAData()->DeleteAllPossible();
	CEADataResetButton->Enabled = ExtensionBlock->CEAData()->UndoPossible() || ExtensionBlock->ColorFormats()->UndoPossible();
	CEADataUpButton->Enabled = ExtensionBlock->CEAData()->ExchangePossible(CEADataListBox->ItemIndex, CEADataListBox->ItemIndex - 1);
	CEADataDownButton->Enabled = ExtensionBlock->CEAData()->ExchangePossible(CEADataListBox->ItemIndex, CEADataListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshStandardCaption()
{
	const char *Caption = " Standard resolutions ";
	char Text[TEXTSIZE];

	ExtensionBlock->StandardResolutions()->GetSlotsLeftText(Caption, Text, TEXTSIZE);
	StandardGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshStandardListBox(int ItemIndex)
{
	int Index;
	char Text[TEXTSIZE];

	int TopIndex = StandardListBox->TopIndex;

	if (ExtensionBlock->StandardResolutions()->GetCount() <= StandardRows * StandardListBox->Columns)
	{
		StandardListBox->Clear();
		StandardListBox->Items->BeginUpdate();
	}
	else
	{
		StandardListBox->Items->BeginUpdate();
		StandardListBox->Clear();
	}

	StandardResolutionClass StandardResolution;

	for (Index = 0; ExtensionBlock->StandardResolutions()->Get(Index, StandardResolution); Index++)
		if (StandardResolution.GetText(Text, TEXTSIZE))
			StandardListBox->Items->Add(Text);

	if (Index == 0)
		StandardListBox->Items->Add("No standard resolutions");

	if (ItemIndex > 0)
		StandardListBox->TopIndex = TopIndex;

	if (ItemIndex < ExtensionBlock->StandardResolutions()->GetCount())
		StandardListBox->ItemIndex = ItemIndex;

	StandardListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshStandardButtons()
{
	StandardLastItemIndex = StandardListBox->ItemIndex;
	StandardAddButton->Enabled = ExtensionBlock->StandardResolutions()->AddPossible();
	StandardEditButton->Enabled = ExtensionBlock->StandardResolutions()->EditPossible(StandardListBox->ItemIndex);
	StandardDeleteButton->Enabled = ExtensionBlock->StandardResolutions()->DeletePossible(StandardListBox->ItemIndex);
	StandardDeleteAllButton->Enabled = ExtensionBlock->StandardResolutions()->DeleteAllPossible();
	StandardResetButton->Enabled = ExtensionBlock->StandardResolutions()->UndoPossible();
	StandardUpButton->Enabled = ExtensionBlock->StandardResolutions()->ExchangePossible(StandardListBox->ItemIndex, StandardListBox->ItemIndex - 1);
	StandardDownButton->Enabled = ExtensionBlock->StandardResolutions()->ExchangePossible(StandardListBox->ItemIndex, StandardListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshDIDDataCaption()
{
	const char *Caption = " Data blocks ";
	char Text[TEXTSIZE];

	ExtensionBlock->DIDData()->GetBytesLeftText(Caption, Text, TEXTSIZE);
	DIDDataGroupBox->Caption = Text;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshDIDDataListBox(int ItemIndex)
{
	int Index;

	int TopIndex = DIDDataListBox->TopIndex;
	DIDDataListBox->Items->BeginUpdate();
	DIDDataListBox->Clear();

	for (Index = 0; Index < ExtensionBlock->DIDData()->GetCount(); Index++)
		DIDDataListBox->Items->Add("Text");

	if (Index == 0)
		DIDDataListBox->Items->Add("No data blocks");

	if (ItemIndex > 0)
		DIDDataListBox->TopIndex = TopIndex;

	if (ItemIndex < ExtensionBlock->DIDData()->GetCount())
		DIDDataListBox->ItemIndex = ItemIndex;

	DIDDataListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::RefreshDIDDataButtons()
{
	DIDDataLastItemIndex = DIDDataListBox->ItemIndex;
	DIDDataAddButton->Enabled = ExtensionBlock->DIDData()->AddPossible();
	DIDDataEditButton->Enabled = ExtensionBlock->DIDData()->EditPossible(DIDDataListBox->ItemIndex);
	DIDDataDeleteButton->Enabled = ExtensionBlock->DIDData()->DeletePossible(DIDDataListBox->ItemIndex);
	DIDDataDeleteAllButton->Enabled = ExtensionBlock->DIDData()->DeleteAllPossible();
	DIDDataResetButton->Enabled = ExtensionBlock->DIDData()->UndoPossible();
	DIDDataUpButton->Enabled = ExtensionBlock->DIDData()->ExchangePossible(DIDDataListBox->ItemIndex, DIDDataListBox->ItemIndex - 1);
	DIDDataDownButton->Enabled = ExtensionBlock->DIDData()->ExchangePossible(DIDDataListBox->ItemIndex, DIDDataListBox->ItemIndex + 1);
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::ScaleControls()
{
	ExtensionTypeLabel->Left = Scale;
	ExtensionTypeLabel->Top = Scale + 4;

	ExtensionTypeComboBox->Height = ComboBoxHeight;
	ExtensionTypeComboBox->Left = ExtensionTypeLabel->Left + ExtensionTypeLabel->Width + LabelSpacing;
	ExtensionTypeComboBox->Top = ExtensionTypeLabel->Top - 4;

	ExtensionCopyButton->Width = ButtonWidth;
	ExtensionCopyButton->Height = ButtonHeight;
	ExtensionCopyButton->Top = ExtensionTypeComboBox->Top;
	FixButtonCaption(ExtensionCopyButton, Canvas->TextWidth(ExtensionCopyButton->Caption));

	ExtensionPasteButton->Width = ButtonWidth;
	ExtensionPasteButton->Height = ButtonHeight;
	ExtensionPasteButton->Top = ExtensionCopyButton->Top;
	FixButtonCaption(ExtensionPasteButton, Canvas->TextWidth(ExtensionPasteButton->Caption));

	ExtensionResetButton->Width = ButtonWidth;
	ExtensionResetButton->Height = ButtonHeight;
	ExtensionResetButton->Top = ExtensionPasteButton->Top;
	FixButtonCaption(ExtensionResetButton, Canvas->TextWidth(ExtensionResetButton->Caption));

	DetailedListBox->Width = ListBoxWidth;
	DetailedListBox->Height = Text.tmHeight * DetailedRows + 4;
	DetailedListBox->ItemHeight = Text.tmHeight;
	DetailedListBox->Left = PaddingWidth;
	DetailedListBox->Top = PaddingTop;

	DetailedAddButton->Width = ButtonWidth;
	DetailedAddButton->Height = ButtonHeight;
	DetailedAddButton->Left = DetailedListBox->Left + ButtonLeft;
	DetailedAddButton->Top = DetailedListBox->Top + DetailedListBox->Height + Scale + ButtonTop;
	FixButtonCaption(DetailedAddButton, Canvas->TextWidth(DetailedAddButton->Caption));

	DetailedEditButton->Width = ButtonWidth;
	DetailedEditButton->Height = ButtonHeight;
	DetailedEditButton->Left = DetailedAddButton->Left + DetailedAddButton->Width;
	DetailedEditButton->Top = DetailedAddButton->Top;
	FixButtonCaption(DetailedEditButton, Canvas->TextWidth(DetailedEditButton->Caption));

	DetailedDeleteButton->Width = ButtonWidth;
	DetailedDeleteButton->Height = ButtonHeight;
	DetailedDeleteButton->Left = DetailedEditButton->Left + DetailedEditButton->Width;
	DetailedDeleteButton->Top = DetailedEditButton->Top;
	FixButtonCaption(DetailedDeleteButton, Canvas->TextWidth(DetailedDeleteButton->Caption));

	DetailedDeleteAllButton->Width = LongButtonWidth;
	DetailedDeleteAllButton->Height = LongButtonHeight;
	DetailedDeleteAllButton->Left = DetailedDeleteButton->Left + DetailedDeleteButton->Width;
	DetailedDeleteAllButton->Top = DetailedDeleteButton->Top;
	FixButtonCaption(DetailedDeleteAllButton, Canvas->TextWidth(DetailedDeleteAllButton->Caption));

	DetailedResetButton->Width = ButtonWidth;
	DetailedResetButton->Height = ButtonHeight;
	DetailedResetButton->Left = DetailedDeleteAllButton->Left + DetailedDeleteAllButton->Width;
	DetailedResetButton->Top = DetailedDeleteAllButton->Top;
	FixButtonCaption(DetailedResetButton, Canvas->TextWidth(DetailedResetButton->Caption));

	DetailedUpButton->Width = ArrowButtonWidth;
	DetailedUpButton->Height = ArrowButtonHeight;
	DetailedUpButton->Top = DetailedResetButton->Top;
	DetailedUpButton->Enabled = false;
	DetailedUpButton->NumGlyphs = NumGlyphs;
	DetailedUpButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_UP));

	DetailedDownButton->Width = ArrowButtonWidth;
	DetailedDownButton->Height = ArrowButtonHeight;
	DetailedDownButton->Top = DetailedUpButton->Top;
	DetailedDownButton->Enabled = false;
	DetailedDownButton->NumGlyphs = NumGlyphs;
	DetailedDownButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_DOWN));

	DetailedDownButton->Left = DetailedListBox->Left + DetailedListBox->Width - ButtonRight - DetailedDownButton->Width;
	DetailedUpButton->Left = DetailedDownButton->Left - DetailedUpButton->Width;

	DetailedGroupBox->Width = DetailedListBox->Left + DetailedListBox->Width + PaddingWidth;
	DetailedGroupBox->Height = DetailedAddButton->Top + DetailedAddButton->Height + ButtonBottom + PaddingBottom;
	DetailedGroupBox->Left = Scale;
	DetailedGroupBox->Top = ExtensionTypeComboBox->Top + ExtensionTypeComboBox->Height + GroupBoxTop;

	CEADataListBox->Width = DetailedListBox->Width;
	CEADataListBox->Height = Text.tmHeight * CEADataRows + 4;
	CEADataListBox->ItemHeight = Text.tmHeight;
	CEADataListBox->Left = PaddingWidth;
	CEADataListBox->Top = PaddingTop;

	CEADataAddButton->Width = ButtonWidth;
	CEADataAddButton->Height = ButtonHeight;
	CEADataAddButton->Left = CEADataListBox->Left + ButtonLeft;
	CEADataAddButton->Top = CEADataListBox->Top + CEADataListBox->Height + Scale + ButtonTop;
	FixButtonCaption(CEADataAddButton, Canvas->TextWidth(CEADataAddButton->Caption));

	CEADataEditButton->Width = ButtonWidth;
	CEADataEditButton->Height = ButtonHeight;
	CEADataEditButton->Left = CEADataAddButton->Left + CEADataAddButton->Width;
	CEADataEditButton->Top = CEADataAddButton->Top;
	FixButtonCaption(CEADataEditButton, Canvas->TextWidth(CEADataEditButton->Caption));

	CEADataDeleteButton->Width = ButtonWidth;
	CEADataDeleteButton->Height = ButtonHeight;
	CEADataDeleteButton->Left = CEADataEditButton->Left + CEADataEditButton->Width;
	CEADataDeleteButton->Top = CEADataEditButton->Top;
	FixButtonCaption(CEADataDeleteButton, Canvas->TextWidth(CEADataDeleteButton->Caption));

	CEADataDeleteAllButton->Width = LongButtonWidth;
	CEADataDeleteAllButton->Height = LongButtonHeight;
	CEADataDeleteAllButton->Left = CEADataDeleteButton->Left + CEADataDeleteButton->Width;
	CEADataDeleteAllButton->Top = CEADataDeleteButton->Top;
	FixButtonCaption(CEADataDeleteAllButton, Canvas->TextWidth(CEADataDeleteAllButton->Caption));

	CEADataResetButton->Width = ButtonWidth;
	CEADataResetButton->Height = ButtonHeight;
	CEADataResetButton->Left = CEADataDeleteAllButton->Left + CEADataDeleteAllButton->Width;
	CEADataResetButton->Top = CEADataDeleteAllButton->Top;
	FixButtonCaption(CEADataResetButton, Canvas->TextWidth(CEADataResetButton->Caption));

	CEADataUpButton->Width = ArrowButtonWidth;
	CEADataUpButton->Height = ArrowButtonHeight;
	CEADataUpButton->Top = CEADataResetButton->Top;
	CEADataUpButton->Enabled = false;
	CEADataUpButton->NumGlyphs = NumGlyphs;
	CEADataUpButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_UP));

	CEADataDownButton->Width = ArrowButtonWidth;
	CEADataDownButton->Height = ArrowButtonHeight;
	CEADataDownButton->Top = CEADataUpButton->Top;
	CEADataDownButton->Enabled = false;
	CEADataDownButton->NumGlyphs = NumGlyphs;
	CEADataDownButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_DOWN));

	CEADataDownButton->Left = CEADataListBox->Left + CEADataListBox->Width - ButtonRight - CEADataDownButton->Width;
	CEADataUpButton->Left = CEADataDownButton->Left - CEADataUpButton->Width;

	CEADataGroupBox->Width = DetailedGroupBox->Width;
	CEADataGroupBox->Height = CEADataAddButton->Top + CEADataAddButton->Height + ButtonBottom + PaddingBottom;
	CEADataGroupBox->Left = DetailedGroupBox->Left;
	CEADataGroupBox->Top = DetailedGroupBox->Top + DetailedGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	StandardListBox->Width = DetailedListBox->Width;
	StandardListBox->Height = Text.tmHeight * StandardRows + 4;
	StandardListBox->ItemHeight = Text.tmHeight;
	StandardListBox->Left = PaddingWidth;
	StandardListBox->Top = PaddingTop;

	StandardAddButton->Width = ButtonWidth;
	StandardAddButton->Height = ButtonHeight;
	StandardAddButton->Left = StandardListBox->Left + ButtonLeft;
	StandardAddButton->Top = StandardListBox->Top + StandardListBox->Height + Scale + ButtonTop;
	FixButtonCaption(StandardAddButton, Canvas->TextWidth(StandardAddButton->Caption));

	StandardEditButton->Width = ButtonWidth;
	StandardEditButton->Height = ButtonHeight;
	StandardEditButton->Left = StandardAddButton->Left + StandardAddButton->Width;
	StandardEditButton->Top = StandardAddButton->Top;
	FixButtonCaption(StandardEditButton, Canvas->TextWidth(StandardEditButton->Caption));

	StandardDeleteButton->Width = ButtonWidth;
	StandardDeleteButton->Height = ButtonHeight;
	StandardDeleteButton->Left = StandardEditButton->Left + StandardEditButton->Width;
	StandardDeleteButton->Top = StandardEditButton->Top;
	FixButtonCaption(StandardDeleteButton, Canvas->TextWidth(StandardDeleteButton->Caption));

	StandardDeleteAllButton->Width = LongButtonWidth;
	StandardDeleteAllButton->Height = LongButtonHeight;
	StandardDeleteAllButton->Left = StandardDeleteButton->Left + StandardDeleteButton->Width;
	StandardDeleteAllButton->Top = StandardDeleteButton->Top;
	FixButtonCaption(StandardDeleteAllButton, Canvas->TextWidth(StandardDeleteAllButton->Caption));

	StandardResetButton->Width = ButtonWidth;
	StandardResetButton->Height = ButtonHeight;
	StandardResetButton->Left = StandardDeleteAllButton->Left + StandardDeleteAllButton->Width;
	StandardResetButton->Top = StandardDeleteAllButton->Top;
	FixButtonCaption(StandardResetButton, Canvas->TextWidth(StandardResetButton->Caption));

	StandardUpButton->Width = ArrowButtonWidth;
	StandardUpButton->Height = ArrowButtonHeight;
	StandardUpButton->Top = StandardResetButton->Top;
	StandardUpButton->Enabled = false;
	StandardUpButton->NumGlyphs = NumGlyphs;
	StandardUpButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_UP));

	StandardDownButton->Width = ArrowButtonWidth;
	StandardDownButton->Height = ArrowButtonHeight;
	StandardDownButton->Top = StandardUpButton->Top;
	StandardDownButton->Enabled = false;
	StandardDownButton->NumGlyphs = NumGlyphs;
	StandardDownButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_DOWN));

	StandardDownButton->Left = StandardListBox->Left + StandardListBox->Width - ButtonRight - StandardDownButton->Width;
	StandardUpButton->Left = StandardDownButton->Left - StandardUpButton->Width;

	StandardGroupBox->Width = DetailedGroupBox->Width;
	StandardGroupBox->Height = StandardAddButton->Top + StandardAddButton->Height + ButtonBottom + PaddingBottom;
	StandardGroupBox->Left = DetailedGroupBox->Left;
	StandardGroupBox->Top = DetailedGroupBox->Top + DetailedGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	DIDDataListBox->Width = DetailedListBox->Width;
	DIDDataListBox->Height = DetailedListBox->Height + Scale + ButtonTop + DetailedAddButton->Height + ButtonBottom + PaddingBottom + GroupBoxBottom + GroupBoxTop + PaddingTop + CEADataListBox->Height;
	DIDDataListBox->ItemHeight = Text.tmHeight;
	DIDDataListBox->Left = PaddingWidth;
	DIDDataListBox->Top = PaddingTop;

	DIDDataAddButton->Width = ButtonWidth;
	DIDDataAddButton->Height = ButtonHeight;
	DIDDataAddButton->Left = DIDDataListBox->Left + ButtonLeft;
	DIDDataAddButton->Top = DIDDataListBox->Top + DIDDataListBox->Height + Scale + ButtonTop;
	FixButtonCaption(DIDDataAddButton, Canvas->TextWidth(DIDDataAddButton->Caption));

	DIDDataEditButton->Width = ButtonWidth;
	DIDDataEditButton->Height = ButtonHeight;
	DIDDataEditButton->Left = DIDDataAddButton->Left + DIDDataAddButton->Width;
	DIDDataEditButton->Top = DIDDataAddButton->Top;
	FixButtonCaption(DIDDataEditButton, Canvas->TextWidth(DIDDataEditButton->Caption));

	DIDDataDeleteButton->Width = ButtonWidth;
	DIDDataDeleteButton->Height = ButtonHeight;
	DIDDataDeleteButton->Left = DIDDataEditButton->Left + DIDDataEditButton->Width;
	DIDDataDeleteButton->Top = DIDDataEditButton->Top;
	FixButtonCaption(DIDDataDeleteButton, Canvas->TextWidth(DIDDataDeleteButton->Caption));

	DIDDataDeleteAllButton->Width = LongButtonWidth;
	DIDDataDeleteAllButton->Height = LongButtonHeight;
	DIDDataDeleteAllButton->Left = DIDDataDeleteButton->Left + DIDDataDeleteButton->Width;
	DIDDataDeleteAllButton->Top = DIDDataDeleteButton->Top;
	FixButtonCaption(DIDDataDeleteAllButton, Canvas->TextWidth(DIDDataDeleteAllButton->Caption));

	DIDDataResetButton->Width = ButtonWidth;
	DIDDataResetButton->Height = ButtonHeight;
	DIDDataResetButton->Left = DIDDataDeleteAllButton->Left + DIDDataDeleteAllButton->Width;
	DIDDataResetButton->Top = DIDDataDeleteAllButton->Top;
	FixButtonCaption(DIDDataResetButton, Canvas->TextWidth(DIDDataResetButton->Caption));

	DIDDataUpButton->Width = ArrowButtonWidth;
	DIDDataUpButton->Height = ArrowButtonHeight;
	DIDDataUpButton->Top = DIDDataResetButton->Top;
	DIDDataUpButton->Enabled = false;
	DIDDataUpButton->NumGlyphs = NumGlyphs;
	DIDDataUpButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_UP));

	DIDDataDownButton->Width = ArrowButtonWidth;
	DIDDataDownButton->Height = ArrowButtonHeight;
	DIDDataDownButton->Top = DIDDataUpButton->Top;
	DIDDataDownButton->Enabled = false;
	DIDDataDownButton->NumGlyphs = NumGlyphs;
	DIDDataDownButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_DOWN));

	DIDDataDownButton->Left = DIDDataListBox->Left + DIDDataListBox->Width - ButtonRight - DIDDataDownButton->Width;
	DIDDataUpButton->Left = DIDDataDownButton->Left - DIDDataUpButton->Width;

	DIDDataGroupBox->Width = DetailedGroupBox->Width;
	DIDDataGroupBox->Height = DIDDataAddButton->Top + DIDDataAddButton->Height + ButtonBottom + PaddingBottom;
	DIDDataGroupBox->Left = DetailedGroupBox->Left;
	DIDDataGroupBox->Top = DetailedGroupBox->Top;

	DefaultOutline->Width = DetailedGroupBox->Width;
	DefaultOutline->Height = GroupBoxTop + DetailedGroupBox->Height + GroupBoxBottom + GroupBoxTop + CEADataGroupBox->Height + GroupBoxBottom - Scale;
	DefaultOutline->Left = DetailedGroupBox->Left;
	DefaultOutline->Top = ExtensionTypeComboBox->Top + ExtensionTypeComboBox->Height + Scale;

	DefaultLabel->Font->Height = Font->Height * 2;
	DefaultLabel->Left = DefaultOutline->Left + (DefaultOutline->Width - DefaultLabel->Width) / 2;
	DefaultLabel->Top = DefaultOutline->Top + (DefaultOutline->Height - DefaultLabel->Height) / 2;

	ExtensionResetButton->Left = DetailedGroupBox->Left + DetailedGroupBox->Width - ButtonRight - ExtensionResetButton->Width;
	ExtensionPasteButton->Left = ExtensionResetButton->Left - ExtensionPasteButton->Width;
	ExtensionCopyButton->Left = ExtensionPasteButton->Left - ExtensionCopyButton->Width;
	ExtensionTypeComboBox->Width = ExtensionCopyButton->Left - ButtonLeft - Scale - ExtensionTypeComboBox->Left;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = CEADataGroupBox->Top + CEADataGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = CEADataGroupBox->Left + CEADataGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::FormShow(TObject *Sender)
{
	InitExtensionTypeComboBox();
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::ExtensionTypeComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	ExtensionBlock->SetType(ExtensionTypeComboBox->ItemIndex);
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::ExtensionCopyButtonClick(TObject *Sender)
{
	ExtensionBlock->ExtensionCopy();
	RefreshExtensionButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::ExtensionPasteButtonClick(TObject *Sender)
{
	ExtensionBlock->ExtensionPaste();
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::ExtensionResetButtonClick(TObject *Sender)
{
	ExtensionBlock->ExtensionReset();
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	ListBoxDrawItem(DetailedListBox, Rect, State, DetailedListBox->Items->Strings[Index].c_str(), ExtensionBlock->DetailedResolutions()->EditPossible(Index), false);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	DetailedLastClickedItemIndex = DetailedListBox->ItemIndex;

	if (DetailedListBox->ItemIndex == DetailedLastItemIndex)
		DetailedListBox->ItemIndex = -1;

	RefreshDetailedButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedListBoxDoubleClick(TObject *Sender)
{
	DetailedListBox->ItemIndex = DetailedLastClickedItemIndex;
	RefreshDetailedButtons();

	if (ExtensionBlock->DetailedResolutions()->EditPossible(DetailedListBox->ItemIndex))
		DetailedEditButtonClick(DetailedListBox);

	DetailedLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedListBoxSelect(TObject *Sender)
{
	RefreshDetailedButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedAddButtonClick(TObject *Sender)
{
	DetailedResolutionClass DetailedResolution;
	TDetailedResolutionForm *DetailedResolutionForm = new TDetailedResolutionForm(this);

	DetailedResolution = NativeResolution;
	DetailedResolutionForm->Connect(DetailedResolution);

	if (DetailedResolutionForm->ShowModal() == mrOk)
	{
		ExtensionBlock->DetailedResolutions()->Add(DetailedResolution);
		Refresh(DetailedGroupBox, ExtensionBlock->DetailedResolutions()->GetCount() - 1);
	}

	delete DetailedResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedEditButtonClick(TObject *Sender)
{
	DetailedResolutionClass DetailedResolution;
	TDetailedResolutionForm *DetailedResolutionForm = new TDetailedResolutionForm(this);

	ExtensionBlock->DetailedResolutions()->Get(DetailedListBox->ItemIndex, DetailedResolution);
	DetailedResolutionForm->Connect(DetailedResolution);

	if (DetailedResolutionForm->ShowModal() == mrOk)
	{
		ExtensionBlock->DetailedResolutions()->Set(DetailedListBox->ItemIndex, DetailedResolution);
		Refresh(DetailedGroupBox, DetailedListBox->ItemIndex);
	}

	delete DetailedResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedDeleteButtonClick(TObject *Sender)
{
	ExtensionBlock->DetailedResolutions()->Delete(DetailedListBox->ItemIndex);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedDeleteAllButtonClick(TObject *Sender)
{
	ExtensionBlock->DetailedResolutions()->DeleteAll();
	Refresh(DetailedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedResetButtonClick(TObject *Sender)
{
	ExtensionBlock->DetailedResolutions()->Undo();
	Refresh(DetailedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedUpButtonClick(TObject *Sender)
{
	ExtensionBlock->DetailedResolutions()->Exchange(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex - 1);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DetailedDownButtonClick(TObject *Sender)
{
	ExtensionBlock->DetailedResolutions()->Exchange(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex + 1);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	if (Index < ExtensionBlock->CEAData()->GetCount())
	{
		Column Columns[4];

		ExtensionBlock->CEAData()->GetSlotTypeText(Index, Columns[0].Text, TEXTSIZE);
		std::snprintf(Columns[1].Text, TEXTSIZE, "%d", ExtensionBlock->CEAData()->GetSlotSize(Index));
		std::snprintf(Columns[2].Text, TEXTSIZE, " byte%s", ExtensionBlock->CEAData()->GetSlotSize(Index) != 1 ? "s" : "");
		ExtensionBlock->CEAData()->GetSlotInfoText(Index, Columns[3].Text, TEXTSIZE);

		Columns[0].Width = Canvas->TextWidth("HDR dynamic metadata");
		Columns[1].Width = Canvas->TextWidth("999");
		Columns[2].Width = Canvas->TextWidth(" bytes");
		Columns[3].Width = CEADataListBox->Width / 3;

		Columns[2].Width += CEADataListBox->Width - Columns[0].Width - Columns[1].Width - Columns[2].Width - Columns[3].Width;

		Columns[0].Format = DT_LEFT;
		Columns[1].Format = DT_RIGHT;
		Columns[2].Format = DT_LEFT;
		Columns[3].Format = DT_LEFT;

		ListBoxDrawItems(CEADataListBox, Rect, State, Columns, 4, ExtensionBlock->CEAData()->EditPossible(Index), false);
		return;
	}

	ListBoxDrawItem(CEADataListBox, Rect, State, CEADataListBox->Items->Strings[Index].c_str(), false, false);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	CEADataLastClickedItemIndex = CEADataListBox->ItemIndex;

	if (CEADataListBox->ItemIndex == CEADataLastItemIndex)
		CEADataListBox->ItemIndex = -1;

	RefreshCEADataButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataListBoxDoubleClick(TObject *Sender)
{
	CEADataListBox->ItemIndex = CEADataLastClickedItemIndex;
	RefreshCEADataButtons();

	if (ExtensionBlock->CEAData()->EditPossible(CEADataListBox->ItemIndex))
		CEADataEditButtonClick(CEADataListBox);

	CEADataLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataListBoxSelect(TObject *Sender)
{
	RefreshCEADataButtons();
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddTVResolutions()
{
	TVResolutionListClass TVResolutionList;
	TTVResolutionListForm *TVResolutionListForm = new TTVResolutionListForm(this);

	TVResolutionList.SetMaxSize(ExtensionBlock->ExtensionGetBytesLeft() - 1);
	TVResolutionListForm->Connect(TVResolutionList);

	if (TVResolutionListForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(TVResolutionList);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete TVResolutionListForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditTVResolutions(int Slot)
{
	TVResolutionListClass TVResolutionList;
	TTVResolutionListForm *TVResolutionListForm = new TTVResolutionListForm(this);

	ExtensionBlock->CEAData()->Get(Slot, TVResolutionList);
	TVResolutionListForm->Connect(TVResolutionList);

	if (TVResolutionListForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, TVResolutionList);
		Refresh(CEADataGroupBox, Slot);
	}

	delete TVResolutionListForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddAudioFormats()
{
	AudioFormatListClass AudioFormatList;
	TAudioFormatListForm *AudioFormatListForm = new TAudioFormatListForm(this);

	AudioFormatList.SetMaxSize(ExtensionBlock->ExtensionGetBytesLeft() - 1);
	AudioFormatListForm->Connect(AudioFormatList);

	if (AudioFormatListForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(AudioFormatList);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete AudioFormatListForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditAudioFormats(int Slot)
{
	AudioFormatListClass AudioFormatList;
	TAudioFormatListForm *AudioFormatListForm = new TAudioFormatListForm(this);

	ExtensionBlock->CEAData()->Get(Slot, AudioFormatList);
	AudioFormatListForm->Connect(AudioFormatList);

	if (AudioFormatListForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, AudioFormatList);
		Refresh(CEADataGroupBox, Slot);
	}

	delete AudioFormatListForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddSpeakerSetup()
{
	SpeakerSetupClass SpeakerSetup;
	TSpeakerSetupForm *SpeakerSetupForm = new TSpeakerSetupForm(this);

	SpeakerSetupForm->Connect(SpeakerSetup);

	if (SpeakerSetupForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(SpeakerSetup);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete SpeakerSetupForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditSpeakerSetup(int Slot)
{
	SpeakerSetupClass SpeakerSetup;
	TSpeakerSetupForm *SpeakerSetupForm = new TSpeakerSetupForm(this);

	ExtensionBlock->CEAData()->Get(Slot, SpeakerSetup);
	SpeakerSetupForm->Connect(SpeakerSetup);

	if (SpeakerSetupForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, SpeakerSetup);
		Refresh(CEADataGroupBox, Slot);
	}

	delete SpeakerSetupForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddHDMISupport()
{
	HDMISupportClass HDMISupport(ExtensionBlock->ExtensionGetBytesLeft() - 1);
	ColorFormatListClass ColorFormatList;
	THDMISupportForm *HDMISupportForm = new THDMISupportForm(this);

	ColorFormatList.SetYCbCr422(true);
	ColorFormatList.SetYCbCr444(true);
	HDMISupportForm->Connect(HDMISupport, ColorFormatList);

	if (HDMISupportForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(HDMISupport);
		ExtensionBlock->ColorFormats()->Set(ColorFormatList);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete HDMISupportForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditHDMISupport(int Slot)
{
	HDMISupportClass HDMISupport;
	ColorFormatListClass ColorFormatList;
	THDMISupportForm *HDMISupportForm = new THDMISupportForm(this);

	ExtensionBlock->CEAData()->Get(Slot, HDMISupport);
	ExtensionBlock->ColorFormats()->Get(ColorFormatList);
	HDMISupportForm->Connect(HDMISupport, ColorFormatList);

	if (HDMISupportForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, HDMISupport);
		ExtensionBlock->ColorFormats()->Set(ColorFormatList);
		Refresh(CEADataGroupBox, Slot);
	}

	delete HDMISupportForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddHDMI2Support()
{
	HDMI2SupportClass HDMI2Support(ExtensionBlock->ExtensionGetBytesLeft() - 1);
	THDMI2SupportForm *HDMI2SupportForm = new THDMI2SupportForm(this);

	HDMI2SupportForm->Connect(HDMI2Support);

	if (HDMI2SupportForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(HDMI2Support);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete HDMI2SupportForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditHDMI2Support(int Slot)
{
	HDMI2SupportClass HDMI2Support;
	THDMI2SupportForm *HDMI2SupportForm = new THDMI2SupportForm(this);

	ExtensionBlock->CEAData()->Get(Slot, HDMI2Support);
	HDMI2SupportForm->Connect(HDMI2Support);

	if (HDMI2SupportForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, HDMI2Support);
		Refresh(CEADataGroupBox, Slot);
	}

	delete HDMI2SupportForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddFreeSyncRange()
{
	FreeSyncRangeClass FreeSyncRange;
	TFreeSyncRangeForm *FreeSyncRangeForm = new TFreeSyncRangeForm(this);

	FreeSyncRangeForm->Connect(FreeSyncRange);

	if (FreeSyncRangeForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(FreeSyncRange);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete FreeSyncRangeForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditFreeSyncRange(int Slot)
{
	FreeSyncRangeClass FreeSyncRange;
	TFreeSyncRangeForm *FreeSyncRangeForm = new TFreeSyncRangeForm(this);

	ExtensionBlock->CEAData()->Get(Slot, FreeSyncRange);
	FreeSyncRangeForm->Connect(FreeSyncRange);

	if (FreeSyncRangeForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, FreeSyncRange);
		Refresh(CEADataGroupBox, Slot);
	}

	delete FreeSyncRangeForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddColorimetry()
{
	ColorimetryClass Colorimetry;
	TColorimetryForm *ColorimetryForm = new TColorimetryForm(this);

	ColorimetryForm->Connect(Colorimetry);

	if (ColorimetryForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(Colorimetry);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete ColorimetryForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditColorimetry(int Slot)
{
	ColorimetryClass Colorimetry;
	TColorimetryForm *ColorimetryForm = new TColorimetryForm(this);

	ExtensionBlock->CEAData()->Get(Slot, Colorimetry);
	ColorimetryForm->Connect(Colorimetry);

	if (ColorimetryForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, Colorimetry);
		Refresh(CEADataGroupBox, Slot);
	}

	delete ColorimetryForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddVideoCapability()
{
	VideoCapabilityClass VideoCapability;
	TVideoCapabilityForm *VideoCapabilityForm = new TVideoCapabilityForm(this);

	VideoCapabilityForm->Connect(VideoCapability);

	if (VideoCapabilityForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(VideoCapability);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete VideoCapabilityForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditVideoCapability(int Slot)
{
	VideoCapabilityClass VideoCapability;
	TVideoCapabilityForm *VideoCapabilityForm = new TVideoCapabilityForm(this);

	ExtensionBlock->CEAData()->Get(Slot, VideoCapability);
	VideoCapabilityForm->Connect(VideoCapability);

	if (VideoCapabilityForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, VideoCapability);
		Refresh(CEADataGroupBox, Slot);
	}

	delete VideoCapabilityForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAddHDRStaticMetadata()
{
	HDRStaticMetadataClass HDRStaticMetadata(ExtensionBlock->ExtensionGetBytesLeft() - 1);
	THDRStaticMetadataForm *HDRStaticMetadataForm = new THDRStaticMetadataForm(this);

	HDRStaticMetadataForm->Connect(HDRStaticMetadata);

	if (HDRStaticMetadataForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Add(HDRStaticMetadata);
		Refresh(CEADataGroupBox, ExtensionBlock->CEAData()->GetCount() - 1);
	}

	delete HDRStaticMetadataForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEditHDRStaticMetadata(int Slot)
{
	HDRStaticMetadataClass HDRStaticMetadata;
	THDRStaticMetadataForm *HDRStaticMetadataForm = new THDRStaticMetadataForm(this);

	ExtensionBlock->CEAData()->Get(Slot, HDRStaticMetadata);
	HDRStaticMetadataForm->Connect(HDRStaticMetadata);

	if (HDRStaticMetadataForm->ShowModal() == mrOk)
	{
		ExtensionBlock->CEAData()->Set(Slot, HDRStaticMetadata);
		Refresh(CEADataGroupBox, Slot);
	}

	delete HDRStaticMetadataForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataAdd(int Type)
{
	switch (Type)
	{
		case ADD_CEA_VIDEO:
			return CEADataAddTVResolutions();

		case ADD_CEA_AUDIO:
			return CEADataAddAudioFormats();

		case ADD_CEA_SPEAKER_ALLOCATION:
			return CEADataAddSpeakerSetup();

		case ADD_CEA_HDMI:
			return CEADataAddHDMISupport();

		case ADD_CEA_HDMI2:
			return CEADataAddHDMI2Support();

		case ADD_CEA_FREESYNC:
			return CEADataAddFreeSyncRange();

		case ADD_CEA_COLORIMETRY:
			return CEADataAddColorimetry();

		case ADD_CEA_VIDEO_CAPABILITY:
			return CEADataAddVideoCapability();

		case ADD_CEA_HDR_STATIC:
			return CEADataAddHDRStaticMetadata();
	}

	return false;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::CEADataEdit(int Slot)
{
	switch (ExtensionBlock->CEAData()->GetSlotType(Slot))
	{
		case CEA_VIDEO:
		case CEA_YCC420_VIDEO:
			return CEADataEditTVResolutions(Slot);

		case CEA_AUDIO:
			return CEADataEditAudioFormats(Slot);

		case CEA_SPEAKER_ALLOCATION:
			return CEADataEditSpeakerSetup(Slot);

		case CEA_HDMI:
			return CEADataEditHDMISupport(Slot);

		case CEA_HDMI2:
		case CEA_HDMI21:
			return CEADataEditHDMI2Support(Slot);

		case CEA_FREESYNC:
			return CEADataEditFreeSyncRange(Slot);

		case CEA_COLORIMETRY:
			return CEADataEditColorimetry(Slot);

		case CEA_VIDEO_CAPABILITY:
			return CEADataEditVideoCapability(Slot);

		case CEA_HDR_STATIC_METADATA:
			return CEADataEditHDRStaticMetadata(Slot);
	}

	return false;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataAddButtonClick(TObject *Sender)
{
	AddCEADataClass AddCEAData;
	TAddCEADataForm *AddCEADataForm = new TAddCEADataForm(this);

	AddCEAData.SetMaxSize(ExtensionBlock->ExtensionGetBytesLeft());
	AddCEADataForm->Connect(AddCEAData);

	if (AddCEADataForm->ShowModal() == mrOk)
		CEADataAdd(AddCEAData.GetType());

	delete AddCEADataForm;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataEditButtonClick(TObject *Sender)
{
	CEADataEdit(CEADataListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataDeleteButtonClick(TObject *Sender)
{
	ExtensionBlock->CEAData()->Delete(CEADataListBox->ItemIndex);

	if (!ExtensionBlock->CEAData()->HDMISupported())
	{
		ExtensionBlock->ColorFormats()->SetYCbCr422(false);
		ExtensionBlock->ColorFormats()->SetYCbCr444(false);
	}

	Refresh(CEADataGroupBox, CEADataListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataDeleteAllButtonClick(TObject *Sender)
{
	ExtensionBlock->CEAData()->DeleteAll();
	ExtensionBlock->ColorFormats()->SetYCbCr422(false);
	ExtensionBlock->ColorFormats()->SetYCbCr444(false);
	Refresh(CEADataGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataResetButtonClick(TObject *Sender)
{
	ExtensionBlock->CEAData()->Undo();
	ExtensionBlock->ColorFormats()->Undo();
	Refresh(CEADataGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataUpButtonClick(TObject *Sender)
{
	ExtensionBlock->CEAData()->Exchange(CEADataListBox->ItemIndex, CEADataListBox->ItemIndex - 1);
	Refresh(CEADataGroupBox, CEADataListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::CEADataDownButtonClick(TObject *Sender)
{
	ExtensionBlock->CEAData()->Exchange(CEADataListBox->ItemIndex, CEADataListBox->ItemIndex + 1);
	Refresh(CEADataGroupBox, CEADataListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	StandardResolutionClass StandardResolution;
	bool Supported = false;

	if (ExtensionBlock->StandardResolutions()->Get(Index, StandardResolution))
		Supported = StandardResolution.IsSupported();

	ListBoxDrawItem(StandardListBox, Rect, State, StandardListBox->Items->Strings[Index].c_str(), Supported, false);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	StandardLastClickedItemIndex = StandardListBox->ItemIndex;

	if (StandardListBox->ItemIndex == StandardLastItemIndex)
		StandardListBox->ItemIndex = -1;

	RefreshStandardButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardListBoxDoubleClick(TObject *Sender)
{
	StandardListBox->ItemIndex = StandardLastClickedItemIndex;
	RefreshStandardButtons();

	if (ExtensionBlock->StandardResolutions()->EditPossible(StandardListBox->ItemIndex))
		StandardEditButtonClick(StandardListBox);

	StandardLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardListBoxSelect(TObject *Sender)
{
	RefreshStandardButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardAddButtonClick(TObject *Sender)
{
	StandardResolutionClass StandardResolution;
	TStandardResolutionForm *StandardResolutionForm = new TStandardResolutionForm(this);

	StandardResolutionForm->Connect(StandardResolution);

	if (StandardResolutionForm->ShowModal() == mrOk)
	{
		ExtensionBlock->StandardResolutions()->Add(StandardResolution);
		Refresh(StandardGroupBox, ExtensionBlock->StandardResolutions()->GetCount() - 1);
	}

	delete StandardResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardEditButtonClick(TObject *Sender)
{
	StandardResolutionClass StandardResolution;
	TStandardResolutionForm *StandardResolutionForm = new TStandardResolutionForm(this);

	ExtensionBlock->StandardResolutions()->Get(StandardListBox->ItemIndex, StandardResolution);
	StandardResolutionForm->Connect(StandardResolution);

	if (StandardResolutionForm->ShowModal() == mrOk)
	{
		ExtensionBlock->StandardResolutions()->Set(StandardListBox->ItemIndex, StandardResolution);
		Refresh(StandardGroupBox, StandardListBox->ItemIndex);
	}

	delete StandardResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardDeleteButtonClick(TObject *Sender)
{
	ExtensionBlock->StandardResolutions()->Delete(StandardListBox->ItemIndex);
	Refresh(StandardGroupBox, StandardListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardDeleteAllButtonClick(TObject *Sender)
{
	ExtensionBlock->StandardResolutions()->DeleteAll();
	Refresh(StandardGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardResetButtonClick(TObject *Sender)
{
	ExtensionBlock->StandardResolutions()->Undo();
	Refresh(StandardGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardUpButtonClick(TObject *Sender)
{
	ExtensionBlock->StandardResolutions()->Exchange(StandardListBox->ItemIndex, StandardListBox->ItemIndex - 1);
	Refresh(StandardGroupBox, StandardListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::StandardDownButtonClick(TObject *Sender)
{
	ExtensionBlock->StandardResolutions()->Exchange(StandardListBox->ItemIndex, StandardListBox->ItemIndex + 1);
	Refresh(StandardGroupBox, StandardListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	if (Index < ExtensionBlock->DIDData()->GetCount())
	{
		Column Columns[4];

		ExtensionBlock->DIDData()->GetSlotTypeText(Index, Columns[0].Text, TEXTSIZE);
		std::snprintf(Columns[1].Text, TEXTSIZE, "%d", ExtensionBlock->DIDData()->GetSlotSize(Index));
		std::snprintf(Columns[2].Text, TEXTSIZE, " byte%s", ExtensionBlock->DIDData()->GetSlotSize(Index) != 1 ? "s" : "");
		ExtensionBlock->DIDData()->GetSlotInfoText(Index, Columns[3].Text, TEXTSIZE);

		Columns[0].Width = Canvas->TextWidth("Tiled display topology (9.x)");
		Columns[1].Width = Canvas->TextWidth("999");
		Columns[2].Width = Canvas->TextWidth(" bytes");
		Columns[3].Width = DIDDataListBox->Width / 3;

		Columns[2].Width += DIDDataListBox->Width - Columns[0].Width - Columns[1].Width - Columns[2].Width - Columns[3].Width;

		Columns[0].Format = DT_LEFT;
		Columns[1].Format = DT_RIGHT;
		Columns[2].Format = DT_LEFT;
		Columns[3].Format = DT_LEFT;

		ListBoxDrawItems(DIDDataListBox, Rect, State, Columns, 4, ExtensionBlock->DIDData()->EditPossible(Index), false);
		return;
	}

	ListBoxDrawItem(DIDDataListBox, Rect, State, DIDDataListBox->Items->Strings[Index].c_str(), false, false);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	DIDDataLastClickedItemIndex = DIDDataListBox->ItemIndex;

	if (DIDDataListBox->ItemIndex == DIDDataLastItemIndex)
		DIDDataListBox->ItemIndex = -1;

	RefreshDIDDataButtons();
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataListBoxDoubleClick(TObject *Sender)
{
	DIDDataListBox->ItemIndex = DIDDataLastClickedItemIndex;
	RefreshDIDDataButtons();

	if (ExtensionBlock->DIDData()->EditPossible(DIDDataListBox->ItemIndex))
		DIDDataEditButtonClick(DIDDataListBox);

	DIDDataLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataListBoxSelect(TObject *Sender)
{
	RefreshDIDDataButtons();
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::DIDDataAddDetailedResolutions(int Type)
{
	DIDDetailedResolutionListClass DIDDetailedResolutionList(Type);
	TDIDDetailedResolutionListForm *DIDDetailedResolutionListForm = new TDIDDetailedResolutionListForm(this);

	DIDDetailedResolutionList.SetMaxSize(ExtensionBlock->ExtensionGetBytesLeft() - 3);
	DIDDetailedResolutionListForm->Connect(DIDDetailedResolutionList, NativeResolution);

	if (DIDDetailedResolutionListForm->ShowModal() == mrOk)
	{
		ExtensionBlock->DIDData()->Add(DIDDetailedResolutionList);
		Refresh(DIDDataGroupBox, ExtensionBlock->DIDData()->GetCount() - 1);
	}

	delete DIDDetailedResolutionListForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::DIDDataEditDetailedResolutions(int Type, int Slot)
{
	DIDDetailedResolutionListClass DIDDetailedResolutionList(Type);
	TDIDDetailedResolutionListForm *DIDDetailedResolutionListForm = new TDIDDetailedResolutionListForm(this);

	ExtensionBlock->DIDData()->Get(Slot, DIDDetailedResolutionList);
	DIDDetailedResolutionListForm->Connect(DIDDetailedResolutionList, NativeResolution);

	if (DIDDetailedResolutionListForm->ShowModal() == mrOk)
	{
		ExtensionBlock->DIDData()->Set(Slot, DIDDetailedResolutionList);
		Refresh(DIDDataGroupBox, Slot);
	}

	delete DIDDetailedResolutionListForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::DIDDataAddTiledDisplayTopology(int Version)
{
	TiledDisplayTopologyClass TiledDisplayTopology(Version);
	TTiledDisplayTopologyForm *TiledDisplayTopologyForm = new TTiledDisplayTopologyForm(this);

	char DeviceID[TEXTSIZE];
	Properties.GetDeviceID(DeviceID, TEXTSIZE);
	TiledDisplayTopology.SetDeviceID(DeviceID);
	TiledDisplayTopology.SetSerialID(Properties.GetSerialID());
	TiledDisplayTopology.SetHSize(NativeResolution.GetHActive());
	TiledDisplayTopology.SetVSize(NativeResolution.GetVActive());
	TiledDisplayTopologyForm->Connect(TiledDisplayTopology);

	if (TiledDisplayTopologyForm->ShowModal() == mrOk)
	{
		ExtensionBlock->DIDData()->Add(TiledDisplayTopology);
		Refresh(DIDDataGroupBox, ExtensionBlock->DIDData()->GetCount() - 1);
	}

	delete TiledDisplayTopologyForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::DIDDataEditTiledDisplayTopology(int Version, int Slot)
{
	TiledDisplayTopologyClass TiledDisplayTopology(Version);
	TTiledDisplayTopologyForm *TiledDisplayTopologyForm = new TTiledDisplayTopologyForm(this);

	ExtensionBlock->DIDData()->Get(Slot, TiledDisplayTopology);
	TiledDisplayTopologyForm->Connect(TiledDisplayTopology);

	if (TiledDisplayTopologyForm->ShowModal() == mrOk)
	{
		ExtensionBlock->DIDData()->Set(Slot, TiledDisplayTopology);
		Refresh(DIDDataGroupBox, Slot);
	}

	delete TiledDisplayTopologyForm;
	return true;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::DIDDataAdd(int Type)
{
	switch (ExtensionBlock->GetType())
	{
		case DISPLAYID_EXT:
			switch (Type)
			{
				case ADD_DID_DETAILED_RESOLUTIONS:
					return DIDDataAddDetailedResolutions(1);

				case ADD_DID_TILED_DISPLAY_TOPOLOGY:
					return DIDDataAddTiledDisplayTopology(1);
			}

			break;

		case DISPLAYID2_EXT:
			switch (Type)
			{
				case ADD_DID_DETAILED_RESOLUTIONS:
					return DIDDataAddDetailedResolutions(7);

				case ADD_DID_TILED_DISPLAY_TOPOLOGY:
					return DIDDataAddTiledDisplayTopology(2);
			}

			break;
	}

	return false;
}
//---------------------------------------------------------------------------
bool TExtensionBlockForm::DIDDataEdit(int Slot)
{
	switch (ExtensionBlock->DIDData()->GetSlotType(Slot))
	{
		case DID_DETAILED_RESOLUTIONS:
			return DIDDataEditDetailedResolutions(1, Slot);

		case DID_TILED_DISPLAY_TOPOLOGY:
			return DIDDataEditTiledDisplayTopology(1, Slot);

		case DID2_DETAILED_RESOLUTIONS:
			return DIDDataEditDetailedResolutions(7, Slot);

		case DID2_TILED_DISPLAY_TOPOLOGY:
			return DIDDataEditTiledDisplayTopology(2, Slot);
	}

	return false;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataAddButtonClick(TObject *Sender)
{
	AddDIDDataClass AddDIDData;
	TAddDIDDataForm *AddDIDDataForm = new TAddDIDDataForm(this);

	AddDIDData.SetMaxSize(ExtensionBlock->ExtensionGetBytesLeft());
	AddDIDDataForm->Connect(AddDIDData);

	if (AddDIDDataForm->ShowModal() == mrOk)
		DIDDataAdd(AddDIDData.GetType());

	delete AddDIDDataForm;
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataEditButtonClick(TObject *Sender)
{
	DIDDataEdit(DIDDataListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataDeleteButtonClick(TObject *Sender)
{
	ExtensionBlock->DIDData()->Delete(DIDDataListBox->ItemIndex);
	Refresh(DIDDataGroupBox, DIDDataListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataDeleteAllButtonClick(TObject *Sender)
{
	ExtensionBlock->DIDData()->DeleteAll();
	Refresh(DIDDataGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataResetButtonClick(TObject *Sender)
{
	ExtensionBlock->DIDData()->Undo();
	Refresh(DIDDataGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataUpButtonClick(TObject *Sender)
{
	ExtensionBlock->DIDData()->Exchange(DIDDataListBox->ItemIndex, DIDDataListBox->ItemIndex - 1);
	Refresh(DIDDataGroupBox, DIDDataListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TExtensionBlockForm::DIDDataDownButtonClick(TObject *Sender)
{
	ExtensionBlock->DIDData()->Exchange(DIDDataListBox->ItemIndex, DIDDataListBox->ItemIndex + 1);
	Refresh(DIDDataGroupBox, DIDDataListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
