// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

// Give VC7.1 a declared pair destructor that explicit instantiation can emit.
#define _STLP_TRIVIAL_DESTRUCTOR_BUG
#include <utility>

class AsciiString;

#include "string_base.h"

// Retail inlines the forwarding copy and calls the narrow StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString();
};

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

typedef std::pair<const int, MultiplayerColorDefinition> MultiplayerColorPair;

// The map subscript at 0x0008F160 reaches this key/value constructor via 0x00048FEA.
template MultiplayerColorPair::pair(const int &, const MultiplayerColorDefinition &);
template MultiplayerColorPair::pair(const MultiplayerColorPair &);
template MultiplayerColorPair::~pair();
