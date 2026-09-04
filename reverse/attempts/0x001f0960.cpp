// ?update@BezierProjectileBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.42 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BezierProjectileBehavior::update, retail 0x001F0960 size 1733.
// Identity: calls calcFlightPath ILT 0x00021BD9, projectileFire 0x001F00A0,
// getAimPosition, Inv_Sqrt, buildTransformMatrix, setPosition/setLayer,
// getHighestLayerForDestination. ecx is the UpdateModuleInterface this
// (module+0x10): [this-0xC] module data, [this-8] Object*, vector at +0x34
// (dtor-proven 12-byte flight path at module+0x44), step at +0x60.
// ZH twin is DumbProjectileBehavior::update; BFME adds a model-condition
// burst, victim-aim path adjust via getAimPosition, and an extra pos at
// Object+0x178.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <math.h>

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

extern const Real BfmeZeroRange;
extern const Real g_bfmeScaleBK;
extern const Real g_bfmeADL;
extern const Real g_bfmeFudge2;
extern const Real g_bfmeTumbleScale;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize();
	Real length() const;
};

struct Vector3
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D
{
public:
	void buildTransformMatrix(const Vector3 &pos, const Vector3 &dir);

private:
	Real m[12];
};

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;

private:
	char m_pad[0x10];
};

class Thing
{
public:
	virtual void slot00();
	void setTransformMatrix(const Matrix3D *mtx);
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	Int getLayer() const;
	void setLayer(PathfindLayerEnum layer);
	void applySpecialModelCondition(Int a, const void *b, Int c);
	void applyOwnerNotify();

	char m_pad04[0x38 - 4];
	Coord3D m_position;
	char m_pad44[0xAC - 0x44];
	GeometryInfo m_geom;
	Real m_radius;
	char m_padC0[0x120 - 0xC0];
	unsigned m_status120;
	char m_pad124[0x178 - 0x124];
	Coord3D m_extraPos;
	char m_pad184[0x186 - 0x184];
	unsigned char m_extraFlag;
};

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *out, const Object *proj, const Object *victim, Int flag);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Int extra);
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Int extra, Int extra2);

	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges);
};

class View
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void addDebugIcon(const Coord3D *pos, Int color, Int player, Int flag);
};

class GlobalData
{
public:
	char m_pad[0xEC8];
	unsigned char m_debugProjectiles;
};

class BezierProjectileBehaviorModuleData
{
public:
	char m_pad00[0x3C];
	Int m_fxLeadSteps;
	char m_pad40[0x48 - 0x40];
	unsigned char m_tumbleRandomly;
	unsigned char m_orientToFlightPath;
	char m_pad4A[0x84 - 0x4A];
	Real m_flightPathAdjustDistPerFrame;
	char m_pad88[0xA4 - 0x88];
	Int m_modelCondition;
	Int m_debugPlayer;
};

class Gen_001EFCE0
{
public:
	int bfmeCost() const;
};

class WideGuard
{
public:
	WideGuard();
	~WideGuard();
};

void keepWideGuard(WideGuard *);

struct FlightPod
{
	int a[3];
};

class CollideIface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void handleCollision(Object *other);
};

extern GameLogic *TheBfmeGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;
extern GlobalData *TheWritableGlobalData;

class BezierProjectileBehavior
{
public:
	virtual UpdateSleepTime update();

	Bool calcFlightPath(Bool recalc);
	void projectileFire();

	unsigned m_nextCallFrame;
	int m_indexInLogic;
	unsigned m_updateState;
	CollideIface m_collide;
	void *m_iface24;
	char m_pad18[0x28 - 0x18];
	ObjectID m_victimId;
	WeaponTemplate *m_aimWeapon;
	char m_pad30[0x34 - 0x30];
	_STL::vector<FlightPod> m_flightPath;
	char m_pad40[0x4C - 0x40];
	Coord3D m_flightPathEnd;
	Real m_flightPathSpeed;
	int m_flightPathSegments;
	int m_currentFlightPathStep;
	char m_pad64[0x74 - 0x64];
	Real m_heightScale;
};

static UpdateSleepTime sleepFromPathSize(Int n)
{
	return n ? UPDATE_SLEEP_NONE : UPDATE_SLEEP_FOREVER;
}

static BezierProjectileBehavior *complete(BezierProjectileBehavior *iface)
{
	return (BezierProjectileBehavior *)((char *)iface - 0x10);
}

// ?update@BezierProjectileBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime BezierProjectileBehavior::update()
{
	BezierProjectileBehaviorModuleData *md =
		*(BezierProjectileBehaviorModuleData **)((char *)this - 0x0C);
	int z = 0;
	Object *obj = *(Object **)((char *)this - 8);
	if ((int)md == z || (int)obj == z)
		return UPDATE_SLEEP_FOREVER;

	Int pathSize = (Int)m_flightPath.size();
	if (m_currentFlightPathStep >= pathSize)
	{
		m_collide.handleCollision((Object *)z);
		return sleepFromPathSize((Int)m_flightPath.size());
	}

	if (md->m_fxLeadSteps != z && m_currentFlightPathStep == pathSize - md->m_fxLeadSteps)
	{
		if ((obj->m_status120 & 0x20000) == (unsigned)z)
		{
			obj->m_status120 |= 0x20000;
			obj->applyOwnerNotify();
		}
		if (md->m_modelCondition != -1)
		{
			if (TheWritableGlobalData->m_debugProjectiles)
			{
				Coord3D pos;
				pos.y = m_flightPathEnd.y;
				pos.z = m_flightPathEnd.z;
				pos.x = m_flightPathEnd.x;
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, z);
				TheTacticalView->addDebugIcon(&pos, 0xFFFF00FF, md->m_debugPlayer, z);
			}
			WideGuard wr;
			keepWideGuard(&wr);
		}
	}

	if (m_victimId != 0 && md->m_flightPathAdjustDistPerFrame > BfmeZeroRange)
	{
		Object *victim = TheBfmeGameLogic->findObjectByID(m_victimId);
		if (victim)
		{
			Coord3D newVictimPos;
			m_aimWeapon->getAimPosition(&newVictimPos, obj, victim, 1);
			Coord3D delta;
			delta.x = newVictimPos.x - m_flightPathEnd.x;
			delta.y = newVictimPos.y - m_flightPathEnd.y;
			delta.z = newVictimPos.z - m_flightPathEnd.z;
			Real distVictimMovedSqr = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
			if (distVictimMovedSqr > g_bfmeScaleBK)
			{
				Real distVictimMoved = sqrtf(distVictimMovedSqr);
				if (distVictimMoved > md->m_flightPathAdjustDistPerFrame)
					distVictimMoved = md->m_flightPathAdjustDistPerFrame;
				delta.normalize();
				m_flightPathEnd.x += distVictimMoved * delta.x;
				m_flightPathEnd.y += distVictimMoved * delta.y;
				m_flightPathEnd.z += distVictimMoved * delta.z;
				BezierProjectileBehavior *self = complete(this);
				if (!self->calcFlightPath(false))
				{
					self->projectileFire();
					return (UpdateSleepTime)((Gen_001EFCE0 *)self)->bfmeCost();
				}
			}
		}
	}

	Coord3D *begin = (Coord3D *)&m_flightPath[0];
	Coord3D *flightStep = begin + m_currentFlightPathStep;

	if (md->m_orientToFlightPath && !md->m_tumbleRandomly)
	{
		Real tumble = m_heightScale * g_bfmeTumbleScale;
		Coord3D prevPos;
		if (m_currentFlightPathStep > 0)
			prevPos = begin[m_currentFlightPathStep - 1];
		else
		{
			prevPos = begin[0];
			prevPos.z -= tumble;
		}
		Coord3D curPos;
		if (m_currentFlightPathStep < pathSize - 1)
			curPos = begin[m_currentFlightPathStep + 1];
		else
		{
			curPos = *flightStep;
			curPos.z -= tumble;
		}
		Vector3 curDir;
		curDir.x = curPos.x - prevPos.x;
		curDir.y = curPos.y - prevPos.y;
		curDir.z = curPos.z - prevPos.z;
		Real len2 = curDir.x * curDir.x + curDir.y * curDir.y + curDir.z * curDir.z;
		if (len2 != BfmeZeroRange)
		{
			Real inv = WWMath::Inv_Sqrt(len2);
			curDir.x *= inv;
			curDir.y *= inv;
			curDir.z *= inv;
		}
		Vector3 pos;
		pos.x = flightStep->x;
		pos.y = flightStep->y;
		pos.z = flightStep->z;
		Matrix3D orientMtx;
		orientMtx.buildTransformMatrix(pos, curDir);
		obj->setTransformMatrix(&orientMtx);
	}
	else
	{
		obj->setPosition(flightStep);
	}

	if (m_currentFlightPathStep < pathSize - 1)
	{
		obj->m_extraFlag = 1;
		obj->m_extraPos = begin[m_currentFlightPathStep + 1];
	}
	else
	{
		obj->m_extraFlag = 1;
		obj->m_extraPos.x = obj->m_position.x + obj->m_position.x - flightStep->x;
		obj->m_extraPos.y = obj->m_position.y + obj->m_position.y - flightStep->y;
		obj->m_extraPos.z = obj->m_position.z + obj->m_position.z - flightStep->z;
	}

	if (m_victimId != 0)
	{
		Object *victim = TheBfmeGameLogic->findObjectByID(m_victimId);
		if (victim)
		{
			Coord3D vicPos = victim->m_position;
			vicPos.z += victim->m_geom.getMaxHeightAbovePosition() * g_bfmeADL;
			if (victim->m_radius + m_flightPathSpeed > vicPos.length())
				m_collide.handleCollision(victim);
		}
	}

	PathfindLayerEnum oldLayer = (PathfindLayerEnum)obj->getLayer();
	PathfindLayerEnum newLayer = TheTerrainLogic->getHighestLayerForDestination(&obj->m_position, false);
	obj->setLayer(newLayer);

	if (oldLayer != LAYER_GROUND && newLayer == LAYER_GROUND)
	{
		Coord3D tmp = obj->m_position;
		tmp.z = 9999.0f;
		PathfindLayerEnum testLayer = TheTerrainLogic->getHighestLayerForDestination(&tmp, false);
		if (testLayer == oldLayer)
		{
			tmp.z = TheTerrainLogic->getLayerHeight(tmp.x, tmp.y, testLayer, 0, 1) + g_bfmeFudge2;
			obj->setPosition(&tmp);
			BezierProjectileBehavior *self = complete(this);
			self->projectileFire();
			return (UpdateSleepTime)((Gen_001EFCE0 *)self)->bfmeCost();
		}
	}

	++m_currentFlightPathStep;
	return sleepFromPathSize((Int)m_flightPath.size());
}
