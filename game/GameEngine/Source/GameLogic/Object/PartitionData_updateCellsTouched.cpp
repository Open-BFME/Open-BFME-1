// ?updateCellsTouched@PartitionData@@AAEXXZ
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008F8800, 959 bytes (ret at +0x3BE).
//
// Identity: the matched public facade ?friend_updateCellsTouched@PartitionData@@QAEXXZ
// (0x008F8BF0, PartitionData_friendUpdateCellsTouched.cpp) tail-calls this body,
// exactly as Zero Hour's friend_updateCellsTouched calls the private
// updateCellsTouched; the symbols.csv pin names it. The head follows the ZH
// body (object-or-ghost, removeAllTouchedCells, small / circle / rect fill);
// the tail is BFME-only: after the cell move test it undoes and re-applies the
// object's reveal (m_grid calls at 0x008FBCB0, 0x008FA010 and 0x008FA070 twice)
// and finally clears the sixteen per-player shroud status dwords (ZH
// invalidateShroudedStatusForAllPlayers; OBJECTSHROUD_INVALID is 0).
//
// Types are TU-local shims:
//  - The local shape is the 0x24-byte GeometryInfo shape element whose ledger
//    class name is Rva000FC640 (GeometryInfoRva0087E190.cpp fills it); retail
//    builds it inline (type 0, three 1.0f radii, zero offset, empty name,
//    enabled) and destroys its AsciiString name through ~StringBase<char>.
//  - m_object and m_ghostObject share one type with a virtual base (vfptr +0,
//    vbptr +4); retail selects one and converts once. Virtual slots keep
//    opaque names; slot 0 returns the GeometryInfo whose rva0087E190 retail
//    calls, slot 1 the position, slot 2 the angle passed to the rect fill.
//  - The grid at +0 keeps the doSmallFill TU's field names (origin +4/+8,
//    scale +0x20). worldToCellDist is ZH PartitionManager's inline
//    REAL_TO_INT_CEIL(w * m_cellSizeInv); written as that inline method the
//    second call site allocates EAX as retail does.
//  - 0x008F8520 and 0x008F7F00 are still ledger dumps, reached by their dump
//    symbols through member-pointer casts (thiscall, 3 and 5 floats).
//  - Callee owner classes are the names their matched ledger rows carry.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail frees the COI array through operator delete[] (0x00881EF0).
void __cdecl operator delete[](void *);

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline Real fast_float_ceil(Real f)
{
	return (Real)ceil((double)f);
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
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

struct Coord3D
{
	Real x, y, z;
};

// Coord3D-shaped offset whose default constructor zeroes it (retail stores the
// three zeros before the name and the enabled flag).
struct Rva000FC640Offset
{
	Rva000FC640Offset() : x(0.0f), y(0.0f), z(0.0f) {}
	Real x, y, z;
};

class Rva000FC640
{
public:
	Rva000FC640() : m_type(0), m_height(1.0f), m_majorRadius(1.0f), m_minorRadius(1.0f),
		m_enabled(true)
	{
	}

	Int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Rva000FC640Offset m_offset;
	AsciiString m_name;
	Bool m_enabled;
};

class GeometryInfo
{
public:
	void rva0087E190(Rva000FC640 &out) const;

	void *m_vtbl;
	Bool m_isSmall;
};

class Thing
{
public:
	virtual const GeometryInfo *slot00Geometry() const;
	virtual const Coord3D *slot04Position() const;
	virtual Real slot08Angle() const;
};

class Object : public virtual Thing
{
public:
	virtual void slot00();
	virtual void slot04CellChanged();
	virtual void slot08();
	virtual Real slot0C(UnsignedInt *value);
	virtual Real slot10(Int index, UnsignedInt *amount, UnsignedInt *id);
};

class BfmeShapeEU;
class BfmeHostEU
{
public:
	Int bfmeStepsEU(const BfmeShapeEU *shape);
};

class ShroudManagerImpl008FBA40
{
public:
	void doShroudReveal(Int x, Int y, Int radius, UnsignedInt value);
};

class BfmeOwnerXO
{
public:
	void bfmeSendXO(void *x, void *y, Int radius, Int index, void *amount, UnsignedInt id);
};

class Rva008FBCB0P20Queue
{
public:
	void append(Int x, Int y, Int radius, Int value);
};

class Rva008F7EC0
{
public:
	void method();
};

class BfmeThingCDE
{
public:
	void initializeArray(Int count);
};

class PartitionGrid008F8800
{
public:
	char m_head[4];
	Real m_originX;
	Real m_originY;
	char m_middle[20];
	Real m_scale;

	__forceinline Int worldToCellDist(Real w)
	{
		return REAL_TO_INT_CEIL(w * m_scale);
	}
};

class CellAndObjectIntersection
{
public:
	CellAndObjectIntersection() {}
	~CellAndObjectIntersection() {}

	Int m_00;
	void *m_04;
	Int m_08;
	Int m_0c;
};

extern void d_008f8520();
extern void d_008f7f00();

class Rva008F8520Fill
{
public:
	void call(Real x, Real y, Real radius);
};

class Rva008F7F00Fill
{
public:
	void call(Real x, Real y, Real majorRadius, Real minorRadius, Real angle);
};

class PartitionData
{
private:
	void updateCellsTouched();
	Bool doSmallFill(Real x, Real y, Real radius);

	PartitionGrid008F8800 *m_grid;
	Object *m_object;
	Object *m_ghostObject;
	unsigned char m_pad0c[0x1c - 0x0c];
	CellAndObjectIntersection *m_coiArray;
	Int m_coiArrayCount;
	Int m_shroudedness[16];
	unsigned char m_pad64[0xb4 - 0x64];
	Int m_lastCellX;
	Int m_lastCellY;
	Int m_revealRadius;
	UnsignedInt m_revealValue;
	Int m_slotRadius[2];
	UnsignedInt m_slotId[2];
	UnsignedInt m_slotAmount[2];
	Bool m_forceUpdate;
};

void PartitionData::updateCellsTouched()
{
	if (m_object == 0 && m_ghostObject == 0)
		return;

	Object *obj = m_object ? m_object : m_ghostObject;
	Thing *thing = obj;
	const GeometryInfo *geom = thing->slot00Geometry();
	const Coord3D *pos = thing->slot04Position();
	reinterpret_cast<Rva008F7EC0 *>(this)->method();

	Rva000FC640 shape;
	geom->rva0087E190(shape);
	if (!geom->m_isSmall)
	{
		Int count = reinterpret_cast<BfmeHostEU *>(m_grid)->bfmeStepsEU(
			reinterpret_cast<const BfmeShapeEU *>(&shape));
		if (count != m_coiArrayCount)
		{
			delete[] m_coiArray;
			m_coiArray = 0;
			reinterpret_cast<BfmeThingCDE *>(this)->initializeArray(count);
		}
	}

	Bool isSmall = geom->m_isSmall;
	if (isSmall)
	{
		union { void (*asFunction)(); void (Rva008F8520Fill::*asMember)(Real, Real, Real); } fnCast;
		fnCast.asFunction = d_008f8520;
		(reinterpret_cast<Rva008F8520Fill *>(this)->*fnCast.asMember)(pos->x, pos->y, shape.m_majorRadius);
	}
	else
	{
		switch (shape.m_type)
		{
		case 0:
		case 1:
			doSmallFill(pos->x, pos->y, shape.m_majorRadius);
			break;
		case 2:
		{
			Real minorRadius = shape.m_minorRadius;
			Real majorRadius = shape.m_majorRadius;
			union { void (*asFunction)(); void (Rva008F7F00Fill::*asMember)(Real, Real, Real, Real, Real); } fnCast;
			fnCast.asFunction = d_008f7f00;
			(reinterpret_cast<Rva008F7F00Fill *>(this)->*fnCast.asMember)(pos->x, pos->y, majorRadius, minorRadius, thing->slot08Angle());
			break;
		}
		}
	}

	if (m_object != 0)
	{
		Int cellX = REAL_TO_INT_FLOOR((pos->x - m_grid->m_originX) * m_grid->m_scale);
		Int cellY = REAL_TO_INT_FLOOR((pos->y - m_grid->m_originY) * m_grid->m_scale);
		if (cellX != m_lastCellX || cellY != m_lastCellY || m_forceUpdate)
		{
			if (m_revealRadius >= 0)
				reinterpret_cast<Rva008FBCB0P20Queue *>(m_grid)->append(
					m_lastCellX, m_lastCellY, m_revealRadius, m_revealValue);
			Int i;
			for (i = 0; i < 2; ++i)
			{
				if (m_slotRadius[i] >= 0 && m_slotAmount[i] > 0)
					reinterpret_cast<BfmeOwnerXO *>(m_grid)->bfmeSendXO(
						(void *)m_lastCellX, (void *)m_lastCellY, m_slotRadius[i], i,
						(void *)-(Int)m_slotAmount[i], m_slotId[i]);
			}

			Real range = m_object->slot0C(&m_revealValue);
			m_revealRadius = (range < 0.0f) ? -1 : m_grid->worldToCellDist(range);
			if (m_revealRadius >= 0)
				reinterpret_cast<ShroudManagerImpl008FBA40 *>(m_grid)->doShroudReveal(
					cellX, cellY, m_revealRadius, m_revealValue);

			for (i = 0; i < 2; ++i)
			{
				Real slotRange = m_object->slot10(i, &m_slotAmount[i], &m_slotId[i]);
				m_slotRadius[i] = (slotRange < 0.0f) ? -1 : m_grid->worldToCellDist(slotRange);
				if (m_slotRadius[i] >= 0 && m_slotAmount[i] > 0)
				{
					if (m_slotId[i] == 0)
						m_slotId[i] = m_revealValue;
					reinterpret_cast<BfmeOwnerXO *>(m_grid)->bfmeSendXO(
						(void *)cellX, (void *)cellY, m_slotRadius[i], i,
						(void *)m_slotAmount[i], m_slotId[i]);
				}
			}

			m_lastCellX = cellX;
			m_lastCellY = cellY;
			m_object->slot04CellChanged();
		}
	}

	for (Int p = 0; p < 16; ++p)
		m_shroudedness[p] = 0;
}
