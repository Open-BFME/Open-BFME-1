// ?d_00402f50@@YAXXZ
// partial score=0.26 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME: carved body at retail 0x00402F50 (293 B). reverse/symbols.csv
// also pins this VA to an unrelated ICF-merged destructor
// (??1Gen008030A0@@UAE@XZ); the actual bytes here are a PathfindZoneManager
// worker, address-derived. Three phases: (1) copy each cell's zone field
// into a shadow field over the IRegion2D bounds (3rd param); (2) swap two
// parallel 6x12 record arrays at this+0x2329c/this+0x2363c-ish (double
// buffer flip); (3) two grid loops over m_zoneBlocks (this+0x23628,
// matching the 0x00408480 body) and a 16-entry PathfindLayer array calling
// the landed PathfindLayer::bfmeApplyZone.

typedef int Int;

struct ICoord2D { Int x; Int y; };
struct IRegion2D { ICoord2D lo; ICoord2D hi; };

class PathfindLayer
{
public:
	void bfmeApplyZone();
};

class ZoneBlock
{
public:
	void bfmeProcessCell(void *p1);
};

#pragma pack(push, 1)
class PathfindZoneManager
{
public:
	void bfmeRebuildZones00402F50(void **map, void *unused, IRegion2D *bounds);

private:
	unsigned char m_before2329c[0x2329c];
	int m_swapArea[6][12];                  // +0x2329c .. +0x2331c-ish (6 groups of 12 dwords, stride 0x18)
	unsigned char m_pad1[0x23628 - 0x2329c - 6 * 12 * 4];
	ZoneBlock **m_zoneBlocks;               // +0x23628
	unsigned char m_pad2[4];
	PathfindLayer m_layers[16];             // +0x23630-ish, stride 0x44
};
#pragma pack(pop)

void PathfindZoneManager::bfmeRebuildZones00402F50(void **map, void *unused, IRegion2D *bounds)
{
	PathfindZoneManager *self = this;
	for (Int y = bounds->lo.y; y <= bounds->hi.y; ++y)
	{
		Int rowOffset = y << 4;
		for (Int x = bounds->lo.x; x <= bounds->hi.x; ++x)
		{
			char *cell = (char *)map[x] + rowOffset;
			*(short *)(cell + 8) = *(short *)(cell + 0xa);
		}
	}

	for (Int group = 0; group < 6; ++group)
	{
		char *rec = (char *)&self->m_swapArea[group][0];
		for (Int i = 0; i < 12; ++i)
		{
			int *a = (int *)rec;
			int *b = (int *)(rec + 0x39c);
			int t = *b;
			*b = *a;
			*a = t;
			rec += 0x18;
		}
	}

	Int loX = bounds->lo.x;
	Int width = bounds->hi.x - loX;
	Int loY = bounds->lo.y;
	Int blockCountX = (width + 16) / 16;
	Int height = bounds->hi.y - loY;
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
				block->bfmeProcessCell(unused);
				rowOffset += 0x228;
			} while (--remaining != 0);
		}
	}

	for (Int i = 0; i < 16; ++i)
		self->m_layers[i].bfmeApplyZone();
}
