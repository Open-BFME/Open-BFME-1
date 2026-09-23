// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/buildlistinfo /Ireference/shims/moduledata /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
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

// The canonical StringBase<char> shim supplies BFME AsciiString layout.
// Retail inlines its reference release here; expose that base operation
// within this TU. Every existing sibling remains byte-verified.
#include "string_base.h"

inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }

struct BfmeSidesListXferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// BFME's Xfer interface predates the Zero Hour vtable layout used by the
// released headers. Keep the retail slots local to this translation unit.
class BfmeSidesListXfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(BfmeSidesListXferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void xferCoord2D(Coord2D *value);
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

extern void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);

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

class SidesInfoAssignmentTemp
{
	unsigned char m_pad[0x18];

public:
	SidesInfoAssignmentTemp *copyFrom(void *source);
	void swapWith(SidesInfo *target);
};

// ??4SidesInfo@@QAEAAV0@ABV0@@Z
SidesInfo& SidesInfo::operator=(const SidesInfo& that)
{
	SidesInfoAssignmentTemp temp;
	SidesInfoAssignmentTemp *copy = temp.copyFrom((void *)&that);
	copy->swapWith(this);
	(reinterpret_cast<SidesInfo *>(&temp))->~SidesInfo();
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

// BFME RVA 001A0390: identity is independently proved by the exact
// GameLogic::startNewGame call position and the SidesList pin. Retail uses
// a temporary SidesList and indexed team records; the ZH stream path does not
// occur in this body. Witnesses: build/unclaimed_map/astra_H/LAYOUTS.md.
#include <vector>
extern "C" int __cdecl memcmp(const void*,const void*,unsigned int);
#pragma intrinsic(memcmp)
template<class T> inline bool StringBase<T>::isEmpty() const { return !m_data || !m_data->length; }
template<class T> inline int StringBase<T>::compare(const T* s, int len) const {
    int n = m_data ? m_data->length : 0;
    const T* p = m_data ? m_data->data : "";
    int c = memcmp(p, s, n < len ? n : len);
    if(c!=0) return c;
    return n-len;
}
template<class T> inline int StringBase<T>::compare(const T* s) const { return compare(s, strlen(s)); }
template<class T> inline void StringBase<T>::concat(const T* s) { concat(s, strlen(s)); }

// Address-only ILT adapters below use the existing ?j_XXXXXXXX identities.
// The member-pointer representation is MSVC 7.1 single-inheritance: one code
// address with ECX as receiver. Each signature follows the decoded call and
// callee; no semantic name or pin is invented. The temporary's retail ctor
// and dtor own construction/destruction of Dict and vector subobjects; the
// trivial storage views avoid constructing them a second time.
void j_0002c6c4();
void j_00020d97();
void j_0000fdf8();
void j_000023d8();
void j_00045dc7();
void j_0002cd8b();
void j_0001e5bf();
void j_000384e7();
void j_0000aa9c();
struct Rva001A0390NodeBase { virtual ~Rva001A0390NodeBase(); };
struct Rva00359E40 : Rva001A0390NodeBase { void rva00359E40() { union { void (*entry)(); void (Rva00359E40::*method)(); } fn; fn.entry=&j_000384e7; (this->*fn.method)(); } };
template<class T> inline void rva001A0390Swap(T& a,T& b) { T t=a;a=b;b=t; }
struct Rva001A0390VectorStorage {
    unsigned words[3];
    void clear() { ((std::vector<AsciiString>*)this)->clear(); }
    void swap(Rva001A0390VectorStorage& b) { ((std::vector<AsciiString>*)this)->swap(*(std::vector<AsciiString>*)&b); }
};
struct Rva001A0390Side {
    Rva001A0390NodeBase* rva00;
    unsigned rva04;
    Dict& dict04() { return *(Dict*)&rva04; }
    Rva00359E40* rva08;
    Rva001A0390VectorStorage rva0C;
    void swap(Rva001A0390Side& b) {
        rva001A0390Swap(rva00,b.rva00);
        rva001A0390Swap(*(unsigned*)&rva04,*(unsigned*)&b.rva04);
        rva001A0390Swap(rva08,b.rva08);
        rva0C.swap(b.rva0C);
    }
    void init(const Dict* dict) {
        delete rva00; rva00=0;
        dict04().clear();
        delete rva08; rva08=0;
        rva0C.clear();
        if(dict) dict04()=*dict;
    }
};
struct Rva001A0390TeamNode { short rva00,rva02,rva04,rva06; void* rva08; Dict rva0C; };
struct Rva001A0390Teams {
    unsigned rva00,rva04,rva08;
    Rva001A0390TeamNode* rva0C;
    unsigned rva10,rva14;
    short rva18,rva1A;
    Rva001A0390Teams& rva0019DA80(const Rva001A0390Teams& rhs) { union { void (*entry)(); Rva001A0390Teams& (Rva001A0390Teams::*method)(const Rva001A0390Teams&); } fn; fn.entry=&j_0002c6c4; return (this->*fn.method)(rhs); }
    void rva00197750(int i) { union { void (*entry)(); void (Rva001A0390Teams::*method)(int); } fn; fn.entry=&j_00020d97; (this->*fn.method)(i); }
    void rva001977F0(int i) { union { void (*entry)(); void (Rva001A0390Teams::*method)(int); } fn; fn.entry=&j_0000fdf8; (this->*fn.method)(i); }
    void rva00197860() { union { void (*entry)(); void (Rva001A0390Teams::*method)(); } fn; fn.entry=&j_000023d8; (this->*fn.method)(); }
    void rva0019BA40(const Dict* dict) { union { void (*entry)(); void (Rva001A0390Teams::*method)(const Dict*); } fn; fn.entry=&j_00045dc7; (this->*fn.method)(dict); }
    void erase(int i) {
        rva00197750(i);
        Rva001A0390TeamNode& node=rva0C[i];
        node.rva0C.clear();
        rva0C[node.rva00].rva02=node.rva02;
        rva0C[node.rva02].rva00=node.rva00;
        --rva18;
        node.rva00=rva1A; rva1A=(short)i;
    }
    void swap(Rva001A0390Teams& b) {
        rva001A0390Swap(rva00,b.rva00); rva001A0390Swap(rva04,b.rva04);
        rva001A0390Swap(rva0C,b.rva0C); rva001A0390Swap(rva10,b.rva10);
        rva001A0390Swap(rva14,b.rva14); rva001A0390Swap(rva18,b.rva18);
        rva001A0390Swap(rva1A,b.rva1A);
    }
};
struct Rva001A0390GameInfo {
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual bool slot34();
};
struct Rva001A0390Template { char rva00[0x10c]; AsciiString rva10C; };
struct Rva000E0F30 { Rva001A0390Template* rva000E0F30(NameKeyType key) { union { void (*entry)(); Rva001A0390Template* (Rva000E0F30::*method)(NameKeyType); } fn; fn.entry=&j_0002cd8b; return (this->*fn.method)(key); } };
extern Rva001A0390GameInfo* g012F708C;
extern Rva000E0F30* g012ED750;
extern StaticNameKey g012A7918,g012A7920,g012A7930,g012A7938,g012A7940,g012A7948,g012A7988;
extern StaticNameKey g012A75B8,g012A75C0,g012A75C8;

void j_00032ec5(); void j_000238ad();
class Rva001A0390Layout {
public:
    Rva001A0390Layout() { union { void (*entry)(); void (Rva001A0390Layout::*method)(); } fn; fn.entry=&j_00032ec5; (this->*fn.method)(); }
    ~Rva001A0390Layout() { union { void (*entry)(); void (Rva001A0390Layout::*method)(); } fn; fn.entry=&j_000238ad; (this->*fn.method)(); }
    public:
    char rva00[0x28];
    int rva28;
    Rva001A0390Side rva2C[32];
    int rva32C;
    Rva001A0390Side rva330[32];
    Rva001A0390Teams rva630,rva64C;
    char rva668[0x384];
public:

    void rva0019B640(int i) { union { void (*entry)(); void (Rva001A0390Layout::*method)(int); } fn; fn.entry=&j_0000aa9c; (this->*fn.method)(i); }
    void rva001A0290() { union { void (*entry)(); void (Rva001A0390Layout::*method)(); } fn; fn.entry=&j_0001e5bf; (this->*fn.method)(); }

    void addSide(const Dict* dict) { if(rva28<32) { int i=rva28; ++rva28; rva2C[i].init(dict); } }
};


typedef char Rva001A0390SideSize[(sizeof(Rva001A0390Side)==0x18)?1:-1];
typedef char Rva001A0390TeamSize[(sizeof(Rva001A0390Teams)==0x1c)?1:-1];
typedef char Rva001A0390LayoutSize[(sizeof(Rva001A0390Layout)==0x9ec)?1:-1];
typedef void (Rva001A0390Layout::*Rva001A0390MemberPointer)();
typedef char Rva001A0390MemberPointerSize[(sizeof(Rva001A0390MemberPointer)==sizeof(void(*)()))?1:-1];
template<class T> inline const T* StringBase<T>::str() const { return m_data ? m_data->data : ""; }
void SidesList::prepareForMP_or_Skirmish() {
    Rva001A0390Layout temp;
    Rva001A0390Layout* self=(Rva001A0390Layout*)this;
    temp.rva630.rva0019DA80(self->rva630);
    for(int i=0;i<self->rva28;) {
        Dict* side=&self->rva2C[i].dict04();
        AsciiString name=side->getAsciiString(g012A7918);
        if(((const StringBase<char>*)&name)->isEmpty()) goto keepSide;
        if(((const StringBase<char>*)&name)->compare("PlyrCivilian")==0) goto keepSide;
        if(((const StringBase<char>*)&name)->compare("PlyrCreeps")==0) goto keepSide;
        { temp.rva2C[temp.rva28].swap(self->rva2C[i]);
            if(temp.rva2C[temp.rva28].rva08) temp.rva2C[temp.rva28].rva08->rva00359E40();
            ++temp.rva28; self->rva0019B640(i); }
        continue;
    keepSide:
        { side->setBool(g012A7920,false); ++i; }
    }
    Rva001A0390TeamNode* nodes=self->rva630.rva0C;
    for(int idx=nodes[0].rva00;idx;) {
        nodes=self->rva630.rva0C;
        int next=nodes[idx].rva00;
        AsciiString owner=nodes[idx].rva0C.getAsciiString(g012A75C0);
        if(((const StringBase<char>*)&owner)->isEmpty() || ((const StringBase<char>*)&owner)->compare("PlyrCivilian")==0 || ((const StringBase<char>*)&owner)->compare("PlyrCreeps")==0)
            temp.rva630.erase(idx);
        else self->rva630.rva001977F0(idx);
        idx=next;
    }
    if(!g012F708C || !g012F708C->slot34()) {
        for(int j=0;j<temp.rva28;++j) {
            Dict& side=temp.rva2C[j].dict04();
            if(side.getType(g012A7988)!=Dict::DICT_ASCIISTRING) {
                AsciiString faction=side.getAsciiString(g012A7938);
                Rva001A0390Template* t=g012ED750->rva000E0F30(TheNameKeyGenerator->nameToKey(((const StringBase<char>*)&faction)->str()));
                if(t && !((const StringBase<char>*)&t->rva10C)->isEmpty()) side.setAsciiString(g012A7988,t->rva10C);
            }
        }
    }
    Dict dict;
    dict.setAsciiString(g012A7918,AsciiString("SkirmishHuman"));
    dict.setBool(g012A7920,true);
    dict.setUnicodeString(g012A7930,UnicodeString::TheEmptyString);
    dict.setAsciiString(g012A7938,AsciiString("FactionCivilian"));
    dict.setAsciiString(g012A7940,AsciiString::TheEmptyString);
    dict.setAsciiString(g012A7948,AsciiString::TheEmptyString);
    dict.setAsciiString(g012A7988,AsciiString("Multiplayer_Human"));
    temp.addSide(&dict);
    dict.clear();
    AsciiString teamName("team"); ((StringBase<char>*)&teamName)->concat("SkirmishHuman",13);
    dict.setAsciiString(g012A75B8,teamName);
    dict.setAsciiString(g012A75C0,AsciiString("SkirmishHuman"));
    dict.setBool(g012A75C8,true);
    temp.rva630.rva0019BA40(&dict);
    temp.rva001A0290();
    for(int k=0;k<temp.rva28;++k)
        if(temp.rva2C[k].rva08) temp.rva2C[k].rva08->rva00359E40();
    temp.rva630.rva00197860();
    self->rva32C=temp.rva28;
    for(int n=0;n<32;++n) self->rva330[n].swap(temp.rva2C[n]);
    self->rva64C.swap(temp.rva630);
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

// RE-HOMED with ::removeTeam -- see the note there for the evidence.
// ?addTeam@SidesList@@QAEXPBVDict@@@Z present-unmatched
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

// RE-HOMED, with ::addTeam below. Retail's 0x00C2787D is
// `add ecx,0x194; jmp 0x0000D828`, and 0x0000D828 is `jmp 0x0005EE90` =
// ??1AsciiString@@QAE@XZ. That eleven-byte body is a this-adjusting DESTRUCTOR
// helper -- adjust this by 0x194 to reach an AsciiString member and destroy it.
// Neither of these two forwards to a string destructor; both forward to
// m_teamrec. They matched because the jump is a masked relocation and the only
// compared prefix is the add-ecx immediate, which our m_teamrec offset happens
// to share. Third instance of the AsciiString import-thunk family after the
// TeamsInfoRec trio. One ?dup_00c2787d@@YAXXZ row keeps the bytes covered.
// ?removeTeam@SidesList@@QAEXH@Z present-unmatched
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

// ?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z exact retail body is
// emitted by SidesListAddPlayerByTemplate.cpp.

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
void SidesList::loadPostProcess( void )
{

}  // end loadPostProcess

/* ********* BuildListInfo class ****************************/
/**
 BuildListInfo - Constructor.
*/
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
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Map/BuildListInfoDestructors.cpp
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
void BuildListInfo::xfer( Xfer *xfer )
{
	BfmeSidesListXfer *bfmeXfer = (BfmeSidesListXfer *)xfer;
	if (bfmeXfer->isLightCRC())
		return;

	// version
	BfmeSidesListXferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	bfmeXfer->xferVersion( &version );

	bfmeXfer->xferAsciiString( &m_buildingName );
	bfmeXfer->xferAsciiString( &m_templateName );
	bfmeXfer->xferCoord3D( &m_location );
	bfmeXfer->xferCoord2D( &m_rallyPointOffset );
	bfmeXfer->xferReal( &m_angle );
	bfmeXfer->xferBool( &m_isInitiallyBuilt );
	bfmeXfer->xferUnsignedInt( &m_numRebuilds );
	bfmeXfer->xferAsciiString( &m_script );
	bfmeXfer->xferInt( &m_health );
	bfmeXfer->xferBool( &m_whiner );
	bfmeXfer->xferBool( &m_unsellable );
	bfmeXfer->xferBool( &m_repairable );
	bfmeXfer->xferBool( &m_automaticallyBuild );
	// m_renderObj we don't need to xfer this, its for the editor only
	// m_shadowObj we don't need to xfer this, its for the editor only
	// m_selected we don't need to xfer this, its for the editor only
	friend_xferObjectID( xfer, &m_objectID );
	bfmeXfer->xferUnsignedInt( &m_objectTimestamp );
	bfmeXfer->xferBool( &m_underConstruction );
	for (Int i = 0; i < MAX_RESOURCE_GATHERERS; ++i)
		friend_xferObjectID( xfer, &m_resourceGatherers[i] );
	bfmeXfer->xferBool( &m_isSupplyBuilding );
	bfmeXfer->xferInt( &m_desiredGatherers );
	bfmeXfer->xferBool( &m_priorityBuild );
	bfmeXfer->xferInt( &m_currentGatherers );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void BuildListInfo::loadPostProcess( void )
{

}  // end loadPostProcess

/* ********* TeamsInfoRec class ****************************/
// stale marker removed: ??0TeamsInfoRec@@QAE@XZ is matched from this file
TeamsInfoRec::TeamsInfoRec() : 
	m_numTeams(0), m_numTeamsAllocated(0), m_teams(NULL)
{
}

// ??0TeamsInfoRec@@QAE@ABV0@@Z present-unmatched
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
