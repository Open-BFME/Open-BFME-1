// ?rva001F0480@BezierProjectileBehavior@@QAEXPAVObject@@PBUCoord3D@@@Z
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport

// BezierProjectileBehavior primary-interface body at retail 0x001F0480.
// The primary vtable and the two-argument thiscall ABI are proven by the
// constructor, vtable slot, and the caller at 0x001F1CE0.  The semantic
// method name remains address-derived pending lexical evidence.

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef int ObjectID;

enum KindOfType
{
	KINDOF_0x0A = 0x0A,
	KINDOF_0x59 = 0x59,
	KINDOF_0x61 = 0x61
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_SHROUDED = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D
{
public:
	Real Get_Z_Rotation() const;
};

class Drawable
{
public:
	void bfmeSet(Bool value);
	void bfmeDelayA(Int frames);
	void bfmeDelayB(Int frames);
	void bfmePair(Int a, Int b);
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
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
	virtual Drawable *getDrawable();

	void setOrientation(Real angle);
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	void bfmeRefreshPartitionCells();
	void bfmeRecordTransform(unsigned frame);

	char m_pad04[0x08 - 4];
	char m_mtx[0x30];
	Coord3D m_position;
	char m_pad044[0x78 - 0x44];
	ObjectID m_producerID;
	char m_pad07C[0x208 - 0x7C];
	void *m_orientExtra;
};

class WeaponTemplate
{
public:
	Real getWeaponSpeed() const { return m_weaponSpeed; }
	Real getMinWeaponSpeed() const { return m_minWeaponSpeed; }
	Bool isScaleWeaponSpeed() const { return m_scaleWeaponSpeed; }
	Real getMinimumAttackRange() const;
	Real getUnmodifiedAttackRange() const;
	Coord3D *getAimPosition(Coord3D *out, const Object *proj,
		const Object *victim, Int flag);

	char m_pad00[0x58];
	Real m_weaponSpeed;
	Real m_minWeaponSpeed;
	Real m_maxScaledSpeed;
	unsigned char m_scaleWeaponSpeed;
};

class BezierProjectileBehaviorModuleData
{
public:
	char m_pad00[0x18];
	unsigned char m_snapZToTerrain;
	char m_pad19[0x40 - 0x19];
	Int m_pairA;
	Int m_pairB;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);

	char m_pad00[0x3C];
	unsigned m_frame;
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

	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex,
		const Coord3D *pos) const;
};

class GameEngine
{
public:
	char m_pad00[0x34];
	Int m_frameScale;
};

class PlayerList
{
public:
	char m_pad00[0x0C];
	struct Inner
	{
		char m_pad00[0x24];
		Int m_localIndex;
	} *m_inner;
};

class LockIface
{
public:
	virtual void lock();
};

class UpdateModule
{
public:
	void setWakeFrame(Object *obj, unsigned sleep);
};

extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *TheShroudManager;
extern GameEngine *TheGameEngine;
extern PlayerList *ThePlayerList;
extern const Real BfmeZeroRange;

class BezierProjectileBehavior : public UpdateModule
{
public:
	void rva001F0480(Object *victim, const Coord3D *victimPos);
	Bool calcFlightPath(Bool recalcNumSegments);

	void *m_vtable;
	const BezierProjectileBehaviorModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x10 - 0x0C];
	LockIface m_lock;
	char m_pad14[0x3C - 0x14];
	WeaponTemplate *m_weapon;
	char m_pad40[0x50 - 0x40];
	Coord3D m_flightPathStart;
	Coord3D m_flightPathEnd;
	Real m_flightPathSpeed;
	Int m_flightPathSegments;
	Int m_currentFlightPathStep;
};

// ?rva001F0480@BezierProjectileBehavior@@QAEXPAVObject@@PBUCoord3D@@@Z
void BezierProjectileBehavior::rva001F0480(Object *victim,
	const Coord3D *victimPos)
{
	const BezierProjectileBehaviorModuleData *md = m_moduleData;
	int zero = 0;
	Object *obj = m_object;
	Real weaponSpeed;
	Real minWeaponSpeed;
	weaponSpeed = (m_weapon != (WeaponTemplate *)zero) ?
		m_weapon->getWeaponSpeed() : BfmeZeroRange;
	minWeaponSpeed = (m_weapon != (WeaponTemplate *)zero) ?
		m_weapon->getMinWeaponSpeed() : BfmeZeroRange;
	Coord3D framePad;

	setWakeFrame(obj, 1);

	if (md == (const BezierProjectileBehaviorModuleData *)zero)
		return;

	Coord3D victimPosToUse;
	if (victim != (Object *)zero)
	{
		Coord3D *aimed = m_weapon->getAimPosition(&framePad, obj, victim, 1);
		victimPosToUse = *aimed;
	}
	else
	{
		victimPosToUse = *victimPos;
	}

	if (md->m_snapZToTerrain)
	{
		if (TheTerrainLogic->getLayerForDestination((Object *)zero,
			&victimPosToUse) == LAYER_GROUND)
			victimPosToUse.z = TheTerrainLogic->getGroundHeight(
				victimPosToUse.x, victimPosToUse.y, zero);
	}

	if (m_weapon != (WeaponTemplate *)zero && m_weapon->isScaleWeaponSpeed())
	{
		Real lo = weaponSpeed;
		Real hi = minWeaponSpeed;
		if (hi < lo)
			hi = lo;

		Real minRange = m_weapon->getMinimumAttackRange();
		Real maxRange = m_weapon->getUnmodifiedAttackRange();
		Real dx = obj->m_position.x - victimPosToUse.x;
		Real dy = obj->m_position.y - victimPosToUse.y;
		Real distSq = dx * dx + dy * dy;
		Real speed = ((distSq - minRange) / (maxRange - minRange)) *
			(hi - lo) + lo;
		m_flightPathSpeed = speed;
		if (speed > m_weapon->m_maxScaledSpeed)
			m_flightPathSpeed = m_weapon->m_maxScaledSpeed;
	}
	else
	{
		m_flightPathSpeed = weaponSpeed;
	}

	if (obj->m_orientExtra != (void *)zero &&
		obj->isKindOf(KINDOF_0x61))
	{
		Real ang = ((const Matrix3D *)obj->m_mtx)->Get_Z_Rotation();
		obj->setOrientation(ang);
	}

	m_flightPathStart.x = obj->m_position.x;
	m_flightPathStart.y = obj->m_position.y;
	m_flightPathStart.z = obj->m_position.z;
	m_flightPathEnd.x = victimPosToUse.x;
	m_flightPathEnd.y = victimPosToUse.y;
	m_flightPathEnd.z = victimPosToUse.z;

	if (!calcFlightPath(true))
	{
		TheGameLogic->destroyObject(obj);
		return;
	}

	m_currentFlightPathStep = zero;

	Drawable *draw = obj->getDrawable();
	if (draw != (Drawable *)zero)
	{
		if (!obj->isKindOf(KINDOF_0x59) && !obj->isKindOf(KINDOF_0x0A))
		{
			Int player = zero;
			if (ThePlayerList != (PlayerList *)zero)
				player = ThePlayerList->m_inner->m_localIndex;

			Object *producer = TheGameLogic->findObjectByID(obj->m_producerID);
			Bool producerShrouded = false;
			if (producer != (Object *)zero &&
				producer->getShroudedStatus(player) == OBJECTSHROUD_SHROUDED)
				producerShrouded = true;

			Bool cellClear = TheShroudManager->getShroudStatusForPlayer(
				player, &m_flightPathEnd) == CELLSHROUD_CLEAR;

			if (producerShrouded)
			{
				if (!cellClear)
				{
					Int frames = (Int)((Real)TheGameEngine->m_frameScale *
						(Real)m_flightPathSegments);
					draw->bfmeDelayA(frames);
				}
				else if (md->m_pairA != zero || md->m_pairB != zero)
				{
					Real fb = (Real)md->m_pairB;
					if (md->m_pairB < zero)
						fb = fb + 4294967296.0f;
					Real fa = (Real)md->m_pairA;
					if (md->m_pairA < zero)
						fa = fa + 4294967296.0f;
					draw->bfmePair((Int)(fa * 0.03f),
						(Int)(fb * 0.03f));
				}
			}
			else if (cellClear)
			{
				Int frames = (Int)((Real)TheGameEngine->m_frameScale *
					(Real)m_flightPathSegments);
				draw->bfmeDelayB(frames);
			}
			else
			{
				draw->bfmeSet(true);
			}
		}
	}

	m_lock.lock();
	obj->bfmeRefreshPartitionCells();
	obj->bfmeRecordTransform(TheGameLogic->m_frame);
	m_lock.lock();
	obj->bfmeRefreshPartitionCells();
}
