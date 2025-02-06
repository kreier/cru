//---------------------------------------------------------------------------
#ifndef CommonFormClassH
#define CommonFormClassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#define ARROW_UP	100
#define ARROW_DOWN	200
//---------------------------------------------------------------------------
struct Column
{
	char Text[TEXTSIZE];
	int Width;
	int Format;
};
//---------------------------------------------------------------------------
class TCommonForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
protected:	// User declarations
	TEXTMETRIC Text;
	int Scale;
	int Themed;
	int LabelSpacing;
	int PostLabelSpacing;
	int ComboBoxHeight;
	int NumberWidth;
	int TextBoxPadding;
	int TextBoxHeight;
	int TextBoxSpacing;
	int ButtonWidth;
	int ButtonHeight;
	int ButtonLeft;
	int ButtonRight;
	int ButtonTop;
	int ButtonBottom;
	int LongButtonWidth;
	int LongButtonHeight;
	int ArrowButtonWidth;
	int ArrowButtonHeight;
	int NumGlyphs;
	int CheckBoxWidth;
	int CheckBoxHeight;
	int CheckBoxRight;
	int CheckBoxTop;
	int CheckBoxBottom;
	int CheckBoxSpacing;
	int RadioButtonWidth;
	int RadioButtonHeight;
	int RadioButtonRight;
	int RadioButtonTop;
	int RadioButtonBottom;
	int RadioButtonSpacing;
	int ListBoxWidth;
	int LongListBoxWidth;
	int PaddingWidth;
	int PaddingTop;
	int PaddingBottom;
	int GroupBoxTop;
	int GroupBoxBottom;
	int FormButtonWidth;
	int FormButtonHeight;
	int FormButtonsWidth;

public:		// User declarations
	__fastcall TCommonForm(TComponent *Owner);
	int GetFormSize();
	int GetFormScale();
	int GetFontHeight();
	int GetCheckBoxWidth();
	int GetCheckBoxRight();
	int GetRadioButtonWidth();
	int GetRadioButtonRight();
	int GetScaledResourceID(int);
	TColor GetTextColor(bool);
	const char *Dash();
	BOOL IsAppThemed();
	bool FixButtonCaption(TButton *, int);
	void ListBoxDrawItems(TListBox *, RECT, TOwnerDrawState, Column *, int, bool, bool);
	void ListBoxDrawItem(TListBox *, RECT, TOwnerDrawState, const char *, bool, bool);
	int TextToInteger(const char *);
	bool IntegerToText(int, char *, int);
	long long TextToDecimal(const char *, int);
	bool DecimalToText(long long, int, int, char *, int);
};
//---------------------------------------------------------------------------
extern PACKAGE TCommonForm *CommonForm;
//---------------------------------------------------------------------------
#endif
