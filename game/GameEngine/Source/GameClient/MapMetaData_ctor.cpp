// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the BFME MapMetaData constructor.

#include <list>
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef unsigned short UnsignedShort;

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);

private:
	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};

	Data *m_data;
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString();
};

class MapDisplayNameTail : private StringBase<UnsignedShort>
{
public:
	MapDisplayNameTail() : StringBase<UnsignedShort>() {}
	MapDisplayNameTail(const MapDisplayNameTail &other) : StringBase<UnsignedShort>(other) {}
	~MapDisplayNameTail();
};

class MapDescriptionTail : private StringBase<UnsignedShort>
{
public:
	MapDescriptionTail() : StringBase<UnsignedShort>() {}
	MapDescriptionTail(const MapDescriptionTail &other) : StringBase<UnsignedShort>(other) {}
	~MapDescriptionTail();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
	bool operator<(const AsciiString &other) const;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	WaypointMap() : m_numStartSpots(0) {}
	Int m_numStartSpots;
};

typedef std::list<Coord3D> Coord3DList;

struct PlayerPosition
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	void *m_factionHeader;
	UnsignedInt m_factionCount;
	UnsignedInt m_factionPad;

	PlayerPosition();
	PlayerPosition(const PlayerPosition &other);
	~PlayerPosition();
};

// The slot record's body and its EH-vector destructor thunk are still ledger
// placeholders. Their retail addresses are independently established by the
// 0x000C0B00 and 0x0001F951 rows.
#pragma comment(linker, "/alternatename:??0PlayerPosition@@QAE@XZ=?j_0003a760@@YAXXZ")
#pragma comment(linker, "/alternatename:??0PlayerPosition@@QAE@ABU0@@Z=??0Gen_000C0DF0@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:??1PlayerPosition@@QAE@XZ=??1Rva00078460Elem@@QAE@XZ")

struct MapPlayers
{
	PlayerPosition m_items[8];
};

class MapMetaData
{
public:
	MapMetaData();
	~MapMetaData();

private:
	UnicodeString m_displayName;
	UnicodeString m_description;
	float m_extentLoX;
	float m_extentLoY;
	float m_extentLoZ;
	float m_extentHiX;
	float m_extentHiY;
	float m_extentHiZ;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	UnsignedInt m_timestampLo;
	UnsignedInt m_timestampHi;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	AsciiString m_fileName;
	MapPlayers m_players;
	MapDisplayNameTail m_displayNameTail;
	MapDescriptionTail m_descriptionTail;
};

MapMetaData::MapMetaData()
	: m_numPlayers(0),
	  m_isMultiplayer(0),
	  m_isScenarioMP(0),
	  m_isOfficial(0),
	  m_filesize(0),
	  m_CRC(0)
{
	m_extentLoX = 0.0f;
	m_extentLoY = 0.0f;
	m_extentLoZ = 0.0f;
	m_extentHiX = 0.0f;
	m_extentHiY = 0.0f;
	m_extentHiZ = 0.0f;
	m_timestampHi = 0;
	m_timestampLo = 0;
}


// Keep the compiler-generated copy constructor in this translation unit. The
// map-cache callers copy the complete record before reading its scalar fields.
volatile MapMetaData *g_mapMetaDataCopyAnchor;

__declspec(noinline) void copyMapMetaData(const MapMetaData &other)
{
	MapMetaData copy(other);
	g_mapMetaDataCopyAnchor = &copy;
}
