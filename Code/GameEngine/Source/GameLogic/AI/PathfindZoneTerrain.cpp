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

// BFME stores the movement properties consulted by the zone manager in this
// compact form.  The Zero Hour LocomotorSet layout is not binary-compatible.
struct PathfindMovementProfile
{
	int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	int layer;
};

struct ZoneEquivalencies
{
	zoneStorageType *base;
	zoneStorageType *groundCliff;
	zoneStorageType *groundWater;
	zoneStorageType *groundRubble;
	zoneStorageType *terrain;
	zoneStorageType *all;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;

private:
	unsigned char opaque[0x23634];
	unsigned int maxZone;
	ZoneEquivalencies equivalencies[9];
};

zoneStorageType PathfindZoneManager::getEffectiveZone(
	const PathfindMovementProfile &profile, zoneStorageType zone) const
{
	if (zone > maxZone)
		return 0;

	const int surfaces = profile.acceptableSurfaces;
	if (surfaces & LOCOMOTORSURFACE_AIR)
		return 1;

	int profileIndex = profile.layer < 0 ? 0 : profile.layer + 1;
	if (profile.crusher)
		profileIndex += 3;
	if (profile.terrainOnly)
		profileIndex += 6;

	if ((surfaces & LOCOMOTORSURFACE_GROUND) &&
		(surfaces & LOCOMOTORSURFACE_RUBBLE) &&
		(surfaces & LOCOMOTORSURFACE_WATER) &&
		(surfaces & LOCOMOTORSURFACE_OBSTACLE) &&
		(surfaces & LOCOMOTORSURFACE_IMPASSABLE)) {
		return equivalencies[profileIndex].all[zone];
	}

	switch (surfaces & 7) {
		case LOCOMOTORSURFACE_GROUND:
			if (surfaces & LOCOMOTORSURFACE_RUBBLE)
				return equivalencies[profileIndex].groundRubble[zone];
			return equivalencies[profileIndex].base[zone];

		case LOCOMOTORSURFACE_GROUND | LOCOMOTORSURFACE_WATER:
			return equivalencies[profileIndex].groundWater[zone];

		case LOCOMOTORSURFACE_GROUND | LOCOMOTORSURFACE_CLIFF:
			return equivalencies[profileIndex].groundCliff[zone];

		case LOCOMOTORSURFACE_GROUND | LOCOMOTORSURFACE_WATER |
			LOCOMOTORSURFACE_CLIFF:
			return 1;

		case 0:
			return 0;
		default:
			return 0;
	}

	return 0;
}

zoneStorageType PathfindZoneManager::bfmeEffectiveTerrainZone(
	const PathfindMovementProfile &profile, zoneStorageType zone) const
{
	int profileIndex = profile.layer;
	if (profileIndex < 0)
		profileIndex = 0;
	else
		++profileIndex;

	if (profile.crusher)
		profileIndex += 3;
	if (profile.terrainOnly)
		profileIndex += 6;

	return equivalencies[profileIndex].terrain[zone];
}
