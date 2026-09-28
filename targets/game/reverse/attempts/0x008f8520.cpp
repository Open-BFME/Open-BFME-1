// ?doSmallFill@PartitionData@@AAE_NMMM@Z
// partial score=0.2698 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x008F8520, 734 bytes, ret 0xC: PartitionData::doSmallFill (BFME).
// Identity: its DEBUG_CRASH strings ("Object ", " is too large for 'small'
// geometry.\nRadius given is ", "; truncating...") are Zero Hour
// PartitionData::doSmallFill's, and updateCellsTouched calls it on the
// geom->getIsSmall() branch exactly where ZH calls doSmallFill. CONFLICT: the
// ledger already names 0x008F83F0 doSmallFill, but that body is the midpoint
// circle fill called on the sphere/cylinder case (ZH doCircleFill); resolve
// that row before landing this one under the real name.
// Banked partial (opus-5.5): 719/734 B, 506 differing, shape 0.949.
// Residue: our allocator pins 0 in ebp through the debug block (retail uses
// literal zeros and keeps the name temporary in ebp, stream in esi), and the
// floor results cx2/cy2 and the row counter land in different arg slots
// (retail: y in the centerX slot, cy2 in the radius slot).
// Levers that helped: __forceinline getCellRange (matched sibling body),
// (coi++)->addCoverage(first++), ++y right after getCellRange (retail
// materialises the null range and bumps y before the cell loop).
// Tried: halfCellSize local, getObject accessor, do/while(0) debug macro,
// ternary polarity, ref-bound name temp, ZH-style declarations, coi placement
// (coi at the top removes the zero pin but hoists the m_coiArray load).

#include "ascii_string.h"

template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef int Int;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual BfmeAwakenLog *v20(Real value); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

class PartitionData;

class PartitionCell
{
public:
	class CellAndObjectIntersection *m_firstCoiInCell;
	Int m_data[25];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class CellAndObjectIntersection
{
public:
	PartitionCell *m_cell;
	void *m_module;
	PartitionCell *m_prev;
	CellAndObjectIntersection *m_next;

	__forceinline void addCoverage(PartitionCell *cell)
	{
		m_cell = cell;
		CellAndObjectIntersection *next = cell->m_firstCoiInCell;
		m_next = next;
		if (next != 0)
			next->m_prev = (PartitionCell *)&m_next;
		m_prev = cell;
		cell->m_firstCoiInCell = this;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	Real getCellSize() const { return m_cellSize; }

	// Matched out of line at 0x008F...; retail inlines it here.
	__forceinline void getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y)
	{
		if (x2 < 0 || x1 >= m_cellCountX || y < 0 || y >= m_cellCountY)
		{
			*last = 0;
			*first = 0;
			return;
		}
		PartitionCell *row = m_cells + y * m_cellCountX;
		*last = row;
		*first = row;
		if (x1 > 0)
			*first = row + x1;
		*last += x2 < m_cellCountX ? x2 + 1 : m_cellCountX;
	}

	char m_head[4];
	Real m_worldOriginX;
	Real m_worldOriginY;
	char m_middle[0x10];
	Real m_cellSize;
	Real m_cellSizeInv;
	Int m_cellCountX;
	Int m_cellCountY;
	PartitionCell *m_cells;
};

class Object
{
public:
	virtual AsciiString slot00() const;
};

class PartitionData
{
private:
	Bool doSmallFill(Real centerX, Real centerY, Real radius);

	PartitionManager *m_grid;
	Object *m_object;
	char m_prefix[0x1c - 0x08];
	CellAndObjectIntersection *m_coiArray;
};

Bool PartitionData::doSmallFill(Real centerX, Real centerY, Real radius)
{
	if (radius > m_grid->getCellSize() * 0.5f)
	{
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)->v38("Object ")
				->v38((m_object ? m_object->slot00() : AsciiString("*unknown*")).str())
				->v38(" is too large for 'small' geometry.\nRadius given is ")->v20(radius)
				->v38(" but maximum radius for small geometry is ")->v20(m_grid->getCellSize() * 0.5f)
				->v38("; truncating.\n\nIn order to fix this problem either set the geometry of the given object\nto non-small or reduce the geometry major radius.\n")
				->v4c(2);
		}
		radius = m_grid->getCellSize() * 0.5f;
	}

	CellAndObjectIntersection *coi = m_coiArray;
	Int cx1 = REAL_TO_INT_FLOOR((centerX - radius - m_grid->m_worldOriginX) * m_grid->m_cellSizeInv);
	Int cx2 = REAL_TO_INT_FLOOR((centerX + radius - m_grid->m_worldOriginX) * m_grid->m_cellSizeInv);
	Int cy1 = REAL_TO_INT_FLOOR((centerY - radius - m_grid->m_worldOriginY) * m_grid->m_cellSizeInv);
	Int cy2 = REAL_TO_INT_FLOOR((centerY + radius - m_grid->m_worldOriginY) * m_grid->m_cellSizeInv);

	for (Int y = cy1; y <= cy2; )
	{
		PartitionCell *first, *last;
		m_grid->getCellRange(&first, &last, cx1, cx2, y);
		++y;
		while (first != last)
			(coi++)->addCoverage(first++);
	}
	return true;
}
