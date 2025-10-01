//---------------------------------------------------------------------------
#ifndef FreeSyncRangeClassH
#define FreeSyncRangeClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class FreeSyncRangeClass : public ItemClass
{
private:
	static const int MinVRange;
	static const int MaxVRange[];

	int MinVRate;
	int MaxVRate;
	int Version;
	int Flags;
	int OtherSize;
	int MaxOtherSize;
	unsigned char OtherData[24];

public:
	FreeSyncRangeClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	int GetMinVRate();
	bool SetMinVRate(int);
	int GetMaxVRate();
	bool SetMaxVRate(int);
	bool IsValid();
	bool IsValidMinVRate();
	bool IsValidMaxVRate();
};
//---------------------------------------------------------------------------
#endif
