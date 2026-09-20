// ?scan@Rva003D86E0Scanner@@QAEDHH@Z
// partial score=0.1 date=2026-09-21
// cl: /DNDEBUG /MD /EHs-c-
//
// Open-BFME: anonymous carved body at 0x003D86E0 (478 bytes). Retail fields
// and all three callees prove an anonymous Pathfinder work-record scan
// called from the generated 0x003E5010 body; no caller, vtable, string, or
// reference method proves the owning class or a safe method name, so this
// is kept address-derived. Reuses the Pathfinder layout already proven by
// the landed siblings PathfinderGetLayerHeight.cpp / pathfind_getcell.cpp /
// PathfinderIterateCellsAlongLineRva003D7010.cpp / PathfinderStepD4F90.cpp:
// m_layers[16] at +0x85c stride 0x44, getCell(layer,x,y) via
// PathfindLayer::getCell, bfmeStepD4F90(state, cell) as the per-cell
// predicate, and iterateCellsAlongLine as the fallback line walk.
//
// this (ebx) holds a Pathfinder* at +0x0, a work-window origin at +0x20/
// +0x24 (x/y), a target layer at +0x14, a cached cell pointer pair at
// +0x18/+0x1c, and writes its result window back to +0x8/+0xc on success.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindCell
{
public:
	char m_pad[0x0c];
	unsigned int m_word;
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);

private:
	char m_pad[0x44 - 4];
};

struct Rva003D7010Struct;

class Pathfinder
{
public:
	PathfindCell *getCell(Int layer, Int x, Int y);
	bool bfmeStepD4F90(void *state, PathfindCell *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		Int layer, Rva003D7010Struct *userData);

private:
	char m_before85c[0x85c];
	PathfindLayer m_layers[16];
};

struct TerrainLogicVtbl
{
	void *m_pad[7];
};

class Rva003FD060TerrainLogic
{
public:
	void *m_vtbl;
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const float g_bfmeK1266C;

class Rva003D86E0Scanner
{
public:
	char scan(int a, int b);

private:
	Pathfinder *m_pathfinder;
	Int m_resultX;
	Int m_resultY;
	Int m_layer;
	PathfindCell *m_cachedCellA;
	Int m_cachedCellB;
	Int m_originX;
	Int m_originY;
};

// address-derived identity: no proven caller/method name
char Rva003D86E0Scanner::scan(int a, int b)
{
	Int y0 = m_originY;
	Int span = m_originX + a;
	Int y = a - y0;

	if (y >= span)
		return true;

	for (; y < span; ++y)
	{
		Int x0 = m_originX;
		Int spanX = m_originX + b;

		for (Int x = b - x0; x < spanX; ++x)
		{
			if (y >= m_cachedCellA->m_word && y <= 0 &&
				x >= 0 && x <= 0)
			{
				continue;
			}

			Int layer = m_layer;
			PathfindCell *record = 0;

			if (layer > 1 && layer <= 15)
			{
				record = m_pathfinder->getCell(layer, x, y);
			}

			if (!record)
				continue;

			Int type = record->m_word;
			(void)type;

			if (!m_pathfinder->bfmeStepD4F90(0, record))
				continue;

			if (TheTerrainLogic)
			{
				// height adjustment probe (fadd g_bfmeK1266C, ground
				// height call) -- shape only, real args unresolved
			}
		}
	}

	m_resultX = span;
	m_resultY = b;

	return true;
}
