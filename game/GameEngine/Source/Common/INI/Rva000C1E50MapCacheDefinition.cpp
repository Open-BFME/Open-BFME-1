// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Opaque body at retail RVA 0x000C1E50.
#define __PLACEMENT_VEC_NEW_INLINE
// TU-local BFME string views for by-value MSVC 7.1 calls.

template <typename T> struct Rva000C1E50StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const T *text, int length );
	void set( const StringBase<T> &other );
	void releaseBuffer();
	void toLower();

private:
	Rva000C1E50StringData<T> *m_data;
};

template <typename T>
bool operator<( const StringBase<T> &left, const StringBase<T> &right );

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const AsciiString &other ) { ((StringBase<char> *)this)->set( *(const StringBase<char> *)&other ); return *this; }
	void set( const char *text, int length ) { ((StringBase<char> *)this)->set( text, length ); }
	void toLower() { ((StringBase<char> *)this)->toLower(); }
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
	static AsciiString TheEmptyString;
	void format( AsciiString format, ... );
	bool isEmpty( void ) const;
	bool isNotEmpty( void ) const;
	int compareNoCase( const AsciiString &other ) const;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	bool isEmpty( void ) const { return m_data == 0 || m_data->m_length == 0; }
	UnicodeString &operator=( const UnicodeString &other ) { ((StringBase<unsigned short> *)this)->set( *(const StringBase<unsigned short> *)&other ); return *this; }
	void __cdecl format( UnicodeString format, ... );
	const unsigned short *str( void ) const;
	static UnicodeString TheEmptyString;
	int getLength( void ) const;
	int compareNoCase( const UnicodeString &other ) const;
};

inline bool operator<( const AsciiString &left, const AsciiString &right )
{
	return *(const StringBase<char> *)&left < *(const StringBase<char> *)&right;
}

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.compareNoCase( right ) == 0;
}
#define ASCIISTRING_H
#define UNICODESTRING_H
#include <list>
#include "PreRTS.h"

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

struct WinTimeStamp
{
	UnsignedInt m_lowTimeStamp;
	UnsignedInt m_highTimeStamp;
};

typedef std::list<Coord3D> Coord3DList;

struct Rva000C0D00Less : _STL::less<AsciiString>
{
};

struct Rva000C0D00Value
{
	float x;
	float y;
	float z;
};

namespace _STL
{
template <> class map<AsciiString, Rva000C0D00Value, Rva000C0D00Less,
	allocator<pair<const AsciiString, Rva000C0D00Value> > >
{
public:
	Rva000C0D00Value &operator[]( const AsciiString &key );
};
}

typedef _STL::map<AsciiString, Rva000C0D00Value, Rva000C0D00Less,
	_STL::allocator<_STL::pair<const AsciiString, Rva000C0D00Value> > > Rva000C0D00Map;

class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	WaypointMap() : m_numStartSpots(0) {}
	Int m_numStartSpots;
};

struct PlayerPosition
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	std::set<AsciiString> m_factionSet;
};

class Rva000C0C60MapPlayers
{
public:
	Rva000C0C60MapPlayers &operator=(const Rva000C0C60MapPlayers &other);
	PlayerPosition m_items[8];
};

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
	Rva000C0C60MapPlayers m_players;
	UnicodeString m_displayNameTail;
	UnicodeString m_descriptionTail;
};

class MapCache : public std::map<AsciiString, MapMetaData>
{
};

class Rva000C1D10MapCache
{
public:
	MapMetaData &operator[](const AsciiString &key);
};

#pragma comment(linker, "/alternatename:??ARva000C1D10MapCache@@QAEAAVMapMetaData@@ABVAsciiString@@@Z=?j_00031e99@@YAXXZ")

extern MapCache *TheMapCache;

class MapMetaDataReader
{
public:
	MapMetaDataReader();
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
	Rva000C0C60MapPlayers m_players;
	static const FieldParse m_mapFieldParseTable[];
	const FieldParse *getFieldParse( void ) const { return m_mapFieldParseTable; }
};

class Rva000C0B90MapMetaDataReader : public MapMetaDataReader
{
public:
	~Rva000C0B90MapMetaDataReader();
};

#pragma comment(linker, "/alternatename:??1Rva000C0B90MapMetaDataReader@@QAE@XZ=?j_0003404f@@YAXXZ")

void parseSupplyPositionCoord3D( INI* ini, void * instance, void * /*store*/, const void* /*userData*/ )
{
	Rva000C0B90MapMetaDataReader *mmdr = (Rva000C0B90MapMetaDataReader *)instance;
	Coord3D coord3d;
	INI::parseCoord3D(ini, NULL, &coord3d,NULL );
	mmdr->m_supplyPositions.push_front(coord3d);
}

void parseTechPositionsCoord3D( INI* ini, void * instance, void * /*store*/, const void* /*userData*/ )
{
	Rva000C0B90MapMetaDataReader *mmdr = (Rva000C0B90MapMetaDataReader *)instance;
	Coord3D coord3d;
	INI::parseCoord3D(ini, NULL, &coord3d,NULL );
	mmdr->m_techPositions.push_front(coord3d);
}

const FieldParse MapMetaDataReader::m_mapFieldParseTable[] =
{
	{ "isOfficial", INI::parseBool, NULL, offsetof( MapMetaDataReader, m_isOfficial ) },
	{ "isMultiplayer", INI::parseBool, NULL, offsetof( MapMetaDataReader, m_isMultiplayer ) },
	{ "extentMin", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_extent.lo ) },
	{ "extentMax", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_extent.hi ) },
	{ "numPlayers", INI::parseInt, NULL, offsetof( MapMetaDataReader, m_numPlayers ) },
	{ "fileSize", INI::parseUnsignedInt, NULL, offsetof( MapMetaDataReader, m_filesize ) },
	{ "fileCRC", INI::parseUnsignedInt, NULL, offsetof( MapMetaDataReader, m_CRC ) },
	{ "timestampLo", INI::parseInt, NULL, offsetof( MapMetaDataReader, m_timestamp.m_lowTimeStamp ) },
	{ "timestampHi", INI::parseInt, NULL, offsetof( MapMetaDataReader, m_timestamp.m_highTimeStamp ) },
	{ "displayName", INI::parseAsciiString, NULL, offsetof( MapMetaDataReader, m_asciiDisplayName ) },
	{ "nameLookupTag", INI::parseAsciiString, NULL, offsetof( MapMetaDataReader, m_asciiNameLookupTag ) },
	{ "supplyPosition", parseSupplyPositionCoord3D, NULL, NULL },
	{ "techPosition", parseTechPositionsCoord3D, NULL, NULL },
	{ "Player_1_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) },
	{ "Player_2_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 1 },
	{ "Player_3_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 2 },
	{ "Player_4_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 3 },
	{ "Player_5_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 4 },
	{ "Player_6_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 5 },
	{ "Player_7_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 6 },
	{ "Player_8_Start", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_waypoints ) + sizeof(Coord3D) * 7 },
	{ "InitialCameraPosition", INI::parseCoord3D, NULL, offsetof( MapMetaDataReader, m_initialCameraPosition ) },
	{ NULL, NULL, NULL, 0 }
};

class Rva000C1E50
{
public:
	static void parseMapCacheDefinition( INI *ini );
};

void Rva000C1E50::parseMapCacheDefinition( INI *ini )
{
	const char *c;
	AsciiString name;
	Rva000C0B90MapMetaDataReader mdr;
	MapMetaData md;

	c = ini->getNextToken(" \n\r\t");
	((StringBase<char> *)&name)->set(c, c ? (Int)strlen(c) : 0);
	name = QuotedPrintableToAsciiString(name);
	md.m_waypoints.clear();
	ini->initFromINI( &mdr, mdr.getFieldParse() );

	md.m_extent = mdr.m_extent;
	md.m_isOfficial = mdr.m_isOfficial != 0;
	md.m_isMultiplayer = mdr.m_isMultiplayer != 0;
	md.m_isScenarioMP = mdr.m_isScenarioMP;
	md.m_numPlayers = mdr.m_numPlayers;
	md.m_filesize = mdr.m_filesize;
	md.m_CRC = mdr.m_CRC;
	md.m_timestamp = mdr.m_timestamp;

	reinterpret_cast<Coord3D &>((*reinterpret_cast<Rva000C0D00Map *>(&md.m_waypoints))[TheNameKeyGenerator->keyToName(TheKey_InitialCameraPosition)]) = mdr.m_initialCameraPosition;
	md.m_displayName = QuotedPrintableToUnicodeString(mdr.m_asciiDisplayName);
	md.m_description = QuotedPrintableToUnicodeString(mdr.m_asciiNameLookupTag);

	AsciiString startingCamName;
	for (Int i=0; i<md.m_numPlayers; ++i)
	{
		startingCamName.format("Player_%d_Start", i+1);
		reinterpret_cast<Coord3D &>((*reinterpret_cast<Rva000C0D00Map *>(&md.m_waypoints))[startingCamName]) = mdr.m_waypoints[i];
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
		(*reinterpret_cast<Rva000C1D10MapCache *>(TheMapCache))[lowerName] = md;
	}
}
