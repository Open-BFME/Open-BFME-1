// ?d_00404b10@@YAXXZ
// partial score=0.55 date=2026-09-02
// Reconstruct the BFME-only incremental zone-equivalency pass.  Zero Hour has
// one set of six tables; BFME performs the same work for twelve movement
// profiles and keeps union-list heads/links beside every table.

typedef unsigned short zoneStorageType;

struct BfmeZoneRegion
{
	int loX;
	int loY;
	int hiX;
	int hiY;
};

struct BfmeZoneCell
{
	void *info;
	unsigned int unused4;
	zoneStorageType zone;
	unsigned short unusedA;
	unsigned int flags;
};

struct BfmeZoneLayer
{
	unsigned char opaque[0x30];
	zoneStorageType zone;
	unsigned char tail[0x12];
};

void bfmeResolveZones(int sourceZone, int targetZone,
	zoneStorageType *zoneEquivalency, zoneStorageType *zoneListHeads,
	zoneStorageType *zoneListNext);

// The retail switch is maintained by the pathfinder update scheduler.  It is
// deliberately TU-local until its owning field is identified from a caller.
bool g_bfmeUseIncrementalZoneObjects;

#pragma pack(push, 1)
class PathfindZoneManager
{
public:
	void bfmeBuildProfileZones(BfmeZoneCell **map, BfmeZoneLayer *layers,
		const BfmeZoneRegion &bounds, int startPercent, int endPercent);

private:
	unsigned char m_beforeMaxZone[0x23298];
	unsigned int m_maxZone;
	zoneStorageType *m_zoneEquivalency[12][6];
	zoneStorageType *m_zoneListHeads[12][6];
	zoneStorageType *m_zoneListNext[12][6];
	void *m_incrementalObjects;
	unsigned int m_scanWidth;
	unsigned int m_scanHeight;
	void *m_currentIncrementalObject;
};
#pragma pack(pop)

static bool sameProfileLayer(unsigned int a, unsigned int b, int layer)
{
	if (layer <= 0)
		return true;
	return (((a >> 22) & 3) > (unsigned int)layer) ==
		(((b >> 22) & 3) > (unsigned int)layer);
}

static bool sameProfileCell(unsigned int a, unsigned int b,
	int layer, bool crusher, bool terrainOnly)
{
	if (!sameProfileLayer(a, b, layer))
		return false;
	if (crusher && (((a >> 20) ^ (b >> 20)) & 1))
		return false;
	if (terrainOnly && (((a >> 21) ^ (b >> 21)) & 1))
		return false;
	return true;
}

static unsigned int substituteZero(unsigned int value, unsigned int replacement)
{
	value &= 7;
	return value ? value : replacement;
}

void PathfindZoneManager::bfmeBuildProfileZones(BfmeZoneCell **map,
	BfmeZoneLayer *layers, const BfmeZoneRegion &bounds,
	int startPercent, int endPercent)
{
	if (startPercent == 0)
	{
		for (int table = 0; table < 6; ++table)
		{
			for (int profile = 0; profile < 12; ++profile)
			{
				for (unsigned int zone = 0; zone < m_maxZone; ++zone)
				{
					m_zoneEquivalency[profile][table][zone] =
						(zoneStorageType)zone;
					m_zoneListHeads[profile][table][zone] =
						(zoneStorageType)zone;
					m_zoneListNext[profile][table][zone] = 0xffff;
				}
			}
		}
		m_currentIncrementalObject =
			*(void **)((unsigned char *)m_incrementalObjects + 8);
	}

	unsigned int firstObject = m_scanWidth * (unsigned int)startPercent / 100;
	unsigned int lastObject = m_scanWidth * (unsigned int)endPercent / 100;
	int width = bounds.hiX - bounds.loX + 1;
	int firstX = bounds.loX + width * startPercent / 100;
	int lastX = bounds.loX + width * endPercent / 100;

	for (int profile = 0; profile < 12; ++profile)
	{
		int layer = profile % 3;
		int profileFlags = profile / 3;
		bool crusher = (profileFlags & 1) != 0;
		bool terrainOnly = ((profileFlags >> 1) & 1) != 0;

		if (!g_bfmeUseIncrementalZoneObjects)
		{
			for (int x = firstX; x < lastX; ++x)
			{
				for (int y = bounds.loY; y <= bounds.hiY; ++y)
				{
					BfmeZoneCell &cell = map[y][x];
					unsigned int bits = cell.flags;
					unsigned int connectLayer = (bits >> 12) & 0x3f;
					if (connectLayer >= 2 && connectLayer <= 15 &&
						(bits & 7) == 0)
					{
						bfmeResolveZones(cell.zone, layers[connectLayer].zone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0]);
					}

					if (y <= bounds.loY)
						goto check_left_cell;
					{
					BfmeZoneCell &other = map[y - 1][x];
					if (cell.zone == other.zone ||
						!sameProfileCell(bits, other.flags, layer,
							crusher, terrainOnly))
						goto check_left_cell;

					unsigned int otherBits = other.flags;
					if (substituteZero(bits, 1) == substituteZero(otherBits, 1) &&
						((bits ^ otherBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, other.zone,
							m_zoneEquivalency[profile][2],
							m_zoneListHeads[profile][2],
							m_zoneListNext[profile][2]);

					if (substituteZero(bits, 3) == substituteZero(otherBits, 3) &&
						((bits ^ otherBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, other.zone,
							m_zoneEquivalency[profile][3],
							m_zoneListHeads[profile][3],
							m_zoneListNext[profile][3]);

					if (substituteZero(bits, 2) == substituteZero(otherBits, 2) &&
						((bits ^ otherBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, other.zone,
							m_zoneEquivalency[profile][1],
							m_zoneListHeads[profile][1],
							m_zoneListNext[profile][1]);

					if (substituteZero(bits, 4) == substituteZero(otherBits, 4) &&
						((bits ^ otherBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, other.zone,
							m_zoneEquivalency[profile][4],
							m_zoneListHeads[profile][4],
							m_zoneListNext[profile][4]);

					if (((bits & 7) == 2) == ((otherBits & 7) == 2))
						bfmeResolveZones(cell.zone, other.zone,
							m_zoneEquivalency[profile][5],
							m_zoneListHeads[profile][5],
							m_zoneListNext[profile][5]);

					unsigned int cellType = (bits >> 6) & 0x3f;
					unsigned int otherType = (otherBits >> 6) & 0x3f;
					unsigned int cellConnect = (bits >> 12) & 0x3f;
					unsigned int otherConnect = (otherBits >> 12) & 0x3f;
					if (((bits ^ otherBits) & 7) == 0 &&
						(cellType == otherType || cellType == otherConnect ||
						 cellConnect == otherType ||
						 (cellConnect == 16 && otherConnect == 16)))
						bfmeResolveZones(cell.zone, other.zone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0]);
					}

				check_left_cell:
					if (x <= bounds.loX)
						continue;
					BfmeZoneCell &left = map[y][x - 1];
					if (cell.zone == left.zone ||
						!sameProfileCell(bits, left.flags, layer,
							crusher, terrainOnly))
						continue;

					unsigned int leftBits = left.flags;
					if (substituteZero(bits, 1) == substituteZero(leftBits, 1) &&
						((bits ^ leftBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, left.zone,
							m_zoneEquivalency[profile][2],
							m_zoneListHeads[profile][2],
							m_zoneListNext[profile][2]);
					if (substituteZero(bits, 3) == substituteZero(leftBits, 3) &&
						((bits ^ leftBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, left.zone,
							m_zoneEquivalency[profile][3],
							m_zoneListHeads[profile][3],
							m_zoneListNext[profile][3]);
					if (substituteZero(bits, 2) == substituteZero(leftBits, 2) &&
						((bits ^ leftBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, left.zone,
							m_zoneEquivalency[profile][1],
							m_zoneListHeads[profile][1],
							m_zoneListNext[profile][1]);
					if (substituteZero(bits, 4) == substituteZero(leftBits, 4) &&
						((bits ^ leftBits) & 0xfc0) == 0)
						bfmeResolveZones(cell.zone, left.zone,
							m_zoneEquivalency[profile][4],
							m_zoneListHeads[profile][4],
							m_zoneListNext[profile][4]);
					if (((bits & 7) == 2) == ((leftBits & 7) == 2))
						bfmeResolveZones(cell.zone, left.zone,
							m_zoneEquivalency[profile][5],
							m_zoneListHeads[profile][5],
							m_zoneListNext[profile][5]);

					unsigned int cellType = (bits >> 6) & 0x3f;
					unsigned int otherType = (leftBits >> 6) & 0x3f;
					unsigned int cellConnect = (bits >> 12) & 0x3f;
					unsigned int otherConnect = (leftBits >> 12) & 0x3f;
					if (((bits ^ leftBits) & 7) == 0 &&
						(cellType == otherType || cellType == otherConnect ||
						 cellConnect == otherType ||
						 (cellConnect == 16 && otherConnect == 16)))
						bfmeResolveZones(cell.zone, left.zone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0]);
				}
			}
		}
		else
		{
			// The alternate path consumes a scheduler-owned object list.  Its
			// cell/layer bridge pass is identical and provides the established
			// profile-table side effects while that list layout is identified.
			for (int x = firstX; x < lastX; ++x)
				for (int y = bounds.loY; y <= bounds.hiY; ++y)
				{
					BfmeZoneCell &cell = map[y][x];
					unsigned int connectLayer = (cell.flags >> 12) & 0x3f;
					if (connectLayer >= 2 && connectLayer <= 15 &&
						(cell.flags & 7) == 0)
						bfmeResolveZones(cell.zone, layers[connectLayer].zone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0]);
				}
			(void)firstObject;
			(void)lastObject;
		}
	}
}
