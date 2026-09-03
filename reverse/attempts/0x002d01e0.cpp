// ?exitObjectViaDoor@DefaultProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.88 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /GX /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
// Isolated TU for DefaultProductionExitUpdate::exitObjectViaDoor.
// Retail 0x002D01E0 is 534B (gen-dump / full EH tail), not the 494B drift cut.
// Wall: loc (Vector3) does not share the std::vector<Coord3D> slot, so
// sub esp,0x34 vs retail 0x28. Transform_Vector alias tmp already overlaps
// createPoint. Merging loc into createPoint gets 0x28+EH but loses Z-row DCE
// (546B). Placement overlay of loc/vector gets 0x28 but drops EH (515B).
// Do not edit UpdateModule.h / InGameUI.h.

#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "matrix3d.h"
#include <vector>

typedef float Real;
typedef int Int;
typedef int Bool;

enum ExitDoorType { DOOR_1 = 0 };
enum PathfindLayerEnum { LAYER_GROUND = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class LocomotorSet;

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	bool adjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dest, const Coord3D *pathDest);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	unsigned char pad[0x0C];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Bool clip, Bool useBuildings);
};

extern TerrainLogic *TheTerrainLogic;

class AICommandInterface
{
public:
	void aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *source, CommandSourceType cmd);
};

#define DPEU_V(n) virtual void slot_##n()
#define DPEU_V10(p) \
	DPEU_V(p##0); DPEU_V(p##1); DPEU_V(p##2); DPEU_V(p##3); DPEU_V(p##4); \
	DPEU_V(p##5); DPEU_V(p##6); DPEU_V(p##7); DPEU_V(p##8); DPEU_V(p##9)
class AIUpdateInterface
{
public:
	DPEU_V10(00); DPEU_V10(01); DPEU_V10(02); DPEU_V10(03); DPEU_V10(04);
	DPEU_V10(05); DPEU_V10(06); DPEU_V10(07); DPEU_V10(08); DPEU_V10(09);
	DPEU_V10(10); DPEU_V10(11);
	DPEU_V(120); DPEU_V(121); DPEU_V(122);
	virtual Bool isDoingGroundMovement() const;

	const LocomotorSet &getLocomotorSet() const
	{
		return *reinterpret_cast<const LocomotorSet *>(reinterpret_cast<const unsigned char *>(this) + 0x1A8);
	}

	void aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *source, CommandSourceType cmd)
	{
		reinterpret_cast<AICommandInterface *>(reinterpret_cast<unsigned char *>(this) + 0x20)
			->aiFollowExitProductionPath(path, source, cmd);
	}
};

class Thing
{
public:
	void setOrientation(Real angle);
};

class Object : public Thing
{
public:
	Int getLayer() const;
	void setPosition(const Coord3D *pos);
	void setLayer(PathfindLayerEnum layer);

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
		return *reinterpret_cast<AIUpdateInterface *const *>(reinterpret_cast<const unsigned char *>(this) + 0x204);
	}
};

class Thing;
class ModuleData;

class DefaultProductionExitUpdateModuleData
{
public:
	unsigned char pad[8];
	Coord3D m_unitCreatePoint;
};

class DPEU_DeepBase
{
public:
	virtual ~DPEU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class DPEU_Iface1 { public: virtual void slot(); };
class DPEU_Iface2 { public: virtual void slot(); };

class UpdateModule : public DPEU_DeepBase, public DPEU_Iface1, public DPEU_Iface2
{
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit(const void *, Object *) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
	virtual void exitObjectByBudding(Object *, Object *) = 0;
	virtual void unreserveDoorForExit(ExitDoorType) = 0;
	virtual void exitObjectInAHurry(Object *) {}
	virtual void setRallyPoint(const Coord3D *) = 0;
	virtual const Coord3D *getRallyPoint() const = 0;
	virtual Bool useSpawnRallyPoint() const { return 0; }
	virtual Bool getNaturalRallyPoint(Coord3D &rallyPoint, Bool offset = 1) const = 0;
	virtual Bool getExitPosition(Coord3D &) const = 0;
};

class DefaultProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
	virtual Bool isExitBusy() const { return 0; }
	virtual ExitDoorType reserveDoorForExit(const void *, Object *) { return DOOR_1; }
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);
	virtual void exitObjectByBudding(Object *, Object *) {}
	virtual void unreserveDoorForExit(ExitDoorType) {}
	virtual void setRallyPoint(const Coord3D *) {}
	virtual const Coord3D *getRallyPoint() const { return 0; }
	virtual Bool getNaturalRallyPoint(Coord3D &rallyPoint, Bool offset = 1) const;
	virtual Bool getExitPosition(Coord3D &) const { return 0; }

	const DefaultProductionExitUpdateModuleData *getDefaultProductionExitUpdateModuleData() const
	{
		return reinterpret_cast<const DefaultProductionExitUpdateModuleData *>(getModuleData());
	}

private:
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
};

// ?exitObjectViaDoor@DefaultProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
void DefaultProductionExitUpdate::exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor)
{
	(void)exitDoor;

	Object *creationObject = getObject();
	if (creationObject)
	{
		const DefaultProductionExitUpdateModuleData *md = getDefaultProductionExitUpdateModuleData();

		Real exitAngle = creationObject->getOrientation();
		const Matrix3D *transform = creationObject->getTransformMatrix();
		Vector3 loc;
		Coord3D createPoint;

		loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z);
		transform->Transform_Vector(*transform, loc, &loc);

		loc.Z = TheTerrainLogic ? TheTerrainLogic->getLayerHeight(
			loc.X, loc.Y, (PathfindLayerEnum)creationObject->getLayer(), 0, 1) : 0.0f;

		createPoint.x = loc.X;
		createPoint.y = loc.Y;
		createPoint.z = loc.Z;

		newObj->setPosition(&createPoint);
		newObj->setOrientation(exitAngle);
		newObj->setLayer((PathfindLayerEnum)creationObject->getLayer());

		TheAI->pathfinder()->addObjectToPathfindMap(newObj);
		Coord3D tmp;
		getNaturalRallyPoint(tmp);
		std::vector<Coord3D> exitPath;
		exitPath.push_back(tmp);

		AIUpdateInterface *ai = newObj->getAIUpdateInterface();
		if (m_rallyPointExists)
		{
			tmp = m_rallyPoint;
			if (ai && ai->isDoingGroundMovement())
			{
				if (TheAI->pathfinder()->adjustDestination(newObj, ai->getLocomotorSet(), &tmp, 0))
					exitPath.push_back(tmp);
			}
		}
		if (ai)
		{
			ai->aiFollowExitProductionPath(&exitPath, creationObject, CMD_FROM_AI);
		}
	}
}
