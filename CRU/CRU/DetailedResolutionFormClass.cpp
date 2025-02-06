//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "DetailedResolutionFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDetailedResolutionForm *DetailedResolutionForm;
//---------------------------------------------------------------------------
__fastcall TDetailedResolutionForm::TDetailedResolutionForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::Connect(DetailedResolutionClass &NewDetailedResolution)
{
	DetailedResolution = &NewDetailedResolution;
	VRateDigits = DetailedResolution->GetVRateDigits();
	HRateDigits = DetailedResolution->GetHRateDigits();
	PClockDigits = DetailedResolution->GetPClockDigits();
	return true;
}
//---------------------------------------------------------------------------
TColor TDetailedResolutionForm::GetTextColor(bool Valid, bool Set)
{
	if (!Set)
	{
		if (!Valid)
			return (TColor)RGB(255, 128, 128);

		return clGrayText;
	}

	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
TColor TDetailedResolutionForm::GetColor(bool Set)
{
	if (!Set)
		return clBtnFace;

	return clWindow;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::Refresh(void *Value)
{
	Refreshing = true;
	RefreshTimingComboBox();
	RefreshTimingButtons();

	if (Value == NULL || Value == ParametersGroupBox || Value == FrequencyGroupBox)
	{
		RefreshParametersRadioButtons();
		RefreshParametersTextBoxes();
		RefreshParametersComboBoxes();
		RefreshParametersLabels();
		RefreshFrequencyRadioButtons();
		RefreshFrequencyTextBoxes();
		RefreshFrequencyLabels();
		RefreshFrequencyCheckBoxes();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = DetailedResolution->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::InitTimingComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = TimingComboBox->ItemIndex;
	TimingComboBox->Items->BeginUpdate();
	TimingComboBox->Clear();

	for (Index = 0; DetailedResolution->GetTimingText(Index, Text, TEXTSIZE); Index++)
		TimingComboBox->Items->Add(Text);

	TimingComboBox->ItemIndex = ItemIndex;
	TimingComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshTimingComboBox()
{
	TimingComboBox->ItemIndex = DetailedResolution->GetTiming();
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshTimingButtons()
{
	TimingCopyButton->Enabled = DetailedResolution->CopyPossible();
	TimingPasteButton->Enabled = DetailedResolution->PastePossible();
	TimingResetButton->Enabled = DetailedResolution->ResetPossible();
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshParametersRadioButtons()
{
	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	Last0->Visible = Manual || ManualVTotal;
	Last1->Visible = Manual || ManualVTotal;
	Last2->Visible = Manual || ManualVTotal;

	Last0->Checked = DetailedResolution->IsLast(0);
	Last1->Checked = DetailedResolution->IsLast(1);
	Last2->Checked = DetailedResolution->IsLast(2);

	Last0->TabStop = false;
	Last1->TabStop = false;
	Last2->TabStop = false;
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshParametersTextBoxes()
{
	char Text[TEXTSIZE];

	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	HFront->Enabled = Manual || ManualVTotal;
	HSync->Enabled = Manual || ManualVTotal;
	HBack->Enabled = Manual || ManualVTotal;
	HBlank->Enabled = Manual || ManualVTotal;
	HTotal->Enabled = Manual || ManualVTotal;

	HFront->Color = GetColor(Manual || ManualVTotal);
	HSync->Color = GetColor(Manual || ManualVTotal);
	HBack->Color = GetColor(Manual || ManualVTotal);
	HBlank->Color = GetColor(Manual || ManualVTotal);
	HTotal->Color = GetColor(Manual || ManualVTotal);

	HActive->Font->Color = GetTextColor(DetailedResolution->IsValidHActive(), true);
	HFront->Font->Color = GetTextColor(DetailedResolution->IsValidHFront(), Manual || ManualVTotal);
	HSync->Font->Color = GetTextColor(DetailedResolution->IsValidHSync(), Manual || ManualVTotal);
	HBack->Font->Color = GetTextColor(DetailedResolution->IsValidHBack(), (Manual || ManualVTotal) && DetailedResolution->IsLast(0));
	HBlank->Font->Color = GetTextColor(DetailedResolution->IsValidHBlank(), (Manual || ManualVTotal) && DetailedResolution->IsLast(1));
	HTotal->Font->Color = GetTextColor(DetailedResolution->IsValidHTotal(), (Manual || ManualVTotal) && DetailedResolution->IsLast(2));

	if (!HActive->Focused() && IntegerToText(DetailedResolution->GetHActive(), Text, TEXTSIZE))
		HActive->Text = Text;

	if (!HFront->Focused() && IntegerToText(DetailedResolution->GetHFront(), Text, TEXTSIZE))
		HFront->Text = Text;

	if (!HSync->Focused() && IntegerToText(DetailedResolution->GetHSync(), Text, TEXTSIZE))
		HSync->Text = Text;

	if (!HBack->Focused() && IntegerToText(DetailedResolution->GetHBack(), Text, TEXTSIZE))
		HBack->Text = Text;

	if (!HBlank->Focused() && IntegerToText(DetailedResolution->GetHBlank(), Text, TEXTSIZE))
		HBlank->Text = Text;

	if (!HTotal->Focused() && IntegerToText(DetailedResolution->GetHTotal(), Text, TEXTSIZE))
		HTotal->Text = Text;

	VFront->Enabled = Manual || ManualVTotal;
	VSync->Enabled = Manual || ManualVTotal;
	VBack->Enabled = Manual;
	VBlank->Enabled = Manual;
	VTotal->Enabled = Manual;

	VFront->Color = GetColor(Manual || ManualVTotal);
	VSync->Color = GetColor(Manual || ManualVTotal);
	VBack->Color = GetColor(Manual);
	VBlank->Color = GetColor(Manual);
	VTotal->Color = GetColor(Manual);

	VActive->Font->Color = GetTextColor(DetailedResolution->IsValidVActive(), true);
	VFront->Font->Color = GetTextColor(DetailedResolution->IsValidVFront(), Manual || ManualVTotal);
	VSync->Font->Color = GetTextColor(DetailedResolution->IsValidVSync(), Manual || ManualVTotal);
	VBack->Font->Color = GetTextColor(DetailedResolution->IsValidVBack(), Manual && DetailedResolution->IsLast(0));
	VBlank->Font->Color = GetTextColor(DetailedResolution->IsValidVBlank(), Manual && DetailedResolution->IsLast(1));
	VTotal->Font->Color = GetTextColor(DetailedResolution->IsValidVTotal(), Manual && DetailedResolution->IsLast(2));

	if (!VActive->Focused() && IntegerToText(DetailedResolution->GetVActive(), Text, TEXTSIZE))
		VActive->Text = Text;

	if (!VFront->Focused() && IntegerToText(DetailedResolution->GetVFront(), Text, TEXTSIZE))
		VFront->Text = Text;

	if (!VSync->Focused() && IntegerToText(DetailedResolution->GetVSync(), Text, TEXTSIZE))
		VSync->Text = Text;

	if (!VBack->Focused() && IntegerToText(DetailedResolution->GetVBack(), Text, TEXTSIZE))
		VBack->Text = Text;

	if (!VBlank->Focused() && IntegerToText(DetailedResolution->GetVBlank(), Text, TEXTSIZE))
		VBlank->Text = Text;

	if (!VTotal->Focused() && IntegerToText(DetailedResolution->GetVTotal(), Text, TEXTSIZE))
		VTotal->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshParametersComboBoxes()
{
	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	HPolarity->Enabled = Manual || ManualVTotal;
	HPolarity->Color = GetColor(Manual || ManualVTotal);
	HPolarity->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	HPolarity->ItemIndex = DetailedResolution->GetHPolarity();

	VPolarity->Enabled = Manual || ManualVTotal;
	VPolarity->Color = GetColor(Manual || ManualVTotal);
	VPolarity->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	VPolarity->ItemIndex = DetailedResolution->GetVPolarity();
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshParametersLabels()
{
	char Text[TEXTSIZE];

	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	Back->Visible = !Manual && !ManualVTotal;
	Blank->Visible = !Manual && !ManualVTotal;
	Total->Visible = !Manual && !ManualVTotal;

	Front->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	Sync->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	Back->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	Blank->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	Total->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	Polarity->Font->Color = GetTextColor(true, Manual || ManualVTotal);

	FrontPixels->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	SyncPixels->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	BackPixels->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	BlankPixels->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	TotalPixels->Font->Color = GetTextColor(true, Manual || ManualVTotal);

	FrontLines->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	SyncLines->Font->Color = GetTextColor(true, Manual || ManualVTotal);
	BackLines->Font->Color = GetTextColor(true, Manual);
	BlankLines->Font->Color = GetTextColor(true, Manual);
	TotalLines->Font->Color = GetTextColor(true, Manual);

	if (DetailedResolution->GetVActiveLinesText(Text, TEXTSIZE))
		ActiveLines->Caption = Text;

	if (DetailedResolution->GetVFrontLinesText(Text, TEXTSIZE))
		FrontLines->Caption = Text;

	if (DetailedResolution->GetVSyncLinesText(Text, TEXTSIZE))
		SyncLines->Caption = Text;

	if (DetailedResolution->GetVBackLinesText(Text, TEXTSIZE))
		BackLines->Caption = Text;

	if (DetailedResolution->GetVBlankLinesText(Text, TEXTSIZE))
		BlankLines->Caption = Text;

	if (DetailedResolution->GetVTotalLinesText(Text, TEXTSIZE))
		TotalLines->Caption = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshFrequencyRadioButtons()
{
	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	LastRate0->Visible = Manual || ManualVTotal;
	LastRate1->Visible = Manual;
	LastRate2->Visible = Manual || ManualVTotal;

	LastRate0->Checked = DetailedResolution->IsLastRate(0);
	LastRate1->Checked = DetailedResolution->IsLastRate(1);
	LastRate2->Checked = DetailedResolution->IsLastRate(2);

	LastRate0->TabStop = false;
	LastRate1->TabStop = false;
	LastRate2->TabStop = false;
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshFrequencyTextBoxes()
{
	char Text[TEXTSIZE];

	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	VRate->Font->Color = GetTextColor(DetailedResolution->IsValidVRate(), Manual && DetailedResolution->IsLastRate(0) || !Manual);

	HRate->Enabled = Manual;
	HRate->Color = GetColor(Manual);
	HRate->Font->Color = GetTextColor(DetailedResolution->IsValidHRate(), Manual && DetailedResolution->IsLastRate(1));

	PClock->Enabled = Manual || ManualVTotal;
	PClock->Color = GetColor(Manual || ManualVTotal);
	PClock->Font->Color = GetTextColor(DetailedResolution->IsValidPClock(), Manual && DetailedResolution->IsLastRate(2) || ManualVTotal);

	if (!VRate->Focused() && DecimalToText(DetailedResolution->GetVRate(), VRate->MaxLength, VRateDigits, Text, TEXTSIZE))
		VRate->Text = Text;

	if (!HRate->Focused() && DecimalToText(DetailedResolution->GetHRate(), HRate->MaxLength, HRateDigits, Text, TEXTSIZE))
		HRate->Text = Text;

	if (!PClock->Focused() && DecimalToText(DetailedResolution->GetPClock(), PClock->MaxLength, PClockDigits, Text, TEXTSIZE))
		PClock->Text = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshFrequencyLabels()
{
	char Text[TEXTSIZE];

	bool Manual = DetailedResolution->GetTiming() == TIMING_MANUAL;
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	Rate0->Visible = !Manual && !ManualVTotal;
	Rate1->Visible = !Manual;
	Rate2->Visible = !Manual && !ManualVTotal;

	Rate1->Font->Color = GetTextColor(true, Manual);
	Rate2->Font->Color = GetTextColor(true, Manual || ManualVTotal);

	kHz->Font->Color = GetTextColor(true, Manual);
	MHz->Font->Color = GetTextColor(true, Manual || ManualVTotal);

	ActualHRate->Visible = !ManualVTotal;
	ActualPClock->Visible = ManualVTotal;

	if (DetailedResolution->GetActualVRateText(Text, TEXTSIZE, Dash()))
		ActualVRate->Caption = Text;

	if (DetailedResolution->GetActualHRateText(Text, TEXTSIZE, Dash()))
		ActualHRate->Caption = Text;

	if (DetailedResolution->GetActualPClockText(Text, TEXTSIZE, Dash()))
		ActualPClock->Caption = Text;

	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::RefreshFrequencyCheckBoxes()
{
	bool ManualVTotal = DetailedResolution->GetTiming() == TIMING_MANUAL_VTOTAL;

	if (ManualVTotal)
		Interlaced->Top = HRate->Top + 3 + CheckBoxTop;
	else
		Interlaced->Top = PClock->Top + 3 + CheckBoxTop;

	Interlaced->Enabled = DetailedResolution->InterlacedPossible();
	Interlaced->Checked = DetailedResolution->GetInterlaced();

	Preferred->Top = Interlaced->Top;
	Preferred->Visible = DetailedResolution->PreferredPossible();
	Preferred->Checked = DetailedResolution->GetPreferred();
	return true;
}
//---------------------------------------------------------------------------
bool TDetailedResolutionForm::ScaleControls()
{
	int GroupBoxWidth = FormButtonsWidth * 2 + PostLabelSpacing + Canvas->TextWidth("pixels") + Scale * 3;
	int TextBoxWidth = 7 * NumberWidth + TextBoxPadding;
	int RateTextBoxWidth = 9 * NumberWidth + TextBoxPadding;
	int ComboBoxWidth = TextBoxWidth;
	int Column1Left = FormButtonsWidth - TextBoxWidth;
	int Column2Left = GroupBoxWidth - FormButtonsWidth;

	Timing->Left = Scale;
	Timing->Top = Scale + 4;

	TimingComboBox->Height = ComboBoxHeight;
	TimingComboBox->Left = Timing->Left + Timing->Width + LabelSpacing;
	TimingComboBox->Top = Timing->Top - 4;

	TimingCopyButton->Width = ButtonWidth;
	TimingCopyButton->Height = ButtonHeight;
	TimingCopyButton->Top = TimingComboBox->Top;
	FixButtonCaption(TimingCopyButton, Canvas->TextWidth(TimingCopyButton->Caption));

	TimingPasteButton->Width = ButtonWidth;
	TimingPasteButton->Height = ButtonHeight;
	TimingPasteButton->Top = TimingCopyButton->Top;
	FixButtonCaption(TimingPasteButton, Canvas->TextWidth(TimingPasteButton->Caption));

	TimingResetButton->Width = ButtonWidth;
	TimingResetButton->Height = ButtonHeight;
	TimingResetButton->Top = TimingPasteButton->Top;
	FixButtonCaption(TimingResetButton, Canvas->TextWidth(TimingResetButton->Caption));

	Horizontal->Font->Height = Text.tmHeight;
	Horizontal->Canvas->Font->Height = Text.tmHeight;
	Horizontal->Left = Column1Left + (TextBoxWidth - Horizontal->Width) / 2;
	Horizontal->Top = Text.tmHeight;

	HActive->AutoSize = false;
	HActive->Width = TextBoxWidth;
	HActive->Height = TextBoxHeight;
	HActive->Left = Column1Left;
	HActive->Top = Horizontal->Top + Text.tmAscent + Scale;

	HFront->AutoSize = false;
	HFront->Width = TextBoxWidth;
	HFront->Height = TextBoxHeight;
	HFront->Left = HActive->Left;
	HFront->Top = HActive->Top + HActive->Height + TextBoxSpacing;

	HSync->AutoSize = false;
	HSync->Width = TextBoxWidth;
	HSync->Height = TextBoxHeight;
	HSync->Left = HFront->Left;
	HSync->Top = HFront->Top + HFront->Height + TextBoxSpacing;

	HBack->AutoSize = false;
	HBack->Width = TextBoxWidth;
	HBack->Height = TextBoxHeight;
	HBack->Left = HSync->Left;
	HBack->Top = HSync->Top + HSync->Height + TextBoxSpacing;

	HBlank->AutoSize = false;
	HBlank->Width = TextBoxWidth;
	HBlank->Height = TextBoxHeight;
	HBlank->Left = HBack->Left;
	HBlank->Top = HBack->Top + HBack->Height + TextBoxSpacing;

	HTotal->AutoSize = false;
	HTotal->Width = TextBoxWidth;
	HTotal->Height = TextBoxHeight;
	HTotal->Left = HBlank->Left;
	HTotal->Top = HBlank->Top + HBlank->Height + TextBoxSpacing;

	HPolarity->Font->Height = Text.tmHeight;
	HPolarity->Canvas->Font->Height = Text.tmHeight;
	HPolarity->Width = ComboBoxWidth;
	HPolarity->Height = ComboBoxHeight;
	HPolarity->Left = HTotal->Left;
	HPolarity->Top = HTotal->Top + HTotal->Height + TextBoxSpacing;

	Last0->Width = Column1Left - PaddingWidth - Scale;
	Last0->Height = RadioButtonHeight;
	Last0->Left = PaddingWidth;
	Last0->Top = HBack->Top + 3 + RadioButtonTop;

	Last1->Width = Last0->Width;
	Last1->Height = RadioButtonHeight;
	Last1->Left = Last0->Left;
	Last1->Top = HBlank->Top + 3 + RadioButtonTop;

	Last2->Width = Last1->Width;
	Last2->Height = RadioButtonHeight;
	Last2->Left = Last1->Left;
	Last2->Top = HTotal->Top + 3 + RadioButtonTop;

	Active->Left = PaddingWidth + RadioButtonWidth + RadioButtonRight;
	Active->Top = HActive->Top + 3;

	Front->Left = Active->Left;
	Front->Top = HFront->Top + 3;

	Sync->Left = Front->Left;
	Sync->Top = HSync->Top + 3;

	Back->Left = Sync->Left;
	Back->Top = HBack->Top + 3;

	Blank->Left = Back->Left;
	Blank->Top = HBlank->Top + 3;

	Total->Left = Blank->Left;
	Total->Top = HTotal->Top + 3;

	Polarity->Left = Total->Left;
	Polarity->Top = HPolarity->Top + 3;

	ActivePixels->Left = HActive->Left + HActive->Width + PostLabelSpacing;
	ActivePixels->Top = HActive->Top + 3;

	FrontPixels->Left = ActivePixels->Left;
	FrontPixels->Top = HFront->Top + 3;

	SyncPixels->Left = FrontPixels->Left;
	SyncPixels->Top = HSync->Top + 3;

	BackPixels->Left = SyncPixels->Left;
	BackPixels->Top = HBack->Top + 3;

	BlankPixels->Left = BackPixels->Left;
	BlankPixels->Top = HBlank->Top + 3;

	TotalPixels->Left = BlankPixels->Left;
	TotalPixels->Top = HTotal->Top + 3;

	Vertical->Font->Height = Text.tmHeight;
	Vertical->Canvas->Font->Height = Text.tmHeight;
	Vertical->Left = Column2Left + (TextBoxWidth - Vertical->Width) / 2;
	Vertical->Top = Horizontal->Top;

	VActive->AutoSize = false;
	VActive->Width = TextBoxWidth;
	VActive->Height = TextBoxHeight;
	VActive->Left = Column2Left;
	VActive->Top = HActive->Top;

	VFront->AutoSize = false;
	VFront->Width = TextBoxWidth;
	VFront->Height = TextBoxHeight;
	VFront->Left = VActive->Left;
	VFront->Top = HFront->Top;

	VSync->AutoSize = false;
	VSync->Width = TextBoxWidth;
	VSync->Height = TextBoxHeight;
	VSync->Left = VFront->Left;
	VSync->Top = HSync->Top;

	VBack->AutoSize = false;
	VBack->Width = TextBoxWidth;
	VBack->Height = TextBoxHeight;
	VBack->Left = VSync->Left;
	VBack->Top = HBack->Top;

	VBlank->AutoSize = false;
	VBlank->Width = TextBoxWidth;
	VBlank->Height = TextBoxHeight;
	VBlank->Left = VBack->Left;
	VBlank->Top = HBlank->Top;

	VTotal->AutoSize = false;
	VTotal->Width = TextBoxWidth;
	VTotal->Height = TextBoxHeight;
	VTotal->Left = VBlank->Left;
	VTotal->Top = HTotal->Top;

	VPolarity->Font->Height = Text.tmHeight;
	VPolarity->Canvas->Font->Height = Text.tmHeight;
	VPolarity->Width = ComboBoxWidth;
	VPolarity->Height = ComboBoxHeight;
	VPolarity->Left = VTotal->Left;
	VPolarity->Top = HPolarity->Top;

	ActiveLines->Left = VActive->Left + VActive->Width + PostLabelSpacing;
	ActiveLines->Top = VActive->Top + 3;

	FrontLines->Left = ActiveLines->Left;
	FrontLines->Top = VFront->Top + 3;

	SyncLines->Left = FrontLines->Left;
	SyncLines->Top = VSync->Top + 3;

	BackLines->Left = SyncLines->Left;
	BackLines->Top = VBack->Top + 3;

	BlankLines->Left = BackLines->Left;
	BlankLines->Top = VBlank->Top + 3;

	TotalLines->Left = BlankLines->Left;
	TotalLines->Top = VTotal->Top + 3;

	ParametersGroupBox->Width = GroupBoxWidth;
	ParametersGroupBox->Height = HPolarity->Top + HPolarity->Height + PaddingBottom;
	ParametersGroupBox->Left = Scale;
	ParametersGroupBox->Top = TimingComboBox->Top + TimingComboBox->Height + GroupBoxTop;

	VRate->AutoSize = false;
	VRate->Width = RateTextBoxWidth;
	VRate->Height = TextBoxHeight;
	VRate->Left = Column1Left;
	VRate->Top = PaddingTop;

	HRate->AutoSize = false;
	HRate->Width = RateTextBoxWidth;
	HRate->Height = TextBoxHeight;
	HRate->Left = VRate->Left;
	HRate->Top = VRate->Top + VRate->Height + TextBoxSpacing;

	PClock->AutoSize = false;
	PClock->Width = RateTextBoxWidth;
	PClock->Height = TextBoxHeight;
	PClock->Left = HRate->Left;
	PClock->Top = HRate->Top + HRate->Height + TextBoxSpacing;

	LastRate0->Width = Column1Left - PaddingWidth - Scale;
	LastRate0->Height = RadioButtonHeight;
	LastRate0->Left = PaddingWidth;
	LastRate0->Top = VRate->Top + 3 + RadioButtonTop;

	LastRate1->Width = LastRate0->Width;
	LastRate1->Height = RadioButtonHeight;
	LastRate1->Left = LastRate0->Left;
	LastRate1->Top = HRate->Top + 3 + RadioButtonTop;

	LastRate2->Width = LastRate1->Width;
	LastRate2->Height = RadioButtonHeight;
	LastRate2->Left = LastRate1->Left;
	LastRate2->Top = PClock->Top + 3 + RadioButtonTop;

	Rate0->Left = PaddingWidth + RadioButtonWidth + RadioButtonRight;
	Rate0->Top = VRate->Top + 3;

	Rate1->Left = Rate0->Left;
	Rate1->Top = HRate->Top + 3;

	Rate2->Left = Rate1->Left;
	Rate2->Top = PClock->Top + 3;

	Hz->Left = VRate->Left + VRate->Width + PostLabelSpacing;
	Hz->Top = VRate->Top + 3;

	kHz->Left = HRate->Left + HRate->Width + PostLabelSpacing;
	kHz->Top = HRate->Top + 3;

	MHz->Left = PClock->Left + PClock->Width + PostLabelSpacing;
	MHz->Top = PClock->Top + 3;

	ActualVRate->Left = Column2Left;
	ActualVRate->Top = VRate->Top + 3;

	ActualHRate->Left = ActualVRate->Left;
	ActualHRate->Top = HRate->Top + 3;

	ActualPClock->Left = ActualHRate->Left;
	ActualPClock->Top = PClock->Top + 3;

	Interlaced->Width = CheckBoxWidth + Canvas->TextWidth(Interlaced->Caption);
	Interlaced->Height = CheckBoxHeight;
	Interlaced->Left = ActualPClock->Left;
	Interlaced->Top = PClock->Top + 3 + CheckBoxTop;

	Preferred->Width = CheckBoxWidth + Canvas->TextWidth(Preferred->Caption);
	Preferred->Height = CheckBoxHeight;
	Preferred->Left = Interlaced->Left + ButtonLeft + FormButtonWidth + ButtonRight + Scale;
	Preferred->Top = Interlaced->Top;

	FrequencyGroupBox->Width = ParametersGroupBox->Width;
	FrequencyGroupBox->Height = PClock->Top + PClock->Height + PaddingBottom;
	FrequencyGroupBox->Left = ParametersGroupBox->Left;
	FrequencyGroupBox->Top = ParametersGroupBox->Top + ParametersGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	TimingResetButton->Left = ParametersGroupBox->Left + ParametersGroupBox->Width - ButtonRight - TimingResetButton->Width;
	TimingPasteButton->Left = TimingResetButton->Left - TimingPasteButton->Width;
	TimingCopyButton->Left = TimingPasteButton->Left - TimingCopyButton->Width;
	TimingComboBox->Width = TimingCopyButton->Left - ButtonLeft - Scale - TimingComboBox->Left;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = FrequencyGroupBox->Top + FrequencyGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = FrequencyGroupBox->Left + FrequencyGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::FormShow(TObject *Sender)
{
	InitTimingComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::TimingComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetTiming(TimingComboBox->ItemIndex);
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::TimingCopyButtonClick(TObject *Sender)
{
	DetailedResolution->Copy();
	RefreshTimingButtons();
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::TimingPasteButtonClick(TObject *Sender)
{
	DetailedResolution->Paste();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::TimingResetButtonClick(TObject *Sender)
{
	DetailedResolution->Reset();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::Last0Click(TObject *Sender)
{
	if (Refreshing)
		return;

	if (!Last0->Visible)
		return;

	DetailedResolution->SetLast(0);
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::Last1Click(TObject *Sender)
{
	if (Refreshing)
		return;

	if (!Last1->Visible)
		return;

	DetailedResolution->SetLast(1);
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::Last2Click(TObject *Sender)
{
	if (Refreshing)
		return;

	if (!Last2->Visible)
		return;

	DetailedResolution->SetLast(2);
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HActiveChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHActive(TextToInteger(HActive->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HActiveExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HFrontChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHFront(TextToInteger(HFront->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HFrontExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HSyncChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHSync(TextToInteger(HSync->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HSyncExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HBackChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHBack(TextToInteger(HBack->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HBackExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HBlankChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHBlank(TextToInteger(HBlank->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HBlankExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HTotalChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHTotal(TextToInteger(HTotal->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HTotalExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HPolarityChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHPolarity(HPolarity->ItemIndex);
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VActiveChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVActive(TextToInteger(VActive->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VActiveExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VFrontChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVFront(TextToInteger(VFront->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VFrontExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VSyncChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVSync(TextToInteger(VSync->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VSyncExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VBackChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVBack(TextToInteger(VBack->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VBackExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VBlankChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVBlank(TextToInteger(VBlank->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VBlankExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VTotalChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVTotal(TextToInteger(VTotal->Text.c_str()));
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VTotalExit(TObject *Sender)
{
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VPolarityChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVPolarity(VPolarity->ItemIndex);
	Refresh(ParametersGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::LastRate0Click(TObject *Sender)
{
	if (Refreshing)
		return;

	if (!LastRate0->Visible)
		return;

	DetailedResolution->SetLastRate(0);
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::LastRate1Click(TObject *Sender)
{
	if (Refreshing)
		return;

	if (!LastRate1->Visible)
		return;

	DetailedResolution->SetLastRate(1);
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::LastRate2Click(TObject *Sender)
{
	if (Refreshing)
		return;

	if (!LastRate2->Visible)
		return;

	DetailedResolution->SetLastRate(2);
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetVRate(TextToDecimal(VRate->Text.c_str(), VRateDigits));
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::VRateExit(TObject *Sender)
{
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetHRate(TextToDecimal(HRate->Text.c_str(), HRateDigits));
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::HRateExit(TObject *Sender)
{
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::PClockChange(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetPClock(TextToDecimal(PClock->Text.c_str(), PClockDigits));
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::PClockExit(TObject *Sender)
{
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::InterlacedClick(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetInterlaced(Interlaced->Checked);
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TDetailedResolutionForm::PreferredClick(TObject *Sender)
{
	if (Refreshing)
		return;

	DetailedResolution->SetPreferred(Preferred->Checked);
	Refresh(FrequencyGroupBox);
}
//---------------------------------------------------------------------------
