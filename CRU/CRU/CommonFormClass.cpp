//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "CommonFormClass.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TCommonForm *CommonForm;
//---------------------------------------------------------------------------
__fastcall TCommonForm::TCommonForm(TComponent *Owner) : TForm(Owner)
{
	bool Small;
	int ListBoxWidth1;
	int ListBoxWidth2;

	Font->Height = GetFontHeight();
	Canvas->Font->Height = Font->Height;
	GetTextMetrics(Canvas->Handle, &Text);

	Scale = GetFormScale();
	Themed = IsAppThemed();
	Small = Scale < 8;
	LabelSpacing = Scale * 7 / 10 - 1;
	PostLabelSpacing = Small ? LabelSpacing : Scale / 2 + 2;
	ComboBoxHeight = Text.tmHeight + 8;
	NumberWidth = Canvas->TextWidth("9");
	TextBoxPadding = NumberWidth < 6 ? 6 : NumberWidth;
	TextBoxHeight = Text.tmHeight + 8;
	TextBoxSpacing = Scale + Small - 4;
	ButtonWidth = Canvas->TextWidth("Delete") / 2 * 2 + NumberWidth * 2 + Scale % 2;
	ButtonHeight = Text.tmHeight + 8;
	ButtonLeft = -1;
	ButtonRight = -1;
	ButtonTop = -1;
	ButtonBottom = -1;
	LongButtonWidth = Canvas->TextWidth("Delete all") / 2 * 2 + NumberWidth * 2 + Scale % 2;
	LongButtonHeight = ButtonHeight;
	ArrowButtonWidth = ButtonHeight;
	ArrowButtonHeight = ButtonHeight;
	NumGlyphs = 1 + Themed;
	CheckBoxWidth = GetCheckBoxWidth() + (Canvas->TextWidth("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") + 16) / 104;
	CheckBoxHeight = Text.tmHeight + 4;
	CheckBoxRight = GetCheckBoxRight();
	CheckBoxTop = -1 - Themed + (Small && Themed);
	CheckBoxBottom = -3 + Themed;
	CheckBoxSpacing = Scale / 4 + Small - 2;
	RadioButtonWidth = GetRadioButtonWidth() + (Canvas->TextWidth("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") + 16) / 104;
	RadioButtonHeight = CheckBoxHeight;
	RadioButtonRight = GetRadioButtonRight();
	RadioButtonTop = CheckBoxTop;
	RadioButtonBottom = CheckBoxBottom;
	RadioButtonSpacing = CheckBoxSpacing;
	PaddingWidth = Scale + 1;
	PaddingTop = Text.tmAscent + Scale;
	PaddingBottom = Scale + 2;
	GroupBoxTop = PaddingTop - Text.tmHeight / 2 * 2 - 1;
	GroupBoxBottom = -1;
	ListBoxWidth1 = Canvas->TextWidth("9999x9999 (99:99) @ 999 Hz") * 2 + NumberWidth * 4 + Small * 4 + 4;
	ListBoxWidth2 = Canvas->TextWidth("Type:") + LabelSpacing + Canvas->TextWidth("VTB-EXT: Video Timing Block") + NumberWidth + ComboBoxHeight + Scale + ButtonLeft + ButtonWidth * 3 + ButtonRight - PaddingWidth * 2;
	ListBoxWidth2 = (ListBoxWidth2 + 1) / 2 * 2;
	ListBoxWidth = ListBoxWidth1 > ListBoxWidth2 ? ListBoxWidth1 : ListBoxWidth2;
	Canvas->Font->Style = TFontStyles() << fsBold;
	LongListBoxWidth = Canvas->TextWidth("9999x9999i (99:9) @ 999 Hz") * 2 + NumberWidth * 4 + Small * 4 + 4;
	Canvas->Font->Style = TFontStyles();
	FormButtonWidth = Text.tmHeight * 5 + Scale + Small + 2;
	FormButtonHeight = Text.tmHeight + Scale + 2;
	FormButtonsWidth = (ButtonLeft + FormButtonWidth + ButtonRight) * 2 + Scale;
}
//---------------------------------------------------------------------------
int TCommonForm::GetFormSize()
{
	if (Screen->Width < 720 || Screen->Height < 576)
		return 6;

	return 8;
}
//---------------------------------------------------------------------------
int TCommonForm::GetFormScale()
{
	return (GetFormSize() * Screen->PixelsPerInch + 96) / 192 * 2;
}
//---------------------------------------------------------------------------
int TCommonForm::GetFontHeight()
{
	return GetFormSize() * Screen->PixelsPerInch * 5 / 576 * 2 + 1;
}
//---------------------------------------------------------------------------
int TCommonForm::GetCheckBoxWidth()
{
	int i;
	int x[] = {120, 144, 192, 240, 288, 384,   0};
	int y[] = { 15,  18,  23,  29,  35,  43,  55};

	if (!IsAppThemed() || Screen->PixelsPerInch > 480)
		return Screen->PixelsPerInch / 8 + 5;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int TCommonForm::GetCheckBoxRight()
{
	int i;
	int x[] = {144,   0};
	int y[] = { -2,  -3};

	if (!IsAppThemed())
		return -2;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int TCommonForm::GetRadioButtonWidth()
{
	int i;
	int x[] = {120, 144, 192, 240, 288, 384,   0};
	int y[] = { 15,  18,  23,  29,  35,  42,  55};

	if (!IsAppThemed() || Screen->PixelsPerInch > 480)
		return Screen->PixelsPerInch / 8 + 5;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int TCommonForm::GetRadioButtonRight()
{
	int i;
	int x[] = {144,   0};
	int y[] = { -2,  -3};

	if (!IsAppThemed())
		return -2;

	for (i = 0; x[i]; i++)
		if (Screen->PixelsPerInch < x[i])
			break;

	return y[i];
}
//---------------------------------------------------------------------------
int TCommonForm::GetScaledResourceID(int ResourceID)
{
	int i;
	int x[] = {9, 11, 13, 15, 17, 19, 21, 23, 0};

	for (i = 0; x[i]; i++)
		if (GetFormScale() < x[i])
			break;

	return ResourceID + IsAppThemed() * 10 + i;
}
//---------------------------------------------------------------------------
TColor TCommonForm::GetTextColor(bool Valid)
{
	if (!Valid)
		return (TColor)RGB(255, 0, 0);

	return clWindowText;
}
//---------------------------------------------------------------------------
const char *TCommonForm::Dash()
{
	static const char *Dash;

	if (!Dash)
	{
		switch (GetACP())
		{
			case 874:
			case 1250:
			case 1251:
			case 1252:
			case 1253:
			case 1254:
			case 1255:
			case 1256:
			case 1257:
			case 1258:
				Dash = "\x96";
				break;

			default:
				Dash = "-";
				break;
		}
	}

	return Dash;
}
//---------------------------------------------------------------------------
BOOL TCommonForm::IsAppThemed()
{
	typedef BOOL IsAppThemedProc();
	static IsAppThemedProc *IsAppThemed;
	static HMODULE Library;

	if (!IsAppThemed)
	{
		if (!Library)
		{
			Library = LoadLibrary("uxtheme.dll");

			if (!Library)
				return FALSE;
		}

		IsAppThemed = (IsAppThemedProc *)GetProcAddress(Library, "IsAppThemed");

		if (!IsAppThemed)
			return FALSE;
	}

	return IsAppThemed();
}
//---------------------------------------------------------------------------
bool TCommonForm::FixButtonCaption(TButton *Button, int TextWidth)
{
	if (GetFormScale() == 8 && TextWidth % 2 != 0)
		Button->Caption = "{                " + Button->Caption + "                ]";

	return true;
}
//---------------------------------------------------------------------------
void TCommonForm::ListBoxDrawItems(TListBox *ListBox, RECT Rect, TOwnerDrawState State, Column *Columns, int Count, bool Enabled, bool Bold)
{
	RECT ItemRect;
	int Index;

	if (!Enabled)
	{
		if (State.Contains(odSelected))
			ListBox->Canvas->Brush->Color = clGrayText;
		else
			ListBox->Canvas->Font->Color = clGrayText;
	}

	if (Bold)
		ListBox->Canvas->Font->Style = TFontStyles() << fsBold;

	ListBox->Canvas->FillRect(Rect);
	ItemRect = Rect;
	ItemRect.left += 2;

	if (GetFormScale() == 8)
		ItemRect.left++;

	for (Index = 0; Index < Count; Index++)
	{
		ItemRect.right = ItemRect.left + Columns[Index].Width;
		DrawText(ListBox->Canvas->Handle, Columns[Index].Text, -1, &ItemRect, Columns[Index].Format | DT_NOPREFIX);
		ItemRect.left = ItemRect.right;
	}

	if (State.Contains(odFocused) && State.Contains(odNoFocusRect))
		ListBox->Canvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
void TCommonForm::ListBoxDrawItem(TListBox *ListBox, RECT Rect, TOwnerDrawState State, const char *Text, bool Enabled, bool Bold)
{
	RECT ItemRect;

	if (!Enabled)
	{
		if (State.Contains(odSelected))
			ListBox->Canvas->Brush->Color = clGrayText;
		else
			ListBox->Canvas->Font->Color = clGrayText;
	}

	if (Bold)
		ListBox->Canvas->Font->Style = TFontStyles() << fsBold;

	ListBox->Canvas->FillRect(Rect);
	ItemRect = Rect;
	ItemRect.left += 2;

	if (GetFormScale() == 8)
		if (!IsDigit(*Text))
			ItemRect.left++;

	DrawText(ListBox->Canvas->Handle, Text, -1, &ItemRect, DT_LEFT | DT_NOPREFIX);

	if (State.Contains(odFocused) && State.Contains(odNoFocusRect))
		ListBox->Canvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
int TCommonForm::TextToInteger(const char *Text)
{
	long long result = TextToDecimal(Text, 0);

	switch (result)
	{
		case DECIMAL_BLANK:
			return BLANK;

		case DECIMAL_INVALID:
			return INVALID;
	}

	return result;
}
//---------------------------------------------------------------------------
bool TCommonForm::IntegerToText(int Value, char *Text, int TextSize)
{
	switch (Value)
	{
		case BLANK:
			Text[0] = 0;
			return true;

		case INVALID:
			return false;
	}

	return DecimalToText(Value, TextSize, 0, Text, TextSize);
}
//---------------------------------------------------------------------------
long long TCommonForm::TextToDecimal(const char *Text, int Digits)
{
	const char *Byte = Text;

	while (IsSpace(*Byte))
		Byte++;

	if (*Byte == 0)
		return DECIMAL_BLANK;

	int Sign;

	if (*Byte == '-')
	{
		Sign = -1;
		Byte++;
	}
	else
	{
		Sign = 1;

		if (*Byte == '+')
			Byte++;
	}

	bool Invalid = true;
	long long Value = 0;

	if (IsDigit(*Byte))
	{
		Invalid = false;

		do
		{
			Value *= 10;
			Value += *Byte - '0';
			Byte++;
		}
		while (IsDigit(*Byte));
	}

	int Count = 0;

	if (*Byte == '.')
	{
		Byte++;

		if (Count < Digits && IsDigit(*Byte))
		{
			Invalid = false;

			do
			{
				Value *= 10;
				Value += *Byte - '0';
				Byte++;
				Count++;
			}
			while (Count < Digits && IsDigit(*Byte));
		}
	}

	if (Invalid)
		return DECIMAL_INVALID;

	while (IsDigit(*Byte))
		Byte++;

	while (IsSpace(*Byte))
		Byte++;

	if (*Byte != 0)
		return DECIMAL_INVALID;

	while (Count < Digits)
	{
		Value *= 10;
		Count++;
	}

	return Sign * Value;
}
//---------------------------------------------------------------------------
bool TCommonForm::DecimalToText(long long Value, int MaxLength, int Digits, char *Text, int TextSize)
{
	switch (Value)
	{
		case DECIMAL_BLANK:
			Text[0] = 0;
			return true;

		case DECIMAL_INVALID:
			return false;
	}

	int Sign;

	if (Value < 0)
		Sign = -1;
	else
		Sign = 1;

	int Count = 1;
	char *Byte = Text;

	while (Count <= Digits && Count < TextSize)
	{
		*Byte = Sign * Value % 10 + '0';
		Value /= 10;
		Byte++;
		Count++;
	}

	if (Count < TextSize)
	{
		if (Digits > 0)
		{
			*Byte = '.';
			Byte++;
			Count++;
		}

		if (Count < TextSize)
		{
			do
			{
				*Byte = Sign * Value % 10 + '0';
				Value /= 10;
				Byte++;
				Count++;
			}
			while (Value != 0 && Count < TextSize);

			if (Sign < 0 && Count < TextSize)
			{
				*Byte = '-';
				Byte++;
			}
		}
	}

	*Byte = 0;
	std::strrev(Text);

	if (MaxLength < TextSize)
	{
		if (Text[MaxLength - 1] == '.')
			Text[MaxLength - 1] = 0;
		else
			Text[MaxLength] = 0;
	}

	return true;
}
//---------------------------------------------------------------------------
