//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "AudioFormatClass.h"
//---------------------------------------------------------------------------
const AudioFormatStruct AudioFormatClass::Formats[] =
{
	{ "Other (0)",           0,       32, 127, AUDIO_FLAGS },
	{ "LPCM",                1,       8,  127, AUDIO_BIT_DEPTHS },
	{ "AC-3",                2,       8,  127, AUDIO_BIT_RATE },
	{ "MPEG-1",              3,       8,  127, AUDIO_BIT_RATE },
	{ "MP3",                 4,       8,  127, AUDIO_BIT_RATE },
	{ "MPEG-2",              5,       8,  127, AUDIO_BIT_RATE },
	{ "AAC LC",              6,       8,  127, AUDIO_BIT_RATE },
	{ "DTS",                 7,       8,  127, AUDIO_BIT_RATE },
	{ "ATRAC",               8,       8,  127, AUDIO_BIT_RATE },
	{ "DSD",                 9,       8,  127, AUDIO_FLAGS },
	{ "E-AC-3",              10,      8,  127, AUDIO_FLAGS },
	{ "DTS-HD",              11,      8,  127, AUDIO_FLAGS },
	{ "TrueHD",              12,      8,  127, AUDIO_FLAGS },
	{ "DST",                 13,      8,  127, AUDIO_FLAGS },
	{ "WMA Pro",             14,      8,  127, AUDIO_PROFILE },
	{ "MPEG-4 HE AAC",       15 + 4,  8,  31,  AUDIO_MPEG4 },
	{ "MPEG-4 HE AAC v2",    15 + 5,  8,  31,  AUDIO_MPEG4 },
	{ "MPEG-4 AAC LC",       15 + 6,  8,  31,  AUDIO_MPEG4_H },
	{ "MPEG-4 HE AAC + MPS", 15 + 8,  8,  31,  AUDIO_MPEG4_MPS },
	{ "MPEG-4 AAC LC + MPS", 15 + 10, 8,  31,  AUDIO_MPEG4_MPS },
	{ "MPEG-H 3D",           15 + 11, 5,  127, AUDIO_MPEGH_3D },
	{ "AC-4",                15 + 12, 0,  86,  AUDIO_EXTENSION_FLAGS },
	{ "LPCM 3D",             15 + 13, 32, 127, AUDIO_BIT_DEPTHS },
	{ "Auro-Cx",             15 + 14, 0,  127, AUDIO_EXTENSION_FLAGS },
	{ "MPEG-D USAC",         15 + 15, 8,  31,  AUDIO_NONE },
	{ "Extension",           15,      32, 127, AUDIO_EXTENSION },
};

const char *AudioFormatClass::ChannelsText[] =
{
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6 (5.1)",
	"7",
	"8 (7.1)",
};

const char *AudioFormatClass::LevelText[] =
{
	"Unspecified",
	"1",
	"2",
	"3",
	"4",
	"5",
	0,
	0,
};

const int AudioFormatClass::MinFormat = 0;
const int AudioFormatClass::MaxFormat = 25;
const int AudioFormatClass::MinExtension = 0;
const int AudioFormatClass::MaxExtension = 31;
const int AudioFormatClass::MinChannels = 1;
const int AudioFormatClass::MaxChannels = 8;
const int AudioFormatClass::MinChannels3D = 1;
const int AudioFormatClass::MaxChannels3D = 32;
const int AudioFormatClass::MinSampleRate = 0;
const int AudioFormatClass::MaxSampleRate = 6;
const int AudioFormatClass::MinBitDepth = 0;
const int AudioFormatClass::MaxBitDepth = 2;
const int AudioFormatClass::MinBitRate = 0;
const int AudioFormatClass::MaxBitRate = 2040;
const int AudioFormatClass::ModBitRate = 8;
const int AudioFormatClass::MinFlags = 0;
const int AudioFormatClass::MaxFlags = 255;
const int AudioFormatClass::MinProfile = 0;
const int AudioFormatClass::MaxProfile = 7;
const int AudioFormatClass::MinLevel = 0;
const int AudioFormatClass::MaxLevel = 7;
const int AudioFormatClass::MinExtensionFlags = 0;
const int AudioFormatClass::MaxExtensionFlags = 7;
//---------------------------------------------------------------------------
AudioFormatClass::AudioFormatClass()
{
	Format = 1;
	Extension = 0;
	Channels = 8;
	Channels3D = 8;
	SampleRates = 127;
	BitDepths = 7;
	BitRate = 640;
	Flags = 0;
	Profile = 0;
	FrameLength960 = true;
	FrameLength1024 = true;
	SystemH = false;
	ExplicitMPS = false;
	Level = 0;
	LowComplexity = true;
	Baseline = true;
	ExtensionFlags = 0;
	LastFormat = Format;
	std::memset(OtherFlags, 0, 3);
}
//---------------------------------------------------------------------------
bool AudioFormatClass::Read(const unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	int Code = (Data[0] >> 3) & 15;

	if (Code == 15)
		Code += (Data[2] >> 3);

	for (Format = MinFormat; Format < MaxFormat; Format++)
		if (Code == Formats[Format].Code)
			break;

	if (Format == MaxFormat)
		Extension = Code - 15;

	LastFormat = Format;
	std::memset(OtherFlags, 0, 3);

	switch (Formats[Format].Channels)
	{
		case 5:
			Level = Data[0] & 7;
			OtherFlags[0] |= Data[0] & 128;
			OtherFlags[1] |= Data[1] & 128;
			break;

		case 8:
			Channels = (Data[0] & 7) + 1;
			OtherFlags[0] |= Data[0] & 128;
			OtherFlags[1] |= Data[1] & 128;
			break;

		case 32:
			Channels3D = Data[0] & 7;
			Channels3D |= (Data[0] & 128) >> 4;
			Channels3D |= (Data[1] & 128) >> 3;
			Channels3D++;
			break;

		default:
			OtherFlags[0] |= Data[0] & 135;
			OtherFlags[1] |= Data[1] & 128;
			break;
	}

	SampleRates = Data[1] & Formats[Format].SampleRates;
	OtherFlags[1] |= Data[1] & (~Formats[Format].SampleRates & 127);

	switch (Formats[Format].Type)
	{
		case AUDIO_NONE:
			OtherFlags[2] |= Data[2] & 7;
			break;

		case AUDIO_BIT_DEPTHS:
			BitDepths = Data[2] & 7;

			if (Formats[Format].Code < 15)
				OtherFlags[2] |= Data[2] & 248;

			break;

		case AUDIO_BIT_RATE:
			BitRate = Data[2] * 8;
			break;

		case AUDIO_FLAGS:
			Flags = Data[2];
			break;

		case AUDIO_PROFILE:
			Profile = Data[2] & 7;

			if (Formats[Format].Code < 15)
				OtherFlags[2] |= Data[2] & 248;

			break;

		case AUDIO_MPEG4:
			FrameLength960 = Data[2] & 2;
			FrameLength1024 = Data[2] & 4;
			OtherFlags[2] |= Data[2] & 1;
			break;

		case AUDIO_MPEG4_H:
			FrameLength960 = Data[2] & 2;
			FrameLength1024 = Data[2] & 4;
			SystemH = Data[2] & 1;
			break;

		case AUDIO_MPEG4_MPS:
			FrameLength960 = Data[2] & 2;
			FrameLength1024 = Data[2] & 4;
			ExplicitMPS = Data[2] & 1;
			break;

		case AUDIO_MPEGH_3D:
			LowComplexity = Data[2] & 1;
			Baseline = Data[2] & 2;
			OtherFlags[2] |= Data[2] & 4;
			break;

		case AUDIO_EXTENSION_FLAGS:
		case AUDIO_EXTENSION:
			ExtensionFlags = Data[2] & 7;
			break;
	}

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 3)
		return false;

	if (!IsValid())
		return false;

	if (Formats[Format].Code < 15)
	{
		Data[0] = Formats[Format].Code << 3;
		Data[1] = 0;
		Data[2] = 0;
	}
	else
	{
		Data[0] = 15 << 3;
		Data[1] = 0;

		if (Format < MaxFormat)
			Data[2] = (Formats[Format].Code - 15) << 3;
		else
			Data[2] = Extension << 3;
	}

	switch (Formats[Format].Channels)
	{
		case 5:
			Data[0] |= Level;
			break;

		case 8:
			Data[0] |= Channels - 1;
			break;

		case 32:
			Channels3D--;
			Data[0] |= Channels3D & 7;
			Data[0] |= (Channels3D & 8) << 4;
			Data[1] |= (Channels3D & 16) << 3;
			Channels3D++;
			break;
	}

	Data[1] |= SampleRates & Formats[Format].SampleRates;

	switch (Formats[Format].Type)
	{
		case AUDIO_BIT_DEPTHS:
			Data[2] |= BitDepths;
			break;

		case AUDIO_BIT_RATE:
			Data[2] |= BitRate / 8;
			break;

		case AUDIO_FLAGS:
			Data[2] |= Flags;
			break;

		case AUDIO_PROFILE:
			Data[2] |= Profile;
			break;

		case AUDIO_MPEG4:
			Data[2] |= FrameLength960 << 1;
			Data[2] |= FrameLength1024 << 2;
			break;

		case AUDIO_MPEG4_H:
			Data[2] |= FrameLength960 << 1;
			Data[2] |= FrameLength1024 << 2;
			Data[2] |= SystemH;
			break;

		case AUDIO_MPEG4_MPS:
			Data[2] |= FrameLength960 << 1;
			Data[2] |= FrameLength1024 << 2;
			Data[2] |= ExplicitMPS;
			break;

		case AUDIO_MPEGH_3D:
			Data[2] |= LowComplexity;
			Data[2] |= Baseline << 1;
			break;

		case AUDIO_EXTENSION_FLAGS:
		case AUDIO_EXTENSION:
			Data[2] |= ExtensionFlags;
			break;
	}

	if (Format == LastFormat)
	{
		Data[0] |= OtherFlags[0];
		Data[1] |= OtherFlags[1];
		Data[2] |= OtherFlags[2];
	}

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetInfoText(char *Text, int TextSize)
{
	if (!IsValid())
		return false;

	Text[0] = 0;

	switch (Formats[Format].Type)
	{
		case AUDIO_BIT_DEPTHS:
			if (BitDepths != 0)
			{
				const char *BitDepth16 = (BitDepths & 1) ? "16" : "";
				const char *Slash1 = (BitDepths & 1) && (BitDepths & 2) ? "/" : "";
				const char *BitDepth20 = (BitDepths & 2) ? "20" : "";
				const char *Slash2 = (BitDepths & 3) && (BitDepths & 4) ? "/" : "";
				const char *BitDepth24 = (BitDepths & 4) ? "24" : "";
				std::snprintf(Text, TextSize, "%s%s%s%s%s-bit", BitDepth16, Slash1, BitDepth20, Slash2, BitDepth24);
			}

			break;

		case AUDIO_BIT_RATE:
			if (BitRate != 0)
				std::snprintf(Text, TextSize, "Max: %d kbit/s", BitRate);

			break;

		case AUDIO_FLAGS:
			if (Flags != 0)
				std::snprintf(Text, TextSize, "Flags: %d", Flags);

			break;

		case AUDIO_PROFILE:
			if (Profile != 0)
				std::snprintf(Text, TextSize, "Profile: %d", Profile);

			break;

		case AUDIO_MPEG4:
		case AUDIO_MPEG4_H:
		case AUDIO_MPEG4_MPS:
			if (FrameLength960 || FrameLength1024)
			{
				const char *Samples960 = FrameLength960 ? "960" : "";
				const char *Slash = FrameLength960 && FrameLength1024 ? "/" : "";
				const char *Samples1024 = FrameLength1024 ? "1024" : "";
				std::snprintf(Text, TextSize, "%s%s%s samples", Samples960, Slash, Samples1024);
			}

			break;

		case AUDIO_MPEGH_3D:
			if (Level != 0)
				std::snprintf(Text, TextSize, "Level: %d", Level);

			break;

		case AUDIO_EXTENSION_FLAGS:
		case AUDIO_EXTENSION:
			if (ExtensionFlags != 0)
				std::snprintf(Text, TextSize, "Flags: %d", ExtensionFlags);

			break;
	}

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetFormatText(char *Text, int TextSize)
{
	if (!IsValidFormat())
		return false;

	if (Format < MaxFormat)
		std::snprintf(Text, TextSize, "%s", Formats[Format].Text);
	else
		std::snprintf(Text, TextSize, "%s (%d)", Formats[Format].Text, Extension);

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetFormatText(int Format, char *Text, int TextSize)
{
	if (Format < MinFormat || Format > MaxFormat)
		return false;

	std::snprintf(Text, TextSize, "%s", Formats[Format].Text);
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetFormat()
{
	return Format;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetFormat(int Value)
{
	Format = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetExtension()
{
	return Extension;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetExtension(int Value)
{
	Extension = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetType()
{
	if (!IsValidFormat())
		return AUDIO_INVALID;

	return Formats[Format].Type;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetMaxChannels()
{
	if (!IsValidFormat())
		return AUDIO_INVALID;

	return Formats[Format].Channels;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetChannelsText(int Channels, char *Text, int TextSize)
{
	if (Channels < MinChannels || Channels > MaxChannels)
		return false;

	std::snprintf(Text, TextSize, "%s", ChannelsText[Channels]);
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetChannels()
{
	return Channels;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetChannels(int Value)
{
	Channels = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetChannels3D()
{
	return Channels3D;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetChannels3D(int Value)
{
	Channels3D = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetSampleRates()
{
	if (!IsValidFormat())
		return AUDIO_INVALID;

	return Formats[Format].SampleRates;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetSampleRate(int Index)
{
	if (Index < MinSampleRate || Index > MaxSampleRate)
		return false;

	return SampleRates & (1 << Index);
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetSampleRate(int Index, bool Enabled)
{
	if (Index < MinSampleRate || Index > MaxSampleRate)
		return false;

	if (Enabled)
		SampleRates |= 1 << Index;
	else
		SampleRates &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetBitDepth(int Index)
{
	if (Index < MinBitDepth || Index > MaxBitDepth)
		return false;

	return BitDepths & (1 << Index);
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetBitDepth(int Index, bool Enabled)
{
	if (Index < MinBitDepth || Index > MaxBitDepth)
		return false;

	if (Enabled)
		BitDepths |= 1 << Index;
	else
		BitDepths &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetBitRate()
{
	return BitRate;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetBitRate(int Value)
{
	BitRate = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetFlags()
{
	return Flags;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetFlags(int Value)
{
	Flags = Value;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetProfile()
{
	return Profile;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetProfile(int Value)
{
	Profile = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetFrameLength960()
{
	return FrameLength960;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetFrameLength960(bool Enabled)
{
	FrameLength960 = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetFrameLength1024()
{
	return FrameLength1024;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetFrameLength1024(bool Enabled)
{
	FrameLength1024 = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetSystemH()
{
	return SystemH;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetSystemH(bool Enabled)
{
	SystemH = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetExplicitMPS()
{
	return ExplicitMPS;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetExplicitMPS(bool Enabled)
{
	ExplicitMPS = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetLevelText(int Level, char *Text, int TextSize)
{
	if (Level < MinLevel || Level > MaxLevel || LevelText[Level] == 0)
		return false;

	std::snprintf(Text, TextSize, "%s", LevelText[Level]);
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetLevel()
{
	return Level;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetLevel(int Value)
{
	Level = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetLowComplexity()
{
	return LowComplexity;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetLowComplexity(bool Enabled)
{
	LowComplexity = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::GetBaseline()
{
	return Baseline;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetBaseline(bool Enabled)
{
	Baseline = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int AudioFormatClass::GetExtensionFlags()
{
	return ExtensionFlags;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::SetExtensionFlags(int Value)
{
	ExtensionFlags = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValid()
{
	if (!IsValidFormat())
		return false;

	if (Format == MaxFormat && !IsValidExtension())
		return false;

	switch (Formats[Format].Channels)
	{
		case 8:
			if (!IsValidChannels())
				return false;

			break;

		case 32:
			if (!IsValidChannels3D())
				return false;

			break;
	}

	switch (Formats[Format].Type)
	{
		case AUDIO_NONE:
			return true;

		case AUDIO_BIT_DEPTHS:
			return true;

		case AUDIO_BIT_RATE:
			return IsValidBitRate();

		case AUDIO_FLAGS:
			return IsValidFlags();

		case AUDIO_PROFILE:
			return IsValidProfile();

		case AUDIO_MPEG4:
		case AUDIO_MPEG4_H:
		case AUDIO_MPEG4_MPS:
			return true;

		case AUDIO_MPEGH_3D:
			return IsValidLevel();

		case AUDIO_EXTENSION_FLAGS:
			return IsValidExtensionFlags();

		case AUDIO_EXTENSION:
			return IsValidExtension() && IsValidExtensionFlags();
	}

	return false;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidFormat()
{
	return Format >= MinFormat && Format <= MaxFormat;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidExtension()
{
	return Extension >= MinExtension && Extension <= MaxExtension;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidChannels()
{
	return Channels >= MinChannels && Channels <= MaxChannels;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidChannels3D()
{
	return Channels3D >= MinChannels3D && Channels3D <= MaxChannels3D;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidBitRate()
{
	return BitRate >= MinBitRate && BitRate <= MaxBitRate && BitRate % ModBitRate == 0;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidFlags()
{
	return Flags >= MinFlags && Flags <= MaxFlags;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidProfile()
{
	return Profile >= MinProfile && Profile <= MaxProfile;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidLevel()
{
	return Level >= MinLevel && Level <= MaxLevel;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsValidExtensionFlags()
{
	return ExtensionFlags >= MinExtensionFlags && ExtensionFlags <= MaxExtensionFlags;
}
//---------------------------------------------------------------------------
bool AudioFormatClass::IsSupported()
{
	if (Formats[Format].Code == 0 || Formats[Format].Code == 15)
		return false;

	return IsValidFormat();
}
//---------------------------------------------------------------------------
