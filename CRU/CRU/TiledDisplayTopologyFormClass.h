//---------------------------------------------------------------------------
#ifndef TiledDisplayTopologyFormClassH
#define TiledDisplayTopologyFormClassH
//---------------------------------------------------------------------------
#include "CommonFormClass.h"
#include "TiledDisplayTopologyClass.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTiledDisplayTopologyForm : public TCommonForm
{
__published:	// IDE-managed Components
	TLabel *VendorIDLabel;
	TLabel *ProductIDLabel;
	TLabel *SerialIDLabel;
	TLabel *TilesLabel;
	TLabel *LocationLabel;
	TLabel *SizeLabel;
	TLabel *MultiplierLabel;
	TLabel *MultiplierDivisorLabel;
	TShape *Rectangle;
	TGroupBox *TopologyIDGroupBox;
	TEdit *VendorID;
	TEdit *ProductID;
	TEdit *SerialID;
	TGroupBox *PhysicalEnclosuresGroupBox;
	TRadioButton *PhysicalEnclosuresRadioButton1;
	TRadioButton *PhysicalEnclosuresRadioButton0;
	TGroupBox *SingleTileBehaviorGroupBox;
	TRadioButton *SingleTileBehaviorRadioButton1;
	TRadioButton *SingleTileBehaviorRadioButton2;
	TRadioButton *SingleTileBehaviorRadioButton3;
	TRadioButton *SingleTileBehaviorRadioButton0;
	TGroupBox *MultipleTileBehaviorGroupBox;
	TRadioButton *MultipleTileBehaviorRadioButton1;
	TRadioButton *MultipleTileBehaviorRadioButton0;
	TGroupBox *TilesGroupBox;
	TEdit *HTiles;
	TEdit *VTiles;
	TGroupBox *LocationGroupBox;
	TEdit *HLocation;
	TEdit *VLocation;
	TGroupBox *SizeGroupBox;
	TEdit *HSize;
	TEdit *VSize;
	TGroupBox *BezelGroupBox;
	TEdit *PixelMultiplier;
	TEdit *TopBezelSize;
	TEdit *LeftBezelSize;
	TEdit *RightBezelSize;
	TEdit *BottomBezelSize;
	TButton *FormOKButton;
	TButton *FormCancelButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall VendorIDChange(TObject *Sender);
	void __fastcall VendorIDExit(TObject *Sender);
	void __fastcall ProductIDChange(TObject *Sender);
	void __fastcall ProductIDExit(TObject *Sender);
	void __fastcall SerialIDChange(TObject *Sender);
	void __fastcall SerialIDExit(TObject *Sender);
	void __fastcall EnclosuresRadioButtonClick(TObject *Sender);
	void __fastcall SingleTileBehaviorRadioButtonClick(TObject *Sender);
	void __fastcall MultipleTileBehaviorRadioButtonClick(TObject *Sender);
	void __fastcall HTilesChange(TObject *Sender);
	void __fastcall HTilesExit(TObject *Sender);
	void __fastcall VTilesChange(TObject *Sender);
	void __fastcall VTilesExit(TObject *Sender);
	void __fastcall HLocationChange(TObject *Sender);
	void __fastcall HLocationExit(TObject *Sender);
	void __fastcall VLocationChange(TObject *Sender);
	void __fastcall VLocationExit(TObject *Sender);
	void __fastcall HSizeChange(TObject *Sender);
	void __fastcall HSizeExit(TObject *Sender);
	void __fastcall VSizeChange(TObject *Sender);
	void __fastcall VSizeExit(TObject *Sender);
	void __fastcall PixelMultiplierChange(TObject *Sender);
	void __fastcall PixelMultiplierExit(TObject *Sender);
	void __fastcall TopBezelSizeChange(TObject *Sender);
	void __fastcall TopBezelSizeExit(TObject *Sender);
	void __fastcall LeftBezelSizeChange(TObject *Sender);
	void __fastcall LeftBezelSizeExit(TObject *Sender);
	void __fastcall RightBezelSizeChange(TObject *Sender);
	void __fastcall RightBezelSizeExit(TObject *Sender);
	void __fastcall BottomBezelSizeChange(TObject *Sender);
	void __fastcall BottomBezelSizeExit(TObject *Sender);
private:	// User declarations
	TiledDisplayTopologyClass *TiledDisplayTopology;
	bool Refreshing;
public:		// User declarations
	__fastcall TTiledDisplayTopologyForm(TComponent *Owner);
	bool Connect(TiledDisplayTopologyClass &);
	bool Refresh(void *);
	bool RefreshTopologyIDTextBoxes();
	bool RefreshPhysicalEnclosuresRadioButtons();
	bool RefreshSingleTileBehaviorRadioButtons();
	bool RefreshMultipleTileBehaviorRadioButtons();
	bool RefreshTilesTextBoxes();
	bool RefreshLocationTextBoxes();
	bool RefreshSizeTextBoxes();
	bool RefreshBezelTextBoxes();
	bool ScaleControls();
};
//---------------------------------------------------------------------------
extern PACKAGE TTiledDisplayTopologyForm *TiledDisplayTopologyForm;
//---------------------------------------------------------------------------
#endif
