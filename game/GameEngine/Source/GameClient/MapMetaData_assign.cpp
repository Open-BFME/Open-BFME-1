// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x000C1050 is the bounded MapMetaData assignment body.  Its
// neighboring copy constructor at 0x000C1240 establishes this record's
// member order; the +0x54 MapPlayers assignment is the eight-record body
// recovered at 0x000C0C60.  The map and list assignments below deliberately
// call their existing retail thunks through typed member-function pointers.
// That preserves the retail ECX/stack ABI without assigning a new identity to
// an ILT that is only a routing helper.

typedef unsigned short UnsignedShort;

#include "string_base.h"

class UnicodeString
{
public:
	void set(const UnicodeString &other);

private:
	void *m_data;
};

struct WaypointMap
{
	unsigned char m_treeStorage[12];
	int m_numStartSpots;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

struct Coord3DList
{
	unsigned char m_listStorage[4];
};

struct MapPlayers
{
	unsigned char m_items[0xa0];
};

extern void j_000262ce(void);
extern void j_000044f8(void);
extern void j_0001ffc3(void);

class MapMetaData
{
public:
	MapMetaData &operator=(const MapMetaData &other);

private:
	StringBase<UnsignedShort> m_displayName;
	StringBase<UnsignedShort> m_description;
	Region3D m_extent;
	int m_numPlayers;
	unsigned char m_isMultiplayer;
	unsigned char m_isScenarioMP;
	unsigned char m_isOfficial;
	unsigned int m_filesize;
	unsigned int m_CRC;
	unsigned int m_timestampLo;
	unsigned int m_timestampHi;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	UnicodeString m_mapDescription;
	MapPlayers m_players;
	StringBase<UnsignedShort> m_displayNameTail;
	StringBase<UnsignedShort> m_descriptionTail;
};

MapMetaData &MapMetaData::operator=(const MapMetaData &other)
{
	m_displayName.set(other.m_displayName);
	m_description.set(other.m_description);
	m_extent = other.m_extent;
	m_numPlayers = other.m_numPlayers;
	m_isMultiplayer = other.m_isMultiplayer;
	m_isScenarioMP = other.m_isScenarioMP;
	m_isOfficial = other.m_isOfficial;
	m_filesize = other.m_filesize;
	m_CRC = other.m_CRC;
	m_timestampLo = other.m_timestampLo;
	m_timestampHi = other.m_timestampHi;
	{
		const WaypointMap *sourceWaypoints = &other.m_waypoints;
		WaypointMap *destinationWaypoints = &m_waypoints;
		typedef WaypointMap &(WaypointMap::*Function)(const WaypointMap &);
		union
		{
			void (*raw)(void);
			Function member;
		} fn;
		fn.raw = j_000262ce;
		(destinationWaypoints->*fn.member)(*sourceWaypoints);
		destinationWaypoints->m_numStartSpots = sourceWaypoints->m_numStartSpots;
	}
	{
		typedef Coord3DList &(Coord3DList::*Function)(const Coord3DList &);
		union
		{
			void (*raw)(void);
			Function member;
		} fn;
		fn.raw = j_000044f8;
		(reinterpret_cast<Coord3DList *>(&m_supplyPositions)->*fn.member)(other.m_supplyPositions);
	}
	{
		typedef Coord3DList &(Coord3DList::*Function)(const Coord3DList &);
		union
		{
			void (*raw)(void);
			Function member;
		} fn;
		fn.raw = j_000044f8;
		(reinterpret_cast<Coord3DList *>(&m_techPositions)->*fn.member)(other.m_techPositions);
	}
	m_mapDescription.set(other.m_mapDescription);
	{
		typedef MapPlayers &(MapPlayers::*Function)(const MapPlayers &);
		union
		{
			void (*raw)(void);
			Function member;
		} fn;
		fn.raw = j_0001ffc3;
		(reinterpret_cast<MapPlayers *>(&m_players)->*fn.member)(other.m_players);
	}
	m_displayNameTail.set(other.m_displayNameTail);
	m_descriptionTail.set(other.m_descriptionTail);
	return *this;
}
