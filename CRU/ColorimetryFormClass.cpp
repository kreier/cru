//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "ColorimetryFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TColorimetryForm *ColorimetryForm;
//---------------------------------------------------------------------------
__fastcall TColorimetryForm::TColorimetryForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::Connect(ColorimetryClass &NewColorimetry)
{
	Colorimetry = &NewColorimetry;
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == ColorimetryGroupBox)
		RefreshColorimetryCheckBoxes();

	if (Value == NULL || Value == MetadataGroupBox)
		RefreshMetadataCheckBoxes();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::RefreshColorimetryCheckBoxes()
{
	ColorimetryCheckBox0->Checked = Colorimetry->Get(0);
	ColorimetryCheckBox1->Checked = Colorimetry->Get(1);
	ColorimetryCheckBox2->Checked = Colorimetry->Get(2);
	ColorimetryCheckBox3->Checked = Colorimetry->Get(3);
	ColorimetryCheckBox4->Checked = Colorimetry->Get(4);
	ColorimetryCheckBox5->Checked = Colorimetry->Get(5);
	ColorimetryCheckBox6->Checked = Colorimetry->Get(6);
	ColorimetryCheckBox7->Checked = Colorimetry->Get(7);
	ColorimetryCheckBox15->Checked = Colorimetry->Get(15);
	ColorimetryCheckBox14->Checked = Colorimetry->Get(14);
	ColorimetryCheckBox13->Checked = Colorimetry->Get(13);
	ColorimetryCheckBox12->Checked = Colorimetry->Get(12);
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::RefreshMetadataCheckBoxes()
{
	MetadataCheckBox0->Checked = Colorimetry->Get(8);
	MetadataCheckBox1->Checked = Colorimetry->Get(9);
	MetadataCheckBox2->Checked = Colorimetry->Get(10);
	MetadataCheckBox3->Checked = Colorimetry->Get(11);
	return true;
}
//---------------------------------------------------------------------------
bool TColorimetryForm::ScaleControls()
{
	ColorimetryCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox0->Caption);
	ColorimetryCheckBox0->Height = CheckBoxHeight;
	ColorimetryCheckBox0->Left = PaddingWidth;
	ColorimetryCheckBox0->Top = PaddingTop + CheckBoxTop;

	ColorimetryCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox1->Caption);
	ColorimetryCheckBox1->Height = CheckBoxHeight;
	ColorimetryCheckBox1->Left = ColorimetryCheckBox0->Left;
	ColorimetryCheckBox1->Top = ColorimetryCheckBox0->Top + ColorimetryCheckBox0->Height + CheckBoxSpacing;

	ColorimetryCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox2->Caption);
	ColorimetryCheckBox2->Height = CheckBoxHeight;
	ColorimetryCheckBox2->Left = ColorimetryCheckBox1->Left;
	ColorimetryCheckBox2->Top = ColorimetryCheckBox1->Top + ColorimetryCheckBox1->Height + CheckBoxSpacing;

	ColorimetryCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox3->Caption);
	ColorimetryCheckBox3->Height = CheckBoxHeight;
	ColorimetryCheckBox3->Left = ColorimetryCheckBox2->Left;
	ColorimetryCheckBox3->Top = ColorimetryCheckBox2->Top + ColorimetryCheckBox2->Height + CheckBoxSpacing;

	ColorimetryCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox4->Caption);
	ColorimetryCheckBox4->Height = CheckBoxHeight;
	ColorimetryCheckBox4->Left = ColorimetryCheckBox3->Left;
	ColorimetryCheckBox4->Top = ColorimetryCheckBox3->Top + ColorimetryCheckBox3->Height + CheckBoxSpacing;

	ColorimetryCheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox5->Caption);
	ColorimetryCheckBox5->Height = CheckBoxHeight;
	ColorimetryCheckBox5->Left = ColorimetryCheckBox4->Left;
	ColorimetryCheckBox5->Top = ColorimetryCheckBox4->Top + ColorimetryCheckBox4->Height + CheckBoxSpacing;

	ColorimetryCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox6->Caption);
	ColorimetryCheckBox6->Height = CheckBoxHeight;
	ColorimetryCheckBox6->Left = ColorimetryCheckBox5->Left;
	ColorimetryCheckBox6->Top = ColorimetryCheckBox5->Top + ColorimetryCheckBox5->Height + CheckBoxSpacing;

	ColorimetryCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox7->Caption);
	ColorimetryCheckBox7->Height = CheckBoxHeight;
	ColorimetryCheckBox7->Left = ColorimetryCheckBox6->Left;
	ColorimetryCheckBox7->Top = ColorimetryCheckBox6->Top + ColorimetryCheckBox6->Height + CheckBoxSpacing;

	ColorimetryCheckBox15->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox15->Caption);
	ColorimetryCheckBox15->Height = CheckBoxHeight;
	ColorimetryCheckBox15->Left = ColorimetryCheckBox7->Left;
	ColorimetryCheckBox15->Top = ColorimetryCheckBox7->Top + ColorimetryCheckBox7->Height + CheckBoxSpacing;

	ColorimetryCheckBox14->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox14->Caption);
	ColorimetryCheckBox14->Height = CheckBoxHeight;
	ColorimetryCheckBox14->Left = ColorimetryCheckBox15->Left;
	ColorimetryCheckBox14->Top = ColorimetryCheckBox15->Top + ColorimetryCheckBox15->Height + CheckBoxSpacing;

	ColorimetryCheckBox13->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox13->Caption);
	ColorimetryCheckBox13->Height = CheckBoxHeight;
	ColorimetryCheckBox13->Left = ColorimetryCheckBox14->Left;
	ColorimetryCheckBox13->Top = ColorimetryCheckBox14->Top + ColorimetryCheckBox14->Height + CheckBoxSpacing;

	ColorimetryCheckBox12->Width = CheckBoxWidth + Canvas->TextWidth(ColorimetryCheckBox12->Caption);
	ColorimetryCheckBox12->Height = CheckBoxHeight;
	ColorimetryCheckBox12->Left = ColorimetryCheckBox13->Left;
	ColorimetryCheckBox12->Top = ColorimetryCheckBox13->Top + ColorimetryCheckBox13->Height + CheckBoxSpacing;

	ColorimetryGroupBox->Width = FormButtonsWidth;
	ColorimetryGroupBox->Height = ColorimetryCheckBox12->Top + ColorimetryCheckBox12->Height + CheckBoxBottom + PaddingBottom;
	ColorimetryGroupBox->Left = Scale;
	ColorimetryGroupBox->Top = GroupBoxTop;

	MetadataCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox0->Caption);
	MetadataCheckBox0->Height = CheckBoxHeight;
	MetadataCheckBox0->Left = PaddingWidth;
	MetadataCheckBox0->Top = PaddingTop + CheckBoxTop;

	MetadataCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox1->Caption);
	MetadataCheckBox1->Height = CheckBoxHeight;
	MetadataCheckBox1->Left = MetadataCheckBox0->Left;
	MetadataCheckBox1->Top = MetadataCheckBox0->Top + MetadataCheckBox0->Height + CheckBoxSpacing;

	MetadataCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox2->Caption);
	MetadataCheckBox2->Height = CheckBoxHeight;
	MetadataCheckBox2->Left = MetadataCheckBox1->Left;
	MetadataCheckBox2->Top = MetadataCheckBox1->Top + MetadataCheckBox1->Height + CheckBoxSpacing;

	MetadataCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(MetadataCheckBox3->Caption);
	MetadataCheckBox3->Height = CheckBoxHeight;
	MetadataCheckBox3->Left = MetadataCheckBox2->Left;
	MetadataCheckBox3->Top = MetadataCheckBox2->Top + MetadataCheckBox2->Height + CheckBoxSpacing;

	MetadataGroupBox->Width = ColorimetryGroupBox->Width;
	MetadataGroupBox->Height = MetadataCheckBox3->Top + MetadataCheckBox3->Height + CheckBoxBottom + PaddingBottom;
	MetadataGroupBox->Left = ColorimetryGroupBox->Left;
	MetadataGroupBox->Top = ColorimetryGroupBox->Top + ColorimetryGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = MetadataGroupBox->Top + MetadataGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = MetadataGroupBox->Left + MetadataGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::FormShow(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::ColorimetryCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	Colorimetry->Set(CheckBox->Tag, CheckBox->Checked);
	Refresh(ColorimetryGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TColorimetryForm::MetadataCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	Colorimetry->Set(CheckBox->Tag, CheckBox->Checked);
	Refresh(MetadataGroupBox);
}
//---------------------------------------------------------------------------
