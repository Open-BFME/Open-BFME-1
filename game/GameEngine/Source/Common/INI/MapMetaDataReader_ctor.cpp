// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Clean C++ reconstruction of the BFME MapMetaDataReader default
// constructor, retail 0x000C0EA0.
//
// The class and its member order come from the upstream Zero Hour
// definition of MapMetaDataReader in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/INI/INIMapCache.cpp,
// whose field parse table fixes every offset used here: Region3D at +0x00,
// m_numPlayers at +0x18, m_isMultiplayer at +0x1c, the two AsciiString
// members at +0x20/+0x24, m_isOfficial at +0x28, m_timestamp at +0x2c,
// m_filesize at +0x34, m_CRC at +0x38, m_waypoints[MAX_SLOTS] at +0x3c,
// m_initialCameraPosition at +0x9c, m_supplyPositions at +0xa8 and
// m_techPositions at +0xac.  The retail bytes add exactly two BFME
// extensions: the multiplayer-scenario byte that follows m_isMultiplayer at
// +0x1d, and the eight PlayerPosition slots that follow m_techPositions at
// +0xb0.  AsciiString is the canonical class from
// game/Libraries/Source/WWVegas/WWLib/ascii_string.h, not a TU-local shim: its
// inlined default ctor is what makes the two +0x20/+0x24 pointers plain stores
// instead of out-of-line calls.

#include "coord3d.h"
#include "ascii_string.h"
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

struct WinTimeStamp
{
	UnsignedInt m_lowTimeStamp;
	UnsignedInt m_highTimeStamp;
};

// The scalar fields the retail ctor clears with plain dword stores are seen
// through a POD view of the same twelve bytes, so the compiler schedules
// those stores instead of out-of-line Coord3D constructor calls.  Only
// m_waypoints needs the real non-trivial class: its eight-element
// construction is the 0x00016C93/0x0001364C vector the retail body calls.
struct Coord3DPod
{
	float x;
	float y;
	float z;
};

struct Region3D
{
	Coord3DPod lo;
	Coord3DPod hi;
};

typedef std::list<Coord3D> Coord3DList;

// Retail constructs each slot with the 0x14-byte record body at 0x000C0B00
// and destroys it through 0x000782A0; both are the existing ledger rows the
// already matched MapMetaData constructor routes to.
#pragma comment(linker, "/alternatename:??0PlayerPosition@@QAE@XZ=?j_0003a760@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PlayerPosition@@QAE@XZ=?j_0001f951@@YAXXZ")

class PlayerPosition
{
public:
	PlayerPosition();
	~PlayerPosition();

private:
	char m_body[0x14];
};

class MapMetaDataReader
{
public:
	MapMetaDataReader();

private:
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
	Coord3D m_waypoints[8];
	Coord3DPod m_initialCameraPosition;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	PlayerPosition m_players[8];
};

MapMetaDataReader::MapMetaDataReader()
	: m_numPlayers(0),
	  m_isMultiplayer(0),
	  m_isScenarioMP(0),
	  m_asciiDisplayName(),
	  m_asciiNameLookupTag(),
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
	m_timestamp.m_highTimeStamp = 0;
	m_timestamp.m_lowTimeStamp = 0;
	m_initialCameraPosition.x = 0.0f;
	m_initialCameraPosition.y = 0.0f;
	m_initialCameraPosition.z = 0.0f;
	Coord3D *first = m_waypoints;
	first->x = 0.0f;
	first->y = 0.0f;
	first->z = 0.0f;
	m_waypoints[1].x = 0.0f;
	m_waypoints[1].y = 0.0f;
	m_waypoints[1].z = 0.0f;
	m_waypoints[2].x = 0.0f;
	m_waypoints[2].y = 0.0f;
	m_waypoints[2].z = 0.0f;
	m_waypoints[3].x = 0.0f;
	m_waypoints[3].y = 0.0f;
	m_waypoints[3].z = 0.0f;
	m_waypoints[4].x = 0.0f;
	m_waypoints[4].y = 0.0f;
	m_waypoints[4].z = 0.0f;
	m_waypoints[5].x = 0.0f;
	m_waypoints[5].y = 0.0f;
	m_waypoints[5].z = 0.0f;
	m_waypoints[6].x = 0.0f;
	m_waypoints[6].y = 0.0f;
	m_waypoints[6].z = 0.0f;
	m_waypoints[7].x = 0.0f;
	m_waypoints[7].y = 0.0f;
	m_waypoints[7].z = 0.0f;
}
