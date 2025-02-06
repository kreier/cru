//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "ColorimetryClass.h"
//---------------------------------------------------------------------------
ColorimetryClass::ColorimetryClass()
{
	ColorimetryData[0] = 3;
	ColorimetryData[1] = 1;
	ColorimetrySize = 2;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 4)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 7)
		return false;

	if (Size < 3)
		return false;

	if (Data[1] != 5)
		return false;

	ColorimetrySize = Size - 1;
	std::memcpy(ColorimetryData, &Data[2], ColorimetrySize);
	return true;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < ColorimetrySize + 2)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 7 << 5;
	Data[0] |= ColorimetrySize + 1;
	Data[1] = 5;
	std::memcpy(&Data[2], ColorimetryData, ColorimetrySize);
	return true;
}
//---------------------------------------------------------------------------
bool ColorimetryClass::Get(int Index)
{
	if (Index < 0 || Index >= ColorimetrySize * 8)
		return false;

	return ColorimetryData[Index / 8] & (1 << Index % 8);
}
//---------------------------------------------------------------------------
bool ColorimetryClass::Set(int Index, bool Enabled)
{
	if (Index < 0 || Index >= ColorimetrySize * 8)
		return false;

	if (Enabled)
		ColorimetryData[Index / 8] |= 1 << Index % 8;
	else
		ColorimetryData[Index / 8] &= ~(1 << Index % 8);

	return true;
}
//---------------------------------------------------------------------------
