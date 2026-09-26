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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Science.h ////////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, Colin Day November 2001
// Desc:   Science descriptoins
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __SCIENCE_H_
#define __SCIENCE_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/Overridable.h"
#include "Common/NameKeyGenerator.h"
#include "Common/UnicodeString.h"

class Player;

//-------------------------------------------------------------------------------------------------
enum ScienceType
{
	SCIENCE_INVALID = -1
};

//-------------------------------------------------------------------------------------------------
typedef std::vector<ScienceType> ScienceVec;

//-------------------------------------------------------------------------------------------------
class ScienceInfo : public Overridable
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( ScienceInfo, "ScienceInfo"  )

	friend class ScienceStore;

private:
	// BFME layout drift (proven from retail lotrbfme.exe against the ZH reference).
	// The whole layout is now pinned by friend_parseScienceDefinition@0xE8630,
	// which inlines this constructor: it allocates 0x30 bytes and writes the
	// vtable at +0x00, 0 at +0x04/+0x08, SCIENCE_INVALID at +0x0c, 0 through
	// +0x10..+0x28 and 1 at +0x2c. That agrees with the two offsets already
	// proven from elsewhere -- m_grantable at +0x2c (isScienceGrantable@0xE6DE0)
	// and m_prereqSciences begin/end at +0x18/+0x1c
	// (playerHasPrereqsForScience@0xE6E50).
	//
	// Two consequences. The BFME-only Int at +0x28 is not opaque any more: the
	// Science block's field table at 0x01084D40 binds the token
	// "SciencePurchasePointCostMP" to it. And m_rootSciences does not exist in
	// BFME at all -- fields run to +0x2c inclusive, so sizeof rounds to exactly
	// the 0x30 retail allocates, leaving no room for a 12-byte ScienceVec.
	// Retail's parse function ends at info->m_science = st with no
	// addRootSciences call, which is the same story from the other side.
	ScienceType						m_science;
	UnicodeString					m_name;
	UnicodeString					m_description;
	ScienceVec						m_prereqSciences;
	Int										m_sciencePurchasePointCost;
	Int										m_sciencePurchasePointCostMP;	///< @0x28 BFME-only; used instead of the above in multiplayer
	Bool									m_grantable;

	ScienceInfo() :
		m_science(SCIENCE_INVALID),
		m_sciencePurchasePointCost(0),	// 0 means "cannot be purchased"
		m_sciencePurchasePointCostMP(0),
		m_grantable(true)
	{
	}

	// Kept even though m_rootSciences is gone: this reads m_prereqSciences and
	// fills the vector it is handed, so it does not need the member, and the TU
	// demonstrably still contains it -- the matched __find<ScienceType*> at
	// 0x0018B470 and find at 0x0018B590 are the instantiations its std::find
	// call emits, and nothing else in Science.cpp produces them. What BFME does
	// with the result is what is unresolved, not whether the function is there.
	void addRootSciences(ScienceVec& v) const;
};
EMPTY_DTOR(ScienceInfo);

//-------------------------------------------------------------------------------------------------
class ScienceStore : public SubsystemInterface
{
	friend class ScienceInfo;

public:
	virtual ~ScienceStore();

	void init();
	void reset();
	void update() { }

	Bool isValidScience(ScienceType st) const;

	Bool isScienceGrantable(ScienceType st) const;

	Bool getNameAndDescription(ScienceType st, UnicodeString& name, UnicodeString& description) const;

	Bool playerHasPrereqsForScience(const Player* player, ScienceType st) const;

	// Zero Hour's playerHasRootPrereqsForScience and getPurchasableSciences are
	// dropped here rather than ported: both are built on ScienceInfo::
	// m_rootSciences, and that member does not exist in BFME (see the layout
	// note above -- retail's ScienceInfo is exactly 0x30 bytes with no room for
	// it, and the parse function never populates one). Whatever BFME does
	// instead is unresolved, and guessing at it would put unverifiable bodies
	// in the tree.

	Int getSciencePurchaseCost(ScienceType science) const;

	ScienceType getScienceFromInternalName(const AsciiString& name) const;
	AsciiString getInternalNameForScience(ScienceType science) const;

	// this is intended ONLY for use by INI::scanScience.
	// Don't use it anywhere else. In particular, never, ever, ever
	// call this with a hardcoded science name. (srj)
	ScienceType friend_lookupScience(const char* scienceName) const;
	static void friend_parseScienceDefinition(INI* ini);

	// return a vector of all the currently-known science names
	// NOTE: this is really only for use by WorldBuilder! Please
	// do not use it in RTS!
	std::vector<AsciiString> friend_getScienceNames() const;


private:

	const ScienceInfo* findScienceInfo(ScienceType st) const;

	typedef std::vector<ScienceInfo*> ScienceInfoVec;
	ScienceInfoVec m_sciences;
};

extern ScienceStore* TheScienceStore;


#endif // __SCIENCE_H_
