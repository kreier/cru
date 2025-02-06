//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "DisplayFormClass.h"
#include "PropertiesFormClass.h"
#include "DetailedResolutionFormClass.h"
#include "StandardResolutionFormClass.h"
#include "ExtensionBlockFormClass.h"
#include "VistaAltFixUnit.hpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDisplayForm *DisplayForm;
//---------------------------------------------------------------------------
__fastcall TDisplayForm::TDisplayForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
	DetailedLastItemIndex = -1;
	DetailedLastClickedItemIndex = -1;
	StandardLastItemIndex = -1;
	StandardLastClickedItemIndex = -1;
	ExtensionLastItemIndex = -1;
	ExtensionLastClickedItemIndex = -1;
	new TVistaAltFix(this);
}
//---------------------------------------------------------------------------
void TDisplayForm::FatalError(const char *Message)
{
	Application->MessageBox(Message, "Error", MB_ICONERROR);
	exit(1);
}
//---------------------------------------------------------------------------
bool TDisplayForm::Refresh(void *Value, int ItemIndex)
{
	Refreshing = true;
	RefreshDisplayButtons();

	if (Value == NULL || Value == EstablishedGroupBox)
	{
		RefreshEstablishedCheckBoxes();
		RefreshEstablishedButtons();
	}

	if (Value == NULL || Value == DetailedGroupBox)
	{
		RefreshDetailedCaption();
		RefreshDetailedListBox(ItemIndex);
		RefreshDetailedButtons();
		RefreshStandardCaption();
		RefreshStandardButtons();
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

	if (Value == NULL || Value == ExtensionGroupBox)
	{
		RefreshExtensionCaption();
		RefreshExtensionListBox(ItemIndex);
		RefreshExtensionButtons();
	}

	if (Value == NULL)
		RefreshImportExportButtons();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshDisplayComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = DisplayComboBox->ItemIndex;
	DisplayComboBox->Items->BeginUpdate();
	DisplayComboBox->Clear();

	for (Index = 0; DisplayList.GetItemText(Index, Text, TEXTSIZE); Index++)
		DisplayComboBox->Items->Add(Text);

	DisplayComboBox->ItemIndex = ItemIndex;
	DisplayComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshDisplayButtons()
{
	if (Display->DisplayDeletePossible())
	{
		DisplayEditButton->Enabled = true;
		DisplayCopyButton->Enabled = Display->DisplayCopyPossible();
		DisplayPasteButton->Enabled = Display->DisplayPastePossible();
		DisplayDeleteButton->Caption = "Delete";
	}
	else
	{
		DisplayEditButton->Enabled = false;
		DisplayCopyButton->Enabled = false;
		DisplayPasteButton->Enabled = false;
		DisplayDeleteButton->Caption = "Keep";
	}

	FixButtonCaption(DisplayDeleteButton, Canvas->TextWidth(DisplayDeleteButton->Caption));
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshEstablishedCheckBoxes()
{
	if (Display->DisplayDeletePossible())
	{
		EstablishedLabel1->Font->Color = clWindowText;
		EstablishedLabel2->Font->Color = clWindowText;
		EstablishedLabel3->Font->Color = clWindowText;
		EstablishedLabel4->Font->Color = clWindowText;

		EstablishedCheckBox2->Enabled = true;
		EstablishedCheckBox4->Enabled = true;
		EstablishedCheckBox5->Enabled = true;
		EstablishedCheckBox6->Enabled = true;
		EstablishedCheckBox7->Enabled = true;
		EstablishedCheckBox8->Enabled = true;
		EstablishedCheckBox9->Enabled = true;
		EstablishedCheckBox12->Enabled = true;
		EstablishedCheckBox13->Enabled = true;
		EstablishedCheckBox14->Enabled = true;
		EstablishedCheckBox15->Enabled = true;

		EstablishedCheckBox2->Checked = Display->EstablishedResolutions()->Get(2);
		EstablishedCheckBox4->Checked = Display->EstablishedResolutions()->Get(4);
		EstablishedCheckBox5->Checked = Display->EstablishedResolutions()->Get(5);
		EstablishedCheckBox6->Checked = Display->EstablishedResolutions()->Get(6);
		EstablishedCheckBox7->Checked = Display->EstablishedResolutions()->Get(7);
		EstablishedCheckBox8->Checked = Display->EstablishedResolutions()->Get(8);
		EstablishedCheckBox9->Checked = Display->EstablishedResolutions()->Get(9);
		EstablishedCheckBox12->Checked = Display->EstablishedResolutions()->Get(12);
		EstablishedCheckBox13->Checked = Display->EstablishedResolutions()->Get(13);
		EstablishedCheckBox14->Checked = Display->EstablishedResolutions()->Get(14);
		EstablishedCheckBox15->Checked = Display->EstablishedResolutions()->Get(15);
	}
	else
	{
		EstablishedLabel1->Font->Color = clGrayText;
		EstablishedLabel2->Font->Color = clGrayText;
		EstablishedLabel3->Font->Color = clGrayText;
		EstablishedLabel4->Font->Color = clGrayText;

		EstablishedCheckBox2->Enabled = false;
		EstablishedCheckBox4->Enabled = false;
		EstablishedCheckBox5->Enabled = false;
		EstablishedCheckBox6->Enabled = false;
		EstablishedCheckBox7->Enabled = false;
		EstablishedCheckBox8->Enabled = false;
		EstablishedCheckBox9->Enabled = false;
		EstablishedCheckBox12->Enabled = false;
		EstablishedCheckBox13->Enabled = false;
		EstablishedCheckBox14->Enabled = false;
		EstablishedCheckBox15->Enabled = false;

		EstablishedCheckBox2->Checked = false;
		EstablishedCheckBox4->Checked = false;
		EstablishedCheckBox5->Checked = false;
		EstablishedCheckBox6->Checked = false;
		EstablishedCheckBox7->Checked = false;
		EstablishedCheckBox8->Checked = false;
		EstablishedCheckBox9->Checked = false;
		EstablishedCheckBox12->Checked = false;
		EstablishedCheckBox13->Checked = false;
		EstablishedCheckBox14->Checked = false;
		EstablishedCheckBox15->Checked = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshEstablishedButtons()
{
	if (Display->DisplayDeletePossible())
	{
		EstablishedAllButton->Enabled = Display->EstablishedResolutions()->AllPossible();
		EstablishedNoneButton->Enabled = Display->EstablishedResolutions()->NonePossible();
		EstablishedResetButton->Enabled = Display->EstablishedResolutions()->UndoPossible();
	}
	else
	{
		EstablishedAllButton->Enabled = false;
		EstablishedNoneButton->Enabled = false;
		EstablishedResetButton->Enabled = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshDetailedCaption()
{
	const char *Caption = " Detailed resolutions ";
	char Text[TEXTSIZE];

	if (Display->DisplayDeletePossible())
	{
		Display->DetailedResolutions()->GetSlotsLeftText(Caption, Text, TEXTSIZE);
		DetailedGroupBox->Caption = Text;
		return true;
	}

	DetailedGroupBox->Caption = Caption;
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshDetailedListBox(int ItemIndex)
{
	int Index;
	char Text[TEXTSIZE];

	if (Display->DisplayDeletePossible())
	{
		if (Display->DetailedResolutions()->GetMaxCount() > 0)
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
	}
	else
	{
		DetailedListBox->Enabled = false;
		DetailedListBox->Color = clBtnFace;
		DetailedListBox->Font->Color = clGrayText;
		DetailedListBox->Clear();
		return true;
	}

	int TopIndex = DetailedListBox->TopIndex;
	DetailedListBox->Items->BeginUpdate();
	DetailedListBox->Clear();
	DetailedResolutionClass DetailedResolution;

	for (Index = 0; Display->DetailedResolutions()->Get(Index, DetailedResolution); Index++)
		if (DetailedResolution.GetText(Text, TEXTSIZE, Dash()))
			DetailedListBox->Items->Add(Text);

	if (Index == 0 && Display->DetailedResolutions()->GetMaxCount() > Display->Properties()->GetCount())
		DetailedListBox->Items->Add("No detailed resolutions");

	for (Index = 0; Display->DetailedGetStandardText(Index, Text, TEXTSIZE); Index++)
		DetailedListBox->Items->Add(Text);

	for (Index = 0; Index < 4 && DetailedListBox->Count < 4; Index++)
		if (Display->Properties()->GetText(Index, Text, TEXTSIZE))
			DetailedListBox->Items->Add(Text);

	if (ItemIndex > 0)
		DetailedListBox->TopIndex = TopIndex;

	if (ItemIndex < Display->DetailedResolutions()->GetCount())
		DetailedListBox->ItemIndex = ItemIndex;

	DetailedListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshDetailedButtons()
{
	if (Display->DisplayDeletePossible())
	{
		DetailedLastItemIndex = DetailedListBox->ItemIndex;
		DetailedAddButton->Enabled = Display->DetailedResolutions()->AddPossible();
		DetailedEditButton->Enabled = Display->DetailedResolutions()->EditPossible(DetailedListBox->ItemIndex);
		DetailedDeleteButton->Enabled = Display->DetailedResolutions()->DeletePossible(DetailedListBox->ItemIndex);
		DetailedDeleteAllButton->Enabled = Display->DetailedResolutions()->DeleteAllPossible();
		DetailedResetButton->Enabled = Display->DetailedResolutions()->UndoPossible();
		DetailedUpButton->Enabled = Display->DetailedResolutions()->ExchangePossible(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex - 1);
		DetailedDownButton->Enabled = Display->DetailedResolutions()->ExchangePossible(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex + 1);
	}
	else
	{
		DetailedAddButton->Enabled = false;
		DetailedEditButton->Enabled = false;
		DetailedDeleteButton->Enabled = false;
		DetailedDeleteAllButton->Enabled = false;
		DetailedResetButton->Enabled = false;
		DetailedUpButton->Enabled = false;
		DetailedDownButton->Enabled = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshStandardCaption()
{
	const char *Caption = " Standard resolutions ";
	char Text[TEXTSIZE];

	if (Display->DisplayDeletePossible())
	{
		Display->StandardResolutions()->GetSlotsLeftText(Caption, Text, TEXTSIZE);
		StandardGroupBox->Caption = Text;
		return true;
	}

	StandardGroupBox->Caption = Caption;
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshStandardListBox(int ItemIndex)
{
	int Index;
	char Text[TEXTSIZE];

	if (Display->DisplayDeletePossible())
	{
		StandardListBox->Enabled = true;
		StandardListBox->Color = clWindow;
		StandardListBox->Font->Color = clWindowText;
	}
	else
	{
		StandardListBox->Enabled = false;
		StandardListBox->Color = clBtnFace;
		StandardListBox->Font->Color = clGrayText;
		StandardListBox->Clear();
		return true;
	}

	int TopIndex = StandardListBox->TopIndex;

	if (Display->StandardResolutions()->GetCount() <= StandardRows * StandardListBox->Columns)
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

	for (Index = 0; Display->StandardResolutions()->Get(Index, StandardResolution); Index++)
		if (StandardResolution.GetText(Text, TEXTSIZE))
			StandardListBox->Items->Add(Text);

	if (Index == 0)
		StandardListBox->Items->Add("No standard resolutions");

	if (ItemIndex > 0)
		StandardListBox->TopIndex = TopIndex;

	if (ItemIndex < Display->StandardResolutions()->GetCount())
		StandardListBox->ItemIndex = ItemIndex;

	StandardListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshStandardButtons()
{
	if (Display->DisplayDeletePossible())
	{
		StandardLastItemIndex = StandardListBox->ItemIndex;
		StandardAddButton->Enabled = Display->StandardResolutions()->AddPossible();
		StandardEditButton->Enabled = Display->StandardResolutions()->EditPossible(StandardListBox->ItemIndex);
		StandardDeleteButton->Enabled = Display->StandardResolutions()->DeletePossible(StandardListBox->ItemIndex);
		StandardDeleteAllButton->Enabled = Display->StandardResolutions()->DeleteAllPossible();
		StandardResetButton->Enabled = Display->StandardResolutions()->UndoPossible();
		StandardUpButton->Enabled = Display->StandardResolutions()->ExchangePossible(StandardListBox->ItemIndex, StandardListBox->ItemIndex - 1);
		StandardDownButton->Enabled = Display->StandardResolutions()->ExchangePossible(StandardListBox->ItemIndex, StandardListBox->ItemIndex + 1);
	}
	else
	{
		StandardAddButton->Enabled = false;
		StandardEditButton->Enabled = false;
		StandardDeleteButton->Enabled = false;
		StandardDeleteAllButton->Enabled = false;
		StandardResetButton->Enabled = false;
		StandardUpButton->Enabled = false;
		StandardDownButton->Enabled = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshExtensionCaption()
{
	const char *Caption = " Extension blocks ";
	char Text[TEXTSIZE];

	if (Display->DisplayDeletePossible())
	{
		Display->ExtensionBlocks()->GetSlotsLeftText(Caption, Text, TEXTSIZE);
		ExtensionGroupBox->Caption = Text;
		return true;
	}

	ExtensionGroupBox->Caption = Caption;
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshExtensionListBox(int ItemIndex)
{
	int Index;
	char Text[TEXTSIZE];

	if (Display->DisplayDeletePossible())
	{
		ExtensionListBox->Enabled = true;
		ExtensionListBox->Color = clWindow;
		ExtensionListBox->Font->Color = clWindowText;
	}
	else
	{
		ExtensionListBox->Enabled = false;
		ExtensionListBox->Color = clBtnFace;
		ExtensionListBox->Font->Color = clGrayText;
		ExtensionListBox->Clear();
		return true;
	}

	int TopIndex = ExtensionListBox->TopIndex;
	ExtensionListBox->Items->BeginUpdate();
	ExtensionListBox->Clear();
	ExtensionBlockClass ExtensionBlock;

	for (Index = 0; Display->ExtensionBlocks()->Get(Index, ExtensionBlock); Index++)
		if (ExtensionBlock.GetText(Text, TEXTSIZE))
			ExtensionListBox->Items->Add(Text);

	if (Index == 0)
		ExtensionListBox->Items->Add("No extension blocks");

	if (ItemIndex > 0)
		ExtensionListBox->TopIndex = TopIndex;

	if (ItemIndex < Display->ExtensionBlocks()->GetCount())
		ExtensionListBox->ItemIndex = ItemIndex;

	ExtensionListBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshExtensionButtons()
{
	if (Display->DisplayDeletePossible())
	{
		ExtensionLastItemIndex = ExtensionListBox->ItemIndex;
		ExtensionAddButton->Enabled = Display->ExtensionBlocks()->AddPossible();
		ExtensionEditButton->Enabled = Display->ExtensionBlocks()->EditPossible(ExtensionListBox->ItemIndex);
		ExtensionDeleteButton->Enabled = Display->ExtensionBlocks()->DeletePossible(ExtensionListBox->ItemIndex);
		ExtensionDeleteAllButton->Enabled = Display->ExtensionBlocks()->DeleteAllPossible();
		ExtensionResetButton->Enabled = Display->ExtensionBlocks()->UndoPossible();
		ExtensionUpButton->Enabled = Display->ExtensionBlocks()->ExchangePossible(ExtensionListBox->ItemIndex, ExtensionListBox->ItemIndex - 1);
		ExtensionDownButton->Enabled = Display->ExtensionBlocks()->ExchangePossible(ExtensionListBox->ItemIndex, ExtensionListBox->ItemIndex + 1);
	}
	else
	{
		ExtensionAddButton->Enabled = false;
		ExtensionEditButton->Enabled = false;
		ExtensionDeleteButton->Enabled = false;
		ExtensionDeleteAllButton->Enabled = false;
		ExtensionResetButton->Enabled = false;
		ExtensionUpButton->Enabled = false;
		ExtensionDownButton->Enabled = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::RefreshImportExportButtons()
{
	if (Display->DisplayDeletePossible())
	{
		DisplayImportButton->Enabled = true;
		DisplayExportButton->Enabled = true;
	}
	else
	{
		DisplayImportButton->Enabled = false;
		DisplayExportButton->Enabled = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool TDisplayForm::ScaleControls()
{
	TEXTMETRIC Label;

	EstablishedLabel1->Font->Height = -Text.tmAscent;
	EstablishedLabel2->Font->Height = -Text.tmAscent;
	EstablishedLabel3->Font->Height = -Text.tmAscent;
	EstablishedLabel4->Font->Height = -Text.tmAscent;
	EstablishedLabel1->Canvas->Font->Height = -Text.tmAscent;
	EstablishedLabel2->Canvas->Font->Height = -Text.tmAscent;
	EstablishedLabel3->Canvas->Font->Height = -Text.tmAscent;
	EstablishedLabel4->Canvas->Font->Height = -Text.tmAscent;
	GetTextMetrics(EstablishedLabel1->Canvas->Handle, &Label);

	DisplayComboBox->Height = ComboBoxHeight;
	DisplayComboBox->Left = Scale;
	DisplayComboBox->Top = Scale;

	DisplayEditButton->Width = ButtonWidth;
	DisplayEditButton->Height = ButtonHeight;
	DisplayEditButton->Top = DisplayComboBox->Top;
	FixButtonCaption(DisplayEditButton, Canvas->TextWidth(DisplayEditButton->Caption));

	DisplayCopyButton->Width = ButtonWidth;
	DisplayCopyButton->Height = ButtonHeight;
	DisplayCopyButton->Top = DisplayEditButton->Top;
	FixButtonCaption(DisplayCopyButton, Canvas->TextWidth(DisplayCopyButton->Caption));

	DisplayPasteButton->Width = ButtonWidth;
	DisplayPasteButton->Height = ButtonHeight;
	DisplayPasteButton->Top = DisplayCopyButton->Top;
	FixButtonCaption(DisplayPasteButton, Canvas->TextWidth(DisplayPasteButton->Caption));

	DisplayDeleteButton->Width = ButtonWidth;
	DisplayDeleteButton->Height = ButtonHeight;
	DisplayDeleteButton->Top = DisplayPasteButton->Top;
	FixButtonCaption(DisplayDeleteButton, Canvas->TextWidth(DisplayDeleteButton->Caption));

	EstablishedAllButton->Width = ButtonWidth;
	EstablishedAllButton->Height = ButtonHeight;
	EstablishedAllButton->Left = PaddingWidth + ButtonLeft;
	FixButtonCaption(EstablishedAllButton, Canvas->TextWidth(EstablishedAllButton->Caption));

	EstablishedNoneButton->Width = ButtonWidth;
	EstablishedNoneButton->Height = ButtonHeight;
	EstablishedNoneButton->Left = EstablishedAllButton->Left + EstablishedAllButton->Width;
	FixButtonCaption(EstablishedNoneButton, Canvas->TextWidth(EstablishedNoneButton->Caption));

	EstablishedResetButton->Width = ButtonWidth;
	EstablishedResetButton->Height = ButtonHeight;
	EstablishedResetButton->Left = EstablishedNoneButton->Left + EstablishedNoneButton->Width;
	FixButtonCaption(EstablishedResetButton, Canvas->TextWidth(EstablishedResetButton->Caption));

	EstablishedGroupBox->Width = EstablishedResetButton->Left + EstablishedResetButton->Width + ButtonRight + PaddingWidth;
	EstablishedGroupBox->Left = DisplayComboBox->Left;
	EstablishedGroupBox->Top = DisplayComboBox->Top + DisplayComboBox->Height + GroupBoxTop;

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
	DetailedGroupBox->Left = EstablishedGroupBox->Left + EstablishedGroupBox->Width + Scale;
	DetailedGroupBox->Top = EstablishedGroupBox->Top;

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

	ExtensionListBox->Width = StandardListBox->Width;
	ExtensionListBox->Height = Text.tmHeight * ExtensionRows + 4;
	ExtensionListBox->ItemHeight = Text.tmHeight;
	ExtensionListBox->Left = PaddingWidth;
	ExtensionListBox->Top = PaddingTop;

	ExtensionAddButton->Width = ButtonWidth;
	ExtensionAddButton->Height = ButtonHeight;
	ExtensionAddButton->Left = ExtensionListBox->Left + ButtonLeft;
	ExtensionAddButton->Top = ExtensionListBox->Top + ExtensionListBox->Height + Scale + ButtonTop;
	FixButtonCaption(ExtensionAddButton, Canvas->TextWidth(ExtensionAddButton->Caption));

	ExtensionEditButton->Width = ButtonWidth;
	ExtensionEditButton->Height = ButtonHeight;
	ExtensionEditButton->Left = ExtensionAddButton->Left + ExtensionAddButton->Width;
	ExtensionEditButton->Top = ExtensionAddButton->Top;
	FixButtonCaption(ExtensionEditButton, Canvas->TextWidth(ExtensionEditButton->Caption));

	ExtensionDeleteButton->Width = ButtonWidth;
	ExtensionDeleteButton->Height = ButtonHeight;
	ExtensionDeleteButton->Left = ExtensionEditButton->Left + ExtensionEditButton->Width;
	ExtensionDeleteButton->Top = ExtensionEditButton->Top;
	FixButtonCaption(ExtensionDeleteButton, Canvas->TextWidth(ExtensionDeleteButton->Caption));

	ExtensionDeleteAllButton->Width = LongButtonWidth;
	ExtensionDeleteAllButton->Height = LongButtonHeight;
	ExtensionDeleteAllButton->Left = ExtensionDeleteButton->Left + ExtensionDeleteButton->Width;
	ExtensionDeleteAllButton->Top = ExtensionDeleteButton->Top;
	FixButtonCaption(ExtensionDeleteAllButton, Canvas->TextWidth(ExtensionDeleteAllButton->Caption));

	ExtensionResetButton->Width = ButtonWidth;
	ExtensionResetButton->Height = ButtonHeight;
	ExtensionResetButton->Left = ExtensionDeleteAllButton->Left + ExtensionDeleteAllButton->Width;
	ExtensionResetButton->Top = ExtensionDeleteAllButton->Top;
	FixButtonCaption(ExtensionResetButton, Canvas->TextWidth(ExtensionResetButton->Caption));

	ExtensionUpButton->Width = ArrowButtonWidth;
	ExtensionUpButton->Height = ArrowButtonHeight;
	ExtensionUpButton->Top = ExtensionResetButton->Top;
	ExtensionUpButton->Enabled = false;
	ExtensionUpButton->NumGlyphs = NumGlyphs;
	ExtensionUpButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_UP));

	ExtensionDownButton->Width = ArrowButtonWidth;
	ExtensionDownButton->Height = ArrowButtonHeight;
	ExtensionDownButton->Top = ExtensionUpButton->Top;
	ExtensionDownButton->Enabled = false;
	ExtensionDownButton->NumGlyphs = NumGlyphs;
	ExtensionDownButton->Glyph->LoadFromResourceID(0, GetScaledResourceID(ARROW_DOWN));

	ExtensionDownButton->Left = ExtensionListBox->Left + ExtensionListBox->Width - ButtonRight - ExtensionDownButton->Width;
	ExtensionUpButton->Left = ExtensionDownButton->Left - ExtensionUpButton->Width;

	ExtensionGroupBox->Width = StandardGroupBox->Width;
	ExtensionGroupBox->Height = ExtensionAddButton->Top + ExtensionAddButton->Height + ButtonBottom + PaddingBottom;
	ExtensionGroupBox->Left = StandardGroupBox->Left;
	ExtensionGroupBox->Top = StandardGroupBox->Top + StandardGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	DisplayDeleteButton->Left = DetailedGroupBox->Left + DetailedGroupBox->Width - ButtonRight - DisplayDeleteButton->Width;
	DisplayPasteButton->Left = DisplayDeleteButton->Left - DisplayPasteButton->Width;
	DisplayCopyButton->Left = DisplayPasteButton->Left - DisplayCopyButton->Width;
	DisplayEditButton->Left = DisplayCopyButton->Left - DisplayEditButton->Width;
	DisplayComboBox->Width = DisplayEditButton->Left - ButtonLeft - Scale - DisplayComboBox->Left;

	EstablishedAllButton->Top = ExtensionGroupBox->Top + ExtensionAddButton->Top - DetailedGroupBox->Top;
	EstablishedNoneButton->Top = EstablishedAllButton->Top;
	EstablishedResetButton->Top = EstablishedNoneButton->Top;
	EstablishedGroupBox->Height = EstablishedAllButton->Top + EstablishedAllButton->Height + ButtonBottom + PaddingBottom;

	int EstablishedHeight = EstablishedAllButton->Top - ButtonTop - Scale - PaddingTop;
	int EstablishedCheckBoxSpacing = (EstablishedHeight - CheckBoxHeight * 15 - Text.tmHeight * 3) / 11;
	int EstablishedLabelSpacing = (EstablishedHeight - CheckBoxHeight * 15 - EstablishedCheckBoxSpacing * 11) / 3;
	int EstablishedLabelHeight = Text.tmAscent + Label.tmDescent + 2;

	EstablishedLabel1->AutoSize = false;
	EstablishedLabel1->Layout = tlBottom;
	EstablishedLabel1->Width = EstablishedLabel1->Canvas->TextWidth(EstablishedLabel1->Caption);
	EstablishedLabel1->Height = EstablishedLabelHeight;
	EstablishedLabel1->Left = PaddingWidth + CheckBoxWidth + CheckBoxRight + (Canvas->TextWidth(EstablishedCheckBox2->Caption) - EstablishedLabel1->Width) / 2;
	EstablishedLabel1->Top = PaddingTop;

	EstablishedCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox2->Caption);
	EstablishedCheckBox2->Height = CheckBoxHeight;
	EstablishedCheckBox2->Left = PaddingWidth;
	EstablishedCheckBox2->Top = EstablishedLabel1->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox4->Caption);
	EstablishedCheckBox4->Height = CheckBoxHeight;
	EstablishedCheckBox4->Left = EstablishedCheckBox2->Left;
	EstablishedCheckBox4->Top = EstablishedCheckBox2->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox5->Caption);
	EstablishedCheckBox5->Height = CheckBoxHeight;
	EstablishedCheckBox5->Left = EstablishedCheckBox4->Left;
	EstablishedCheckBox5->Top = EstablishedCheckBox4->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedLabel2->AutoSize = false;
	EstablishedLabel2->Layout = tlBottom;
	EstablishedLabel2->Width = EstablishedLabel2->Canvas->TextWidth(EstablishedLabel2->Caption);
	EstablishedLabel2->Height = EstablishedLabelHeight;
	EstablishedLabel2->Left = EstablishedLabel1->Left;
	EstablishedLabel2->Top = EstablishedCheckBox5->Top + CheckBoxHeight + EstablishedLabelSpacing;

	EstablishedCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox6->Caption);
	EstablishedCheckBox6->Height = CheckBoxHeight;
	EstablishedCheckBox6->Left = EstablishedCheckBox5->Left;
	EstablishedCheckBox6->Top = EstablishedLabel2->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox7->Caption);
	EstablishedCheckBox7->Height = CheckBoxHeight;
	EstablishedCheckBox7->Left = EstablishedCheckBox6->Left;
	EstablishedCheckBox7->Top = EstablishedCheckBox6->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox8->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox8->Caption);
	EstablishedCheckBox8->Height = CheckBoxHeight;
	EstablishedCheckBox8->Left = EstablishedCheckBox7->Left;
	EstablishedCheckBox8->Top = EstablishedCheckBox7->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox9->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox9->Caption);
	EstablishedCheckBox9->Height = CheckBoxHeight;
	EstablishedCheckBox9->Left = EstablishedCheckBox8->Left;
	EstablishedCheckBox9->Top = EstablishedCheckBox8->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedLabel3->AutoSize = false;
	EstablishedLabel3->Layout = tlBottom;
	EstablishedLabel3->Width = EstablishedLabel3->Canvas->TextWidth(EstablishedLabel3->Caption);
	EstablishedLabel3->Height = EstablishedLabelHeight;
	EstablishedLabel3->Left = EstablishedLabel2->Left;
	EstablishedLabel3->Top = EstablishedCheckBox9->Top + CheckBoxHeight + EstablishedLabelSpacing;

	EstablishedCheckBox12->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox12->Caption);
	EstablishedCheckBox12->Height = CheckBoxHeight;
	EstablishedCheckBox12->Left = EstablishedCheckBox9->Left;
	EstablishedCheckBox12->Top = EstablishedLabel3->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox13->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox13->Caption);
	EstablishedCheckBox13->Height = CheckBoxHeight;
	EstablishedCheckBox13->Left = EstablishedCheckBox12->Left;
	EstablishedCheckBox13->Top = EstablishedCheckBox12->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedCheckBox14->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox14->Caption);
	EstablishedCheckBox14->Height = CheckBoxHeight;
	EstablishedCheckBox14->Left = EstablishedCheckBox13->Left;
	EstablishedCheckBox14->Top = EstablishedCheckBox13->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	EstablishedLabel4->AutoSize = false;
	EstablishedLabel4->Layout = tlBottom;
	EstablishedLabel4->Width = EstablishedLabel4->Canvas->TextWidth(EstablishedLabel4->Caption);
	EstablishedLabel4->Height = EstablishedLabelHeight;
	EstablishedLabel4->Left = EstablishedLabel3->Left;
	EstablishedLabel4->Top = EstablishedCheckBox14->Top + CheckBoxHeight + EstablishedLabelSpacing;

	EstablishedCheckBox15->Width = CheckBoxWidth + Canvas->TextWidth(EstablishedCheckBox15->Caption);
	EstablishedCheckBox15->Height = CheckBoxHeight;
	EstablishedCheckBox15->Left = EstablishedCheckBox14->Left;
	EstablishedCheckBox15->Top = EstablishedLabel4->Top + CheckBoxHeight + EstablishedCheckBoxSpacing;

	DisplayImportButton->Width = (EstablishedGroupBox->Width - Scale) / 2 - ButtonLeft - ButtonRight;
	DisplayImportButton->Height = FormButtonHeight;
	DisplayImportButton->Left = EstablishedGroupBox->Left + ButtonLeft;
	DisplayImportButton->Top = EstablishedGroupBox->Top + EstablishedGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(DisplayImportButton, Canvas->TextWidth(DisplayImportButton->Caption));

	DisplayExportButton->Width = (EstablishedGroupBox->Width - Scale) / 2 - ButtonLeft - ButtonRight;
	DisplayExportButton->Height = FormButtonHeight;
	DisplayExportButton->Left = DisplayImportButton->Left + DisplayImportButton->Width + ButtonRight + Scale + ButtonLeft;
	DisplayExportButton->Top = DisplayImportButton->Top;
	FixButtonCaption(DisplayExportButton, Canvas->TextWidth(DisplayExportButton->Caption));

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = ExtensionGroupBox->Top + ExtensionGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = ExtensionGroupBox->Left + ExtensionGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::FormCreate(TObject *Sender)
{
	if (!DisplayList.Load())
		FatalError("Failed to load displays from the registry.\nTry running as administrator.");

	if (DisplayList.GetCount() == 0)
		FatalError("No displays found in the registry.\nRun restart.exe or reboot to redetect displays.");

	Display = DisplayList.Get(0);
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::FormShow(TObject *Sender)
{
	RefreshDisplayComboBox();
	DisplayComboBox->ItemIndex = 0;
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Display = DisplayList.Get(DisplayComboBox->ItemIndex);
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayEditButtonClick(TObject *Sender)
{
	PropertiesClass Properties;
	TPropertiesForm *PropertiesForm = new TPropertiesForm(this);

	Display->GetProperties(Properties);
	PropertiesForm->Connect(Properties);

	if (PropertiesForm->ShowModal() == mrOk)
	{
		Display->SetProperties(Properties);
		RefreshDisplayComboBox();
		RefreshDisplayButtons();
		RefreshDetailedListBox(-1);
		RefreshDetailedButtons();
	}

	delete PropertiesForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayCopyButtonClick(TObject *Sender)
{
	Display->DisplayCopy();
	RefreshDisplayButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayPasteButtonClick(TObject *Sender)
{
	Display->DisplayPaste();
	RefreshDisplayComboBox();
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayDeleteButtonClick(TObject *Sender)
{
	if (Display->DisplayDeletePossible())
		Display->DisplayDelete();
	else
		Display->DisplayRestore();

	RefreshDisplayComboBox();
	Refresh(NULL, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::EstablishedCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	Display->EstablishedResolutions()->Set(CheckBox->Tag, CheckBox->Checked);
	Refresh(EstablishedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::EstablishedAllButtonClick(TObject *Sender)
{
	Display->EstablishedResolutions()->All();
	Refresh(EstablishedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::EstablishedNoneButtonClick(TObject *Sender)
{
	Display->EstablishedResolutions()->None();
	Refresh(EstablishedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::EstablishedResetButtonClick(TObject *Sender)
{
	Display->EstablishedResolutions()->Undo();
	Refresh(EstablishedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	ListBoxDrawItem(DetailedListBox, Rect, State, DetailedListBox->Items->Strings[Index].c_str(), Display->DetailedResolutions()->EditPossible(Index), false);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	DetailedLastClickedItemIndex = DetailedListBox->ItemIndex;

	if (DetailedListBox->ItemIndex == DetailedLastItemIndex)
		DetailedListBox->ItemIndex = -1;

	RefreshDetailedButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedListBoxDoubleClick(TObject *Sender)
{
	DetailedListBox->ItemIndex = DetailedLastClickedItemIndex;
	RefreshDetailedButtons();

	if (Display->DetailedResolutions()->EditPossible(DetailedListBox->ItemIndex))
		DetailedEditButtonClick(DetailedListBox);

	DetailedLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedListBoxSelect(TObject *Sender)
{
	RefreshDetailedButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedAddButtonClick(TObject *Sender)
{
	DetailedResolutionClass DetailedResolution;
	TDetailedResolutionForm *DetailedResolutionForm = new TDetailedResolutionForm(this);

	Display->GetNative(DetailedResolution);
	DetailedResolutionForm->Connect(DetailedResolution);

	if (DetailedResolutionForm->ShowModal() == mrOk)
	{
		Display->DetailedResolutions()->Add(DetailedResolution);
		Refresh(DetailedGroupBox, Display->DetailedResolutions()->GetCount() - 1);
	}

	delete DetailedResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedEditButtonClick(TObject *Sender)
{
	DetailedResolutionClass DetailedResolution;
	TDetailedResolutionForm *DetailedResolutionForm = new TDetailedResolutionForm(this);

	Display->DetailedResolutions()->Get(DetailedListBox->ItemIndex, DetailedResolution);
	DetailedResolutionForm->Connect(DetailedResolution);

	if (DetailedResolutionForm->ShowModal() == mrOk)
	{
		Display->DetailedResolutions()->Set(DetailedListBox->ItemIndex, DetailedResolution);
		Refresh(DetailedGroupBox, DetailedListBox->ItemIndex);
	}

	delete DetailedResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedDeleteButtonClick(TObject *Sender)
{
	Display->DetailedResolutions()->Delete(DetailedListBox->ItemIndex);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedDeleteAllButtonClick(TObject *Sender)
{
	Display->DetailedResolutions()->DeleteAll();
	Refresh(DetailedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedResetButtonClick(TObject *Sender)
{
	Display->DetailedResolutions()->Undo();
	Refresh(DetailedGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedUpButtonClick(TObject *Sender)
{
	Display->DetailedResolutions()->Exchange(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex - 1);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DetailedDownButtonClick(TObject *Sender)
{
	Display->DetailedResolutions()->Exchange(DetailedListBox->ItemIndex, DetailedListBox->ItemIndex + 1);
	Refresh(DetailedGroupBox, DetailedListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	StandardResolutionClass StandardResolution;
	bool Supported = false;

	if (Display->StandardResolutions()->Get(Index, StandardResolution))
		Supported = StandardResolution.IsSupported();

	ListBoxDrawItem(StandardListBox, Rect, State, StandardListBox->Items->Strings[Index].c_str(), Supported, false);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	StandardLastClickedItemIndex = StandardListBox->ItemIndex;

	if (StandardListBox->ItemIndex == StandardLastItemIndex)
		StandardListBox->ItemIndex = -1;

	RefreshStandardButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardListBoxDoubleClick(TObject *Sender)
{
	StandardListBox->ItemIndex = StandardLastClickedItemIndex;
	RefreshStandardButtons();

	if (Display->StandardResolutions()->EditPossible(StandardListBox->ItemIndex))
		StandardEditButtonClick(StandardListBox);

	StandardLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardListBoxSelect(TObject *Sender)
{
	RefreshStandardButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardAddButtonClick(TObject *Sender)
{
	StandardResolutionClass StandardResolution;
	TStandardResolutionForm *StandardResolutionForm = new TStandardResolutionForm(this);

	StandardResolutionForm->Connect(StandardResolution);

	if (StandardResolutionForm->ShowModal() == mrOk)
	{
		Display->StandardResolutions()->Add(StandardResolution);
		Refresh(StandardGroupBox, Display->StandardResolutions()->GetCount() - 1);
	}

	delete StandardResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardEditButtonClick(TObject *Sender)
{
	StandardResolutionClass StandardResolution;
	TStandardResolutionForm *StandardResolutionForm = new TStandardResolutionForm(this);

	Display->StandardResolutions()->Get(StandardListBox->ItemIndex, StandardResolution);
	StandardResolutionForm->Connect(StandardResolution);

	if (StandardResolutionForm->ShowModal() == mrOk)
	{
		Display->StandardResolutions()->Set(StandardListBox->ItemIndex, StandardResolution);
		Refresh(StandardGroupBox, StandardListBox->ItemIndex);
	}

	delete StandardResolutionForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardDeleteButtonClick(TObject *Sender)
{
	Display->StandardResolutions()->Delete(StandardListBox->ItemIndex);
	Refresh(StandardGroupBox, StandardListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardDeleteAllButtonClick(TObject *Sender)
{
	Display->StandardResolutions()->DeleteAll();
	Refresh(StandardGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardResetButtonClick(TObject *Sender)
{
	Display->StandardResolutions()->Undo();
	Refresh(StandardGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardUpButtonClick(TObject *Sender)
{
	Display->StandardResolutions()->Exchange(StandardListBox->ItemIndex, StandardListBox->ItemIndex - 1);
	Refresh(StandardGroupBox, StandardListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::StandardDownButtonClick(TObject *Sender)
{
	Display->StandardResolutions()->Exchange(StandardListBox->ItemIndex, StandardListBox->ItemIndex + 1);
	Refresh(StandardGroupBox, StandardListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	ExtensionBlockClass ExtensionBlock;
	bool Supported = false;

	if (Display->ExtensionBlocks()->Get(Index, ExtensionBlock))
		Supported = ExtensionBlock.IsSupported();

	ListBoxDrawItem(ExtensionListBox, Rect, State, ExtensionListBox->Items->Strings[Index].c_str(), Supported, false);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionListBoxClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ExtensionLastClickedItemIndex = ExtensionListBox->ItemIndex;

	if (ExtensionListBox->ItemIndex == ExtensionLastItemIndex)
		ExtensionListBox->ItemIndex = -1;

	RefreshExtensionButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionListBoxDoubleClick(TObject *Sender)
{
	ExtensionListBox->ItemIndex = ExtensionLastClickedItemIndex;
	RefreshExtensionButtons();

	if (Display->ExtensionBlocks()->EditPossible(ExtensionListBox->ItemIndex))
		ExtensionEditButtonClick(ExtensionListBox);

	ExtensionLastItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionListBoxSelect(TObject *Sender)
{
	RefreshExtensionButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionAddButtonClick(TObject *Sender)
{
	ExtensionBlockClass ExtensionBlock;
	DetailedResolutionClass NativeResolution;
	PropertiesClass Properties;
	TExtensionBlockForm *ExtensionBlockForm = new TExtensionBlockForm(this);

	Display->GetNative(NativeResolution);
	Display->GetProperties(Properties);
	ExtensionBlockForm->Connect(ExtensionBlock, NativeResolution, Properties);

	if (ExtensionBlockForm->ShowModal() == mrOk)
	{
		Display->ExtensionBlocks()->Add(ExtensionBlock);
		Refresh(ExtensionGroupBox, Display->ExtensionBlocks()->GetCount() - 1);
	}

	delete ExtensionBlockForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionEditButtonClick(TObject *Sender)
{
	ExtensionBlockClass ExtensionBlock;
	DetailedResolutionClass NativeResolution;
	PropertiesClass Properties;
	TExtensionBlockForm *ExtensionBlockForm = new TExtensionBlockForm(this);

	Display->ExtensionBlocks()->Get(ExtensionListBox->ItemIndex, ExtensionBlock);
	Display->GetNative(NativeResolution);
	Display->GetProperties(Properties);
	ExtensionBlockForm->Connect(ExtensionBlock, NativeResolution, Properties);

	if (ExtensionBlockForm->ShowModal() == mrOk)
	{
		Display->ExtensionBlocks()->Set(ExtensionListBox->ItemIndex, ExtensionBlock);
		Refresh(ExtensionGroupBox, ExtensionListBox->ItemIndex);
	}

	delete ExtensionBlockForm;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionDeleteButtonClick(TObject *Sender)
{
	Display->ExtensionBlocks()->Delete(ExtensionListBox->ItemIndex);
	Refresh(ExtensionGroupBox, ExtensionListBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionDeleteAllButtonClick(TObject *Sender)
{
	Display->ExtensionBlocks()->DeleteAll();
	Refresh(ExtensionGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionResetButtonClick(TObject *Sender)
{
	Display->ExtensionBlocks()->Undo();
	Refresh(ExtensionGroupBox, -1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionUpButtonClick(TObject *Sender)
{
	Display->ExtensionBlocks()->Exchange(ExtensionListBox->ItemIndex, ExtensionListBox->ItemIndex - 1);
	Refresh(ExtensionGroupBox, ExtensionListBox->ItemIndex - 1);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::ExtensionDownButtonClick(TObject *Sender)
{
	Display->ExtensionBlocks()->Exchange(ExtensionListBox->ItemIndex, ExtensionListBox->ItemIndex + 1);
	Refresh(ExtensionGroupBox, ExtensionListBox->ItemIndex + 1);
}
//---------------------------------------------------------------------------
UINT_PTR CALLBACK ImportHook(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	static OPENFILENAME *OpenFileName;
	static bool *Complete;

	switch (Message)
	{
		case WM_INITDIALOG:
			OpenFileName = (OPENFILENAME *)lParam;
			Complete = (bool *)OpenFileName->lCustData;
			CheckDlgButton(Window, 100, *Complete);
			break;

		case WM_COMMAND:
			*Complete = IsDlgButtonChecked(Window, 100);
			break;
	}

	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayImportButtonClick(TObject *Sender)
{
	OPENFILENAME OpenFileName;
	char FileName[MAX_PATH];
	bool Complete;

	std::memset(&OpenFileName, 0, sizeof OpenFileName);
	std::memset(FileName, 0, sizeof FileName);
	Complete = false;

	OpenFileName.lStructSize = sizeof OpenFileName;
	OpenFileName.hwndOwner = Handle;
	OpenFileName.hInstance = HInstance;
	OpenFileName.lpstrFilter = DisplayClass::GetImportFormats();
	OpenFileName.lpstrFile = FileName;
	OpenFileName.nMaxFile = MAX_PATH;
	OpenFileName.lpstrTitle = "Import";
	OpenFileName.Flags = OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	OpenFileName.lpstrDefExt = "bin";
	OpenFileName.lCustData = (LPARAM)&Complete;
	OpenFileName.lpfnHook = ImportHook;
	OpenFileName.lpTemplateName = "IDD_IMPORT";

	if (GetOpenFileName(&OpenFileName))
	{
		if (!Display->Import(FileName, Complete))
			Application->MessageBox("Failed to import file.", "Import", MB_ICONERROR);

		RefreshDisplayComboBox();
		Refresh(NULL, -1);
	}
}
//---------------------------------------------------------------------------
UINT_PTR CALLBACK ExportHook(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::DisplayExportButtonClick(TObject *Sender)
{
	OPENFILENAME SaveFileName;
	char FileName[MAX_PATH];
	char Name[MAX_PATH];

	std::memset(&SaveFileName, 0, sizeof SaveFileName);
	std::memset(FileName, 0, sizeof FileName);
	std::memset(Name, 0, sizeof Name);

	SaveFileName.lStructSize = sizeof SaveFileName;
	SaveFileName.hwndOwner = Handle;
	SaveFileName.hInstance = HInstance;
	SaveFileName.lpstrFilter = DisplayClass::GetExportFormats();
	SaveFileName.lpstrFile = FileName;
	SaveFileName.nMaxFile = MAX_PATH;
	SaveFileName.lpstrFileTitle = Name;
	SaveFileName.nMaxFileTitle = MAX_PATH;
	SaveFileName.lpstrTitle = "Export";
	SaveFileName.Flags = OFN_ENABLEHOOK | OFN_EXPLORER | OFN_OVERWRITEPROMPT;
	SaveFileName.lpstrDefExt = "bin";
	SaveFileName.lpfnHook = ExportHook;

	if (GetSaveFileName(&SaveFileName))
	{
		Name[SaveFileName.nFileExtension - SaveFileName.nFileOffset - 1] = 0;

		if (!Display->Export(FileName, SaveFileName.nFilterIndex, Name))
			Application->MessageBox("Failed to write file.", "Export", MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::FormOKButtonClick(TObject *Sender)
{
	if (!DisplayList.Save())
		FatalError("An error occurred while saving. Not all changes were saved.");

	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TDisplayForm::FormCancelButtonClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
