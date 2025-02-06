#ifndef REGISTRY_H
#define REGISTRY_H

/* Includes ***************************************************************/

#include "common.h"

/* Defines ****************************************************************/

#define REGISTRY_SUCCESS		1
#define REGISTRY_NOT_FOUND		0
#define REGISTRY_INCOMPLETE		-1
#define REGISTRY_ERROR			-2

/* Functions **************************************************************/

void RegistryResetStatus();
int RegistrySetStatus(int result);
int RegistryGetStatus();
int RegistryOpenKey(HKEY key, LPCTSTR name, REGSAM desired, PHKEY result);
int RegistryEnumKey(HKEY key, DWORD index, LPTSTR name, DWORD size);
int RegistryCloseKey(HKEY key);
int RegistryCloseKeys(HKEY key1, HKEY key2);
int RegistryCreateKey(HKEY key, LPCTSTR name, REGSAM desired, PHKEY result);
int RegistryRenameKey(HKEY key, LPCWSTR old_name, LPCWSTR new_name);
int RegistryDeleteTree(HKEY key, LPCTSTR name);
int RegistryEnumValue(HKEY key, DWORD index, LPTSTR name, DWORD size);
int RegistryQueryValue(HKEY key, LPCTSTR name, LPDWORD type, LPBYTE data, LPDWORD size);
int RegistrySetValue(HKEY key, LPCTSTR name, DWORD type, LPCBYTE data, DWORD size);
int RegistrySetDWORD(HKEY key, LPCTSTR name, DWORD value);
int RegistryResetValue(HKEY key, LPCTSTR name, DWORD type, LPCBYTE data, DWORD size);
int RegistryResetDWORD(HKEY key, LPCTSTR name, DWORD value);
int RegistryCopyValue(HKEY old_key, HKEY new_key, LPCTSTR name);
int RegistryDeleteValue(HKEY key, LPCTSTR name);

/**************************************************************************/

#endif
