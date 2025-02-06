//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "HDMI2SupportFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
THDMI2SupportForm *HDMI2SupportForm;
//---------------------------------------------------------------------------
__fastcall THDMI2SupportForm::THDMI2SupportForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::Connect(HDMI2SupportClass &NewHDMI2Support)
{
	HDMI2Support = &NewHDMI2Support;
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::Refresh(void *Value)
{
	Refreshing = true;

	if (Value == NULL || Value == TMDSRateGroupBox)
	{
		RefreshTMDSRateCheckBox();
		RefreshTMDSRateTextBox();
	}

	if (Value == NULL || Value == FeaturesGroupBox)
		RefreshFeaturesCheckBoxes();

	if (Value == NULL || Value == ColorFormatsGroupBox)
		RefreshColorFormatsCheckBoxes();

	if (Value == NULL || Value == FRLRateComboBox)
		RefreshFRLRateComboBox();

	if (Value == NULL || Value == Features21GroupBox)
	{
		RefreshFeatures21Caption();
		RefreshFeatures21CheckBoxes();
	}

	if (Value == NULL || Value == RefreshRateGroupBox)
	{
		RefreshRefreshRateCaption();
		RefreshRefreshRateTextBoxes();
	}

	if (Value == NULL || Value == DSCGroupBox)
	{
		RefreshDSCCaption();
		RefreshDSCCheckBoxes();
		RefreshDSCFRLRateComboBox();
		RefreshDSCSlicesComboBox();
		RefreshDSCChunkSizeTextBox();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = HDMI2Support->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshTMDSRateCheckBox()
{
	OverrideTMDSRate->Checked = HDMI2Support->GetOverrideTMDSRate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshTMDSRateTextBox()
{
	char Text[TEXTSIZE];

	if (HDMI2Support->GetOverrideTMDSRate())
	{
		TMDSRate->Enabled = true;
		TMDSRate->Color = clWindow;
		TMDSRate->Font->Color = GetTextColor(HDMI2Support->IsValidTMDSRate());
		TMDSRateLabel->Font->Color = clWindowText;
	}
	else
	{
		TMDSRate->Enabled = false;
		TMDSRate->Color = clBtnFace;
		TMDSRate->Font->Color = clGrayText;
		TMDSRateLabel->Font->Color = clGrayText;
	}

	if (!TMDSRate->Focused() && IntegerToText(HDMI2Support->GetTMDSRate(), Text, TEXTSIZE))
		TMDSRate->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshFeaturesCheckBoxes()
{
	FeaturesCheckBox7->Checked = HDMI2Support->GetFeature(7);
	FeaturesCheckBox6->Checked = HDMI2Support->GetFeature(6);
	FeaturesCheckBox4->Checked = HDMI2Support->GetFeature(4);
	FeaturesCheckBox3->Checked = HDMI2Support->GetFeature(3);
	FeaturesCheckBox2->Checked = HDMI2Support->GetFeature(2);
	FeaturesCheckBox1->Checked = HDMI2Support->GetFeature(1);
	FeaturesCheckBox0->Checked = HDMI2Support->GetFeature(0);
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshColorFormatsCheckBoxes()
{
	ColorFormatsCheckBox0->Checked = HDMI2Support->GetColorFormat(0);
	ColorFormatsCheckBox1->Checked = HDMI2Support->GetColorFormat(1);
	ColorFormatsCheckBox2->Checked = HDMI2Support->GetColorFormat(2);
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshFRLRateComboBox()
{
	FRLRateComboBox->ItemIndex = HDMI2Support->GetFRLRate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshFeatures21Caption()
{
	if (HDMI2Support->Features21Possible())
		Features21GroupBox->Caption = " 2.1 features ";
	else
		Features21GroupBox->Caption = " 2.1 features (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshFeatures21CheckBoxes()
{
	if (HDMI2Support->Features21Possible())
	{
		Features21CheckBox5->Enabled = true;
		Features21CheckBox4->Enabled = true;
		Features21CheckBox3->Enabled = true;
		Features21CheckBox2->Enabled = true;
		Features21CheckBox1->Enabled = true;
		Features21CheckBox0->Enabled = true;
	}
	else
	{
		Features21CheckBox5->Enabled = false;
		Features21CheckBox4->Enabled = false;
		Features21CheckBox3->Enabled = false;
		Features21CheckBox2->Enabled = false;
		Features21CheckBox1->Enabled = false;
		Features21CheckBox0->Enabled = false;
	}

	Features21CheckBox5->Checked = HDMI2Support->GetFeature21(5);
	Features21CheckBox4->Checked = HDMI2Support->GetFeature21(4);
	Features21CheckBox3->Checked = HDMI2Support->GetFeature21(3);
	Features21CheckBox2->Checked = HDMI2Support->GetFeature21(2);
	Features21CheckBox1->Checked = HDMI2Support->GetFeature21(1);
	Features21CheckBox0->Checked = HDMI2Support->GetFeature21(0);
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshRefreshRateCaption()
{
	if (HDMI2Support->RefreshRatePossible())
		RefreshRateGroupBox->Caption = " Variable refresh rate ";
	else if (HDMI2Support->Features21Possible())
		RefreshRateGroupBox->Caption = " VRR (no space for range) ";
	else
		RefreshRateGroupBox->Caption = " VRR (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshRefreshRateTextBoxes()
{
	char Text[TEXTSIZE];

	if (HDMI2Support->RefreshRatePossible())
	{
		VRateLabel->Font->Color = clWindowText;
		MinVRate->Enabled = true;
		VRateDash->Pen->Color = clWindowText;
		MaxVRate->Enabled = true;
		HzLabel->Font->Color = clWindowText;
	}
	else
	{
		VRateLabel->Font->Color = clGrayText;
		MinVRate->Enabled = false;
		VRateDash->Pen->Color = clGrayText;
		MaxVRate->Enabled = false;
		HzLabel->Font->Color = clGrayText;
	}

	MinVRate->Font->Color = GetTextColor(HDMI2Support->IsValidMinRefreshRate());

	if (!MinVRate->Focused() && IntegerToText(HDMI2Support->GetMinRefreshRate(), Text, TEXTSIZE))
		MinVRate->Text = Text;

	MaxVRate->Font->Color = GetTextColor(HDMI2Support->IsValidMaxRefreshRate());

	if (!MaxVRate->Focused() && IntegerToText(HDMI2Support->GetMaxRefreshRate(), Text, TEXTSIZE))
		MaxVRate->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshDSCCaption()
{
	if (HDMI2Support->DSCPossible())
		DSCGroupBox->Caption = " Display stream compression ";
	else
		DSCGroupBox->Caption = " DSC (no space left) ";

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshDSCCheckBoxes()
{
	if (HDMI2Support->DSCPossible())
	{
		DSCCheckBox7->Enabled = true;
		DSCCheckBox6->Enabled = true;
		DSCCheckBox0->Enabled = true;
		DSCCheckBox1->Enabled = true;
		DSCCheckBox2->Enabled = true;
		DSCCheckBox3->Enabled = true;
	}
	else
	{
		DSCCheckBox7->Enabled = false;
		DSCCheckBox6->Enabled = false;
		DSCCheckBox0->Enabled = false;
		DSCCheckBox1->Enabled = false;
		DSCCheckBox2->Enabled = false;
		DSCCheckBox3->Enabled = false;
	}

	DSCCheckBox7->Checked = HDMI2Support->GetDSCFeature(7);
	DSCCheckBox6->Checked = HDMI2Support->GetDSCFeature(6);
	DSCCheckBox0->Checked = HDMI2Support->GetDSCFeature(0);
	DSCCheckBox1->Checked = HDMI2Support->GetDSCFeature(1);
	DSCCheckBox2->Checked = HDMI2Support->GetDSCFeature(2);
	DSCCheckBox3->Checked = HDMI2Support->GetDSCFeature(3);
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshDSCFRLRateComboBox()
{
	if (HDMI2Support->DSCPossible())
	{
		DSCFRLRateLabel->Font->Color = clWindowText;
		DSCFRLRateComboBox->Enabled = true;
	}
	else
	{
		DSCFRLRateLabel->Font->Color = clGrayText;
		DSCFRLRateComboBox->Enabled = false;
	}

	DSCFRLRateComboBox->ItemIndex = HDMI2Support->GetDSCFRLRate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshDSCSlicesComboBox()
{
	if (HDMI2Support->DSCPossible())
	{
		DSCSlicesLabel->Font->Color = clWindowText;
		DSCSlicesComboBox->Enabled = true;
	}
	else
	{
		DSCSlicesLabel->Font->Color = clGrayText;
		DSCSlicesComboBox->Enabled = false;
	}

	DSCSlicesComboBox->ItemIndex = HDMI2Support->GetDSCSlices();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::RefreshDSCChunkSizeTextBox()
{
	char Text[TEXTSIZE];

	if (HDMI2Support->DSCPossible())
	{
		DSCChunkSizeLabel->Font->Color = clWindowText;
		DSCChunkSize->Enabled = true;
		DSCChunkSizeUnitsLabel->Font->Color = clWindowText;
	}
	else
	{
		DSCChunkSizeLabel->Font->Color = clGrayText;
		DSCChunkSize->Enabled = false;
		DSCChunkSizeUnitsLabel->Font->Color = clGrayText;
	}

	DSCChunkSize->Font->Color = GetTextColor(HDMI2Support->IsValidDSCChunkSize());

	if (!DSCChunkSize->Focused() && IntegerToText(HDMI2Support->GetDSCChunkSize(), Text, TEXTSIZE))
		DSCChunkSize->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::InitFRLRateComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = FRLRateComboBox->ItemIndex;
	FRLRateComboBox->Items->BeginUpdate();
	FRLRateComboBox->Clear();

	for (Index = 0; HDMI2Support->GetFRLRateText(Index, Text, TEXTSIZE); Index++)
		FRLRateComboBox->Items->Add(Text);

	FRLRateComboBox->ItemIndex = ItemIndex;
	FRLRateComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::InitDSCFRLRateComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = DSCFRLRateComboBox->ItemIndex;
	DSCFRLRateComboBox->Items->BeginUpdate();
	DSCFRLRateComboBox->Clear();

	for (Index = 0; HDMI2Support->GetFRLRateText(Index, Text, TEXTSIZE); Index++)
		DSCFRLRateComboBox->Items->Add(Text);

	DSCFRLRateComboBox->ItemIndex = ItemIndex;
	DSCFRLRateComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::InitDSCSlicesComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = DSCSlicesComboBox->ItemIndex;
	DSCSlicesComboBox->Items->BeginUpdate();
	DSCSlicesComboBox->Clear();

	for (Index = 0; HDMI2Support->GetDSCSlicesText(Index, Text, TEXTSIZE); Index++)
		DSCSlicesComboBox->Items->Add(Text);

	DSCSlicesComboBox->ItemIndex = ItemIndex;
	DSCSlicesComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool THDMI2SupportForm::ScaleControls()
{
	OverrideTMDSRate->Width = CheckBoxWidth + Canvas->TextWidth(OverrideTMDSRate->Caption);
	OverrideTMDSRate->Height = CheckBoxHeight;

	TMDSRate->AutoSize = false;
	TMDSRate->Width = TMDSRate->MaxLength * NumberWidth + TextBoxPadding;
	TMDSRate->Height = TextBoxHeight;

	OverrideTMDSRate->Left = PaddingWidth;
	TMDSRate->Left = OverrideTMDSRate->Left + OverrideTMDSRate->Width + CheckBoxRight + LabelSpacing;
	TMDSRateLabel->Left = TMDSRate->Left + TMDSRate->Width + PostLabelSpacing;

	TMDSRate->Top = PaddingTop;
	OverrideTMDSRate->Top = TMDSRate->Top + 3 + CheckBoxTop;
	TMDSRateLabel->Top = TMDSRate->Top + 3;

	TMDSRateGroupBox->Width = FormButtonsWidth;
	TMDSRateGroupBox->Height = TMDSRate->Top + TMDSRate->Height + PaddingBottom;
	TMDSRateGroupBox->Left = Scale;
	TMDSRateGroupBox->Top = GroupBoxTop;

	FeaturesCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox7->Caption);
	FeaturesCheckBox7->Height = CheckBoxHeight;
	FeaturesCheckBox7->Left = PaddingWidth;
	FeaturesCheckBox7->Top = PaddingTop + CheckBoxTop;

	FeaturesCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox6->Caption);
	FeaturesCheckBox6->Height = CheckBoxHeight;
	FeaturesCheckBox6->Left = FeaturesCheckBox7->Left;
	FeaturesCheckBox6->Top = FeaturesCheckBox7->Top + FeaturesCheckBox7->Height + CheckBoxSpacing;

	FeaturesCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox4->Caption);
	FeaturesCheckBox4->Height = CheckBoxHeight;
	FeaturesCheckBox4->Left = FeaturesCheckBox6->Left;
	FeaturesCheckBox4->Top = FeaturesCheckBox6->Top + FeaturesCheckBox6->Height + CheckBoxSpacing;

	FeaturesCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox3->Caption);
	FeaturesCheckBox3->Height = CheckBoxHeight;
	FeaturesCheckBox3->Left = FeaturesCheckBox4->Left;
	FeaturesCheckBox3->Top = FeaturesCheckBox4->Top + FeaturesCheckBox4->Height + CheckBoxSpacing;

	FeaturesCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox2->Caption);
	FeaturesCheckBox2->Height = CheckBoxHeight;
	FeaturesCheckBox2->Left = FeaturesCheckBox3->Left;
	FeaturesCheckBox2->Top = FeaturesCheckBox3->Top + FeaturesCheckBox3->Height + CheckBoxSpacing;

	FeaturesCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox1->Caption);
	FeaturesCheckBox1->Height = CheckBoxHeight;
	FeaturesCheckBox1->Left = FeaturesCheckBox2->Left;
	FeaturesCheckBox1->Top = FeaturesCheckBox2->Top + FeaturesCheckBox2->Height + CheckBoxSpacing;

	FeaturesCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(FeaturesCheckBox0->Caption);
	FeaturesCheckBox0->Height = CheckBoxHeight;
	FeaturesCheckBox0->Left = FeaturesCheckBox1->Left;
	FeaturesCheckBox0->Top = FeaturesCheckBox1->Top + FeaturesCheckBox1->Height + CheckBoxSpacing;

	FeaturesGroupBox->Width = TMDSRateGroupBox->Width;
	FeaturesGroupBox->Height = FeaturesCheckBox0->Top + FeaturesCheckBox0->Height + CheckBoxBottom + PaddingBottom;
	FeaturesGroupBox->Left = TMDSRateGroupBox->Left;
	FeaturesGroupBox->Top = TMDSRateGroupBox->Top + TMDSRateGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	ColorFormatsCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(ColorFormatsCheckBox0->Caption);
	ColorFormatsCheckBox0->Height = CheckBoxHeight;
	ColorFormatsCheckBox0->Left = PaddingWidth;
	ColorFormatsCheckBox0->Top = PaddingTop + CheckBoxTop;

	ColorFormatsCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(ColorFormatsCheckBox1->Caption);
	ColorFormatsCheckBox1->Height = CheckBoxHeight;
	ColorFormatsCheckBox1->Left = ColorFormatsCheckBox0->Left;
	ColorFormatsCheckBox1->Top = ColorFormatsCheckBox0->Top + ColorFormatsCheckBox0->Height + CheckBoxSpacing;

	ColorFormatsCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(ColorFormatsCheckBox2->Caption);
	ColorFormatsCheckBox2->Height = CheckBoxHeight;
	ColorFormatsCheckBox2->Left = ColorFormatsCheckBox1->Left;
	ColorFormatsCheckBox2->Top = ColorFormatsCheckBox1->Top + ColorFormatsCheckBox1->Height + CheckBoxSpacing;

	ColorFormatsGroupBox->Width = FeaturesGroupBox->Width;
	ColorFormatsGroupBox->Height = ColorFormatsCheckBox2->Top + ColorFormatsCheckBox2->Height + CheckBoxBottom + PaddingBottom;
	ColorFormatsGroupBox->Left = FeaturesGroupBox->Left;
	ColorFormatsGroupBox->Top = FeaturesGroupBox->Top + FeaturesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	int DashWidth = NumberWidth;
	int DashHeight = Text.tmHeight < 22 ? 1 : (Text.tmHeight + 13) / 16;
	int DashSpacing = NumberWidth;

	MinVRate->AutoSize = false;
	MinVRate->Width = TextBoxHeight;
	MinVRate->Height = TextBoxHeight;

	VRateDash->Width = DashWidth;
	VRateDash->Height = DashHeight;

	MaxVRate->AutoSize = false;
	MaxVRate->Width = MaxVRate->MaxLength * NumberWidth + TextBoxPadding;
	MaxVRate->Height = TextBoxHeight;

	VRateLabel->Left = PaddingWidth;
	MinVRate->Left = VRateLabel->Left + VRateLabel->Width + LabelSpacing;
	VRateDash->Left = MinVRate->Left + MinVRate->Width + DashSpacing;
	MaxVRate->Left = VRateDash->Left + VRateDash->Width + DashSpacing;
	HzLabel->Left = MaxVRate->Left + MaxVRate->Width + PostLabelSpacing;

	MinVRate->Top = PaddingTop;
	MaxVRate->Top = MinVRate->Top;

	VRateLabel->Top = MinVRate->Top + 3;
	VRateDash->Top = MinVRate->Top + MinVRate->Height / 2;
	HzLabel->Top = VRateLabel->Top;

	Features21CheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(Features21CheckBox5->Caption);
	Features21CheckBox5->Height = CheckBoxHeight;
	Features21CheckBox5->Left = VRateLabel->Left;
	Features21CheckBox5->Top = MinVRate->Top + MinVRate->Height + Scale + CheckBoxTop;

	Features21CheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(Features21CheckBox4->Caption);
	Features21CheckBox4->Height = CheckBoxHeight;
	Features21CheckBox4->Left = Features21CheckBox5->Left;
	Features21CheckBox4->Top = Features21CheckBox5->Top + Features21CheckBox5->Height + CheckBoxSpacing;

	Features21CheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(Features21CheckBox3->Caption);
	Features21CheckBox3->Height = CheckBoxHeight;
	Features21CheckBox3->Left = Features21CheckBox4->Left;
	Features21CheckBox3->Top = Features21CheckBox4->Top + Features21CheckBox4->Height + CheckBoxSpacing;

	RefreshRateGroupBox->Width = ColorFormatsGroupBox->Width;
	RefreshRateGroupBox->Height = Features21CheckBox3->Top + Features21CheckBox3->Height + CheckBoxBottom + PaddingBottom;
	RefreshRateGroupBox->Left = ColorFormatsGroupBox->Left;
	RefreshRateGroupBox->Top = ColorFormatsGroupBox->Top + ColorFormatsGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FRLRateComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	FRLRateComboBox->Height = ComboBoxHeight;
	FRLRateComboBox->Left = PaddingWidth;
	FRLRateComboBox->Top = PaddingTop;

	FRLRateGroupBox->Width = TMDSRateGroupBox->Width;
	FRLRateGroupBox->Height = FRLRateComboBox->Top + FRLRateComboBox->Height + PaddingBottom;
	FRLRateGroupBox->Left = TMDSRateGroupBox->Left + TMDSRateGroupBox->Width + Scale;
	FRLRateGroupBox->Top = TMDSRateGroupBox->Top;

	Features21CheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(Features21CheckBox2->Caption);
	Features21CheckBox2->Height = CheckBoxHeight;
	Features21CheckBox2->Left = PaddingWidth;
	Features21CheckBox2->Top = PaddingTop + CheckBoxTop;

	Features21CheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(Features21CheckBox1->Caption);
	Features21CheckBox1->Height = CheckBoxHeight;
	Features21CheckBox1->Left = Features21CheckBox2->Left;
	Features21CheckBox1->Top = Features21CheckBox2->Top + Features21CheckBox2->Height + CheckBoxSpacing;

	Features21CheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(Features21CheckBox0->Caption);
	Features21CheckBox0->Height = CheckBoxHeight;
	Features21CheckBox0->Left = Features21CheckBox1->Left;
	Features21CheckBox0->Top = Features21CheckBox1->Top + Features21CheckBox1->Height + CheckBoxSpacing;

	Features21GroupBox->Width = FRLRateGroupBox->Width;
	Features21GroupBox->Height = Features21CheckBox0->Top + Features21CheckBox0->Height + CheckBoxBottom + PaddingBottom;
	Features21GroupBox->Left = FRLRateGroupBox->Left;
	Features21GroupBox->Top = FRLRateGroupBox->Top + FRLRateGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	DSCCheckBox7->Width = CheckBoxWidth + Canvas->TextWidth(DSCCheckBox7->Caption);
	DSCCheckBox7->Height = CheckBoxHeight;
	DSCCheckBox7->Left = PaddingWidth;
	DSCCheckBox7->Top = PaddingTop + CheckBoxTop;

	DSCCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(DSCCheckBox6->Caption);
	DSCCheckBox6->Height = CheckBoxHeight;
	DSCCheckBox6->Left = DSCCheckBox7->Left;
	DSCCheckBox6->Top = DSCCheckBox7->Top + DSCCheckBox7->Height + CheckBoxSpacing;

	DSCCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(DSCCheckBox0->Caption);
	DSCCheckBox0->Height = CheckBoxHeight;
	DSCCheckBox0->Left = DSCCheckBox6->Left;
	DSCCheckBox0->Top = DSCCheckBox6->Top + DSCCheckBox6->Height + CheckBoxSpacing;

	DSCCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(DSCCheckBox1->Caption);
	DSCCheckBox1->Height = CheckBoxHeight;
	DSCCheckBox1->Left = DSCCheckBox0->Left;
	DSCCheckBox1->Top = DSCCheckBox0->Top + DSCCheckBox0->Height + CheckBoxSpacing;

	DSCCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(DSCCheckBox2->Caption);
	DSCCheckBox2->Height = CheckBoxHeight;
	DSCCheckBox2->Left = DSCCheckBox1->Left;
	DSCCheckBox2->Top = DSCCheckBox1->Top + DSCCheckBox1->Height + CheckBoxSpacing;

	DSCCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(DSCCheckBox3->Caption);
	DSCCheckBox3->Height = CheckBoxHeight;
	DSCCheckBox3->Left = DSCCheckBox2->Left;
	DSCCheckBox3->Top = DSCCheckBox2->Top + DSCCheckBox2->Height + CheckBoxSpacing;

	int Space = GroupBoxTop + PaddingTop + PaddingBottom + GroupBoxBottom + TextBoxHeight + CheckBoxTop + CheckBoxHeight * 2 + CheckBoxBottom * 2 - ComboBoxHeight * 3;

	DSCFRLRateLabel->Left = DSCCheckBox3->Left;
	DSCFRLRateLabel->Top = DSCCheckBox3->Top + DSCCheckBox3->Height + CheckBoxSpacing + Space / 2;

	DSCFRLRateComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	DSCFRLRateComboBox->Height = ComboBoxHeight;
	DSCFRLRateComboBox->Left = DSCFRLRateLabel->Left;
	DSCFRLRateComboBox->Top = DSCFRLRateLabel->Top + CheckBoxHeight + CheckBoxSpacing;

	DSCSlicesLabel->Left = DSCFRLRateComboBox->Left;
	DSCSlicesLabel->Top = DSCFRLRateComboBox->Top + DSCFRLRateComboBox->Height + Space / 2 + Space % 2;

	DSCSlicesComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	DSCSlicesComboBox->Height = ComboBoxHeight;
	DSCSlicesComboBox->Left = DSCSlicesLabel->Left;
	DSCSlicesComboBox->Top = DSCSlicesLabel->Top + CheckBoxHeight + CheckBoxSpacing;

	DSCChunkSize->AutoSize = false;
	DSCChunkSize->Width = TextBoxHeight;
	DSCChunkSize->Height = TextBoxHeight;

	DSCChunkSizeLabel->Left = DSCSlicesComboBox->Left;
	DSCChunkSize->Left = DSCChunkSizeLabel->Left + DSCChunkSizeLabel->Width + LabelSpacing;
	DSCChunkSizeUnitsLabel->Left = DSCChunkSize->Left + DSCChunkSize->Width + PostLabelSpacing;

	DSCChunkSize->Top = DSCSlicesComboBox->Top + DSCSlicesComboBox->Height + Scale;
	DSCChunkSizeLabel->Top = DSCChunkSize->Top + 3;
	DSCChunkSizeUnitsLabel->Top = DSCChunkSizeLabel->Top;

	DSCGroupBox->Width = Features21GroupBox->Width;
	DSCGroupBox->Height = DSCChunkSize->Top + DSCChunkSize->Height + PaddingBottom;
	DSCGroupBox->Left = Features21GroupBox->Left;
	DSCGroupBox->Top = Features21GroupBox->Top + Features21GroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = DSCGroupBox->Top + DSCGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = DSCGroupBox->Left + DSCGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FormShow(TObject *Sender)
{
	InitFRLRateComboBox();
	InitDSCFRLRateComboBox();
	InitDSCSlicesComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::OverrideTMDSRateClick(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetOverrideTMDSRate(OverrideTMDSRate->Checked);
	Refresh(TMDSRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::TMDSRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetTMDSRate(TextToInteger(TMDSRate->Text.c_str()));
	Refresh(TMDSRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::TMDSRateExit(TObject *Sender)
{
	Refresh(TMDSRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FeaturesCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMI2Support->SetFeature(CheckBox->Tag, CheckBox->Checked);
	Refresh(FeaturesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::ColorFormatsCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMI2Support->SetColorFormat(CheckBox->Tag, CheckBox->Checked);
	Refresh(ColorFormatsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::FRLRateComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetFRLRate(FRLRateComboBox->ItemIndex);
	Refresh(FRLRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::Features21CheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMI2Support->SetFeature21(CheckBox->Tag, CheckBox->Checked);
	Refresh(Features21GroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::MinVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetMinRefreshRate(TextToInteger(MinVRate->Text.c_str()));
	Refresh(RefreshRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::MinVRateExit(TObject *Sender)
{
	Refresh(RefreshRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::MaxVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetMaxRefreshRate(TextToInteger(MaxVRate->Text.c_str()));
	Refresh(RefreshRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::MaxVRateExit(TObject *Sender)
{
	Refresh(RefreshRateGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::DSCCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	HDMI2Support->SetDSCFeature(CheckBox->Tag, CheckBox->Checked);
	Refresh(DSCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::DSCFRLRateComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetDSCFRLRate(DSCFRLRateComboBox->ItemIndex);
	Refresh(DSCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::DSCSlicesComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetDSCSlices(DSCSlicesComboBox->ItemIndex);
	Refresh(DSCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::DSCChunkSizeChange(TObject *Sender)
{
	if (Refreshing)
		return;

	HDMI2Support->SetDSCChunkSize(TextToInteger(DSCChunkSize->Text.c_str()));
	Refresh(DSCGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall THDMI2SupportForm::DSCChunkSizeExit(TObject *Sender)
{
	Refresh(DSCGroupBox);
}
//---------------------------------------------------------------------------
