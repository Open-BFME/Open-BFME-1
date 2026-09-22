// ?d_000c1e50@@YAXXZ
// partial score=0.26 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
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

// FILE: INIMapCache.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Matthew D. Campbell, February 2002
// Desc:   Parsing MapCache INI entries
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>		// BFME uses the STLport node allocator for std::list<Coord3D>; include it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include <list>
#include <map>
#include <set>
#include "Lib/BaseType.h"
#include "Common/INI.h"
#include "GameClient/GameText.h"
#include "GameNetwork/NetworkDefs.h"
#include "Common/NameKeyGenerator.h"
#include "Common/WellKnownKeys.h"
#include "Common/QuotedPrintable.h"

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

struct WinTimeStamp
{
	UnsignedInt m_lowTimeStamp;
	UnsignedInt m_highTimeStamp;
};

typedef std::list<Coord3D> Coord3DList;

class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	void clear();
	Int m_numStartSpots;
};

#pragma comment(linker, "/alternatename:?clear@WaypointMap@@QAEXXZ=?j_000433a6@@YAXXZ")

struct PlayerPosition
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	std::set<AsciiString> m_factionSet;
};

struct MapPlayers
{
	MapPlayers &operator=(const MapPlayers &other);
	PlayerPosition m_items[8];
};

#pragma comment(linker, "/alternatename:??4MapPlayers@@QAEAAV0@ABV0@@Z=?j_0001ffc3@@YAXXZ")

class MapMetaData
{
public:
	MapMetaData();
	MapMetaData &operator=(const MapMetaData &other);
	~MapMetaData();

	UnicodeString m_displayName;
	UnicodeString m_description;
	Region3D m_extent;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	WinTimeStamp m_timestamp;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	AsciiString m_fileName;
	MapPlayers m_players;
	UnicodeString m_displayNameTail;
	UnicodeString m_descriptionTail;
};

class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	MapMetaData &operator[](const AsciiString &key);
};

#pragma comment(linker, "/alternatename:?operator[]@MapCache@@QAEAAVMapMetaData@@ABVAsciiString@@@Z=?j_00031e99@@YAXXZ")

extern MapCache *TheMapCache;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

class MapMetaDataReader
{
public:
	Region3D m_extent;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	AsciiString m_asciiDisplayName;
	AsciiString m_asciiNameLookupTag;

	Bool m_isOfficial;
	WinTimeStamp m_timestamp;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;

	Coord3D m_waypoints[MAX_SLOTS];
	Coord3D m_initialCameraPosition;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	MapPlayers m_players;
	static const FieldParse m_mapFieldParseTable[];		///< the parse table for INI definition
	const FieldParse *getFieldParse( void ) const { return m_mapFieldParseTable; }
};


void parseSupplyPositionCoord3D( INI* ini, void * instance, void * /*store*/, const void* /*userData*/ )
{
	MapMetaDataReader *mmdr = (MapMetaDataReader *)instance;
	Coord3D coord3d;
	INI::parseCoord3D(ini, NULL, &coord3d,NULL );
	mmdr->m_supplyPositions.push_front(coord3d);

}

void parseTechPositionsCoord3D( INI* ini, void * instance, void * /*store*/, const void* /*userData*/ )
{
	MapMetaDataReader *mmdr = (MapMetaDataReader *)instance;
	Coord3D coord3d;
	INI::parseCoord3D(ini, NULL, &coord3d,NULL );
	mmdr->m_techPositions.push_front(coord3d);

}

const FieldParse MapMetaDataReader::m_mapFieldParseTable[] = 
{

	{ "isOfficial",							INI::parseBool,			NULL,	offsetof( MapMetaDataReader, m_isOfficial ) },
	{ "isMultiplayer",					INI::parseBool,			NULL,	offsetof( MapMetaDataReader, m_isMultiplayer ) },
	{ "extentMin",							INI::parseCoord3D,	NULL, offsetof( MapMetaDataReader, m_extent.lo ) },
	{ "extentMax",							INI::parseCoord3D,	NULL, offsetof( MapMetaDataReader, m_extent.hi ) },
	{ "numPlayers",							INI::parseInt,			NULL,	offsetof( MapMetaDataReader, m_numPlayers ) },
	{ "fileSize",								INI::parseUnsignedInt,	NULL,	offsetof( MapMetaDataReader, m_filesize ) },
	{ "fileCRC",								INI::parseUnsignedInt,	NULL,	offsetof( MapMetaDataReader, m_CRC ) },
	{ "timestampLo",						INI::parseInt,			NULL,	offsetof( MapMetaDataReader, m_timestamp.m_lowTimeStamp ) },
	{ "timestampHi",						INI::parseInt,			NULL,	offsetof( MapMetaDataReader, m_timestamp.m_highTimeStamp ) },
	{ "displayName",						INI::parseAsciiString,	NULL,	offsetof( MapMetaDataReader, m_asciiDisplayName ) },
	{ "nameLookupTag",					INI::parseAsciiString,	NULL,	offsetof( MapMetaDataReader, m_asciiNameLookupTag ) },

	{ "supplyPosition",					parseSupplyPositionCoord3D,	NULL, NULL },
	{ "techPosition",						parseTechPositionsCoord3D,	NULL, NULL },

	{ "Player_1_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) },
	{ "Player_2_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 1 },
	{ "Player_3_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 2 },
	{ "Player_4_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 3 },
	{ "Player_5_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 4 },
	{ "Player_6_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 5 },
	{ "Player_7_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 6 },
	{ "Player_8_Start",					INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 7 },

	{ "InitialCameraPosition",	INI::parseCoord3D,	NULL,	offsetof( MapMetaDataReader, m_initialCameraPosition ) },

	{ NULL,					NULL,						NULL,						0 }  // keep this last

};

// ?parseMapCacheDefinition@INI@@ present-unmatched
void INI::parseMapCacheDefinition( INI* ini )
{
	const char *c;
	AsciiString name;
	MapMetaDataReader mdr;
	MapMetaData md;

	// read the name
	c = ini->getNextToken(" \n\r\t");
	if (c == NULL)
		return;
	((StringBase<char> *)&name)->set(c, (Int)strlen(c));
	name = QuotedPrintableToAsciiString(name);
	md.m_waypoints.clear();

	ini->initFromINI( &mdr, mdr.getFieldParse() );

	md.m_extent = mdr.m_extent;
	md.m_isOfficial = mdr.m_isOfficial != 0;
	md.m_isMultiplayer = mdr.m_isMultiplayer != 0;
	md.m_isScenarioMP = mdr.m_isScenarioMP != 0;
	md.m_numPlayers = mdr.m_numPlayers;
	md.m_filesize = mdr.m_filesize;
	md.m_CRC = mdr.m_CRC;
	md.m_timestamp = mdr.m_timestamp;

	md.m_waypoints[TheNameKeyGenerator->keyToName(TheKey_InitialCameraPosition)] = mdr.m_initialCameraPosition;

	md.m_displayName = QuotedPrintableToUnicodeString(mdr.m_asciiDisplayName);
	md.m_description = QuotedPrintableToUnicodeString(mdr.m_asciiNameLookupTag);

	AsciiString startingCamName;
	for (Int i=0; i<md.m_numPlayers; ++i)
	{
		startingCamName.format("Player_%d_Start", i+1); // start pos waypoints are 1-based
		md.m_waypoints[startingCamName] = mdr.m_waypoints[i];
	}

	Coord3DList::iterator it = mdr.m_supplyPositions.begin();
	while( it != mdr.m_supplyPositions.end())
	{
		md.m_supplyPositions.push_front(*it);
		it++;
	}

	it = mdr.m_techPositions.begin();
	while( it != mdr.m_techPositions.end())
	{
		md.m_techPositions.push_front(*it);
		it++;
	}

	md.m_players = mdr.m_players;

	if(TheMapCache && !md.m_displayName.isEmpty())
	{
		AsciiString lowerName = name;
		lowerName.toLower();
		md.m_fileName = lowerName;
//		DEBUG_LOG(("INI::parseMapCacheDefinition - adding %s to map cache\n", lowerName.str()));
		(*TheMapCache)[lowerName] = md;
	}
}

