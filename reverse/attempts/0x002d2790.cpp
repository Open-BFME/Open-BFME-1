// ?d_002d2790@@YAXXZ
// partial score=0.87 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1

#include <vector>

#include "Lib/BaseType.h"
#include "vector3.h"
#include "matrix3d.h"

class Object;
class ThingTemplate;

enum ExitDoorType
{
	DOOR_1 = 0
};

template <Int N>
class Rva002D2790VirtualSlots : public Rva002D2790VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva002D2790VirtualSlots<0>
{
};

class Rva002D2790TerrainLogic : public Rva002D2790VirtualSlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y,
		Coord3D *normal = 0) const = 0;
};

class Rva002D2790Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
};

class Rva002D2790AI
{
public:
	Rva002D2790Pathfinder *pathfinder() const
	{
		return *(Rva002D2790Pathfinder * const *)((const char *)this + 0x0c);
	}
};

class Rva002D2790SupplyTruckAIInterface
	: public Rva002D2790VirtualSlots<11>
{
public:
	virtual void setForceWantingState(Bool force) = 0;
};

class Rva002D2790AIUpdateInterface
	: public Rva002D2790VirtualSlots<81>
{
public:
	virtual Rva002D2790SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;
};

class Rva002D2790Object
{
public:
	const Matrix3D *getTransformMatrix() const
	{
		return (const Matrix3D *)((const char *)this + 8);
	}

	Real getOrientation() const
	{
		return *(const Real *)((const char *)this + 0x44);
	}

	Rva002D2790AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(Rva002D2790AIUpdateInterface * const *)
			((const char *)this + 0x204);
	}
};

class Rva002D2790SupplyCenterProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	Coord3D m_unitCreatePoint;
	Coord3D m_naturalRallyPoint;
};

class Rva002D2790SupplyCenterProductionExitUpdate
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *what,
		Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;

	Object *getObject() const
	{
		return *(Object * const *)((const char *)this - 0x18);
	}

	const Rva002D2790SupplyCenterProductionExitUpdateModuleData *
	getSupplyCenterProductionExitUpdateModuleData() const
	{
		return *(const Rva002D2790SupplyCenterProductionExitUpdateModuleData * const *)
			((const char *)this - 0x1c);
	}

private:
	Coord3D m_rallyPoint;
	Bool m_rallyPointExists;
};

class Rva002D2790AICommandInterface
{
};

extern void j_0000b81b();
extern void j_00010a05();
extern void j_00035f8f();
extern void j_0003a1a7();
extern void j_000399a5();
extern void j_00070cc();

typedef void (Rva002D2790Object::*SetPositionCall)(const Coord3D *position);
typedef void (Rva002D2790Object::*SetOrientationCall)(Real angle);
typedef void (Rva002D2790Pathfinder::*AddObjectCall)(Object *object);
typedef void (Rva002D2790AICommandInterface::*FollowExitProductionPathCall)(
	const std::vector<Coord3D> *path, Object *creationObject, Int commandSource);

union SetPositionCallBits
{
	void (*raw)();
	SetPositionCall member;
};

union SetOrientationCallBits
{
	void (*raw)();
	SetOrientationCall member;
};

union AddObjectCallBits
{
	void (*raw)();
	AddObjectCall member;
};

union FollowExitProductionPathCallBits
{
	void (*raw)();
	FollowExitProductionPathCall member;
};

static __forceinline void bfmeSetPosition(Object *object,
	const Coord3D *position)
{
	SetPositionCallBits call;
	call.raw = j_0003a1a7;
	(((Rva002D2790Object *)object)->*call.member)(position);
}

static __forceinline void bfmeSetOrientation(Object *object, Real angle)
{
	SetOrientationCallBits call;
	call.raw = j_000399a5;
	(((Rva002D2790Object *)object)->*call.member)(angle);
}

static __forceinline void bfmeAddObject(Rva002D2790Pathfinder *pathfinder,
	Object *object)
{
	AddObjectCallBits call;
	call.raw = j_0000b81b;
	(pathfinder->*call.member)(object);
}

static __forceinline void bfmeFollowExitProductionPath(
	Rva002D2790AIUpdateInterface *ai, const std::vector<Coord3D> *path,
	Object *creationObject)
{
	FollowExitProductionPathCallBits call;
	call.raw = j_00010a05;
	(((Rva002D2790AICommandInterface *)((char *)ai + 0x20))->*call.member)(
		path, creationObject, 2);
}

extern Rva002D2790TerrainLogic *TheTerrainLogic;
extern Rva002D2790AI *TheAI;
extern const Real BFME_DEFAULT_GROUND_HEIGHT;

// ?exitObjectViaDoor@SupplyCenterProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
void Rva002D2790SupplyCenterProductionExitUpdate::exitObjectViaDoor(
	Object *newObj, ExitDoorType exitDoor)
{
	Object *creationObject = getObject();
	if (creationObject)
	{
		const Rva002D2790SupplyCenterProductionExitUpdateModuleData *md =
			getSupplyCenterProductionExitUpdateModuleData();

		Real exitAngle = ((Rva002D2790Object *)creationObject)->getOrientation();
		const Matrix3D *transform =
			((Rva002D2790Object *)creationObject)->getTransformMatrix();
		Vector3 loc;
		Coord3D createPoint;
		loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y,
			md->m_unitCreatePoint.z);
		transform->Transform_Vector(*transform, loc, &loc);
		loc.Z = TheTerrainLogic ?
			TheTerrainLogic->getGroundHeight(loc.X, loc.Y)
			: BFME_DEFAULT_GROUND_HEIGHT;

		createPoint.x = loc.X;
		createPoint.y = loc.Y;
		createPoint.z = loc.Z;

		bfmeSetPosition(newObj, &createPoint);
		bfmeSetOrientation(newObj, exitAngle);
		bfmeAddObject(TheAI->pathfinder(), newObj);

		Vector3 p;
		p.X = md->m_naturalRallyPoint.x;
		p.Y = md->m_naturalRallyPoint.y;
		p.Z = md->m_naturalRallyPoint.z;
		transform->Transform_Vector(*transform, p, &p);

		std::vector<Coord3D> exitPath;
		Coord3D tmp; tmp.x = p.X; tmp.y = p.Y; tmp.z = p.Z;
		exitPath.push_back(tmp);

		if (m_rallyPointExists)
			exitPath.push_back(m_rallyPoint);

		Rva002D2790AIUpdateInterface *ai =
			((Rva002D2790Object *)newObj)->getAIUpdateInterface();
		if (ai)
		{
			bfmeFollowExitProductionPath(ai, &exitPath, creationObject);
			Rva002D2790SupplyTruckAIInterface *supplyTruckAI =
				ai->getSupplyTruckAIInterface();
			if (supplyTruckAI)
				supplyTruckAI->setForceWantingState(true);
		}
	}
}
