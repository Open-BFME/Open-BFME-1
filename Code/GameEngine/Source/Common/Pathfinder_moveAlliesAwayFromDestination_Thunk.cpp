// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?moveAlliesAwayFromDestination@Pathfinder@@QAEXPAVObject@@ABUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// Lift the Pathfinder::moveAlliesAwayFromDestination naked dump to clean C++.
//
// Zero Hour's AIPathfind.cpp body with three BFME changes, two of which the
// already-pinned getLayerForDestination confirms outright: it takes the object
// as well as the destination here, where ZH passes only the destination.
//
// The line walk is the bigger change. ZH hands iterateCellsAlongLine two world
// positions and a callback; retail converts both positions to integer cell
// coordinates first -- through a helper that scales by a constant and rounds --
// and then passes the two cell pairs, the layer and the user data, with no
// callback among them. The name is kept because the role is ZH's, but the
// signature is not; the callback ZH passes is simply not a parameter.
//
// The third change is the user data: retail writes only the object and the
// ignored obstacle id, never a back-pointer to the pathfinder, so the record is
// two fields rather than ZH's three.
//
// Retail pins the layout: the AI pointer is at object+0x204 and the position at
// object+0x38, both agreeing with earlier conversions, and the ignored obstacle
// id is a plain read of ai+0x164.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum { LAYER_GROUND = 1 };

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID(void);						///< ILT thunk at 0x0001A36B
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int getLayer(void) const;							///< ILT thunk at 0x0003A391

	AIUpdateInterface *getAI(void) { return m_ai; }
	const Coord3D *getPosition(void) const { return &m_position; }

private:
	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_position;									///< retail this+0x38
	unsigned char m_unreconstructed_44[0x204 - 0x44];
	AIUpdateInterface *m_ai;							///< retail this+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *destination);	///< ILT thunk at 0x0001C675
};

extern TerrainLogic *TheTerrainLogic;					///< retail [0x012EF4CC]

// Two fields: retail never stores a back-pointer to the pathfinder.
struct MADStruct
{
	Object *obj;										///< retail this+0x00
	Int ignoreID;										///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void moveAlliesAwayFromDestination(Object *obj, const Coord3D &destination);

private:
	void worldToCell(const Coord3D *world, ICoord2D *cell);	///< ILT thunk at 0x000171E8
	void iterateCellsAlongLine(const ICoord2D *from, const ICoord2D *to,
			PathfindLayerEnum layer, MADStruct *info);		///< ILT thunk at 0x00014092
};

// ?moveAlliesAwayFromDestination@Pathfinder@@QAEXPAVObject@@ABUCoord3D@@@Z
void Pathfinder::moveAlliesAwayFromDestination(Object *obj,const Coord3D& destination)
{
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	if (layer==LAYER_GROUND) {
		layer = TheTerrainLogic->getLayerForDestination(obj, &destination);
	}

	MADStruct info;
	info.obj = obj;
	info.ignoreID = obj->getAI()->getIgnoredObstacleID();

	ICoord2D from, to;
	worldToCell(obj->getPosition(), &from);
	worldToCell(&destination, &to);
	iterateCellsAlongLine(&from, &to, layer, &info);

}
