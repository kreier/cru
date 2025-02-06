//---------------------------------------------------------------------------
#ifndef HDMIResolutionListClassH
#define HDMIResolutionListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
//---------------------------------------------------------------------------
class HDMIResolutionListClass : public ListClass
{
public:
	HDMIResolutionListClass(int = 7);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
};
//---------------------------------------------------------------------------
#endif
