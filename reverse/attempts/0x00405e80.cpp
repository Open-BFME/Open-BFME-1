// ?d_00405e80@@YAXXZ
// partial score=0.1 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

typedef unsigned char Byte;
typedef unsigned short UShort;

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct PathfindCell
{
	char opaque00[0x0A];
	UShort zone;
	unsigned int properties;
};

struct Rva00405E80ZoneBlock
{
	char opaque00[0x224];
	Byte interactsWithBridge;
	char opaque225[3];
};

struct Rva00405E80TreeNode
{
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

class Rva00405E80DebugManager
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

extern Rva00405E80DebugManager *TheGen001336E5C;
extern void __cdecl _bfme_debugRecordCallsite(int kind);
extern void __cdecl bfmeResolveZones(int sourceZone, int targetZone,
	UShort *groundCliff, UShort *groundWater, UShort *groundRubble, int size);

class Rva00405E80ZoneManager
{
private:
	char opaque00000[0x18];
	UShort groundCliff[24000];
	UShort groundWater[24000];
	UShort groundRubble[24000];
	int maxZone;
	char opaque2329C[0x360];
	Rva00405E80Tree pendingCells;
	char opaque23604[0x24];
	Rva00405E80ZoneBlock **zoneBlocks;

	static __forceinline bool compatible(const PathfindCell &a, const PathfindCell &b)
	{
		unsigned int av = a.properties;
		unsigned int bv = b.properties;
		if (((av ^ bv) & 7) != 0)
			return false;

		unsigned int a6 = (av >> 6) & 0x3F;
		unsigned int b6 = (bv >> 6) & 0x3F;
		unsigned int a12 = (av >> 12) & 0x3F;
		unsigned int b12 = (bv >> 12) & 0x3F;
		if (a6 != b6 && a6 != b12 && a12 != b6 && !(a12 == 0x10 && b12 == 0x10))
			return false;
		if (((av >> 20) ^ (bv >> 20)) & 1)
			return false;
		if (((av >> 21) ^ (bv >> 21)) & 1)
			return false;
		return ((av ^ bv) & 0x00C00000) == 0;
	}

	__forceinline void applyZone(PathfindCell &target, const PathfindCell &source)
	{
		int sourceZone = source.zone;
		int targetZone = target.zone;
		if (targetZone == 0)
		{
			target.zone = (UShort)sourceZone;
			return;
		}
		if (targetZone != sourceZone)
			bfmeResolveZones(sourceZone, targetZone, groundCliff, groundWater,
				groundRubble, maxZone);
	}

public:
	void Rva00405E80InitialZonePass(PathfindCell **map,
		const IRegion2D &globalBounds, int startPercent, int endPercent);
};

void Rva00405E80ZoneManager::Rva00405E80InitialZonePass(PathfindCell **map,
	const IRegion2D &globalBounds, int startPercent, int endPercent)
{
	if (startPercent == 0)
	{
		maxZone = 1;
		groundCliff[0] = 0;
		groundWater[0] = 0xFFFF;
		groundRubble[0] = 0xFFFF;
		pendingCells.clear();
	}

	int xCount = (globalBounds.hi.x - globalBounds.lo.x + 16) / 16;
	int yCount = (globalBounds.hi.y - globalBounds.lo.y + 16) / 16;
	int firstXBlock = xCount * startPercent / 100;
	int lastXBlock = xCount * endPercent / 100;

	for (int xBlock = firstXBlock; xBlock < lastXBlock; ++xBlock)
	{
		for (int yBlock = 0; yBlock < yCount; ++yBlock)
		{
			IRegion2D bounds;
			bounds.lo.x = globalBounds.lo.x + xBlock * 16;
			bounds.lo.y = globalBounds.lo.y + yBlock * 16;
			bounds.hi.x = bounds.lo.x + 15;
			bounds.hi.y = bounds.lo.y + 15;
			if (bounds.hi.x > globalBounds.hi.x)
				bounds.hi.x = globalBounds.hi.x;
			if (bounds.hi.y > globalBounds.hi.y)
				bounds.hi.y = globalBounds.hi.y;

			Rva00405E80ZoneBlock &block = zoneBlocks[xBlock][yBlock];
			block.interactsWithBridge = 0;
			for (int y = bounds.lo.y; y <= bounds.hi.y; ++y)
			{
				for (int x = bounds.lo.x; x <= bounds.hi.x; ++x)
				{
					PathfindCell &cell = map[x][y];
					cell.zone = 0;
					if (x > bounds.lo.x && compatible(cell, map[x - 1][y]))
						applyZone(cell, map[x - 1][y]);
					if (y > bounds.lo.y && compatible(cell, map[x][y - 1]))
						applyZone(cell, map[x][y - 1]);
					if (cell.zone == 0)
					{
						cell.zone = (UShort)maxZone;
						groundCliff[maxZone] = (UShort)maxZone;
						groundWater[maxZone] = (UShort)maxZone;
						groundRubble[maxZone] = 0xFFFF;
						++maxZone;
						if (maxZone >= 24000)
						{
							_bfme_debugRecordCallsite(1);
							TheGen001336E5C->beginReport();
							Rva00405E80DebugReport *report =
								TheGen001336E5C->startReport(0, 0);
							report->addMessage("Ran out of pathfind zones.  SERIOUS ERROR! jba.")->finish(1);
						}
					}

					unsigned int connectLayer = (cell.properties >> 12) & 0x3F;
					if (connectLayer > 1 && connectLayer < 16)
						block.interactsWithBridge = 1;
				}
			}
		}
	}
}
