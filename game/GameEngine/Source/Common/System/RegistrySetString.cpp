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

static int registryLength(const AsciiString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? *(unsigned short *)(data + 4) : 0;
}

bool setStringInRegistry(HKEY root, AsciiString path, AsciiString key, AsciiString val)
{
	HKEY handle;
	unsigned long type;
	unsigned long returnValue;
	int size;

	if ((returnValue = RegCreateKeyEx(root, registryString(path), 0, "REG_NONE",
	                                  REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
	                                  &handle, NULL)) == ERROR_SUCCESS)
	{
		type = REG_SZ;
		size = registryLength(val) + 1;
		returnValue = RegSetValueEx(handle, registryString(key), 0, type,
		                            (unsigned char *)registryString(val), size);
		RegCloseKey(handle);
	}

	return returnValue == ERROR_SUCCESS;
}
