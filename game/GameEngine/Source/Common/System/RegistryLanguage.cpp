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

#include "Common/AsciiString.h"

bool GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString &val);

AsciiString GetRegistryLanguage(void)
{
	static bool cached = false;
	static AsciiString val = "english";

	if (cached)
		return val;

	cached = true;
	GetStringFromRegistry("", "Language", val);
	return val;
}
