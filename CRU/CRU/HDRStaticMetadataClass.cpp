//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "HDRStaticMetadataClass.h"
//---------------------------------------------------------------------------
const int HDRStaticMetadataClass::MinEOTF = 0;
const int HDRStaticMetadataClass::MaxEOTF = 3;
const int HDRStaticMetadataClass::MinType = 0;
const int HDRStaticMetadataClass::MaxType = 0;
const int HDRStaticMetadataClass::MinIndex = 0;
const int HDRStaticMetadataClass::MaxIndex = 2;
const int HDRStaticMetadataClass::MinLuminance = 1;
const int HDRStaticMetadataClass::MaxLuminance = 255;
//---------------------------------------------------------------------------
HDRStaticMetadataClass::HDRStaticMetadataClass(int NewMaxDataSize)
{
	MaxDataSize = NewMaxDataSize;
	Metadata[0] = 0;
	Metadata[1] = 0;
	Luminance[0] = BLANK;
	Luminance[1] = BLANK;
	Luminance[2] = BLANK;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::Read(const unsigned char *Data, int MaxSize)
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

	MaxDataSize = MaxSize - 1;

	if (Size < 3 || Size > MaxDataSize)
		return false;

	if (Data[1] != 6)
		return false;

	Metadata[0] = Data[2];
	Metadata[1] = Data[3];

	if (Size >= 4 && Data[4] != 0)
		Luminance[0] = Data[4];
	else
		Luminance[0] = BLANK;

	if (Size >= 5 && Data[5] != 0)
		Luminance[1] = Data[5];
	else
		Luminance[1] = BLANK;

	if (Size >= 6 && Data[6] != 0)
		Luminance[2] = Data[6];
	else
		Luminance[2] = BLANK;

	return true;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::Write(unsigned char *Data, int MaxSize)
{
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 4)
		return false;

	std::memset(Data, 0, MaxSize);
	Size = 3;
	Data[1] = 6;
	Data[2] = Metadata[0];
	Data[3] = Metadata[1];

	if (MaxSize > 4 && Luminance[0] != BLANK)
	{
		Size = 4;
		Data[4] = Luminance[0];
	}

	if (MaxSize > 5 && Luminance[1] != BLANK)
	{
		Size = 5;
		Data[5] = Luminance[1];
	}

	if (MaxSize > 6 && Luminance[2] != BLANK)
	{
		Size = 6;
		Data[6] = Luminance[2];
	}

	Data[0] = 7 << 5;
	Data[0] |= Size;
	return true;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::GetEOTF(int Index)
{
	if (Index < MinEOTF || Index > MaxEOTF)
		return false;

	return Metadata[0] & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::SetEOTF(int Index, bool Enabled)
{
	if (Index < MinEOTF || Index > MaxEOTF)
		return false;

	if (Enabled)
		Metadata[0] |= 1 << Index;
	else
		Metadata[0] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::GetType(int Index)
{
	if (Index < MinType || Index > MaxType)
		return false;

	return Metadata[1] & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::SetType(int Index, bool Enabled)
{
	if (Index < MinType || Index > MaxType)
		return false;

	if (Enabled)
		Metadata[1] |= 1 << Index;
	else
		Metadata[1] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::LuminancePossible(int Index)
{
	if (Index < MinIndex || Index > MaxIndex)
		return false;

	return MaxDataSize >= Index + 4;
}
//---------------------------------------------------------------------------
int HDRStaticMetadataClass::GetLuminance(int Index)
{
	if (Index < MinIndex || Index > MaxIndex)
		return BLANK;

	return Luminance[Index];
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::SetLuminance(int Index, int Value)
{
	if (Index < MinIndex || Index > MaxIndex)
		return false;

	Luminance[Index] = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::IsValid()
{
	int Index;

	for (Index = MinIndex; Index <= MaxIndex; Index++)
		if (!IsValidLuminance(Index))
			return false;

	return true;
}
//---------------------------------------------------------------------------
bool HDRStaticMetadataClass::IsValidLuminance(int Index)
{
	if (Index < MinIndex || Index > MaxIndex)
		return false;

	if (Luminance[Index] == BLANK)
		return true;

	return Luminance[Index] >= MinLuminance && Luminance[Index] <= MaxLuminance;
}
//---------------------------------------------------------------------------
