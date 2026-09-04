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

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName(void) const;
	MultiplayerColorDefinition *operator=(const MultiplayerColorDefinition &other);

private:
	AsciiString m_tooltipName;
	RGBColor m_rgbValue;
	int m_color;
	RGBColor m_rgbValueNight;
	int m_colorNight;
};

MultiplayerColorDefinition *MultiplayerColorDefinition::operator=(
	const MultiplayerColorDefinition &other)
{
	m_tooltipName = other.getTooltipName();
	m_rgbValue = other.m_rgbValue;
	m_color = other.m_color;
	m_rgbValueNight = other.m_rgbValueNight;
	m_colorNight = other.m_colorNight;
	return this;
}
