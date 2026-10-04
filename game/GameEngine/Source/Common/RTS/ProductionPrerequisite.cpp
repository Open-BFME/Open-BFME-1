// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ProductionPrerequisite.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: ProductionPrerequisite.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ProductionPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"

// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

class UpgradeTemplate;

// BFME appends this vector after the two vectors in the Generals header. The
// field name and +0x18 placement are witnessed by ProductionPrerequisiteIsSatisfied.cpp
// and ParsePrerequisiteUpgradeThunk.cpp; this view keeps the reference header intact.
struct Rva000E4BE0UpgradeVectorView
{
	unsigned char prefix[0x18];
	std::vector<UpgradeTemplate *> m_prereqUpgrades;
};

// The retail UnicodeString shim calls StringBase::concat with an explicit
// wcslen result. Keep that call shape at the append sites in this body.
static __forceinline void appendWideText(UnicodeString &destination, const wchar_t *text)
{
	((StringBase<wchar_t> *)&destination)->concat(text, (Int)wcslen(text));
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// The exact retail constructor is emitted by ProductionPrerequisiteCtorThunk.cpp.

//-----------------------------------------------------------------------------
void ProductionPrerequisite::init()
{
	m_prereqUnits.clear();
	m_prereqSciences.clear();
	
}

//-----------------------------------------------------------------------------
Int ProductionPrerequisite::calcNumPrereqUnitsOwned(const Player *player, Int counts[MAX_PREREQ]) const
{
	const ThingTemplate *tmpls[MAX_PREREQ];
	UnsignedInt cnt = m_prereqUnits.size();
	if (cnt > MAX_PREREQ)
		cnt = MAX_PREREQ;
	UnsignedInt i;
	for (i = 0; i < cnt; i++)
		tmpls[i] = m_prereqUnits[i].unit;
	int j;
	for (j = cnt; j < MAX_PREREQ; j++)
		tmpls[j] = NULL;
	player->countObjectsByThingTemplate(cnt, tmpls, false, counts);
	return cnt;
}

//-----------------------------------------------------------------------------
Int ProductionPrerequisite::getAllPossibleBuildFacilityTemplates(const ThingTemplate* tmpls[], Int maxtmpls) const
{
	Int count = 0;
	for (int i = 0; i < m_prereqUnits.size(); i++)
	{
		if (i > 0 && !(m_prereqUnits[i].flags & UNIT_OR_WITH_PREV))
			break;
		if (count >= maxtmpls)
			break;
		tmpls[count++] = m_prereqUnits[i].unit;
	}
	return count;
}

//-----------------------------------------------------------------------------
const ThingTemplate *ProductionPrerequisite::getExistingBuildFacilityTemplate( const Player *player ) const
{
	DEBUG_ASSERTCRASH(player, ("player may not be null"));
	if (m_prereqUnits.size())
	{
		Int ownCount[MAX_PREREQ];
		Int cnt = calcNumPrereqUnitsOwned(player, ownCount);
		for (int i = 0; i < cnt; i++)
		{
			if (i > 0 && !(m_prereqUnits[i].flags & UNIT_OR_WITH_PREV))
				break;
			if (ownCount[i])
				return m_prereqUnits[i].unit;
		} 
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// ?isSatisfied@ProductionPrerequisite@@QBE_NPBVPlayer@@@Z present-unmatched
Bool ProductionPrerequisite::isSatisfied(const Player *player) const
{
	Int i;

	if (!player)
		return false;

	// gotta have all the prereq sciences.
	for (i = 0; i < m_prereqSciences.size(); i++)
	{
		if (!player->hasScience(m_prereqSciences[i]))
			return false;
	}

	// the player must have at least one instance of each prereq unit.
	Int ownCount[MAX_PREREQ];
	Int cnt = calcNumPrereqUnitsOwned(player, ownCount);

	// fix up the "or" cases. (start at 1!)
	for (i = 1; i < cnt; i++)
	{
		if (m_prereqUnits[i].flags & UNIT_OR_WITH_PREV)
		{
			ownCount[i] += ownCount[i-1];	// lump 'em together for prereq purposes
			ownCount[i-1] = -1;						// flag for "ignore me"
		}
	}

	for (i = 0; i < cnt; i++)
	{
		if (ownCount[i] == -1)	// the magic "ignore me" flag
			continue;	
		if (ownCount[i] == 0)		// everything not ignored, is required
			return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries. 
	* Return FALSE if no space left to add unit */
//-------------------------------------------------------------------------------------------------
// ?addUnitPrereq@ProductionPrerequisite@@ present-unmatched
void ProductionPrerequisite::addUnitPrereq( AsciiString unit, Bool orUnitWithPrevious )
{
	PrereqUnitRec info;
	info.name = unit;
	info.flags = orUnitWithPrevious ? UNIT_OR_WITH_PREV : 0;
	info.unit = NULL;
	m_prereqUnits.push_back(info);

}  // end addUnitPrereq

//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries. 
	* Return FALSE if no space left to add unit */
//-------------------------------------------------------------------------------------------------
// ?addUnitPrereq@ProductionPrerequisite@@ present-unmatched
void ProductionPrerequisite::addUnitPrereq( const std::vector<AsciiString>& units )
{
	Bool orWithPrevious = false;
	for (int i = 0; i < units.size(); ++i)
	{
		addUnitPrereq(units[i], orWithPrevious);
		orWithPrevious = true;
	}

}  // end addUnitPrereq

//-------------------------------------------------------------------------------------------------
// returns an asciistring which is a list of all the prerequisites
// not satisfied yet
// ?getRequiresList@ProductionPrerequisite@@QBE?AVUnicodeString@@PBVPlayer@@@Z
UnicodeString ProductionPrerequisite::getRequiresList(const Player *player) const
{

	// if player is invalid, return empty string
	if (!player)
		return UnicodeString::TheEmptyString;

	UnicodeString requiresList = UnicodeString::TheEmptyString;
		
	// check the prerequired units
	Int ownCount[MAX_PREREQ];
	Int cnt = calcNumPrereqUnitsOwned(player, ownCount);
	Int i;

	Bool orRequirements[MAX_PREREQ];
	//Added for fix below in getRequiresList
	//By Sadullah Nader
	//Initializes the OR_WITH_PREV structures
	for (i = 0; i < MAX_PREREQ; i++)
	{
		orRequirements[i] = FALSE;
	}
	//
	// account for the "or" unit cases, start for loop at 1
	for (i = 1; i < cnt; i++)
	{
		if (m_prereqUnits[i].flags & UNIT_OR_WITH_PREV)
		{
			orRequirements[i] = TRUE;     // set the flag for this unit to be "ored" with previous
			ownCount[i] += ownCount[i-1];	// lump 'em together for prereq purposes
			ownCount[i-1] = -1;						// flag for "ignore me"
		}
	}
	
	// check to see if anything is required
	const ThingTemplate *unit;
	UnicodeString unitName;
	Bool firstRequirement = true;
	for (i = 0; i < cnt; i++)
	{
		// we have an unfulfilled requirement
		if (ownCount[i] == 0) {
			
			if(orRequirements[i])
			{
				unit = m_prereqUnits[i-1].unit;
				unitName = unit->getDisplayName();
				appendWideText(unitName, L" " );
				unitName.concat(TheGameText->fetch("CONTROLBAR:OrRequirement", NULL));
				appendWideText(unitName, L" " );
				requiresList.concat(unitName);
			}

			// get the requirement and then its name
			unit = m_prereqUnits[i].unit;
			unitName = unit->getDisplayName();

			// gets command button, and then modifies unitName
			//CommandButton *cmdButton = TheControlBar->findCommandButton(unit->getName());
			//if (cmdButton)
				//unitName.translate(TheGameText->fetch(cmdButton->m_textLabel.str()));

			// format name appropriately with 'returns' if necessary
			if (firstRequirement)
				firstRequirement = false;
			else
				appendWideText(unitName, L"\n");

			// add it to the list
			requiresList.concat(unitName);
		}
	}

	Bool hasSciences = TRUE;
	// gotta have all the prereq sciences.
	for (i = 0; i < m_prereqSciences.size(); i++)
	{
		if (!player->hasScience(m_prereqSciences[i]))
			hasSciences = FALSE;
	}

	if (hasSciences == FALSE) {
		if (firstRequirement) {
			firstRequirement = false;
		} else {
			appendWideText(unitName, L"\n");
		}
		requiresList.concat(TheGameText->fetch("CONTROLBAR:GeneralsPromotion", NULL));
	}

	Bool hasUpgrades = TRUE;
	const UpgradeTemplate *upgrade;
	const Rva000E4BE0UpgradeVectorView *upgradeView =
		reinterpret_cast<const Rva000E4BE0UpgradeVectorView *>(this);
	for (i = 0; i < upgradeView->m_prereqUpgrades.size(); i++)
	{
		upgrade = upgradeView->m_prereqUpgrades[i];
		if (!const_cast<Player *>(player)->hasUpgradeComplete(upgrade))
			hasUpgrades = FALSE;
	}
	if (hasUpgrades == FALSE)
	{
		if (firstRequirement)
			firstRequirement = false;
		else
			appendWideText(unitName, L"\n");
		requiresList.concat(TheGameText->fetch("CONTROLBAR:UpgradeRequired", NULL));
	}

	// return final list
	return requiresList;
}
