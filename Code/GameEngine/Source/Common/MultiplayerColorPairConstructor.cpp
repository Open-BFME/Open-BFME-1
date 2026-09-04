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
private:
	AsciiString m_tooltipName;
	RGBColor m_rgbValue;
	int m_color;
	RGBColor m_rgbValueNight;
	int m_colorNight;
};

namespace _STL
{
	template <class First, class Second>
	struct pair;

	template <>
	struct pair<const int, MultiplayerColorDefinition>
	{
		pair(const int &firstValue, const MultiplayerColorDefinition &secondValue);

		const int first;
		MultiplayerColorDefinition second;
	};

	pair<const int, MultiplayerColorDefinition>::pair(
		const int &firstValue, const MultiplayerColorDefinition &secondValue) :
		first(firstValue), second(secondValue)
	{
	}
}
