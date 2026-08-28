typedef bool Bool;
typedef unsigned short zoneStorageType;

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

class PathfindZoneManager
{
public:
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;

private:
	unsigned char opaque[0x23638];
	ZoneEquivalencies equivalencies[9];
};

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
