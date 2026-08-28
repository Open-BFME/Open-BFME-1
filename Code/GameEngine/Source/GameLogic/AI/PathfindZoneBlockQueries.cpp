typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short zoneStorageType;

struct ICoord2D
{
	Int x;
	Int y;
};

class Waypoint;

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

struct PathfindCell
{
	unsigned char m_prefix[8];
	zoneStorageType m_zone;
	unsigned char m_tail[6];
};

struct ZoneBlock
{
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;

	Int m_numWaypoints;                       // 0x000
	Int m_unknown04;                          // 0x004
	Waypoint *m_waypoints[12];                // 0x008
	unsigned char m_zoneState[0x12c - 0x38];
	Bool m_interactsWithBridge;               // 0x12c
	unsigned char m_tail[0x224 - 0x12d];
	Bool m_tailFlag;                          // 0x224
	unsigned char m_tailPadding[3];
};

class PathfindZoneManager
{
public:
	Bool bfmeInteractsWithBridge(Int cellX, Int cellY) const;
	Bool bfmeHasWaypoints(Int cellX, Int cellY) const;
	Waypoint *bfmeGetWaypoint(Int cellX, Int cellY, UnsignedInt index) const;
	zoneStorageType bfmeGetBlockZone(const PathfindMovementProfile &profile,
		Int cellX, Int cellY, PathfindCell **map) const;
	void bfmeSetTailFlag(Int cellX, Int cellY, Bool flag);

private:
	unsigned char m_prefix[0x23628];
	ZoneBlock **m_zoneBlocks;                 // 0x23628
	ICoord2D m_zoneBlockExtent;               // 0x2362c
};

Bool PathfindZoneManager::bfmeInteractsWithBridge(Int cellX, Int cellY) const
{
	if (cellX < 0 || cellY < 0)
		return false;

	Int blockX = cellX / 16;
	Int blockY = cellY / 16;
	if (blockX >= m_zoneBlockExtent.x || blockY >= m_zoneBlockExtent.y)
		return false;

	return m_zoneBlocks[blockX][blockY].m_interactsWithBridge;
}

Bool PathfindZoneManager::bfmeHasWaypoints(Int cellX, Int cellY) const
{
	if (cellX < 0 || cellY < 0)
		return false;

	Int blockX = cellX / 16;
	Int blockY = cellY / 16;
	if (blockX >= m_zoneBlockExtent.x || blockY >= m_zoneBlockExtent.y)
		return false;

	return m_zoneBlocks[blockX][blockY].m_numWaypoints > 0;
}

Waypoint *PathfindZoneManager::bfmeGetWaypoint(
	Int cellX, Int cellY, UnsignedInt index) const
{
	if (cellX < 0 || cellY < 0)
		return 0;

	Int blockX = cellX / 16;
	Int blockY = cellY / 16;
	if (blockX < m_zoneBlockExtent.x && blockY < m_zoneBlockExtent.y) {
		const ZoneBlock &block = m_zoneBlocks[blockX][blockY];
		if (index < (UnsignedInt)block.m_numWaypoints)
			return block.m_waypoints[index];
	}

	return 0;
}

zoneStorageType PathfindZoneManager::bfmeGetBlockZone(
	const PathfindMovementProfile &profile,
	Int cellX, Int cellY, PathfindCell **map) const
{
	if (cellX < 0 || cellY < 0)
		return 0;

	Int blockX = cellX / 16;
	Int blockY = cellY / 16;
	if (blockX >= m_zoneBlockExtent.x || blockY >= m_zoneBlockExtent.y)
		return 0;

	return m_zoneBlocks[blockX][blockY].getEffectiveZone(
		profile, map[cellX][cellY].m_zone);
}

void PathfindZoneManager::bfmeSetTailFlag(Int cellX, Int cellY, Bool flag)
{
	if (cellX < 0 || cellY < 0)
		return;

	Int blockX = cellX / 16;
	Int blockY = cellY / 16;
	if (blockX < m_zoneBlockExtent.x && blockY < m_zoneBlockExtent.y)
		m_zoneBlocks[blockX][blockY].m_tailFlag = flag;
}
