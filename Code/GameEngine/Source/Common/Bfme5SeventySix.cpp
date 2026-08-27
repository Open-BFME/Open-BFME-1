// cl: /GX

// Six more: a delta adjustment, two bounds-checked cell-range operations, a
// hash-bucket lookup, an append to a global table, and another clamped read.

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
void *__cdecl operator new[](unsigned int size);

__forceinline Real bfmeFloatFloorFC(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real bfmeFloatCeilFC(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline long bfmeFloatToLongFC(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class Gen_0078D130
{
public:
	void bfmeAdjust(int firstX, int firstY, int secondX, int secondY);

private:
	char m_bfmeHead[0xD0];					// +0x000
	int m_bfmeX;						// +0x0D0
	int m_bfmeY;						// +0x0D4
	char m_bfmeGap[5];					// +0x0D8
	bool m_bfmeDirty;					// +0x0DD
};

// ?bfmeAdjust@Gen_0078D130@@QAEXHHHH@Z
void Gen_0078D130::bfmeAdjust(int firstX, int firstY, int secondX, int secondY)
{
	m_bfmeX = m_bfmeX + (secondX - firstX);
	m_bfmeY = m_bfmeY + (secondY - firstY);

	m_bfmeDirty = true;
}

class BfmeCellFC
{
public:
	BfmeCellFC();
	~BfmeCellFC();
	void bfmeUpdate(int amount, bool absolute);

	unsigned char m_bfmeKind;				// +0x00
	unsigned char m_bfmeGap[3];				// +0x01
	int m_bfmeValue;					// +0x04
};

BfmeCellFC::BfmeCellFC()
	: m_bfmeKind(0x80), m_bfmeValue(0)
{
}

BfmeCellFC::~BfmeCellFC()
{
}

typedef void (__cdecl *BfmeCellVisitorFC)(int x, int y,
	unsigned char kind);

struct BfmePointFC
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct Region3D
{
	__forceinline Region3D() {}

	__forceinline Region3D(const Region3D &other)
	{
		lo.x = other.lo.x;
		lo.y = other.lo.y;
		lo.z = other.lo.z;
		hi.x = other.hi.x;
		hi.y = other.hi.y;
		hi.z = other.hi.z;
	}

	__forceinline ~Region3D() {}

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }

	Coord3D lo;
	Coord3D hi;
};

class Gen_008812D0
{
public:
	Gen_008812D0();
	~Gen_008812D0();
	void bfmeReset();
	void bfmeConfigure(Region3D region, Real cellSize);
	void bfmeSetRegion(const Region3D *region, Real cellSize);
	BfmeCellFC *bfmeAt(int x, int y) const;
	void bfmeGetCellRange(BfmeCellFC **first, BfmeCellFC **last,
		int x1, int x2, int y);
	BfmeCellFC *bfmeCellAtWorld(Real x, Real y) const;
	void bfmeVisitCells(void);
	int bfmeValueAtWorld(const BfmePointFC *point) const;
	void bfmeApplyCircle(int x, int y, int radius, int amount, bool absolute);

	friend class BfmeRangeUpdaterFC;
	friend class BfmeTaintManager;

private:
	Region3D m_bfmeRegion;					// +0x00
	Real m_bfmeCellSize;					// +0x18
	float m_bfmeCellSizeInv;				// +0x1C
	int m_bfmeWidth;					// +0x20
	int m_bfmeHeight;					// +0x24
	BfmeCellFC *m_bfmeCells;				// +0x28
	BfmeCellVisitorFC m_bfmeVisitor;			// +0x2C
};

class BfmeRangeUpdaterFC
{
public:
	__declspec(noinline) void operator()(int firstX, int lastX, int y);

private:
	Gen_008812D0 *m_bfmeGrid;
	int m_bfmeAmount;
	bool m_bfmeAbsolute;
};

class BfmeTaintManager
{
public:
	void bfmeResetGrid();
	void bfmeApplyCircleWorld(const BfmePointFC *point, Real radius,
		int amount, bool absolute);

private:
	unsigned char m_bfmeHead[0x0C];				// +0x00
	Gen_008812D0 *m_bfmeGrid;				// +0x0C
};

// ??0Gen_008812D0@@QAE@XZ
Gen_008812D0::Gen_008812D0()
{
	m_bfmeRegion.lo.zero();
	m_bfmeWidth = 0;
	m_bfmeHeight = 0;
	m_bfmeCells = 0;
	m_bfmeVisitor = 0;
	m_bfmeCellSize = 1.0f;
	m_bfmeRegion.hi.zero();

	bfmeConfigure(m_bfmeRegion, 1.0f);
}

// ?bfmeConfigure@Gen_008812D0@@QAEXURegion3D@@M@Z
void Gen_008812D0::bfmeConfigure(Region3D region, Real cellSize)
{
	if (region.width() < 1.0f)
		region.hi.x = region.lo.x + 1.0f;
	if (region.height() < 1.0f)
		region.hi.y = region.lo.y + 1.0f;

	Real cellSizeInv = 1.0f / cellSize;
	int width = bfmeFloatToLongFC(bfmeFloatCeilFC(
		region.width() * cellSizeInv));
	if (width < 1)
		width = 1;
	int height = bfmeFloatToLongFC(bfmeFloatCeilFC(
		region.height() * cellSizeInv));
	if (height < 1)
		height = 1;

	BfmeCellFC *cells = new BfmeCellFC[width * height];
	BfmeCellFC *cell = cells;
	for (unsigned int y = 0; y < (unsigned int)height; ++y)
	{
		int oldY = bfmeFloatToLongFC(bfmeFloatFloorFC(
			((Real)y * cellSize + region.lo.y - m_bfmeRegion.lo.y)
				* m_bfmeCellSizeInv));
		if (oldY >= 0 && oldY < m_bfmeHeight)
		{
			for (unsigned int x = 0; x < (unsigned int)width;
				++x, ++cell)
			{
				int oldX = bfmeFloatToLongFC(bfmeFloatFloorFC(
					((Real)x * cellSize + region.lo.x - m_bfmeRegion.lo.x)
						* m_bfmeCellSizeInv));
				if (oldX >= 0 && oldX < m_bfmeWidth)
					cell->m_bfmeKind = m_bfmeCells[
						oldY * m_bfmeWidth + oldX].m_bfmeKind;
			}
		}
		else
		{
			cell += width;
		}
	}

	delete[] m_bfmeCells;
	m_bfmeCells = cells;
	m_bfmeRegion = region;
	m_bfmeCellSizeInv = cellSizeInv;
	m_bfmeWidth = width;
	m_bfmeHeight = height;
	m_bfmeCellSize = cellSize;
}

// ??1Gen_008812D0@@QAE@XZ
Gen_008812D0::~Gen_008812D0()
{
	delete[] m_bfmeCells;
}

// ?bfmeSetRegion@Gen_008812D0@@QAEXPBURegion3D@@M@Z
void Gen_008812D0::bfmeSetRegion(const Region3D *region, Real cellSize)
{
	if (cellSize <= 0.0f)
		cellSize = m_bfmeCellSize;

	if (!(region->width() < 0.0f)
		&& !(region->height() < 0.0f))
	{
		bfmeConfigure(*region, cellSize);
	}
}

// ?bfmeResetGrid@BfmeTaintManager@@QAEXXZ
void BfmeTaintManager::bfmeResetGrid()
{
	m_bfmeGrid->bfmeReset();

	Region3D region;
	region.lo.zero();
	region.hi.zero();
	m_bfmeGrid->bfmeSetRegion(&region, 0.0f);
}

// ?bfmeAt@Gen_008812D0@@QBEPAVBfmeCellFC@@HH@Z
BfmeCellFC *Gen_008812D0::bfmeAt(int x, int y) const
{
	if (x >= 0 && x < m_bfmeWidth && y >= 0 && y < m_bfmeHeight)
		return &m_bfmeCells[m_bfmeWidth * y + x];

	return 0;
}

// ?bfmeGetCellRange@Gen_008812D0@@QAEXPAPAVBfmeCellFC@@0HHH@Z
void Gen_008812D0::bfmeGetCellRange(BfmeCellFC **first,
	BfmeCellFC **last, int x1, int x2, int y)
{
	if (x2 < 0 || x1 >= m_bfmeWidth || y < 0 || y >= m_bfmeHeight)
	{
		*last = 0;
		*first = 0;
		return;
	}

	BfmeCellFC *row = m_bfmeCells + y * m_bfmeWidth;
	*last = row;
	*first = row;
	if (x1 > 0)
		*first = row + x1;

	*last += x2 < m_bfmeWidth ? x2 + 1 : m_bfmeWidth;
}

// ?bfmeCellAtWorld@Gen_008812D0@@QBEPAVBfmeCellFC@@MM@Z
BfmeCellFC *Gen_008812D0::bfmeCellAtWorld(Real worldX, Real worldY) const
{
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldX - m_bfmeRegion.lo.x) * m_bfmeCellSizeInv));
	if (x < 0 || x >= m_bfmeWidth)
		return 0;

	int y = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldY - m_bfmeRegion.lo.y) * m_bfmeCellSizeInv));
	if (y < 0 || y >= m_bfmeHeight)
		return 0;

	return &m_bfmeCells[y * m_bfmeWidth + x];
}

// ?bfmeVisitCells@Gen_008812D0@@QAEXXZ
void Gen_008812D0::bfmeVisitCells(void)
{
	BfmeCellFC *end = m_bfmeCells + m_bfmeWidth * m_bfmeHeight;
	int x = 0;
	int y = 0;

	for (BfmeCellFC *cell = m_bfmeCells; cell != end; ++cell)
	{
		m_bfmeVisitor(x, y, cell->m_bfmeKind);
		++x;
		if (x == m_bfmeWidth)
		{
			x = 0;
			++y;
		}
	}
}

// ?bfmeValueAtWorld@Gen_008812D0@@QBEHPBUBfmePointFC@@@Z
int Gen_008812D0::bfmeValueAtWorld(const BfmePointFC *point) const
{
	BfmeCellFC *cell = bfmeCellAtWorld(point->x, point->y);
	return cell ? cell->m_bfmeValue : 0;
}

// ??RBfmeRangeUpdaterFC@@QAEXHHH@Z
void BfmeRangeUpdaterFC::operator()(int firstX, int lastX, int y)
{
	BfmeCellFC *first;
	BfmeCellFC *last;
	m_bfmeGrid->bfmeGetCellRange(&first, &last, firstX, lastX, y);

	for (BfmeCellFC *cell = first; cell != last; ++cell)
	{
		cell->bfmeUpdate(m_bfmeAmount, m_bfmeAbsolute);
		m_bfmeGrid->m_bfmeVisitor(firstX, y, cell->m_bfmeKind);
		++firstX;
	}
}

// ?bfmeRasterCircleFC@@YAXHHHVBfmeRangeUpdaterFC@@@Z
void __cdecl bfmeRasterCircleFC(int centerX, int centerY, const int radius,
	BfmeRangeUpdaterFC updater)
{
	int x = 0;
	int y = radius;
	int d = (1 - radius) << 1;
	int firstX = centerX;
	int lastX = centerX;

	for (;;)
	{
		if (d + y > 0)
		{
			if (y == 0 && radius == 1)
			{
				++x;
				++lastX;
				--firstX;
			}

			updater(firstX, lastX, centerY + y);
			if (y == 0)
				return;

			updater(firstX, lastX, centerY - y);
			--y;
			d -= ((y << 1) - 1);
		}

		if (x > d)
		{
			++x;
			++lastX;
			--firstX;
			d += ((x << 1) + 1);
		}
	}
}

// ?bfmeApplyCircleWorld@BfmeTaintManager@@QAEXPBUBfmePointFC@@MH_N@Z
void BfmeTaintManager::bfmeApplyCircleWorld(const BfmePointFC *point,
	Real radius, int amount, bool absolute)
{
	int cellRadius = bfmeFloatToLongFC(bfmeFloatCeilFC(
		radius * m_bfmeGrid->m_bfmeCellSizeInv));
	int y = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(point->y - m_bfmeGrid->m_bfmeRegion.lo.y)
			* m_bfmeGrid->m_bfmeCellSizeInv));
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(point->x - m_bfmeGrid->m_bfmeRegion.lo.x)
			* m_bfmeGrid->m_bfmeCellSizeInv));

	m_bfmeGrid->bfmeApplyCircle(x, y, cellRadius, amount, absolute);
}

class BfmeNodeFC
{
public:
	BfmeNodeFC *m_bfmeNext;					// +0x00
	unsigned int m_bfmeKey;					// +0x04
};

class Gen_00889290
{
public:
	BfmeNodeFC *bfmeFind(unsigned int key) const;

private:
	int m_bfmeHead[6];					// +0x00
	BfmeNodeFC *m_bfmeBuckets[10007];			// +0x18
};

// ?bfmeFind@Gen_00889290@@QBEPAVBfmeNodeFC@@I@Z
BfmeNodeFC *Gen_00889290::bfmeFind(unsigned int key) const
{
	BfmeNodeFC *node = m_bfmeBuckets[key % 10007];

	while (node != 0)
	{
		if (node->m_bfmeKey == key)
			return node;

		node = node->m_bfmeNext;
	}

	return 0;
}

class BfmeTripleDU
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

extern BfmeTripleDU g_bfmeEntriesDU[16];			// retail 0x013378E0
extern int g_bfmeCountDU;					// retail 0x013379A4

// ?bfmeAppend@@YAXHHH@Z
void __cdecl bfmeAppend(int first, int second, int third)
{
	int index = g_bfmeCountDU;

	g_bfmeEntriesDU[index].m_bfmeFirst = first;
	g_bfmeEntriesDU[index].m_bfmeSecond = second;
	g_bfmeEntriesDU[index].m_bfmeThird = third;

	g_bfmeCountDU = index + 1;
}

class BfmeStateEE
{
public:
	char m_bfmeHead[0x170C];				// +0x0000
	int m_bfmeLevel;					// +0x170C
};

extern BfmeStateEE *g_bfmeStateEE;				// retail 0x012ED5AC

class BfmeRowFC
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeThird;					// +0x08
	int m_bfmeTail[2];					// +0x0C
};

class BfmeHolderFC
{
public:
	char m_bfmeHead[0x15C];					// +0x000
	BfmeRowFC m_bfmeRows[3];				// +0x15C
};

class Gen_00752FF0
{
public:
	int bfmeThird(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeHolderFC *m_bfmeHolder;				// +0x04
};

// ?bfmeThird@Gen_00752FF0@@QBEHXZ
int Gen_00752FF0::bfmeThird(void) const
{
	int level = g_bfmeStateEE->m_bfmeLevel - 1;

	BfmeHolderFC *holder = m_bfmeHolder;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return holder->m_bfmeRows[level].m_bfmeThird;
}
