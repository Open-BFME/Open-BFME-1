// cl: /O2 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
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

// Real C++ reconstruction of the unclaimed ExperienceLevelSystem helper at
// retail RVA 0x00382210 (474 bytes).  The matched parser body at 0x00382460
// routes its non-override ExperienceLevel through this address-derived member
// carrier.  The raw helper's ECX+8 hash_map and argument+0x1c target-name
// vector establish the owner and the D8 ExperienceLevel layout; its ret 4
// establishes the one-pointer member ABI.  The address-derived spelling keeps
// the identity claim limited to that caller and those concrete offsets.
//
// For each target name the helper appends a copied ExperienceLevel to the
// existing keyed list.  A missing key first builds a one-node local list and
// assigns it through hash_map::operator[].  The StringInline AsciiString view
// is intentional: retail's temporary copy calls StringBase<char>'s proven
// 0x00887B60 body directly and its cleanup calls releaseBuffer at 0x00887940.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>

#include "StringInline.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Overridable
{
public:
	virtual ~Overridable();

protected:
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	RadiusDecalTemplate(const RadiusDecalTemplate &that);
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

	friend class ExperienceLevelSystem;
};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xd8 ? 1 : -1];

typedef _STL::list<ExperienceLevel> ExperienceLevelList;
typedef _STL::pair<const Int, ExperienceLevelList> ExperienceLevelMapPair;
typedef _STL::hash_map<Int, ExperienceLevelList, _STL::hash<Int>,
	_STL::equal_to<Int>, _STL::allocator<ExperienceLevelMapPair> > ExperienceLevelMap;

class ExperienceLevelSystem
{
public:
	void rva00382210(ExperienceLevel *level);

private:
	unsigned char m_subsystemHead[8];
	ExperienceLevelMap m_levels;
};

void ExperienceLevelSystem::rva00382210(ExperienceLevel *level)
{
	for (UnsignedInt index = 0;
		index < (UnsignedInt)level->m_targetNames.size(); ++index)
	{
		AsciiString name = level->m_targetNames[index];
		const Int key = (Int)TheNameKeyGenerator->nameToKey(name.str());
		ExperienceLevelMap::iterator found = m_levels.find(key);
		if (found == m_levels.end())
		{
			ExperienceLevelList levels;
			levels.push_back(*level);
			m_levels[key] = levels;
		}
		else
		{
			found->second.push_back(*level);
		}
	}
}
