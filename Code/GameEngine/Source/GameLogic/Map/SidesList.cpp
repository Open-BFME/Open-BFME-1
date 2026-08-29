// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_outofline /Ireference/shims/buildlistinfo /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: SidesList.cpp /////////////////////////////////////////////////////////
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
// File name: SidesList.cpp
//
// Created:   John Ahlquist, Nov 2001
//
// Desc:      Contains the information describing Sides (player, ai, neutral etc.)
//						in a scenario, including build lists for non-player sides.
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/DataChunk.h"
#include "Common/GameState.h"
#include "Common/PlayerTemplate.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "GameLogic/AI.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/SidesList.h"

static const Int K_SIDES_DATA_VERSION_1 = 1;
static const Int K_SIDES_DATA_VERSION_2 = 2;	// includes Team list.
static const Int K_SIDES_DATA_VERSION_3 = 3;	// includes Team list.

/* ********* SidesInfo class ****************************/
/**
 SidesInfo - Constructor.
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Map/SidesInfoConstructorThunk.cpp
// ??0SidesInfo@@ present-unmatched
SidesInfo::SidesInfo(void) :
	m_pBuildList(NULL),
	m_scripts(NULL)
{
}

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Map/SidesInfoConstructorThunk.cpp
// ??0SidesInfo@@ present-unmatched
SidesInfo::SidesInfo(const SidesInfo& thatref) :
	m_pBuildList(NULL),
	m_scripts(NULL)
{
	*this = thatref;
}

/**
 SidesInfo - Destructor - 
*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/SidesInfoDestructorThunk.cpp
// ??1SidesInfo@@QAE@XZ present-unmatched
SidesInfo::~SidesInfo(void)
{
	clear();
}

// ?init@SidesInfo@@QAEXPBVDict@@@Z present-unmatched
void SidesInfo::init(const Dict* d)
{
	m_pBuildList->deleteInstance();
	m_pBuildList = NULL;
	m_dict.clear();
	if (m_scripts) 
		m_scripts->deleteInstance();
	m_scripts = NULL;
	if (d)
		m_dict = *d;
}

// ug, I hate having to overload stuff, but this makes it a lot easier to make copies safely
// ??4SidesInfo@@QAEAAV0@ABV0@@Z present-unmatched
SidesInfo& SidesInfo::operator=(const SidesInfo& that)
{
	if (this != &that)
	{
		this->clear();
		this->m_dict = that.m_dict;

		BuildListInfo* thisBLTail = NULL;
		for (BuildListInfo* thatBL = that.m_pBuildList; thatBL; thatBL = thatBL->getNext())
		{
			BuildListInfo* thisBL = newInstance( BuildListInfo );	
			*thisBL = *thatBL;
			thisBL->setNextBuildList(NULL);

			if (thisBLTail)
				thisBLTail->setNextBuildList(thisBL);
			else
				this->m_pBuildList = thisBL;
				
			thisBLTail = thisBL;
		}

		if (that.m_scripts)
			this->m_scripts = that.m_scripts->duplicate();
		else
			this->m_scripts = NULL;
	}
	return *this;
}

/**
* SidesInfo::addToBuildList - Adds a build list entry as the nth entry.
*		
*/
void SidesInfo::addToBuildList(BuildListInfo *pBuildList, Int position)
{
	DEBUG_ASSERTLOG(pBuildList->getNext()==NULL, ("WARNING***Adding already linked element."));
	BuildListInfo *pCur = NULL;
	while (position) {
		position--;
		if (pCur==NULL) {
			pCur = m_pBuildList;
		} else {
			if (pCur->getNext()) {
				pCur = pCur->getNext();
			}	else {
				break; // at end of list.
			}
		}
	}
	if (pCur==NULL) {
		// add to front of list.
		pBuildList->setNextBuildList(m_pBuildList);
		m_pBuildList = pBuildList;
	}	else {
		pBuildList->setNextBuildList(pCur->getNext());
		pCur->setNextBuildList(pBuildList);
	}
}

/**
* SidesInfo::reorderInBuildList - Reorders a build list entry as the nth entry.
*		
*/
void SidesInfo::reorderInBuildList(BuildListInfo *pBuildList, Int newPosition)
{
	/*Int oldPos =*/ removeFromBuildList(pBuildList);
	addToBuildList(pBuildList, newPosition);
}

/**
* SidesInfo::removeFromBuildList - Removes a build list entry.
* Returns the position in the list that the item occupied.
*		
*/
Int SidesInfo::removeFromBuildList(BuildListInfo *pBuildList)
{
	DEBUG_ASSERTCRASH(pBuildList, ("Removing NULL list."));
	if (pBuildList==NULL) return 0;

	Int position = 0;

	if (pBuildList == m_pBuildList) {
		// First item in list, so update head.
		m_pBuildList = pBuildList->getNext();
	} else {
		position = 1;
		// Not the first item, so find the preceeding list element.
		BuildListInfo *pPrev = m_pBuildList;
		while (pPrev && (pPrev->getNext()!=pBuildList) ) {
			pPrev = pPrev->getNext();
			position++;
		}
		DEBUG_ASSERTCRASH(pPrev, ("Removing item not in list."));
		if (pPrev) {
			pPrev->setNextBuildList(pBuildList->getNext());
		}
	}
	pBuildList->setNextBuildList(NULL);
	return position;
}

/* ********* SidesList class ****************************/
/*extern*/ SidesList *TheSidesList = NULL;	 ///< singleton instance of SidesList
/**
 SidesList - Constructor.
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Map/SidesListCtorThunk.cpp
// ??0SidesList@@QAE@XZ present-unmatched
SidesList::SidesList(void) : m_numSides(0), m_numSkirmishSides(0)
{
}

/**
 SidesList - Destructor - 
*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/SidesListDestructorThunk.cpp
// ??1SidesList@@UAE@XZ present-unmatched
SidesList::~SidesList(void)
{
}

/**
 SidesList - reset - 
*/
// ?reset@SidesList@@UAEXXZ present-unmatched
void SidesList::reset(void)
{
	clear();
}

/**
 SidesList - clear - 
*/
// ?clear@SidesList@@QAEXXZ present-unmatched
void SidesList::clear(void)
{
	emptySides();
	emptyTeams();
}



/**
* SidesList::ParseSidesDataChunk - read a Sides chunk.
* Format is the newer CHUNKY format.
*	See SidesList::WriteSidesDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// ?ParseSidesDataChunk@SidesList@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z present-unmatched
Bool SidesList::ParseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	DEBUG_ASSERTCRASH(TheSidesList, ("TheSidesList is null"));

	if (TheSidesList==NULL) 
		return false;

	TheSidesList->clear();
	Int count = file.readInt();
	Int i, j;
	TheSidesList->emptySides();
	for (i=0; i<count; i++) 
	{
		if (i >= MAX_PLAYER_COUNT) break;
		Dict d =  file.readDict();
		TheSidesList->addSide(&d);
		BuildListInfo* pBuildList;
		Int count = file.readInt();
		for (j=0; j<count; j++) 
		{
			pBuildList = newInstance( BuildListInfo );
			pBuildList->setBuildingName(file.readAsciiString());
			pBuildList->setTemplateName(file.readAsciiString());
			Coord3D loc;
			loc.x = file.readReal();
			loc.y = file.readReal();
			loc.z = file.readReal();
			loc.z = 0; // force to ground level
			pBuildList->setLocation(loc);
			pBuildList->setAngle(file.readReal());
			pBuildList->setInitiallyBuilt(file.readByte());
			pBuildList->setNumRebuilds(file.readInt());
			if (info->version >= K_SIDES_DATA_VERSION_3)
			{
				pBuildList->setScript(file.readAsciiString());
				pBuildList->setHealth(file.readInt());
				pBuildList->setWhiner(file.readByte());
				pBuildList->setUnsellable(file.readByte());
				pBuildList->setRepairable(file.readByte());
			}
			TheSidesList->getSideInfo(i)->addToBuildList(pBuildList, j);
		}
	}	
	if (info->version >= K_SIDES_DATA_VERSION_2)
	{
		count = file.readInt();
		TheSidesList->emptyTeams();
		for (i=0; i<count; i++) 
		{
			Dict d =  file.readDict();
			TheSidesList->addTeam(&d);
		}
	}
	
	file.registerParser( AsciiString("PlayerScriptsList"), info->label, ScriptList::ParseScriptsDataChunk );
	if (!file.parse(NULL)) {
		throw(ERROR_CORRUPT_FILE_FORMAT);
	}
	ScriptList *scripts[MAX_PLAYER_COUNT];
	count = ScriptList::getReadScripts(scripts);
	for (i=0; i<count; i++) {
		if (i<TheSidesList->getNumSides()) {
			ScriptList *pSL = TheSidesList->getSideInfo(i)->getScriptList();
			pSL->deleteInstance();
			TheSidesList->getSideInfo(i)->setScriptList(scripts[i]);
			scripts[i] = NULL;
		} else {
			// Read in more players worth than we have.
			scripts[i]->deleteInstance();
			scripts[i] = NULL;
		}
	}
	TheSidesList->validateSides();

	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Incorrect data file length."));
	return true;
}


/**
* SidesList::WriteSidesDataChunk - Writes a Sides chunk.
* Format is the newer CHUNKY format.
*	See SidesList::ParseSidesDataChunk for the reader.
*	Input: DataChunkInput 
*		
*/
// ?WriteSidesDataChunk@SidesList@@SAXAAVDataChunkOutput@@@Z present-unmatched
void SidesList::WriteSidesDataChunk(DataChunkOutput &chunkWriter)
{
	DEBUG_ASSERTCRASH(TheSidesList, ("TheSidesList is null"));
	if (TheSidesList==NULL) 
		return;
	/**********HEIGHT MAP DATA ***********************/
	chunkWriter.openDataChunk("SidesList", K_SIDES_DATA_VERSION_3);	
	
		chunkWriter.writeInt(TheSidesList->getNumSides());
		Int i;
		for (i=0; i<TheSidesList->getNumSides(); i++) {
			chunkWriter.writeDict(*TheSidesList->getSideInfo(i)->getDict());	
			BuildListInfo* pBuildList = TheSidesList->getSideInfo(i)->getBuildList();
			Int count = 0;
			while (pBuildList) {
				count++;
				pBuildList = pBuildList->getNext();
			}
			chunkWriter.writeInt(count);
			pBuildList = TheSidesList->getSideInfo(i)->getBuildList();
			while (pBuildList) {
				chunkWriter.writeAsciiString(pBuildList->getBuildingName());
				chunkWriter.writeAsciiString(pBuildList->getTemplateName());
				chunkWriter.writeReal(pBuildList->getLocation()->x);
				chunkWriter.writeReal(pBuildList->getLocation()->y);
				chunkWriter.writeReal(pBuildList->getLocation()->z);
				chunkWriter.writeReal(pBuildList->getAngle());
				chunkWriter.writeByte(pBuildList->isInitiallyBuilt());
				chunkWriter.writeInt(pBuildList->getNumRebuilds());
				// BEGIN stuff new to K_SIDES_DATA_VERSION_3
				chunkWriter.writeAsciiString(pBuildList->getScript());
				chunkWriter.writeInt(pBuildList->getHealth());
				chunkWriter.writeByte(pBuildList->getWhiner());
				chunkWriter.writeByte(pBuildList->getUnsellable());
				chunkWriter.writeByte(pBuildList->getRepairable());
				// END stuff new to K_SIDES_DATA_VERSION_3

				pBuildList = pBuildList->getNext();
			}
		}	
		
		// BEGIN stuff new to K_SIDES_DATA_VERSION_2
		chunkWriter.writeInt(TheSidesList->getNumTeams());
		for (i=0; i<TheSidesList->getNumTeams(); i++) {
			chunkWriter.writeDict(*TheSidesList->getTeamInfo(i)->getDict());	
		}
		// END stuff new to K_SIDES_DATA_VERSION_2

		ScriptList *scripts[MAX_PLAYER_COUNT];
		for (i=0; i<TheSidesList->getNumSides(); i++) {
			scripts[i] = TheSidesList->getSideInfo(i)->getScriptList();
		}
		ScriptList::WriteScriptsDataChunk(chunkWriter, scripts, TheSidesList->getNumSides());
	chunkWriter.closeDataChunk();

	Bool modified = TheSidesList->validateSides();
	DEBUG_ASSERTLOG(!modified, ("*** had to clean up sideslist on read"));
	modified = false;	// silence compiler warnings in release build
	
}

// ?findTeamInfo@SidesList@@QAEPAVTeamsInfo@@VAsciiString@@PAH@Z present-unmatched
TeamsInfo *SidesList::findTeamInfo(AsciiString name, Int* index /*= NULL*/)
{
	return m_teamrec.findTeamInfo(name, index);
}

// ?findSideInfo@SidesList@@QAEPAVSidesInfo@@VAsciiString@@PAH@Z present-unmatched
SidesInfo *SidesList::findSideInfo(AsciiString name, Int* index /*= NULL*/)
{
	for (int i = 0; i < m_numSides; i++) 
	{
		if (m_sides[i].getDict()->getAsciiString(TheKey_playerName) == name)
		{
			if (index)
				*index = i;
			return &m_sides[i];
		}
	}
	return NULL;
}

// ?findSkirmishSideInfo@SidesList@@QAEPAVSidesInfo@@VAsciiString@@PAH@Z present-unmatched
SidesInfo *SidesList::findSkirmishSideInfo(AsciiString name, Int* index /*= NULL*/)
{
	for (int i = 0; i < m_numSkirmishSides; i++) 
	{
		if (m_skirmishSides[i].getDict()->getAsciiString(TheKey_playerName) == name)
		{
			if (index)
				*index = i;
			return &m_skirmishSides[i];
		}
	}
	return NULL;
}

static AsciiString static_readPlayerNames[MAX_PLAYER_COUNT];

/**
* ParsePlayersDataChunk - read players names data chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
#define K_PLAYERS_NAMES_FOR_SCRIPTS_VERSION_1 1
#define K_PLAYERS_NAMES_FOR_SCRIPTS_VERSION_2 2

static Bool ParsePlayersDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Int readDicts = 0;
	if (info->version >= K_PLAYERS_NAMES_FOR_SCRIPTS_VERSION_2) {
		readDicts = file.readInt();
	}
	Int numNames = file.readInt();
	Int i;
	for (i=0; i<numNames; i++) {
		if (i>=MAX_PLAYER_COUNT) break;
		static_readPlayerNames[i] = file.readAsciiString();
		if (readDicts) {
			Dict sideDict = file.readDict();
		}
	}
	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Unexpected data left over."));
	return true;
}

/**
* ParseTeamsDataChunk - read teams data chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
static Bool ParseTeamsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	SidesList *sides = (SidesList *)userData;
	while (!file.atEndOfChunk()) {
		Dict teamDict = file.readDict();
		AsciiString teamName = teamDict.getAsciiString(TheKey_teamName);
		AsciiString player = teamDict.getAsciiString(TheKey_teamOwner);
		if (sides->findSkirmishSideInfo(player)) {
			// player exists, so just add it.
			sides->addSkirmishTeam(&teamDict);
			//DEBUG_LOG(("Adding team %s\n", teamName.str()));
		} else {
			//DEBUG_LOG(("Couldn't add team %s, no player %s\n", teamName.str(), player.str()));
		}
	}
	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Unexpected data left over."));
	return true;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/SidesList_prepareForMP_or_SkirmishMethodThunk.cpp
// ?prepareForMP_or_Skirmish@SidesList@@QAEXXZ present-unmatched
void SidesList::prepareForMP_or_Skirmish(void)
{
	m_skirmishTeamrec.clear();
	Int i;
	for (i = 0; i < getNumTeams(); i++)
	{
		Dict *tdict = getTeamInfo(i)->getDict();
		m_skirmishTeamrec.addTeam(tdict);
	}
	m_teamrec.clear();

	for (i = 0; i < MAX_PLAYER_COUNT; i++) {
		m_skirmishSides[i].clear();
	}
	m_numSkirmishSides = 0;

	for (i = 0; i < m_numSides; i++) 
	{
		m_skirmishSides[m_numSkirmishSides] = m_sides[i];
		m_numSkirmishSides++;
		if (m_sides[i].getDict()->getAsciiString(TheKey_playerFaction) == "FactionCivilian") {
			// Don't remove FactionCivilian.
			continue;
		}
		if (m_numSides == 1) break;	// can't remove the last side.
		removeSide(i);
		i--;
	}
	Bool gotScripts = false;
	for (i=0; i<m_numSkirmishSides; i++) {
		if (m_skirmishSides[i].getDict()->getAsciiString(TheKey_playerFaction) == "FactionCivilian") {
			// Don't consider FactionCivilian.
			continue;
		}
		if (m_skirmishSides[i].getScriptList()==NULL) continue;
		if (m_skirmishSides[i].getScriptList()->getScript() != NULL || 
			m_skirmishSides[i].getScriptList()->getScriptGroup()!=NULL) {
			gotScripts = true;
		}
	}
	if (!gotScripts) {
		AsciiString path = "data\\Scripts\\SkirmishScripts.scb";
		DEBUG_LOG(("Skirmish map using standard scripts\n"));
		m_skirmishTeamrec.clear();
		CachedFileInputStream theInputStream;
		if (theInputStream.open(path)) { 
				ChunkInputStream *pStrm = &theInputStream;
				DataChunkInput file( pStrm );
				file.registerParser( AsciiString("PlayerScriptsList"), AsciiString::TheEmptyString, ScriptList::ParseScriptsDataChunk );
				file.registerParser( AsciiString("ScriptsPlayers"), AsciiString::TheEmptyString, ParsePlayersDataChunk );
				file.registerParser( AsciiString("ScriptTeams"), AsciiString::TheEmptyString, ParseTeamsDataChunk );
				if (!file.parse(this)) {
					DEBUG_LOG(("ERROR - Unable to read in skirmish scripts.\n"));
					return;
				}
				ScriptList *scripts[MAX_PLAYER_COUNT];
				Int count = ScriptList::getReadScripts(scripts);
				Int i;
				for (i=0; i<count; i++) {
					Int curSide = -1;
					Int j;
					for (j=0; j<m_numSkirmishSides; j++) {
 						AsciiString name = getSkirmishSideInfo(j)->getDict()->getAsciiString(TheKey_playerName);
						if (name == static_readPlayerNames[i]) {
							curSide = j;
							break;
						}
					}
					if (curSide == -1) continue;

					ScriptList *pSL = getSkirmishSideInfo(curSide)->getScriptList();
					getSkirmishSideInfo(curSide)->setScriptList(scripts[i]);
					scripts[i] = NULL;
					if (pSL) 
						pSL->deleteInstance();
					scripts[i] = NULL;
				}
				for (i=0; i<MAX_PLAYER_COUNT; i++) {
					static_readPlayerNames[i].clear();
				}
		}


	}
}


// byte-exact reconstruction: Code/GameEngine/Source/Common/SidesList_isPlayerDefaultTeam_Thunk.cpp
// ?isPlayerDefaultTeam@SidesList@@QAE_NPAVTeamsInfo@@@Z present-unmatched
Bool SidesList::isPlayerDefaultTeam(TeamsInfo *t)
{
	// if our name is "teamfoo" and there is a player named "foo", we are a player-default team.
	AsciiString tname = t->getDict()->getAsciiString(TheKey_teamName);
	if (tname.startsWith("team"))
	{
		const char* rest = tname.str() + 4;
		for (int j = 0; j < m_numSides; j++)
		{
			AsciiString pname = m_sides[j].getDict()->getAsciiString(TheKey_playerName);
			if (strcmp(pname.str(), rest) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

// ?emptySides@SidesList@@QAEXXZ present-unmatched
void SidesList::emptySides() 
{ 
	Int i;

	m_numSides = 0; 
	m_numSkirmishSides = 0; 
	for (i = 0; i < MAX_PLAYER_COUNT; i++) {
		m_sides[i].clear(); 
		m_skirmishSides[i].clear();
	}
}

// ?emptyTeams@SidesList@@QAEXXZ present-unmatched
void SidesList::emptyTeams() 
{ 
	m_teamrec.clear();
	m_skirmishTeamrec.clear();
}

// SidesList::addSide has its exact retail body emitted by
// SidesListAddSideThunk.cpp. (Name in prose: a comment line that starts with a
// mangled name is read as a present-unmatched marker for whatever follows it.)

void SidesList::addTeam(const Dict* d)
{
	m_teamrec.addTeam(d);
}

void SidesList::addSkirmishTeam(const Dict* d)
{
	m_skirmishTeamrec.addTeam(d);
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/SidesList_removeSideMethodThunk.cpp
// ?removeSide@SidesList@@QAEXH@Z present-unmatched
void SidesList::removeSide(Int i)
{
	if (i < 0 || i >= m_numSides || m_numSides <= 1)
		return;

	for ( ; i < m_numSides-1; i++)
		m_sides[i] = m_sides[i+1];

	for ( ; i < MAX_PLAYER_COUNT; i++)
		m_sides[i].clear();

	--m_numSides;
}

void SidesList::removeTeam(Int i)
{
	m_teamrec.removeTeam(i);
}

__declspec(naked) Bool SidesList::validateAllyEnemyList(const AsciiString& tname, AsciiString& allies)
{
	__asm {
	__emit 0x6a;
	__emit 0xff;
	__emit 0x68;
	__emit 0x2e;
	__emit 0x7f;
	__emit 0x00;
	__emit 0x01;
	__emit 0x64;
	__emit 0xa1;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x50;
	__emit 0x64;
	__emit 0x89;
	__emit 0x25;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x81;
	__emit 0xec;
	__emit 0x04;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x53;
	__emit 0x55;
	__emit 0x56;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0x57;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x07;
	__emit 0x2b;
	__emit 0xe9;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x86;
	__emit 0x30;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x33;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xea;
	__emit 0xc2;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x39;
	__emit 0x7e;
	__emit 0x28;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0x52;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x6e;
	__emit 0x40;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x00;
	__emit 0xb9;
	__emit 0x18;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x5d;
	__emit 0xf0;
	__emit 0xe8;
	__emit 0x05;
	__emit 0x8f;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xcb;
	__emit 0xe8;
	__emit 0x61;
	__emit 0xfb;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x85;
	__emit 0xc0;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x01;
	__emit 0x74;
	__emit 0x67;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x04;
	__emit 0x66;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x5e;
	__emit 0x0f;
	__emit 0xb7;
	__emit 0xd1;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x08;
	__emit 0x83;
	__emit 0xfa;
	__emit 0x0c;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8b;
	__emit 0xca;
	__emit 0x7c;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x0c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xf0;
	__emit 0xbf;
	__emit 0x8c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x33;
	__emit 0xc0;
	__emit 0xf3;
	__emit 0xa6;
	__emit 0x74;
	__emit 0x05;
	__emit 0x1b;
	__emit 0xc0;
	__emit 0x83;
	__emit 0xd8;
	__emit 0xff;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x07;
	__emit 0x8d;
	__emit 0x42;
	__emit 0xf4;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x74;
	__emit 0x2b;
	__emit 0x83;
	__emit 0xfa;
	__emit 0x0a;
	__emit 0x8b;
	__emit 0xca;
	__emit 0x7c;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x74;
	__emit 0x24;
	__emit 0x20;
	__emit 0xbf;
	__emit 0x7c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x33;
	__emit 0xc0;
	__emit 0xf3;
	__emit 0xa6;
	__emit 0x74;
	__emit 0x05;
	__emit 0x1b;
	__emit 0xc0;
	__emit 0x83;
	__emit 0xd8;
	__emit 0xff;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x24;
	__emit 0x8d;
	__emit 0x42;
	__emit 0xf6;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x1d;
	__emit 0x6a;
	__emit 0x00;
	__emit 0xb9;
	__emit 0x20;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x75;
	__emit 0x8e;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xcb;
	__emit 0xe8;
	__emit 0xcd;
	__emit 0x6a;
	__emit 0xe6;
	__emit 0xff;
	__emit 0xff;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x83;
	__emit 0xc5;
	__emit 0x18;
	__emit 0xeb;
	__emit 0x77;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x55;
	__emit 0xec;
	__emit 0x8d;
	__emit 0x04;
	__emit 0x40;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0xc4;
	__emit 0x54;
	__emit 0x8d;
	__emit 0x44;
	__emit 0xc4;
	__emit 0x54;
	__emit 0x89;
	__emit 0x10;
	__emit 0x89;
	__emit 0x4d;
	__emit 0xec;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x13;
	__emit 0x89;
	__emit 0x50;
	__emit 0x04;
	__emit 0x89;
	__emit 0x0b;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x08;
	__emit 0x8b;
	__emit 0x55;
	__emit 0xf4;
	__emit 0x89;
	__emit 0x50;
	__emit 0x08;
	__emit 0x89;
	__emit 0x4d;
	__emit 0xf4;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x0c;
	__emit 0x8b;
	__emit 0x55;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x50;
	__emit 0x0c;
	__emit 0x89;
	__emit 0x4d;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x55;
	__emit 0xfc;
	__emit 0x89;
	__emit 0x50;
	__emit 0x10;
	__emit 0x89;
	__emit 0x4d;
	__emit 0xfc;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x55;
	__emit 0x00;
	__emit 0x89;
	__emit 0x50;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x04;
	__emit 0x40;
	__emit 0x89;
	__emit 0x4d;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0xc4;
	__emit 0x5c;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x05;
	__emit 0xe8;
	__emit 0xe2;
	__emit 0x7f;
	__emit 0xe9;
	__emit 0xff;
	__emit 0xff;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0xe8;
	__emit 0x85;
	__emit 0xa5;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x18;
	__emit 0x74;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x74;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x18;
	__emit 0x3b;
	__emit 0x56;
	__emit 0x28;
	__emit 0x0f;
	__emit 0x8c;
	__emit 0xb7;
	__emit 0xfe;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xb6;
	__emit 0x3c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0f;
	__emit 0xbf;
	__emit 0x1e;
	__emit 0x85;
	__emit 0xdb;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x45;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0xb0;
	__emit 0x3c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xeb;
	__emit 0xc1;
	__emit 0xe5;
	__emit 0x04;
	__emit 0x0f;
	__emit 0xbf;
	__emit 0x0c;
	__emit 0x2e;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x6a;
	__emit 0x00;
	__emit 0xb9;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x91;
	__emit 0x8d;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0x52;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x2e;
	__emit 0x0c;
	__emit 0xe8;
	__emit 0xeb;
	__emit 0xf9;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x85;
	__emit 0xc0;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x02;
	__emit 0x74;
	__emit 0x7b;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x04;
	__emit 0x66;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x72;
	__emit 0x0f;
	__emit 0xb7;
	__emit 0xd1;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x08;
	__emit 0x83;
	__emit 0xfa;
	__emit 0x0c;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0xca;
	__emit 0x7c;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x0c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x74;
	__emit 0x24;
	__emit 0x10;
	__emit 0xbf;
	__emit 0x8c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x33;
	__emit 0xc0;
	__emit 0xf3;
	__emit 0xa6;
	__emit 0x74;
	__emit 0x05;
	__emit 0x1b;
	__emit 0xc0;
	__emit 0x83;
	__emit 0xd8;
	__emit 0xff;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x07;
	__emit 0x8d;
	__emit 0x42;
	__emit 0xf4;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x74;
	__emit 0x3d;
	__emit 0x83;
	__emit 0xfa;
	__emit 0x0a;
	__emit 0x8b;
	__emit 0xca;
	__emit 0x7c;
	__emit 0x05;
	__emit 0xb9;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x74;
	__emit 0x24;
	__emit 0x10;
	__emit 0xbf;
	__emit 0x7c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x33;
	__emit 0xc0;
	__emit 0xf3;
	__emit 0xa6;
	__emit 0x74;
	__emit 0x05;
	__emit 0x1b;
	__emit 0xc0;
	__emit 0x83;
	__emit 0xd8;
	__emit 0xff;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x07;
	__emit 0x8d;
	__emit 0x42;
	__emit 0xf6;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x74;
	__emit 0x12;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x53;
	__emit 0x81;
	__emit 0xc1;
	__emit 0x30;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xed;
	__emit 0xf7;
	__emit 0xe6;
	__emit 0xff;
	__emit 0xeb;
	__emit 0x65;
	__emit 0x53;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x7d;
	__emit 0x07;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x84;
	__emit 0x24;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x34;
	__emit 0x28;
	__emit 0x8d;
	__emit 0x4e;
	__emit 0x0c;
	__emit 0xe8;
	__emit 0x1a;
	__emit 0x39;
	__emit 0xe9;
	__emit 0xff;
	__emit 0x0f;
	__emit 0xbf;
	__emit 0x0e;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x56;
	__emit 0x02;
	__emit 0x8b;
	__emit 0x84;
	__emit 0x24;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc1;
	__emit 0xe1;
	__emit 0x04;
	__emit 0x66;
	__emit 0x89;
	__emit 0x54;
	__emit 0x01;
	__emit 0x02;
	__emit 0x0f;
	__emit 0xbf;
	__emit 0x4e;
	__emit 0x02;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0x84;
	__emit 0x24;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc1;
	__emit 0xe1;
	__emit 0x04;
	__emit 0x66;
	__emit 0x89;
	__emit 0x14;
	__emit 0x01;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x72;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0xff;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x70;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x89;
	__emit 0x0e;
	__emit 0x66;
	__emit 0x89;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x72;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x18;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xb9;
	__emit 0x72;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x85;
	__emit 0xdb;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xc1;
	__emit 0xfe;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x8c;
	__emit 0x70;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x0d;
	__emit 0x8b;
	__emit 0x11;
	__emit 0xff;
	__emit 0x52;
	__emit 0x34;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xcc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x33;
	__emit 0xff;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0xbe;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x74;
	__emit 0x24;
	__emit 0x58;
	__emit 0xbb;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x49;
	__emit 0x00;
	__emit 0xb9;
	__emit 0x88;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x3a;
	__emit 0x8c;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xe8;
	__emit 0x06;
	__emit 0xe9;
	__emit 0xe7;
	__emit 0xff;
	__emit 0x3b;
	__emit 0xc3;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x88;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x00;
	__emit 0xb9;
	__emit 0x38;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x1e;
	__emit 0x8c;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xe8;
	__emit 0x7a;
	__emit 0xf8;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x88;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x74;
	__emit 0x05;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x08;
	__emit 0xeb;
	__emit 0x05;
	__emit 0xb8;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x07;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x00;
	__emit 0xd6;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x50;
	__emit 0xe8;
	__emit 0xbf;
	__emit 0xa6;
	__emit 0xe9;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x50;
	__emit 0xd7;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x50;
	__emit 0xe8;
	__emit 0x67;
	__emit 0xc6;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x74;
	__emit 0x29;
	__emit 0x8b;
	__emit 0x88;
	__emit 0x0c;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x05;
	__emit 0x0c;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x1a;
	__emit 0x66;
	__emit 0x83;
	__emit 0x79;
	__emit 0x04;
	__emit 0x00;
	__emit 0x74;
	__emit 0x13;
	__emit 0x50;
	__emit 0xb9;
	__emit 0x88;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0xbb;
	__emit 0x8b;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xe8;
	__emit 0x3f;
	__emit 0xa8;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xde;
	__emit 0x71;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x47;
	__emit 0x83;
	__emit 0xc6;
	__emit 0x18;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x0f;
	__emit 0x8c;
	__emit 0x4e;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x6a;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x18;
	__emit 0xe8;
	__emit 0x50;
	__emit 0x27;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x68;
	__emit 0x6c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x04;
	__emit 0xe8;
	__emit 0x2d;
	__emit 0x84;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x51;
	__emit 0xb9;
	__emit 0x18;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x05;
	__emit 0xe8;
	__emit 0x5a;
	__emit 0x8b;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0xdc;
	__emit 0xa7;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x04;
	__emit 0xe8;
	__emit 0x7b;
	__emit 0x71;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x01;
	__emit 0xb9;
	__emit 0x20;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x33;
	__emit 0x8b;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x89;
	__emit 0x67;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x68;
	__emit 0x54;
	__emit 0x6e;
	__emit 0x33;
	__emit 0x01;
	__emit 0xb9;
	__emit 0x30;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x1a;
	__emit 0x8b;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x93;
	__emit 0x79;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x68;
	__emit 0x58;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xe8;
	__emit 0xbe;
	__emit 0x83;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x10;
	__emit 0x52;
	__emit 0xb9;
	__emit 0x38;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x06;
	__emit 0xe8;
	__emit 0xeb;
	__emit 0x8a;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x6d;
	__emit 0xa7;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x04;
	__emit 0xe8;
	__emit 0x0c;
	__emit 0x71;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x68;
	__emit 0x50;
	__emit 0x6e;
	__emit 0x33;
	__emit 0x01;
	__emit 0xb9;
	__emit 0x40;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0xc1;
	__emit 0x8a;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x43;
	__emit 0xa7;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x68;
	__emit 0x50;
	__emit 0x6e;
	__emit 0x33;
	__emit 0x01;
	__emit 0xb9;
	__emit 0x48;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0xa8;
	__emit 0x8a;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x2a;
	__emit 0xa7;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x68;
	__emit 0x40;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xe8;
	__emit 0x4c;
	__emit 0x83;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x50;
	__emit 0xb9;
	__emit 0x88;
	__emit 0x79;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x07;
	__emit 0xe8;
	__emit 0x79;
	__emit 0x8a;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0xfb;
	__emit 0xa6;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x04;
	__emit 0xe8;
	__emit 0x9a;
	__emit 0x70;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x20;
	__emit 0x0f;
	__emit 0x8d;
	__emit 0x9c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0x8d;
	__emit 0x3c;
	__emit 0x49;
	__emit 0x40;
	__emit 0x8d;
	__emit 0x7c;
	__emit 0xfc;
	__emit 0x54;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x6a;
	__emit 0x01;
	__emit 0xff;
	__emit 0x12;
	__emit 0x8d;
	__emit 0x4f;
	__emit 0x04;
	__emit 0xc7;
	__emit 0x07;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0xe8;
	__emit 0x67;
	__emit 0x36;
	__emit 0xe9;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x08;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x01;
	__emit 0xff;
	__emit 0x10;
	__emit 0xc7;
	__emit 0x47;
	__emit 0x08;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x77;
	__emit 0x0c;
	__emit 0x8b;
	__emit 0xc1;
	__emit 0x2b;
	__emit 0xc1;
	__emit 0xc1;
	__emit 0xf8;
	__emit 0x02;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x7e;
	__emit 0x1d;
	__emit 0x8b;
	__emit 0xe9;
	__emit 0x2b;
	__emit 0xee;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x0c;
	__emit 0x2e;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xe8;
	__emit 0x75;
	__emit 0x73;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x83;
	__emit 0xc6;
	__emit 0x04;
	__emit 0x4b;
	__emit 0x75;
	__emit 0xef;
	__emit 0x8b;
	__emit 0x5f;
	__emit 0x10;
	__emit 0x3b;
	__emit 0xf3;
	__emit 0x8b;
	__emit 0xee;
	__emit 0x74;
	__emit 0x14;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xcd;
	__emit 0xe8;
	__emit 0x09;
	__emit 0x70;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x83;
	__emit 0xc5;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xeb;
	__emit 0x75;
	__emit 0xf2;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x14;
	__emit 0x52;
	__emit 0x89;
	__emit 0x77;
	__emit 0x10;
	__emit 0xe8;
	__emit 0x17;
	__emit 0x4c;
	__emit 0xea;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xe8;
	__emit 0xee;
	__emit 0x35;
	__emit 0xe9;
	__emit 0xff;
	__emit 0x68;
	__emit 0x1c;
	__emit 0x3e;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x28;
	__emit 0xe8;
	__emit 0x5a;
	__emit 0x82;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x0d;
	__emit 0xb3;
	__emit 0x08;
	__emit 0x68;
	__emit 0x6c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x88;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xe1;
	__emit 0x73;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0x50;
	__emit 0xb9;
	__emit 0xb8;
	__emit 0x75;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x76;
	__emit 0x89;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0xf8;
	__emit 0xa5;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x68;
	__emit 0x6c;
	__emit 0xc2;
	__emit 0x09;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xe8;
	__emit 0x1a;
	__emit 0x82;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x51;
	__emit 0xb9;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x09;
	__emit 0xe8;
	__emit 0x47;
	__emit 0x89;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0xc9;
	__emit 0xa5;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x88;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x69;
	__emit 0x6f;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x01;
	__emit 0xb9;
	__emit 0xc8;
	__emit 0x75;
	__emit 0x2a;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x21;
	__emit 0x89;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0x77;
	__emit 0x65;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x14;
	__emit 0x52;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xc9;
	__emit 0x53;
	__emit 0xea;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x28;
	__emit 0xe8;
	__emit 0xb8;
	__emit 0xdb;
	__emit 0xe7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x33;
	__emit 0xf6;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x7e;
	__emit 0x1b;
	__emit 0x8d;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x8b;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x05;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x7a;
	__emit 0xe9;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x46;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x18;
	__emit 0x3b;
	__emit 0xf0;
	__emit 0x7c;
	__emit 0xe9;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xa0;
	__emit 0x19;
	__emit 0xe6;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x89;
	__emit 0x82;
	__emit 0x2c;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x68;
	__emit 0x8d;
	__emit 0x8a;
	__emit 0x44;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0xbf;
	__emit 0x20;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x71;
	__emit 0xec;
	__emit 0x8b;
	__emit 0x58;
	__emit 0xec;
	__emit 0x89;
	__emit 0x59;
	__emit 0xec;
	__emit 0x89;
	__emit 0x70;
	__emit 0xec;
	__emit 0x8b;
	__emit 0x71;
	__emit 0xf0;
	__emit 0x8b;
	__emit 0x58;
	__emit 0xf0;
	__emit 0x89;
	__emit 0x59;
	__emit 0xf0;
	__emit 0x89;
	__emit 0x70;
	__emit 0xf0;
	__emit 0x8b;
	__emit 0x71;
	__emit 0xf4;
	__emit 0x8b;
	__emit 0x58;
	__emit 0xf4;
	__emit 0x89;
	__emit 0x59;
	__emit 0xf4;
	__emit 0x89;
	__emit 0x70;
	__emit 0xf4;
	__emit 0x8b;
	__emit 0x71;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x58;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x59;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x70;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0x71;
	__emit 0xfc;
	__emit 0x8b;
	__emit 0x58;
	__emit 0xfc;
	__emit 0x89;
	__emit 0x59;
	__emit 0xfc;
	__emit 0x89;
	__emit 0x70;
	__emit 0xfc;
	__emit 0x8b;
	__emit 0x31;
	__emit 0x8b;
	__emit 0x18;
	__emit 0x89;
	__emit 0x19;
	__emit 0x89;
	__emit 0x30;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x18;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x18;
	__emit 0x4f;
	__emit 0x75;
	__emit 0xb3;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x4c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x4c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x58;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x50;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x50;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x58;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x58;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x68;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x5c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x68;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x60;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x60;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x70;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x64;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x72;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x70;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x8b;
	__emit 0x82;
	__emit 0x66;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x66;
	__emit 0x89;
	__emit 0x8a;
	__emit 0x66;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x66;
	__emit 0x89;
	__emit 0x84;
	__emit 0x24;
	__emit 0x72;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x04;
	__emit 0xe8;
	__emit 0xcf;
	__emit 0x6d;
	__emit 0x6e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xf3;
	__emit 0x38;
	__emit 0xe7;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x28;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0x17;
	__emit 0x2d;
	__emit 0xe8;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5f;
	__emit 0x5e;
	__emit 0x5d;
	__emit 0x5b;
	__emit 0x64;
	__emit 0x89;
	__emit 0x0d;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x81;
	__emit 0xc4;
	__emit 0x10;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc3;
	}
#if 0
		// owners/allies/enemies must be players.

	Bool modified = false;

	AsciiString str, newstr, token;
	
	str = allies;
	newstr.clear();
	while (str.nextToken(&token))
	{
		if (token == tname)
		{
			modified = true;
			continue;	// no allies/enemies with self
		}

		SidesInfo *si = findSideInfo(token);
		if (!si)
		{
			modified = true;
			continue;	// player not found.
		}

		if (!newstr.isEmpty())
			newstr.concat(" ");
		newstr.concat(token);
	}

	allies = newstr;
	return modified;
#endif
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/SidesList_addPlayerByTemplateMethodThunk.cpp
// ?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z present-unmatched
void SidesList::addPlayerByTemplate(AsciiString playerTemplateName)
{
	AsciiString playerName;
	UnicodeString playerDisplayName;
	Bool isHuman = false;

	if (playerTemplateName.isEmpty())
	{
		playerName.set("");	// magic code for "neutral"
		playerDisplayName = L"Neutral";
		isHuman = false;
	}
	else
	{
		playerName.set("Plyr");
		if (playerTemplateName.startsWith("Faction"))
		{
			playerName.concat(playerTemplateName.str() + 7);
		}
		else
		{
			playerName.concat(playerTemplateName);
		}
		playerDisplayName.translate(playerName);
		isHuman = true;
		// special-case "civilian"...
		if (playerName == "PlyrCivilian")
			isHuman = false;
	}

	Dict d;

	d.clear();
	d.setAsciiString(TheKey_playerName, playerName);	
	d.setBool(TheKey_playerIsHuman, isHuman);
	d.setUnicodeString(TheKey_playerDisplayName, playerDisplayName);
	d.setAsciiString(TheKey_playerFaction, playerTemplateName);
	d.setAsciiString(TheKey_playerAllies, AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerEnemies, AsciiString::TheEmptyString);

	addSide(&d);

	AsciiString playerTeamName;
	playerTeamName.set("team");
	playerTeamName.concat(playerName);

	d.clear();
	d.setAsciiString(TheKey_teamName, playerTeamName);
	d.setAsciiString(TheKey_teamOwner, playerName);
	d.setBool(TheKey_teamIsSingleton, true);
	addTeam(&d);
}

// ?validateSides@SidesList@@QAE_NXZ matched 1810 bytes (Open-BFME5)
__declspec(naked) Bool SidesList::validateSides()
{
	__asm
	{
		__emit 0x6a;
		__emit 0xff;
		__emit 0x68;
		__emit 0x10;
		__emit 0x78;
		__emit 0x00;
		__emit 0x01;
		__emit 0x64;
		__emit 0xa1;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0x64;
		__emit 0x89;
		__emit 0x25;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xec;
		__emit 0x38;
		__emit 0x53;
		__emit 0x55;
		__emit 0x56;
		__emit 0x8b;
		__emit 0xd9;
		__emit 0x57;
		__emit 0x8b;
		__emit 0x7b;
		__emit 0x28;
		__emit 0x33;
		__emit 0xed;
		__emit 0x3b;
		__emit 0xfd;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x18;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x8e;
		__emit 0xa2;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x43;
		__emit 0x2c;
		__emit 0x89;
		__emit 0x44;
		__emit 0x24;
		__emit 0x24;
		__emit 0xeb;
		__emit 0x03;
		__emit 0x8d;
		__emit 0x49;
		__emit 0x00;
		__emit 0x85;
		__emit 0xed;
		__emit 0x7c;
		__emit 0x0b;
		__emit 0x3b;
		__emit 0x6b;
		__emit 0x28;
		__emit 0x7d;
		__emit 0x06;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x24;
		__emit 0xeb;
		__emit 0x02;
		__emit 0x33;
		__emit 0xc0;
		__emit 0x8d;
		__emit 0x70;
		__emit 0x04;
		__emit 0x85;
		__emit 0xf6;
		__emit 0x74;
		__emit 0x3b;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x13;
		__emit 0x51;
		__emit 0xb9;
		__emit 0x18;
		__emit 0x79;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x7d;
		__emit 0xc9;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x40;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xd9;
		__emit 0x35;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x18;
		__emit 0x8b;
		__emit 0x00;
		__emit 0x83;
		__emit 0xca;
		__emit 0x01;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x89;
		__emit 0x54;
		__emit 0x24;
		__emit 0x18;
		__emit 0x74;
		__emit 0x07;
		__emit 0x66;
		__emit 0x83;
		__emit 0x78;
		__emit 0x04;
		__emit 0x00;
		__emit 0x75;
		__emit 0x07;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x12;
		__emit 0x01;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x12;
		__emit 0x00;
		__emit 0xf6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x18;
		__emit 0x01;
		__emit 0x74;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x18;
		__emit 0x83;
		__emit 0xe0;
		__emit 0xfe;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0x89;
		__emit 0x44;
		__emit 0x24;
		__emit 0x18;
		__emit 0xe8;
		__emit 0x6d;
		__emit 0xaf;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8a;
		__emit 0x44;
		__emit 0x24;
		__emit 0x12;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x16;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x45;
		__emit 0x83;
		__emit 0xc1;
		__emit 0x18;
		__emit 0x3b;
		__emit 0xef;
		__emit 0x89;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x0f;
		__emit 0x8c;
		__emit 0x71;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xeb;
		__emit 0x05;
		__emit 0x83;
		__emit 0xfd;
		__emit 0xff;
		__emit 0x75;
		__emit 0x1d;
		__emit 0x51;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x48;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x68;
		__emit 0x50;
		__emit 0x6e;
		__emit 0x33;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x59;
		__emit 0xb1;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xe8;
		__emit 0x20;
		__emit 0xbf;
		__emit 0xe9;
		__emit 0xff;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x43;
		__emit 0x28;
		__emit 0x33;
		__emit 0xc9;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x89;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x0f;
		__emit 0x8e;
		__emit 0x9c;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x53;
		__emit 0x2c;
		__emit 0x89;
		__emit 0x54;
		__emit 0x24;
		__emit 0x34;
		__emit 0xeb;
		__emit 0x04;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x33;
		__emit 0xff;
		__emit 0x3b;
		__emit 0xcf;
		__emit 0x7c;
		__emit 0x0a;
		__emit 0x3b;
		__emit 0xc8;
		__emit 0x7d;
		__emit 0x06;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x34;
		__emit 0xeb;
		__emit 0x02;
		__emit 0x33;
		__emit 0xc0;
		__emit 0x8d;
		__emit 0x70;
		__emit 0x04;
		__emit 0x57;
		__emit 0xb9;
		__emit 0x18;
		__emit 0x79;
		__emit 0x2a;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x48;
		__emit 0xe8;
		__emit 0xaf;
		__emit 0xc8;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x0b;
		__emit 0x35;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x68;
		__emit 0x1c;
		__emit 0x3e;
		__emit 0x08;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0x89;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x54;
		__emit 0xe8;
		__emit 0x4c;
		__emit 0xc1;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x3b;
		__emit 0xc7;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x01;
		__emit 0x74;
		__emit 0x09;
		__emit 0x0f;
		__emit 0xb7;
		__emit 0x48;
		__emit 0x04;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x07;
		__emit 0x33;
		__emit 0xc9;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x51;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0xe8;
		__emit 0xc4;
		__emit 0xb2;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x18;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x40;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xbd;
		__emit 0xd0;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x8d;
		__emit 0xb3;
		__emit 0x30;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x58;
		__emit 0x02;
		__emit 0xe8;
		__emit 0x60;
		__emit 0x8b;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x61;
		__emit 0xae;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x3b;
		__emit 0xef;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x5d;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x39;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x20;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x53;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x57;
		__emit 0xb9;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x08;
		__emit 0xc8;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x44;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xcd;
		__emit 0xe8;
		__emit 0x64;
		__emit 0x34;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0x3b;
		__emit 0xcf;
		__emit 0x74;
		__emit 0x0d;
		__emit 0x0f;
		__emit 0xb7;
		__emit 0x79;
		__emit 0x04;
		__emit 0x89;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x28;
		__emit 0x8d;
		__emit 0x71;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x09;
		__emit 0x89;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xbe;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x00;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x06;
		__emit 0x0f;
		__emit 0xb7;
		__emit 0x50;
		__emit 0x04;
		__emit 0xeb;
		__emit 0x02;
		__emit 0x33;
		__emit 0xd2;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x3b;
		__emit 0xd7;
		__emit 0x8b;
		__emit 0xca;
		__emit 0x7c;
		__emit 0x02;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0x8b;
		__emit 0xfe;
		__emit 0x8b;
		__emit 0xf0;
		__emit 0x33;
		__emit 0xc0;
		__emit 0xf3;
		__emit 0xa6;
		__emit 0x74;
		__emit 0x05;
		__emit 0x1b;
		__emit 0xc0;
		__emit 0x83;
		__emit 0xd8;
		__emit 0xff;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x08;
		__emit 0x2b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc2;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x0f;
		__emit 0x95;
		__emit 0x44;
		__emit 0x24;
		__emit 0x12;
		__emit 0xe8;
		__emit 0xcc;
		__emit 0xad;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8a;
		__emit 0x44;
		__emit 0x24;
		__emit 0x12;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x8d;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0xb8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x78;
		__emit 0xc7;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x48;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcd;
		__emit 0xe8;
		__emit 0xd4;
		__emit 0x33;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xf8;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x20;
		__emit 0x8d;
		__emit 0xb3;
		__emit 0x30;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x54;
		__emit 0x03;
		__emit 0xe8;
		__emit 0xe5;
		__emit 0x41;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x0c;
		__emit 0xc1;
		__emit 0xe1;
		__emit 0x04;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x14;
		__emit 0x8d;
		__emit 0x74;
		__emit 0x01;
		__emit 0x0c;
		__emit 0x52;
		__emit 0xb9;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x35;
		__emit 0xc7;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xb9;
		__emit 0xe3;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x57;
		__emit 0xb9;
		__emit 0xb8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x22;
		__emit 0xc7;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xa6;
		__emit 0xe3;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x20;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x8b;
		__emit 0x30;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xf4;
		__emit 0x5a;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x40;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x38;
		__emit 0xad;
		__emit 0x6e;
		__emit 0x00;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xeb;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xcd;
		__emit 0xe8;
		__emit 0xfc;
		__emit 0x6d;
		__emit 0xea;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x91;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0x01;
		__emit 0xb9;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xcf;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xcd;
		__emit 0xe8;
		__emit 0x27;
		__emit 0xa3;
		__emit 0xe6;
		__emit 0xff;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0xeb;
		__emit 0x76;
		__emit 0x57;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0xe8;
		__emit 0x7f;
		__emit 0x62;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x51;
		__emit 0xb9;
		__emit 0xb8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x54;
		__emit 0x04;
		__emit 0xe8;
		__emit 0xa2;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0xe8;
		__emit 0x24;
		__emit 0xe3;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x14;
		__emit 0x52;
		__emit 0xb9;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x89;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0xe8;
		__emit 0x0b;
		__emit 0xe3;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x01;
		__emit 0xb9;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x73;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0xe8;
		__emit 0xc9;
		__emit 0xa2;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x20;
		__emit 0x91;
		__emit 0xea;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xbb;
		__emit 0x77;
		__emit 0xe7;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0x48;
		__emit 0x79;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x3e;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x74;
		__emit 0x24;
		__emit 0x48;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x96;
		__emit 0x32;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0x40;
		__emit 0x79;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x54;
		__emit 0x05;
		__emit 0xe8;
		__emit 0x1c;
		__emit 0xc6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x34;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x78;
		__emit 0x32;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x30;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x58;
		__emit 0x06;
		__emit 0xe8;
		__emit 0x8c;
		__emit 0x3a;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x1c;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x30;
		__emit 0x52;
		__emit 0xb9;
		__emit 0x48;
		__emit 0x79;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xe6;
		__emit 0xc5;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x6a;
		__emit 0xe2;
		__emit 0xe8;
		__emit 0xff;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x2c;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xe8;
		__emit 0x5b;
		__emit 0x3a;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x1c;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x2c;
		__emit 0x52;
		__emit 0xb9;
		__emit 0x40;
		__emit 0x79;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xb5;
		__emit 0xc5;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x39;
		__emit 0xe2;
		__emit 0xe8;
		__emit 0xff;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x05;
		__emit 0xe8;
		__emit 0xd6;
		__emit 0xab;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x30;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xc8;
		__emit 0xab;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xba;
		__emit 0xab;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0xa9;
		__emit 0xab;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x8b;
		__emit 0x74;
		__emit 0x24;
		__emit 0x34;
		__emit 0x8b;
		__emit 0x43;
		__emit 0x28;
		__emit 0x41;
		__emit 0x83;
		__emit 0xc6;
		__emit 0x18;
		__emit 0x3b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x34;
		__emit 0x0f;
		__emit 0x8c;
		__emit 0x77;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0xeb;
		__emit 0x08;
		__emit 0x8d;
		__emit 0xa4;
		__emit 0x24;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x90;
		__emit 0x8b;
		__emit 0x83;
		__emit 0x3c;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0f;
		__emit 0xbf;
		__emit 0x28;
		__emit 0x8d;
		__emit 0xa4;
		__emit 0x24;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x85;
		__emit 0xed;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x8b;
		__emit 0x3c;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xc5;
		__emit 0xc1;
		__emit 0xe0;
		__emit 0x04;
		__emit 0x0f;
		__emit 0xbf;
		__emit 0x3c;
		__emit 0x08;
		__emit 0x8d;
		__emit 0x74;
		__emit 0x08;
		__emit 0x0c;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0xb8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x0d;
		__emit 0xc5;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x69;
		__emit 0x31;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x4c;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x52;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x5c;
		__emit 0x07;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x41;
		__emit 0xad;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xe8;
		__emit 0x93;
		__emit 0xa6;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x15;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0x8b;
		__emit 0xef;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x03;
		__emit 0xab;
		__emit 0x6e;
		__emit 0x00;
		__emit 0xeb;
		__emit 0x91;
		__emit 0x8d;
		__emit 0xbb;
		__emit 0x30;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x55;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0x4a;
		__emit 0x3f;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x0c;
		__emit 0x8b;
		__emit 0xf5;
		__emit 0xc1;
		__emit 0xe6;
		__emit 0x04;
		__emit 0x03;
		__emit 0xf0;
		__emit 0x8d;
		__emit 0x4e;
		__emit 0x0c;
		__emit 0xe8;
		__emit 0xe7;
		__emit 0x70;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x0f;
		__emit 0xbf;
		__emit 0x0e;
		__emit 0x66;
		__emit 0x8b;
		__emit 0x56;
		__emit 0x02;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x0c;
		__emit 0xc1;
		__emit 0xe1;
		__emit 0x04;
		__emit 0x66;
		__emit 0x89;
		__emit 0x54;
		__emit 0x01;
		__emit 0x02;
		__emit 0x0f;
		__emit 0xbf;
		__emit 0x4e;
		__emit 0x02;
		__emit 0x66;
		__emit 0x8b;
		__emit 0x16;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x0c;
		__emit 0xc1;
		__emit 0xe1;
		__emit 0x04;
		__emit 0x66;
		__emit 0x89;
		__emit 0x14;
		__emit 0x01;
		__emit 0x66;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x1a;
		__emit 0x66;
		__emit 0xff;
		__emit 0x4f;
		__emit 0x18;
		__emit 0x66;
		__emit 0x89;
		__emit 0x06;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0x66;
		__emit 0x89;
		__emit 0x6f;
		__emit 0x1a;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x99;
		__emit 0xaa;
		__emit 0x6e;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x14;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x83;
		__emit 0x3c;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0f;
		__emit 0xbf;
		__emit 0x28;
		__emit 0x85;
		__emit 0xed;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x5a;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc1;
		__emit 0xe5;
		__emit 0x04;
		__emit 0x66;
		__emit 0x83;
		__emit 0x7c;
		__emit 0x28;
		__emit 0x06;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x35;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0xb8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x74;
		__emit 0x28;
		__emit 0x0c;
		__emit 0xe8;
		__emit 0x24;
		__emit 0xc4;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x80;
		__emit 0x30;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xb9;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x54;
		__emit 0x08;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x03;
		__emit 0xc4;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x30;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x5f;
		__emit 0x30;
		__emit 0xe9;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x30;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x4c;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x50;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x5c;
		__emit 0x09;
		__emit 0xe8;
		__emit 0x3a;
		__emit 0xac;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xe8;
		__emit 0x8c;
		__emit 0xa5;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x5d;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x20;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x0d;
		__emit 0x0f;
		__emit 0xb7;
		__emit 0x48;
		__emit 0x04;
		__emit 0x89;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0x8d;
		__emit 0x78;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x11;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x34;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0xbf;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x28;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x09;
		__emit 0x0f;
		__emit 0xb7;
		__emit 0x50;
		__emit 0x04;
		__emit 0x8d;
		__emit 0x70;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x07;
		__emit 0x33;
		__emit 0xd2;
		__emit 0xbe;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x3b;
		__emit 0xd1;
		__emit 0x7d;
		__emit 0x02;
		__emit 0x8b;
		__emit 0xca;
		__emit 0x33;
		__emit 0xc0;
		__emit 0xf3;
		__emit 0xa6;
		__emit 0x74;
		__emit 0x05;
		__emit 0x1b;
		__emit 0xc0;
		__emit 0x83;
		__emit 0xd8;
		__emit 0xff;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x62;
		__emit 0x2b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x34;
		__emit 0x8b;
		__emit 0xc2;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x58;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x8d;
		__emit 0xb3;
		__emit 0x30;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xf7;
		__emit 0x3d;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x0c;
		__emit 0x68;
		__emit 0x50;
		__emit 0x6e;
		__emit 0x33;
		__emit 0x01;
		__emit 0xb9;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x7c;
		__emit 0x28;
		__emit 0x0c;
		__emit 0xe8;
		__emit 0x4e;
		__emit 0xc3;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0xd2;
		__emit 0xdf;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x20;
		__emit 0x52;
		__emit 0xb9;
		__emit 0xb8;
		__emit 0x75;
		__emit 0x2a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x37;
		__emit 0xc3;
		__emit 0xe6;
		__emit 0xff;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0xbb;
		__emit 0xdf;
		__emit 0xe8;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x18;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x0d;
		__emit 0x57;
		__emit 0xe6;
		__emit 0xff;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xc6;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x4c;
		__emit 0xa9;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x50;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x3b;
		__emit 0xa9;
		__emit 0x6e;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x83;
		__emit 0x3c;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0f;
		__emit 0xbf;
		__emit 0x2c;
		__emit 0x28;
		__emit 0x85;
		__emit 0xed;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xa6;
		__emit 0xfe;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x48;
		__emit 0x8a;
		__emit 0x44;
		__emit 0x24;
		__emit 0x11;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x64;
		__emit 0x89;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5b;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x44;
		__emit 0xc3;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SidesList@@MAEXPAVXfer@@@Z present-unmatched
void SidesList::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method 
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@SidesList@@MAEXPAVXfer@@@Z present-unmatched
void SidesList::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// xfer num sides
	Int sideCount = getNumSides();
	xfer->xferInt( &sideCount );
	if( sideCount != getNumSides() )
	{

		DEBUG_CRASH(( "SidesList::xfer - The sides list size has changed, this was not supposed to happen, you must version this method and figure out how to translate between old and new versions now\n" ));
		throw SC_INVALID_DATA;

	}  // end if

	// side data
	ScriptList *scriptList;
	Bool scriptListPresent;
	for( Int i = 0; i < sideCount; ++i )
	{

		// xfer script list data that can change
		scriptList = getSideInfo( i )->getScriptList();
		scriptListPresent = scriptList ? TRUE : FALSE;
		xfer->xferBool( &scriptListPresent );
		if( (scriptList == NULL && scriptListPresent == TRUE) ||
				(scriptList != NULL && scriptListPresent == FALSE) )
		{

			DEBUG_CRASH(( "SidesList::xfer - script list missing/present mismatch\n" ));
			throw SC_INVALID_DATA;

		}  // end if
		if( scriptListPresent )
			xfer->xferSnapshot( scriptList );

	}  // end for i

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SidesList@@MAEXXZ present-unmatched
void SidesList::loadPostProcess( void )
{

}  // end loadPostProcess

/* ********* BuildListInfo class ****************************/
/**
 BuildListInfo - Constructor.
*/
// ??0BuildListInfo@@QAE@XZ present-unmatched
BuildListInfo::BuildListInfo(void) :
m_nextBuildList(NULL),
m_renderObj(NULL),
m_shadowObj(NULL),
m_isInitiallyBuilt(false),
m_numRebuilds(0),
m_angle(0),
m_script(AsciiString::TheEmptyString),
m_health(100),
m_whiner(true),
m_unsellable(false),
m_repairable(true),
m_objectID(INVALID_ID),
m_objectTimestamp(0),
m_underConstruction(false),
m_isSupplyBuilding(false),
m_desiredGatherers(0),
m_currentGatherers(0),
m_automaticallyBuild(true),
m_priorityBuild(false),
m_buildingName(AsciiString::TheEmptyString)
{
	// Added by Sadullah Nader
	// these initialized values are necessary!!!
	m_location.zero();
	m_rallyPointOffset.x = 0.0f;
	m_rallyPointOffset.y = 0.0f;
	m_selected = FALSE;

	Int i;
	for (i=0; i<MAX_RESOURCE_GATHERERS; i++) 
	{
		m_resourceGatherers[i] = INVALID_ID;
	}
}


/**
 BuildListInfo - Destructor - note - if linked, deletes linked items.
*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/BuildListInfoDestructorThunk.cpp
// ??1BuildListInfo@@MAE@XZ present-unmatched
BuildListInfo::~BuildListInfo(void)
{
	if (m_nextBuildList) {
		BuildListInfo *cur = m_nextBuildList;
		BuildListInfo *next;
		while (cur) {
			next = cur->getNext();
			cur->setNextBuildList(NULL); // prevents recursion. 
			cur->deleteInstance();
			cur = next; 
		}
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/BuildListInfo_parseStructureMethodThunk.cpp
// ?parseStructure@BuildListInfo@@ present-unmatched
void BuildListInfo::parseStructure(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	const char* c = ini->getNextToken();
	AsciiString tTemplateName(c);

	static const FieldParse myFieldParse[] = 
		{
			{ "Name",				INI::parseAsciiString,		NULL, offsetof( BuildListInfo, m_buildingName	 ) },
			{ "Location",		INI::parseCoord2D,				NULL, offsetof( BuildListInfo, m_location ) },
      { "Rebuilds",		INI::parseInt,						NULL, offsetof( BuildListInfo, m_numRebuilds ) },
      { "Angle",			INI::parseAngleReal,			NULL, offsetof( BuildListInfo, m_angle ) },
      { "InitiallyBuilt",			INI::parseBool,		NULL, offsetof( BuildListInfo, m_isInitiallyBuilt ) },
      { "RallyPointOffset",			INI::parseCoord2D,		NULL, offsetof( BuildListInfo, m_rallyPointOffset ) },
      { "AutomaticallyBuild",			INI::parseBool,	NULL, offsetof( BuildListInfo, m_automaticallyBuild ) },
			{ NULL,							NULL,											NULL, 0 }  // keep this last
		};

	BuildListInfo *buildInfo = newInstance( BuildListInfo );
	buildInfo->setTemplateName(tTemplateName);
	ini->initFromINI(buildInfo, myFieldParse);
	((AISideBuildList*)instance)->addInfo(buildInfo);
}


/**
 BuildListInfo - Duplicate - note - if linked, duplicates linked items.
*/
BuildListInfo *BuildListInfo::duplicate(void)
{
	BuildListInfo *first = newInstance( BuildListInfo );
	*first = *this;
	first->m_nextBuildList = NULL;
	BuildListInfo *next = this->m_nextBuildList;
	BuildListInfo *cur = first;
	while (next) {
		BuildListInfo *link = newInstance( BuildListInfo );
		*link = *next;
		link->m_nextBuildList = NULL;
		cur->m_nextBuildList = link;
		cur = link;
		next = next->m_nextBuildList;
	}
	return first;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BuildListInfo@@MAEXPAVXfer@@@Z present-unmatched
void BuildListInfo::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@BuildListInfo@@MAEXPAVXfer@@@Z present-unmatched
void BuildListInfo::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 2;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	xfer->xferAsciiString( &m_buildingName );
	xfer->xferAsciiString( &m_templateName );
	xfer->xferCoord3D( &m_location );
	xfer->xferCoord2D( &m_rallyPointOffset );
	xfer->xferReal( &m_angle );
	xfer->xferBool( &m_isInitiallyBuilt );
	xfer->xferUnsignedInt( &m_numRebuilds );
	xfer->xferAsciiString( &m_script );
	xfer->xferInt( &m_health );
	xfer->xferBool( &m_whiner );
	xfer->xferBool( &m_unsellable );
	xfer->xferBool( &m_repairable );
	xfer->xferBool( &m_automaticallyBuild );
	// m_renderObj we don't need to xfer this, its for the editor only
	// m_shadowObj we don't need to xfer this, its for the editor only
	// m_selected we don't need to xfer this, its for the editor only
	xfer->xferObjectID( &m_objectID );
	xfer->xferUnsignedInt( &m_objectTimestamp );
	xfer->xferBool( &m_underConstruction );
	xfer->xferUser( m_resourceGatherers, sizeof( ObjectID ) * MAX_RESOURCE_GATHERERS );
	xfer->xferBool( &m_isSupplyBuilding );
	xfer->xferInt( &m_desiredGatherers );
	xfer->xferBool( &m_priorityBuild );
	if (version>=2) {
		xfer->xferInt(&m_currentGatherers);
	}

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BuildListInfo@@MAEXXZ present-unmatched
void BuildListInfo::loadPostProcess( void )
{

}  // end loadPostProcess

/* ********* TeamsInfoRec class ****************************/
// ??0TeamsInfoRec@@ present-unmatched
TeamsInfoRec::TeamsInfoRec() : 
	m_numTeams(0), m_numTeamsAllocated(0), m_teams(NULL)
{
}

// ??0TeamsInfoRec@@ present-unmatched
TeamsInfoRec::TeamsInfoRec(const TeamsInfoRec& thatref) : 
	m_numTeams(0), m_numTeamsAllocated(0), m_teams(NULL)
{
	*this = thatref;
}

// ??1TeamsInfoRec@@QAE@XZ present-unmatched
TeamsInfoRec::~TeamsInfoRec() 
{
	clear();
}

// ug, I hate having to overload stuff, but this makes it a lot easier to make copies safely
// ??4TeamsInfoRec@@QAEAAV0@ABV0@@Z present-unmatched
TeamsInfoRec& TeamsInfoRec::operator=(const TeamsInfoRec& thatref)
{
	const TeamsInfoRec* that = &thatref;
	if (this != that)
	{
		this->clear();
		for (int i = 0; i < that->m_numTeams; i++) 
		{
			this->addTeam(that->m_teams[i].getDict());
		}
	}
	return *this;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__clear_TeamsInfoRec_QAEXXZ_001991F0.cpp
// ?clear@TeamsInfoRec@@QAEXXZ present-unmatched
void TeamsInfoRec::clear() 
{ 
	Int i;

	for (i = 0; i < m_numTeamsAllocated; i++) 
		m_teams[i].clear(); 

	m_numTeams = 0; 
	m_numTeamsAllocated = 0;
	delete [] m_teams;
	m_teams = NULL;
}

// ?findTeamInfo@TeamsInfoRec@@QAEPAVTeamsInfo@@VAsciiString@@PAH@Z present-unmatched
TeamsInfo *TeamsInfoRec::findTeamInfo(AsciiString name, Int* index /*= NULL*/)
{
	for (int i = 0; i < m_numTeams; i++) 
	{
		if (m_teams[i].getDict()->getAsciiString(TheKey_teamName) == name)
		{
			if (index)
				*index = i;
			return &m_teams[i];
		}
	}
	return NULL;
}

// ?addTeam@TeamsInfoRec@@QAEXPBVDict@@@Z present-unmatched
// That donor does NOT hold this body, so the pointer to it is gone. It owns
// three rows on RVA 0x0000D828, and 0x0000D828 is `E9 63 16 05 00` = jmp
// 0x0005EE90 -- which this same ledger already records as ??1AsciiString@@QAE@XZ
// (export_rva 0x0000D828, body 0x0005EE90, matched from ascii_string.cpp). The
// binary settles it by call profile: 6,947 direct call/jmp sites reach that stub
// and exactly one reaches the body behind it. That is a string destructor's
// import thunk, not TeamsInfoRec::addTeam, which retail calls from a handful of
// places. The rows pass verification only because a jmp's rel32 is a masked
// relocation, so ANY 5-byte tail-call thunk byte-matches any other -- the same
// mechanism that let a wrong $L pin ride along on the PeerDefs funclets.
//
// So do not screen these two against that donor: marker_screen reports miss(4)
// for addTeam, which is only the first five bytes of this real body compared
// against a jump. Retail's TeamsInfoRec::addTeam and ::removeTeam are still
// unlocated. Logged in re_attempts.log as mis-anchored?.
void TeamsInfoRec::addTeam(const Dict* d)
{
	enum
	{
		TEAM_ALLOC_CHUNK = 8	///< how many teams to alloc at a time
	};

	DEBUG_ASSERTCRASH(m_numTeams < 2048, ("%d teams have been allocated (so far). This seems excessive.", m_numTeams ));
	if (m_numTeams >= m_numTeamsAllocated)
	{
	// pool[]ify
		TeamsInfo* nti = NEW TeamsInfo[m_numTeamsAllocated + TEAM_ALLOC_CHUNK];	// throws on failure
		
		Int i;

		for (i = 0; i < m_numTeams; i++)
			nti[i] = m_teams[i];

		for ( ; i < m_numTeamsAllocated + TEAM_ALLOC_CHUNK; i++) 
			nti[i].clear(); 
		
		delete [] m_teams;

		m_teams = nti;
		m_numTeamsAllocated += TEAM_ALLOC_CHUNK;
	}

	m_teams[m_numTeams++].init(d);
}

// ?removeTeam@TeamsInfoRec@@QAEXH@Z present-unmatched
// That donor does NOT hold this body, so the pointer to it is gone. It owns
// three rows on RVA 0x0000D828, and 0x0000D828 is `E9 63 16 05 00` = jmp
// 0x0005EE90 -- which this same ledger already records as ??1AsciiString@@QAE@XZ
// (export_rva 0x0000D828, body 0x0005EE90, matched from ascii_string.cpp). The
// binary settles it by call profile: 6,947 direct call/jmp sites reach that stub
// and exactly one reaches the body behind it. That is a string destructor's
// import thunk, not TeamsInfoRec::addTeam, which retail calls from a handful of
// places. The rows pass verification only because a jmp's rel32 is a masked
// relocation, so ANY 5-byte tail-call thunk byte-matches any other -- the same
// mechanism that let a wrong $L pin ride along on the PeerDefs funclets.
//
// So do not screen these two against that donor: marker_screen reports miss(4)
// for addTeam, which is only the first five bytes of this real body compared
// against a jump. Retail's TeamsInfoRec::addTeam and ::removeTeam are still
// unlocated. Logged in re_attempts.log as mis-anchored?.
void TeamsInfoRec::removeTeam(Int i)
{
	if (i < 0 || i >= m_numTeams || m_numTeams <= 1)
		return;

	for ( ; i < m_numTeams-1; i++)
		m_teams[i] = m_teams[i+1];

	for ( ; i < m_numTeamsAllocated; i++)
		m_teams[i].clear();

	--m_numTeams;
}
