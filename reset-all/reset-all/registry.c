/* Includes ***************************************************************/

#include "registry.h"

/* Defines ****************************************************************/

#define REGISTRY_WRITE 1

/* Locals *****************************************************************/

static int status;

/* Functions **************************************************************/

void RegistryResetStatus()
{
	status = 0;
}

/**************************************************************************/

int RegistrySetStatus(int result)
{
	status |= result;
	return status;
}

/**************************************************************************/

int RegistryGetStatus()
{
	return status;
}

/**************************************************************************/

int RegistryOpenKey(HKEY key, LPCTSTR name, REGSAM desired, PHKEY result)
{
	switch (RegOpenKeyEx(key, name, 0, desired, result))
	{
		case ERROR_SUCCESS:
			return REGISTRY_SUCCESS;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryEnumKey(HKEY key, DWORD index, LPTSTR name, DWORD size)
{
	switch (RegEnumKeyEx(key, index, name, &size, NULL, NULL, NULL, NULL))
	{
		case ERROR_SUCCESS:
			return REGISTRY_SUCCESS;

		case ERROR_NO_MORE_ITEMS:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryCloseKey(HKEY key)
{
	if (RegCloseKey(key) != ERROR_SUCCESS)
		status |= REGISTRY_ERROR;

	return status;
}

/**************************************************************************/

int RegistryCloseKeys(HKEY key1, HKEY key2)
{
	if (RegCloseKey(key1) != ERROR_SUCCESS)
		status |= REGISTRY_ERROR;

	if (RegCloseKey(key2) != ERROR_SUCCESS)
		status |= REGISTRY_ERROR;

	return status;
}

/**************************************************************************/

int RegistryCreateKey(HKEY key, LPCTSTR name, REGSAM desired, PHKEY result)
{
	if (RegCreateKeyEx(key, name, 0, NULL, 0, desired, NULL, result, NULL) == ERROR_SUCCESS)
	{
		status |= REGISTRY_WRITE;
		return REGISTRY_SUCCESS;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryRenameKey(HKEY key, LPCWSTR old_name, LPCWSTR new_name)
{
	switch (RegRenameKey(key, old_name, new_name))
	{
		case ERROR_SUCCESS:
			status |= REGISTRY_WRITE;
			return REGISTRY_SUCCESS;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryDeleteTree(HKEY key, LPCTSTR name)
{
	switch (RegDeleteTree(key, name))
	{
		case ERROR_SUCCESS:
			status |= REGISTRY_WRITE;
			return REGISTRY_SUCCESS;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryEnumValue(HKEY key, DWORD index, LPTSTR name, DWORD size)
{
	switch (RegEnumValue(key, index, name, &size, NULL, NULL, NULL, NULL))
	{
		case ERROR_SUCCESS:
			return REGISTRY_SUCCESS;

		case ERROR_NO_MORE_ITEMS:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryQueryValue(HKEY key, LPCTSTR name, LPDWORD type, LPBYTE data, LPDWORD size)
{
	switch (RegQueryValueEx(key, name, NULL, type, data, size))
	{
		case ERROR_SUCCESS:
			return REGISTRY_SUCCESS;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistrySetValue(HKEY key, LPCTSTR name, DWORD type, LPCBYTE data, DWORD size)
{
	if (RegSetValueEx(key, name, 0, type, data, size) == ERROR_SUCCESS)
	{
		status |= REGISTRY_WRITE;
		return REGISTRY_SUCCESS;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistrySetDWORD(HKEY key, LPCTSTR name, DWORD value)
{
	return RegistrySetValue(key, name, REG_DWORD, (LPCBYTE)&value, sizeof value);
}

/**************************************************************************/

int RegistryResetValue(HKEY key, LPCTSTR name, DWORD type, LPCBYTE data, DWORD size)
{
	DWORD get_type;
	LPBYTE get_data;
	DWORD get_size;

	get_data = (LPBYTE)malloc(size);

	if (!get_data)
	{
		status |= REGISTRY_ERROR;
		return REGISTRY_ERROR;
	}

	get_size = size;

	switch (RegQueryValueEx(key, name, NULL, &get_type, get_data, &get_size))
	{
		case ERROR_SUCCESS:
			if (get_type == type && get_size == size && memcmp(get_data, data, size) == 0)
			{
				free(get_data);
				return REGISTRY_SUCCESS;
			}

			free(get_data);
			return RegistrySetValue(key, name, type, data, size);

		case ERROR_MORE_DATA:
		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			free(get_data);
			return RegistrySetValue(key, name, type, data, size);
	}

	free(get_data);
	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryResetDWORD(HKEY key, LPCTSTR name, DWORD value)
{
	return RegistryResetValue(key, name, REG_DWORD, (LPCBYTE)&value, sizeof value);
}

/**************************************************************************/

int RegistryCopyValue(HKEY old_key, HKEY new_key, LPCTSTR name)
{
	DWORD type;
	LPBYTE data;
	DWORD size;
	int result;

	switch (RegQueryValueEx(old_key, name, NULL, NULL, NULL, &size))
	{
		case ERROR_SUCCESS:
			break;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			return REGISTRY_NOT_FOUND;

		default:
			status |= REGISTRY_ERROR;
			return REGISTRY_ERROR;
	}

	data = (LPBYTE)malloc(size);

	if (!data)
	{
		status |= REGISTRY_ERROR;
		return REGISTRY_ERROR;
	}

	switch (RegQueryValueEx(old_key, name, NULL, &type, data, &size))
	{
		case ERROR_SUCCESS:
			result = RegistrySetValue(new_key, name, type, data, size);
			free(data);
			return result;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			free(data);
			return REGISTRY_NOT_FOUND;
	}

	free(data);
	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/

int RegistryDeleteValue(HKEY key, LPCTSTR name)
{
	switch (RegDeleteValue(key, name))
	{
		case ERROR_SUCCESS:
			status |= REGISTRY_WRITE;
			return REGISTRY_SUCCESS;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			return REGISTRY_NOT_FOUND;
	}

	status |= REGISTRY_ERROR;
	return REGISTRY_ERROR;
}

/**************************************************************************/
