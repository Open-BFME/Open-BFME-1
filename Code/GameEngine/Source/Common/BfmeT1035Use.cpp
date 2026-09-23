// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x001AE1E0, 557 bytes, ret 8 at +0x22A. Identity and the
// two-argument thiscall ABI come from the matched bfmeGo1035C
// (Code/GameEngine/Source/Common/BfmeConv1035.cpp), which builds a BfmeT1035
// and calls this body through ILT 0x00022372. The record fields and the
// terrain-visual slots are unnamed, so they keep offset/slot names.
// Frame lever (docs/shape_levers.md, filter construction): the visible
// noinline 0x000C3DD0 constructor proves the masks are copied, and the pos
// block lets VC7.1 put pos on the dead kind-of mask temporary (esp+0x14),
// giving retail's 0xBC frame. The +5.0f height is a pooled literal.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

extern void j_000309f4(void);

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);
	// ??1Rva000FFCA0@@QAE@XZ
	~GeometryInfo()
	{
		typedef void (__fastcall *DestroyCall)(GeometryInfo *);
		((DestroyCall)j_000309f4)(this);
	}

private:
	void *m_vtable;
	unsigned char m_unmodelled[0x58];
};

class TerrainVisual
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31(const Coord3D *pos, const GeometryInfo *geom, int flag) = 0;	// +0x7C
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0;
	virtual void slot35() = 0; virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual Bool slot40(int value, const Coord3D *delta) = 0;	// +0xA0
};

extern TerrainVisual *TheTerrainVisual;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) { return false; }

	PartitionFilter *m_next;
};

struct VptrZeroBlock24
{
	unsigned int m_dwords[6];

	VptrZeroBlock24(int bit)
	{
		clear();
		set(bit);
	}
	void clear()
	{
		for (int i = 0; i < 6; ++i)
			m_dwords[i] = 0;
	}
	void set(int bit)
	{
		m_dwords[bit >> 5] |= 1u << (bit & 31);
	}
};

class Rva000C3DD0VptrZeroBlockObject : public PartitionFilter
{
public:
	// Complete body of the 102-byte constructor at 0x000C3DD0; visible and
	// noinline so VC7.1 knows the mask references are copied, not retained.
	__declspec(noinline) Rva000C3DD0VptrZeroBlockObject(
		const VptrZeroBlock24 &first, const VptrZeroBlock24 &second)
		: m_first(first), m_second(second) {}
	virtual ~Rva000C3DD0VptrZeroBlockObject() {}
	virtual Bool allow(Object *object);

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

template <size_t NUMBITS> class BitFlags
{
	unsigned int m_dwords[NUMBITS / 32];
};

extern const BitFlags<192> KINDOFMASK_NONE;

struct Rva001AE1E0Entry
{
	Object *object;
	unsigned unknown04;
};

struct Rva001AE1E0ResultData
{
	std::vector<Rva001AE1E0Entry> entries;
	Rva001AE1E0Entry *current;
	int references;
};

struct BfmeWideResult
{
	Rva001AE1E0ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

class BfmeX1035
{
public:
	Coord3D m_pos;				// +0x00
	int m_value0c;				// +0x0C
	unsigned char m_unmodelled10[8];
	Bool m_processed;			// +0x18
	Coord3D m_delta;			// +0x1C
};

struct BfmeT1035
{
	void bfmeUse1035(BfmeX1035 *p, int b);

	Object *m_bfmeV;
};

// ?bfmeUse1035@BfmeT1035@@QAEXPAVBfmeX1035@@H@Z
void BfmeT1035::bfmeUse1035(BfmeX1035 *p, int b)
{
	if (p->m_processed)
		return;

	Coord3D delta;
	delta.x = p->m_pos.x;
	delta.y = p->m_pos.y;
	delta.z = p->m_pos.z;
	if (m_bfmeV)
	{
		delta.x -= m_bfmeV->getPosition()->x;
		delta.y -= m_bfmeV->getPosition()->y;
	}
	else
	{
		const Coord3D *at = (const Coord3D *)b;
		delta.x -= at->x;
		delta.y -= at->y;
	}
	int value = p->m_value0c;
	delta.z = 0.0f;

	if (!TheTerrainVisual->slot40(value, &delta))
		return;

	if (!p->m_processed)
		p->m_processed = true;
	p->m_delta.x = delta.x;
	p->m_delta.y = delta.y;
	p->m_delta.z = delta.z;

	BfmeWideResult iterator = ThePartitionManager->bfmeForwardWideC(
		(int)p, 0x40A00000 /* 5.0f */, 1,
		(int)&Rva000C3DD0VptrZeroBlockObject(VptrZeroBlock24(144),
			*(const VptrZeroBlock24 *)&KINDOFMASK_NONE), 0);

	Object *obj;
	while (iterator.next(obj))
		TheGameLogic->destroyObject(obj);

	GeometryInfo geom(GEOMETRY_CYLINDER, false, 25.0f, 25.0f, 25.0f);
	{
		Coord3D pos;
		pos.x = p->m_pos.x;
		pos.y = p->m_pos.y;
		pos.z = p->m_pos.z + 5.0f;
		TheTerrainVisual->slot31(&pos, &geom, 0);
	}
}
