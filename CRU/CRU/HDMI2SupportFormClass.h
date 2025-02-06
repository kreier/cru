//---------------------------------------------------------------------------
#ifndef HDMI2SupportFormClassH
#define HDMI2SupportFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "HDMI2SupportClass.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class THDMI2SupportForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *TMDSRateLabel;
	TLabel *VRateLabel;
	TShape *VRateDash;
	TLabel *HzLabel;
	TLabel *DSCFRLRateLabel;
	TLabel *DSCSlicesLabel;
	TLabel *DSCChunkSizeLabel;
	TLabel *DSCChunkSizeUnitsLabel;
	TGroupBox *TMDSRateGroupBox;
	TCheckBox *OverrideTMDSRate;
	TEdit *TMDSRate;
	TGroupBox *FeaturesGroupBox;
	TCheckBox *FeaturesCheckBox7;
	TCheckBox *FeaturesCheckBox6;
	TCheckBox *FeaturesCheckBox4;
	TCheckBox *FeaturesCheckBox3;
	TCheckBox *FeaturesCheckBox2;
	TCheckBox *FeaturesCheckBox1;
	TCheckBox *FeaturesCheckBox0;
	TGroupBox *ColorFormatsGroupBox;
	TCheckBox *ColorFormatsCheckBox0;
	TCheckBox *ColorFormatsCheckBox1;
	TCheckBox *ColorFormatsCheckBox2;
	TGroupBox *RefreshRateGroupBox;
	TEdit *MinVRate;
	TEdit *MaxVRate;
	TCheckBox *Features21CheckBox5;
	TCheckBox *Features21CheckBox4;
	TCheckBox *Features21CheckBox3;
	TGroupBox *FRLRateGroupBox;
	TComboBox *FRLRateComboBox;
	TGroupBox *Features21GroupBox;
	TCheckBox *Features21CheckBox2;
	TCheckBox *Features21CheckBox1;
	TCheckBox *Features21CheckBox0;
	TGroupBox *DSCGroupBox;
	TCheckBox *DSCCheckBox7;
	TCheckBox *DSCCheckBox6;
	TCheckBox *DSCCheckBox0;
	TCheckBox *DSCCheckBox1;
	TCheckBox *DSCCheckBox2;
	TCheckBox *DSCCheckBox3;
	TComboBox *DSCFRLRateComboBox;
	TComboBox *DSCSlicesComboBox;
	TEdit *DSCChunkSize;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OverrideTMDSRateClick(TObject *Sender);
	void __fastcall TMDSRateChange(TObject *Sender);
	void __fastcall TMDSRateExit(TObject *Sender);
	void __fastcall FeaturesCheckBoxClick(TObject *Sender);
	void __fastcall ColorFormatsCheckBoxClick(TObject *Sender);
	void __fastcall FRLRateComboBoxChange(TObject *Sender);
	void __fastcall Features21CheckBoxClick(TObject *Sender);
	void __fastcall MinVRateChange(TObject *Sender);
	void __fastcall MinVRateExit(TObject *Sender);
	void __fastcall MaxVRateChange(TObject *Sender);
	void __fastcall MaxVRateExit(TObject *Sender);
	void __fastcall DSCCheckBoxClick(TObject *Sender);
	void __fastcall DSCFRLRateComboBoxChange(TObject *Sender);
	void __fastcall DSCSlicesComboBoxChange(TObject *Sender);
	void __fastcall DSCChunkSizeChange(TObject *Sender);
	void __fastcall DSCChunkSizeExit(TObject *Sender);
private:	// User declarations
	HDMI2SupportClass *HDMI2Support;
	bool Refreshing;
public:		// User declarations
	__fastcall THDMI2SupportForm(TComponent *Owner);
	bool Connect(HDMI2SupportClass &);
	bool Refresh(void *);
	bool RefreshTMDSRateCheckBox();
	bool RefreshTMDSRateTextBox();
	bool RefreshFeaturesCheckBoxes();
	bool RefreshColorFormatsCheckBoxes();
	bool RefreshFRLRateComboBox();
	bool RefreshFeatures21Caption();
	bool RefreshFeatures21CheckBoxes();
	bool RefreshRefreshRateCaption();
	bool RefreshRefreshRateTextBoxes();
	bool RefreshDSCCaption();
	bool RefreshDSCCheckBoxes();
	bool RefreshDSCFRLRateComboBox();
	bool RefreshDSCSlicesComboBox();
	bool RefreshDSCChunkSizeTextBox();
	bool InitFRLRateComboBox();
	bool InitDSCFRLRateComboBox();
	bool InitDSCSlicesComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE THDMI2SupportForm *HDMI2SupportForm;
//---------------------------------------------------------------------------
#endif
