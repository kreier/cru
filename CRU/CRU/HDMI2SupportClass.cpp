//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "HDMI2SupportClass.h"
//---------------------------------------------------------------------------
const char *HDMI2SupportClass::FRLRateText[] =
{
	"Not supported",
	"9 Gbps (3 x 3 lanes)",
	"18 Gbps (6 x 3 lanes)",
	"24 Gbps (6 x 4 lanes)",
	"32 Gbps (8 x 4 lanes)",
	"40 Gbps (10 x 4 lanes)",
	"48 Gbps (12 x 4 lanes)",
};

const char *HDMI2SupportClass::DSCSlicesText[] =
{
	"Not supported",
	"1 slice up to 340 MHz",
	"2 slices up to 340 MHz",
	"4 slices up to 340 MHz",
	"8 slices up to 340 MHz",
	"8 slices up to 400 MHz",
	"12 slices up to 400 MHz",
	"16 slices up to 400 MHz",
};

const int HDMI2SupportClass::MinTMDSRate = 5;
const int HDMI2SupportClass::MaxTMDSRate = 1275;
const int HDMI2SupportClass::ModTMDSRate = 5;
const int HDMI2SupportClass::FeaturesMask = 223;
const int HDMI2SupportClass::MinColorFormat = 0;
const int HDMI2SupportClass::MaxColorFormat = 2;
const int HDMI2SupportClass::MinFRLRate = 0;
const int HDMI2SupportClass::MaxFRLRate = 6;
const int HDMI2SupportClass::Features21Mask = 63;
const int HDMI2SupportClass::MinMinRefreshRate = 1;
const int HDMI2SupportClass::MaxMinRefreshRate = 48;
const int HDMI2SupportClass::MinMaxRefreshRate = 100;
const int HDMI2SupportClass::MaxMaxRefreshRate = 1023;
const int HDMI2SupportClass::DSCFeaturesMask = 207;
const int HDMI2SupportClass::MinDSCSlices = 0;
const int HDMI2SupportClass::MaxDSCSlices = 7;
const int HDMI2SupportClass::MinDSCChunkSize = 1;
const int HDMI2SupportClass::MaxDSCChunkSize = 63;
//---------------------------------------------------------------------------
HDMI2SupportClass::HDMI2SupportClass(int NewMaxDataSize)
{
	MaxDataSize = NewMaxDataSize;
	Version = 1;
	OverrideTMDSRate = true;
	TMDSRate = 600;
	Features[0] = 128;
	Features[1] = 0;
	Features[2] = 0;
	MinRefreshRate = BLANK;
	MaxRefreshRate = BLANK;
	DSCFeatures[0] = 0;
	DSCFeatures[1] = 0;
	DSCChunkSize = BLANK;
	OtherSize = 0;
	MaxOtherSize = sizeof OtherData;
	std::memset(OtherData, 0, MaxOtherSize);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;
	int Index;

	if (!Data)
		return false;

	if (MaxSize < 8)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 3)
		return false;

	MaxDataSize = MaxSize - 1;

	if (Size < 7 || Size > MaxDataSize)
		return false;

	if (std::memcmp(&Data[1], "\xD8\x5D\xC4", 3) != 0)
		return false;

	if (Data[4] != 0)
		Version = Data[4];
	else
		Version = 1;

	if (Data[5] != 0)
	{
		OverrideTMDSRate = true;
		TMDSRate = Data[5] * 5;
	}
	else
	{
		OverrideTMDSRate = false;
		TMDSRate = 600;
	}

	Features[0] = Data[6];
	Features[1] = Data[7];

	if (Size >= 8)
		Features[2] = Data[8];

	if (Size >= 10)
	{
		MinRefreshRate = Data[9] & 63;
		MaxRefreshRate = ((Data[9] & 192) << 2) | Data[10];

		if (!IsValidRefreshRate())
		{
			MinRefreshRate = BLANK;
			MaxRefreshRate = BLANK;
		}
	}

	if (Size >= 13)
	{
		DSCFeatures[0] = Data[11];
		DSCFeatures[1] = Data[12];
		DSCChunkSize = Data[13] & 63;

		if (!IsValidDSCChunkSize())
			DSCChunkSize = BLANK;
	}

	Index = 14;
	OtherSize = Size - Index + 1;

	if (OtherSize < 0 || OtherSize > MaxOtherSize)
		OtherSize = 0;

	std::memset(OtherData, 0, MaxOtherSize);

	if (OtherSize > 0)
		std::memcpy(OtherData, &Data[Index], OtherSize);

	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::Write(unsigned char *Data, int MaxSize)
{
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 8)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[1] = 0xD8;
	Data[2] = 0x5D;
	Data[3] = 0xC4;
	Data[4] = Version;

	if (OverrideTMDSRate)
		Data[5] = TMDSRate / 5;

	Data[6] = Features[0];
	Data[7] = Features[1];
	Size = 7;

	if (Features[2])
	{
		Size = 8;
		Data[8] = Features[2];
	}

	if (IsValidMinRefreshRate() && IsValidMaxRefreshRate())
	{
		Size = 10;
		Data[9] = ((MaxRefreshRate >> 2) & 192) | (MinRefreshRate & 63);
		Data[10] = MaxRefreshRate & 255;
	}

	if (DSCFeatures[0] || DSCFeatures[1] || DSCChunkSize != BLANK)
	{
		Size = 13;
		Data[11] = DSCFeatures[0];
		Data[12] = DSCFeatures[1];

		if (DSCChunkSize != BLANK)
			Data[13] = DSCChunkSize & 63;
	}

	if (OtherSize > 0)
	{
		if (Size < 13)
			Size = 13;

		std::memcpy(&Data[Size + 1], OtherData, OtherSize);
		Size += OtherSize;
	}

	Data[0] = 3 << 5;
	Data[0] |= Size;
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetOverrideTMDSRate()
{
	return OverrideTMDSRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetOverrideTMDSRate(bool Enabled)
{
	OverrideTMDSRate = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetTMDSRate()
{
	return TMDSRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetTMDSRate(int Value)
{
	TMDSRate = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetFeature(int Index)
{
	if (!(FeaturesMask & (1 << Index)))
		return false;

	return Features[0] & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetFeature(int Index, bool Enabled)
{
	if (!(FeaturesMask & (1 << Index)))
		return false;

	if (Enabled)
		Features[0] |= 1 << Index;
	else
		Features[0] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetColorFormat(int Index)
{
	if (Index < MinColorFormat || Index > MaxColorFormat)
		return false;

	return Features[1] & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetColorFormat(int Index, bool Enabled)
{
	if (Index < MinColorFormat || Index > MaxColorFormat)
		return false;

	if (Enabled)
		Features[1] |= 1 << Index;
	else
		Features[1] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetFRLRateText(int Value, char *Text, int TextSize)
{
	if (Value < MinFRLRate || Value > MaxFRLRate)
		return false;

	std::snprintf(Text, TextSize, "%s", FRLRateText[Value]);
	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetFRLRate()
{
	return Features[1] >> 4;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetFRLRate(int Value)
{
	if (Value < MinFRLRate || Value > MaxFRLRate)
		return false;

	Features[1] = (Value << 4) | (Features[1] & 15);
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::Features21Possible()
{
	return MaxDataSize >= 8;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetFeature21(int Index)
{
	if (!(Features21Mask & (1 << Index)))
		return false;

	return Features[2] & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetFeature21(int Index, bool Enabled)
{
	if (!(Features21Mask & (1 << Index)))
		return false;

	if (Enabled)
		Features[2] |= 1 << Index;
	else
		Features[2] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::RefreshRatePossible()
{
	return MaxDataSize >= 10;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetMinRefreshRate()
{
	return MinRefreshRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetMinRefreshRate(int Value)
{
	MinRefreshRate = Value;
	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetMaxRefreshRate()
{
	return MaxRefreshRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetMaxRefreshRate(int Value)
{
	MaxRefreshRate = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::DSCPossible()
{
	return MaxDataSize >= 13;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetDSCFeature(int Index)
{
	if (!(DSCFeaturesMask & (1 << Index)))
		return false;

	return DSCFeatures[0] & (1 << Index);
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetDSCFeature(int Index, bool Enabled)
{
	if (!(DSCFeaturesMask & (1 << Index)))
		return false;

	if (Enabled)
		DSCFeatures[0] |= 1 << Index;
	else
		DSCFeatures[0] &= ~(1 << Index);

	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetDSCFRLRate()
{
	return DSCFeatures[1] >> 4;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetDSCFRLRate(int Value)
{
	if (Value < MinFRLRate || Value > MaxFRLRate)
		return false;

	DSCFeatures[1] = (Value << 4) | (DSCFeatures[1] & 15);
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::GetDSCSlicesText(int Value, char *Text, int TextSize)
{
	if (Value < MinDSCSlices || Value > MaxDSCSlices)
		return false;

	std::snprintf(Text, TextSize, "%s", DSCSlicesText[Value]);
	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetDSCSlices()
{
	return DSCFeatures[1] & 15;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetDSCSlices(int Value)
{
	if (Value < MinDSCSlices || Value > MaxDSCSlices)
		return false;

	DSCFeatures[1] = (DSCFeatures[1] & 240) | Value;
	return true;
}
//---------------------------------------------------------------------------
int HDMI2SupportClass::GetDSCChunkSize()
{
	return DSCChunkSize;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::SetDSCChunkSize(int Value)
{
	DSCChunkSize = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValid()
{
	return IsValidTMDSRate() && IsValidRefreshRate() && IsValidDSCChunkSize();
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValidTMDSRate()
{
	if (!OverrideTMDSRate)
		return true;

	return TMDSRate >= MinTMDSRate && TMDSRate <= MaxTMDSRate && TMDSRate % ModTMDSRate == 0;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValidRefreshRate()
{
	if (MinRefreshRate == BLANK && MaxRefreshRate == BLANK)
		return true;

	return IsValidMinRefreshRate() && IsValidMaxRefreshRate();
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValidMinRefreshRate()
{
	return MinRefreshRate >= MinMinRefreshRate && MinRefreshRate <= MaxMinRefreshRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValidMaxRefreshRate()
{
	return MaxRefreshRate >= MinMaxRefreshRate && MaxRefreshRate <= MaxMaxRefreshRate;
}
//---------------------------------------------------------------------------
bool HDMI2SupportClass::IsValidDSCChunkSize()
{
	if (DSCChunkSize == BLANK)
		return true;

	return DSCChunkSize >= MinDSCChunkSize && DSCChunkSize <= MaxDSCChunkSize;
}
//---------------------------------------------------------------------------
