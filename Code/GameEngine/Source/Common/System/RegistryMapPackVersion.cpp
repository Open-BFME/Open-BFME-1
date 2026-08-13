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

#include "Common/AsciiString.h"

bool GetUnsignedIntFromRegistry(AsciiString path, AsciiString key, unsigned int &val);

unsigned int GetRegistryMapPackVersion(void)
{
	unsigned int val = 65536;
	GetUnsignedIntFromRegistry("", "MapPackVersion", val);
	return val;
}
