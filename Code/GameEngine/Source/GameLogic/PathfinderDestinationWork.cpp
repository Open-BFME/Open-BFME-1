// cl: /DNDEBUG /MD /EHsc
// readable body of ?adjustTargetDestination@Pathfinder@@QAE_NPBVObject@@0PBUCoord3D@@PBVWeapon@@PAU3@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?moveAlliesAwayFromDestination@Pathfinder@@QAEXPAVObject@@ABUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
//
// Open-BFME: the two Pathfinder bodies that build a compact work record and
// hand it to a separate scan.
//
//   ?adjustTargetDestination@        0x003F2DB0, 207 bytes
//   ?moveAlliesAwayFromDestination@  0x003F2EC0, 127 bytes
//
// They are consecutive in the retail image and neither does its own searching.
// adjustTargetDestination fills an eight-field record and hands it to the radial
// scan at 0x003F18E0; moveAlliesAwayFromDestination fills a two-field record and
// hands it to the cell-space line walk at 0x003ED9F0. Both convert a world
// position to a cell first, and both take the object rather than only the
// destination -- which is BFME's change from Zero Hour, where the destination
// alone was enough.
//
// Retail pins the object layout the same way in both: the position at
// object+0x38 and the AI at object+0x204, agreeing with the conversions in
// AIUpdateInterfaceCommandButton.cpp and PathfinderAttackViewForwarders.cpp.
//
// The two files disagreed about worldToCell, and the disagreement was in the
// mangled name rather than the body. moveAlliesAwayFromDestination declared it
// PRIVATE returning void; adjustTargetDestination declared it PUBLIC returning
// bool, because it branches on the answer. The ledger pins both spellings to the
// same ILT 0x000171E8, so they are one function seen from two angles, and the
// public one is kept here -- it is the only one of the two that can say what the
// return value is.
//
// moveAlliesAwayFromDestination's other callee stays private, because that one
// really is private: `?iterateCellsAlongLine@Pathfinder@@AAEXPBUICoord2D@@0
// W4PathfindLayerEnum@@PAUMADStruct@@@Z` at ILT 0x00014092. It also keeps Zero
// Hour's name and not Zero Hour's signature: retail converts both endpoints to
// cells before the call and passes no callback, so the callback ZH hands it is
// simply not a parameter here.

typedef int Int;
typedef unsigned char Bool;

class Object;
class Weapon;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum { LAYER_GROUND = 1 };

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

// The radial scan's record: eight fields, filled here and read at 0x003F18E0.
struct AdjustTargetInfo;

// The line walk's record: two fields. Retail never stores a back-pointer to the
// pathfinder in it, where Zero Hour's third field is exactly that.
struct MADStruct
{
	Object *obj;										///< retail this+0x00
	Int ignoreID;										///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *world, ICoord2D *cell);	///< ILT thunk at 0x000171E8

	void bfmeQuery(Object *obj, Int *radius, Bool *center);
	bool iterateCircular2(ICoord2D *cell, Int limit, void *info);

	bool adjustTargetDestination(const Object *obj, const Object *target,
		const Coord3D *targetPos, const Weapon *weapon, Coord3D *dest);
	void moveAlliesAwayFromDestination(Object *obj, const Coord3D &destination);

private:
	void iterateCellsAlongLine(const ICoord2D *from, const ICoord2D *to,
			PathfindLayerEnum layer, MADStruct *info);		///< ILT thunk at 0x00014092
};

struct AdjustTargetInfo
{
	Pathfinder *m_pathfinder;
	Object *m_obj;
	Bool m_center;
	Int m_radius;
	Coord3D *m_dest;
	Object *m_target;
	const Coord3D *m_targetPos;
	const Weapon *m_weapon;
};

// ?adjustTargetDestination@Pathfinder@@QAE_NPBVObject@@0PBUCoord3D@@PBVWeapon@@PAU3@@Z
bool Pathfinder::adjustTargetDestination(const Object *obj, const Object *target,
	const Coord3D *targetPos, const Weapon *weapon, Coord3D *dest)
{
	ICoord2D cell;
	Bool center;
	Coord3D adjustDest;

	bfmeQuery((Object *)obj, &cell.x, &center);
	adjustDest.x = dest->x;
	adjustDest.y = dest->y;
	adjustDest.z = dest->z;
	if (!center)
	{
		adjustDest.x += 5.0f;
		adjustDest.y += 5.0f;
	}
	if (worldToCell(&adjustDest, &cell))
		return false;

	AdjustTargetInfo info;
	info.m_pathfinder = this;
	info.m_obj = (Object *)obj;
	info.m_dest = dest;
	info.m_target = (Object *)target;
	info.m_targetPos = targetPos;
	info.m_weapon = weapon;
	bfmeQuery(info.m_obj, &info.m_radius, &info.m_center);
	return iterateCircular2(&cell, 0x190, &info);
}

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
