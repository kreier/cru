//---------------------------------------------------------------------------
#ifndef DetailedResolutionClassH
#define DetailedResolutionClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
enum
{
	TIMING_MANUAL,
	TIMING_AUTOMATIC_PC,
	TIMING_AUTOMATIC_HDTV,
	TIMING_AUTOMATIC_CRT,
	TIMING_NATIVE_PC,
	TIMING_NATIVE_HDTV,
	TIMING_EXACT,
	TIMING_EXACT_REDUCED,
	TIMING_EXACT_CRT,
	TIMING_CVT_STANDARD,
	TIMING_CVTRB_STANDARD,
	TIMING_CVTRB2_STANDARD,
	TIMING_GTF_STANDARD,
	TIMING_MANUAL_VTOTAL,
};
//---------------------------------------------------------------------------
struct DetailedResolutionStruct
{
	int HActive;
	int VActive;
	bool Interlaced;
	int MinVRate;
	int MaxVRate;
	int HFront;
	int HSync;
	int HBack;
	int VFront;
	int VSync;
	int VBack;
	bool HPolarity;
	bool VPolarity;
};
//---------------------------------------------------------------------------
class DetailedResolutionClass : public ItemClass
{
private:
	static const int MinTiming;
	static const int MaxTiming;
	static const char *TimingText[];

	static bool (DetailedResolutionClass::*TimingFunction[])();
	static const DetailedResolutionStruct AutomaticPC[];
	static const DetailedResolutionStruct AutomaticHDTV[];
	static const DetailedResolutionStruct AutomaticCRT[];
	static const DetailedResolutionStruct Native[];
	static const int AspectVSync[][3];

	static const int C;
	static const int J;
	static const int K;
	static const int M;

	static const int CPrime;
	static const int MPrime;

	static const int MinTimeCVT;
	static const int MinTimeCVTRB;
	static const int MinTimeCVTRB2;
	static const int MinTimeGTF;

	static const int MinHActive[];
	static const int MaxHActive[];
	static const int MinHFront[];
	static const int MaxHFront[];
	static const int MinHSync[];
	static const int MaxHSync[];
	static const int MinHBack[];
	static const int MaxHBlank[];

	static const int MinVActive[];
	static const int MaxVActive[];
	static const int MinVFront[];
	static const int MaxVFront[];
	static const int MinVSync[];
	static const int MaxVSync[];
	static const int MinVBack[];
	static const int MaxVBlank[];

	static const long long MinPClock[];
	static const long long MaxPClock[];
	static const int PClockPrecision[];

	static const bool BordersAvailable[];
	static const bool InterlacedAvailable[];
	static const bool PreferredAvailable[];

	static bool Copied;
	static int CopyType;
	static int CopyHActive;
	static int CopyHFront;
	static int CopyHSync;
	static int CopyHBlank;
	static int CopyVActive;
	static int CopyVFront;
	static int CopyVSync;
	static int CopyVBlank;
	static int CopyHBorder;
	static int CopyVBorder;
	static bool CopyHPolarity;
	static bool CopyVPolarity;
	static int CopyStereo;
	static long long CopyPClock;
	static bool CopyInterlaced;
	static bool CopyPreferred;

	int Type;
	int Timing;
	int Last;
	int HActive;
	int HFront;
	int HSync;
	int HBack;
	int HBlank;
	int HTotal;
	int VActive;
	int VFront;
	int VSync;
	int VBack;
	int VBlank;
	int VTotal;
	int HBorder;
	int VBorder;
	bool HPolarity;
	bool VPolarity;
	int Stereo;
	int LastRate;
	long long VRate;
	long long HRate;
	long long PClock;
	long long ActualVRate;
	long long ActualHRate;
	long long ActualPClock;
	bool Interlaced;
	int Fields;
	bool Preferred;
	int VActiveI;
	int VFrontI;
	int VSyncI;
	int VBackI;
	int VBlankI;
	int VTotalI;
	long long VRateI;

	int ResetHActive;
	int ResetHFront;
	int ResetHSync;
	int ResetHBlank;
	int ResetVActive;
	int ResetVFront;
	int ResetVSync;
	int ResetVBlank;
	int ResetHBorder;
	int ResetVBorder;
	bool ResetHPolarity;
	bool ResetVPolarity;
	int ResetStereo;
	long long ResetPClock;
	bool ResetInterlaced;
	bool ResetPreferred;

public:
	DetailedResolutionClass(int = 0);
	bool Read(const unsigned char *, int);
	bool Init();
	bool Write(unsigned char *, int);
	bool GetText(char *, int, const char *);
	bool SetType(int);
	bool GetTimingText(int, char *, int);
	int GetTiming();
	bool SetTiming(int);
	bool CopyPossible();
	bool Copy();
	bool PasteInterlacedPossible();
	bool PasteStereoPossible();
	bool PastePossible();
	bool Paste();
	bool UpdateReset();
	bool ResetPossible();
	bool Reset();
	bool IsLast(int);
	int GetHActive();
	int GetHFront();
	int GetHSync();
	int GetHBack();
	int GetHBlank();
	int GetHTotal();
	bool Positive(int);
	int GetValue(int);
	int GetVActive();
	int GetVFront();
	int GetVSync();
	int GetVBack();
	int GetVBlank();
	int GetVTotal();
	bool GetHPolarity();
	bool GetVPolarity();
	bool GetVActiveLinesText(char *, int);
	bool GetVFrontLinesText(char *, int);
	bool GetVSyncLinesText(char *, int);
	bool GetVBackLinesText(char *, int);
	bool GetVBlankLinesText(char *, int);
	bool GetVTotalLinesText(char *, int);
	bool IsLastRate(int);
	int GetVRateDigits();
	int GetHRateDigits();
	int GetPClockDigits();
	long long GetVRate();
	long long GetHRate();
	long long GetPClock();
	long long GetActualVRate();
	long long GetActualHRate();
	long long GetActualPClock();
	bool GetActualVRateText(char *, int, const char *);
	bool GetActualHRateText(char *, int, const char *);
	bool GetActualPClockText(char *, int, const char *);
	bool SetLast(int);
	bool SetHActive(int);
	bool SetHFront(int);
	bool SetHSync(int);
	bool SetHBack(int);
	bool SetHBlank(int);
	bool SetHTotal(int);
	bool SetVActive(int);
	bool SetVFront(int);
	bool SetVSync(int);
	bool SetVBack(int);
	bool SetVBlank(int);
	bool SetVTotal(int);
	bool SetHPolarity(bool);
	bool SetVPolarity(bool);
	bool SetLastRate(int);
	bool SetVRate(long long);
	bool SetHRate(long long);
	bool SetPClock(long long);
	bool InterlacedPossible();
	bool GetInterlaced();
	bool SetInterlaced(bool);
	bool PreferredPossible();
	bool GetPreferred();
	bool SetPreferred(bool);
	bool Update();
	bool UpdateInterlaced();
	bool UpdateInterlacedRate();
	bool CalculateManual();
	bool CalculateManualVTotal();
	bool CalculateNative(bool);
	bool CalculateAutomaticPC();
	bool CalculateAutomaticHDTV();
	bool CalculateAutomaticCRT();
	bool CalculateNativePC();
	bool CalculateNativeHDTV();
	bool CalculateExact();
	bool CalculateExactReduced();
	bool CalculateExactCRT();
	bool CalculateCVTStandard();
	bool CalculateCVTRBStandard();
	bool CalculateCVTRB2Standard();
	bool CalculateGTFStandard();
	bool CalculateCVT();
	bool CalculateCVTRB();
	bool CalculateCVTRB2();
	bool CalculateGTF();
	long long GetHPeriodForCVT();
	long long GetHPeriodForCVTRB();
	long long GetHPeriodForCVTRB2();
	long long GetHPeriodForGTF();
	int GetHFrontForCVT();
	int GetHFrontForGTF();
	int GetHSyncForCVT();
	int GetHSyncForGTF();
	int GetHBackForCVT();
	int GetHBackForGTF();
	int GetHBlankForCVT();
	int GetHBlankForGTF();
	int GetVFrontForCVT();
	int GetVFrontForCVTRB();
	int GetVFrontForCVTRB2();
	int GetVFrontForGTF();
	int GetVSyncForCVT();
	int GetVSyncForCVTRB();
	int GetVSyncForCVTRB2();
	int GetVSyncForGTF();
	int GetVBackForCVT();
	int GetVBackForCVTRB();
	int GetVBackForCVTRB2();
	int GetVBackForGTF();
	bool CalculateHBack();
	bool CalculateHBackFromHTotal();
	bool CalculateHBlank();
	bool CalculateHTotal();
	bool CalculateVBack();
	bool CalculateVBackFromVTotal();
	bool CalculateVBlank();
	bool CalculateVTotal();
	bool CalculateVTotalFromFrequencies();
	int GetVRateDivisor();
	int GetHRateDivisor();
	long long GetVRateLimit(int = 0);
	long long GetHRateLimit(int = 0);
	bool CalculateActualVRate();
	bool CalculateActualHRate();
	bool CalculateActualPClockForCVT();
	bool CalculateActualPClockForCVTRB();
	bool CalculateActualPClockForCVTRB2();
	bool CalculateActualPClockForGTF();
	bool CalculateActualPClockFromVRate();
	bool CalculateActualPClockFromHRate();
	bool IsValid();
	bool IsValidTiming();
	bool IsValidHActive();
	bool IsValidHFront();
	bool IsValidHSync();
	bool IsValidHBack();
	bool IsValidHBlank();
	bool IsValidHTotal();
	bool IsValidVActive();
	bool IsValidVFront();
	bool IsValidVSync();
	bool IsValidVBack();
	bool IsValidVBlank();
	bool IsValidVTotal();
	bool IsValidVRate();
	bool IsValidHRate();
	bool IsValidPClock();
	bool IsValidActualPClock();
	bool IsSupported();
	bool IsSupportedHActive();
	bool IsSupportedHFront();
	bool IsSupportedHSync();
	bool IsSupportedHBack();
	bool IsSupportedHBlank();
	bool IsSupportedHTotal();
	bool IsSupportedVActive();
	bool IsSupportedVFront();
	bool IsSupportedVSync();
	bool IsSupportedVBack();
	bool IsSupportedVBlank();
	bool IsSupportedVTotal();
	bool IsSupportedVRate();
	bool IsSupportedHRate();
	bool IsSupportedPClock();
	bool IsSupportedActualPClock();
	int GetMinHBack(int);
	int GetMaxHBack(int);
	int GetMinHBlank(int);
	int GetMaxHBlank(int);
	int GetMinHTotal(int);
	int GetMaxHTotal(int);
	int GetMinVBack(int);
	int GetMaxVBack(int);
	int GetMinVBlank(int);
	int GetMaxVBlank(int);
	int GetMinVTotal(int);
	int GetMaxVTotal(int);
};
//---------------------------------------------------------------------------
#endif
