// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /Igame/Libraries/Source/WWVegas/WWMath
// RVA 0x00405E80: initial incremental zone-building pass.
// Named scheduler at 0x00408AD0 calls via ILT 0x0002FF9F with
// (map, bounds, startPercent, endPercent); ret16 confirms the ABI.
// Retail witnesses 16-byte cells, 0x228-byte blocks, three 24000-entry
// zone tables, and the manager map at +0x235FC.
#include "region.h"

typedef unsigned char Byte;
typedef unsigned short UShort;

class PathfindCell
{
public:
	char opaque00[0x0A];
	UShort zone;
	union { unsigned int properties; struct {
 unsigned type:3, unused03:3, layer06:6, layer12:6, unused18:2, flag20:1, flag21:1, field22:2;
}; };
};

struct Rva00405E80ZoneBlock
{
	char opaque00[0x224];
	Byte interactsWithBridge;
	char opaque225[3];
};

struct Rva00405E80TreeNode
{
	int color;
	Rva00405E80TreeNode *parent;
	Rva00405E80TreeNode *left;
	Rva00405E80TreeNode *right;
};

class Rva00405E80Tree
{
public:
	Rva00405E80TreeNode *header;
	int size;

	void eraseNodes(Rva00405E80TreeNode *node);

	__forceinline void clear()
	{
		if (size != 0)
		{
			eraseNodes(header->parent);
			header->left = header;
			header->parent = 0;
			header->right = header;
			size = 0;
		}
	}
};

class Rva00405E80DebugReport
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Rva00405E80DebugReport *addMessage(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void finish(int severity);
};

struct Rva00889690Obj
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual Rva00405E80DebugReport *startReport(void *a, void *b);
};

extern Rva00889690Obj *g_rva00889690;
extern void __cdecl _bfme_debugRecordCallsite(int kind);
extern void __cdecl bfmeResolveZones(int sourceZone, int targetZone,
	UShort *zoneEquivalency18, UShort *zoneListHeadsBB98, UShort *zoneListNext17718, int size);

class PathfindZoneManager
{
private:
	char opaque00000[0x18];
	UShort zoneEquivalency18[24000];
	UShort zoneListHeadsBB98[24000];
	UShort zoneListNext17718[24000];
	unsigned maxZone;
	char opaque2329C[0x360];
	Rva00405E80Tree pendingCells;
	char opaque23604[0x24];
	Rva00405E80ZoneBlock **zoneBlocks;

    static __forceinline bool compatible(const PathfindCell &a, const PathfindCell &b)
    {
        return a.type == b.type &&
            (a.layer06 == b.layer06 || a.layer06 == b.layer12 ||
             a.layer12 == b.layer06 || (a.layer12 == 16 && b.layer12 == 16)) &&
            (bool)a.flag20 == (bool)b.flag20 && (bool)a.flag21 == (bool)b.flag21 && a.field22 == b.field22;
    }

	static __forceinline void applyZone(PathfindCell &target, const PathfindCell &source,
        UShort *zoneEquivalency18, UShort *zoneListHeadsBB98, UShort *zoneListNext17718, unsigned maxZone)
	{
		int sourceZone = source.zone;
		int targetZone = target.zone;
		if (targetZone == 0)
		{
			target.zone = (UShort)sourceZone;
			return;
		}
		bfmeResolveZones(sourceZone, targetZone, zoneEquivalency18, zoneListHeadsBB98,
				zoneListNext17718, maxZone);
	}

public:
	void method00405E80(PathfindCell **map,
		const IRegion2D &globalBounds, int startPercent, int endPercent);
};

void PathfindZoneManager::method00405E80(PathfindCell **map,
	const IRegion2D &globalBounds, int startPercent, int endPercent)
{
	if (startPercent == 0)
	{
		maxZone = 1;
		zoneEquivalency18[0] = 0;
		zoneListNext17718[0] = 0xFFFF;
		zoneListHeadsBB98[0] = 0xFFFF;
		pendingCells.clear();
	}

	int xCount = (globalBounds.x_max - globalBounds.x_min + 16) / 16;
	int yCount = (globalBounds.y_max - globalBounds.y_min + 16) / 16;
	int firstXBlock = xCount * startPercent / 100;
	int lastXBlock = xCount * endPercent / 100;

	for (int xBlock = firstXBlock; xBlock < lastXBlock; ++xBlock)
	{
		for (int yBlock = 0; yBlock < yCount; ++yBlock)
		{
			IRegion2D bounds;
			bounds.x_min = globalBounds.x_min + xBlock * 16;
			bounds.y_min = globalBounds.y_min + yBlock * 16;
			bounds.x_max = bounds.x_min + 15;
			bounds.y_max = bounds.y_min + 15;
			if (bounds.x_max > globalBounds.x_max)
				bounds.x_max = globalBounds.x_max;
			if (bounds.y_max > globalBounds.y_max)
				bounds.y_max = globalBounds.y_max;

			if(bounds.x_min>bounds.x_max || bounds.y_min>bounds.y_max) continue;
            zoneBlocks[xBlock][yBlock].interactsWithBridge = 0;
			for (int y = bounds.y_min; y <= bounds.y_max; ++y)
			{
				for (int x = bounds.x_min; x <= bounds.x_max; ++x)
				{
					PathfindCell &cell = map[x][y];
					cell.zone = 0;
					if (x > bounds.x_min && compatible(cell, map[x - 1][y]))
						applyZone(cell, map[x - 1][y],zoneEquivalency18,zoneListHeadsBB98,zoneListNext17718,maxZone);
					if (y > bounds.y_min && compatible(cell, map[x][y - 1]))
						applyZone(cell, map[x][y - 1],zoneEquivalency18,zoneListHeadsBB98,zoneListNext17718,maxZone);
					if (cell.zone == 0)
					{
						cell.zone = (UShort)maxZone;
						zoneEquivalency18[maxZone] = (UShort)maxZone;
						zoneListHeadsBB98[maxZone] = (UShort)maxZone;
						zoneListNext17718[maxZone] = 0xFFFF;
						++maxZone;
						if (maxZone >= 24000)
						{
							_bfme_debugRecordCallsite(1);
							g_rva00889690->beginReport();
							Rva00405E80DebugReport *report =
								g_rva00889690->startReport(0, 0);
							report->addMessage("Ran out of pathfind zones.  SERIOUS ERROR! jba.")->finish(1);
                            break;
						}
					}

					unsigned int connectLayer = (cell.properties >> 12) & 0x3F;
					if (connectLayer != 0 && connectLayer != 1 && (int)connectLayer < 16)
						zoneBlocks[xBlock][yBlock].interactsWithBridge = 1;
				}
			}
		}
	}
}
