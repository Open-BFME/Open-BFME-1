// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

// The AsciiString twin of RegistryGetUnicodeString.cpp (0x00109030). Retail
// puts both in one compiland; they are byte-for-byte the same shape apart from
// the ANSI registry entry points, the narrow buffer, and strlen inlining where
// the wide copy calls the wcslen import.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>

#include "Common/AsciiString.h"

static const char *registryString(const AsciiString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? (data + 8) : "";
}

bool getStringFromRegistry(HKEY root, AsciiString path, AsciiString key, AsciiString &val)
{
	HKEY handle;
	char buffer[256];
	unsigned long size = 256;
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyExA(root, registryString(path), 0, KEY_READ, &handle)) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueExA(handle, registryString(key), NULL, &type,
		                              (unsigned char *)buffer, &size);
		RegCloseKey(handle);
	}

	if (returnValue == ERROR_SUCCESS)
	{
		((StringBase<char> *)&val)->set(buffer, strlen(buffer));
		return true;
	}

	return false;
}
