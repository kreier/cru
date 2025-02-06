//---------------------------------------------------------------------------
#ifndef ColorimetryClassH
#define ColorimetryClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class ColorimetryClass : public ItemClass
{
private:
	unsigned char ColorimetryData[30];
	int ColorimetrySize;

public:
	ColorimetryClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool Get(int);
	bool Set(int, bool);
};
//---------------------------------------------------------------------------
#endif
