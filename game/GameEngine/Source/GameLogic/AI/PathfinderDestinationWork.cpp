// cl: /DNDEBUG /MD /EHsc
// readable body of ?adjustTargetDestination@Pathfinder@@QAE_NPBVObject@@0PBUCoord3D@@PBVWeapon@@PAU3@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?moveAlliesAwayFromDestination@Pathfinder@@QAEXPAVObject@@ABUCoord3D@@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum { LAYER_GROUND = 1 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID(void);						///< ILT thunk at 0x0001A36B
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *position);	///< ILT thunk at 0x0001C675
};

extern TerrainLogic *TheTerrainLogic;					///< retail [0x012EF4CC]

// The radial scan's record: eight fields, filled here and read at 0x003F18E0.
struct AdjustTargetInfo;

// The line walk's record: two fields. Retail never stores a back-pointer to the
// pathfinder in it, where Zero Hour's third field is exactly that.
struct MADStruct
{
	Object *object;										///< retail this+0x00
	Int ignoredObstacleID;								///< retail this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);	///< ILT thunk at 0x000171E8

	void bfmeQuery(Object *object, Int *radius, Bool *centerInCell);
	bool iterateCircular2(ICoord2D *cell, Int limit, void *info);

	bool adjustTargetDestination(const Object *object, const Object *target,
		const Coord3D *targetPosition, const Weapon *weapon, Coord3D *destination);
	void moveAlliesAwayFromDestination(Object *object, const Coord3D &destination);

protected:
	friend struct AdjustTargetInfo;
	bool checkForTarget(const Object *object, Int cellX, Int cellY,
		const Weapon *weapon, const Object *target,
		const Coord3D *targetPosition, Int radius, bool centerInCell, Coord3D *destination);

private:
	void iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell,
			PathfindLayerEnum layer, MADStruct *walkInfo);		///< ILT thunk at 0x00014092
};

struct AdjustTargetInfo
{
	Pathfinder *m_pathfinder;
	Object *m_object;
	bool m_centerInCell;
	Int m_radius;
	Coord3D *m_destination;
	Object *m_target;
	const Coord3D *m_targetPosition;
	const Weapon *m_weapon;
	__forceinline bool check(Int x, Int y) const;
};

// ?adjustTargetDestination@Pathfinder@@QAE_NPBVObject@@0PBUCoord3D@@PBVWeapon@@PAU3@@Z
bool Pathfinder::adjustTargetDestination(const Object *object, const Object *target,
	const Coord3D *targetPosition, const Weapon *weapon, Coord3D *destination)
{
	ICoord2D cellIndex;
	Bool center;
	Coord3D adjustDest;

	bfmeQuery((Object *)object, &cellIndex.x, &center);
	adjustDest.x = destination->x;
	adjustDest.y = destination->y;
	adjustDest.z = destination->z;
	if (!center)
	{
		adjustDest.x += 5.0f;
		adjustDest.y += 5.0f;
	}
	if (worldToCell(&adjustDest, &cellIndex))
		return false;

	AdjustTargetInfo info;
	info.m_pathfinder = this;
	info.m_object = (Object *)object;
	info.m_destination = destination;
	info.m_target = (Object *)target;
	info.m_targetPosition = targetPosition;
	info.m_weapon = weapon;
	bfmeQuery(info.m_object, &info.m_radius,
		reinterpret_cast<Bool *>(&info.m_centerInCell));
	return iterateCircular2(&cellIndex, 0x190, &info);
}

// ?moveAlliesAwayFromDestination@Pathfinder@@QAEXPAVObject@@ABUCoord3D@@@Z
void Pathfinder::moveAlliesAwayFromDestination(Object *object,const Coord3D& destination)
{
	PathfindLayerEnum layer = (PathfindLayerEnum)object->getLayer();
	if (layer==LAYER_GROUND) {
		layer = TheTerrainLogic->getLayerForDestination(object, &destination);
	}

	MADStruct info;
	info.object = object;
	info.ignoredObstacleID = object->getAI()->getIgnoredObstacleID();

	ICoord2D startCell, destinationCell;
	worldToCell(object->getPosition(), &startCell);
	worldToCell(&destination, &destinationCell);
	iterateCellsAlongLine(&startCell, &destinationCell, layer, &info);

}
