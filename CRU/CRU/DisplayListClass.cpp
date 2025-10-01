//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "DisplayListClass.h"
#include "EDIDListClass.h"
#include "AMDDisplayClass.h"
#include "NVIDIADisplayClass.h"
//---------------------------------------------------------------------------
DisplayListClass::DisplayListClass()
{
	Count = 0;
	ItemIndex = -1;
}
//---------------------------------------------------------------------------
bool DisplayListClass::Load()
{
	int Index;

	if (!LoadDisplays())
		return false;

	if (Count == 0)
		return true;

	EDIDListClass EDIDList;
	AMDDisplayClass AMDDisplay;
	AMDDisplay.LoadEDIDList(EDIDList);
	NVIDIADisplayClass NVIDIADisplay;
	NVIDIADisplay.LoadEDIDList(EDIDList);

	if (EDIDList.GetCount() > 0)
	{
		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchCompleteActive(EDIDList);

		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchCompleteOverride(EDIDList);

		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchIncompleteOverride(EDIDList);

		for (Index = 0; Index < Count; Index++)
			Items[Index]->MatchIncompleteActive(EDIDList);
	}

	for (Index = 0; Index < Count; Index++)
		Items[Index]->Init();

	std::sort(Items.begin(), Items.end(), DisplayClass::Compare);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::LoadDisplays()
{
	HKEY Key;
	char DeviceID[TEXTSIZE];
	unsigned long TextSize;
	int Index;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY", 0, KEY_ENUMERATE_SUB_KEYS, &Key) != ERROR_SUCCESS)
		return false;

	for (Index = 0; TextSize = TEXTSIZE, RegEnumKeyEx(Key, Index, DeviceID, &TextSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; Index++)
		LoadDisplay(DeviceID);

	RegCloseKey(Key);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::LoadDisplay(const char *DeviceID)
{
	HKEY Key;
	char Path[TEXTSIZE];
	char InstanceID[TEXTSIZE];
	unsigned long TextSize;
	int Index;

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s", DeviceID) >= TEXTSIZE)
		return false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_ENUMERATE_SUB_KEYS, &Key) != ERROR_SUCCESS)
		return false;

	for (Index = 0; TextSize = TEXTSIZE, RegEnumKeyEx(Key, Index, InstanceID, &TextSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; Index++)
		LoadInstance(DeviceID, InstanceID);

	RegCloseKey(Key);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::LoadInstance(const char *DeviceID, const char *InstanceID)
{
	DisplayClass *NewDisplay = new DisplayClass;

	if (!NewDisplay->Load(DeviceID, InstanceID))
	{
		delete NewDisplay;
		return false;
	}

	Items.push_back(NewDisplay);
	Count++;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayListClass::Save()
{
	int Index;
	int Result = 0;

	for (Index = 0; Index < Count; Index++)
		Result |= Items[Index]->Save();

	if (Result & 1)
		for (Index = 0; Index < Count; Index++)
			Result |= Items[Index]->SaveActiveData();

	if (Result < 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
int DisplayListClass::GetCount()
{
	return Count;
}
//---------------------------------------------------------------------------
bool DisplayListClass::GetItemText(int Index, char *Text, int TextSize)
{
	if (Index < 0 || Index >= Count)
		return false;

	Items[Index]->GetText(Text, TextSize, true);
	return true;
}
//---------------------------------------------------------------------------
DisplayClass *DisplayListClass::Get(int Index)
{
	if (Index < 0 || Index >= Count)
		return NULL;

	return Items[Index];
}
//---------------------------------------------------------------------------
