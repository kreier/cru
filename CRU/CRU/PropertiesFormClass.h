//---------------------------------------------------------------------------
#ifndef PropertiesFormClassH
#define PropertiesFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "PropertiesClass.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPropertiesForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *DeviceIDLabel;
	TLabel *SerialIDLabel;
	TLabel *VRateLabel;
	TShape *VRateDash;
	TLabel *HzLabel;
	TLabel *HRateLabel;
	TShape *HRateDash;
	TLabel *kHzLabel;
	TLabel *MaxPClockLabel;
	TLabel *MHzLabel;
	TGroupBox *DeviceIDGroupBox;
	TEdit *DeviceID;
	TButton *DeviceIDResetButton;
	TEdit *SerialID;
	TGroupBox *ColorFormatsGroupBox;
	TCheckBox *YCbCr422;
	TCheckBox *YCbCr444;
	TLabel *ColorDepthLabel;
	TComboBox *ColorDepthComboBox;
	TGroupBox *NameGroupBox;
	TEdit *Name;
	TCheckBox *IncludeName;
	TGroupBox *SerialNumberGroupBox;
	TEdit *SerialNumber;
	TCheckBox *IncludeSerialNumber;
	TGroupBox *RangeLimitsGroupBox;
	TEdit *MinVRate;
	TEdit *MaxVRate;
	TEdit *MinHRate;
	TEdit *MaxHRate;
	TEdit *MaxPClock;
	TCheckBox *IncludeRangeLimits;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DeviceIDChange(TObject *Sender);
	void __fastcall DeviceIDExit(TObject *Sender);
	void __fastcall DeviceIDResetButtonClick(TObject *Sender);
	void __fastcall SerialIDChange(TObject *Sender);
	void __fastcall SerialIDExit(TObject *Sender);
	void __fastcall YCbCr422Click(TObject *Sender);
	void __fastcall YCbCr444Click(TObject *Sender);
	void __fastcall ColorDepthComboBoxChange(TObject *Sender);
	void __fastcall NameChange(TObject *Sender);
	void __fastcall NameExit(TObject *Sender);
	void __fastcall IncludeNameClick(TObject *Sender);
	void __fastcall SerialNumberChange(TObject *Sender);
	void __fastcall SerialNumberExit(TObject *Sender);
	void __fastcall IncludeSerialNumberClick(TObject *Sender);
	void __fastcall MinVRateChange(TObject *Sender);
	void __fastcall MinVRateExit(TObject *Sender);
	void __fastcall MaxVRateChange(TObject *Sender);
	void __fastcall MaxVRateExit(TObject *Sender);
	void __fastcall MinHRateChange(TObject *Sender);
	void __fastcall MinHRateExit(TObject *Sender);
	void __fastcall MaxHRateChange(TObject *Sender);
	void __fastcall MaxHRateExit(TObject *Sender);
	void __fastcall MaxPClockChange(TObject *Sender);
	void __fastcall MaxPClockExit(TObject *Sender);
	void __fastcall IncludeRangeLimitsClick(TObject *Sender);
private:	// User declarations
	PropertiesClass *Properties;
	bool Refreshing;
public:		// User declarations
	__fastcall TPropertiesForm(TComponent *Owner);
	bool Connect(PropertiesClass &);
	bool Refresh(void *);
	bool InitColorDepthComboBox();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TPropertiesForm *PropertiesForm;
//---------------------------------------------------------------------------
#endif
