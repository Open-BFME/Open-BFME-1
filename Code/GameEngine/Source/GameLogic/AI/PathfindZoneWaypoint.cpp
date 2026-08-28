typedef bool Bool;

class Waypoint;

class ZoneBlock
{
public:
	void bfmeSetWaypoint(Bool insert, Waypoint *waypoint);

private:
	unsigned char opaque[0x228];
};

class PathfindZoneManager
{
public:
	void bfmeSetWaypoint(
		int cellX, int cellY, Bool insert, Waypoint *waypoint);

private:
	unsigned char opaque[0x23628];
	ZoneBlock **zoneBlocks;
	int zoneBlocksWide;
	int zoneBlocksHigh;
};

void PathfindZoneManager::bfmeSetWaypoint(
	int cellX, int cellY, Bool insert, Waypoint *waypoint)
{
	if (cellX < 0 || cellY < 0)
		return;

	int blockX = cellX / 16;
	int blockY = cellY / 16;

	if (blockX >= zoneBlocksWide)
		return;
	if (blockY >= zoneBlocksHigh)
		return;

	zoneBlocks[blockX][blockY].bfmeSetWaypoint(insert, waypoint);
}
