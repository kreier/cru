//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "TiledDisplayTopologyClass.h"
//---------------------------------------------------------------------------
const int TiledDisplayTopologyClass::MinPhysicalEnclosures = 0;
const int TiledDisplayTopologyClass::MaxPhysicalEnclosures = 1;
const int TiledDisplayTopologyClass::MinSingleTileBehavior = 0;
const int TiledDisplayTopologyClass::MaxSingleTileBehavior = 3;
const int TiledDisplayTopologyClass::MinMultipleTileBehavior = 0;
const int TiledDisplayTopologyClass::MaxMultipleTileBehavior = 1;
const int TiledDisplayTopologyClass::MinHTiles = 1;
const int TiledDisplayTopologyClass::MaxHTiles = 64;
const int TiledDisplayTopologyClass::MinVTiles = 1;
const int TiledDisplayTopologyClass::MaxVTiles = 64;
const int TiledDisplayTopologyClass::MinHLocation = 1;
const int TiledDisplayTopologyClass::MaxHLocation = 64;
const int TiledDisplayTopologyClass::MinVLocation = 1;
const int TiledDisplayTopologyClass::MaxVLocation = 64;
const int TiledDisplayTopologyClass::MinHSize = 1;
const int TiledDisplayTopologyClass::MaxHSize = 65536;
const int TiledDisplayTopologyClass::MinVSize = 1;
const int TiledDisplayTopologyClass::MaxVSize = 65536;
const int TiledDisplayTopologyClass::MinPixelMultiplier = 0;
const int TiledDisplayTopologyClass::MaxPixelMultiplier = 255;
const int TiledDisplayTopologyClass::MinTopBezelSize = 0;
const int TiledDisplayTopologyClass::MaxTopBezelSize = 255;
const int TiledDisplayTopologyClass::MinBottomBezelSize = 0;
const int TiledDisplayTopologyClass::MaxBottomBezelSize = 255;
const int TiledDisplayTopologyClass::MinRightBezelSize = 0;
const int TiledDisplayTopologyClass::MaxRightBezelSize = 255;
const int TiledDisplayTopologyClass::MinLeftBezelSize = 0;
const int TiledDisplayTopologyClass::MaxLeftBezelSize = 255;
const long long TiledDisplayTopologyClass::MinSerialID = 1;
const long long TiledDisplayTopologyClass::MaxSerialID = 4294967295LL;
//---------------------------------------------------------------------------
TiledDisplayTopologyClass::TiledDisplayTopologyClass(int NewVersion)
{
	Version = NewVersion;
	PhysicalEnclosures = 1;
	SingleTileBehavior = 1;
	MultipleTileBehavior = 1;
	HTiles = 1;
	VTiles = 1;
	HLocation = 1;
	VLocation = 1;
	HSize = BLANK;
	VSize = BLANK;
	PixelMultiplier = 0;
	TopBezelSize = 0;
	BottomBezelSize = 0;
	RightBezelSize = 0;
	LeftBezelSize = 0;
	VendorID[0] = 0;
	ProductID[0] = 0;
	SerialID = DECIMAL_BLANK;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::Read(const unsigned char *Data, int MaxSize)
{
	int Code;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 25)
		return false;

	Code = Data[0];
	Size = Data[2];

	switch (Version)
	{
		case 1:
			if (Code != 18)
				return false;

			break;

		case 2:
			if (Code != 40)
				return false;

			break;

		default:
			return false;
	}

	if (Size < 22)
		return false;

	PhysicalEnclosures = (Data[3] >> 7) & 1;
	SingleTileBehavior = Data[3] & 7;
	MultipleTileBehavior = (Data[3] >> 3) & 3;

	if (SingleTileBehavior > 3)
		SingleTileBehavior = 0;

	if (MultipleTileBehavior > 1)
		MultipleTileBehavior = 0;

	HTiles = ((Data[4] >> 4) & 15) + ((Data[6] >> 2) & 48) + 1;
	VTiles = (Data[4] & 15) + (Data[6] & 48) + 1;
	HLocation = ((Data[5] >> 4) & 15) + ((Data[6] << 2) & 48) + 1;
	VLocation = (Data[5] & 15) + ((Data[6] << 4) & 48) + 1;
	HSize = (Data[8] << 8) + Data[7] + 1;
	VSize = (Data[10] << 8) + Data[9] + 1;
	PixelMultiplier = Data[11];
	TopBezelSize = Data[12];
	BottomBezelSize = Data[13];
	RightBezelSize = Data[14];
	LeftBezelSize = Data[15];
	ReadVendorID(&Data[16]);
	ReadProductID(&Data[19]);
	ReadSerialID(&Data[21]);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ReadVendorID(const unsigned char *Data)
{
	if (Version == 1)
	if (IsUpper(Data[0]))
	if (IsUpper(Data[1]))
	if (IsUpper(Data[2]))
	{
		VendorID[0] = Data[0];
		VendorID[1] = Data[1];
		VendorID[2] = Data[2];
		VendorID[3] = 0;
		return true;
	}

	return DataToHex(Data, 3, VendorID);
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ReadProductID(const unsigned char *Data)
{
	return DataToHex(Data, 2, ProductID, true);
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ReadSerialID(const unsigned char *Data)
{
	SerialID = Data[0];
	SerialID += Data[1] << 8;
	SerialID += Data[2] << 16;
	SerialID += (long long)Data[3] << 24;

	if (SerialID == 0)
		SerialID = DECIMAL_BLANK;

	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 25)
		return false;

	std::memset(Data, 0, MaxSize);

	switch (Version)
	{
		case 1:
			Data[0] = 18;
			break;

		case 2:
			Data[0] = 40;
			break;

		default:
			return false;
	}

	Data[2] = 22;
	Data[3] = ((PhysicalEnclosures & 1) << 7) + (SingleTileBehavior & 7) + ((MultipleTileBehavior & 3) << 3) + (PixelMultiplier ? 64 : 0);
	Data[4] = ((--HTiles & 15) << 4) + (--VTiles & 15);
	Data[5] = ((--HLocation & 15) << 4) + (--VLocation & 15);
	Data[6] = ((HTiles++ & 48) << 2) + (VTiles++ & 48) + ((HLocation++ & 48) >> 2) + ((VLocation++ & 48) >> 4);
	Data[7] = --HSize & 255;
	Data[8] = (HSize++ >> 8) & 255;
	Data[9] = --VSize & 255;
	Data[10] = (VSize++ >> 8) & 255;
	Data[11] = PixelMultiplier & 255;
	Data[12] = TopBezelSize & 255;
	Data[13] = BottomBezelSize & 255;
	Data[14] = RightBezelSize & 255;
	Data[15] = LeftBezelSize & 255;
	WriteVendorID(&Data[16]);
	WriteProductID(&Data[19]);
	WriteSerialID(&Data[21]);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::WriteVendorID(unsigned char *Data)
{
	if (Version == 1)
	if (IsUpper(VendorID[0]))
	if (IsUpper(VendorID[1]))
	if (IsUpper(VendorID[2]))
	if (VendorID[3] == 0)
	{
		if (Data)
		{
			Data[0] = VendorID[0];
			Data[1] = VendorID[1];
			Data[2] = VendorID[2];
		}

		return true;
	}

	return HexToData(VendorID, Data, 3);
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::WriteProductID(unsigned char *Data)
{
	return HexToData(ProductID, Data, 2, true);
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::WriteSerialID(unsigned char *Data)
{
	if (!IsValidSerialID())
		return false;

	if (SerialID == DECIMAL_BLANK)
	{
		Data[0] = 0;
		Data[1] = 0;
		Data[2] = 0;
		Data[3] = 0;
	}
	else
	{
		Data[0] = SerialID & 255;
		Data[1] = (SerialID >> 8) & 255;
		Data[2] = (SerialID >> 16) & 255;
		Data[3] = (SerialID >> 24) & 255;
	}

	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetPhysicalEnclosures()
{
	return PhysicalEnclosures;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetPhysicalEnclosures(int Value)
{
	PhysicalEnclosures = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetSingleTileBehavior()
{
	return SingleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetSingleTileBehavior(int Value)
{
	SingleTileBehavior = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetMultipleTileBehavior()
{
	return MultipleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetMultipleTileBehavior(int Value)
{
	MultipleTileBehavior = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetHTiles()
{
	return HTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetHTiles(int Value)
{
	HTiles = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetVTiles()
{
	return VTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVTiles(int Value)
{
	VTiles = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetHLocation()
{
	return HLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetHLocation(int Value)
{
	HLocation = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetVLocation()
{
	return VLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVLocation(int Value)
{
	VLocation = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetHSize()
{
	return HSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetHSize(int Value)
{
	HSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetVSize()
{
	return VSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVSize(int Value)
{
	VSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetPixelMultiplier()
{
	return PixelMultiplier;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetPixelMultiplier(int Value)
{
	PixelMultiplier = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetTopBezelSize()
{
	return TopBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetTopBezelSize(int Value)
{
	TopBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetBottomBezelSize()
{
	return BottomBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetBottomBezelSize(int Value)
{
	BottomBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetRightBezelSize()
{
	return RightBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetRightBezelSize(int Value)
{
	RightBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetLeftBezelSize()
{
	return LeftBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetLeftBezelSize(int Value)
{
	LeftBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::GetVendorID(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", VendorID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVendorID(const char *NewVendorID)
{
	std::snprintf(VendorID, sizeof VendorID, "%s", NewVendorID);
	Trim(VendorID);
	ToUpper(VendorID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::GetProductID(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", ProductID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetProductID(const char *NewProductID)
{
	std::snprintf(ProductID, sizeof ProductID, "%s", NewProductID);
	Trim(ProductID);
	ToUpper(ProductID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetDeviceID(const char *NewDeviceID)
{
	if (std::strlen(NewDeviceID) != 7)
		return false;

	ReadVendorID((const unsigned char *)NewDeviceID);
	ProductID[0] = NewDeviceID[3];
	ProductID[1] = NewDeviceID[4];
	ProductID[2] = NewDeviceID[5];
	ProductID[3] = NewDeviceID[6];
	ProductID[4] = 0;
	return true;
}
//---------------------------------------------------------------------------
long long TiledDisplayTopologyClass::GetSerialID()
{
	return SerialID;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetSerialID(long long Value)
{
	SerialID = Value;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValid()
{
	if (IsValidPhysicalEnclosures())
	if (IsValidSingleTileBehavior())
	if (IsValidMultipleTileBehavior())
	if (IsValidHTiles())
	if (IsValidVTiles())
	if (IsValidHLocation())
	if (IsValidVLocation())
	if (IsValidHSize())
	if (IsValidVSize())
	if (IsValidPixelMultiplier())
	if (IsValidTopBezelSize())
	if (IsValidBottomBezelSize())
	if (IsValidRightBezelSize())
	if (IsValidLeftBezelSize())
	if (IsValidVendorID())
	if (IsValidProductID())
	if (IsValidSerialID())
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidPhysicalEnclosures()
{
	return PhysicalEnclosures >= MinPhysicalEnclosures && PhysicalEnclosures <= MaxPhysicalEnclosures;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidSingleTileBehavior()
{
	return SingleTileBehavior >= MinSingleTileBehavior && SingleTileBehavior <= MaxSingleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidMultipleTileBehavior()
{
	return MultipleTileBehavior >= MinMultipleTileBehavior && MultipleTileBehavior <= MaxMultipleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidHTiles()
{
	return HTiles >= MinHTiles && HTiles <= MaxHTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVTiles()
{
	return VTiles >= MinVTiles && VTiles <= MaxVTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidHLocation()
{
	return HLocation >= MinHLocation && HLocation <= MaxHLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVLocation()
{
	return VLocation >= MinVLocation && VLocation <= MaxVLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidHSize()
{
	return HSize >= MinHSize && HSize <= MaxHSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVSize()
{
	return VSize >= MinVSize && VSize <= MaxVSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidPixelMultiplier()
{
	return PixelMultiplier >= MinPixelMultiplier && PixelMultiplier <= MaxPixelMultiplier;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidTopBezelSize()
{
	return TopBezelSize >= MinTopBezelSize && TopBezelSize <= MaxTopBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidBottomBezelSize()
{
	return BottomBezelSize >= MinBottomBezelSize && BottomBezelSize <= MaxBottomBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidRightBezelSize()
{
	return RightBezelSize >= MinRightBezelSize && RightBezelSize <= MaxRightBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidLeftBezelSize()
{
	return LeftBezelSize >= MinLeftBezelSize && LeftBezelSize <= MaxLeftBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVendorID()
{
	return WriteVendorID(NULL);
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidProductID()
{
	return WriteProductID(NULL);
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidSerialID()
{
	if (SerialID == DECIMAL_BLANK)
		return true;

	return SerialID >= MinSerialID && SerialID <= MaxSerialID;
}
//---------------------------------------------------------------------------
