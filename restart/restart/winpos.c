/* Includes ***************************************************************/

#include "winpos.h"

/* Defines ****************************************************************/

#define MAX_WINDOWS 10000

/* Locals *****************************************************************/

static int window_count;
static HWND window_list[MAX_WINDOWS];
static WINDOWPLACEMENT window_placement[MAX_WINDOWS];

/* Functions **************************************************************/

static BOOL CALLBACK EnumWindowsProc(HWND window, LPARAM lParam)
{
	if (window_count >= MAX_WINDOWS)
		return FALSE;

	if (IsWindowVisible(window))
	{
		window_list[window_count] = window;
		window_placement[window_count].length = sizeof window_placement[window_count];
		GetWindowPlacement(window, &window_placement[window_count]);

		switch (window_placement[window_count].showCmd)
		{
			case SW_SHOWNORMAL:
				GetWindowRect(window, &window_placement[window_count].rcNormalPosition);
				break;

			case SW_SHOWMAXIMIZED:
				ShowWindow(window, SW_SHOWNORMAL);
				break;
		}

		window_placement[window_count].flags |= WPF_ASYNCWINDOWPLACEMENT;
		window_count++;
	}

	return TRUE;
}

/**************************************************************************/

void SaveWindows()
{
	window_count = 0;
	EnumWindows(EnumWindowsProc, 0);
}

/**************************************************************************/

static BOOL SetWindowRect(HWND window, RECT rect, UINT flags)
{
	return SetWindowPos(window, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, flags);
}

/**************************************************************************/

void RestoreWindows()
{
	int index;

	for (index = 0; index < window_count; index++)
	{
		if (window_placement[index].showCmd == SW_SHOWNORMAL)
			SetWindowRect(window_list[index], window_placement[index].rcNormalPosition, SWP_ASYNCWINDOWPOS);
		else
			SetWindowPlacement(window_list[index], &window_placement[index]);
	}
}

/**************************************************************************/
