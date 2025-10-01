//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "ExtensionBlockListClass.h"
#include "ExtensionBlockClass.h"
//---------------------------------------------------------------------------
ExtensionBlockListClass::ExtensionBlockListClass(int Slots) : ListClass(Slots, 128)
{
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Slots;
	int Slot;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize - 2))
		return false;

    // Extension override
	if (Data[0] >= 1 && Data[2] == 2 && Data[3] >= 3 && Data[4] >= 7 && Data[6] >> 5 == 7 && (Data[6] & 31) >= 2 && Data[7] == 0x78)
		Slots = Data[8];
	else
		Slots = Data[0];

	ExtensionBlockClass ExtensionBlock;

	for (Slot = 0; Slot < Slots && SlotCount < MaxSlotCount; Slot++)
	{
		if (!ExtensionBlock.Read(&Data[Slot * SlotSize + 2], SlotSize))
			continue;

		if (!ExtensionBlock.Write(&SlotData[SlotCount * SlotSize], SlotSize))
			continue;

		SlotCount++;
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < DataSize + 2)
		return false;

	std::memset(Data, 0, MaxSize);
	std::memcpy(&Data[2], SlotData, DataSize);

	// Extension override
	if (SlotCount >= 1 && Data[2] == 2 && Data[3] >= 3 && Data[4] >= 7 && Data[6] >> 5 == 7 && (Data[6] & 31) >= 2 && Data[7] == 0x78)
	{
		Data[0] = 1;
		Data[8] = SlotCount;
	}
	else
	{
		Data[0] = SlotCount;
	}

	return true;
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::WriteBlankExtension(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < SlotSize)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 2;
	Data[1] = 3;
	Data[127] = 251;
	return true;
}
//---------------------------------------------------------------------------
bool ExtensionBlockListClass::EditPossible(int Slot)
{
	ExtensionBlockClass ExtensionBlock;

	if (!Get(Slot, ExtensionBlock))
		return false;

	return ExtensionBlock.IsValidType();
}
//---------------------------------------------------------------------------
