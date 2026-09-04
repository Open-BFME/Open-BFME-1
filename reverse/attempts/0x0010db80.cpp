// ??0SaveGameInfo@@QAE@ABV0@@Z
// partial score=0.84 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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
#include "Common/UnicodeString.h"

struct SaveDate
{
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short dayOfWeek;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned short milliseconds;
};

enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,
	SAVE_FILE_TYPE_MISSION,
	SAVE_FILE_TYPE_NUM_TYPES
};

class SaveGameInfo
{
public:
	SaveGameInfo(const SaveGameInfo &other);

	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	SaveDate date;
	AsciiString campaignSide;
	int missionNumber;
	UnicodeString description;
	SaveFileType saveFileType;
	AsciiString missionMapName;
};

SaveGameInfo::SaveGameInfo(const SaveGameInfo &other) :
	saveGameMapName(other.saveGameMapName),
	pristineMapName(other.pristineMapName),
	mapLabel(other.mapLabel),
	date(other.date),
	campaignSide(other.campaignSide),
	missionNumber(other.missionNumber),
	description(other.description),
	saveFileType(other.saveFileType),
	missionMapName(other.missionMapName)
{
}
