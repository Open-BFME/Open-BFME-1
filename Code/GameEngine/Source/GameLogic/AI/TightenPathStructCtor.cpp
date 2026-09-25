// cl: /DNDEBUG /MD
//
// Retail 0x003E1720: the constructor of the tightenPath callback payload.
//
// ZH AIPathfind.cpp:8407 declares TightenPathStruct as a plain aggregate that
// Pathfinder::tightenPath (AIPathfind.cpp:8438) fills field by field.  BFME
// turned it into a class whose constructor takes the pathfinder, the object,
// the locomotor set, the starting layer and the destination, then asks the
// pathfinder for the object's radius and centre flag through
// Pathfinder::bfmeQuery -- the out-of-line replacement for ZH's inlined
// getRadiusAndCenter(obj, info.radius, info.centerInCell). foundDestination is cleared
// after that query and the found-destination Coord3D starts zeroed.
//
// Layout recovered from the stores: pathfinder 0x00, obj 0x04, locomotorSet
// 0x08, radius 0x0C, center 0x10, layer 0x14, foundDest 0x18, the requested
// destination 0x1C and the found destination 0x28.
//
// Codegen note: the zeroing of adjustedDestination has to go through Coord3D::zero().
// Writing the three floats directly lets MSVC 7.1 forward the just-stored
// pathfinder and obj registers into the bfmeQuery argument pushes; storing
// through Coord3D's own this pointer blocks that forwarding, so retail's
// reload of [esi+4] and [esi] before the call is reproduced.
//
// No /EHsc: retail registers no handler for the body.

class Object;
class LocomotorSet;
class Pathfinder;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;

	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

enum PathfindLayerEnum { LAYER_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmeQuery( Object *object, int *radius, int *centerInCell );
};

class TightenPathStruct
{
public:
	TightenPathStruct( Pathfinder *pathfinder, Object *object,
		const LocomotorSet *locomotorSet, PathfindLayerEnum layer,
		const Coord3D *destinationPosition );

	Pathfinder *pathfinder;				// 0x00
	Object *object;						// 0x04
	const LocomotorSet *locomotorSet;		// 0x08
	int radius;						// 0x0C
	int centerInCell;					// 0x10
	PathfindLayerEnum layer;				// 0x14
	bool foundDestination;				// 0x18
	Coord3D requestedDestination;			// 0x1C
	Coord3D adjustedDestination;			// 0x28
};

TightenPathStruct::TightenPathStruct( Pathfinder *pathfinder, Object *object,
	const LocomotorSet *locomotorSet, PathfindLayerEnum layer,
	const Coord3D *destinationPosition )
{
	this->pathfinder = pathfinder;
	this->object = object;
	this->locomotorSet = locomotorSet;
	this->layer = layer;

	this->requestedDestination.x = destinationPosition->x;
	this->requestedDestination.y = destinationPosition->y;
	this->requestedDestination.z = destinationPosition->z;

	this->adjustedDestination.zero();

	this->pathfinder->bfmeQuery(this->object, &this->radius, &this->centerInCell);

	this->foundDestination = false;
}
