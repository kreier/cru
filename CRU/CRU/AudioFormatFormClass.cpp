//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "AudioFormatFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAudioFormatForm *AudioFormatForm;
//---------------------------------------------------------------------------
__fastcall TAudioFormatForm::TAudioFormatForm(TComponent *Owner) : TCommonForm(Owner)
{
	Refreshing = false;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::Connect(AudioFormatClass &NewAudioFormat)
{
	AudioFormat = &NewAudioFormat;
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::Refresh(void *Value)
{
	char Text[TEXTSIZE];

	Refreshing = true;

	switch (AudioFormat->GetMaxChannels())
	{
		case 5:
			ChannelsLabel->Visible = false;
			ChannelsComboBox->Visible = false;
			Channels3D->Visible = false;
			Channels3DRangeLabel->Visible = false;
			LevelLabel->Visible = true;
			LevelComboBox->Visible = true;
			FormatGroupBox->Height = LevelComboBox->Top + LevelComboBox->Height + PaddingBottom;
			break;

		case 8:
			ChannelsLabel->Visible = true;
			ChannelsComboBox->Visible = true;
			Channels3D->Visible = false;
			Channels3DRangeLabel->Visible = false;
			ChannelsLabel->Top = ChannelsComboBox->Top + 4;
			LevelLabel->Visible = false;
			LevelComboBox->Visible = false;
			FormatGroupBox->Height = ChannelsComboBox->Top + ChannelsComboBox->Height + PaddingBottom;
			break;

		case 32:
			ChannelsLabel->Visible = true;
			ChannelsComboBox->Visible = false;
			Channels3D->Visible = true;
			Channels3DRangeLabel->Visible = true;
			ChannelsLabel->Top = Channels3D->Top + 3;
			LevelLabel->Visible = false;
			LevelComboBox->Visible = false;
			FormatGroupBox->Height = ChannelsComboBox->Top + ChannelsComboBox->Height + PaddingBottom;
			break;

		default:
			ChannelsLabel->Visible = false;
			ChannelsComboBox->Visible = false;
			Channels3D->Visible = false;
			Channels3DRangeLabel->Visible = false;
			LevelLabel->Visible = false;
			LevelComboBox->Visible = false;
			FormatGroupBox->Height = FormatComboBox->Top + FormatComboBox->Height + PaddingBottom;
			break;
	}

	switch (AudioFormat->GetSampleRates())
	{
		case 127:
			SampleRateCheckBox0->Visible = true;
			SampleRateCheckBox1->Visible = true;
			SampleRateCheckBox2->Visible = true;
			SampleRateCheckBox3->Visible = true;
			SampleRateCheckBox4->Visible = true;
			SampleRateCheckBox5->Visible = true;
			SampleRateCheckBox6->Visible = true;
			SampleRateCheckBox0->Top = PaddingTop + CheckBoxTop;
			SampleRateCheckBox1->Top = SampleRateCheckBox0->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox2->Top = SampleRateCheckBox1->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox3->Top = SampleRateCheckBox2->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox4->Top = SampleRateCheckBox3->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox5->Top = SampleRateCheckBox4->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox6->Top = SampleRateCheckBox5->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRatesGroupBox->Height = SampleRateCheckBox6->Top + SampleRateCheckBox6->Height + CheckBoxBottom + PaddingBottom;
			break;

		case 31:
			SampleRateCheckBox0->Visible = true;
			SampleRateCheckBox1->Visible = true;
			SampleRateCheckBox2->Visible = true;
			SampleRateCheckBox3->Visible = true;
			SampleRateCheckBox4->Visible = true;
			SampleRateCheckBox5->Visible = false;
			SampleRateCheckBox6->Visible = false;
			SampleRateCheckBox0->Top = PaddingTop + CheckBoxTop;
			SampleRateCheckBox1->Top = SampleRateCheckBox0->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox2->Top = SampleRateCheckBox1->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox3->Top = SampleRateCheckBox2->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox4->Top = SampleRateCheckBox3->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRatesGroupBox->Height = SampleRateCheckBox4->Top + SampleRateCheckBox4->Height + CheckBoxBottom + PaddingBottom;
			break;

		case 86:
			SampleRateCheckBox0->Visible = false;
			SampleRateCheckBox1->Visible = true;
			SampleRateCheckBox2->Visible = true;
			SampleRateCheckBox3->Visible = false;
			SampleRateCheckBox4->Visible = true;
			SampleRateCheckBox5->Visible = false;
			SampleRateCheckBox6->Visible = true;
			SampleRateCheckBox1->Top = PaddingTop + CheckBoxTop;
			SampleRateCheckBox2->Top = SampleRateCheckBox1->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox4->Top = SampleRateCheckBox2->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRateCheckBox6->Top = SampleRateCheckBox4->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;
			SampleRatesGroupBox->Height = SampleRateCheckBox6->Top + SampleRateCheckBox6->Height + CheckBoxBottom + PaddingBottom;
			break;
	}

	SampleRatesGroupBox->Top = FormatGroupBox->Top + FormatGroupBox->Height + GroupBoxBottom + GroupBoxTop;
	FrameLengthsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;
	SystemHGroupBox->Top = FrameLengthsGroupBox->Top + FrameLengthsGroupBox->Height + GroupBoxBottom + GroupBoxTop;
	MPEGSurroundGroupBox->Top = FrameLengthsGroupBox->Top + FrameLengthsGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	switch (AudioFormat->GetType())
	{
		case AUDIO_NONE:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_BIT_DEPTHS:
			BitDepthsGroupBox->Visible = true;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = BitDepthsGroupBox->Top + BitDepthsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_BIT_RATE:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = true;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = BitRateGroupBox->Top + BitRateGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_FLAGS:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = true;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = FlagsGroupBox->Top + FlagsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_PROFILE:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = true;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = ProfileGroupBox->Top + ProfileGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_MPEG4:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = true;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = FrameLengthsGroupBox->Top + FrameLengthsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_MPEG4_H:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = true;
			SystemHGroupBox->Visible = true;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = SystemHGroupBox->Top + SystemHGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_MPEG4_MPS:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = true;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = true;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = MPEGSurroundGroupBox->Top + MPEGSurroundGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_MPEGH_3D:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = true;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = false;
			FormOKButton->Top = ProfilesGroupBox->Top + ProfilesGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_EXTENSION_FLAGS:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = false;
			ExtensionFlagsGroupBox->Visible = true;
			ExtensionFlagsGroupBox->Width = SampleRatesGroupBox->Width;
			ExtensionFlagsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;
			ExtensionFlagsGroupBox->Left = SampleRatesGroupBox->Left;
			FormOKButton->Top = ExtensionFlagsGroupBox->Top + ExtensionFlagsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;

		case AUDIO_EXTENSION:
			BitDepthsGroupBox->Visible = false;
			BitRateGroupBox->Visible = false;
			FlagsGroupBox->Visible = false;
			ProfileGroupBox->Visible = false;
			FrameLengthsGroupBox->Visible = false;
			SystemHGroupBox->Visible = false;
			MPEGSurroundGroupBox->Visible = false;
			ProfilesGroupBox->Visible = false;
			ExtensionGroupBox->Visible = true;
			ExtensionFlagsGroupBox->Visible = true;
			ExtensionFlagsGroupBox->Width = ExtensionGroupBox->Width;
			ExtensionFlagsGroupBox->Top = ExtensionGroupBox->Top;
			ExtensionFlagsGroupBox->Left = ExtensionGroupBox->Left + ExtensionGroupBox->Width + Scale;
			FormOKButton->Top = ExtensionFlagsGroupBox->Top + ExtensionFlagsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
			break;
	}

	FormCancelButton->Top = FormOKButton->Top;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;

	if (Value != FormatComboBox)
		FormatComboBox->ItemIndex = AudioFormat->GetFormat() - 1;

	if (Value != ChannelsComboBox)
		ChannelsComboBox->ItemIndex = AudioFormat->GetChannels() - 1;

	if (Value != Channels3D && IntegerToText(AudioFormat->GetChannels3D(), Text, TEXTSIZE))
		Channels3D->Text = Text;

	if (Value != LevelComboBox)
		LevelComboBox->ItemIndex = AudioFormat->GetLevel();

	Channels3D->Font->Color = GetTextColor(AudioFormat->IsValidChannels3D());

	if (Value != SampleRatesGroupBox)
	{
		SampleRateCheckBox0->Checked = AudioFormat->GetSampleRate(0);
		SampleRateCheckBox1->Checked = AudioFormat->GetSampleRate(1);
		SampleRateCheckBox2->Checked = AudioFormat->GetSampleRate(2);
		SampleRateCheckBox3->Checked = AudioFormat->GetSampleRate(3);
		SampleRateCheckBox4->Checked = AudioFormat->GetSampleRate(4);
		SampleRateCheckBox5->Checked = AudioFormat->GetSampleRate(5);
		SampleRateCheckBox6->Checked = AudioFormat->GetSampleRate(6);
	}

	if (Value != BitDepthsGroupBox)
	{
		BitDepthCheckBox0->Checked = AudioFormat->GetBitDepth(0);
		BitDepthCheckBox1->Checked = AudioFormat->GetBitDepth(1);
		BitDepthCheckBox2->Checked = AudioFormat->GetBitDepth(2);
	}

	if (Value != BitRate && IntegerToText(AudioFormat->GetBitRate(), Text, TEXTSIZE))
		BitRate->Text = Text;

	BitRate->Font->Color = GetTextColor(AudioFormat->IsValidBitRate());

	if (Value != Flags && IntegerToText(AudioFormat->GetFlags(), Text, TEXTSIZE))
		Flags->Text = Text;

	Flags->Font->Color = GetTextColor(AudioFormat->IsValidFlags());

	if (Value != Profile && IntegerToText(AudioFormat->GetProfile(), Text, TEXTSIZE))
		Profile->Text = Text;

	Profile->Font->Color = GetTextColor(AudioFormat->IsValidProfile());

	if (Value != FrameLengthsGroupBox)
	{
		FrameLength960->Checked = AudioFormat->GetFrameLength960();
		FrameLength1024->Checked = AudioFormat->GetFrameLength1024();
	}

	if (Value != SystemHGroupBox)
		SystemH->Checked = AudioFormat->GetSystemH();

	if (Value != MPEGSurroundGroupBox)
	{
		ExplicitMPS0->Checked = !AudioFormat->GetExplicitMPS();
		ExplicitMPS1->Checked = AudioFormat->GetExplicitMPS();
	}

	if (Value != ProfilesGroupBox)
	{
		LowComplexity->Checked = AudioFormat->GetLowComplexity();
		Baseline->Checked = AudioFormat->GetBaseline();
	}

	if (Value != Extension && IntegerToText(AudioFormat->GetExtension(), Text, TEXTSIZE))
		Extension->Text = Text;

	Extension->Font->Color = GetTextColor(AudioFormat->IsValidExtension());

	if (Value != ExtensionFlags && IntegerToText(AudioFormat->GetExtensionFlags(), Text, TEXTSIZE))
		ExtensionFlags->Text = Text;

	ExtensionFlags->Font->Color = GetTextColor(AudioFormat->IsValidExtensionFlags());

	if (Value != FormOKButton)
		FormOKButton->Enabled = AudioFormat->IsValid();

	Refreshing = false;
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::InitFormatComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = FormatComboBox->ItemIndex;
	FormatComboBox->Items->BeginUpdate();
	FormatComboBox->Clear();

	for (Index = 0; AudioFormat->GetFormatText(Index + 1, Text, TEXTSIZE); Index++)
		FormatComboBox->Items->Add(Text);

	FormatComboBox->ItemIndex = ItemIndex;
	FormatComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::InitChannelsComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = ChannelsComboBox->ItemIndex;
	ChannelsComboBox->Items->BeginUpdate();
	ChannelsComboBox->Clear();

	for (Index = 0; AudioFormat->GetChannelsText(Index + 1, Text, TEXTSIZE); Index++)
		ChannelsComboBox->Items->Add(Text);

	ChannelsComboBox->ItemIndex = ItemIndex;
	ChannelsComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::InitLevelComboBox()
{
	int ItemIndex;
	int Index;
	char Text[TEXTSIZE];

	ItemIndex = LevelComboBox->ItemIndex;
	LevelComboBox->Items->BeginUpdate();
	LevelComboBox->Clear();

	for (Index = 0; AudioFormat->GetLevelText(Index, Text, TEXTSIZE); Index++)
		LevelComboBox->Items->Add(Text);

	LevelComboBox->ItemIndex = ItemIndex;
	LevelComboBox->Items->EndUpdate();
	return true;
}
//---------------------------------------------------------------------------
bool TAudioFormatForm::ScaleControls()
{
	FormatComboBox->Width = FormButtonsWidth - PaddingWidth * 2;
	FormatComboBox->Height = ComboBoxHeight;
	FormatComboBox->Left = PaddingWidth;
	FormatComboBox->Top = PaddingTop;

	ChannelsComboBox->Width = FormatComboBox->Width - ChannelsLabel->Width - LabelSpacing;
	ChannelsComboBox->Height = ComboBoxHeight;

	ChannelsLabel->Left = FormatComboBox->Left;
	ChannelsComboBox->Left = ChannelsLabel->Left + ChannelsLabel->Width + LabelSpacing;

	ChannelsComboBox->Top = FormatComboBox->Top + FormatComboBox->Height + Scale;
	ChannelsLabel->Top = ChannelsComboBox->Top + 4;

	Channels3D->AutoSize = false;
	Channels3D->Width = FormatComboBox->Width - ChannelsLabel->Width - LabelSpacing - PostLabelSpacing - Channels3DRangeLabel->Width;
	Channels3D->Height = TextBoxHeight;

	Channels3D->Left = ChannelsComboBox->Left;
	Channels3DRangeLabel->Left = Channels3D->Left + Channels3D->Width + PostLabelSpacing;

	Channels3D->Top = ChannelsComboBox->Top;
	Channels3DRangeLabel->Top = Channels3D->Top + 3;

	LevelComboBox->Width = FormatComboBox->Width - LevelLabel->Width - LabelSpacing;
	LevelComboBox->Height = ComboBoxHeight;

	LevelLabel->Left = FormatComboBox->Left;
	LevelComboBox->Left = LevelLabel->Left + LevelLabel->Width + LabelSpacing;

	LevelComboBox->Top = FormatComboBox->Top + FormatComboBox->Height + Scale;
	LevelLabel->Top = LevelComboBox->Top + 4;

	FormatGroupBox->Width = FormatComboBox->Left + FormatComboBox->Width + PaddingWidth;
	FormatGroupBox->Height = ChannelsComboBox->Top + ChannelsComboBox->Height + PaddingBottom;
	FormatGroupBox->Left = Scale;
	FormatGroupBox->Top = GroupBoxTop;

	SampleRateCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox0->Caption);
	SampleRateCheckBox0->Height = CheckBoxHeight;
	SampleRateCheckBox0->Left = PaddingWidth;
	SampleRateCheckBox0->Top = PaddingTop + CheckBoxTop;

	SampleRateCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox1->Caption);
	SampleRateCheckBox1->Height = CheckBoxHeight;
	SampleRateCheckBox1->Left = SampleRateCheckBox0->Left;
	SampleRateCheckBox1->Top = SampleRateCheckBox0->Top + SampleRateCheckBox0->Height + CheckBoxSpacing;

	SampleRateCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox2->Caption);
	SampleRateCheckBox2->Height = CheckBoxHeight;
	SampleRateCheckBox2->Left = SampleRateCheckBox1->Left;
	SampleRateCheckBox2->Top = SampleRateCheckBox1->Top + SampleRateCheckBox1->Height + CheckBoxSpacing;

	SampleRateCheckBox3->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox3->Caption);
	SampleRateCheckBox3->Height = CheckBoxHeight;
	SampleRateCheckBox3->Left = SampleRateCheckBox2->Left;
	SampleRateCheckBox3->Top = SampleRateCheckBox2->Top + SampleRateCheckBox2->Height + CheckBoxSpacing;

	SampleRateCheckBox4->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox4->Caption);
	SampleRateCheckBox4->Height = CheckBoxHeight;
	SampleRateCheckBox4->Left = SampleRateCheckBox3->Left;
	SampleRateCheckBox4->Top = SampleRateCheckBox3->Top + SampleRateCheckBox3->Height + CheckBoxSpacing;

	SampleRateCheckBox5->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox5->Caption);
	SampleRateCheckBox5->Height = CheckBoxHeight;
	SampleRateCheckBox5->Left = SampleRateCheckBox4->Left;
	SampleRateCheckBox5->Top = SampleRateCheckBox4->Top + SampleRateCheckBox4->Height + CheckBoxSpacing;

	SampleRateCheckBox6->Width = CheckBoxWidth + Canvas->TextWidth(SampleRateCheckBox6->Caption);
	SampleRateCheckBox6->Height = CheckBoxHeight;
	SampleRateCheckBox6->Left = SampleRateCheckBox5->Left;
	SampleRateCheckBox6->Top = SampleRateCheckBox5->Top + SampleRateCheckBox5->Height + CheckBoxSpacing;

	SampleRatesGroupBox->Width = FormatGroupBox->Width;
	SampleRatesGroupBox->Height = SampleRateCheckBox6->Top + SampleRateCheckBox6->Height + CheckBoxBottom + PaddingBottom;
	SampleRatesGroupBox->Left = FormatGroupBox->Left;
	SampleRatesGroupBox->Top = FormatGroupBox->Top + FormatGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	BitDepthCheckBox0->Width = CheckBoxWidth + Canvas->TextWidth(BitDepthCheckBox0->Caption);
	BitDepthCheckBox0->Height = CheckBoxHeight;
	BitDepthCheckBox0->Left = PaddingWidth;
	BitDepthCheckBox0->Top = PaddingTop + CheckBoxTop;

	BitDepthCheckBox1->Width = CheckBoxWidth + Canvas->TextWidth(BitDepthCheckBox1->Caption);
	BitDepthCheckBox1->Height = CheckBoxHeight;
	BitDepthCheckBox1->Left = BitDepthCheckBox0->Left;
	BitDepthCheckBox1->Top = BitDepthCheckBox0->Top + BitDepthCheckBox0->Height + CheckBoxSpacing;

	BitDepthCheckBox2->Width = CheckBoxWidth + Canvas->TextWidth(BitDepthCheckBox2->Caption);
	BitDepthCheckBox2->Height = CheckBoxHeight;
	BitDepthCheckBox2->Left = BitDepthCheckBox1->Left;
	BitDepthCheckBox2->Top = BitDepthCheckBox1->Top + BitDepthCheckBox1->Height + CheckBoxSpacing;

	BitDepthsGroupBox->Width = SampleRatesGroupBox->Width;
	BitDepthsGroupBox->Height = BitDepthCheckBox2->Top + BitDepthCheckBox2->Height + CheckBoxBottom + PaddingBottom;
	BitDepthsGroupBox->Left = SampleRatesGroupBox->Left;
	BitDepthsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	BitRate->AutoSize = false;
	BitRate->Width = BitRate->MaxLength * NumberWidth + TextBoxPadding;
	BitRate->Height = TextBoxHeight;
	BitRate->Left = PaddingWidth;
	BitRate->Top = PaddingTop;

	BitRateLabel->Left = BitRate->Left + BitRate->Width + PostLabelSpacing;
	BitRateLabel->Top = BitRate->Top + 3;

	BitRateGroupBox->Width = SampleRatesGroupBox->Width;
	BitRateGroupBox->Height = BitRate->Top + BitRate->Height + PaddingBottom;
	BitRateGroupBox->Left = SampleRatesGroupBox->Left;
	BitRateGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	Flags->AutoSize = false;
	Flags->Width = Flags->MaxLength * NumberWidth + TextBoxPadding;
	Flags->Height = TextBoxHeight;
	Flags->Left = PaddingWidth;
	Flags->Top = PaddingTop;

	FlagsRangeLabel->Left = Flags->Left + Flags->Width + PostLabelSpacing;
	FlagsRangeLabel->Top = Flags->Top + 3;

	FlagsGroupBox->Width = SampleRatesGroupBox->Width;
	FlagsGroupBox->Height = Flags->Top + Flags->Height + PaddingBottom;
	FlagsGroupBox->Left = SampleRatesGroupBox->Left;
	FlagsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	Profile->AutoSize = false;
	Profile->Width = TextBoxHeight;
	Profile->Height = TextBoxHeight;
	Profile->Left = PaddingWidth;
	Profile->Top = PaddingTop;

	ProfileRangeLabel->Left = Profile->Left + Profile->Width + PostLabelSpacing;
	ProfileRangeLabel->Top = Profile->Top + 3;

	ProfileGroupBox->Width = SampleRatesGroupBox->Width;
	ProfileGroupBox->Height = Profile->Top + Profile->Height + PaddingBottom;
	ProfileGroupBox->Left = SampleRatesGroupBox->Left;
	ProfileGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FrameLength960->Width = CheckBoxWidth + Canvas->TextWidth(FrameLength960->Caption);
	FrameLength960->Height = CheckBoxHeight;
	FrameLength960->Left = PaddingWidth;
	FrameLength960->Top = PaddingTop + CheckBoxTop;

	FrameLength1024->Width = CheckBoxWidth + Canvas->TextWidth(FrameLength1024->Caption);
	FrameLength1024->Height = CheckBoxHeight;
	FrameLength1024->Left = FrameLength960->Left;
	FrameLength1024->Top = FrameLength960->Top + FrameLength960->Height + CheckBoxSpacing;

	FrameLengthsGroupBox->Width = SampleRatesGroupBox->Width;
	FrameLengthsGroupBox->Height = FrameLength1024->Top + FrameLength1024->Height + CheckBoxBottom + PaddingBottom;
	FrameLengthsGroupBox->Left = SampleRatesGroupBox->Left;
	FrameLengthsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	SystemH->Width = CheckBoxWidth + Canvas->TextWidth(SystemH->Caption);
	SystemH->Height = CheckBoxHeight;
	SystemH->Left = PaddingWidth;
	SystemH->Top = PaddingTop + CheckBoxTop;

	SystemHGroupBox->Width = FrameLengthsGroupBox->Width;
	SystemHGroupBox->Height = SystemH->Top + SystemH->Height + CheckBoxBottom + PaddingBottom;
	SystemHGroupBox->Left = FrameLengthsGroupBox->Left;
	SystemHGroupBox->Top = FrameLengthsGroupBox->Top + FrameLengthsGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	ExplicitMPS0->Width = RadioButtonWidth + Canvas->TextWidth(ExplicitMPS0->Caption);
	ExplicitMPS0->Height = RadioButtonHeight;
	ExplicitMPS0->Left = PaddingWidth;
	ExplicitMPS0->Top = PaddingTop + RadioButtonTop;

	ExplicitMPS1->Width = RadioButtonWidth + Canvas->TextWidth(ExplicitMPS1->Caption);
	ExplicitMPS1->Height = RadioButtonHeight;
	ExplicitMPS1->Left = ExplicitMPS0->Left;
	ExplicitMPS1->Top = ExplicitMPS0->Top + ExplicitMPS0->Height + RadioButtonSpacing;

	MPEGSurroundGroupBox->Width = FrameLengthsGroupBox->Width;
	MPEGSurroundGroupBox->Height = ExplicitMPS1->Top + ExplicitMPS1->Height + RadioButtonBottom + PaddingBottom;
	MPEGSurroundGroupBox->Left = FrameLengthsGroupBox->Left;
	MPEGSurroundGroupBox->Top = FrameLengthsGroupBox->Top + FrameLengthsGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	LowComplexity->Width = CheckBoxWidth + Canvas->TextWidth(LowComplexity->Caption);
	LowComplexity->Height = CheckBoxHeight;
	LowComplexity->Left = PaddingWidth;
	LowComplexity->Top = PaddingTop + CheckBoxTop;

	Baseline->Width = CheckBoxWidth + Canvas->TextWidth(Baseline->Caption);
	Baseline->Height = CheckBoxHeight;
	Baseline->Left = LowComplexity->Left;
	Baseline->Top = LowComplexity->Top + LowComplexity->Height + CheckBoxSpacing;

	ProfilesGroupBox->Width = SampleRatesGroupBox->Width;
	ProfilesGroupBox->Height = Baseline->Top + Baseline->Height + CheckBoxBottom + PaddingBottom;
	ProfilesGroupBox->Left = SampleRatesGroupBox->Left;
	ProfilesGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	Extension->AutoSize = false;
	Extension->Width = TextBoxHeight;
	Extension->Height = TextBoxHeight;
	Extension->Left = PaddingWidth;
	Extension->Top = PaddingTop;

	ExtensionRangeLabel->Left = Extension->Left + Extension->Width + PostLabelSpacing;
	ExtensionRangeLabel->Top = Extension->Top + 3;

	ExtensionGroupBox->Width = ButtonLeft + FormButtonWidth + ButtonRight;
	ExtensionGroupBox->Height = Extension->Top + Extension->Height + PaddingBottom;
	ExtensionGroupBox->Left = SampleRatesGroupBox->Left;
	ExtensionGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	ExtensionFlags->AutoSize = false;
	ExtensionFlags->Width = TextBoxHeight;
	ExtensionFlags->Height = TextBoxHeight;
	ExtensionFlags->Left = PaddingWidth;
	ExtensionFlags->Top = PaddingTop;

	ExtensionFlagsRangeLabel->Left = ExtensionFlags->Left + ExtensionFlags->Width + PostLabelSpacing;
	ExtensionFlagsRangeLabel->Top = ExtensionFlags->Top + 3;

	ExtensionFlagsGroupBox->Width = SampleRatesGroupBox->Width;
	ExtensionFlagsGroupBox->Height = ExtensionFlags->Top + ExtensionFlags->Height + PaddingBottom;
	ExtensionFlagsGroupBox->Left = SampleRatesGroupBox->Left;
	ExtensionFlagsGroupBox->Top = SampleRatesGroupBox->Top + SampleRatesGroupBox->Height + GroupBoxBottom + GroupBoxTop;

	FormOKButton->Width = FormButtonWidth;
	FormOKButton->Height = FormButtonHeight;
	FormOKButton->Top = BitDepthsGroupBox->Top + BitDepthsGroupBox->Height + GroupBoxBottom + Scale + ButtonTop;
	FixButtonCaption(FormOKButton, Canvas->TextWidth(FormOKButton->Caption));

	FormCancelButton->Width = FormButtonWidth;
	FormCancelButton->Height = FormButtonHeight;
	FormCancelButton->Top = FormOKButton->Top;
	FixButtonCaption(FormCancelButton, Canvas->TextWidth(FormCancelButton->Caption));

	FormCancelButton->Left = BitDepthsGroupBox->Left + BitDepthsGroupBox->Width - ButtonRight - FormCancelButton->Width;
	FormOKButton->Left = FormCancelButton->Left - ButtonLeft - Scale - ButtonRight - FormOKButton->Width;

	ClientWidth = FormCancelButton->Left + FormCancelButton->Width + ButtonRight + Scale;
	ClientHeight = FormCancelButton->Top + FormCancelButton->Height + ButtonBottom + Scale;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FormCreate(TObject *Sender)
{
	ScaleControls();
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FormShow(TObject *Sender)
{
	InitFormatComboBox();
	InitChannelsComboBox();
	InitLevelComboBox();
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FormatComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetFormat(FormatComboBox->ItemIndex + 1);
	Refresh(FormatComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ChannelsComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetChannels(ChannelsComboBox->ItemIndex + 1);
	Refresh(ChannelsComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::Channels3DChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetChannels3D(TextToInteger(Channels3D->Text.c_str()));
	Refresh(Channels3D);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::Channels3DExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::LevelComboBoxChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetLevel(LevelComboBox->ItemIndex);
	Refresh(LevelComboBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::SampleRateCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	AudioFormat->SetSampleRate(CheckBox->Tag, CheckBox->Checked);
	Refresh(SampleRatesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BitDepthCheckBoxClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TCheckBox *CheckBox = (TCheckBox *)Sender;
	AudioFormat->SetBitDepth(CheckBox->Tag, CheckBox->Checked);
	Refresh(BitDepthsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BitRateChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetBitRate(TextToInteger(BitRate->Text.c_str()));
	Refresh(BitRate);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BitRateExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FlagsChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetFlags(TextToInteger(Flags->Text.c_str()));
	Refresh(Flags);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FlagsExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ProfileChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetProfile(TextToInteger(Profile->Text.c_str()));
	Refresh(Profile);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ProfileExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FrameLength960Click(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetFrameLength960(FrameLength960->Checked);
	Refresh(FrameLengthsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::FrameLength1024Click(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetFrameLength1024(FrameLength1024->Checked);
	Refresh(FrameLengthsGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::SystemHClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetSystemH(SystemH->Checked);
	Refresh(SystemHGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ExplicitMPSClick(TObject *Sender)
{
	if (Refreshing)
		return;

	TRadioButton *RadioButton = (TRadioButton *)Sender;
	AudioFormat->SetExplicitMPS(RadioButton->Tag);
	Refresh(MPEGSurroundGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::LowComplexityClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetLowComplexity(LowComplexity->Checked);
	Refresh(ProfilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::BaselineClick(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetBaseline(Baseline->Checked);
	Refresh(ProfilesGroupBox);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ExtensionChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetExtension(TextToInteger(Extension->Text.c_str()));
	Refresh(Extension);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ExtensionExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ExtensionFlagsChange(TObject *Sender)
{
	if (Refreshing)
		return;

	AudioFormat->SetExtensionFlags(TextToInteger(ExtensionFlags->Text.c_str()));
	Refresh(ExtensionFlags);
}
//---------------------------------------------------------------------------
void __fastcall TAudioFormatForm::ExtensionFlagsExit(TObject *Sender)
{
	Refresh(NULL);
}
//---------------------------------------------------------------------------
