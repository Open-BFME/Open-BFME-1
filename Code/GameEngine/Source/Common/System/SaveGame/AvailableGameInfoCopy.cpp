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

class SaveGameInfo
{
public:
	SaveGameInfo(const SaveGameInfo &other);

private:
	char m_data[0x30];
};

struct AvailableGameInfo
{
	AvailableGameInfo(const AvailableGameInfo &other);

	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

AvailableGameInfo::AvailableGameInfo(const AvailableGameInfo &other) :
	filename(other.filename),
	saveGameInfo(other.saveGameInfo),
	next(other.next),
	prev(other.prev)
{
}
