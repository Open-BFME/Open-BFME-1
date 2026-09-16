// ?checkForAdjust@Rva003D6210@@QAE_NABUPathfindMovementProfile@@H_NHHHPAUCoord3D@@1@Z
// partial score=0.23 date=2026-09-16
// Scratch-only full-body probe for retail 0x003D6210 (181 bytes).
// Owner and method name are address-derived pending root caller review.
// The parameter order is the independently decoded BFME body ABI:
// profile, expectedZone, center, cellX, cellY, layer, pos, terrainZone.

// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef bool Bool;
typedef unsigned short zoneStorageType;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
};

class PathfindCell
{
public:
	unsigned char m_pad00[8];
	zoneStorageType m_zone;

	private:
	unsigned short m_pad0a;

	public:
	union
	{
		unsigned int m_flags;
		struct
		{
			unsigned int m_type : 3;
			unsigned int m_unused0 : 18;
			unsigned int m_bit21 : 1;
			unsigned int m_unused1 : 10;
		};
	};
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);
	void adjustCoordToCell(Int cellX, Int cellY, Bool center,
		Coord3D &pos, PathfindLayerEnum layer);

protected:
	unsigned char m_pad[0xc9c];
	PathfindZoneManager m_zoneManager;
};

class Rva003D6210 : public Pathfinder
{
public:
	Bool checkForAdjust(const PathfindMovementProfile &profile,
		Int expectedZone, Bool center, Int cellX, Int cellY, Int layer,
		Coord3D *pos, Bool terrainZone);
};

Bool Rva003D6210::checkForAdjust(
	const PathfindMovementProfile &profile, Int expectedZone, Bool center,
	Int cellX, Int cellY, Int layer, Coord3D *pos, Bool terrainZone)
{
	PathfindCell *cell;
	unsigned int flags;
	unsigned int type;
	zoneStorageType zone;

	cell = getCell((PathfindLayerEnum)layer, cellX, cellY);
	if (cell == 0)
		goto earlyFailure;

	flags = cell->m_flags;
	if (((flags >> 6) & 0x3f) != (unsigned int)layer)
 		goto earlyFailure;
	type = flags & 7;
	if (type == 4)
		goto earlyFailure;
	if (type != 5)
		goto cellAccepted;

earlyFailure:
	return false;

cellAccepted:
	if (cell->m_bit21 && profile.terrainOnly)
		goto lateFailure;

	zone = m_zoneManager.getEffectiveZone(profile,
		cell->m_zone);
	if (terrainZone)
		zone = m_zoneManager.bfmeEffectiveTerrainZone(profile, zone);
	if (expectedZone != (Int)zone)
		goto lateFailure;

	adjustCoordToCell(cellX, cellY, center, *pos,
		(PathfindLayerEnum)layer);
	return true;

lateFailure:
	return false;
}
