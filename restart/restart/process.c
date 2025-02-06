/* Includes ***************************************************************/

#include "process.h"

/* Functions **************************************************************/

int KillProcess(LPCTSTR name)
{
	HANDLE processes;
	PROCESSENTRY32 process_entry;
	HANDLE process;
	int result = 0;

	processes = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (processes == INVALID_HANDLE_VALUE)
		return 0;

	process_entry.dwSize = sizeof process_entry;

	if (Process32First(processes, &process_entry))
	{
		do
		{
			if (_tcsicmp(process_entry.szExeFile, name) == 0)
			{
				process = OpenProcess(PROCESS_TERMINATE, FALSE, process_entry.th32ProcessID);

				if (process)
				{
					TerminateProcess(process, 0);
					CloseHandle(process);
					result++;
				}
			}
		}
		while (Process32Next(processes, &process_entry));
	}

	CloseHandle(processes);
	return result;
}

/**************************************************************************/

static BOOL SetProcessTokenPrivilege(LPCTSTR name, DWORD attributes)
{
	TOKEN_PRIVILEGES token_privileges;
	HANDLE process_token;

	token_privileges.PrivilegeCount = 1;
	token_privileges.Privileges[0].Attributes = attributes;

	if (!LookupPrivilegeValue(NULL, name, &token_privileges.Privileges[0].Luid))
		return FALSE;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &process_token))
		return FALSE;

	if (!AdjustTokenPrivileges(process_token, FALSE, &token_privileges, 0, NULL, NULL))
	{
		CloseHandle(process_token);
		return FALSE;
	}

	CloseHandle(process_token);
	return TRUE;
}

/**************************************************************************/

static HANDLE GetUserToken()
{
	HWND shell_window;
	DWORD process_id;
	HANDLE process_handle;
	HANDLE process_token;
	HANDLE user_token;

	if (!SetProcessTokenPrivilege(SE_INCREASE_QUOTA_NAME, SE_PRIVILEGE_ENABLED))
		return NULL;

	shell_window = GetShellWindow();

	if (!shell_window)
		return NULL;

	GetWindowThreadProcessId(shell_window, &process_id);

	if (!process_id)
		return NULL;

	process_handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_id);

	if (!process_handle)
		return NULL;

	if (!OpenProcessToken(process_handle, TOKEN_DUPLICATE, &process_token))
	{
		CloseHandle(process_handle);
		return NULL;
	}

	if (!DuplicateTokenEx(process_token, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID, NULL, SecurityImpersonation, TokenPrimary, &user_token))
		user_token = NULL;

	CloseHandle(process_handle);
	CloseHandle(process_token);
	return user_token;
}

/**************************************************************************/

BOOL RunAsUser(LPWSTR command)
{
	HANDLE user_token;
	STARTUPINFOW startup_info;
	PROCESS_INFORMATION process_info;

	user_token = GetUserToken();

	if (!user_token)
		return FALSE;

	GetStartupInfoW(&startup_info);

	if (!CreateProcessWithTokenW(user_token, 0, NULL, command, 0, NULL, NULL, &startup_info, &process_info))
	{
		CloseHandle(user_token);
		return FALSE;
	}

	CloseHandle(user_token);
	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
	return TRUE;
}

/**************************************************************************/
