// ?exitObjectViaDoor@SupplyCenterProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Igame/Libraries/Include /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1

#include <vector>

#include "Lib/Coord3D.h"
typedef float Real;
typedef int Int;
typedef bool Bool;
#include "vector3.h"
#include "matrix3d.h"

class Object;
class ThingTemplate;

#include "../../../../../Include/Common/Enums/ExitDoorType.h"




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

class SupplyCenterProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	Coord3D m_unitCreatePoint;
	Coord3D m_naturalRallyPoint;
};

class SupplyCenterProductionExitUpdate
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

	const SupplyCenterProductionExitUpdateModuleData *
	getSupplyCenterProductionExitUpdateModuleData() const
	{
		return *(const SupplyCenterProductionExitUpdateModuleData * const *)
			((const char *)this - 0x1c);
	}

private:
	Coord3D m_rallyPoint;
	Bool m_rallyPointExists;
};

class Rva002D2790AICommandInterface
{
};

#define THING_TU_MEMBERS \
public: void setPosition(const Coord3D *position); \
public: void setOrientation(Real angle);
#include "../../../../Common/Thing/thing.h"
#undef THING_TU_MEMBERS
class Pathfinder
{
public:
    void addObjectToPathfindMap(Object *object);
};
#include "../../../command_source_type.h"
enum AICommandType { AICMD_FOLLOW_EXITPRODUCTION_PATH = 10 };
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

struct AICommandParms
{
    AICommandType m_cmd;
    CommandSourceType m_cmdSource;
    Coord3D m_pos;
    Object *m_obj;
    Object *m_otherObj;
    const Team *m_team;
    std::vector<Coord3D> m_coords;
    const Waypoint *m_waypoint;
    const PolygonTrigger *m_polygon;
    int m_intValue;
    char m_damage[0x5c];
    const CommandButton *m_commandButton;
    Path *m_path;
    AICommandParms(AICommandType commandType, CommandSourceType source);
};
class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *parms) = 0;
    void aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *creationObject, CommandSourceType source);
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
    ((Thing *)object)->setPosition(position);
}

static __forceinline void bfmeSetOrientation(Object *object, Real angle)
{
    ((Thing *)object)->setOrientation(angle);
}

static __forceinline void bfmeAddObject(Rva002D2790Pathfinder *pathfinder,
	Object *object)
{
    ((Pathfinder *)pathfinder)->addObjectToPathfindMap(object);
}

static __forceinline void bfmeFollowExitProductionPath(
	Rva002D2790AIUpdateInterface *ai, const std::vector<Coord3D> *path,
	Object *creationObject)
{
    ((AICommandInterface *)((char *)ai + 0x20))->aiFollowExitProductionPath(path, creationObject, CMD_FROM_AI);
}

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class AI;
extern AI *TheAI;
#define BFME_DEFAULT_GROUND_HEIGHT 0.0f

// ?aiFollowExitProductionPath@AICommandInterface@@QAEXPBV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@PAVObject@@W4CommandSourceType@@@Z
inline __declspec(noinline) void AICommandInterface::aiFollowExitProductionPath(const std::vector<Coord3D> *path, Object *creationObject, CommandSourceType source)
{
    AICommandParms parms(AICMD_FOLLOW_EXITPRODUCTION_PATH, source);
    parms.m_coords = *path;
    parms.m_obj = creationObject;
    aiDoCommand(&parms);
}

//-------------------------------------------------------------------------------------------------
// ?exitObjectViaDoor@SupplyCenterProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
void SupplyCenterProductionExitUpdate::exitObjectViaDoor(
	Object *newObj, ExitDoorType exitDoor)
{
	Object *creationObject = getObject();
	if (creationObject)
	{
		const SupplyCenterProductionExitUpdateModuleData *md =
			getSupplyCenterProductionExitUpdateModuleData();

		Real exitAngle = ((Rva002D2790Object *)creationObject)->getOrientation();
		const Matrix3D *transform =
			((Rva002D2790Object *)creationObject)->getTransformMatrix();
		Vector3 loc;
		Coord3D createPoint;
		//
		// calculate the position to create the object at, we take the coord specified
		// in INI which is in model space, rotate it to match the building angle
		// and translate for building location via a transform call
		//
		loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y,
			md->m_unitCreatePoint.z);
		transform->Transform_Vector(*transform, loc, &loc);
		// make sure the point is on the terrain
		loc.Z = TheTerrainLogic ?
			((Rva002D2790TerrainLogic *)TheTerrainLogic)->getGroundHeight(loc.X, loc.Y)
			: BFME_DEFAULT_GROUND_HEIGHT;

		// we need it in Coord3D form
		createPoint.x = loc.X;
		createPoint.y = loc.Y;
		createPoint.z = loc.Z;

		bfmeSetPosition(newObj, &createPoint);
		bfmeSetOrientation(newObj, exitAngle);
		/** @todo This really should be automatically wrapped up in an actication sequence
		for objects in general */
		// tell the AI about it
		bfmeAddObject(((Rva002D2790AI *)TheAI)->pathfinder(), newObj);

		Vector3 p;
		//
		// get the natural rally point from the INI definition, this coord is in model space relative
		// to the model (0,0,0)
		//
		p.X = md->m_naturalRallyPoint.x;
		p.Y = md->m_naturalRallyPoint.y;
		p.Z = md->m_naturalRallyPoint.z;
		// transform the point into world space
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
			// Here is the special bit for this exit style, force wanting on SupplyTruck types
			Rva002D2790SupplyTruckAIInterface *supplyTruckAI =
				ai->getSupplyTruckAIInterface();
			if (supplyTruckAI)
				supplyTruckAI->setForceWantingState(true);
		}
	}
}
