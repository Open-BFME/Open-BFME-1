// ?update@BezierProjectileBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.966 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BezierProjectileBehavior::update, retail 0x001F0960, 1733 bytes.
//
// Zero Hour twin DumbProjectileBehavior::update (BFME renamed the behavior):
// detonate past the end of the flight path, retarget a moving victim through
// calcFlightPath, orient along or snap to the flight path, and detonate on a
// bridge drop. BFME adds a model-condition burst (ModuleData+0x3C frames before
// the end: a debug icon when GlobalData+0xEC8 is set, then a partition query
// over three temporary filters that applies ModuleData+0xA4 to everything in
// ModuleData+0xA8), a 0.5-height victim-contact check through the projectile
// interface at +0x20, and the next-position hint at Object+0x178.
// `this` is the UpdateModuleInterface subobject (module+0x10), as for every
// update() override. Member offsets follow the matched constructor
// 0x001F1470 and xfer 0x001F1860; the filter and result model follows the
// matched Rva002113A0NearbyObjects.cpp, with the relationship filter built by
// its real out-of-line constructor 0x000EC770.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <math.h>
#include "vector3.h"
#include "matrix3d.h"
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef unsigned int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1
};

struct Coord3D
{
	Real x, y, z;
	Real length() const;
	void normalize();
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
	void scale(Real k) { x *= k; y *= k; z *= k; }
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	unsigned char m_pad00[0x10];
	Real m_boundingSphereRadius;			// +0x10
};

class Object
{
public:
	void setTransformMatrix(const Matrix3D *mtx);	// Thing 0x00132200
	void setPosition(const Coord3D *pos);
	Int getLayer() const;
	void setLayer(PathfindLayerEnum layer);
	void notifyModelConditionChanged();
	void bfmeApplySpecialModelCondition(Int condition, const void *source, Int mode);

	unsigned char m_pad000[0x38];
	Coord3D m_position;				// +0x38
	unsigned char m_pad044[0xac - 0x44];
	GeometryInfo m_geometryInfo;			// +0xAC
	unsigned char m_padc0[0x120 - 0xc0];
	UnsignedInt m_modelConditionBits;		// +0x120
	unsigned char m_pad124[0x178 - 0x124];
	Coord3D m_extraPos;				// +0x178
	unsigned char m_pad184[2];
	Bool m_at186;					// +0x186

	void setExtraPos(const Coord3D &pos) { m_at186 = true; m_extraPos = pos; }
	const Coord3D *getPosition() const { return &m_position; }
};

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *out, const Object *source, const Object *victim, Int mode);
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);			// +0x18
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3D *normal, Bool clip);	// +0x1C
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges);
};
extern TerrainLogic *TheTerrainLogic;

class View
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void addIcon(const Coord3D *pos, Real width, Int color, Int duration);	// +0x30
};
extern View *TheTacticalView;

struct GlobalData
{
	unsigned char m_pad000[0xec8];
	Bool m_ec8;					// +0xEC8 debug icon switch
};
extern GlobalData *TheWritableGlobalData;

// ---- partition filters and the owning result (Rva002113A0NearbyObjects.cpp) ----
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(const Object *obj, Int flags, Bool match) throw();	// 0x000EC770
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual int getPlayerMask();

	const Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
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

class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType, PartitionFilter *, Bool);
};
extern PartitionManager *ThePartitionManager;

// ---- module ----
class ModuleData;

struct BezierProjectileBehaviorModuleData
{
	unsigned char m_pad00[0x3c];
	Int m_fxLeadSteps;					// +0x3C burst lead, frames before the end
	unsigned char m_pad40[8];
	Bool m_flag48;					// +0x48 tumble
	Bool m_enabled;					// +0x49 orient to flight path
	unsigned char m_pad4a[0x84 - 0x4a];
	Real m_flightPathAdjustDistPerFrame;					// +0x84 flight path adjust distance per frame
	unsigned char m_pad88[0xa4 - 0x88];
	Int m_invalidA4;				// +0xA4 special model condition (-1 none)
	Real m_valueA8;					// +0xA8 burst radius
};

class Module
{
public:
	virtual ~Module() {}
	const BezierProjectileBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class BezierProjectileInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(Object *victim);
};

class BezierProjectileSecondary
{
public:
	virtual void slot00();
};

class UpdateModule : public Module, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UnsignedInt m_nextCallFrameAndPhase;		// +0x14
	Int m_indexInLogic;				// +0x18
	Int m_currentUpdatePhase;			// +0x1C
};

class BezierProjectileBehavior
	: public UpdateModule, public BezierProjectileInterface, public BezierProjectileSecondary
{
public:
	virtual UpdateSleepTime update();
	Bool calcFlightPath(Bool recalcNumSegments);
	void projectileFire();

	// 0x001EFCE0
	UpdateSleepTime calcSleepTime() const
	{
		return m_flightPath.size() > 0 ? UPDATE_SLEEP_NONE : UPDATE_SLEEP_FOREVER;
	}

	ObjectID m_launcherID;				// +0x28
	Coord3D m_at2C;					// +0x2C
	ObjectID m_victimID;				// +0x38
	WeaponTemplate *m_aimWeapon;				// +0x3C
	const WeaponTemplate *m_at40;			// +0x40
	std::vector<Coord3D> m_flightPath;		// +0x44
	Coord3D m_flightPathStart;			// +0x50
	Coord3D m_flightPathEnd;			// +0x5C
	Real m_flightPathSpeed;				// +0x68
	Int m_flightPathSegments;			// +0x6C
	Int m_currentFlightPathStep;			// +0x70
	UnsignedInt m_extraBonusFlags;			// +0x74
	Int m_altCurve;					// +0x78
	unsigned char m_at7C[4];			// +0x7C list
	Bool m_hasDetonated;				// +0x80
	Real m_heightScale;				// +0x84
};

// ?update@BezierProjectileBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime BezierProjectileBehavior::update()
{
	const BezierProjectileBehaviorModuleData *d = m_moduleData;
	Object *obj = m_object;
	if (!d || !obj)
		return UPDATE_SLEEP_FOREVER;

	Int size = m_flightPath.size();
	if (m_currentFlightPathStep >= size)
	{
		slot0C(0);
		return calcSleepTime();
	}

	if (d->m_fxLeadSteps != 0 && m_currentFlightPathStep == size - d->m_fxLeadSteps)
	{
		if (!(obj->m_modelConditionBits & 0x20000))
		{
			obj->m_modelConditionBits |= 0x20000;
			obj->notifyModelConditionChanged();
		}
		if (d->m_invalidA4 != -1)
		{
			if (TheWritableGlobalData->m_ec8)
			{
				Coord3D pos;
				pos.x = m_flightPathEnd.x;
				pos.y = m_flightPathEnd.y;
				pos.z = m_flightPathEnd.z;
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
				TheTacticalView->addIcon(&pos, d->m_valueA8, 0xFFFF00FF, 0);
			}
			Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
				&m_flightPathEnd, d->m_valueA8, ITER_SORTED_NEAR_TO_FAR,
				PartitionFilterRelationship(obj, 7, false).link(
					Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter(obj))), true);
			Object *other;
			while (iterator.next(other))
			{
				if (other != obj)
					other->bfmeApplySpecialModelCondition(d->m_invalidA4, obj, 1);
			}
		}
	}

	if (m_victimID != 0 && d->m_flightPathAdjustDistPerFrame > 0.0f)
	{
		Object *victim = TheGameLogic->findObjectByID(m_victimID);
		if (victim)
		{
			Coord3D aim;
			Coord3D newVictimPos = *m_aimWeapon->getAimPosition(&aim, obj, victim, 1);
			Coord3D delta;
			delta.x = newVictimPos.x - m_flightPathEnd.x;
			delta.y = newVictimPos.y - m_flightPathEnd.y;
			delta.z = newVictimPos.z - m_flightPathEnd.z;
			Real distVictimMovedSqr = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
			if (distVictimMovedSqr > 0.1f)
			{
				Real distVictimMoved = sqrtf(distVictimMovedSqr);
				if (distVictimMoved > d->m_flightPathAdjustDistPerFrame)
					distVictimMoved = d->m_flightPathAdjustDistPerFrame;
				delta.normalize();
				m_flightPathEnd.x += distVictimMoved * delta.x;
				m_flightPathEnd.y += distVictimMoved * delta.y;
				m_flightPathEnd.z += distVictimMoved * delta.z;
				if (!calcFlightPath(false))
				{
					projectileFire();
					return calcSleepTime();
				}
			}
		}
	}

	const Coord3D *flightStep = &m_flightPath[m_currentFlightPathStep];

	if (d->m_enabled && !d->m_flag48)
	{
		Real drop = m_heightScale * 20.0f;
		Coord3D prevPos;
		Coord3D curPos;
		if (m_currentFlightPathStep > 0)
			prevPos = m_flightPath[m_currentFlightPathStep - 1];
		else
		{
			prevPos = m_flightPath[m_currentFlightPathStep];
			prevPos.z -= drop;
		}
		if (m_currentFlightPathStep < size - 1)
			curPos = m_flightPath[m_currentFlightPathStep + 1];
		else
		{
			curPos = m_flightPath[m_currentFlightPathStep];
			curPos.z -= drop;
		}
		Vector3 curDir(curPos.x - prevPos.x, curPos.y - prevPos.y, curPos.z - prevPos.z);
		curDir.Normalize();
		Matrix3D orientMtx;
		orientMtx.buildTransformMatrix(Vector3(flightStep->x, flightStep->y, flightStep->z), curDir);
		obj->setTransformMatrix(&orientMtx);
	}
	else
	{
		obj->setPosition(flightStep);
	}

	if (m_currentFlightPathStep < size - 1)
	{
		obj->setExtraPos(m_flightPath[m_currentFlightPathStep + 1]);
	}
	else
	{
		const Coord3D *pos = obj->getPosition();
		Coord3D next = *flightStep;
		next.scale(2.0f);
		next.sub(pos);
		obj->setExtraPos(next);
	}

	if (m_victimID != 0)
	{
		Object *victim = TheGameLogic->findObjectByID(m_victimID);
		if (victim)
		{
			Coord3D top = *victim->getPosition();
			top.z += victim->m_geometryInfo.getMaxHeightAbovePosition() * 0.5f;
			if (top.length() < victim->m_geometryInfo.m_boundingSphereRadius + m_flightPathSpeed)
				slot0C(victim);
		}
	}

	Int oldLayer = obj->getLayer();
	const Coord3D *pos = obj->getPosition();
	PathfindLayerEnum newLayer = TheTerrainLogic->getHighestLayerForDestination(pos, false);
	obj->setLayer(newLayer);

	if (oldLayer != LAYER_GROUND && newLayer == LAYER_GROUND)
	{
		Coord3D tmp;
		tmp.x = pos->x;
		tmp.y = pos->y;
		tmp.z = 9999.0f;
		PathfindLayerEnum testLayer = TheTerrainLogic->getHighestLayerForDestination(&tmp, false);
		if (testLayer == oldLayer)
		{
			tmp.z = TheTerrainLogic->getLayerHeight(tmp.x, tmp.y, testLayer, 0, true) + 2.0f;
			obj->setPosition(&tmp);
			projectileFire();
			return calcSleepTime();
		}
	}

	++m_currentFlightPathStep;
	return calcSleepTime();
}
