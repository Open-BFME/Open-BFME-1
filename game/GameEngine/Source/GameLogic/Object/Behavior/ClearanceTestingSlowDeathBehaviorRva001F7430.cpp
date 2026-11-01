// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include

// Open-BFME: ClearanceTestingSlowDeathBehavior clearance test, retail
// 0x001F7430 (675 bytes, ret at +0x288).  Constructor 0x001F7140 installs
// vtable 0x010A2FF0, whose slot 3 reaches this body through ILT 0x0001DBDD;
// the receiver is the interface at +0x24 (module data this-0x20, object
// this-0x1C).  Structure from the Open BFME 2 donor (45afcff3)
// Code/GameEngine/Source/Common/Rva00483C35Rva00483F19.cpp (its retail
// 0x00483F19): the clearance-geometry point transformed into the world, a
// closest-object query over a would-collide filter chained with a crusher
// filter, then a footprint walk comparing terrain layer heights against the
// object height plus the module data's high/low limits and fractions.
// BFME 1 offsets come from the retail body, callee names from the ledger.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum { LAYER_INVALID = 0 };

#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"

class Object;

class GeometryInfo
{
public:
	unsigned char m_pad00[0x14];
	Real m_boundingSphereRadius;				// +0x14
	unsigned char m_pad18[0x5c - 0x18];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilter
{
public:
	PartitionFilter() : m_base(0) { }
	virtual ~PartitionFilter() { }
	virtual Bool allow(Object *obj) = 0;

	PartitionFilter *link(PartitionFilter *next);

private:
	UnsignedInt m_base;
};

// Retail vftable 0x010860A0 (??_7PartitionFilterWouldCollide@@6B@).
class PartitionFilterWouldCollide : public PartitionFilter
{
public:
	PartitionFilterWouldCollide(const Coord3D &pos, const GeometryInfo *geometry,
		Real angle, Bool desired)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
		m_geometry = geometry;
		m_angle = angle;
		m_desired = desired;
	}

	virtual Bool allow(Object *obj)
	{
		return false;
	}

private:
	Coord3D m_position;
	const GeometryInfo *m_geometry;
	Real m_angle;
	Bool m_desired;
};

// Retail vftable 0x010A3118 (recorded as ??_7Rva001F6FC0VptrZeroObject@@6B@):
// an object and its crusher level.
class Rva001F6FC0VptrZeroObject : public PartitionFilter
{
public:
	Rva001F6FC0VptrZeroObject(Object *obj, unsigned char crusherLevel)
		: m_obj(obj), m_crusherLevel(crusherLevel) { }

	virtual Bool allow(Object *obj)
	{
		return false;
	}

private:
	Object *m_obj;
	unsigned char m_crusherLevel;
};

class BfmeC1050
{
public:
	void *bfmeGo1050D(Int, Int, Int, Int);
};
class PartitionManager;
extern PartitionManager *ThePartitionManager;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;

	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges = false);
};
extern TerrainLogic *TheTerrainLogic;

class Rva000FFCA0
{
public:
	~Rva000FFCA0();
};

extern void j_0003ed60();

class FootprintIterator001A1460
{
public:
	FootprintIterator001A1460(const GeometryInfo &geometry, Real angle, const Coord3D *position);

	Bool next(Coord2D *cell)
	{
		typedef Bool (FootprintIterator001A1460::*Call)(Coord2D *);
		union { void (*raw)(); Call call; } u;
		u.raw = &j_0003ed60;
		return (this->*u.call)(cell);
	}

private:
	Rva000FFCA0 m_geometryCopy;
	unsigned char m_pad[0xb4 - 1];
};

class Thing
{
public:
	void transformPoint(const Coord3D *in, Coord3D *out);
};

class Object : public Thing
{
public:
	unsigned char getCrusherLevel() const;

	unsigned char m_pad00[0x40];
	Real m_z;									// +0x40
	Real m_angle;								// +0x44
};

class ClearanceTestingSlowDeathBehaviorModuleData
{
public:
	unsigned char m_pad000[0x1a8];
	GeometryInfo m_geometry;					// +0x1A8
	Coord3D m_clearanceGeometryOffset;			// +0x204
	Real m_clearanceMaxHeight;					// +0x210
	Real m_clearanceMaxHeightFraction;			// +0x214
	Real m_clearanceMinHeight;					// +0x218
	Real m_clearanceMinHeightFraction;			// +0x21C
};

class Rva001F7430Interface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual Bool rva001F7430();
};

class Rva001F7430Module
{
public:
	virtual void s00();

protected:
	const ClearanceTestingSlowDeathBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;							// +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
};

// The class is the constructor's (0x001F7140 installs vtable 0x010A2FF0); the
// method name keeps the address because no evidence names it.
class ClearanceTestingSlowDeathBehavior : public Rva001F7430Module, public Rva001F7430Interface
{
public:
	virtual Bool rva001F7430();
};

// ?rva001F7430@ClearanceTestingSlowDeathBehavior@@UAE_NXZ
Bool ClearanceTestingSlowDeathBehavior::rva001F7430()
{
	const ClearanceTestingSlowDeathBehaviorModuleData *md = m_moduleData;
	Object *obj = m_object;
	if (0 == obj)
		return false;

	Coord3D center;
	obj->transformPoint(&md->m_clearanceGeometryOffset, &center);
	Real radius = md->m_geometry.m_boundingSphereRadius * 1.1f;
	if (((BfmeC1050 *)ThePartitionManager)->bfmeGo1050D((Int)&center, *(Int *)&radius, 3,
			(Int)Rva001F6FC0VptrZeroObject(obj, obj->getCrusherLevel()).link(
				&PartitionFilterWouldCollide(center, &md->m_geometry, obj->m_angle, true))))
		return false;

	if (md->m_clearanceMaxHeightFraction <= 1.0f || md->m_clearanceMinHeightFraction <= 1.0f)
	{
		if (TheTerrainLogic != 0)
		{
			Int total = 0;
			Real z = obj->m_z;
			Int high = 0, low = 0;
			Real angle = obj->m_angle;
			FootprintIterator001A1460 sampler(md->m_geometry, angle, &center);
			Coord2D pt;
			while (sampler.next(&pt))
			{
				++total;
				Coord3D probe;
				probe.x = pt.x;
				probe.y = pt.y;
				probe.z = z;
				Real h = TheTerrainLogic->getLayerHeight(pt.x, pt.y,
					TheTerrainLogic->getHighestLayerForDestination(&probe, false), 0, true);
				if (h > z + md->m_clearanceMaxHeight)
					++high;
				else if (h < z + md->m_clearanceMinHeight)
					++low;
			}
			if (total != 0)
			{
				if ((Real)high / (Real)total >= md->m_clearanceMaxHeightFraction
					|| (Real)low / (Real)total >= md->m_clearanceMinHeightFraction)
					return false;
			}
		}
	}
	return true;
}
