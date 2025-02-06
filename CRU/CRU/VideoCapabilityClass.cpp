//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "VideoCapabilityClass.h"
//---------------------------------------------------------------------------
VideoCapabilityClass::VideoCapabilityClass()
{
	VideoCapabilityData[0] = 192;
	VideoCapabilitySize = 1;
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 7)
		return false;

	if (Size < 2)
		return false;

	if (Data[1] != 0)
		return false;

	VideoCapabilitySize = Size - 1;
	std::memcpy(VideoCapabilityData, &Data[2], VideoCapabilitySize);
	return true;
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < VideoCapabilitySize + 2)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 7 << 5;
	Data[0] |= VideoCapabilitySize + 1;
	Data[1] = 0;
	std::memcpy(&Data[2], VideoCapabilityData, VideoCapabilitySize);
	return true;
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::Get(int Index)
{
	if (Index < 0 || Index >= VideoCapabilitySize * 8)
		return false;

	return VideoCapabilityData[Index / 8] & (1 << Index % 8);
}
//---------------------------------------------------------------------------
bool VideoCapabilityClass::Set(int Index, bool Enabled)
{
	if (Index < 0 || Index >= VideoCapabilitySize * 8)
		return false;

	if (Enabled)
		VideoCapabilityData[Index / 8] |= 1 << Index % 8;
	else
		VideoCapabilityData[Index / 8] &= ~(1 << Index % 8);

	return true;
}
//---------------------------------------------------------------------------
