// cl: /DNDEBUG /DWIN32 /MD /EHsc- /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//
// The ExperienceLevelSystem map's STLport operator[] at retail RVA
// 0x003820A0.  The already-matched 0x00382210 member calls this exact
// specialization through ILT 0x0003BB33; its +0x08 map member and the
// 0x00381E80 list<ExperienceLevel> assignment identify the complete value
// type.  Keep this TU to the explicit template instantiation so the emitted
// body is the real STLport implementation, not an address carrier.

#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <hash_map>
#include <list>
#include <vector>

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class Overridable
{
protected:
	virtual ~Overridable();

	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();

private:
	AsciiString m_name;
	AsciiString m_secondName;
	Int m_shadowType;
	Real m_minOpacity;
	Real m_maxOpacity;
	Real m_opacityThrobTime;
	UnsignedInt m_color;
	Bool m_onlyVisibleToOwningPlayer;
	UnsignedInt m_unmodelled20;
	UnsignedInt m_unmodelled24;
	UnsignedInt m_unmodelled28;
	UnsignedInt m_unmodelled2c;
};

struct ModelConditionFlags
{
	UnsignedInt m_bits[10];
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

struct LevelUpFXInfo
{
	const void *fx;
	AsciiString boneName;
};

typedef _STL::vector<AsciiString> AsciiStringVector;
typedef _STL::vector<LevelUpFXInfo> LevelUpFXVector;

class ExperienceLevel : public Overridable
{
public:
	ExperienceLevel(const ExperienceLevel &that);
	virtual ~ExperienceLevel();

private:
	AsciiString m_name;
	Int m_requiredExperience;
	Int m_experienceAward;
	Int m_experienceAwardOwnGuysDie;
	AsciiStringVector m_targetNames;
	AsciiStringVector m_attributeModifiers;
	LevelUpFXVector m_levelUpFx;
	Int m_levelUpOCL;
	AsciiStringVector m_upgrades;
	ModelConditionFlags m_modelConditionState;
	RadiusDecalTemplate m_selectionDecal;
	Bool m_showLevelUpTint;
	RGBColor m_levelUpTintColor;
	Int m_levelUpTintPreColorTime;
	Int m_levelUpTintPostColorTime;
	Int m_levelUpTintSustainColorTime;
	Real m_levelUpTintFrequency;
	Real m_levelUpTintAmplitude;
	Int m_rank;
	Bool m_informUpdateModule;
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
	Int m_emotionType;
};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xd8 ? 1 : -1];

typedef _STL::list<ExperienceLevel> ExperienceLevelList;
typedef _STL::pair<const Int, ExperienceLevelList> ExperienceLevelMapValue;
typedef _STL::hash_map<Int, ExperienceLevelList, _STL::hash<Int>,
	_STL::equal_to<Int>, _STL::allocator<ExperienceLevelMapValue> >
	ExperienceLevelMap;

// ??A?$hash_map@HV?$list@VExperienceLevel@@V?$allocator@VExperienceLevel@@@_STL@@@_STL@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$list@VExperienceLevel@@V?$allocator@VExperienceLevel@@@_STL@@@_STL@@@_STL@@@2@@_STL@@QAEAAV?$list@VExperienceLevel@@V?$allocator@VExperienceLevel@@@_STL@@@1@ABH@Z
template ExperienceLevelList &ExperienceLevelMap::operator[](
	const Int &key);
