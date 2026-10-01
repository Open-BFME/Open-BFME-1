// ?after@TaintSpecialPower@@QAEXPBVCoord3D@@@Z
// Retail identity is proven by caller 0x0026BF40 through ILT 0x00033C62.
// Retail extent: 1109 bytes (ret 4 at RVA +0x452).
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <vector>
#include <bitset>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef float Real;

class Coord3D
{
public:
	Real x, y, z;
};

class Player;
class Matrix3D;
class Object;

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit };
	BitFlags(BogusInitType, Int bit) { m_bits.set(bit); }
private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual Bool allow(Object *);
private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

struct Rva0026B9D0Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0026B9D0ResultData
{
	std::vector<Rva0026B9D0Entry> entries;
	Rva0026B9D0Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0026B9D0ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	BfmeWideResult &operator=(const BfmeWideResult &other)
	{
		if (this != &other)
		{
			if (--value->references == 0)
				delete value;
			value = other.value;
			++value->references;
		}
		return *this;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int, Real, Int, Int, Int);
};
extern BfmeWideForwardC *ThePartitionManager;

struct Rva0025BD30Target;
typedef Rva0025BD30Target *Rva0025BD30Key;
typedef std::set<Rva0025BD30Key> PointerIdentityTree0025BD30;

class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }

	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x54];
	UnsignedInt m_status98;
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};
extern GameLogic *TheBfmeGameLogic;

struct BfmePointFC;

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld(const BfmePointFC *point, Real radius, Int amount, Bool absolute);
};
extern BfmeTaintManager *TheTaintManager;

class FXList
{
public:
	Bool bfmeIsBlocked() const;
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary) const;
};

class BfmeThingFB
{
public:
	void bfmeTellFB(void *, void *, void *, void *);
};

extern void j_00042cd0(void);
extern void j_00037330(void);

class TerrainArea001ACCC0
{
public:
	void clearOne001AC3D0(const void *, Int);
};

struct Rva003FD060TerrainLogic
{
	void rva001AC3D0(const Coord3D *, Real);
	void clearArea001A64F0(const Coord3D *pos, Real radius, Int flag)
	{
		union { void *raw; void (Rva003FD060TerrainLogic::*fn)(const Coord3D *, Real, Int); } u;
		u.raw = (void *)j_00042cd0;
		(this->*u.fn)(pos, radius, flag);
	}
	void refresh001A3190(const Coord3D *pos, Real radius, Int flag)
	{
		union { void *raw; void (Rva003FD060TerrainLogic::*fn)(const Coord3D *, Real, Int); } u;
		u.raw = (void *)j_00037330;
		(this->*u.fn)(pos, radius, flag);
	}
};
// retail singleton: TerrainLogic *TheTerrainLogic (mangled ?TheTerrainLogic@@3PAVTerrainLogic@@A),
// defined in GameLogic/Map/TerrainLogic.cpp. Uses go through this TU's Rva003FD060TerrainLogic view.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

struct TaintSpecialPowerModuleData
{
	unsigned char m_pad00[0x210];
	UnsignedInt m_taintObject;
	Real m_radius;
	FXList *m_taintFX;
	BfmeThingFB *m_taintOCL;
};

extern void j_000262bf(void);

class TaintSpecialPower
{
public:
	void after(const Coord3D *loc);

	unsigned char m_pad00[4];
	TaintSpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

void TaintSpecialPower::after(const Coord3D *loc)
{
	TaintSpecialPowerModuleData *data = m_moduleData;
	Real radius = data->m_radius;
	Object *owner = m_object;

	BfmeWideResult iterator = ThePartitionManager->bfmeForwardWideC((Int)loc, radius * 2.1f, 0,
		(Int)&PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::kInit, 151), KINDOFMASK_NONE), 1);

	PointerIdentityTree0025BD30 matches;

	Object *candidate;
	while (iterator.next(candidate))
	{
		if (candidate->getControllingPlayer() == owner->getControllingPlayer())
			continue;
		matches.insert(*(Rva0025BD30Key *)&candidate);
		((TerrainArea001ACCC0 *)TheTerrainLogic)->clearOne001AC3D0(candidate->getPosition(), *(Int *)&radius);
		TheBfmeGameLogic->destroyObject(candidate);
	}

	iterator = ThePartitionManager->bfmeForwardWideC((Int)loc, radius * 4.0f, 0,
		(Int)&PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::kInit, 151), KINDOFMASK_NONE), 1);

	while (iterator.next(candidate))
	{
		if (candidate->getControllingPlayer() == owner->getControllingPlayer())
			continue;
		if (matches.find((Rva0025BD30Key)candidate) != matches.end())
			continue;
		UnsignedByte amount = (candidate->m_status98 & 0x80000) ? 0xff : 0;
		Coord3D point;
		point.x = candidate->m_position.x;
		point.y = candidate->m_position.y;
		point.z = candidate->m_position.z;
		TheTaintManager->bfmeApplyCircleWorld((const BfmePointFC *)&point, radius, amount, true);
	}

	((Rva003FD060TerrainLogic *)TheTerrainLogic)->clearArea001A64F0(loc, radius, 1);
	((Rva003FD060TerrainLogic *)TheTerrainLogic)->refresh001A3190(loc, radius + 50.0f, 1);

	FXList *fx = data->m_taintFX;
	if (fx != 0 && !fx->bfmeIsBlocked())
		fx->doFXPos(loc, 0, 0.0f, 0);

	BfmeThingFB *ocl = data->m_taintOCL;
	if (ocl != 0)
	{
		Coord3D oclPoint;
		oclPoint.x = loc->x;
		oclPoint.y = loc->y;
		oclPoint.z = loc->z;
		ocl->bfmeTellFB(owner, &oclPoint, 0, 0);
	}
	union { void *raw; void (TaintSpecialPower::*fn)(const Coord3D *, void *); } bind;
	bind.raw = (void *)j_000262bf;
	(this->*bind.fn)(loc, &data->m_taintObject);
	TheTaintManager->bfmeApplyCircleWorld((const BfmePointFC *)loc, radius, 0, true);
}
