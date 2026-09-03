// ?exitObjectViaDoor@QueueProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.91 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /GX /O2 /Ob2 /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
// Retail 0x002D0F00, 1083 bytes: QueueProductionExitUpdate::exitObjectViaDoor.
// ExitInterface this (module+0x20): object at [this-0x18], moduleData at
// [this-0x1C]. unitCreatePoint at md+8, allowAirborne at md+0x24, extraZ at
// md+0x2C, skipPath at md+0x30, exitDelay at md+0x20. Delay at this+4, rally
// at +8, exists at +0x14, burst at +0x1C, lastExitId at +0x20. ret 8.

#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "matrix3d.h"
#include <vector>

typedef float Real;

enum ExitDoorType { DOOR_1 = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };
enum KindOfType { KINDOF_DOZER = 0x6C, KINDOF_AIRCRAFT = 0x09 };
enum DisabledType { DISABLED_HELD = 3 };

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct StructureCollapsePosition
{
	Real x;
	Real y;
	Real z;
};

class Object;
class LocomotorSet;
class PhysicsBehavior;
class GameLogicFrameSlice;

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void snapPosition(Object *obj, Coord3D *pos);
	void snapAfterFollow(Object *obj, Coord3D *pos);
	bool adjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dest, const Coord3D *pathDest);
};

class AI
{
public:
	unsigned char pad[0x0C];
	Pathfinder *m_pathfinder;
};

extern "C" AI *_TheAIParseDefinitionAI;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, void *normal);
};

extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class GameLogicFrameSlice
{
public:
	Object *bfmeFind(int id);
};

extern GameLogicFrameSlice *TheGameLogic;

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *obj, int tag);
};

extern const Real BfmeZeroRange;
extern "C" const Real g_bfmeDefaultBU;
extern const Real g_bfmeFlyZ;
extern const Real g_bfmeHeightMin;

class AICommandInterface
{
public:
	void aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *source, CommandSourceType cmd);
	void aiIdle(CommandSourceType cmd);
};

#define QV(n) virtual void slot_##n()
#define QV10(p) \
	QV(p##0); QV(p##1); QV(p##2); QV(p##3); QV(p##4); \
	QV(p##5); QV(p##6); QV(p##7); QV(p##8); QV(p##9)

class AIUpdateInterface
{
public:
	QV10(00); QV10(01); QV10(02); QV10(03); QV10(04);
	QV10(05); QV10(06);
	QV(70); QV(71); QV(72); QV(73); QV(74); QV(75);
	virtual bool isDoingGroundMovement() const;

	const LocomotorSet &getLocomotorSet() const
	{
		return *reinterpret_cast<const LocomotorSet *>(
			reinterpret_cast<const unsigned char *>(this) + 0x1A8);
	}

	void aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *source, CommandSourceType cmd)
	{
		reinterpret_cast<AICommandInterface *>(reinterpret_cast<unsigned char *>(this) + 0x20)
			->aiFollowExitProductionPath(path, source, cmd);
	}

	void aiIdle(CommandSourceType cmd)
	{
		reinterpret_cast<AICommandInterface *>(reinterpret_cast<unsigned char *>(this) + 0x20)
			->aiIdle(cmd);
	}
};

class Thing
{
public:
	void setOrientation(Real angle);
	bool isKindOf(KindOfType k) const;
};

class PhysicsBehavior
{
public:
	void applyMotiveForce(const Coord3D *force);
};

class StructureCollapseRetailObject
{
public:
	void setPosition(const StructureCollapsePosition &pos, bool update);
};

class HostAI
{
public:
	QV10(00); QV10(01);
	QV(20); QV(21); QV(22); QV(23); QV(24); QV(25);
	virtual void *getInterface();
};

class HostIface
{
public:
	QV(00); QV(01); QV(02); QV(03); QV(04);
	QV(05); QV(06); QV(07); QV(08); QV(09);
	QV(10);
	virtual void onSpawn(Object *obj);
};

class Field210
{
public:
	void apply(int value);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class Object
{
public:
	void setPosition(const Coord3D *pos);
	bool clearDisabled(DisabledType dt);
	void getVelocity(Coord3D *out) const;
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	void attachToHost(Object *host);
	void setMode(int a, int b);

	QV(00); QV(01); QV(02); QV(03); QV(04);
	QV(05); QV(06); QV(07); QV(08); QV(09);
	QV(10); QV(11); QV(12); QV(13); QV(14);
	QV(15); QV(16); QV(17); QV(18); QV(19);
	virtual bool testStatus(int bit);

	Real getOrientation() const
	{
		return *reinterpret_cast<const Real *>(reinterpret_cast<const unsigned char *>(this) + 0x44);
	}

	const Matrix3D *getTransformMatrix() const
	{
		return reinterpret_cast<const Matrix3D *>(reinterpret_cast<const unsigned char *>(this) + 8);
	}

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x204);
	}

	PhysicsBehavior *getPhysics() const
	{
		return *reinterpret_cast<PhysicsBehavior *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x208);
	}

	int getTag370() const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x370);
	}

	HostAI *getAltAI() const
	{
		return *reinterpret_cast<HostAI *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x1FC);
	}

	int getId74() const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x74);
	}

	Field210 *getField210() const
	{
		return *reinterpret_cast<Field210 *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x210);
	}

	int getField23C() const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x23C);
	}

	void *getDrawable() const
	{
		return *reinterpret_cast<void *const *>(reinterpret_cast<const unsigned char *>(this) + 4);
	}
};

class QueueProductionExitUpdateModuleData
{
public:
	unsigned char pad[8];
	Coord3D m_unitCreatePoint;
	Coord3D m_naturalRallyPoint;
	unsigned m_exitDelayData;
	bool m_allowAirborneCreationData;
	unsigned char pad24[0x2C - 0x25];
	Real m_extraZ;
	bool m_skipPath;
};

class QueueProductionExitUpdate
{
public:
	virtual bool isExitBusy() const;
	virtual ExitDoorType reserveDoorForExit(const void *, Object *);
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);
	virtual void exitObjectByBudding(Object *, Object *);
	virtual void unreserveDoorForExit(ExitDoorType);
	virtual void exitObjectInAHurry(Object *) {}
	virtual void setRallyPoint(const Coord3D *);
	virtual const Coord3D *getRallyPoint() const;
	virtual bool useSpawnRallyPoint() const { return false; }
	virtual bool getNaturalRallyPoint(Coord3D &rallyPoint, bool offset = true) const;
	virtual bool getExitPosition(Coord3D &) const;

	unsigned m_currentDelay;
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
	float m_creationClearDistance;
	unsigned m_currentBurstCount;
	int m_lastExitId;
};

struct ExitPath : public std::vector<Coord3D>
{
	__forceinline void push_one(const Coord3D &x)
	{
		_M_insert_overflow(this->_M_finish, x, _STL::__false_type(), 1UL, true);
	}
};

void QueueProductionExitUpdate::exitObjectViaDoor(Object *newObj, ExitDoorType)
{
	Object *produced = newObj;
	Object *creationObject = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 0x18);
	if (!creationObject)
		return;

	const QueueProductionExitUpdateModuleData *md =
		*reinterpret_cast<const QueueProductionExitUpdateModuleData *const *>(
			reinterpret_cast<char *>(this) - 0x1C);

	const Matrix3D *transform = creationObject->getTransformMatrix();
	Vector3 loc;
	loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z);
	transform->Transform_Vector(*transform, loc, &loc);

	bool creationInAir = false;
	if (TheTerrainLogic)
	{
		Real ground = TheTerrainLogic->getGroundHeight(loc.X, loc.Y, 0);
		if (ground + g_bfmeDefaultBU < loc.Z)
		{
			creationInAir = true;
			if (!md->m_allowAirborneCreationData)
				loc.Z = TheTerrainLogic
					? TheTerrainLogic->getGroundHeight(loc.X, loc.Y, 0)
					: BfmeZeroRange;
		}
	}

	Coord3D createPoint;
	createPoint.x = loc.X;
	createPoint.y = loc.Y;
	createPoint.z = loc.Z;

	AIUpdateInterface *ai = produced->getAIUpdateInterface();
	if (ai && ai->isDoingGroundMovement())
		createPoint.z += g_bfmeFlyZ;

	reinterpret_cast<StructureCollapseRetailObject *>(produced)->setPosition(
		*reinterpret_cast<const StructureCollapsePosition *>(&createPoint), true);
	reinterpret_cast<Thing *>(produced)->setOrientation(
		creationObject->getOrientation() + md->m_extraZ);

	PhysicsBehavior *phys = produced->getPhysics();
	Coord3D startingForce;
	creationObject->getVelocity(&startingForce);
	Real height = creationObject->bfmeGetNonnegativePreferredLocomotorHeight();
	if (creationInAir && phys && height > g_bfmeHeightMin)
	{
		startingForce.x *= height;
		startingForce.y *= height;
		startingForce.z *= height;
		phys->applyMotiveForce(&startingForce);
	}

	reinterpret_cast<BfmeGlobFEA *>(TheGameLogic)->bfmeCallFEA(produced, creationObject->getTag370());
	_TheAIParseDefinitionAI->m_pathfinder->addObjectToPathfindMap(produced);

	Object *host = reinterpret_cast<GameLogic *>(TheGameLogic)->findObjectByID(m_lastExitId);
	if (host)
	{
		HostAI *hostAI = host->getAltAI();
		if (hostAI)
		{
			HostIface *iface = reinterpret_cast<HostIface *>(hostAI->getInterface());
			if (iface)
			{
				produced->attachToHost(host);
				produced->getField210()->apply(host->getId74());
				iface->onSpawn(produced);
				produced->testStatus(host->getField23C());
			}
		}
	}

	Coord3D tmp;
	if (ai)
	{
		getNaturalRallyPoint(tmp, true);
		_TheAIParseDefinitionAI->m_pathfinder->snapPosition(produced, &tmp);
		ExitPath exitPath;
		exitPath.push_one(tmp);

		bool useRally;
		if (reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_DOZER))
			useRally = false;
		else
		{
			useRally = true;
			if (host)
				useRally = false;
		}
		if (reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_DOZER)
			&& reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_AIRCRAFT))
			useRally = true;

		if (m_rallyPointExists && useRally)
		{
			tmp = m_rallyPoint;
			if (!ai->isDoingGroundMovement())
			{
				if (_TheAIParseDefinitionAI->m_pathfinder->adjustDestination(
					produced, ai->getLocomotorSet(), &tmp, 0))
					exitPath.push_back(tmp);
			}
			else
			{
				exitPath.push_back(tmp);
			}
		}

		if (!md->m_skipPath)
		{
			produced->clearDisabled(DISABLED_HELD);
			ai->aiFollowExitProductionPath(&exitPath, creationObject, CMD_FROM_AI);
			_TheAIParseDefinitionAI->m_pathfinder->snapAfterFollow(produced, &tmp);
		}
		else
		{
			ai->aiIdle(CMD_FROM_AI);
		}
	}

	void *draw = produced->getDrawable();
	if (draw)
	{
		void *inner = *reinterpret_cast<void **>(reinterpret_cast<char *>(draw) + 4);
		if (inner)
			draw = const_cast<Overridable *>(
				reinterpret_cast<const Overridable *>(inner)->getFinalOverride());
	}
	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(draw) + 0xD4) & 0x1000)
	{
		getNaturalRallyPoint(tmp, true);
		_TheAIParseDefinitionAI->m_pathfinder->snapPosition(produced, &tmp);
		if (!reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_AIRCRAFT))
			produced->setPosition(&tmp);
		m_lastExitId = produced->getId74();
		produced->setMode(3, 1);
		produced->setMode(2, 1);
	}

	m_currentDelay = md->m_exitDelayData;
	if (m_currentBurstCount)
		m_currentBurstCount--;
}
