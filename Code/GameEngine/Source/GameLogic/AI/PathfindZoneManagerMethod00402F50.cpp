// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include "Lib/BaseType.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class PathfindCell;

class PathfindLayer
{
public:
	void bfmeApplyZone();
};

typedef bool Bool;
class Waypoint;

class ZoneBlock
{
public:
	void bfmeSetWaypoint(Bool shouldInsert, Waypoint *waypoint);
};

class Rva00402C50
{
public:
	void transferBlocks();
};

#pragma pack(push, 1)
class PathfindZoneManager
{
public:
	void method00402F50(PathfindCell **map, PathfindLayer *layers,
		const IRegion2D &bounds);

private:
	unsigned char m_before23298[0x23298];
	int m_word23298;
	int m_swapArea[12][6];
	unsigned char m_pad1[0x23628 - 0x2329c - 12 * 6 * 4];
	ZoneBlock **m_zoneBlocks;
	unsigned char m_pad2[8];
	int m_word23634;
	int m_otherSwapArea[12][6];
};
#pragma pack(pop)

void PathfindZoneManager::method00402F50(PathfindCell **map,
	PathfindLayer *layers, const IRegion2D &bounds)
{
	PathfindZoneManager *self;
	self = this;
	Int y = bounds.lo.y;
	if (y <= bounds.hi.y)
	{
		do
		{
			Int x = bounds.lo.x;
			if (x <= bounds.hi.x)
			{
				Int rowOffset = y << 4;
				do
				{
					char *cell = (char *)map[x] + rowOffset;
					*(short *)(cell + 8) = *(short *)(cell + 0xa);
					++x;
				} while (x <= bounds.hi.x);
			}
			++y;
		} while (y <= bounds.hi.y);
	}

	self->m_word23634 = self->m_word23298;
	self->m_word23298 = 0;

	for (Int group = 0; group < 6; ++group)
	{
		char *record = (char *)&self->m_swapArea[0][group];
		for (Int i = 0; i < 12; ++i)
		{
			int *a = (int *)record;
			int *b = (int *)(record + 0x39c);
			int bValue = *b;
			_ReadWriteBarrier();
			int aValue = *a;
			*b = aValue;
			*a = bValue;
			record += 0x18;
		}
	}

	Int loX = bounds.lo.x;
	Int width = bounds.hi.x - loX;
	Int loY = bounds.lo.y;
	Int blockCountX = (width + 16) / 16;
	Int height = bounds.hi.y - loY;
	Int blockCountY = (height + 16) / 16;

	for (Int col = 0; col < blockCountX; ++col)
	{
		if (blockCountY > 0)
		{
			Int rowOffset = 0;
			Int remaining = blockCountY;
			do
			{
				ZoneBlock *block = (ZoneBlock *)((char *)self->m_zoneBlocks[col] + rowOffset);
				((Rva00402C50 *)block)->transferBlocks();
				rowOffset += 0x228;
			} while (--remaining != 0);
		}
	}

	PathfindLayer *layer = layers;
	Int layerCount = 16;
	do
	{
		layer->bfmeApplyZone();
		layer = (PathfindLayer *)((char *)layer + 0x44);
	} while (--layerCount != 0);
}
