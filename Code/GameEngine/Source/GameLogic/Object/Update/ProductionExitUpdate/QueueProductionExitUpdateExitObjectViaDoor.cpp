// ?exitObjectViaDoor@QueueProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /GX /O2 /Ob2 /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
// Retail 0x002D0F00, 1083 bytes: QueueProductionExitUpdate::exitObjectViaDoor.
// ExitInterface this (module+0x20): object at [this-0x18], moduleData at
// [this-0x1C]. unitCreatePoint at md+8, allowAirborne at md+0x24, exitAngleOffset at
// md+0x2C, skipPath at md+0x30, exitDelay at md+0x20. Delay at this+4, rally
// at +8, exists at +0x14, burst at +0x1C, lastExitId at +0x20. ret 8.
// Actual ctor2D0620 installs ExitInterface vtable10CB654 at whole module+20;
// slot2 names this body, slot9 is the independently matched natural-rally getter.
// ModuleFactory12E6B7 pairs literal1090470 with factory11AE40, which calls
// ctor2D0620. Pool2D06F0 and name getter2D06C0 repeat the same class literal.
// BFME-specific branches: giant birds start500 units higher; hordes inherit
// producer/experience sink/team and may redirect created members to their host.
// The visible220B command builder copies the vector, allowing its dead storage
// to be reused by the final rally point. Canonical Coord3D base assignment and
// AI::pathfinder() accessor preserve the retail alias and register schedule.

#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "matrix3d.h"
#include <vector>

typedef float Real;

enum ObjectID {INVALID_ID=0};
class Team;
class HordeContainInterface;

enum ExitDoorType { DOOR_1 = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };
enum KindOfType { KINDOF_HORDE = 0x6C, KINDOF_VEHICLE = 0x09 };
enum DisabledType { DISABLED_HELD = 3 };

// Canonical BFME copy model, shared with WWMath/coord3d.cpp.
struct Coord3DBase
{
 Real x, y, z;
 Coord3DBase &operator=(const Coord3DBase &other)
 {
  struct Raw { unsigned x, y, z; };
  *(Raw *)this = *(const Raw *)&other;
  return *this;
 }
};
struct Coord3D : public Coord3DBase {
 Coord3D() {} ~Coord3D() {}
 Coord3D(const Coord3D &other) {x=other.x;y=other.y;z=other.z;}
 Coord3D &operator=(const Coord3D &other) {Coord3DBase *base=this; *base=other;return *this;}
};

class StructureCollapsePosition
{
public:
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
	void moveAlliesAwayFromDestination(Object *obj, const Coord3D &pos);
	bool adjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dest, const Coord3D *pathDest);
};

class AI
{
public:
	unsigned char pad[0x0C];
	Pathfinder *m_pathfinder;
 Pathfinder *pathfinder() const {return m_pathfinder;}
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

void j_0003a279();
class GameLogicColorIndexView
{
public:
	void applyObjectColorIndex383930(Object *obj, int colorIndex) {
  // Retail ILT3A279 enters383930: adjust GameLogic this by170 then tail to361250.
  // That113-byte ret8 body applies the selected time-of-day palette color.
  union {void (*code)();void (GameLogicColorIndexView::*method)(Object*,int);} call;
  call.code=j_0003a279;(this->*call.method)(obj,colorIndex);
 }
};


enum AICommandType {AICMD_FOLLOW_EXITPRODUCTION_PATH=10};
struct AICommandParms {
 AICommandType cmd;CommandSourceType source;Coord3D pos;Object *obj;Object *other;void *team;std::vector<Coord3D> coords;void *way;void *poly;int intValue;char damage[0x5c];void *button;void *path;
 AICommandParms(AICommandType,CommandSourceType);
};
class AICommandInterface
{
public:
 virtual void aiDoCommand(const AICommandParms *parms)=0;
	void aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *source, CommandSourceType cmd);
	void aiIdle(CommandSourceType cmd);
};

__declspec(noinline) void AICommandInterface::aiFollowExitProductionPath(const std::vector<Coord3D> *path,Object *source,CommandSourceType cmd) {
 AICommandParms parms(AICMD_FOLLOW_EXITPRODUCTION_PATH,cmd);
 parms.coords=*path;parms.obj=source;aiDoCommand(&parms);
}

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
	virtual bool isGiantBird() const;

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
	void getUnitDirectionVector3D(Coord3D &direction) const;
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

class ContainModuleInterface
{
public:
	QV10(00); QV10(01);
	QV(20); QV(21); QV(22); QV(23); QV(24); QV(25);
	virtual HordeContainInterface *getHordeContainInterface();
};

class HordeContainInterface
{
public:
	QV(00); QV(01); QV(02); QV(03); QV(04);
	QV(05); QV(06); QV(07); QV(08); QV(09);
	QV(10);
	virtual void acceptCreatedMemberRva00240F10(Object *obj);
};

class ExperienceTracker
{
public:
	__declspec(noinline) void setExperienceSink(ObjectID sink);
 // Authenticated by ExperienceTracker ctor and the reference setter.
 unsigned char prefix[0x18];ObjectID m_experienceSink;
};

class Overridable
{
public:
 virtual ~Overridable();
 const Overridable *getFinalOverride() const {if(next) return next->getFinalOverride(); return this;}
 Overridable *next;
};
class ThingTemplate : public Overridable {
public:
 // KindOf words begin at+C8; word3 bit12 is HORDE108.
 unsigned char pad08[0xCC]; unsigned kindFlagsD4;
};
template<class T> class OVERRIDE {
 const T *value;
public:
 const T *operator*() const {if(!value) return 0; return (T*)value->getFinalOverride();}
 operator const T*() const {return operator*();}
};

class Object
{
public:
	void setPosition(const Coord3D *pos);
	bool clearDisabled(DisabledType dt);

	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	void setProducer(const Object *producer);
	void setStatusBit(int bit, bool value);

	QV(00); QV(01); QV(02); QV(03); QV(04);
	QV(05); QV(06); QV(07); QV(08); QV(09);
	QV(10); QV(11); QV(12); QV(13); QV(14);
	QV(15); QV(16); QV(17); QV(18); QV(19);
	virtual void setTeam(Team *team);

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

	int getColorIndex() const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x370);
	}

	ContainModuleInterface *getContain() const
	{
		return *reinterpret_cast<ContainModuleInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x1FC);
	}

	ObjectID getId74() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const unsigned char *>(this) + 0x74);
	}

	ExperienceTracker *getExperienceTracker() const
	{
		return *reinterpret_cast<ExperienceTracker *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x210);
	}

	Team *getTeam() const
	{
		return *reinterpret_cast<Team *const *>(reinterpret_cast<const unsigned char *>(this) + 0x23C);
	}

	const ThingTemplate *getTemplate() const
 {return *reinterpret_cast<const OVERRIDE<ThingTemplate> *>(reinterpret_cast<const unsigned char *>(this)+4);}
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
	Real m_exitAngleOffset;
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
	virtual bool useSpawnRallyPoint() const;
	virtual void setRallyPoint(const Coord3D *);
	virtual const Coord3D *getRallyPoint() const;
	virtual bool getNaturalRallyPoint(Coord3D &rallyPoint, bool offset = true) const;
	virtual bool getExitPosition(Coord3D &, Real &) const;

	unsigned m_currentDelay;
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
	float m_creationClearDistance;
	unsigned m_currentBurstCount;
	int m_lastExitId;
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
	Coord3D createPoint;
	bool creationInAir = false;
	{
		Vector3 loc;
		loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z);
		transform->Transform_Vector(*transform, loc, &loc);

		if (TheTerrainLogic)
		{
			if (TheTerrainLogic->getGroundHeight(loc.X, loc.Y, 0) + 1.0f < loc.Z)
			{
				creationInAir = true;
				if (!md->m_allowAirborneCreationData)
					loc.Z = TheTerrainLogic
						? TheTerrainLogic->getGroundHeight(loc.X, loc.Y, 0)
						: 0.0f;
			}
		}

		createPoint.x = loc.X;
		createPoint.y = loc.Y;
		createPoint.z = loc.Z;
	}

	AIUpdateInterface *ai = produced->getAIUpdateInterface();
	if (ai && ai->isGiantBird())
		createPoint.z += 500.0f;

	reinterpret_cast<StructureCollapseRetailObject *>(produced)->setPosition(
		*reinterpret_cast<const StructureCollapsePosition *>(&createPoint), true);
	reinterpret_cast<Thing *>(produced)->setOrientation(
		creationObject->getOrientation() + md->m_exitAngleOffset);

	PhysicsBehavior *phys = produced->getPhysics();
	Coord3D startingForce;
	reinterpret_cast<const Thing *>(creationObject)->getUnitDirectionVector3D(startingForce);
	Real height = creationObject->bfmeGetNonnegativePreferredLocomotorHeight();
	if (creationInAir && phys && height > 0.01f)
	{
		startingForce.x *= height;
		startingForce.y *= height;
		startingForce.z *= height;
		phys->applyMotiveForce(&startingForce);
	}

	reinterpret_cast<GameLogicColorIndexView *>(TheGameLogic)->applyObjectColorIndex383930(produced, creationObject->getColorIndex());
	_TheAIParseDefinitionAI->pathfinder()->addObjectToPathfindMap(produced);

	Object *host = reinterpret_cast<GameLogic *>(TheGameLogic)->findObjectByID(m_lastExitId);
	if (host)
	{
		ContainModuleInterface *contain = host->getContain();
		if (contain)
		{
			HordeContainInterface *iface = reinterpret_cast<HordeContainInterface *>(contain->getHordeContainInterface());
			if (iface)
			{
				produced->setProducer(host);
				produced->getExperienceTracker()->setExperienceSink(host->getId74());
				iface->acceptCreatedMemberRva00240F10(produced);
				produced->setTeam(host->getTeam());
			}
		}
	}

	if (ai)
	{
		Coord3D tmp;
		getNaturalRallyPoint(tmp, true);
		_TheAIParseDefinitionAI->pathfinder()->snapPosition(produced, &tmp);
		std::vector<Coord3D> exitPath;
		exitPath.push_back(tmp);

		bool useRally;
		if (reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_HORDE))
			useRally = false;
		else
		{
			useRally = true;
			if (host)
				useRally = false;
		}
		if (reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_HORDE)
			&& reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_VEHICLE))
			useRally = true;

		if (m_rallyPointExists && useRally)
		{
			tmp = m_rallyPoint;
			if (!ai->isGiantBird())
			{
				if (_TheAIParseDefinitionAI->pathfinder()->adjustDestination(
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
			_TheAIParseDefinitionAI->pathfinder()->moveAlliesAwayFromDestination(produced, tmp);
		}
		else
		{
			ai->aiIdle(CMD_FROM_AI);
		}
	}

	if (produced->getTemplate()->kindFlagsD4 & 0x1000)
	{
		Coord3D tmp;
		getNaturalRallyPoint(tmp, true);
		_TheAIParseDefinitionAI->pathfinder()->snapPosition(produced, &tmp);
		if (!reinterpret_cast<Thing *>(produced)->isKindOf(KINDOF_VEHICLE))
			produced->setPosition(&tmp);
		m_lastExitId = produced->getId74();
		produced->setStatusBit(3, true);
		produced->setStatusBit(2, true);
	}

	m_currentDelay = md->m_exitDelayData;
	if (m_currentBurstCount)
		m_currentBurstCount--;
}

__declspec(noinline) void ExperienceTracker::setExperienceSink(ObjectID sink)
{
 m_experienceSink=sink;
}
