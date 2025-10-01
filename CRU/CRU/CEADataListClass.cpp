//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "CEADataListClass.h"
//---------------------------------------------------------------------------
CEADataListClass::CEADataListClass(int Slots) : ListClass(Slots, 32)
{
}
//---------------------------------------------------------------------------
const char *CEADataListClass::SlotTypeText[] =
{
	"Invalid",
	"Audio formats",
	"TV resolutions",
	"HDMI support",
	"HDMI 2.0 support",
	"HDMI 2.1 support",
	"FreeSync range",
	"Vendor-specific data",
	"Speaker setup",
	"Video capability",
	"Vendor-specific video",
	"HDR10+ video",
	"Dolby video",
	"HDMI video",
	"Colorimetry",
	"HDR static metadata",
	"HDR dynamic metadata",
	"Video preference",
	"4:2:0 resolutions",
	"4:2:0 capability map",
	"Vendor-specific audio",
	"Dolby audio",
	"HDMI audio",
	"Room configuration",
	"Speaker location",
	"InfoFrame data",
	"Detailed resolution",
	"Type 8 resolutions",
	"Type 10 resolutions",
	"Extension override",
	"Sink capability",
	"Extended",
	"Other",
};
//---------------------------------------------------------------------------
bool CEADataListClass::Read(const unsigned char *Data, int MaxSize)
{
	int Offset;
	int Type;
	int Size;

	if (!Data)
		return false;

	DeleteAll();

	if (!SetMaxSize(MaxSize))
		return false;

	for (Offset = 1; Offset <= MaxDataSize && SlotCount < MaxSlotCount; Offset += Size + 1)
	{
		Type = Data[Offset - 1] >> 5;
		Size = Data[Offset - 1] & 31;

		if (Size > MaxDataSize - Offset)
			Size = MaxDataSize - Offset;

		if (Type == 0 && Size == 0)
			continue;

		std::memcpy(&SlotData[SlotCount * SlotSize], &Data[Offset - 1], Size + 1);
		SlotData[SlotCount * SlotSize] = (Type << 5) | (Size & 31);
		SlotCount++;
	}

	UpdateSize();
	return true;
}
//---------------------------------------------------------------------------
bool CEADataListClass::Write(unsigned char *Data, int MaxSize)
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
int CEADataListClass::GetSlotType(int Slot)
{
	const unsigned char *Byte;
	int Type;
	int Size;

	if (Slot < 0 || Slot >= SlotCount)
		return CEA_INVALID;

	Byte = &SlotData[Slot * SlotSize];
	Type = Byte[0] >> 5;
	Size = GetSlotSize(Slot);

	switch (Type)
	{
		case 1:
			return CEA_AUDIO;

		case 2:
			return CEA_VIDEO;

		case 3:
			if (Size < 4)
				return CEA_OTHER;

			if (Size >= 6 && std::memcmp(&Byte[1], "\x03\x0C\x00", 3) == 0)
				return CEA_HDMI;

			if (Size >= 8 && std::memcmp(&Byte[1], "\xD8\x5D\xC4", 3) == 0)
			{
				if (Size >= 9 || Byte[7] >> 4)
					return CEA_HDMI21;

				return CEA_HDMI2;
			}

			if (Size >= 9 && std::memcmp(&Byte[1], "\x1A\x00\x00", 3) == 0 && Byte[6] != 0 && Byte[7] != 0 && Byte[6] <= Byte[7])
				return CEA_FREESYNC;

			return CEA_VENDOR_SPECIFIC_DATA;

		case 4:
			if (Size < 4)
				return CEA_OTHER;

			return CEA_SPEAKER_ALLOCATION;

		case 7:
			if (Size < 2)
				return CEA_OTHER;

			switch (Byte[1])
			{
				case 0:
					if (Size < 3)
						return CEA_EXTENDED;

					return CEA_VIDEO_CAPABILITY;

				case 1:
					if (Size < 5)
						return CEA_EXTENDED;

					if (std::memcmp(&Byte[2], "\x8B\x84\x90", 3) == 0)
						return CEA_HDR10_VIDEO;

					if (std::memcmp(&Byte[2], "\x46\xD0\x00", 3) == 0)
						return CEA_DOLBY_VIDEO;

					return CEA_VENDOR_SPECIFIC_VIDEO;

				case 4:
					return CEA_HDMI_VIDEO;

				case 5:
					if (Size < 4)
						return CEA_EXTENDED;

					return CEA_COLORIMETRY;

				case 6:
					if (Size < 4)
						return CEA_EXTENDED;

					return CEA_HDR_STATIC_METADATA;

				case 7:
					return CEA_HDR_DYNAMIC_METADATA;

				case 13:
					return CEA_VIDEO_FORMAT_PREFERENCE;

				case 14:
					return CEA_YCC420_VIDEO;

				case 15:
					return CEA_YCC420_CAPABILITY_MAP;

				case 17:
					if (Size < 5)
						return CEA_EXTENDED;

					if (std::memcmp(&Byte[2], "\x46\xD0\x00", 3) == 0)
						return CEA_DOLBY_AUDIO;

					return CEA_VENDOR_SPECIFIC_AUDIO;

				case 18:
					return CEA_HDMI_AUDIO;

				case 19:
					return CEA_ROOM_CONFIGURATION;

				case 20:
					return CEA_SPEAKER_LOCATION;

				case 32:
					return CEA_INFOFRAME_DATA;

				case 34:
					return CEA_DETAILED_RESOLUTION;

				case 35:
					return CEA_TYPE_8_RESOLUTIONS;

				case 42:
					return CEA_TYPE_10_RESOLUTIONS;

				case 120:
					return CEA_EXTENSION_OVERRIDE;

				case 121:
					return CEA_SINK_CAPABILITY;
			}

			return CEA_EXTENDED;
	}

	return CEA_OTHER;
}
//---------------------------------------------------------------------------
int CEADataListClass::GetSlotSize(int Slot)
{
	const unsigned char *Byte;
	int Size;

	if (Slot < 0 || Slot >= SlotCount)
		return 0;

	Byte = &SlotData[Slot * SlotSize];
	Size = Byte[0] & 31;
	return Size + 1;
}
//---------------------------------------------------------------------------
bool CEADataListClass::UpdateSize()
{
	int Slot;

	DataSize = 0;

	for (Slot = 0; Slot < SlotCount; Slot++)
		DataSize += GetSlotSize(Slot);

	return true;
}
//---------------------------------------------------------------------------
bool CEADataListClass::SetMaxCount(int NewMaxSlotCount)
{
	if (NewMaxSlotCount < SlotCount)
		return false;

	if (NewMaxSlotCount > MaxMaxSlotCount)
		NewMaxSlotCount = MaxMaxSlotCount;

	MaxSlotCount = NewMaxSlotCount;
	return true;
}
//---------------------------------------------------------------------------
bool CEADataListClass::SetMaxSize(int NewMaxDataSize)
{
	if (NewMaxDataSize < DataSize)
		return false;

	if (NewMaxDataSize > MaxMaxDataSize)
		NewMaxDataSize = MaxMaxDataSize;

	MaxDataSize = NewMaxDataSize;
	return true;
}
//---------------------------------------------------------------------------
bool CEADataListClass::GetSlotTypeText(int Slot, char *Text, int TextSize)
{
	const unsigned char *Byte;
	int Type;
	int Size;

	if (Slot < 0 || Slot >= SlotCount)
		return false;

	Byte = &SlotData[Slot * SlotSize];
	Type = GetSlotType(Slot);
	Size = GetSlotSize(Slot);

	if (Type == CEA_OTHER)
		std::snprintf(Text, TextSize, "%s (%d)", SlotTypeText[Type], Byte[0] >> 5);
	else if (Type == CEA_EXTENDED && Size >= 2)
		std::snprintf(Text, TextSize, "%s (%d)", SlotTypeText[Type], Byte[1]);
	else
		std::snprintf(Text, TextSize, "%s", SlotTypeText[Type]);

	return true;
}
//---------------------------------------------------------------------------
bool CEADataListClass::GetSlotInfoText(int Slot, char *Text, int TextSize)
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
		case CEA_VIDEO:
			Slots = Size - 1;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case CEA_YCC420_VIDEO:
			Slots = Size - 2;
			std::snprintf(Text, TextSize, "%d resolution%s", Slots, Slots != 1 ? "s" : "");
			break;

		case CEA_AUDIO:
			Slots = (Size - 1) / 3;
			std::snprintf(Text, TextSize, "%d format%s", Slots, Slots != 1 ? "s" : "");
			break;

		case CEA_SPEAKER_ALLOCATION:
			if (Byte[1] == 1 && Byte[2] == 0 && Byte[3] == 0)
				std::snprintf(Text, TextSize, "Stereo");
			else if (Byte[1] == 15 && Byte[2] == 0 && Byte[3] == 0)
				std::snprintf(Text, TextSize, "5.1 surround");
			else if (Byte[1] == 79 && Byte[2] == 0 && Byte[3] == 0)
				std::snprintf(Text, TextSize, "7.1 surround");

			break;

		case CEA_HDMI:
			if (Size > 7 && Byte[7] != 0)
				std::snprintf(Text, TextSize, "Max: %d MHz", Byte[7] * 5);

			break;

		case CEA_HDMI2:
		case CEA_HDMI21:
			if (Size > 7)
			{
				int Rate = Byte[7] >> 4;

				switch (Rate)
				{
					case 0:
						if (Byte[5] != 0)
							std::snprintf(Text, TextSize, "Max: %d Mcsc", Byte[5] * 5);

						break;

					case 1:
					case 2:
						std::snprintf(Text, TextSize, "Max: %d Gbps", Rate * 9);
						break;

					case 3:
					case 4:
					case 5:
					case 6:
						std::snprintf(Text, TextSize, "Max: %d Gbps", Rate * 8);
						break;
				}
			}

			break;

		case CEA_FREESYNC:
			if (Size > 7)
				std::snprintf(Text, TextSize, "%d-%d Hz", Byte[6], Size > 15 ? (Byte[15] & 3) << 8 | Byte[14] : Byte[7]);

			break;

		case CEA_VENDOR_SPECIFIC_DATA:
			if (Size > 3)
				std::snprintf(Text, TextSize, "ID: 0x%02X%02X%02X", Byte[3], Byte[2], Byte[1]);

			break;

		case CEA_VENDOR_SPECIFIC_VIDEO:
		case CEA_VENDOR_SPECIFIC_AUDIO:
			if (Size > 4)
				std::snprintf(Text, TextSize, "ID: 0x%02X%02X%02X", Byte[4], Byte[3], Byte[2]);

			break;
	}

	return true;
}
//---------------------------------------------------------------------------
bool CEADataListClass::EditPossible(int Slot)
{
	int Type;

	if (Slot < 0 || Slot >= SlotCount)
		return false;

	Type = GetSlotType(Slot);

	switch (Type)
	{
		case CEA_AUDIO:
		case CEA_VIDEO:
		case CEA_HDMI:
		case CEA_HDMI2:
		case CEA_HDMI21:
		case CEA_FREESYNC:
		case CEA_SPEAKER_ALLOCATION:
		case CEA_VIDEO_CAPABILITY:
		case CEA_COLORIMETRY:
		case CEA_HDR_STATIC_METADATA:
		case CEA_YCC420_VIDEO:
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool CEADataListClass::HDMISupported()
{
	int Slot;
	int Type;

	for (Slot = 0; Slot < SlotCount; Slot++)
	{
		Type = GetSlotType(Slot);

		if (Type == CEA_HDMI)
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool CEADataListClass::HDMI2Supported()
{
	int Slot;
	int Type;

	for (Slot = 0; Slot < SlotCount; Slot++)
	{
		Type = GetSlotType(Slot);

		if (Type == CEA_HDMI2)
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool CEADataListClass::HDMI21Supported()
{
	int Slot;
	int Type;

	for (Slot = 0; Slot < SlotCount; Slot++)
	{
		Type = GetSlotType(Slot);

		if (Type == CEA_HDMI21)
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool CEADataListClass::AudioSupported()
{
	int Slot;
	int Type;

	for (Slot = 0; Slot < SlotCount; Slot++)
	{
		Type = GetSlotType(Slot);

		if (Type == CEA_AUDIO || Type == CEA_SPEAKER_ALLOCATION)
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool CEADataListClass::UnderscanSupported()
{
	int Slot;
	int Type;
	const unsigned char *Byte;

	for (Slot = 0; Slot < SlotCount; Slot++)
	{
		Type = GetSlotType(Slot);
		Byte = &SlotData[Slot * SlotSize];

		if (Type == CEA_VIDEO_CAPABILITY)
			if ((Byte[2] & 12) == 8)
				return true;
	}

	return false;
}
//---------------------------------------------------------------------------
