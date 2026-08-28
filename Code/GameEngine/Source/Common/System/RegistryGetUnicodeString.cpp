// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wchar.h>

// reference/shims/sweep/windows.h only declares the ANSI registry entry
// points. Retail calls the wide ones here -- the DIR32 check saw this site
// resolve to the RegOpenKeyExW slot at 0x0135914C, not RegOpenKeyExA at
// 0x01359148 -- so declare them rather than casting wchar_t* down to char*.
extern "C" __declspec(dllimport) long __stdcall RegOpenKeyExW(
		HKEY hKey, const wchar_t *lpSubKey, unsigned long ulOptions, unsigned long samDesired, HKEY *phkResult);
extern "C" __declspec(dllimport) long __stdcall RegQueryValueExW(
		HKEY hKey, const wchar_t *lpValueName, unsigned long *lpReserved, unsigned long *lpType,
		unsigned char *lpData, unsigned long *lpcbData);

#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &);
	~UnicodeString();

private:
	unsigned short *m_text;
};

static const wchar_t *registryString(const UnicodeString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? (wchar_t *)(data + 8) : L"";
}

bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val)
{
	HKEY handle;
	wchar_t buffer[128];
	unsigned long size = 256;
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyExW(root, registryString(path), 0, KEY_READ, &handle)) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueExW(handle, registryString(key), NULL, &type,
		                              (unsigned char *)buffer, &size);
		RegCloseKey(handle);
	}

	if (returnValue == ERROR_SUCCESS)
	{
		((StringBase<unsigned short> *)&val)->set((unsigned short *)buffer, wcslen(buffer));
		return true;
	}

	return false;
}
