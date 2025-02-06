/* Includes ***************************************************************/

#include "common.h"
#include "resource.h"
#include "process.h"
#include "registry.h"
#include "winpos.h"

/* Defines ****************************************************************/

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

int ErrorMessage(LPCTSTR text)
{
	MessageBox(NULL, text, _T("Error"), MB_ICONERROR);
	return 1;
}

/**************************************************************************/

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

int RecoverDisplayInstance(BOOL recover, LPCTSTR display, LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%s\\%s\\Device Parameters"), ENUM_DISPLAY, display, instance) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_SET_VALUE, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	if (recover)
	{
		if (RegistryDeleteTree(key, _T("EDID_RECOVERY")) == REGISTRY_ERROR)
			return RegistryCloseKey(key);

		if (RegistryRenameKey(key, L"EDID_OVERRIDE", L"EDID_RECOVERY") == REGISTRY_ERROR)
			return RegistryCloseKey(key);
	}
	else
	{
		if (RegistryDeleteTree(key, _T("EDID_OVERRIDE")) == REGISTRY_ERROR)
			return RegistryCloseKey(key);

		if (RegistryRenameKey(key, L"EDID_RECOVERY", L"EDID_OVERRIDE") == REGISTRY_ERROR)
			return RegistryCloseKey(key);
	}

	return RegistryCloseKey(key);
}

/**************************************************************************/

int RecoverDisplay(BOOL recover, LPCTSTR display)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD index;

	if (_sntprintf(text, TEXTSIZE, _T("%s\\%s"), ENUM_DISPLAY, display) >= TEXTSIZE)
		return RegistrySetStatus(REGISTRY_ERROR);

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, text, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		RecoverDisplayInstance(recover, display, text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int RecoverDisplays(BOOL recover)
{
	HKEY key;
	DWORD index;
	TCHAR text[TEXTSIZE];

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, ENUM_DISPLAY, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		RecoverDisplay(recover, text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

int RecoverIntelInstance(BOOL recover, LPCTSTR instance)
{
	TCHAR text[TEXTSIZE];
	HKEY key;
	DWORD size;
	HKEY recovery_key;
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

	if (recover)
	{
		if (RegistryDeleteTree(key, _T("EDID_RECOVERY")) == REGISTRY_ERROR)
			return RegistryCloseKey(key);

		if (RegistryCreateKey(key, _T("EDID_RECOVERY"), KEY_SET_VALUE, &recovery_key) != REGISTRY_SUCCESS)
			return RegistryCloseKey(key);

		for (index = 0; RegistryEnumValue(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		{
			if (_tcsnicmp(text, _T("FakeEDID_"), 9) != 0)
				continue;

			switch (RegistryCopyValue(key, recovery_key, text))
			{
				case REGISTRY_NOT_FOUND:
					continue;

				case REGISTRY_ERROR:
					return RegistryCloseKeys(recovery_key, key);
			}

			switch (RegistryDeleteValue(key, text))
			{
				case REGISTRY_SUCCESS:
					index--;
					break;

				case REGISTRY_ERROR:
					return RegistryCloseKeys(recovery_key, key);
			}
		}

		if (RegistryCopyValue(key, recovery_key, _T("ReadEDIDFromRegistry")) == REGISTRY_ERROR)
			return RegistryCloseKeys(recovery_key, key);

		RegistryCloseKey(recovery_key);

		if (RegistrySetValue(key, _T("FakeEDID_14_0_af0d_1723"), REG_BINARY, intel_data, sizeof intel_data) != REGISTRY_SUCCESS)
			return RegistryCloseKey(key);

		if (RegistrySetDWORD(key, _T("ReadEDIDFromRegistry"), 1) != REGISTRY_SUCCESS)
			return RegistryCloseKey(key);
	}
	else
	{
		if (RegistryOpenKey(key, _T("EDID_RECOVERY"), KEY_QUERY_VALUE, &recovery_key) != REGISTRY_SUCCESS)
			return RegistryCloseKey(key);

		if (RegistryDeleteValue(key, _T("FakeEDID_14_0_af0d_1723")) == REGISTRY_ERROR)
			return RegistryCloseKeys(recovery_key, key);

		if (RegistryDeleteValue(key, _T("ReadEDIDFromRegistry")) == REGISTRY_ERROR)
			return RegistryCloseKeys(recovery_key, key);

		for (index = 0; RegistryEnumValue(recovery_key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		{
			if (_tcsnicmp(text, _T("FakeEDID_"), 9) != 0)
				continue;

			if (RegistryCopyValue(recovery_key, key, text) == REGISTRY_ERROR)
				return RegistryCloseKeys(recovery_key, key);
		}

		if (RegistryCopyValue(recovery_key, key, _T("ReadEDIDFromRegistry")) == REGISTRY_ERROR)
			return RegistryCloseKeys(recovery_key, key);

		RegistryCloseKey(recovery_key);

		if (RegistryDeleteTree(key, _T("EDID_RECOVERY")) == REGISTRY_ERROR)
			return RegistryCloseKey(key);
	}

	return RegistryCloseKey(key);
}

/**************************************************************************/

int RecoverIntel(BOOL recover)
{
	HKEY key;
	DWORD index;
	TCHAR text[TEXTSIZE];

	if (RegistryOpenKey(HKEY_LOCAL_MACHINE, CONTROL_CLASS, KEY_ENUMERATE_SUB_KEYS, &key) != REGISTRY_SUCCESS)
		return RegistryGetStatus();

	for (index = 0; RegistryEnumKey(key, index, text, TEXTSIZE) == REGISTRY_SUCCESS; index++)
		RecoverIntelInstance(recover, text);

	return RegistryCloseKey(key);
}

/**************************************************************************/

BOOL RefreshNotifyWindow(HWND window)
{
	RECT rect;
	int x, y;

	GetClientRect(window, &rect);

	for (y = 0; y < rect.bottom; y += 4)
		for (x = 0; x < rect.right; x += 4)
			PostMessage(window, WM_MOUSEMOVE, 0, (y << 16) | (x & 65535));

	return TRUE;
}

/**************************************************************************/

BOOL RefreshNotifyIcons()
{
	HWND parent;
	HWND window;

	parent = FindWindow(_T("Shell_TrayWnd"), NULL);

	if (!parent)
		return FALSE;

	parent = FindWindowEx(parent, NULL, _T("TrayNotifyWnd"), NULL);

	if (!parent)
		return FALSE;

	parent = FindWindowEx(parent, NULL, _T("SysPager"), NULL);

	if (!parent)
		return FALSE;

	window = FindWindowEx(parent, NULL, _T("ToolbarWindow32"), _T("Notification Area"));

	if (window)
		RefreshNotifyWindow(window);

	window = FindWindowEx(parent, NULL, _T("ToolbarWindow32"), _T("User Promoted Notification Area"));

	if (window)
		RefreshNotifyWindow(window);

	parent = FindWindow(_T("NotifyIconOverflowWindow"), NULL);

	if (parent)
	{
		window = FindWindowEx(parent, NULL, _T("ToolbarWindow32"), _T("Overflow Notification Area"));

		if (window)
			RefreshNotifyWindow(window);
	}

	return TRUE;
}

/**************************************************************************/

BOOL StopCCC()
{
	KillProcess(_T("MOM.exe"));
	KillProcess(_T("CCC.exe"));
	return TRUE;
}

/**************************************************************************/

BOOL StartCCC()
{
	WCHAR command[] = L"CLI.exe start";
	LPCTSTR program_files;

	program_files = _tgetenv(_T("ProgramFiles(x86)"));

	if (!program_files)
	{
		program_files = _tgetenv(_T("ProgramFiles"));

		if (!program_files)
			return FALSE;
	}

	if (_tchdir(program_files) != 0)
		return FALSE;

	if (_tchdir(_T("AMD\\ATI.ACE\\Core-Static")) != 0)
		if (_tchdir(_T("ATI Technologies\\ATI.ACE\\Core-Static")) != 0)
			return FALSE;

	if (!RunAsUser(command))
		return FALSE;

	return TRUE;
}

/**************************************************************************/

BOOL StopRadeonSettings()
{
	KillProcess(_T("RadeonSoftware.exe"));
	KillProcess(_T("RadeonSettings.exe"));
	KillProcess(_T("cnext.exe"));
	return TRUE;
}

/**************************************************************************/

BOOL StartRadeonSettings()
{
	WCHAR command[] = L"cncmd.exe restart";
	LPCTSTR program_files;

	program_files = _tgetenv(_T("ProgramFiles"));

	if (!program_files)
		return FALSE;

	if (_tchdir(program_files) != 0)
		return FALSE;

	if (_tchdir(_T("AMD\\CNext\\CNext")) != 0)
		return FALSE;

	if (!RunAsUser(command))
		return FALSE;

	return TRUE;
}

/**************************************************************************/

BOOL FixTaskbar()
{
	KillProcess(_T("ShellExperienceHost.exe"));
	KillProcess(_T("SearchUI.exe"));
	return TRUE;
}

/**************************************************************************/

int SetDriverState(DWORD state)
{
	HDEVINFO devices;
	DWORD index;
	SP_DEVINFO_DATA device;
	SP_PROPCHANGE_PARAMS params;
	int result = 0;

	devices = SetupDiGetClassDevs(&GUID_DEVCLASS_DISPLAY, NULL, NULL, DIGCF_PRESENT);

	if (devices == INVALID_HANDLE_VALUE)
		return 0;

	for (index = 0; device.cbSize = sizeof device, SetupDiEnumDeviceInfo(devices, index, &device); index++)
	{
		params.ClassInstallHeader.cbSize = sizeof params.ClassInstallHeader;
		params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
		params.StateChange = state;
		params.Scope = DICS_FLAG_GLOBAL;
		params.HwProfile = 0;

		if (SetupDiSetClassInstallParams(devices, &device, &params.ClassInstallHeader, sizeof params))
			if (SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, devices, &device))
				result++;
	}

	SetupDiDestroyDeviceInfoList(devices);
	return result;
}

/**************************************************************************/

BOOL StopDriver()
{
	SaveWindows();

	if (!SetDriverState(DICS_DISABLE))
		return FALSE;

	StopCCC();
	StopRadeonSettings();
	Sleep(100);
	RefreshNotifyIcons();
	return TRUE;
}

/**************************************************************************/

BOOL StartDriver()
{
	if (!SetDriverState(DICS_ENABLE))
		return FALSE;

	FixTaskbar();
	Sleep(3500);
	RestoreWindows();
	StartRadeonSettings();
	Sleep(100);
	return TRUE;
}

/**************************************************************************/

BOOL RestartDriver()
{
	if (!StopDriver())
		return FALSE;

	if (!StartDriver())
		return FALSE;

	return TRUE;
}

/**************************************************************************/

int FinishRestart()
{
	StartCCC();
	return 0;
}

/**************************************************************************/

BOOL RecoveryMode()
{
	RegistryResetStatus();
	ResetConfiguration();
	ResetConnectivity();
	RecoverDisplays(TRUE);
	RecoverIntel(TRUE);

	if (!RestartDriver())
		return FALSE;

	RecoverDisplays(FALSE);
	RecoverIntel(FALSE);
	return TRUE;
}

/**************************************************************************/

BOOL IsWow64()
{
	BOOL result;

	if (!IsWow64Process(GetCurrentProcess(), &result))
		return FALSE;

	return result;
}

/**************************************************************************/

BOOL WaitForDesktop()
{
	int passes;
	HDESK desktop;

	for (passes = 1;; passes++)
	{
		desktop = OpenInputDesktop(0, FALSE, MAXIMUM_ALLOWED);

		if (desktop)
		{
			CloseDesktop(desktop);
			break;
		}

		if (passes == 20)
			return FALSE;

		Sleep(200);
	}

	return TRUE;
}

/**************************************************************************/

BOOL RestartOnly()
{
	TCHAR path[32768];
	LPTSTR file;

	if (!GetModuleFileName(NULL, path, 32768))
		return FALSE;

	file = _tcsrchr(path, _T('\\'));

	if (!file)
		file = path;

	_tcslwr(file);

	if (_tcsstr(file, _T("-only.")))
		return TRUE;

	return FALSE;
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
				case _T('Q'):
				case _T('q'):
					return IDC_RESTART;

				case _T('R'):
				case _T('r'):
					return IDC_RECOVERY;
			}
		}
	}

	if (RestartOnly())
		return IDC_RESTART;

	return 0;
}

/**************************************************************************/

BOOL Restart64(LPCTSTR cmdLine)
{
	TCHAR command[TEXTSIZE];
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;

	switch (ProcessCommand(cmdLine))
	{
		case IDC_RESTART:
			_tcscpy(command, _T("restart64.exe /q"));
			break;

		case IDC_RECOVERY:
			_tcscpy(command, _T("restart64.exe /r"));
			break;

		default:
			_tcscpy(command, _T("restart64.exe"));
			break;
	}

	GetStartupInfo(&startup_info);

	if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info))
		return FALSE;

	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
	return TRUE;
}

/**************************************************************************/

INT_PTR CALLBACK RestartProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			RegisterHotKey(window, IDC_RECOVERY, 0, VK_F8);
			SetForegroundWindow(window);
			return TRUE;

		case WM_CLOSE:
			UnregisterHotKey(window, 0);
			EndDialog(window, IDC_EXIT);
			return TRUE;

		case WM_HOTKEY:
		case WM_COMMAND:
			if (wParam == IDCANCEL)
				return FALSE;

			UnregisterHotKey(window, 0);
			EndDialog(window, wParam);
			return TRUE;
	}

	return FALSE;
}

/**************************************************************************/

INT_PTR CALLBACK RecoveryProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			SetForegroundWindow(window);
			return TRUE;

		case WM_CLOSE:
			EndDialog(window, IDC_EXIT);
			return TRUE;

		case WM_COMMAND:
			if (wParam == IDCANCEL)
				return FALSE;

			EndDialog(window, wParam);
			return TRUE;
	}

	return FALSE;
}

/* Main *******************************************************************/

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR cmdLine, int cmdShow)
{
	const TCHAR error[] = _T("Failed to restart graphics driver.");

	if (IsWow64())
	{
		if (!Restart64(cmdLine))
			return ErrorMessage(_T("Failed to load restart64.exe."));

		return 0;
	}

	WaitForDesktop();

	switch (ProcessCommand(cmdLine))
	{
		case IDC_RESTART:
			if (!RestartDriver())
				return ErrorMessage(error);

			return FinishRestart();

		case IDC_RECOVERY:
			if (!RecoveryMode())
				return ErrorMessage(error);

			return FinishRestart();
	}

	if (!RestartDriver())
		return ErrorMessage(error);

	for (;;)
	{
		switch (DialogBox(instance, _T("IDD_RESTART"), NULL, RestartProc))
		{
			case IDC_RESTART:
				if (!RestartDriver())
					return ErrorMessage(error);

				break;

			case IDC_RECOVERY:
				if (!RecoveryMode())
					return ErrorMessage(error);

				if (DialogBox(instance, _T("IDD_RECOVERY"), NULL, RecoveryProc) == IDC_EXIT)
					return FinishRestart();

				if (!RestartDriver())
					return ErrorMessage(error);

				break;

			case IDC_EXIT:
				return FinishRestart();
		}
	}
}

/**************************************************************************/
