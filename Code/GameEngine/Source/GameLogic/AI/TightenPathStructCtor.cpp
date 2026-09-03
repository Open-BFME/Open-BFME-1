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
// getRadiusAndCenter(obj, info.radius, info.center).  foundDest is cleared
// after that query and the found-destination Coord3D starts zeroed.
//
// Layout recovered from the stores: pathfinder 0x00, obj 0x04, locomotorSet
// 0x08, radius 0x0C, center 0x10, layer 0x14, foundDest 0x18, the requested
// destination 0x1C and the found destination 0x28.
//
// Codegen note: the zeroing of m_destPos has to go through Coord3D::zero().
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
	void bfmeQuery( Object *obj, int *radius, int *center );
};

class TightenPathStruct
{
public:
	TightenPathStruct( Pathfinder *pathfinder, Object *obj,
		const LocomotorSet *locomotorSet, PathfindLayerEnum layer,
		const Coord3D *to );

	Pathfinder *m_pathfinder;			// 0x00
	Object *m_obj;						// 0x04
	const LocomotorSet *m_locomotorSet;	// 0x08
	int m_radius;						// 0x0C
	int m_center;						// 0x10
	PathfindLayerEnum m_layer;			// 0x14
	bool m_foundDest;					// 0x18
	Coord3D m_to;						// 0x1C
	Coord3D m_destPos;					// 0x28
};

TightenPathStruct::TightenPathStruct( Pathfinder *pathfinder, Object *obj,
	const LocomotorSet *locomotorSet, PathfindLayerEnum layer,
	const Coord3D *to )
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_locomotorSet = locomotorSet;
	m_layer = layer;

	m_to.x = to->x;
	m_to.y = to->y;
	m_to.z = to->z;

	m_destPos.zero();

	m_pathfinder->bfmeQuery( m_obj, &m_radius, &m_center );

	m_foundDest = false;
}
