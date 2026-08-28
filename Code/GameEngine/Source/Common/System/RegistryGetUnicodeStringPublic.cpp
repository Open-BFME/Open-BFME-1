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

#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const wchar_t *value)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			(const unsigned short *)value);
	}
	UnicodeString(const UnicodeString &);
	~UnicodeString();

private:
	unsigned short *m_text;
};

bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val);

static const unsigned short *registryString(const UnicodeString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? (unsigned short *)(data + 8) : (const unsigned short *)L"";
}

static int registryLength(const UnicodeString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? *(unsigned short *)(data + 4) : 0;
}

bool GetStringFromRegistry(UnicodeString path, UnicodeString key, UnicodeString &val)
{
	UnicodeString fullPath = L"SOFTWARE\\Electronic Arts\\EA Games\\The Battle for Middle-earth";

	((StringBase<unsigned short> *)&fullPath)->concat(registryString(path), registryLength(path));
	if (getStringFromRegistry(HKEY_LOCAL_MACHINE, registryString(fullPath), registryString(key), val))
		return true;

	return getStringFromRegistry(HKEY_CURRENT_USER, registryString(fullPath), registryString(key), val);
}
