//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "DIDDataListClass.h"
//---------------------------------------------------------------------------
DIDDataListClass::DIDDataListClass(int Slots) : ListClass(Slots, 121)
{
	Version = 1;
}
//---------------------------------------------------------------------------
const char *DIDDataListClass::SlotTypeText[] =
{
	"Invalid",
	"Product identification",
	"Display parameters",
	"Color characteristics",
	"Detailed resolutions",
	"Type 2 resolutions",
	"Type 3 resolutions",
	"Type 4 resolutions",
	"VESA resolutions",
	"CTA resolutions",
	"Range limits",
	"Serial number",
	"ASCII string",
	"Display device data",
	"Power sequencing",
	"Gamma curves",
	"Display interface",
	"Stereo display",
	"Type 5 resolutions",
	"Tiled display topology",
	"Type 6 resolutions",
	"Vendor-specific data",
	"Product identification",
	"Display parameters",
	"Detailed resolutions",
	"Type 8 resolutions",
	"Type 9 resolutions",
	"Dynamic range limits",
	"Display interface",
	"Stereo display",
	"Tiled display topology",
	"ContainerID",
	"Vendor-specific data",
	"CTA data blocks",
	"Other",
};
//---------------------------------------------------------------------------
bool DIDDataListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Offset;
	int Type;
	int Size;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize))
		return false;

	for (Offset = 3; Offset <= MaxDataSize && SlotCount < MaxSlotCount; Offset += Size + 3)
	{
		Type = Data[Offset - 3];
		Size = Data[Offset - 1];

		if (Size > MaxDataSize - Offset)
			Size = MaxDataSize - Offset;

		if (Type == 0 && Size == 0)
			continue;

		std::memcpy(&SlotData[SlotCount * SlotSize], &Data[Offset - 3], Size + 3);
		SlotData[SlotCount * SlotSize + 2] = Size;
		SlotCount++;
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::Write(unsigned char *Data, int MaxSize)
{
	int Offset;
	int Slot;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < DataSize)
		return false;

	Offset = 0;

	for (Slot = 0; Slot < SlotCount; Slot++)
	{
		Size = GetSlotSize(Slot);
		std::memcpy(&Data[Offset], &SlotData[Slot * SlotSize], Size);
		Offset += Size;
	}

	return true;
}
//---------------------------------------------------------------------------
int DIDDataListClass::GetSlotType(int Slot)
{
	const unsigned char *Byte;
	int Type;
	int Size;

	if (Slot < 0 || Slot >= SlotCount)
		return DID_INVALID;

	Byte = &SlotData[Slot * SlotSize];
	Type = Byte[0];
	Size = GetSlotSize(Slot);

	switch (Type)
	{
		case 0:
			return DID_PRODUCT_IDENTIFICATION;

		case 1:
			return DID_DISPLAY_PARAMETERS;

		case 2:
			return DID_COLOR_CHARACTERISTICS;

		case 3:
			return DID_DETAILED_RESOLUTIONS;

		case 4:
			return DID_TYPE_2_RESOLUTIONS;

		case 5:
			return DID_TYPE_3_RESOLUTIONS;

		case 6:
			return DID_TYPE_4_RESOLUTIONS;

		case 7:
			return DID_VESA_RESOLUTIONS;

		case 8:
			return DID_CEA_RESOLUTIONS;

		case 9:
			return DID_RANGE_LIMITS;

		case 10:
			return DID_SERIAL_NUMBER;

		case 11:
			return DID_ASCII_STRING;

		case 12:
			return DID_DISPLAY_DEVICE_DATA;

		case 13:
			return DID_INTERFACE_POWER_SEQUENCING;

		case 14:
			return DID_TRANSFER_CHARACTERISTICS;

		case 15:
			return DID_DISPLAY_INTERFACE;

		case 16:
			return DID_STEREO_DISPLAY_INTERFACE;

		case 17:
			return DID_TYPE_5_RESOLUTIONS;

		case 18:
			if (Size < 25)
				return DID_OTHER;

			return DID_TILED_DISPLAY_TOPOLOGY;

		case 19:
			return DID_TYPE_6_RESOLUTIONS;

		case 127:
			return DID_VENDOR_SPECIFIC_DATA;

		case 32:
			return DID2_PRODUCT_IDENTIFICATION;

		case 33:
			return DID2_DISPLAY_PARAMETERS;

		case 34:
			return DID2_DETAILED_RESOLUTIONS;

		case 35:
			return DID2_TYPE_8_RESOLUTIONS;

		case 36:
			return DID2_TYPE_9_RESOLUTIONS;

		case 37:
			return DID2_DYNAMIC_RANGE_LIMITS;

		case 38:
			return DID2_DISPLAY_INTERFACE_FEATURES;

		case 39:
			return DID2_STEREO_DISPLAY_INTERFACE;

		case 40:
			if (Size < 25)
				return DID_OTHER;

			return DID2_TILED_DISPLAY_TOPOLOGY;

		case 41:
			return DID2_CONTAINERID;

		case 126:
			return DID2_VENDOR_SPECIFIC_DATA;

		case 129:
			return DID_CEA_DATA_BLOCKS;
	}

	return DID_OTHER;
}
//---------------------------------------------------------------------------
int DIDDataListClass::GetSlotSize(int Slot)
{
	const unsigned char *Byte;
	int Size;

	if (Slot < 0 || Slot >= SlotCount)
		return 0;

	Byte = &SlotData[Slot * SlotSize];
	Size = Byte[2];
	return Size + 3;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::UpdateSize()
{
	int Slot;

	DataSize = 0;

	for (Slot = 0; Slot < SlotCount; Slot++)
		DataSize += GetSlotSize(Slot);

	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::SetMaxCount(int NewMaxSlotCount)
{
	if (NewMaxSlotCount < SlotCount)
		return false;

	if (NewMaxSlotCount > MaxMaxSlotCount)
		NewMaxSlotCount = MaxMaxSlotCount;

	MaxSlotCount = NewMaxSlotCount;
	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::SetMaxSize(int NewMaxDataSize)
{
	if (NewMaxDataSize < DataSize)
		return false;

	if (NewMaxDataSize > MaxMaxDataSize)
		NewMaxDataSize = MaxMaxDataSize;

	MaxDataSize = NewMaxDataSize;
	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::GetSlotTypeText(int Slot, char *Text, int TextSize)
{
	const unsigned char *Byte;
	int Type;

	if (Slot < 0 || Slot >= SlotCount)
		return false;

	Byte = &SlotData[Slot * SlotSize];
	Type = GetSlotType(Slot);

	if (Type >= DID_PRODUCT_IDENTIFICATION && Type <= DID_VENDOR_SPECIFIC_DATA)
		std::snprintf(Text, TextSize, "%s%s", SlotTypeText[Type], Version != 1 ? " (1.x)" : "");
	else if (Type >= DID2_PRODUCT_IDENTIFICATION && Type <= DID2_VENDOR_SPECIFIC_DATA)
		std::snprintf(Text, TextSize, "%s%s", SlotTypeText[Type], Version != 2 ? " (2.x)" : "");
	else if (Type == DID_CEA_DATA_BLOCKS)
		std::snprintf(Text, TextSize, "%s", SlotTypeText[Type]);
	else
		std::snprintf(Text, TextSize, "%s (%d)", SlotTypeText[Type], Byte[0]);

	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::GetSlotInfoText(int Slot, char *Text, int TextSize)
{
	const unsigned char *Byte;
	int Type;
	int Size;
	int Slots;

	if (Slot < 0 || Slot >= SlotCount)
		return false;

	Byte = &SlotData[Slot * SlotSize];
	Type = GetSlotType(Slot);
	Size = GetSlotSize(Slot);
	Text[0] = 0;

	switch (Type)
	{
		case DID_DETAILED_RESOLUTIONS:
		case DID2_DETAILED_RESOLUTIONS:
			Slots = (Size - 3) / 20;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID_TYPE_2_RESOLUTIONS:
			Slots = (Size - 3) / 11;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID_TYPE_3_RESOLUTIONS:
			Slots = (Size - 3) / 3;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID_TYPE_4_RESOLUTIONS:
			Slots = Size - 3;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID_TYPE_5_RESOLUTIONS:
			Slots = (Size - 3) / 7;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID2_TYPE_8_RESOLUTIONS:
			if (Byte[1] & 8)
				Slots = (Size - 3) / 2;
			else
				Slots = Size - 3;

			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID2_TYPE_9_RESOLUTIONS:
			Slots = (Size - 3) / 6;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case DID_TILED_DISPLAY_TOPOLOGY:
		case DID2_TILED_DISPLAY_TOPOLOGY:
		{
			int HTiles = ((Byte[4] >> 4) & 15) + ((Byte[6] >> 2) & 48) + 1;
			int VTiles = (Byte[4] & 15) + (Byte[6] & 48) + 1;
			int HLocation = ((Byte[5] >> 4) & 15) + ((Byte[6] << 2) & 48) + 1;
			int VLocation = (Byte[5] & 15) + ((Byte[6] << 4) & 48) + 1;

			if (HTiles == 1 && VTiles == 1 && HLocation == 1 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d", HTiles, VTiles);
			else if (HTiles == 2 && VTiles == 1 && HLocation == 1 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (left)", HTiles, VTiles);
			else if (HTiles == 2 && VTiles == 1 && HLocation == 2 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (right)", HTiles, VTiles);
			else if (HTiles == 3 && VTiles == 1 && HLocation == 1 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (left)", HTiles, VTiles);
			else if (HTiles == 3 && VTiles == 1 && HLocation == 2 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (center)", HTiles, VTiles);
			else if (HTiles == 3 && VTiles == 1 && HLocation == 3 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (right)", HTiles, VTiles);
			else if (HTiles == 1 && VTiles == 2 && HLocation == 1 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (top)", HTiles, VTiles);
			else if (HTiles == 1 && VTiles == 2 && HLocation == 1 && VLocation == 2)
				std::snprintf(Text, TextSize, "%dx%d (bottom)", HTiles, VTiles);
			else if (HTiles == 1 && VTiles == 3 && HLocation == 1 && VLocation == 1)
				std::snprintf(Text, TextSize, "%dx%d (top)", HTiles, VTiles);
			else if (HTiles == 1 && VTiles == 3 && HLocation == 1 && VLocation == 2)
				std::snprintf(Text, TextSize, "%dx%d (middle)", HTiles, VTiles);
			else if (HTiles == 1 && VTiles == 3 && HLocation == 1 && VLocation == 3)
				std::snprintf(Text, TextSize, "%dx%d (bottom)", HTiles, VTiles);
			else
				std::snprintf(Text, TextSize, "%dx%d (%d,%d)", HTiles, VTiles, HLocation, VLocation);

			break;
		}

		case DID_VENDOR_SPECIFIC_DATA:
			if (Size > 5)
			{
				if (IsUpper(Byte[3]) && IsUpper(Byte[4]) && IsUpper(Byte[5]))
					std::snprintf(Text, TextSize, "ID: %c%c%c", Byte[3], Byte[4], Byte[5]);
				else
					std::snprintf(Text, TextSize, "ID: 0x%02X%02X%02X", Byte[3], Byte[4], Byte[5]);
			}

			break;

		case DID2_VENDOR_SPECIFIC_DATA:
			if (Size > 5)
				std::snprintf(Text, TextSize, "ID: 0x%02X%02X%02X", Byte[3], Byte[4], Byte[5]);

			break;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::SetVersion(int NewVersion)
{
	Version = NewVersion;
	return true;
}
//---------------------------------------------------------------------------
int DIDDataListClass::GetVersion()
{
	return Version;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::AddPossible()
{
	if (SlotCount < 0 || SlotCount >= MaxSlotCount)
		return false;

	if (DataSize < 0 || DataSize >= MaxDataSize - 2)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DIDDataListClass::EditPossible(int Slot)
{
	int Type;

	if (Slot < 0 || Slot >= SlotCount)
		return false;

	Type = GetSlotType(Slot);

	switch (Type)
	{
		case DID_DETAILED_RESOLUTIONS:
		case DID_TILED_DISPLAY_TOPOLOGY:
		case DID2_DETAILED_RESOLUTIONS:
		case DID2_TILED_DISPLAY_TOPOLOGY:
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
