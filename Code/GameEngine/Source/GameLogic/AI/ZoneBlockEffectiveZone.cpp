// Resolve a ZoneBlock zone through the BFME equivalency table selected by a
// movement profile. The block stores nine five-pointer table groups starting
// at +0x3c, one for each profile index.

typedef bool Bool;
typedef unsigned short zoneStorageType;

enum LocomotorSurfaceType
{
	LOCOMOTORSURFACE_GROUND = 1 << 0,
	LOCOMOTORSURFACE_WATER = 1 << 1,
	LOCOMOTORSURFACE_CLIFF = 1 << 2,
	LOCOMOTORSURFACE_AIR = 1 << 3,
	LOCOMOTORSURFACE_RUBBLE = 1 << 4,
	LOCOMOTORSURFACE_OBSTACLE = 1 << 5,
	LOCOMOTORSURFACE_IMPASSABLE = 1 << 6
};

struct PathfindMovementProfile
{
	int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	int layer;

	int bfmeEquivalencyIndex(void) const;
};

struct ZoneBlockEquivalencies
{
	zoneStorageType *groundCliff;
	zoneStorageType *groundWater;
	zoneStorageType *groundRubble;
	zoneStorageType *all;
	zoneStorageType *base;
};

class Waypoint;

class ZoneBlock
{
public:
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;

private:
	int m_numWaypoints;
	int m_unknown04;
	Waypoint *m_waypoints[12];
	zoneStorageType m_firstZone;
	zoneStorageType m_numZones;
	ZoneBlockEquivalencies m_equivalencies[9];
};

// ?getEffectiveZone@ZoneBlock@@QBEGABUPathfindMovementProfile@@G@Z
zoneStorageType ZoneBlock::getEffectiveZone(
	const PathfindMovementProfile &profile, zoneStorageType zone) const
{
	const int surfaces = profile.acceptableSurfaces;
	if (surfaces & LOCOMOTORSURFACE_AIR)
		return 1;

	if ((surfaces & LOCOMOTORSURFACE_GROUND) &&
		(surfaces & LOCOMOTORSURFACE_WATER) &&
		(surfaces & LOCOMOTORSURFACE_CLIFF))
	{
		return 1;
	}

	if (m_numZones < 2)
		return m_firstZone;

	if (zone < m_firstZone || zone >= m_firstZone + m_numZones)
		return m_firstZone;

	zone -= m_firstZone;
	const int profileIndex = profile.bfmeEquivalencyIndex();

	if ((surfaces & LOCOMOTORSURFACE_GROUND) &&
		(surfaces & LOCOMOTORSURFACE_RUBBLE) &&
		(surfaces & LOCOMOTORSURFACE_WATER) &&
		(surfaces & LOCOMOTORSURFACE_OBSTACLE) &&
		(surfaces & LOCOMOTORSURFACE_IMPASSABLE))
	{
		return m_equivalencies[profileIndex].all[zone];
	}

	if ((surfaces & LOCOMOTORSURFACE_GROUND) &&
		(surfaces & LOCOMOTORSURFACE_CLIFF))
	{
		return m_equivalencies[profileIndex].groundCliff[zone];
	}

	if ((surfaces & LOCOMOTORSURFACE_GROUND) &&
		(surfaces & LOCOMOTORSURFACE_WATER))
	{
		return m_equivalencies[profileIndex].groundWater[zone];
	}

	if ((surfaces & LOCOMOTORSURFACE_GROUND) &&
		(surfaces & LOCOMOTORSURFACE_RUBBLE))
	{
		return m_equivalencies[profileIndex].groundRubble[zone];
	}

	return m_equivalencies[profileIndex].base[zone];
}
