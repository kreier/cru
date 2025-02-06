//---------------------------------------------------------------------------
#ifndef AudioFormatFormClassH
#define AudioFormatFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "AudioFormatClass.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAudioFormatForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *ChannelsLabel;
	TLabel *Channels3DRangeLabel;
	TLabel *LevelLabel;
	TLabel *BitRateLabel;
	TLabel *FlagsRangeLabel;
	TLabel *ProfileRangeLabel;
	TLabel *ExtensionRangeLabel;
	TLabel *ExtensionFlagsRangeLabel;
	TGroupBox *FormatGroupBox;
	TComboBox *FormatComboBox;
	TComboBox *ChannelsComboBox;
	TEdit *Channels3D;
	TComboBox *LevelComboBox;
	TGroupBox *SampleRatesGroupBox;
	TCheckBox *SampleRateCheckBox0;
	TCheckBox *SampleRateCheckBox1;
	TCheckBox *SampleRateCheckBox2;
	TCheckBox *SampleRateCheckBox3;
	TCheckBox *SampleRateCheckBox4;
	TCheckBox *SampleRateCheckBox5;
	TCheckBox *SampleRateCheckBox6;
	TGroupBox *BitDepthsGroupBox;
	TCheckBox *BitDepthCheckBox0;
	TCheckBox *BitDepthCheckBox1;
	TCheckBox *BitDepthCheckBox2;
	TGroupBox *BitRateGroupBox;
	TEdit *BitRate;
	TGroupBox *FlagsGroupBox;
	TEdit *Flags;
	TGroupBox *ProfileGroupBox;
	TEdit *Profile;
	TGroupBox *FrameLengthsGroupBox;
	TCheckBox *FrameLength960;
	TCheckBox *FrameLength1024;
	TGroupBox *SystemHGroupBox;
	TCheckBox *SystemH;
	TGroupBox *MPEGSurroundGroupBox;
	TRadioButton *ExplicitMPS0;
	TRadioButton *ExplicitMPS1;
	TGroupBox *ProfilesGroupBox;
	TCheckBox *LowComplexity;
	TCheckBox *Baseline;
	TGroupBox *ExtensionGroupBox;
	TEdit *Extension;
	TGroupBox *ExtensionFlagsGroupBox;
	TEdit *ExtensionFlags;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormatComboBoxChange(TObject *Sender);
	void __fastcall ChannelsComboBoxChange(TObject *Sender);
	void __fastcall Channels3DChange(TObject *Sender);
	void __fastcall Channels3DExit(TObject *Sender);
	void __fastcall LevelComboBoxChange(TObject *Sender);
	void __fastcall SampleRateCheckBoxClick(TObject *Sender);
	void __fastcall BitDepthCheckBoxClick(TObject *Sender);
	void __fastcall BitRateChange(TObject *Sender);
	void __fastcall BitRateExit(TObject *Sender);
	void __fastcall FlagsChange(TObject *Sender);
	void __fastcall FlagsExit(TObject *Sender);
	void __fastcall ProfileChange(TObject *Sender);
	void __fastcall ProfileExit(TObject *Sender);
	void __fastcall FrameLength960Click(TObject *Sender);
	void __fastcall FrameLength1024Click(TObject *Sender);
	void __fastcall SystemHClick(TObject *Sender);
	void __fastcall ExplicitMPSClick(TObject *Sender);
	void __fastcall LowComplexityClick(TObject *Sender);
	void __fastcall BaselineClick(TObject *Sender);
	void __fastcall ExtensionChange(TObject *Sender);
	void __fastcall ExtensionExit(TObject *Sender);
	void __fastcall ExtensionFlagsChange(TObject *Sender);
	void __fastcall ExtensionFlagsExit(TObject *Sender);
private:	// User declarations
	AudioFormatClass *AudioFormat;
	bool Refreshing;
public:		// User declarations
	__fastcall TAudioFormatForm(TComponent *Owner);
	bool Connect(AudioFormatClass &);
	bool Refresh(void *);
	bool InitFormatComboBox();
	bool InitChannelsComboBox();
	bool InitLevelComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TAudioFormatForm *AudioFormatForm;
//---------------------------------------------------------------------------
#endif
