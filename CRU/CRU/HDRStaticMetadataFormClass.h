//---------------------------------------------------------------------------
#ifndef HDRStaticMetadataFormClassH
#define HDRStaticMetadataFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "HDRStaticMetadataClass.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class THDRStaticMetadataForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *LuminanceLabel0;
	TLabel *LuminanceLabel1;
	TLabel *LuminanceLabel2;
	TGroupBox *EOTFGroupBox;
	TCheckBox *EOTFCheckBox0;
	TCheckBox *EOTFCheckBox1;
	TCheckBox *EOTFCheckBox2;
	TCheckBox *EOTFCheckBox3;
	TGroupBox *TypeGroupBox;
	TCheckBox *TypeCheckBox0;
	TGroupBox *LuminanceGroupBox;
	TEdit *Luminance0;
	TEdit *Luminance1;
	TEdit *Luminance2;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EOTFCheckBoxClick(TObject *Sender);
	void __fastcall TypeCheckBoxClick(TObject *Sender);
	void __fastcall LuminanceChange(TObject *Sender);
	void __fastcall LuminanceExit(TObject *Sender);
private:	// User declarations
	HDRStaticMetadataClass *HDRStaticMetadata;
	bool Refreshing;
public:		// User declarations
	__fastcall THDRStaticMetadataForm(TComponent *Owner);
	bool Connect(HDRStaticMetadataClass &);
	bool Refresh(void *);
	bool RefreshEOTFCheckBoxes();
	bool RefreshTypeCheckBoxes();
	bool RefreshLuminanceCaption();
	bool RefreshLuminanceTextBoxes();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE THDRStaticMetadataForm *HDRStaticMetadataForm;
//---------------------------------------------------------------------------
#endif
