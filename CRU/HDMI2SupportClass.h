//---------------------------------------------------------------------------
#ifndef HDMI2SupportClassH
#define HDMI2SupportClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class HDMI2SupportClass : public ItemClass
{
private:
	static const char *FRLRateText[];
	static const char *DSCSlicesText[];
	static const int MinTMDSRate;
	static const int MaxTMDSRate;
	static const int ModTMDSRate;
	static const int FeaturesMask;
	static const int MinColorFormat;
	static const int MaxColorFormat;
	static const int MinFRLRate;
	static const int MaxFRLRate;
	static const int Features21Mask;
	static const int MinMinRefreshRate;
	static const int MaxMinRefreshRate;
	static const int MinMaxRefreshRate;
	static const int MaxMaxRefreshRate;
	static const int DSCFeaturesMask;
	static const int MinDSCSlices;
	static const int MaxDSCSlices;
	static const int MinDSCChunkSize;
	static const int MaxDSCChunkSize;

	int MaxDataSize;
	int Version;
	bool OverrideTMDSRate;
	int TMDSRate;
	int Features[3];
	int MinRefreshRate;
	int MaxRefreshRate;
	int DSCFeatures[2];
	int DSCChunkSize;
	int OtherSize;
	int MaxOtherSize;
	unsigned char OtherData[18];

public:
	HDMI2SupportClass(int = 31);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetOverrideTMDSRate();
	bool SetOverrideTMDSRate(bool);
	int GetTMDSRate();
	bool SetTMDSRate(int);
	bool GetFeature(int);
	bool SetFeature(int, bool);
	bool GetColorFormat(int);
	bool SetColorFormat(int, bool);
	bool GetFRLRateText(int, char *, int);
	int GetFRLRate();
	bool SetFRLRate(int);
	bool Features21Possible();
	bool GetFeature21(int);
	bool SetFeature21(int, bool);
	bool RefreshRatePossible();
	int GetMinRefreshRate();
	bool SetMinRefreshRate(int);
	int GetMaxRefreshRate();
	bool SetMaxRefreshRate(int);
	bool DSCPossible();
	bool GetDSCFeature(int);
	bool SetDSCFeature(int, bool);
	int GetDSCFRLRate();
	bool SetDSCFRLRate(int);
	bool GetDSCSlicesText(int, char *, int);
	int GetDSCSlices();
	bool SetDSCSlices(int);
	int GetDSCChunkSize();
	bool SetDSCChunkSize(int);
	bool IsValid();
	bool IsValidTMDSRate();
	bool IsValidRefreshRate();
	bool IsValidMinRefreshRate();
	bool IsValidMaxRefreshRate();
	bool IsValidDSCChunkSize();
};
//---------------------------------------------------------------------------
#endif
