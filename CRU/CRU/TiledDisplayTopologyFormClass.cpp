//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "TiledDisplayTopologyFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TTiledDisplayTopologyForm *TiledDisplayTopologyForm;
//---------------------------------------------------------------------------
__fastcall TTiledDisplayTopologyForm::TTiledDisplayTopologyForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::Connect(TiledDisplayTopologyClass &NewTiledDisplayTopology)
{
	TiledDisplayTopology = &NewTiledDisplayTopology;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == TopologyIDGroupBox)
		RefreshTopologyIDTextBoxes();

	if (Value == NULL || Value == PhysicalEnclosuresGroupBox)
		RefreshPhysicalEnclosuresRadioButtons();

	if (Value == NULL || Value == SingleTileBehaviorGroupBox)
		RefreshSingleTileBehaviorRadioButtons();

	if (Value == NULL || Value == MultipleTileBehaviorGroupBox)
		RefreshMultipleTileBehaviorRadioButtons();

	if (Value == NULL || Value == TilesGroupBox)
		RefreshTilesTextBoxes();

	if (Value == NULL || Value == LocationGroupBox)
		RefreshLocationTextBoxes();

	if (Value == NULL || Value == SizeGroupBox)
		RefreshSizeTextBoxes();

	if (Value == NULL || Value == BezelGroupBox)
		RefreshBezelTextBoxes();

	if (Value != FormOKButton)
		FormOKButton->Enabled = TiledDisplayTopology->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshTopologyIDTextBoxes()
{
	char Text[TEXTSIZE];

	VendorID->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVendorID());

	if (!VendorID->Focused() && TiledDisplayTopology->GetVendorID(Text, TEXTSIZE))
		VendorID->Text = Text;

	ProductID->Font->Color = GetTextColor(TiledDisplayTopology->IsValidProductID());

	if (!ProductID->Focused() && TiledDisplayTopology->GetProductID(Text, TEXTSIZE))
		ProductID->Text = Text;

	SerialID->Font->Color = GetTextColor(TiledDisplayTopology->IsValidSerialID());

	if (!SerialID->Focused() && DecimalToText(TiledDisplayTopology->GetSerialID(), SerialID->MaxLength, 0, Text, TEXTSIZE))
		SerialID->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshPhysicalEnclosuresRadioButtons()
{
	PhysicalEnclosuresRadioButton1->Checked = TiledDisplayTopology->GetPhysicalEnclosures() == 1;
	PhysicalEnclosuresRadioButton0->Checked = TiledDisplayTopology->GetPhysicalEnclosures() == 0;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshSingleTileBehaviorRadioButtons()
{
	SingleTileBehaviorRadioButton1->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 1;
	SingleTileBehaviorRadioButton2->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 2;
	SingleTileBehaviorRadioButton3->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 3;
	SingleTileBehaviorRadioButton0->Checked = TiledDisplayTopology->GetSingleTileBehavior() == 0;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshMultipleTileBehaviorRadioButtons()
{
	MultipleTileBehaviorRadioButton1->Checked = TiledDisplayTopology->GetMultipleTileBehavior() == 1;
	MultipleTileBehaviorRadioButton0->Checked = TiledDisplayTopology->GetMultipleTileBehavior() == 0;
	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshTilesTextBoxes()
{
	char Text[TEXTSIZE];

	HTiles->Font->Color = GetTextColor(TiledDisplayTopology->IsValidHTiles());

	if (!HTiles->Focused() && IntegerToText(TiledDisplayTopology->GetHTiles(), Text, TEXTSIZE))
		HTiles->Text = Text;

	VTiles->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVTiles());

	if (!VTiles->Focused() && IntegerToText(TiledDisplayTopology->GetVTiles(), Text, TEXTSIZE))
		VTiles->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshLocationTextBoxes()
{
	char Text[TEXTSIZE];

	HLocation->Font->Color = GetTextColor(TiledDisplayTopology->IsValidHLocation());

	if (!HLocation->Focused() && IntegerToText(TiledDisplayTopology->GetHLocation(), Text, TEXTSIZE))
		HLocation->Text = Text;

	VLocation->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVLocation());

	if (!VLocation->Focused() && IntegerToText(TiledDisplayTopology->GetVLocation(), Text, TEXTSIZE))
		VLocation->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshSizeTextBoxes()
{
	char Text[TEXTSIZE];

	HSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidHSize());

	if (!HSize->Focused() && IntegerToText(TiledDisplayTopology->GetHSize(), Text, TEXTSIZE))
		HSize->Text = Text;

	VSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidVSize());

	if (!VSize->Focused() && IntegerToText(TiledDisplayTopology->GetVSize(), Text, TEXTSIZE))
		VSize->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::RefreshBezelTextBoxes()
{
	char Text[TEXTSIZE];

	PixelMultiplier->Font->Color = GetTextColor(TiledDisplayTopology->IsValidPixelMultiplier());

	if (!PixelMultiplier->Focused() && IntegerToText(TiledDisplayTopology->GetPixelMultiplier(), Text, TEXTSIZE))
		PixelMultiplier->Text = Text;

	TopBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidTopBezelSize());

	if (!TopBezelSize->Focused() && IntegerToText(TiledDisplayTopology->GetTopBezelSize(), Text, TEXTSIZE))
		TopBezelSize->Text = Text;

	LeftBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidLeftBezelSize());

	if (!LeftBezelSize->Focused() && IntegerToText(TiledDisplayTopology->GetLeftBezelSize(), Text, TEXTSIZE))
		LeftBezelSize->Text = Text;

	RightBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidRightBezelSize());

	if (!RightBezelSize->Focused() && IntegerToText(TiledDisplayTopology->GetRightBezelSize(), Text, TEXTSIZE))
		RightBezelSize->Text = Text;

	BottomBezelSize->Font->Color = GetTextColor(TiledDisplayTopology->IsValidBottomBezelSize());

	if (!BottomBezelSize->Focused() && IntegerToText(TiledDisplayTopology->GetBottomBezelSize(), Text, TEXTSIZE))
		BottomBezelSize->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TTiledDisplayTopologyForm::ScaleControls()
{
	VendorID->AutoSize = false;
	VendorID->Width = FormButtonsWidth - PaddingWidth - ProductIDLabel->Width - LabelSpacing - PaddingWidth;
	VendorID->Height = TextBoxHeight;

	ProductID->AutoSize = false;
	ProductID->Width = VendorID->Width;
	ProductID->Height = TextBoxHeight;

	SerialID->AutoSize = false;
	SerialID->Width = ProductID->Width;
	SerialID->Height = TextBoxHeight;

	VendorIDLabel->Left = PaddingWidth;
	VendorID->Left = VendorIDLabel->Left + ProductIDLabel->Width + LabelSpacing;

	ProductIDLabel->Left = VendorIDLabel->Left;
	ProductID->Left = VendorID->Left;

	SerialIDLabel->Left = ProductIDLabel->Left;
	SerialID->Left = ProductID->Left;

	VendorID->Top = PaddingTop;
	VendorIDLabel->Top = VendorID->Top + 3;

	ProductID->Top = VendorID->Top + VendorID->Height + TextBoxSpacing;
	ProductIDLabel->Top = ProductID->Top + 3;

	SerialID->Top = ProductID->Top + ProductID->Height + TextBoxSpacing;
	SerialIDLabel->Top = SerialID->Top + 3;

	TopologyIDGroupBox->Width = FormButtonsWidth;
	TopologyIDGroupBox->Height = SerialID->Top + SerialID->Height + PaddingBottom;
	TopologyIDGroupBox->Left = Scale;
	TopologyIDGroupBox->Top = GroupBoxTop;

	PhysicalEnclosuresRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(PhysicalEnclosuresRadioButton1->Caption);
	PhysicalEnclosuresRadioButton1->Height = RadioButtonHeight;
	PhysicalEnclosuresRadioButton1->Left = PaddingWidth;
	PhysicalEnclosuresRadioButton1->Top = PaddingTop + RadioButtonTop;

	PhysicalEnclosuresRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(PhysicalEnclosuresRadioButton0->Caption);
	PhysicalEnclosuresRadioButton0->Height = RadioButtonHeight;
	PhysicalEnclosuresRadioButton0->Left = PhysicalEnclosuresRadioButton1->Left;
	PhysicalEnclosuresRadioButton0->Top = PhysicalEnclosuresRadioButton1->Top + PhysicalEnclosuresRadioButton1->Height + RadioButtonSpacing;

	PhysicalEnclosuresGroupBox->Width = TopologyIDGroupBox->Width;
	PhysicalEnclosuresGroupBox->Height = PhysicalEnclosuresRadioButton0->Top + PhysicalEnclosuresRadioButton0->Height + RadioButtonBottom + PaddingBottom;
	PhysicalEnclosuresGroupBox->Left = TopologyIDGroupBox->Left;
	PhysicalEnclosuresGroupBox->Top = TopologyIDGroupBox->Top + TopologyIDGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	SingleTileBehaviorRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton1->Caption);
	SingleTileBehaviorRadioButton1->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton1->Left = PaddingWidth;
	SingleTileBehaviorRadioButton1->Top = PaddingTop + RadioButtonTop;

	SingleTileBehaviorRadioButton2->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton2->Caption);
	SingleTileBehaviorRadioButton2->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton2->Left = SingleTileBehaviorRadioButton1->Left;
	SingleTileBehaviorRadioButton2->Top = SingleTileBehaviorRadioButton1->Top + SingleTileBehaviorRadioButton1->Height + RadioButtonSpacing;

	SingleTileBehaviorRadioButton3->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton3->Caption);
	SingleTileBehaviorRadioButton3->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton3->Left = SingleTileBehaviorRadioButton2->Left;
	SingleTileBehaviorRadioButton3->Top = SingleTileBehaviorRadioButton2->Top + SingleTileBehaviorRadioButton2->Height + RadioButtonSpacing;

	SingleTileBehaviorRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(SingleTileBehaviorRadioButton0->Caption);
	SingleTileBehaviorRadioButton0->Height = RadioButtonHeight;
	SingleTileBehaviorRadioButton0->Left = SingleTileBehaviorRadioButton3->Left;
	SingleTileBehaviorRadioButton0->Top = SingleTileBehaviorRadioButton3->Top + SingleTileBehaviorRadioButton3->Height + RadioButtonSpacing;

	SingleTileBehaviorGroupBox->Width = PhysicalEnclosuresGroupBox->Width;
	SingleTileBehaviorGroupBox->Height = SingleTileBehaviorRadioButton0->Top + SingleTileBehaviorRadioButton0->Height + RadioButtonBottom + PaddingBottom;
	SingleTileBehaviorGroupBox->Left = PhysicalEnclosuresGroupBox->Left;
	SingleTileBehaviorGroupBox->Top = PhysicalEnclosuresGroupBox->Top + PhysicalEnclosuresGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	MultipleTileBehaviorRadioButton1->Width = RadioButtonWidth + Canvas->TextWidth(MultipleTileBehaviorRadioButton1->Caption);
	MultipleTileBehaviorRadioButton1->Height = RadioButtonHeight;
	MultipleTileBehaviorRadioButton1->Left = PaddingWidth;
	MultipleTileBehaviorRadioButton1->Top = PaddingTop + RadioButtonTop;

	MultipleTileBehaviorRadioButton0->Width = RadioButtonWidth + Canvas->TextWidth(MultipleTileBehaviorRadioButton0->Caption);
	MultipleTileBehaviorRadioButton0->Height = RadioButtonHeight;
	MultipleTileBehaviorRadioButton0->Left = MultipleTileBehaviorRadioButton1->Left;
	MultipleTileBehaviorRadioButton0->Top = MultipleTileBehaviorRadioButton1->Top + MultipleTileBehaviorRadioButton1->Height + RadioButtonSpacing;

	MultipleTileBehaviorGroupBox->Width = SingleTileBehaviorGroupBox->Width;
	MultipleTileBehaviorGroupBox->Height = MultipleTileBehaviorRadioButton0->Top + MultipleTileBehaviorRadioButton0->Height + RadioButtonBottom + PaddingBottom;
	MultipleTileBehaviorGroupBox->Left = SingleTileBehaviorGroupBox->Left;
	MultipleTileBehaviorGroupBox->Top = SingleTileBehaviorGroupBox->Top + SingleTileBehaviorGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	HTiles->AutoSize = false;
	HTiles->Width = TextBoxHeight;
	HTiles->Height = TextBoxHeight;
	HTiles->Left = PaddingWidth;
	HTiles->Top = PaddingTop;

	TilesLabel->Left = HTiles->Left + HTiles->Width + LabelSpacing;
	TilesLabel->Top = HTiles->Top + 3;

	VTiles->AutoSize = false;
	VTiles->Width = TextBoxHeight;
	VTiles->Height = TextBoxHeight;
	VTiles->Left = TilesLabel->Left + TilesLabel->Width + LabelSpacing;
	VTiles->Top = HTiles->Top;

	TilesGroupBox->Width = TopologyIDGroupBox->Width;
	TilesGroupBox->Height = HTiles->Top + HTiles->Height + PaddingBottom;
	TilesGroupBox->Left = TopologyIDGroupBox->Left + TopologyIDGroupBox->Width + Scale;
	TilesGroupBox->Top = TopologyIDGroupBox->Top;

	HLocation->AutoSize = false;
	HLocation->Width = TextBoxHeight;
	HLocation->Height = TextBoxHeight;
	HLocation->Left = PaddingWidth;
	HLocation->Top = PaddingTop;

	LocationLabel->Left = HLocation->Left + HLocation->Width + LabelSpacing;
	LocationLabel->Top = HLocation->Top + 3;

	VLocation->AutoSize = false;
	VLocation->Width = TextBoxHeight;
	VLocation->Height = TextBoxHeight;
	VLocation->Left = LocationLabel->Left + TilesLabel->Width + LabelSpacing;
	VLocation->Top = HLocation->Top;

	LocationGroupBox->Width = TilesGroupBox->Width;
	LocationGroupBox->Height = HLocation->Top + HLocation->Height + PaddingBottom;
	LocationGroupBox->Left = TilesGroupBox->Left;
	LocationGroupBox->Top = TilesGroupBox->Top + TilesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	HSize->AutoSize = false;
	HSize->Width = HSize->MaxLength * NumberWidth + TextBoxPadding;
	HSize->Height = TextBoxHeight;
	HSize->Left = PaddingWidth;
	HSize->Top = PaddingTop;

	SizeLabel->Left = HSize->Left + HSize->Width + LabelSpacing;
	SizeLabel->Top = HSize->Top + 3;

	VSize->AutoSize = false;
	VSize->Width = VSize->MaxLength * NumberWidth + TextBoxPadding;
	VSize->Height = TextBoxHeight;
	VSize->Left = SizeLabel->Left + SizeLabel->Width + LabelSpacing;
	VSize->Top = HSize->Top;

	SizeGroupBox->Width = LocationGroupBox->Width;
	SizeGroupBox->Height = HSize->Top + HSize->Height + PaddingBottom;
	SizeGroupBox->Left = LocationGroupBox->Left;
	SizeGroupBox->Top = LocationGroupBox->Top + LocationGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	PixelMultiplier->AutoSize = false;
	PixelMultiplier->Width = PixelMultiplier->MaxLength * NumberWidth + TextBoxPadding;
	PixelMultiplier->Height = TextBoxHeight;

	TopBezelSize->AutoSize = false;
	TopBezelSize->Width = TopBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	TopBezelSize->Height = TextBoxHeight;

	LeftBezelSize->AutoSize = false;
	LeftBezelSize->Width = LeftBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	LeftBezelSize->Height = TextBoxHeight;

	RightBezelSize->AutoSize = false;
	RightBezelSize->Width = RightBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	RightBezelSize->Height = TextBoxHeight;

	BottomBezelSize->AutoSize = false;
	BottomBezelSize->Width = BottomBezelSize->MaxLength * NumberWidth + TextBoxPadding;
	BottomBezelSize->Height = TextBoxHeight;

	PixelMultiplier->Left = (FormButtonsWidth - PixelMultiplier->Width) / 2;
	TopBezelSize->Left = PixelMultiplier->Left;
	LeftBezelSize->Left = PaddingWidth;
	RightBezelSize->Left = FormButtonsWidth - RightBezelSize->Width - PaddingWidth;
	BottomBezelSize->Left = TopBezelSize->Left;

	int Space = TextBoxSpacing * 2 + RadioButtonTop * 3 + RadioButtonHeight * 8 + RadioButtonSpacing * 5 + RadioButtonBottom * 3 - TextBoxHeight * 4 - Scale;

	PixelMultiplier->Top = PaddingTop;
	TopBezelSize->Top = PixelMultiplier->Top + PixelMultiplier->Height + Scale - Space % 2;
	LeftBezelSize->Top = TopBezelSize->Top + TopBezelSize->Height + Space / 2 + Space % 2;
	RightBezelSize->Top = LeftBezelSize->Top;
	BottomBezelSize->Top = LeftBezelSize->Top + LeftBezelSize->Height + Space / 2 + Space % 2;

	MultiplierLabel->Left = PixelMultiplier->Left - MultiplierLabel->Width - LabelSpacing;
	MultiplierLabel->Top = PixelMultiplier->Top + 3;

	MultiplierDivisorLabel->Left = PixelMultiplier->Left + PixelMultiplier->Width + PostLabelSpacing;
	MultiplierDivisorLabel->Top = PixelMultiplier->Top + 3;

	Rectangle->Pen->Width = Scale / 2;
	int MarginWidth = (LeftBezelSize->Width - Rectangle->Pen->Width) / 2;
	int MarginHeight = (TopBezelSize->Height - Rectangle->Pen->Width) / 2;
	Rectangle->Width = RightBezelSize->Left + RightBezelSize->Width - LeftBezelSize->Left - MarginWidth * 2;
	Rectangle->Height = BottomBezelSize->Top + BottomBezelSize->Height - TopBezelSize->Top - MarginHeight * 2;
	Rectangle->Left = LeftBezelSize->Left + MarginWidth;
	Rectangle->Top = TopBezelSize->Top + MarginHeight;

	BezelGroupBox->Width = SizeGroupBox->Width;
	BezelGroupBox->Height = BottomBezelSize->Top + BottomBezelSize->Height + PaddingBottom;
	BezelGroupBox->Left = SizeGroupBox->Left;
	BezelGroupBox->Top = SizeGroupBox->Top + SizeGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = BezelGroupBox->Top + BezelGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = BezelGroupBox->Left + BezelGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VendorIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVendorID(VendorID->Text.c_str());
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VendorIDExit(TObject *Sender)
{
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::ProductIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetProductID(ProductID->Text.c_str());
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::ProductIDExit(TObject *Sender)
{
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::SerialIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetSerialID(TextToDecimal(SerialID->Text.c_str(), 0));
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::SerialIDExit(TObject *Sender)
{
	Refresh(TopologyIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::EnclosuresRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	TiledDisplayTopology->SetPhysicalEnclosures(RadioButton->Tag);
	Refresh(PhysicalEnclosuresGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::SingleTileBehaviorRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	TiledDisplayTopology->SetSingleTileBehavior(RadioButton->Tag);
	Refresh(SingleTileBehaviorGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::MultipleTileBehaviorRadioButtonClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	TiledDisplayTopology->SetMultipleTileBehavior(RadioButton->Tag);
	Refresh(MultipleTileBehaviorGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HTilesChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetHTiles(TextToInteger(HTiles->Text.c_str()));
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HTilesExit(TObject *Sender)
{
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VTilesChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVTiles(TextToInteger(VTiles->Text.c_str()));
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VTilesExit(TObject *Sender)
{
	Refresh(TilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HLocationChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetHLocation(TextToInteger(HLocation->Text.c_str()));
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HLocationExit(TObject *Sender)
{
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VLocationChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVLocation(TextToInteger(VLocation->Text.c_str()));
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VLocationExit(TObject *Sender)
{
	Refresh(LocationGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetHSize(TextToInteger(HSize->Text.c_str()));
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::HSizeExit(TObject *Sender)
{
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetVSize(TextToInteger(VSize->Text.c_str()));
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::VSizeExit(TObject *Sender)
{
	Refresh(SizeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::PixelMultiplierChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetPixelMultiplier(TextToInteger(PixelMultiplier->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::PixelMultiplierExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::TopBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetTopBezelSize(TextToInteger(TopBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::TopBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::LeftBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetLeftBezelSize(TextToInteger(LeftBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::LeftBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::RightBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetRightBezelSize(TextToInteger(RightBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::RightBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::BottomBezelSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TiledDisplayTopology->SetBottomBezelSize(TextToInteger(BottomBezelSize->Text.c_str()));
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TTiledDisplayTopologyForm::BottomBezelSizeExit(TObject *Sender)
{
	Refresh(BezelGroupBox);
}
//---------------------------------------------------------------------------
