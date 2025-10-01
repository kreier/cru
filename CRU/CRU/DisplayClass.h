//---------------------------------------------------------------------------
#ifndef DisplayClassH
#define DisplayClassH
//---------------------------------------------------------------------------
#include "PropertiesClass.h"
#include "DetailedResolutionListClass.h"
#include "StandardResolutionListClass.h"
#include "EstablishedResolutionListClass.h"
#include "ExtensionBlockListClass.h"
#include "EDIDListClass.h"
#include "DetailedResolutionClass.h"
//---------------------------------------------------------------------------
class DisplayClass
{
private:
	static unsigned char *CopyData;
	static PropertiesClass CopyProperties;

	unsigned char *ActiveData;
	unsigned char *OverrideData;
	unsigned char *ResetData;

	char *DeviceID;
	char *InstanceID;
	char *DriverName;

	bool Active;
	bool Override;
	bool Matched;
	bool Deleted;
	bool Restart;

	PropertiesClass ActiveProperties;
	PropertiesClass OverrideProperties;
	PropertiesClass ResetProperties;

	DetailedResolutionListClass *DetailedResolutionList;
	StandardResolutionListClass *StandardResolutionList;
	EstablishedResolutionListClass *EstablishedResolutionList;
	ExtensionBlockListClass *ExtensionBlockList;

public:
	DisplayClass();
	bool GetText(char *, int, bool);
	bool Load(const char *, const char *);
	bool MatchCompleteActive(EDIDListClass &);
	bool MatchCompleteOverride(EDIDListClass &);
	bool MatchIncompleteOverride(EDIDListClass &);
	bool MatchIncompleteActive(EDIDListClass &);
	bool Init();
	bool LoadDriverName();
	bool LoadActiveStatus();
	bool LoadOverrideData();
	bool LoadActiveData();
	bool LoadDefaultData();
	bool GetDeviceID(char *, int);
	bool GetInstanceID(char *, int);
	bool GetDriverName(char *, int);
	bool GetActiveStatus();
	bool GetOverrideStatus();
	bool IsValidData(const unsigned char *);
	bool FixData(unsigned char *, bool);
	bool Import(const char *, bool);
	bool ImportFile(std::FILE *, bool, const char *);
	bool ImportINF(std::FILE *, bool);
	bool ImportEXE(std::FILE *, bool);
	static const char *GetImportFormats();
	static const char *GetExportFormats();
	bool Export(const char *, int, const char *);
	bool ExportFile(std::FILE *, int, const char *);
	int Save();
	int SaveActiveData();
	int SaveOverrideData();
	int DeleteData();

	bool GetProperties(PropertiesClass &);
	bool SetProperties(const PropertiesClass &);
	PropertiesClass *Properties();

	bool DisplayInit();
	bool DisplayRead();
	bool DisplayWrite();
	bool DisplayCopyPossible();
	bool DisplayCopy();
	bool DisplayPastePossible();
	bool DisplayPaste();
	bool DisplayDeletePossible();
	bool DisplayDelete();
	bool DisplayRestore();

	bool IsDigital();
	bool GetNative(DetailedResolutionClass &);

	bool DetailedInit();
	bool DetailedRead();
	bool DetailedWrite();
	bool DetailedGetStandardText(int, char *, int);
	DetailedResolutionListClass *DetailedResolutions();

	bool StandardInit();
	bool StandardRead();
	bool StandardWrite();
	StandardResolutionListClass *StandardResolutions();

	bool EstablishedInit();
	bool EstablishedRead();
	bool EstablishedWrite();
	EstablishedResolutionListClass *EstablishedResolutions();

	bool ExtensionInit();
	bool ExtensionRead();
	bool ExtensionWrite();
	ExtensionBlockListClass *ExtensionBlocks();

	bool ClearChecksums();
	bool CalculateChecksums();

	static bool Compare(DisplayClass *, DisplayClass *);
};
//---------------------------------------------------------------------------
#endif
