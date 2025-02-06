//---------------------------------------------------------------------------
#ifndef DisplayListClassH
#define DisplayListClassH
//---------------------------------------------------------------------------
#include "DisplayClass.h"
//---------------------------------------------------------------------------
class DisplayListClass
{
private:
	std::vector<DisplayClass *> Items;
	int Count;
	int ItemIndex;

public:
	DisplayListClass();
	bool Load();
	bool LoadDisplays();
	bool LoadDisplay(const char *);
	bool LoadInstance(const char *, const char *);
	bool Save();
	int GetCount();
	bool GetItemText(int, char *, int);
	DisplayClass *Get(int);
};
//---------------------------------------------------------------------------
#endif
