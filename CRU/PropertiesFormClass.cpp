//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "PropertiesFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TPropertiesForm *PropertiesForm;
//---------------------------------------------------------------------------
__fastcall TPropertiesForm::TPropertiesForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::Connect(PropertiesClass &NewProperties)
{
	Properties = &NewProperties;
	return true;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::Refresh(void *Value)
{
	char Text[TEXTSIZE];

	Refreshing = true;

	if (Value == NULL)
	{
		if (Properties->ColorFormatsSupported())
		{
			ColorFormatsGroupBox->Visible = true;
			NameGroupBox->Top = ColorFormatsGroupBox->Top + ColorFormatsGroupBox->Height + GroupBoxBottom + GroupBoxTop;
		}
		else
		{
			ColorFormatsGroupBox->Visible = false;
			NameGroupBox->Top = DeviceIDGroupBox->Top + DeviceIDGroupBox->Height + GroupBoxBottom + GroupBoxTop;
		}

		SerialNumberGroupBox->Top = NameGroupBox->Top + NameGroupBox->Height + GroupBoxBottom + GroupBoxTop;
		RangeLimitsGroupBox->Top = SerialNumberGroupBox->Top + SerialNumberGroupBox->Height + GroupBoxBottom + GroupBoxTop;
		FormOKButton->Top = RangeLimitsGroupBox->Top + RangeLimitsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
		FormCancelButton->Top = FormOKButton->Top;
		ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	}

	if (Value == NULL || Value == DeviceIDGroupBox)
	{
		DeviceID->Font->Color = GetTextColor(Properties->IsValidDeviceID());

		if (!DeviceID->Focused() && Properties->GetDeviceID(Text, TEXTSIZE))
			DeviceID->Text = Text;

		SerialID->Font->Color = GetTextColor(Properties->IsValidSerialID());

		if (!SerialID->Focused() && DecimalToText(Properties->GetSerialID(), SerialID->MaxLength, 0, Text, TEXTSIZE))
			SerialID->Text = Text;

		DeviceIDResetButton->Enabled = Properties->ResetDeviceIDPossible();
	}

	if (Value == NULL || Value == ColorFormatsGroupBox)
	{
		YCbCr422->Checked = Properties->GetYCbCr422();
		YCbCr444->Checked = Properties->GetYCbCr444();

		ColorDepthComboBox->ItemIndex = Properties->GetColorDepth();
	}

	if (Value == NULL || Value == NameGroupBox)
	{
		Name->Font->Color = GetTextColor(Properties->IsValidName());

		if (!Name->Focused() && Properties->GetName(Text, TEXTSIZE))
			Name->Text = Text;

		IncludeName->Checked = Properties->GetIncludeName();
	}

	if (Value == NULL || Value == SerialNumberGroupBox)
	{
		SerialNumber->Font->Color = GetTextColor(Properties->IsValidSerialNumber());

		if (!SerialNumber->Focused() && Properties->GetSerialNumber(Text, TEXTSIZE))
			SerialNumber->Text = Text;

		IncludeSerialNumber->Checked = Properties->GetIncludeSerialNumber();
	}

	if (Value == NULL || Value == RangeLimitsGroupBox)
	{
		MinVRate->Font->Color = GetTextColor(Properties->IsValidMinVRate());

		if (!MinVRate->Focused() && IntegerToText(Properties->GetMinVRate(), Text, TEXTSIZE))
			MinVRate->Text = Text;

		MaxVRate->Font->Color = GetTextColor(Properties->IsValidMaxVRate());

		if (!MaxVRate->Focused() && IntegerToText(Properties->GetMaxVRate(), Text, TEXTSIZE))
			MaxVRate->Text = Text;

		MinHRate->Font->Color = GetTextColor(Properties->IsValidMinHRate());

		if (!MinHRate->Focused() && IntegerToText(Properties->GetMinHRate(), Text, TEXTSIZE))
			MinHRate->Text = Text;

		MaxHRate->Font->Color = GetTextColor(Properties->IsValidMaxHRate());

		if (!MaxHRate->Focused() && IntegerToText(Properties->GetMaxHRate(), Text, TEXTSIZE))
			MaxHRate->Text = Text;

		MaxPClock->Font->Color = GetTextColor(Properties->IsValidMaxPClock());

		if (!MaxPClock->Focused() && IntegerToText(Properties->GetMaxPClock(), Text, TEXTSIZE))
			MaxPClock->Text = Text;

		IncludeRangeLimits->Checked = Properties->GetIncludeRangeLimits();
	}

	if (Value != FormOKButton)
		FormOKButton->Enabled = Properties->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::InitColorDepthComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = ColorDepthComboBox->ItemIndex;
	ColorDepthComboBox->Items->BeginUpdate();
	ColorDepthComboBox->Clear();

	for (Index = 0; Properties->GetColorDepthText(Index, Text, TEXTSIZE); Index++)
		ColorDepthComboBox->Items->Add(Text);

	ColorDepthComboBox->ItemIndex = ItemIndex;
	ColorDepthComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TPropertiesForm::ScaleControls()
{
	DeviceIDResetButton->Width = ButtonWidth;
	DeviceIDResetButton->Height = ButtonHeight;
	FixButtonCaption(DeviceIDResetButton, Canvas->TextWidth(DeviceIDResetButton->Caption));

	DeviceID->AutoSize = false;
	DeviceID->Width = FormButtonsWidth - PaddingWidth - DeviceIDLabel->Width - LabelSpacing - Scale - ButtonLeft - DeviceIDResetButton->Width - ButtonRight - PaddingWidth;
	DeviceID->Height = TextBoxHeight;

	SerialID->AutoSize = false;
	SerialID->Width = FormButtonsWidth - PaddingWidth - SerialIDLabel->Width - LabelSpacing - PaddingWidth;
	SerialID->Height = TextBoxHeight;

	DeviceID->Top = PaddingTop;
	DeviceIDLabel->Top = DeviceID->Top + 3;
	DeviceIDResetButton->Top = DeviceID->Top;

	SerialID->Top = DeviceID->Top + DeviceID->Height + TextBoxSpacing;
	SerialIDLabel->Top = SerialID->Top + 3;

	DeviceIDLabel->Left = PaddingWidth;
	DeviceID->Left = DeviceIDLabel->Left + DeviceIDLabel->Width + LabelSpacing;
	DeviceIDResetButton->Left = DeviceID->Left + DeviceID->Width + Scale + ButtonLeft;

	SerialIDLabel->Left = DeviceIDLabel->Left;
	SerialID->Left = SerialIDLabel->Left + SerialIDLabel->Width + LabelSpacing;

	DeviceIDGroupBox->Width = FormButtonsWidth;
	DeviceIDGroupBox->Height = SerialID->Top + SerialID->Height + PaddingBottom;
	DeviceIDGroupBox->Left = Scale;
	DeviceIDGroupBox->Top = GroupBoxTop;

	YCbCr422->Width = CheckBoxWidth + Canvas->TextWidth(YCbCr422->Caption);
	YCbCr422->Height = CheckBoxHeight;
	YCbCr422->Left = PaddingWidth;
	YCbCr422->Top = PaddingTop + CheckBoxTop;

	YCbCr444->Width = CheckBoxWidth + Canvas->TextWidth(YCbCr444->Caption);
	YCbCr444->Height = CheckBoxHeight;
	YCbCr444->Left = YCbCr422->Left;
	YCbCr444->Top = YCbCr422->Top + YCbCr422->Height + CheckBoxSpacing;

	int Spacing = (GroupBoxTop + PaddingTop + PaddingBottom + GroupBoxBottom + TextBoxHeight + CheckBoxTop + CheckBoxHeight * 2 + CheckBoxBottom * 2 - ComboBoxHeight * 3) / 2;

	ColorDepthLabel->Left = YCbCr444->Left;
	ColorDepthLabel->Top = YCbCr444->Top + YCbCr444->Height + CheckBoxSpacing + Spacing;

	ColorDepthComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	ColorDepthComboBox->Height = ComboBoxHeight;
	ColorDepthComboBox->Left = ColorDepthLabel->Left;
	ColorDepthComboBox->Top = ColorDepthLabel->Top + CheckBoxHeight + CheckBoxSpacing;

	ColorFormatsGroupBox->Width = DeviceIDGroupBox->Width;
	ColorFormatsGroupBox->Height = ColorDepthComboBox->Top + ColorDepthComboBox->Height + PaddingBottom;
	ColorFormatsGroupBox->Left = DeviceIDGroupBox->Left;
	ColorFormatsGroupBox->Top = DeviceIDGroupBox->Top + DeviceIDGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	Name->AutoSize = false;
	Name->Width = FormButtonsWidth - PaddingWidth * 2;
	Name->Height = TextBoxHeight;
	Name->Left = PaddingWidth;
	Name->Top = PaddingTop;

	IncludeName->Width = CheckBoxWidth + Canvas->TextWidth(IncludeName->Caption);
	IncludeName->Height = CheckBoxHeight;
	IncludeName->Left = Name->Left;
	IncludeName->Top = Name->Top + Name->Height + Scale + CheckBoxTop;

	NameGroupBox->Width = ColorFormatsGroupBox->Width;
	NameGroupBox->Height = IncludeName->Top + IncludeName->Height + CheckBoxBottom + PaddingBottom;
	NameGroupBox->Left = ColorFormatsGroupBox->Left;
	NameGroupBox->Top = ColorFormatsGroupBox->Top + ColorFormatsGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	SerialNumber->AutoSize = false;
	SerialNumber->Width = FormButtonsWidth - PaddingWidth * 2;
	SerialNumber->Height = TextBoxHeight;
	SerialNumber->Left = PaddingWidth;
	SerialNumber->Top = PaddingTop;

	IncludeSerialNumber->Width = CheckBoxWidth + Canvas->TextWidth(IncludeSerialNumber->Caption);
	IncludeSerialNumber->Height = CheckBoxHeight;
	IncludeSerialNumber->Left = SerialNumber->Left;
	IncludeSerialNumber->Top = SerialNumber->Top + SerialNumber->Height + Scale + CheckBoxTop;

	SerialNumberGroupBox->Width = NameGroupBox->Width;
	SerialNumberGroupBox->Height = IncludeSerialNumber->Top + IncludeSerialNumber->Height + CheckBoxBottom + PaddingBottom;
	SerialNumberGroupBox->Left = NameGroupBox->Left;
	SerialNumberGroupBox->Top = NameGroupBox->Top + NameGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	MinVRate->AutoSize = false;
	MinVRate->Width = MinVRate->MaxLength * NumberWidth + TextBoxPadding;
	MinVRate->Height = TextBoxHeight;

	MaxVRate->AutoSize = false;
	MaxVRate->Width = MaxVRate->MaxLength * NumberWidth + TextBoxPadding;
	MaxVRate->Height = TextBoxHeight;

	MinHRate->AutoSize = false;
	MinHRate->Width = MinHRate->MaxLength * NumberWidth + TextBoxPadding;
	MinHRate->Height = TextBoxHeight;

	MaxHRate->AutoSize = false;
	MaxHRate->Width = MaxHRate->MaxLength * NumberWidth + TextBoxPadding;
	MaxHRate->Height = TextBoxHeight;

	MaxPClock->AutoSize = false;
	MaxPClock->Width = MaxPClock->MaxLength * NumberWidth + TextBoxPadding;
	MaxPClock->Height = TextBoxHeight;

	VRateLabel->Left = PaddingWidth;
	HRateLabel->Left = VRateLabel->Left;
	MaxPClockLabel->Left = HRateLabel->Left;

	MaxVRate->Left = MaxPClockLabel->Left + MaxPClockLabel->Width + LabelSpacing;
	MaxHRate->Left = MaxVRate->Left;
	MaxPClock->Left = MaxHRate->Left;

	HzLabel->Left = MaxVRate->Left + MaxVRate->Width + PostLabelSpacing;
	kHzLabel->Left = MaxHRate->Left + MaxHRate->Width + PostLabelSpacing;
	MHzLabel->Left = MaxPClock->Left + MaxPClock->Width + PostLabelSpacing;

	int Space = MaxHRate->Left - HRateLabel->Left - HRateLabel->Width - LabelSpacing - MinHRate->Width;
	int DashWidth = Space / 3 + Space % 3;
	int DashHeight = Text.tmHeight < 22 ? 1 : (Text.tmHeight + 13) / 16;
	int DashSpacing = (Space - DashWidth) / 2;

	if (DashWidth > NumberWidth)
		DashWidth = NumberWidth;

	if (DashSpacing > DashWidth)
		DashSpacing = DashWidth;

	VRateDash->Width = DashWidth;
	VRateDash->Height = DashHeight;

	HRateDash->Width = DashWidth;
	HRateDash->Height = DashHeight;

	VRateDash->Left = MaxVRate->Left - DashSpacing - VRateDash->Width;
	HRateDash->Left = VRateDash->Left;

	MinVRate->Left = VRateDash->Left - DashSpacing - MinVRate->Width;
	MinHRate->Left = MinVRate->Left;

	MaxVRate->Top = PaddingTop;
	MaxHRate->Top = MaxVRate->Top + MaxVRate->Height + TextBoxSpacing;
	MaxPClock->Top = MaxHRate->Top + MaxHRate->Height + TextBoxSpacing;

	VRateLabel->Top = MaxVRate->Top + 3;
	HRateLabel->Top = MaxHRate->Top + 3;
	MaxPClockLabel->Top = MaxPClock->Top + 3;

	MinVRate->Top = MaxVRate->Top;
	MinHRate->Top = MaxHRate->Top;

	VRateDash->Top = MaxVRate->Top + MaxVRate->Height / 2;
	HRateDash->Top = MaxHRate->Top + MaxHRate->Height / 2;

	HzLabel->Top = VRateLabel->Top;
	kHzLabel->Top = HRateLabel->Top;
	MHzLabel->Top = MaxPClockLabel->Top;

	IncludeRangeLimits->Width = CheckBoxWidth + Canvas->TextWidth(IncludeRangeLimits->Caption);
	IncludeRangeLimits->Height = CheckBoxHeight;
	IncludeRangeLimits->Left = MaxPClockLabel->Left;
	IncludeRangeLimits->Top = MaxPClock->Top + MaxPClock->Height + Scale + CheckBoxTop;

	RangeLimitsGroupBox->Width = SerialNumberGroupBox->Width;
	RangeLimitsGroupBox->Height = IncludeRangeLimits->Top + IncludeRangeLimits->Height + CheckBoxBottom + PaddingBottom;
	RangeLimitsGroupBox->Left = SerialNumberGroupBox->Left;
	RangeLimitsGroupBox->Top = SerialNumberGroupBox->Top + SerialNumberGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = RangeLimitsGroupBox->Top + RangeLimitsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = RangeLimitsGroupBox->Left + RangeLimitsGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::FormShow(TObject *Sender)
{
	InitColorDepthComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::DeviceIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetDeviceID(DeviceID->Text.c_str());
	Refresh(DeviceIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::DeviceIDExit(TObject *Sender)
{
	Refresh(DeviceIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::DeviceIDResetButtonClick(TObject *Sender)
{
	Properties->ResetDeviceID();
	Refresh(DeviceIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialIDChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetSerialID(TextToDecimal(SerialID->Text.c_str(), 0));
	Refresh(DeviceIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialIDExit(TObject *Sender)
{
	Refresh(DeviceIDGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::YCbCr422Click(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetYCbCr422(YCbCr422->Checked);
	Refresh(ColorFormatsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::YCbCr444Click(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetYCbCr444(YCbCr444->Checked);
	Refresh(ColorFormatsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::ColorDepthComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetColorDepth(ColorDepthComboBox->ItemIndex);
	Refresh(ColorFormatsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::NameChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetName(Name->Text.c_str());
	Refresh(NameGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::NameExit(TObject *Sender)
{
	Refresh(NameGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::IncludeNameClick(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetIncludeName(IncludeName->Checked);
	Refresh(NameGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialNumberChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetSerialNumber(SerialNumber->Text.c_str());
	Refresh(SerialNumberGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::SerialNumberExit(TObject *Sender)
{
	Refresh(SerialNumberGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::IncludeSerialNumberClick(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetIncludeSerialNumber(IncludeSerialNumber->Checked);
	Refresh(SerialNumberGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMinVRate(TextToInteger(MinVRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinVRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxVRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMaxVRate(TextToInteger(MaxVRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxVRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinHRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMinHRate(TextToInteger(MinHRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MinHRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxHRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMaxHRate(TextToInteger(MaxHRate->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxHRateExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxPClockChange(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetMaxPClock(TextToInteger(MaxPClock->Text.c_str()));
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::MaxPClockExit(TObject *Sender)
{
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesForm::IncludeRangeLimitsClick(TObject *Sender)
{
	if (Refreshing)
		return;

	Properties->SetIncludeRangeLimits(IncludeRangeLimits->Checked);
	Refresh(RangeLimitsGroupBox);
}
//---------------------------------------------------------------------------
