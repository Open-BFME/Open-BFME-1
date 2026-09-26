// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Oi
// stlport
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
// TerrainLogic::setWaterHeight at 0x001AC560, 905 bytes through ret 16.
// TerrainLogic vtable 0x0109C428 slot 28 routes through 0x00031796 here.
// The algorithm is the Zero Hour twin: move the grid/polygon water, remap
// paths, and apply drowning damage to submerged objects inside its bounds.
// The grid/point/region temporaries have disjoint lifetimes and retail uses
// one 48-byte stack area for them. Explicit storage and placement construction
// preserve that lifetime reuse with the real Matrix3D header under MSVC 7.1.
// An inline float-returning sqrt wrapper releases the two dead x87 dimensions
// before fsqrt, matching retail without assembly.
//
// Callee contracts were decoded before using the ledger identities:
// 0x000465D3 -> 0x0018F540 is the 12-byte indexed-point setter; 0x0002E064 ->
// 0x003D5780 is the guarded path-map refresh; 0x009F2920 forwards the four
// argument words and returns an owning result in the caller-provided slot.
// BfmeWideResult ownership is the same native vector/refcount layout used by
// MetaImpactNuggetShockWave.cpp and AutoFindHealingUpdateScanClosestTarget.cpp.

// These compatibility headers carry the different Zero Hour damage layout.
#define DamageInfoInput ZeroHourDamageInfoInput
#define DamageInfoOutput ZeroHourDamageInfoOutput
#define DamageInfo ZeroHourDamageInfo
#include "PreRTS.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/PolygonTrigger.h"
#include "WWMath/matrix3d.h"
#undef DamageInfoInput
#undef DamageInfoOutput
#undef DamageInfo

static inline float waterRadius(float squaredRadius)
{
    return (float)sqrt(squaredRadius);
}

// BFME points/count are +0x10/+0x14, as in the bounding-rectangle sibling.
// +0x10 m_points is also independently witnessed by name_oracle.
class Rva001AC560PolygonView
{
public:
	unsigned char m_unreconstructed_00[0x10];
	ICoord3D *m_points;
	Int m_numPoints;

	Int getNumPoints() const { return m_numPoints; }
	const ICoord3D *getPoint(Int index) const
	{
		if (index < 0)
			index = 0;
		if (index >= m_numPoints)
			index = m_numPoints - 1;
		return m_points + index;
	}

};

struct BfmeVector3BG;
class Gen_0018F210
{
public:
    void bfmeSetVector3(const BfmeVector3BG *value, int index);
};

extern "C" WaterHandle g_bfmeGridWaterHandle;

class TerrainVisualDispatch
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void setWaterTransform(const Matrix3D *transform) = 0;
	virtual void v14() = 0;
	virtual void getWaterTransform(const WaterHandle *water, Matrix3D *transform) = 0;
};

extern "C" TerrainVisualDispatch *g_bfmeTerrainVisual;

// BFME damage values expose one virtual xfer, not Zero Hour's three Snapshot
// slots. The tables at 0x01085DE4/0x01085DE0/0x01085DBC each have one slot:
// 0x0037A5C0 transfers input at +4 and output at +0x4c via their slot zero;
// 0x0037A610 serializes the 0x48-byte input; 0x0037A750 serializes the output.
// Input floating fields +0x20 and +0x38..+0x44 use Xfer's Real slot +0x6c;
// +0x2c is the three-float vector slot +0x60. Unproven field names retain offsets.

struct DamageInfoInput
{
    virtual void xfer(Xfer *);
	Int m_sourceID;
	UnsignedShort m_a08;
	Int m_damageType;
	Int m_a10;
	Int m_deathType;
	Real m_amount;
	Bool m_a1c;
	Bool m_a1d;
	Real m_a20;
	void *m_a24;
	void *m_a28;
	Real m_a2c;
	Real m_a30;
	Real m_a34;
	Real m_a38;
	Real m_a3c;
	Real m_a40;
	Real m_a44;

	__forceinline DamageInfoInput()
		: m_sourceID(0),
          m_a08(0),
          m_damageType(0x16),
		  m_a10(0xf),
          m_deathType(0),
          m_amount(0),
		  m_a1c(false),
		  m_a1d(true),
		  m_a20(0),
		  m_a24(0),
		  m_a28(0),
		  m_a2c(0),
		  m_a30(0),
		  m_a34(0),
		  m_a38(0),
		  m_a3c(0),
		  m_a40(0),
		  m_a44(1.0f)
	{
	}
};

struct DamageInfoOutput
{
    virtual void xfer(Xfer *);
    Real m_actualDamageDealt;
    Real m_actualDamageClipped;
    Bool m_noEffect;
    DamageInfoOutput() : m_actualDamageDealt(0), m_actualDamageClipped(0), m_noEffect(false) {}
};
struct DamageInfo
{
    __forceinline DamageInfo() {}
    virtual void xfer(Xfer *);
    DamageInfoInput in;
    DamageInfoOutput out;
};

class Object
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void attemptDamage(DamageInfo *damageInfo) = 0;

	unsigned char m_unreconstructed_04[0x34];
	Coord3D m_cachedPos;

	const Coord3D *getPosition() const { return &m_cachedPos; }
};

struct BfmeIterEntry
{
	Object *m_obj;
	void *m_extra;
};

struct BfmeObjectIterator
{
    std::vector<BfmeIterEntry> m_entries;
    BfmeIterEntry *m_cur;
    int m_refCount;
};
struct BfmeWideResult
{
    BfmeObjectIterator *m_value;
    BfmeWideResult();
    BfmeWideResult(const BfmeWideResult &);
    __forceinline ~BfmeWideResult()
    {
        if (--m_value->m_refCount == 0)
            delete m_value;
    }
    Object *next()
    {
        if (m_value->m_cur == m_value->m_entries.end())
            return 0;
        return (m_value->m_cur++)->m_obj;
    }
};

class BfmeWideForwardA
{
public:
	BfmeWideResult bfmeForwardWideA(int a, int b, int c, int d);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Rva003D5780
{
public:
	void go();
};

class Pathfinder;

class AI
{
public:
	unsigned char m_unreconstructed_00[0xc];
	Pathfinder *m_pathfinder;

	Pathfinder *pathfinder() { return m_pathfinder; }
};

extern AI *TheAI;

class TerrainLogicDispatch
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0;
	virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0;
	virtual void v18() = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
	virtual void v20() = 0; virtual void v21() = 0;
	virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0;
	virtual void v26() = 0;
	virtual Real getWaterHeight(const WaterHandle *water) = 0;
};

void TerrainLogic::setWaterHeight(const WaterHandle *water, Real height, Real damageAmount,
                                 Bool forcePathfindUpdate)
{
	TerrainLogicDispatch *self = reinterpret_cast<TerrainLogicDispatch *>(this);

	if (water == 0)
		return;

    union
    {
        Real transformRows[3][4];
        ICoord3D newPoint;
        Region3D affectedRegion;
    };
	Real previousHeight = 0.0f;
	if (water == &g_bfmeGridWaterHandle) {

		Matrix3D &transform = *new (transformRows) Matrix3D;
		g_bfmeTerrainVisual->getWaterTransform(water, &transform);
		previousHeight = transform.Get_Z_Translation();
		transform.Set_Z_Translation(height);
		g_bfmeTerrainVisual->setWaterTransform(&transform);

	} else {

		previousHeight = self->getWaterHeight(water);

		new (&newPoint) ICoord3D;
		const ICoord3D *p;
		Int numPoints = ((Rva001AC560PolygonView *)water->m_polygon)->getNumPoints();
		for (Int i = 0; i < numPoints; ++i) {
			p = ((Rva001AC560PolygonView *)water->m_polygon)->getPoint(i);
			newPoint.x = p->x;
			newPoint.y = p->y;
			newPoint.z = (Int)height;
			((Gen_0018F210 *)water->m_polygon)->bfmeSetVector3((const BfmeVector3BG *)&newPoint, i);
		}
		height = self->getWaterHeight(water);

	}

	{

	new (&affectedRegion) Region3D;
	affectedRegion.zero();
	findAxisAlignedBoundingRect(water, &affectedRegion);

	if (forcePathfindUpdate || previousHeight != height)
		((Rva003D5780 *)TheAI->pathfinder())->go();

	if (damageAmount > 0.0f && height > previousHeight) {

		Coord3D center;
		center.x = affectedRegion.lo.x + affectedRegion.width() / 2.0f;
		center.y = affectedRegion.lo.y + affectedRegion.height() / 2.0f;
		center.z = 0.0f;

		Real maxDist = (Real)waterRadius(affectedRegion.height() * affectedRegion.height() +
												 affectedRegion.width() * affectedRegion.width());

		BfmeWideResult hold =
			reinterpret_cast<BfmeWideForwardA *>(ThePartitionManager)
				->bfmeForwardWideA((int)&center, *(int *)&maxDist, 0, 0);

		Object *obj;
		const Coord3D *objPos;
		while ((obj = hold.next()) != 0) {

			objPos = obj->getPosition();
			if (self->isUnderwater(objPos->x, objPos->y, 0, 0)) {

				DamageInfo damageInfo;
				damageInfo.in.m_damageType = 9;
				damageInfo.in.m_deathType = 7;
				damageInfo.in.m_sourceID = 0;
				damageInfo.in.m_amount = damageAmount;
				obj->attemptDamage(&damageInfo);

			}
		}
	}

	}
}
