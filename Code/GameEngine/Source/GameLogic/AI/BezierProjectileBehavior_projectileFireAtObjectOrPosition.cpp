// ?projectileFireAtObjectOrPosition@BezierProjectileBehavior@@QAEXPAVObject@@PBUCoord3D@@@Z
// recovered from the 0x001F0480 generated body; 846-byte retail extent
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport

// BezierProjectileBehavior primary-interface body at retail 0x001F0480.
// The primary vtable and the two-argument thiscall ABI are proven by the
// constructor, vtable slot, and the caller at 0x001F1CE0.  The method identity follows the ZH DumbProjectile twin and the BFME caller/callee pins.

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef int ObjectID;

template <typename T>
static __forceinline const T &Luna10Max(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

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

// The bool setter already has a landed canonical owner in
// Common/S3ValueSetters.cpp.  The three effect calls are still only known by
// their incremental-link thunk names, so use the repository's typed member
// pointer adapters below rather than inventing /alternatename aliases.
class Gen_00411DD0
{
public:
	void bfmeSet(Bool value);
};

extern void j_0003f288();
extern void j_00046a1f();
extern void j_0002019e();
extern void j_0002bb43();

class Luna10DrawableDelayCall
{
};

typedef void (Luna10DrawableDelayCall::*Luna10Delay)(Int);
typedef void (Luna10DrawableDelayCall::*Luna10Pair)(Int, Int);

union Luna10DelayCallBits
{
	void (*raw)();
	Luna10Delay member;
};

union Luna10PairCallBits
{
	void (*raw)();
	Luna10Pair member;
};

static __forceinline void luna10DelayA(Gen_00411DD0 *draw, Int frames)
{
	Luna10DelayCallBits call;
	call.raw = j_0003f288;
	(reinterpret_cast<Luna10DrawableDelayCall *>(draw)->*call.member)(frames);
}

static __forceinline void luna10DelayB(Gen_00411DD0 *draw, Int frames)
{
	Luna10DelayCallBits call;
	call.raw = j_00046a1f;
	(reinterpret_cast<Luna10DrawableDelayCall *>(draw)->*call.member)(frames);
}

static __forceinline void luna10Pair(Gen_00411DD0 *draw, Int first, Int second)
{
	Luna10PairCallBits call;
	call.raw = j_0002019e;
	(reinterpret_cast<Luna10DrawableDelayCall *>(draw)->*call.member)(first, second);
}

class Luna10ObjectRecordCall
{
};

typedef void (Luna10ObjectRecordCall::*Luna10Record)(unsigned);

union Luna10RecordCallBits
{
	void (*raw)();
	Luna10Record member;
};

class Thing
{
public:
	virtual void vThing();
	Bool isKindOf(KindOfType kind) const;
	void setOrientation(Real angle);
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
	virtual Gen_00411DD0 *getDrawable();

	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	void bfmeRefreshPartitionCells();

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
	Bool isScaleWeaponSpeed() const { return m_isScaleWeaponSpeed; }
	Real getMinimumAttackRange() const;
	Real getUnmodifiedAttackRange() const;
	Coord3D *getAimPosition(Coord3D *out, const Object *proj,
		const Object *victim, Int flag);

	char m_pad00[0x58];
	Real m_weaponSpeed; // +0x58, name_oracle
	Real m_minWeaponSpeed; // +0x5c, name_oracle
	Real m_shockWaveRadius; // +0x60, name_oracle witness; MaxWeaponSpeed table row is an unresolved competing label
	unsigned char m_isScaleWeaponSpeed; // +0x64, name_oracle
};

class BezierProjectileBehaviorModuleData
{
public:
	char m_pad00[0x18];
	unsigned char m_snapZToTerrain;
	char m_pad19[0x40 - 0x19];
	unsigned int m_value40; // +0x40, constructor witness
	unsigned int m_value44; // +0x44, constructor witness
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

static __forceinline void luna10RecordTransform(Object *object, unsigned frame)
{
	Luna10RecordCallBits call;
	call.raw = j_0002bb43;
	(reinterpret_cast<Luna10ObjectRecordCall *>(object)->*call.member)(frame);
}

extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *TheShroudManager;
extern GameEngine *TheGameEngine;
extern PlayerList *ThePlayerList;
extern const Real BfmeZeroRange;

class BezierProjectileBehavior : public UpdateModule
{
public:
	void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
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

// ?projectileFireAtObjectOrPosition@BezierProjectileBehavior@@QAEXPAVObject@@PBUCoord3D@@@Z
void BezierProjectileBehavior::projectileFireAtObjectOrPosition(Object *victim,
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
		weaponSpeed = Luna10Max(weaponSpeed, minWeaponSpeed);

		Real minRange = m_weapon->getMinimumAttackRange();
		Real maxRange = m_weapon->getUnmodifiedAttackRange();
		Real dx = obj->m_position.x - victimPosToUse.x;
		Real dy = obj->m_position.y - victimPosToUse.y;
		Real distSq = dx * dx + dy * dy;
		Real speed = ((distSq - minRange) / (maxRange - minRange)) *
			(weaponSpeed - minWeaponSpeed) + minWeaponSpeed;
		m_flightPathSpeed = speed;
		if (speed > m_weapon->m_shockWaveRadius)
			m_flightPathSpeed = m_weapon->m_shockWaveRadius;
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

	m_flightPathStart = *(const Coord3D *)((const char *)m_object + 0x38);
	m_flightPathEnd = victimPosToUse;

	if (!calcFlightPath(true))
	{
		TheGameLogic->destroyObject(obj);
		return;
	}

	m_currentFlightPathStep = zero;

	Gen_00411DD0 *draw = obj->getDrawable();
	if (draw != (Gen_00411DD0 *)zero)
	{
		if (!obj->isKindOf(KINDOF_0x59) && !obj->isKindOf(KINDOF_0x0A))
		{
						Int player = (ThePlayerList == (PlayerList *)zero) ?
				zero : ThePlayerList->m_inner->m_localIndex;

			Object *producer = TheGameLogic->findObjectByID(obj->m_producerID);
			Bool producerShrouded = false;
			if (producer != (Object *)zero &&
				producer->getShroudedStatus(player) == OBJECTSHROUD_SHROUDED)
				producerShrouded = true;
			else
				producerShrouded = false;

			Bool cellClear = TheShroudManager->getShroudStatusForPlayer(
				player, &m_flightPathEnd) == CELLSHROUD_CLEAR;

			if (producerShrouded)
			{
				if (!cellClear)
				{
					Int frames = (Int)((Real)TheGameEngine->m_frameScale *
						(Real)m_flightPathSegments);
					luna10DelayA(draw, frames);
				}
				else if (md->m_value40 != zero || md->m_value44 != zero)
				{
					luna10Pair(draw, (Int)((Real)md->m_value40 * 0.03f),
						(Int)((Real)md->m_value44 * 0.03f));
				}
			}
			else if (cellClear)
			{
				Int frames = (Int)((Real)TheGameEngine->m_frameScale *
					(Real)m_flightPathSegments);
					luna10DelayB(draw, frames);
			}
			else
			{
				draw->bfmeSet(true);
			}
		}
	}

	m_lock.lock();
	m_object->bfmeRefreshPartitionCells();
	luna10RecordTransform(m_object, TheGameLogic->m_frame);
	m_lock.lock();
	m_object->bfmeRefreshPartitionCells();
}


