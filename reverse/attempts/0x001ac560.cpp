// ?setWaterHeight@TerrainLogic@@UAEXPBVWaterHandle@@MM_N@Z
// partial score=0.8 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oi
// readable body of ?setWaterHeight@TerrainLogic@@UAEXPBVWaterHandle@@MM_N@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	void zero()
	{
		lo.x = 0.0f;
		lo.y = 0.0f;
		lo.z = 0.0f;
		hi.x = 0.0f;
		hi.y = 0.0f;
		hi.z = 0.0f;
	}
	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/matrix3d.h
class Matrix3D
{
public:
	Real Row[3][4];

	Real Get_Z_Translation() const { return Row[2][3]; }
	void Set_Z_Translation(Real z) { Row[2][3] = z; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	void *m_vtable;
	PolygonTrigger *m_next;
	unsigned char m_pad08[8];
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
	void setPoint(const ICoord3D &point, Int index);
};

class WaterHandle
{
public:
	PolygonTrigger *m_polygon;
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

// ---------------------------------------------------------------------------
// The damage record retail builds on the stack. Layout and store order come
// from the 0x001AC560 body: the outer vftable, a 0x48-byte input block that
// carries its own vftable, then the outer tail.
// ---------------------------------------------------------------------------
extern "C" unsigned char bfmeVftCNDa[];
extern "C" unsigned char bfmeVftCNDb[];
extern "C" unsigned char bfmeVftDamageIn[];

struct DamageInfoInput
{
	void *m_vft;
	Int m_sourceID;
	UnsignedShort m_a08;
	Int m_damageType;
	Int m_a10;
	Int m_deathType;
	Real m_amount;
	Bool m_a1c;
	Bool m_a1d;
	Int m_a20;
	void *m_a24;
	void *m_a28;
	Int m_a2c;
	Int m_a30;
	Int m_a34;
	Int m_a38;
	Int m_a3c;
	Int m_a40;
	Real m_a44;

	DamageInfoInput()
		: m_vft(bfmeVftDamageIn),
		  m_a08(0),
		  m_a10(0xf),
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

struct DamageInfo
{
	void *m_vft;
	DamageInfoInput in;
	void *m_vft2;
	Int m_a50;
	Int m_a54;
	Bool m_a58;

	DamageInfo()
		: m_vft(bfmeVftCNDa),
		  m_vft2(bfmeVftCNDb),
		  m_a50(0),
		  m_a54(0),
		  m_a58(false)
	{
	}
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

	unsigned char m_pad04[0x34];
	Coord3D m_position;

	const Coord3D *getPosition() const { return &m_position; }
};

struct BfmeIterEntry
{
	Object *m_obj;
	void *m_extra;
};

namespace _STL {
	template <bool threads, int inst>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *p, unsigned int n);
	};
}

class BfmeObjectIterator
{
public:
	BfmeIterEntry *m_start;
	BfmeIterEntry *m_finish;
	BfmeIterEntry *m_endOfStorage;
	BfmeIterEntry *m_cur;
	Int m_refCount;

	Object *next()
	{
		BfmeIterEntry *finish = m_finish;
		if (m_cur == finish)
			return 0;
		Object *obj = m_cur->m_obj;
		++m_cur;
		return obj;
	}
};

struct BfmeWideResult
{
	BfmeObjectIterator *m_value;

	__forceinline ~BfmeWideResult()
	{
		m_value->m_refCount--;
		if (m_value->m_refCount == 0) {
			BfmeObjectIterator *iter = m_value;
			BfmeIterEntry *start = iter->m_start;
			if (start != 0) {
				unsigned int bytes = (unsigned int)(iter->m_endOfStorage - start) * sizeof(BfmeIterEntry);
				if (bytes > 0x80)
					operator delete(start);
				else
					_STL::__node_alloc<true, 0>::_M_deallocate(start, bytes);
			}
			operator delete(iter);
		}
	}
};

class BfmeWideForwardA
{
public:
	BfmeWideResult bfmeForwardWideA(int a, int b, int c, int d);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Pathfinder
{
public:
	void forceMapRecalculation();
};

class AI
{
public:
	unsigned char m_pad00[0xc];
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	void findAxisAlignedBoundingRect(const WaterHandle *water, Region3D *region);
	virtual void setWaterHeight(const WaterHandle *water, Real height, Real damageAmount,
															Bool forcePathfindUpdate);
};

void TerrainLogic::setWaterHeight(const WaterHandle *water, Real height, Real damageAmount,
																	Bool forcePathfindUpdate)
{
	TerrainLogicDispatch *self = reinterpret_cast<TerrainLogicDispatch *>(this);

	if (water == 0)
		return;

	Real previousHeight = 0.0f;
	if (water == &g_bfmeGridWaterHandle) {

		Matrix3D transform;
		g_bfmeTerrainVisual->getWaterTransform(water, &transform);
		previousHeight = transform.Get_Z_Translation();
		transform.Set_Z_Translation(height);
		g_bfmeTerrainVisual->setWaterTransform(&transform);

	} else {

		previousHeight = self->getWaterHeight(water);

		const ICoord3D *p;
		ICoord3D newPoint;
		Int numPoints = water->m_polygon->getNumPoints();
		for (Int i = 0; i < numPoints; ++i) {
			p = water->m_polygon->getPoint(i);
			newPoint.x = p->x;
			newPoint.y = p->y;
			newPoint.z = (Int)height;
			water->m_polygon->setPoint(newPoint, i);
		}
		height = self->getWaterHeight(water);

	}

	{

	Region3D affectedRegion;
	affectedRegion.zero();
	findAxisAlignedBoundingRect(water, &affectedRegion);

	if (forcePathfindUpdate || previousHeight != height)
		TheAI->pathfinder()->forceMapRecalculation();

	if (damageAmount > 0.0f && height > previousHeight) {

		Coord3D center;
		center.x = affectedRegion.lo.x + affectedRegion.width() / 2.0f;
		center.y = affectedRegion.lo.y + affectedRegion.height() / 2.0f;
		center.z = 0.0f;

		Real maxDist = (Real)sqrt(affectedRegion.height() * affectedRegion.height() +
												 affectedRegion.width() * affectedRegion.width());

		BfmeWideResult hold =
			reinterpret_cast<BfmeWideForwardA *>(ThePartitionManager)
				->bfmeForwardWideA((int)&center, *(int *)&maxDist, 0, 0);

		Object *obj;
		const Coord3D *objPos;
		while ((obj = hold.m_value->next()) != 0) {

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
