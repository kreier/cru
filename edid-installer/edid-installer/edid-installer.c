/* Includes ***************************************************************/

#include "common.h"
#include "resource.h"
#include "registry.h"

/* Defines ****************************************************************/

#define RESTART_MESSAGE			_T("\nRun restart.exe or reboot to redetect displays.")
#define ADMIN_MESSAGE			_T("\nTry running as administrator.")

#define DISPLAY_NOT_FOUND		_T("No matching displays found.")
#define DISPLAY_ERROR			_T("Failed to open the registry.") ADMIN_MESSAGE

#define INSTALL_SUCCESS			_T("EDID installed successfully.") RESTART_MESSAGE
#define INSTALL_NOT_FOUND		_T("No matching displays found.")
#define INSTALL_INCOMPLETE		_T("Failed to install EDID on some displays.") RESTART_MESSAGE
#define INSTALL_ERROR			_T("Failed to install EDID.") ADMIN_MESSAGE

#define RESET_SUCCESS			_T("EDID reset successfully.") RESTART_MESSAGE
#define RESET_NOT_FOUND			_T("EDID has already been reset.") RESTART_MESSAGE
#define RESET_INCOMPLETE		_T("Failed to reset EDID on some displays.") RESTART_MESSAGE
#define RESET_ERROR				_T("Failed to reset EDID.") ADMIN_MESSAGE

#define UNKNOWN_ERROR			_T("Unknown error.")

#define ENUM_DISPLAY			_T("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY")
#define CONTROL_CLASS			_T("SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}")

#define INTEL_OUTPUTS			20
#define EDID_BLOCKS				4
#define EDID_BLOCKSIZE			128

/* Constants **************************************************************/

const char display[16] = "CRU1234";    // [16] for "Default_Monitor"
const volatile unsigned char id[8] = {0x0E, 0x55, 0x34, 0x12};    // [8] for alignment
const unsigned char magic[] = {0x71, 0x42, 0x12, 0x83, 0x54, 0x24, 0x95, 0x66};    // CRU import

const unsigned char data[EDID_BLOCKS * EDID_BLOCKSIZE] =
{
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x0E, 0x55, 0x34, 0x12, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
	0x45, 0x00, 0xE0, 0x0E, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x54, 0x6F, 0x61,
	0x73, 0x74, 0x79, 0x21, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E
};

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

/* Enums ******************************************************************/

enum action
{
	EXISTS,
	INSTALL,
	RESET,
};

/* Functions **************************************************************/

int InstallDisplayInstance(LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	int block;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%hs\\%s\\Device Parameters\\EDID_OVERRIDE"), ENUM_DISPLAY, display, instance) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryCreateKey(HKEY_LOCAL_MACHINE, text, KEY_SET_VALUE, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (block = 0; block < EDID_BLOCKS; block++)
	{
		if (_sntprintf(text, TEXTSIZE, _T("%d"), block) >= TEXTSIZE)
		{
			RegistrySetStatus(REGISTRY_ERROR);
			return RegistryCloseKey(key);
		}

		if (block == 0 || data[block * EDID_BLOCKSIZE] != 0)
		{
			if (RegistrySetValue(key, text, REG_BINARY, &data[block * EDID_BLOCKSIZE], EDID_BLOCKSIZE) != REGISTRY_SUCCESS)
				return RegistryCloseKey(key);
		}
		else
		{
			if (RegistryDeleteValue(key, text) == REGISTRY_ERROR)
				return RegistryCloseKey(key);
		}
	}

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ResetDisplayInstance(LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%hs\\%s\\Device Parameters"), ENUM_DISPLAY, display, instance) >= TEXTSIZE)
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

int ProcessDisplay(enum action action)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD index;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%hs"), ENUM_DISPLAY, display) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	switch (action)
	{
		case EXISTS:
			if (RegistryEnumKey(key, 0, text, TEXTSIZE) == REGISTRY_SUCCESS)
				RegistrySetStatus(REGISTRY_SUCCESS);

			break;

		case INSTALL:
			for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
				InstallDisplayInstance(text);

			break;

		case RESET:
			for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
				ResetDisplayInstance(text);

			break;
	}

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ProcessIntelInstance(enum action action, LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD size;
	int output;
	int block;

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

	switch (action)
	{
		case INSTALL:
			for (output = 0; output < INTEL_OUTPUTS; output++)
			{
				for (block = 0; block < EDID_BLOCKS; block++)
				{
					if (_sntprintf(text, TEXTSIZE, _T("FakeEDID_%d_%d_%x_%x"), output, block, id[1] << 8 | id[0], id[3] << 8 | id[2]) >= TEXTSIZE)
					{
						RegistrySetStatus(REGISTRY_ERROR);
						return RegistryCloseKey(key);
					}

					if (block == 0 || data[block * EDID_BLOCKSIZE] != 0)
					{
						if (RegistrySetValue(key, text, REG_BINARY, &data[block * EDID_BLOCKSIZE], EDID_BLOCKSIZE) != REGISTRY_SUCCESS)
							return RegistryCloseKey(key);
					}
					else
					{
						if (RegistryDeleteValue(key, text) == REGISTRY_ERROR)
							return RegistryCloseKey(key);
					}
				}
			}

			if (RegistrySetDWORD(key, _T("ReadEDIDFromRegistry"), 1) != REGISTRY_SUCCESS)
				return RegistryCloseKey(key);

			break;

		case RESET:
			for (output = 0; output < INTEL_OUTPUTS; output++)
			{
				for (block = 0; block < EDID_BLOCKS; block++)
				{
					if (_sntprintf(text, TEXTSIZE, _T("FakeEDID_%d_%d_%x_%x"), output, block, id[1] << 8 | id[0], id[3] << 8 | id[2]) >= TEXTSIZE)
					{
						RegistrySetStatus(REGISTRY_ERROR);
						return RegistryCloseKey(key);
					}

					if (_tcsicmp(text, _T("FakeEDID_14_0_af0d_1723")) == 0)
					{
						if (RegistryResetValue(key, _T("FakeEDID_14_0_af0d_1723"), REG_BINARY, intel_data, sizeof intel_data) != REGISTRY_SUCCESS)
							return RegistryCloseKey(key);
					}
					else
					{
						if (RegistryDeleteValue(key, text) == REGISTRY_ERROR)
							return RegistryCloseKey(key);
					}
				}
			}

			break;
	}

	if (RegistryDeleteTree(key, _T("EDID_RECOVERY")) == REGISTRY_ERROR)
		return RegistryCloseKey(key);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int ProcessIntel(enum action action)
{
	HKEY key;
	DWORD index;
	TCHAR text[TEXTSIZE];

	if (strcmp(display, "Default_Monitor") == 0)
		return RegistryGetStatus();

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, CONTROL_CLASS, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		ProcessIntelInstance(action, text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

BOOL DisplayExists()
{
	RegistryResetStatus();
	ProcessDisplay(EXISTS);

	switch (RegistryGetStatus())
	{
		case REGISTRY_SUCCESS:
			return TRUE;

		case REGISTRY_NOT_FOUND:
			MessageBox(NULL, DISPLAY_NOT_FOUND, TITLE, MB_ICONERROR);
			return FALSE;

		case REGISTRY_ERROR:
			MessageBox(NULL, DISPLAY_ERROR, TITLE, MB_ICONERROR);
			return FALSE;
	}

	MessageBox(NULL, UNKNOWN_ERROR, TITLE, MB_ICONERROR);
	return FALSE;
}

/**************************************************************************/

int InstallEDID(BOOL prompt)
{
	RegistryResetStatus();
	ProcessDisplay(INSTALL);
	ProcessIntel(INSTALL);

	switch (RegistryGetStatus())
	{
		case REGISTRY_SUCCESS:
			if (prompt)
				MessageBox(NULL, INSTALL_SUCCESS, INSTALL_TITLE, MB_ICONINFORMATION);

			return 0;

		case REGISTRY_NOT_FOUND:
			MessageBox(NULL, INSTALL_NOT_FOUND, INSTALL_TITLE, MB_ICONERROR);
			return 1;

		case REGISTRY_INCOMPLETE:
			MessageBox(NULL, INSTALL_INCOMPLETE, INSTALL_TITLE, MB_ICONERROR);
			return 1;

		case REGISTRY_ERROR:
			MessageBox(NULL, INSTALL_ERROR, INSTALL_TITLE, MB_ICONERROR);
			return 1;
	}

	MessageBox(NULL, UNKNOWN_ERROR, INSTALL_TITLE, MB_ICONERROR);
	return 1;
}

/**************************************************************************/

int ResetEDID(BOOL prompt)
{
	RegistryResetStatus();
	ProcessDisplay(RESET);
	ProcessIntel(RESET);

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

int ProcessCommand(LPCTSTR cmdLine)
{
	if (cmdLine[0] == _T('-') || cmdLine[0] == _T('/'))
	{
		if (cmdLine[2] == 0)
		{
			switch (cmdLine[1])
			{
				case _T('I'):
				case _T('i'):
					return IDC_INSTALL;

				case _T('R'):
				case _T('r'):
					return IDC_RESET;
			}
		}
	}

	return 0;
}

/**************************************************************************/

INT_PTR CALLBACK DialogProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
			EndDialog(window, wParam);
			return TRUE;
	}

	return FALSE;
}

/* Main *******************************************************************/

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR cmdLine, int cmdShow)
{
	if (!DisplayExists())
		return 1;

	switch (ProcessCommand(cmdLine))
	{
		case IDC_INSTALL:
			return InstallEDID(FALSE);

		case IDC_RESET:
			return ResetEDID(FALSE);
	}

	switch (DialogBox(instance, _T("IDD_DIALOG"), NULL, DialogProc))
	{
		case IDC_INSTALL:
			return InstallEDID(TRUE);

		case IDC_RESET:
			return ResetEDID(TRUE);
	}

	return 0;
}

/**************************************************************************/
