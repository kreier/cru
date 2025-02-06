//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "HDMISupportClass.h"
//---------------------------------------------------------------------------
const int HDMISupportClass::MinTMDSClock = 5;
const int HDMISupportClass::MaxTMDSClock = 1275;
const int HDMISupportClass::ModTMDSClock = 5;
const int HDMISupportClass::MinContentType = 0;
const int HDMISupportClass::MaxContentType = 3;
const int HDMISupportClass::MinLatency = 0;
const int HDMISupportClass::MaxLatency = 500;
const int HDMISupportClass::ModLatency = 2;
//---------------------------------------------------------------------------
HDMISupportClass::HDMISupportClass(int NewMaxDataSize)
{
	MaxDataSize = NewMaxDataSize;
	std::snprintf(PhysicalAddress, sizeof PhysicalAddress, "0.0.0.0");
	DeepColorYCbCr444 = false;
	DeepColor30bit = false;
	DeepColor36bit = false;
	DeepColor48bit = false;
	SupportsAI = false;
	DualLinkDVI = false;
	OverrideTMDSClock = TMDSClockPossible();
	TMDSClock = 340;
	ContentType[0] = false;
	ContentType[1] = false;
	ContentType[2] = false;
	ContentType[3] = false;
	IncludeLatency = false;
	VideoSupported = false;
	VideoLatency = BLANK;
	AudioSupported = false;
	AudioLatency = BLANK;
	IncludeInterlacedLatency = false;
	InterlacedVideoSupported = false;
	InterlacedVideoLatency = BLANK;
	InterlacedAudioSupported = false;
	InterlacedAudioLatency = BLANK;
	OtherFlags = 0;
	HDMI_3D_Length = 0;
	OtherSize = 0;
	MaxOtherSize = sizeof OtherData;
	std::memset(OtherData, 0, MaxOtherSize);
}
//---------------------------------------------------------------------------
bool HDMISupportClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;
	int Index;
	int HDMI_VIC_Length;

	if (!Data)
		return false;

	if (MaxSize < 6)
		return false;

	Type = Data[0] >> 5;
	Size = Data[0] & 31;

	if (Type != 3)
		return false;

	MaxDataSize = MaxSize - 1;

	if (Size < 5 || Size > MaxDataSize)
		return false;

	if (std::memcmp(&Data[1], "\x03\x0C\x00", 3) != 0)
		return false;

	if (!ReadPhysicalAddress(&Data[4]))
		return false;

	if (Size >= 6 && Data[6] != 0)
	{
		DeepColorYCbCr444 = Data[6] & 8;
		DeepColor30bit = Data[6] & 16;
		DeepColor36bit = Data[6] & 32;
		DeepColor48bit = Data[6] & 64;
		SupportsAI = Data[6] & 128;
		DualLinkDVI = Data[6] & 1;
	}
	else
	{
		DeepColorYCbCr444 = false;
		DeepColor30bit = false;
		DeepColor36bit = false;
		DeepColor48bit = false;
		SupportsAI = false;
		DualLinkDVI = false;
	}

	if (Size >= 7 && Data[7] != 0)
	{
		OverrideTMDSClock = true;
		TMDSClock = Data[7] * 5;
	}
	else
	{
		OverrideTMDSClock = false;
		TMDSClock = 340;
	}

	if (Size >= 8 && Data[8] != 0)
	{
		ContentType[0] = Data[8] & 1;
		ContentType[1] = Data[8] & 2;
		ContentType[2] = Data[8] & 4;
		ContentType[3] = Data[8] & 8;
		IncludeLatency = Data[8] & 128;
		IncludeInterlacedLatency = Data[8] & 64;
	}
	else
	{
		ContentType[0] = false;
		ContentType[1] = false;
		ContentType[2] = false;
		ContentType[3] = false;
		IncludeLatency = false;
		IncludeInterlacedLatency = false;
	}

	Index = 9;

	if (IncludeLatency)
		Index += 2;

	if (IncludeInterlacedLatency)
		Index += 2;

	if (Size >= 10 && IncludeLatency)
	{
		VideoLatency = (Data[9] - 1) * 2;

		if (VideoLatency > MaxLatency)
			VideoSupported = false;
		else
			VideoSupported = true;

		if (VideoLatency < MinLatency || VideoLatency > MaxLatency)
			VideoLatency = BLANK;

		AudioLatency = (Data[10] - 1) * 2;

		if (AudioLatency > MaxLatency)
			AudioSupported = false;
		else
			AudioSupported = true;

		if (AudioLatency < MinLatency || AudioLatency > MaxLatency)
			AudioLatency = BLANK;
	}
	else
	{
		IncludeLatency = false;
		VideoSupported = false;
		VideoLatency = BLANK;
		AudioSupported = false;
		AudioLatency = BLANK;
	}

	if (Size >= 12 && IncludeLatency && IncludeInterlacedLatency)
	{
		InterlacedVideoLatency = (Data[11] - 1) * 2;

		if (InterlacedVideoLatency > MaxLatency)
			InterlacedVideoSupported = false;
		else
			InterlacedVideoSupported = true;

		if (InterlacedVideoLatency < MinLatency || InterlacedVideoLatency > MaxLatency)
			InterlacedVideoLatency = BLANK;

		InterlacedAudioLatency = (Data[12] - 1) * 2;

		if (InterlacedAudioLatency > MaxLatency)
			InterlacedAudioSupported = false;
		else
			InterlacedAudioSupported = true;

		if (InterlacedAudioLatency < MinLatency || InterlacedAudioLatency > MaxLatency)
			InterlacedAudioLatency = BLANK;
	}
	else
	{
		IncludeInterlacedLatency = false;
		InterlacedVideoSupported = false;
		InterlacedVideoLatency = BLANK;
		InterlacedAudioSupported = false;
		InterlacedAudioLatency = BLANK;
	}

	if (Size >= Index && Data[Index] != 0)
		OtherFlags = Data[Index];
	else
		OtherFlags = 0;

	Index++;

	if (Size >= Index && Data[Index] != 0)
	{
		HDMI_VIC_Length = Data[Index] >> 5;

		if (HDMI_VIC_Length > Size - Index)
			HDMI_VIC_Length = Size - Index;

		HDMI_3D_Length = Data[Index] & 31;

		if (HDMI_3D_Length > Size - Index - HDMI_VIC_Length)
			HDMI_3D_Length = Size - Index - HDMI_VIC_Length;
	}
	else
	{
		HDMI_VIC_Length = 0;
		HDMI_3D_Length = 0;
	}

	Index++;
	HDMIResolutionList.Read(&Data[Index], HDMI_VIC_Length);
	Index += HDMI_VIC_Length;
	OtherSize = Size - Index + 1;

	if (OtherSize < 0 || OtherSize > MaxOtherSize)
		OtherSize = 0;

	std::memset(OtherData, 0, MaxOtherSize);

	if (OtherSize > 0)
		std::memcpy(OtherData, &Data[Index], OtherSize);

	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::Write(unsigned char *Data, int MaxSize)
{
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 6)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[1] = 0x03;
	Data[2] = 0x0C;
	Data[3] = 0x00;

	if (!WritePhysicalAddress(&Data[4]))
		return false;

	Size = 5;

	if (DeepColorYCbCr444 || DeepColor30bit || DeepColor36bit || DeepColor48bit || SupportsAI || DualLinkDVI)
	{
		Size = 6;
		Data[6] |= DeepColorYCbCr444 ? 8 : 0;
		Data[6] |= DeepColor30bit ? 16 : 0;
		Data[6] |= DeepColor36bit ? 32 : 0;
		Data[6] |= DeepColor48bit ? 64 : 0;
		Data[6] |= SupportsAI ? 128 : 0;
		Data[6] |= DualLinkDVI ? 1 : 0;
	}

	if (OverrideTMDSClock)
	{
		Size = 7;
		Data[7] = TMDSClock / 5;
	}

	if (ContentType[0] || ContentType[1] || ContentType[2] || ContentType[3])
	{
		Size = 8;
		Data[8] |= ContentType[0] ? 1 : 0;
		Data[8] |= ContentType[1] ? 2 : 0;
		Data[8] |= ContentType[2] ? 4 : 0;
		Data[8] |= ContentType[3] ? 8 : 0;
	}

	if (IncludeLatency)
	{
		Size = 10;
		Data[8] |= IncludeLatency ? 128 : 0;

		if (!VideoSupported)
			Data[9] = 255;
		else if (VideoLatency == BLANK)
			Data[9] = 0;
		else
			Data[9] = VideoLatency / 2 + 1;

		if (!AudioSupported)
			Data[10] = 255;
		else if (AudioLatency == BLANK)
			Data[10] = 0;
		else
			Data[10] = AudioLatency / 2 + 1;
	}

	if (IncludeInterlacedLatencyPossible() && IncludeLatency && IncludeInterlacedLatency)
	{
		Size = 12;
		Data[8] |= IncludeInterlacedLatency ? 64 : 0;

		if (!InterlacedVideoSupported)
			Data[11] = 255;
		else if (InterlacedVideoLatency == BLANK)
			Data[11] = 0;
		else
			Data[11] = InterlacedVideoLatency / 2 + 1;

		if (!InterlacedAudioSupported)
			Data[12] = 255;
		else if (InterlacedAudioLatency == BLANK)
			Data[12] = 0;
		else
			Data[12] = InterlacedAudioLatency / 2 + 1;
	}

	if (OtherFlags || HDMIResolutionList.GetCount() > 0 || HDMI_3D_Length > 0)
	{
		if (Size < 8)
			Size = 8;

		Data[8] |= 32;
		Size++;
		Data[Size] = OtherFlags;
	}

	if (HDMIResolutionList.GetCount() > 0 || HDMI_3D_Length > 0)
	{
		Size++;
		Data[Size] = HDMIResolutionList.GetCount() << 5;
		Data[Size] |= HDMI_3D_Length;
		HDMIResolutionList.Write(&Data[Size + 1], HDMIResolutionList.GetSize());
		Size += HDMIResolutionList.GetSize();
	}

	if (OtherSize > 0)
	{
		if (Size < 8)
			Size = 8;

		std::memcpy(&Data[Size + 1], OtherData, OtherSize);
		Size += OtherSize;
	}

	Data[0] = 3 << 5;
	Data[0] |= Size;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::ReadPhysicalAddress(const unsigned char *Data)
{
	if (!Data)
		return false;

	std::snprintf(PhysicalAddress, sizeof PhysicalAddress, "%d.%d.%d.%d", (Data[0] >> 4) & 15, Data[0] & 15, (Data[1] >> 4) & 15, Data[1] & 15);
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::WritePhysicalAddress(unsigned char *Data)
{
	if (!Data)
		return false;

	int Value[4];
	char Invalid;

	if (std::sscanf(PhysicalAddress, "%d.%d.%d.%d %c", &Value[0], &Value[1], &Value[2], &Value[3], &Invalid) != 4)
		return false;

	for (int Index = 0; Index < 4; Index++)
		if (Value[Index] < 0 || Value[Index] > 15)
			return false;

	Data[0] = (Value[0] << 4) | Value[1];
	Data[1] = (Value[2] << 4) | Value[3];
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetPhysicalAddressText(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", PhysicalAddress);
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetPhysicalAddressText(const char *Text)
{
	unsigned char Data[2];

	std::snprintf(PhysicalAddress, sizeof PhysicalAddress, "%s", Text);

	if (WritePhysicalAddress(Data))
		ReadPhysicalAddress(Data);

	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::ExtensionPossible()
{
	return MaxDataSize >= 6;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetDeepColorYCbCr444()
{
	return DeepColorYCbCr444;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetDeepColorYCbCr444(bool Enabled)
{
	DeepColorYCbCr444 = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetDeepColor30bit()
{
	return DeepColor30bit;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetDeepColor30bit(bool Enabled)
{
	DeepColor30bit = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetDeepColor36bit()
{
	return DeepColor36bit;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetDeepColor36bit(bool Enabled)
{
	DeepColor36bit = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetDeepColor48bit()
{
	return DeepColor48bit;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetDeepColor48bit(bool Enabled)
{
	DeepColor48bit = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetSupportsAI()
{
	return SupportsAI;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetSupportsAI(bool Enabled)
{
	SupportsAI = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetDualLinkDVI()
{
	return DualLinkDVI;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetDualLinkDVI(bool Enabled)
{
	DualLinkDVI = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::TMDSClockPossible()
{
	return MaxDataSize >= 7;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetOverrideTMDSClock()
{
	return OverrideTMDSClock;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetOverrideTMDSClock(bool Enabled)
{
	OverrideTMDSClock = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int HDMISupportClass::GetTMDSClock()
{
	return TMDSClock;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetTMDSClock(int Value)
{
	TMDSClock = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::ContentTypesPossible()
{
	return MaxDataSize >= 8;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetContentType(int Index)
{
	if (Index < MinContentType || Index > MaxContentType)
		return false;

	return ContentType[Index];
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetContentType(int Index, bool Enabled)
{
	if (Index < MinContentType || Index > MaxContentType)
		return false;

	ContentType[Index] = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IncludeLatencyPossible()
{
	int DataSize = 10;

	if (OtherFlags || HDMIResolutionList.GetCount() > 0 || HDMI_3D_Length > 0)
		DataSize++;

	if (HDMIResolutionList.GetCount() > 0 || HDMI_3D_Length > 0)
		DataSize++;

	DataSize += HDMIResolutionList.GetSize();
	DataSize += OtherSize;
	return DataSize <= MaxDataSize;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetIncludeLatency()
{
	return IncludeLatency;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetIncludeLatency(bool Enabled)
{
	IncludeLatency = Enabled;

	if (!IncludeLatency)
		IncludeInterlacedLatency = false;

	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetVideoSupported()
{
	return VideoSupported;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetVideoSupported(bool Enabled)
{
	VideoSupported = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int HDMISupportClass::GetVideoLatency()
{
	return VideoLatency;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetVideoLatency(int Value)
{
	VideoLatency = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetAudioSupported()
{
	return AudioSupported;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetAudioSupported(bool Enabled)
{
	AudioSupported = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int HDMISupportClass::GetAudioLatency()
{
	return AudioLatency;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetAudioLatency(int Value)
{
	AudioLatency = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IncludeInterlacedLatencyPossible()
{
	int DataSize = 12;

	if (OtherFlags || HDMIResolutionList.GetCount() > 0 || HDMI_3D_Length > 0)
		DataSize++;

	if (HDMIResolutionList.GetCount() > 0 || HDMI_3D_Length > 0)
		DataSize++;

	DataSize += HDMIResolutionList.GetSize();
	DataSize += OtherSize;
	return DataSize <= MaxDataSize;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetIncludeInterlacedLatency()
{
	return IncludeInterlacedLatency;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetIncludeInterlacedLatency(bool Enabled)
{
	IncludeInterlacedLatency = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetInterlacedVideoSupported()
{
	return InterlacedVideoSupported;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetInterlacedVideoSupported(bool Enabled)
{
	InterlacedVideoSupported = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int HDMISupportClass::GetInterlacedVideoLatency()
{
	return InterlacedVideoLatency;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetInterlacedVideoLatency(int Value)
{
	InterlacedVideoLatency = Value;
	return true;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::GetInterlacedAudioSupported()
{
	return InterlacedAudioSupported;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetInterlacedAudioSupported(bool Enabled)
{
	InterlacedAudioSupported = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int HDMISupportClass::GetInterlacedAudioLatency()
{
	return InterlacedAudioLatency;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::SetInterlacedAudioLatency(int Value)
{
	InterlacedAudioLatency = Value;
	return true;
}
//---------------------------------------------------------------------------
HDMIResolutionListClass *HDMISupportClass::Resolutions()
{
	int MaxSize = MaxDataSize - OtherSize - 10;

	if (IncludeLatency)
		MaxSize -= 2;

	if (IncludeInterlacedLatencyPossible() && IncludeLatency && IncludeInterlacedLatency)
		MaxSize -= 2;

	if (MaxSize < 0)
		MaxSize = 0;

	HDMIResolutionList.SetMaxSize(MaxSize);
	return &HDMIResolutionList;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValid()
{
	return IsValidPhysicalAddress() && IsValidTMDSClock() && IsValidLatency();
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidPhysicalAddress()
{
	unsigned char Data[2];

	return WritePhysicalAddress(Data);
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidTMDSClock()
{
	if (!OverrideTMDSClock)
		return true;

	return TMDSClock >= MinTMDSClock && TMDSClock <= MaxTMDSClock && TMDSClock % ModTMDSClock == 0;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidLatency()
{
	return IsValidVideoLatency() && IsValidAudioLatency() && IsValidInterlacedVideoLatency() && IsValidInterlacedAudioLatency();
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidVideoLatency()
{
	if (!IncludeLatency || !VideoSupported || VideoLatency == BLANK)
		return true;

	return VideoLatency >= MinLatency && VideoLatency <= MaxLatency && VideoLatency % ModLatency == 0;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidAudioLatency()
{
	if (!IncludeLatency || !AudioSupported || AudioLatency == BLANK)
		return true;

	return AudioLatency >= MinLatency && AudioLatency <= MaxLatency && AudioLatency % ModLatency == 0;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidInterlacedVideoLatency()
{
	if (!IncludeLatency || !IncludeInterlacedLatency || !InterlacedVideoSupported || InterlacedVideoLatency == BLANK)
		return true;

	return InterlacedVideoLatency >= MinLatency && InterlacedVideoLatency <= MaxLatency && InterlacedVideoLatency % ModLatency == 0;
}
//---------------------------------------------------------------------------
bool HDMISupportClass::IsValidInterlacedAudioLatency()
{
	if (!IncludeLatency || !IncludeInterlacedLatency || !InterlacedAudioSupported || InterlacedAudioLatency == BLANK)
		return true;

	return InterlacedAudioLatency >= MinLatency && InterlacedAudioLatency <= MaxLatency && InterlacedAudioLatency % ModLatency == 0;
}
//---------------------------------------------------------------------------
