/* Includes ***************************************************************/

#include "common.h"
#include "registry.h"

/* Defines ****************************************************************/

#define RESET_TITLE				_T("Reset All 1.4")
#define RESET_MESSAGE			_T("Reset all displays and delete inactive entries?")

#define RESTART_MESSAGE			_T("\nRun restart.exe or reboot to redetect displays.")
#define ADMIN_MESSAGE			_T("\nTry running as administrator.")

#define RESET_SUCCESS			_T("Displays reset successfully.") RESTART_MESSAGE
#define RESET_NOT_FOUND			_T("Displays have already been reset.") RESTART_MESSAGE
#define RESET_INCOMPLETE		_T("Failed to reset some displays.") RESTART_MESSAGE
#define RESET_ERROR				_T("Failed to reset displays.") ADMIN_MESSAGE

#define UNKNOWN_ERROR			_T("Unknown error.")

#define ENUM_DISPLAY			_T("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY")
#define CONTROL_CLASS			_T("SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}")
#define CONTROL_GRAPHICS		_T("SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers")

/* Constants **************************************************************/

// Default FakeEDID_14_0_af0d_1723
const unsigned char intel_data[] =
{
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x0D, 0xAF, 0x23, 0x17, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x15, 0x01, 0x04, 0x95, 0x26, 0x15, 0x78, 0x02, 0xD1, 0xF5, 0x93, 0x5D, 0x59, 0x90, 0x26,
	0x1D, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1D, 0x36, 0x80, 0xA0, 0x70, 0x38, 0x1E, 0x40, 0x2E, 0x1E,
	0x24, 0x00, 0x7E, 0xD7, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x05, 0x00, 0x74, 0x8B, 0x80,
	0x50, 0x70, 0x38, 0x97, 0x41, 0x08, 0x40, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x43,
	0x4D, 0x49, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFE,
	0x00, 0x4E, 0x31, 0x37, 0x33, 0x48, 0x48, 0x46, 0x2D, 0x45, 0x32, 0x31, 0x20, 0x20, 0x00, 0x39
};

/* Functions **************************************************************/

int ResetConfiguration()
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD index;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\Configuration"), CONTROL_GRAPHICS) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		if (RegistryDeleteTree(key, text) == REGISTRY_SUCCESS)
			index--;

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetConnectivity()
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD index;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\Connectivity"), CONTROL_GRAPHICS) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		if (RegistryDeleteTree(key, text) == REGISTRY_SUCCESS)
			index--;

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetDisplayInstance(LPCTSTR display, LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%s\\%s\\Device Parameters"), ENUM_DISPLAY, display, instance) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_SET_VALUE, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	if (RegistryDeleteTree(key, _T("EDID_OVERRIDE")) == REGISTRY_ERROR)
		return RegistryCloseKey(key);

	if (RegistryDeleteValue(key, _T("EDID")) == REGISTRY_ERROR)
		return RegistryCloseKey(key);

	if (RegistryDeleteTree(key, _T("EDID_RECOVERY")) == REGISTRY_ERROR)
		return RegistryCloseKey(key);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetDisplay(LPCTSTR display)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD index;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%s"), ENUM_DISPLAY, display) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		ResetDisplayInstance(display, text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetDisplays()
{
	HKEY key;
	DWORD index;
	TCHAR text[TEXTSIZE];

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, ENUM_DISPLAY, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		ResetDisplay(text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetIntelInstance(LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD size;
	DWORD index;

	if (_tcslen(instance) != 4)
		return RegistryGetStatus();

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%s"), CONTROL_CLASS, instance) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_QUERY_VALUE | KEY_SET_VALUE, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	size = sizeof text;

	if (RegistryQueryValue(key, _T("ProviderName"), NULL, (LPBYTE)text, &size) != REGISTRY_SUCCESS)
		return RegistryCloseKey(key);

	if (size < 5 || _tcsnicmp(text, _T("Intel"), 5) != 0)
		return RegistryCloseKey(key);

	for (index = 0; RegistryEnumValue(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
	{
		if (_tcsnicmp(text, _T("FakeEDID_"), 9) != 0)
			continue;

		if (_tcsicmp(text, _T("FakeEDID_14_0_af0d_1723")) == 0)
			continue;

		switch (RegistryDeleteValue(key, text))
		{
			case REGISTRY_SUCCESS:
				index--;
				break;

			case REGISTRY_ERROR:
				return RegistryCloseKey(key);
		}
	}

	if (RegistryResetValue(key, _T("FakeEDID_14_0_af0d_1723"), REG_BINARY, intel_data, sizeof intel_data) != REGISTRY_SUCCESS)
		return RegistryCloseKey(key);

	if (RegistryResetDWORD(key, _T("ReadEDIDFromRegistry"), 1) != REGISTRY_SUCCESS)
		return RegistryCloseKey(key);

	if (RegistryDeleteTree(key, _T("EDID_RECOVERY")) == REGISTRY_ERROR)
		return RegistryCloseKey(key);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetIntel()
{
	HKEY key;
	DWORD index;
	TCHAR text[TEXTSIZE];

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, CONTROL_CLASS, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		ResetIntelInstance(text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetAll(BOOL prompt)
{
	RegistryResetStatus();
	ResetConfiguration();
	ResetConnectivity();
	ResetDisplays();
	ResetIntel();

	switch (RegistryGetStatus())
	{
		case REGISTRY_SUCCESS:
			if (prompt)
				MessageBox(NULL, RESET_SUCCESS, RESET_TITLE, MB_ICONINFORMATION);

			return 0;

		case REGISTRY_NOT_FOUND:
			if (prompt)
				MessageBox(NULL, RESET_NOT_FOUND, RESET_TITLE, MB_ICONINFORMATION);

			return 0;

		case REGISTRY_INCOMPLETE:
			MessageBox(NULL, RESET_INCOMPLETE, RESET_TITLE, MB_ICONERROR);
			return 1;

		case REGISTRY_ERROR:
			MessageBox(NULL, RESET_ERROR, RESET_TITLE, MB_ICONERROR);
			return 1;
	}

	MessageBox(NULL, UNKNOWN_ERROR, RESET_TITLE, MB_ICONERROR);
	return 1;
}

/**************************************************************************/

BOOL ProcessCommand(LPCTSTR cmdLine)
{
	if (cmdLine[0] == _T('-') || cmdLine[0] == _T('/'))
	{
		if (cmdLine[2] == 0)
		{
			switch (cmdLine[1])
			{
				case _T('Q'):
				case _T('q'):
					return TRUE;
			}
		}
	}

	return FALSE;
}

/* Main *******************************************************************/

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR cmdLine, int cmdShow)
{
	if (ProcessCommand(cmdLine))
		return ResetAll(FALSE);

	if (MessageBox(NULL, RESET_MESSAGE, RESET_TITLE, MB_YESNO | MB_ICONQUESTION) == IDYES)
		return ResetAll(TRUE);

	return 0;
}

/**************************************************************************/
