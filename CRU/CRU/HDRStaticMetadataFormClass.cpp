//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "HDRStaticMetadataFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
THDRStaticMetadataForm *HDRStaticMetadataForm;
//---------------------------------------------------------------------------
__fastcall THDRStaticMetadataForm::THDRStaticMetadataForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::Connect(HDRStaticMetadataClass &NewHDRStaticMetadata)
{
	HDRStaticMetadata = &NewHDRStaticMetadata;
	return true;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == EOTFGroupBox)
		RefreshEOTFCheckBoxes();

	if (Value == NULL || Value == TypeGroupBox)
		RefreshTypeCheckBoxes();

	if (Value == NULL || Value == LuminanceGroupBox)
	{
		RefreshLuminanceCaption();
		RefreshLuminanceTextBoxes();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = HDRStaticMetadata->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::RefreshEOTFCheckBoxes()
{
	EOTFCheckBox0->Checked = HDRStaticMetadata->GetEOTF(0);
	EOTFCheckBox1->Checked = HDRStaticMetadata->GetEOTF(1);
	EOTFCheckBox2->Checked = HDRStaticMetadata->GetEOTF(2);
	EOTFCheckBox3->Checked = HDRStaticMetadata->GetEOTF(3);
	return true;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::RefreshTypeCheckBoxes()
{
	TypeCheckBox0->Checked = HDRStaticMetadata->GetType(0);
	return true;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::RefreshLuminanceCaption()
{
	if (HDRStaticMetadata->LuminancePossible(2))
		LuminanceGroupBox->Caption = " Luminance ";
	else if (HDRStaticMetadata->LuminancePossible(1))
		LuminanceGroupBox->Caption = " Luminance (2 bytes left) ";
	else if (HDRStaticMetadata->LuminancePossible(0))
		LuminanceGroupBox->Caption = " Luminance (1 byte left) ";
	else
		LuminanceGroupBox->Caption = " Luminance (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::RefreshLuminanceTextBoxes()
{
	char Text[TEXTSIZE];

	if (HDRStaticMetadata->LuminancePossible(0))
	{
		LuminanceLabel0->Font->Color = clWindowText;
		Luminance0->Enabled = true;
		Luminance0->Color = clWindow;
		Luminance0->Font->Color = GetTextColor(HDRStaticMetadata->IsValidLuminance(0));
	}
	else
	{
		LuminanceLabel0->Font->Color = clGrayText;
		Luminance0->Enabled = false;
		Luminance0->Color = clBtnFace;
		Luminance0->Font->Color = clGrayText;
	}

	if (!Luminance0->Focused() && IntegerToText(HDRStaticMetadata->GetLuminance(0), Text, TEXTSIZE))
		Luminance0->Text = Text;

	if (HDRStaticMetadata->LuminancePossible(1))
	{
		LuminanceLabel1->Font->Color = clWindowText;
		Luminance1->Enabled = true;
		Luminance1->Color = clWindow;
		Luminance1->Font->Color = GetTextColor(HDRStaticMetadata->IsValidLuminance(1));
	}
	else
	{
		LuminanceLabel1->Font->Color = clGrayText;
		Luminance1->Enabled = false;
		Luminance1->Color = clBtnFace;
		Luminance1->Font->Color = clGrayText;
	}

	if (!Luminance1->Focused() && IntegerToText(HDRStaticMetadata->GetLuminance(1), Text, TEXTSIZE))
		Luminance1->Text = Text;

	if (HDRStaticMetadata->LuminancePossible(2))
	{
		LuminanceLabel2->Font->Color = clWindowText;
		Luminance2->Enabled = true;
		Luminance2->Color = clWindow;
		Luminance2->Font->Color = GetTextColor(HDRStaticMetadata->IsValidLuminance(2));
	}
	else
	{
		LuminanceLabel2->Font->Color = clGrayText;
		Luminance2->Enabled = false;
		Luminance2->Color = clBtnFace;
		Luminance2->Font->Color = clGrayText;
	}

	if (!Luminance2->Focused() && IntegerToText(HDRStaticMetadata->GetLuminance(2), Text, TEXTSIZE))
		Luminance2->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDRStaticMetadataForm::ScaleControls()
{
	EOTFCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(EOTFCheckBox0->Caption);
	EOTFCheckBox0->Height = CheckBoxHeight;
	EOTFCheckBox0->Left = PaddingWidth;
	EOTFCheckBox0->Top = PaddingTop + CheckBoxTop;

	EOTFCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(EOTFCheckBox1->Caption);
	EOTFCheckBox1->Height = CheckBoxHeight;
	EOTFCheckBox1->Left = EOTFCheckBox0->Left;
	EOTFCheckBox1->Top = EOTFCheckBox0->Top + EOTFCheckBox0->Height + CheckBoxSpacing;

	EOTFCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(EOTFCheckBox2->Caption);
	EOTFCheckBox2->Height = CheckBoxHeight;
	EOTFCheckBox2->Left = EOTFCheckBox1->Left;
	EOTFCheckBox2->Top = EOTFCheckBox1->Top + EOTFCheckBox1->Height + CheckBoxSpacing;

	EOTFCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(EOTFCheckBox3->Caption);
	EOTFCheckBox3->Height = CheckBoxHeight;
	EOTFCheckBox3->Left = EOTFCheckBox2->Left;
	EOTFCheckBox3->Top = EOTFCheckBox2->Top + EOTFCheckBox2->Height + CheckBoxSpacing;

	EOTFGroupBox->Width = FormButtonsWidth;
	EOTFGroupBox->Height = EOTFCheckBox3->Top + EOTFCheckBox3->Height + CheckBoxBottom + PaddingBottom;
	EOTFGroupBox->Left = Scale;
	EOTFGroupBox->Top = GroupBoxTop;

	TypeCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(TypeCheckBox0->Caption);
	TypeCheckBox0->Height = CheckBoxHeight;
	TypeCheckBox0->Left = PaddingWidth;
	TypeCheckBox0->Top = PaddingTop + CheckBoxTop;

	TypeGroupBox->Width = EOTFGroupBox->Width;
	TypeGroupBox->Height = TypeCheckBox0->Top + TypeCheckBox0->Height + CheckBoxBottom + PaddingBottom;
	TypeGroupBox->Left = EOTFGroupBox->Left;
	TypeGroupBox->Top = EOTFGroupBox->Top + EOTFGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	Luminance0->AutoSize = false;
	Luminance0->Width = Luminance0->MaxLength * NumberWidth + TextBoxPadding;
	Luminance0->Height = TextBoxHeight;

	Luminance1->AutoSize = false;
	Luminance1->Width = Luminance1->MaxLength * NumberWidth + TextBoxPadding;
	Luminance1->Height = TextBoxHeight;

	Luminance2->AutoSize = false;
	Luminance2->Width = Luminance2->MaxLength * NumberWidth + TextBoxPadding;
	Luminance2->Height = TextBoxHeight;

	LuminanceLabel0->Left = PaddingWidth;
	LuminanceLabel1->Left = LuminanceLabel0->Left;
	LuminanceLabel2->Left = LuminanceLabel1->Left;

	Luminance0->Left = LuminanceLabel1->Left + LuminanceLabel1->Width + LabelSpacing;
	Luminance1->Left = Luminance0->Left;
	Luminance2->Left = Luminance1->Left;

	Luminance0->Top = PaddingTop;
	Luminance1->Top = Luminance0->Top + Luminance0->Height + TextBoxSpacing;
	Luminance2->Top = Luminance1->Top + Luminance1->Height + TextBoxSpacing;

	LuminanceLabel0->Top = Luminance0->Top + 3;
	LuminanceLabel1->Top = Luminance1->Top + 3;
	LuminanceLabel2->Top = Luminance2->Top + 3;

	LuminanceGroupBox->Width = TypeGroupBox->Width;
	LuminanceGroupBox->Height = Luminance2->Top + Luminance2->Height + PaddingBottom;
	LuminanceGroupBox->Left = TypeGroupBox->Left;
	LuminanceGroupBox->Top = TypeGroupBox->Top + TypeGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = LuminanceGroupBox->Top + LuminanceGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = LuminanceGroupBox->Left + LuminanceGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall THDRStaticMetadataForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall THDRStaticMetadataForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall THDRStaticMetadataForm::EOTFCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDRStaticMetadata->SetEOTF(CheckBox->Tag, CheckBox->Checked);
	Refresh(EOTFGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDRStaticMetadataForm::TypeCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDRStaticMetadata->SetType(CheckBox->Tag, CheckBox->Checked);
	Refresh(TypeGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDRStaticMetadataForm::LuminanceChange(TObject *Sender)
{
	if (Refreshing)
		return;

	TEdit *Luminance = (TEdit *)Sender;
	HDRStaticMetadata->SetLuminance(Luminance->Tag, TextToInteger(Luminance->Text.c_str()));
	Refresh(LuminanceGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDRStaticMetadataForm::LuminanceExit(TObject *Sender)
{
	Refresh(LuminanceGroupBox);
}
//---------------------------------------------------------------------------
