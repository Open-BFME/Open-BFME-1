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
	~UnicodeString();
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	bool operator<(const AsciiString &other) const;

private:
	char *m_data;
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
	~PlayerPosition();
};

// The slot record's body and its EH-vector destructor thunk are still ledger
// placeholders. Their retail addresses are independently established by the
// 0x000C0B00 and 0x0001F951 rows.
#pragma comment(linker, "/alternatename:??0PlayerPosition@@QAE@XZ=?j_0003a760@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PlayerPosition@@QAE@XZ=??1Rva00078460Elem@@QAE@XZ")

class MapMetaData
{
public:
	MapMetaData();
	~MapMetaData();

private:
	UnicodeString m_displayName;
	UnicodeString m_description;
	struct Region3D
	{
		Coord3D lo;
		Coord3D hi;
	} m_extent;
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
	PlayerPosition m_players[8];
	UnicodeString m_displayNameTail;
	UnicodeString m_descriptionTail;
};

MapMetaData::MapMetaData()
	: m_numPlayers(0),
	  m_isMultiplayer(0),
	  m_isScenarioMP(0),
	  m_isOfficial(0),
	  m_filesize(0),
	  m_CRC(0)
{
	m_extent.lo.x = 0.0f;
	m_extent.lo.y = 0.0f;
	m_extent.lo.z = 0.0f;
	m_extent.hi.x = 0.0f;
	m_extent.hi.y = 0.0f;
	m_extent.hi.z = 0.0f;
	m_timestampHi = 0;
	m_timestampLo = 0;
}
