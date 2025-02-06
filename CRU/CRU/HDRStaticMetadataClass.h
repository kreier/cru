//---------------------------------------------------------------------------
#ifndef HDRStaticMetadataClassH
#define HDRStaticMetadataClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class HDRStaticMetadataClass : public ItemClass
{
private:
	static const int MinEOTF;
	static const int MaxEOTF;
	static const int MinType;
	static const int MaxType;
	static const int MinIndex;
	static const int MaxIndex;
	static const int MinLuminance;
	static const int MaxLuminance;

	int MaxDataSize;
	unsigned char Metadata[2];
	int Luminance[3];

public:
	HDRStaticMetadataClass(int = 31);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetEOTF(int);
	bool SetEOTF(int, bool);
	bool GetType(int);
	bool SetType(int, bool);
	bool LuminancePossible(int);
	int GetLuminance(int);
	bool SetLuminance(int, int);
	bool IsValid();
	bool IsValidLuminance(int);
};
//---------------------------------------------------------------------------
#endif
