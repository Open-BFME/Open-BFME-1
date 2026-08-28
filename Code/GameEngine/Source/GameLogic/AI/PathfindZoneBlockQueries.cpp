typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

struct ZoneBlock
{
	Int m_numWaypoints;                       // 0x000
	Int m_unknown04;                          // 0x004
	void *m_waypoints[12];                    // 0x008
	unsigned char m_zoneState[0x12c - 0x38];
	Bool m_interactsWithBridge;               // 0x12c
	unsigned char m_tail[0x228 - 0x12d];
};

class PathfindZoneManager
{
public:
	Bool bfmeInteractsWithBridge(Int cellX, Int cellY) const;

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
