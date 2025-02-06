//---------------------------------------------------------------------------
#ifndef PropertiesClassH
#define PropertiesClassH
//---------------------------------------------------------------------------
class PropertiesClass
{
private:
	static const char *ColorDepthText[];
	static const int MinColorDepth;
	static const int MaxColorDepth;

	static const long long MinSerialID;
	static const long long MaxSerialID;

	static const unsigned long MaxNameSize;
	static const unsigned long MaxSerialNumberSize;

	static const int MinVRange;
	static const int MaxVRange;
	static const int MinHRange;
	static const int MaxHRange;
	static const int MinPClockRange;
	static const int MaxPClockRange;
	static const int ModPClockRange;

	static const char *RegName;
	static const char *RegSerialNumber;
	static const char *RegRangeLimits;
	static const char *RegExtensions;

	int Version;

	char DeviceID[8];
	char ResetID[8];
	long long SerialID;

	bool Digital;

	int ColorDepth;
	bool YCbCr422;
	bool YCbCr444;

	char Name[14];
	bool IncludeName;
	bool IncludedName;

	char SerialNumber[14];
	bool IncludeSerialNumber;
	bool IncludedSerialNumber;

	int ExtRange;
	int MinVRate;
	int MaxVRate;
	int MinHRate;
	int MaxHRate;
	int MaxPClock;
	bool IncludeRangeLimits;
	bool IncludedRangeLimits;

	int Extensions;

public:
	PropertiesClass();
	bool operator==(const PropertiesClass &);
	bool operator!=(const PropertiesClass &);
	bool Read(const unsigned char *, bool);
	bool ReadVersion(const unsigned char *);
	bool ReadDeviceID(const unsigned char *);
	bool ReadSerialID(const unsigned char *);
	bool ReadDigital(const unsigned char *);
	bool ReadColorFormats(const unsigned char *);
	bool ReadName(const unsigned char *, bool);
	bool ReadSerialNumber(const unsigned char *, bool);
	bool ReadRangeLimits(const unsigned char *, bool);
	bool ReadExtensions(const unsigned char *);
	bool Write(unsigned char *);
	bool WriteResetID(unsigned char *);
	bool WriteDeviceID(unsigned char *);
	bool WriteSerialID(unsigned char *);
	bool WriteColorFormats(unsigned char *);
	bool WriteName(unsigned char *);
	bool WriteSerialNumber(unsigned char *);
	bool WriteRangeLimits(unsigned char *);
	bool LoadBackupData(HKEY);
	bool LoadOldBackupName(HKEY);
	bool LoadBackupName(HKEY);
	bool LoadBackupSerialNumber(HKEY);
	bool LoadBackupRangeLimits(HKEY);
	bool LoadBackupExtensions(HKEY);
	bool SaveBackupData(HKEY, int);
	bool SaveOldBackupName(HKEY, int);
	bool SaveBackupName(HKEY);
	bool SaveBackupSerialNumber(HKEY);
	bool SaveBackupRangeLimits(HKEY);
	bool SaveBackupExtensions(HKEY);
	bool CopyPastePossible(PropertiesClass);
	bool CopyPossible(PropertiesClass);
	bool PastePossible(PropertiesClass);
	bool Paste(PropertiesClass);
	bool Import(PropertiesClass);
	bool PasteImport(PropertiesClass);
	bool ResetIncludes();
	bool FixIncludes(int);
	int GetCount();
	bool GetText(int, char *, int);
	bool GetDeviceID(char *, int);
	bool SetDeviceID(const char *);
	bool SetResetID(const char *);
	bool ResetDeviceIDPossible();
	bool ResetDeviceID();
	long long GetSerialID();
	bool SetSerialID(long long);
	bool ColorFormatsSupported();
	bool GetColorDepthText(int, char *, int);
	int GetColorDepth();
	bool SetColorDepth(int);
	bool GetYCbCr422();
	bool SetYCbCr422(bool);
	bool GetYCbCr444();
	bool SetYCbCr444(bool);
	bool GetNameText(char *, int);
	bool GetName(char *, int);
	bool SetName(const char *);
	bool GetIncludeName();
	bool SetIncludeName(bool);
	bool GetSerialNumberText(char *, int);
	bool GetSerialNumber(char *, int);
	bool SetSerialNumber(const char *);
	bool GetIncludeSerialNumber();
	bool SetIncludeSerialNumber(bool);
	bool GetRangeLimitsText(char *, int);
	int GetExtRange();
	int GetMinVRate();
	bool SetMinVRate(int);
	int GetMaxVRate();
	bool SetMaxVRate(int);
	int GetMinHRate();
	bool SetMinHRate(int);
	int GetMaxHRate();
	bool SetMaxHRate(int);
	int GetMaxPClock();
	bool SetMaxPClock(int);
	bool GetIncludeRangeLimits();
	bool SetIncludeRangeLimits(bool);
	int GetExtensions();
	bool IsValid();
	bool IsResetID();
	bool IsDeviceID();
	bool IsValidDeviceID();
	bool IsValidSerialID();
	bool IsValidName();
	bool IsValidSerialNumber();
	bool IsValidMinVRate();
	bool IsValidMaxVRate();
	bool IsValidMinHRate();
	bool IsValidMaxHRate();
	bool IsValidMaxPClock();
	bool IsBlankRangeLimits();
	bool IsValidRangeLimits();
};
//---------------------------------------------------------------------------
#endif
