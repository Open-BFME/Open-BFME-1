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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Common/AsciiString.h"

static const char *registryString(const AsciiString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? data + 8 : "";
}

bool getUnsignedIntFromRegistry(HKEY root, AsciiString path, AsciiString key, unsigned int &val)
{
	HKEY handle;
	unsigned char buffer[4];
	unsigned long size = 4;
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyEx(root, registryString(path), 0, KEY_READ, &handle)) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueEx(handle, registryString(key), NULL, &type, buffer, &size);
		RegCloseKey(handle);
	}

	if (returnValue == ERROR_SUCCESS)
	{
		val = *(unsigned int *)buffer;
		return true;
	}

	return false;
}
