// cl: /GX

// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

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

class BfmeCellFC
{
public:
	BfmeCellFC();
	~BfmeCellFC();

	unsigned char m_bfmeKind;				// +0x00
	unsigned char m_bfmeGap[3];				// +0x01
	int m_bfmeValue;					// +0x04
};

// The three grid/cell bodies this TU calls are defined out of line under the
// ledger's own (still address-derived) names, so the reference has to carry
// those exact scopes.  Each is a separate view class over the same object,
// cast at the use below; none of them is defined here, so no body moves.
class Rva00881B90Class					// 0x00881B90, 75 bytes
{
public:
	void update(int x, int y, int radius, int amount, bool absolute);
};

class Rva00881BE0Class					// 0x00881BE0, 68 bytes
{
public:
	void update(int amount, bool absolute);
};

struct Gen_008811a0					// 0x008811A0, 1-byte ret
{
	void m(void);
};

// ??0BfmeCellFC@@QAE@XZ — retail881200,13B; array ctor callback in8815A0.
BfmeCellFC::BfmeCellFC()
	: m_bfmeKind(0x80), m_bfmeValue(0)
{
}

// ??1BfmeCellFC@@QAE@XZ — retail881210,1B; array dtor callback in8815A0.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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
	void bfmeConfigure(Region3D region, Real cellSize);
	void bfmeSetRegion(const Region3D *region, Real cellSize);
	BfmeCellFC *bfmeAt(int x, int y) const;
	void bfmeGetCellRange(BfmeCellFC **first, BfmeCellFC **last,
		int x1, int x2, int y);
	BfmeCellFC *bfmeCellAtWorld(Real x, Real y) const;
	void bfmeVisitCells(void);
	int bfmeValueAtWorld(const BfmePointFC *point) const;
	int rva00880E70(Real worldX) const;
	int rva00880EA0(Real worldY) const;
	int rva00880ED0(Real distance) const;
	int rva00881500(const BfmePointFC *point) const;

	friend class BfmeRangeUpdaterFC;
	friend class BfmeTaintManager;

private:
	Region3D m_region;					// +0x00
	Real m_cellSize;					// +0x18
	float m_cellSizeInv;				// +0x1C
	int m_width;					// +0x20
	int m_height;					// +0x24
	BfmeCellFC *m_cells;				// +0x28
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
	m_region.lo.zero();
	m_width = 0;
	m_height = 0;
	m_cells = 0;
	m_bfmeVisitor = 0;
	m_cellSize = 1.0f;
	m_region.hi.zero();

	bfmeConfigure(m_region, 1.0f);
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
			((Real)y * cellSize + region.lo.y - m_region.lo.y)
				* m_cellSizeInv));
		if (oldY >= 0 && oldY < m_height)
		{
			for (unsigned int x = 0; x < (unsigned int)width;
				++x, ++cell)
			{
				int oldX = bfmeFloatToLongFC(bfmeFloatFloorFC(
					((Real)x * cellSize + region.lo.x - m_region.lo.x)
						* m_cellSizeInv));
				if (oldX >= 0 && oldX < m_width)
					cell->m_bfmeKind = m_cells[
						oldY * m_width + oldX].m_bfmeKind;
			}
		}
		else
		{
			cell += width;
		}
	}

	delete[] m_cells;
	m_cells = cells;
	m_region = region;
	m_cellSizeInv = cellSizeInv;
	m_width = width;
	m_height = height;
	m_cellSize = cellSize;
}

// ??1Gen_008812D0@@QAE@XZ
Gen_008812D0::~Gen_008812D0()
{
	delete[] m_cells;
}

// The retail 30-byte wrapper is the scalar-deleting destructor for this
// TaintManager-owned grid.  Keep the delete expression out of the matched
// destructor so MSVC emits the compiler-owned ??_G wrapper separately.
void Force_Gen_008812D0_DeletingDestructor(Gen_008812D0 *value)
{
	delete value;
}

// ?bfmeSetRegion@Gen_008812D0@@QAEXPBURegion3D@@M@Z
void Gen_008812D0::bfmeSetRegion(const Region3D *region, Real cellSize)
{
	if (cellSize <= 0.0f)
		cellSize = m_cellSize;

	if (!(region->width() < 0.0f)
		&& !(region->height() < 0.0f))
	{
		bfmeConfigure(*region, cellSize);
	}
}

// ?bfmeResetGrid@BfmeTaintManager@@QAEXXZ
void BfmeTaintManager::bfmeResetGrid()
{
	((Gen_008811a0 *)m_bfmeGrid)->m();

	Region3D region;
	region.lo.zero();
	region.hi.zero();
	m_bfmeGrid->bfmeSetRegion(&region, 0.0f);
}

// ?bfmeAt@Gen_008812D0@@QBEPAVBfmeCellFC@@HH@Z
BfmeCellFC *Gen_008812D0::bfmeAt(int x, int y) const
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		return &m_cells[m_width * y + x];

	return 0;
}

// ?bfmeGetCellRange@Gen_008812D0@@QAEXPAPAVBfmeCellFC@@0HHH@Z
void Gen_008812D0::bfmeGetCellRange(BfmeCellFC **first,
	BfmeCellFC **last, int x1, int x2, int y)
{
	if (x2 < 0 || x1 >= m_width || y < 0 || y >= m_height)
	{
		*last = 0;
		*first = 0;
		return;
	}

	BfmeCellFC *row = m_cells + y * m_width;
	*last = row;
	*first = row;
	if (x1 > 0)
		*first = row + x1;

	*last += x2 < m_width ? x2 + 1 : m_width;
}

// 0x00880E70, 0x00880EA0 and 0x00880ED0 are out-of-line Gen_008812D0 helpers
// with no direct callers; each is the expression bfmeCellAtWorld and
// BfmeTaintManager::bfmeApplyCircleWorld inline (lo.x/lo.y at +0x00/+0x04,
// m_bfmeCellSizeInv at +0x1C, CRT floor/ceil then fistp). Retail places them
// right after this class's ??_G at 0x00880DD0. Names keep the address.

// ?rva00880E70@Gen_008812D0@@QBEHM@Z
int Gen_008812D0::rva00880E70(Real worldX) const
{
	return bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldX - m_region.lo.x) * m_cellSizeInv));
}

// ?rva00880EA0@Gen_008812D0@@QBEHM@Z
int Gen_008812D0::rva00880EA0(Real worldY) const
{
	return bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldY - m_region.lo.y) * m_cellSizeInv));
}

// ?rva00880ED0@Gen_008812D0@@QBEHM@Z
int Gen_008812D0::rva00880ED0(Real distance) const
{
	return bfmeFloatToLongFC(bfmeFloatCeilFC(distance * m_cellSizeInv));
}

// ?bfmeCellAtWorld@Gen_008812D0@@QBEPAVBfmeCellFC@@MM@Z
BfmeCellFC *Gen_008812D0::bfmeCellAtWorld(Real worldX, Real worldY) const
{
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldX - m_region.lo.x) * m_cellSizeInv));
	if (x < 0 || x >= m_width)
		return 0;

	int y = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(worldY - m_region.lo.y) * m_cellSizeInv));
	if (y < 0 || y >= m_height)
		return 0;

	return &m_cells[y * m_width + x];
}

// ?bfmeVisitCells@Gen_008812D0@@QAEXXZ
void Gen_008812D0::bfmeVisitCells(void)
{
	BfmeCellFC *end = m_cells + m_width * m_height;
	int x = 0;
	int y = 0;

	for (BfmeCellFC *cell = m_cells; cell != end; ++cell)
	{
		m_bfmeVisitor(x, y, cell->m_bfmeKind);
		++x;
		if (x == m_width)
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

// ?rva00881500@Gen_008812D0@@QBEHPBUBfmePointFC@@@Z
// The m_bfmeKind twin of bfmeValueAtWorld: same call to the matched
// bfmeCellAtWorld, and 0x80 (BfmeCellFC's default kind) when outside.
int Gen_008812D0::rva00881500(const BfmePointFC *point) const
{
	BfmeCellFC *cell = bfmeCellAtWorld(point->x, point->y);
	return cell ? cell->m_bfmeKind : 0x80;
}

// ??RBfmeRangeUpdaterFC@@QAEXHHH@Z
void BfmeRangeUpdaterFC::operator()(int firstX, int lastX, int y)
{
	BfmeCellFC *first;
	BfmeCellFC *last;
	m_bfmeGrid->bfmeGetCellRange(&first, &last, firstX, lastX, y);

	for (BfmeCellFC *cell = first; cell != last; ++cell)
	{
		((Rva00881BE0Class *)cell)->update(m_bfmeAmount, m_bfmeAbsolute);
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
		radius * m_bfmeGrid->m_cellSizeInv));
	int y = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(point->y - m_bfmeGrid->m_region.lo.y)
			* m_bfmeGrid->m_cellSizeInv));
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC(
		(point->x - m_bfmeGrid->m_region.lo.x)
			* m_bfmeGrid->m_cellSizeInv));

	((Rva00881B90Class *)m_bfmeGrid)->update(x, y, cellRadius, amount, absolute);
}
