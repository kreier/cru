//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "DIDDetailedResolutionListClass.h"
#include "DetailedResolutionClass.h"
//---------------------------------------------------------------------------
DIDDetailedResolutionListClass::DIDDetailedResolutionListClass(int NewType, int Slots) : ListClass(Slots, 20)
{
	Type = NewType;
}
//---------------------------------------------------------------------------
bool DIDDetailedResolutionListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Code;
	int Size;
	int Slots;
	int Slot;

	if (!Data)
		return false;

	Code = Data[0];
	Size = Data[2];

	switch (Type)
	{
		case 1:
			if (Code != 3)
				return false;

			break;

		case 7:
			if (Code != 34)
				return false;

			break;

		default:
			return false;
	}

	DeleteAll();

	if (!SetMaxSize(MaxSize - 3))
		return false;

	Slots = Size / SlotSize;
	DetailedResolutionClass DetailedResolution(Type);

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!DetailedResolution.Read(&Data[Slot * SlotSize + 3], SlotSize))
			continue;

		if (!DetailedResolution.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool DIDDetailedResolutionListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 3)
		return false;

	std::memset(Data, 0, MaxSize);

	switch (Type)
	{
		case 1:
			Data[0] = 3;
			Data[1] = 1;
			break;

		case 7:
			Data[0] = 34;
			break;

		default:
			return false;
	}

	Data[2] = DataSize;
	std::memcpy(&Data[3], SlotData, DataSize);
	return true;
}
//---------------------------------------------------------------------------
int DIDDetailedResolutionListClass::GetType()
{
	return Type;
}
//---------------------------------------------------------------------------
