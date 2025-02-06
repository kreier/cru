//---------------------------------------------------------------------------
#ifndef DIDDetailedResolutionListClassH
#define DIDDetailedResolutionListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
#include "ItemClass.h"
//---------------------------------------------------------------------------
class DIDDetailedResolutionListClass : public ListClass, public ItemClass
{
private:
	int Type;

public:
	DIDDetailedResolutionListClass(int = 1, int = 5);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	int GetType();
};
//---------------------------------------------------------------------------
#endif
