// cl: /DNDEBUG /MD /EHsc
// stlport
#include <bitset>
// BFME AIUpdateInterface::computeQuickPath, RVA 0x00274B60, 566 bytes.
//
// Identity: the matched AIUpdateInterface::requestPath (0x0027BD90) and
// AIFollowPathAsTeamState::computePath (0x001795F0) both call it through the
// ILT at 0x00029375, which symbols.csv already pins as computeQuickPath and
// which jumps here. The body is the Zero Hour computeQuickPath
// (AIUpdate.cpp) with destroyPath inlined, plus a BFME tail: the new path
// gets a second optimize pass along the unit's facing
// (Path::bfmeOptimizeDir, the same pass Pathfinder::buildActualPath runs),
// and one more AI virtual (slot 117) runs after the timestamp.
//
// Path::prependNode is defined here, visible and noinline (the lever that
// landed setPathFromWaypoint 0x00270B40): with an opaque declaration the load
// of the object's position y sinks below the store of pos.x (7 bytes at
// +0x160), because VC7.1 cannot see that &pos is copied rather than retained.
// The helper independently matches all 104 bytes at 0x0026E4D0. The ledger
// row at 0x002712D0 also carries this mangled name (a different body);
// landing needs that row re-homed first.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D( const Coord3D &c ) : x(c.x), y(c.y), z(c.z) {}
	Coord3D &operator=( const Coord3D &c ) { x = c.x; y = c.y; z = c.z; return *this; }

	Real x, y, z;
};

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

// BFME ordinals: bit 12 and bit 25 of ThingTemplate::m_kindof.
enum KindOfType { KINDOF_AIRCRAFT = 12, KINDOF_PROJECTILE = 25 };

enum AIDebugOptions { AI_DEBUG_NONE = 0, AI_DEBUG_PATHS = 1 };

typedef Int LocomotorSurfaceTypeMask;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride( void ) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;			// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if (!m_overridable)
			return 0;
		return (T*) m_overridable->getFinalOverride();
	}
	operator const T*( ) const { return operator->(); }

private:
	const T *m_overridable;
};

template <size_t NUMBITS> class BitFlags
{
public:
	Bool test( Int i ) const { return m_bits.test(i); }
private:
	_STL::bitset<NUMBITS> m_bits;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf( KindOfType t ) const { return m_kindof.test(t); }

private:
	char m_unmodelled_08[0xC8 - 0x08];
	BitFlags<128> m_kindof;				// +0xC8
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/LocomotorSet.h
class LocomotorTemplate : public Overridable
{
public:
	char m_unmodelled_08[0x10 - 0x08];
	LocomotorSurfaceTypeMask m_surfaces;	// +0x10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	LocomotorSurfaceTypeMask getLegalSurfaces() const { return m_template->m_surfaces; }

private:
	char m_unmodelled_00[0x04];
	OVERRIDE<LocomotorTemplate> m_template;	// +0x04
};

// 0x001BE010 (ILT 0x00021017): the object's AI current locomotor, null without
// an AI. Address-derived; the ledger row returns it as an int.
class Rva001BE010
{
public:
	Int get();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	void getUnitDirectionVector2D( Coord3D &dir ) const;	// 0x00132190

private:
	char m_unmodelled_00[0x04];
	OVERRIDE<ThingTemplate> m_template;		// +0x04
	char m_unmodelled_08[0x38 - 0x08];
	Coord3D m_cachedPos;					// +0x38
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	__forceinline Bool isKindOf( KindOfType t ) const { return getTemplate()->isKindOf(t); }
	Int getLayer() const;					// ILT 0x0003A391
	Locomotor *rva001BE010() { return (Locomotor *)((Rva001BE010 *)this)->get(); }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	PathNode( const Coord3D *pos, PathfindLayerEnum layer )
	{
		m_next = 0;
		m_prev = 0;
		m_nextOpti = 0;
		m_pos = *pos;
		m_layer = layer;
		m_canOptimize = false;
		m_costSoFar = 0x7FFFFFFF;
	}

	PathNode *getNext( void ) { return m_next; }
	PathNode *getNextOptimized( void ) const { return m_nextOpti; }
	const Coord3D *getPosition( void ) const { return &m_pos; }
	void setNextOptimized( PathNode *node );	// ILT 0x0002E5FA

private:
	PathNode *m_next;						// +0x00
	PathNode *m_prev;						// +0x04
	PathNode *m_nextOpti;					// +0x08
	Coord3D m_pos;							// +0x0C
	PathfindLayerEnum m_layer;				// +0x18
	Bool m_canOptimize;						// +0x1C
	Int m_costSoFar;						// +0x20

	friend class Path;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	Path();									// ILT 0x000335B4
	__declspec(noinline) void prependNode( const Coord3D *pos, PathfindLayerEnum layer );	// 0x0026E4D0
	void bfmeOptimizeDir( const Object *obj, const Coord3D *dir,
		LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );	// ILT 0x00049DEB
	PathNode *getFirstNode( void ) { return m_path; }
	PathNode *getLastNode( void ) { return m_pathTail; }

	void deleteInstance( void )
	{
		this->Path::~Path();
		::operator delete( this );
	}

protected:
	virtual ~Path();						// ILT 0x0000CA68

private:
	PathNode *m_path;						// +0x04
	PathNode *m_pathTail;					// +0x08
	Bool m_isOptimized;						// +0x0C
	char m_unmodelled_0D[0x24 - 0x0D];
};

// Visible so VC7.1 sees the coordinate is copied, not retained (the same lever
// as setPathFromWaypoint 0x00270B40); independently matches 0x0026E4D0.
void Path::prependNode( const Coord3D *pos, PathfindLayerEnum layer )
{
	PathNode *node = new PathNode( pos, layer );
	PathNode *head = m_path;
	node->m_nextOpti = head;
	node->m_next = head;
	if (head)
		head->m_prev = node;
	m_path = node;
	m_isOptimized = false;
	if (m_pathTail == 0)
		m_pathTail = node;
}

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// Pathfinder::getAircraftPath (0x003EDC50) is still a dump with no pinned
// name; the call is spelled through the ILT placeholder 0x000328A3.
extern void j_000328a3();

class Pathfinder
{
public:
	void setDebugPath( Path *debugpath );	// ILT 0x0002EA3C

	Path *getAircraftPath( const Object *obj, const Coord3D *to )
	{
		typedef Path *(Pathfinder::*Call)( const Object *, const Coord3D * );
		union { void (*address)(); Call member; } route = { j_000328a3 };
		return (this->*route.member)( obj, to );
	}
};

class AI
{
public:
	Pathfinder *pathfinder( void ) { return m_pathfinder; }

private:
	char m_unmodelled_00[0x0C];
	Pathfinder *m_pathfinder;				// +0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_unmodelled_000[0xA88];
	Int m_debugAI;							// +0xA88
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame( void ) const { return m_frame; }

private:
	char m_unmodelled_00[0x3C];
	UnsignedInt m_frame;					// +0x3C
};

extern AI *TheAI;
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BfmeVirtualSlots<117>
{
public:
	virtual void vslot117() = 0;			// vtable +0x1D4
	virtual void vslot118() = 0;
	virtual void vslot119() = 0;
	virtual void vslot120() = 0;
	virtual void vslot121() = 0;
	virtual void setLocomotorGoalNone() = 0;	// vtable +0x1E8

	Object *getObject( void ) const { return m_object; }
	Bool computeQuickPath( const Coord3D *destination );

	void destroyPath( void )
	{
		if (m_path)
			m_path->deleteInstance();
		m_path = 0;
		m_waitingForPath = false;
		m_isBlockedAndStuck = false;
		m_isAttackPath = false;
		setLocomotorGoalNone();
	}

private:
	char m_unmodelled_04[0x08 - 0x04];
	Object *m_object;						// +0x08
	char m_unmodelled_0C[0x140 - 0x0C];
	Path *m_path;							// +0x140
	char m_unmodelled_144[0x160 - 0x144];
	UnsignedInt m_pathTimestamp;			// +0x160
	char m_unmodelled_164[0x16C - 0x164];
	Int m_blockedFrames;					// +0x16C
	char m_unmodelled_170[0x31E - 0x170];
	Bool m_waitingForPath;					// +0x31E
	Bool m_isAttackPath;					// +0x31F
	char m_unmodelled_320[0x326 - 0x320];
	Bool m_isBlockedAndStuck;				// +0x326
};

Bool AIUpdateInterface::computeQuickPath( const Coord3D *destination )
{
	Object *obj = getObject();
	Locomotor *loco = obj->rva001BE010();

	// First, see if our path already goes to the destination.
	if (m_path) {
		PathNode *closeNode = 0;
		closeNode = m_path->getLastNode();
		if (closeNode && closeNode->getNextOptimized()==0) {
			Real dxSqr = destination->x - closeNode->getPosition()->x;
			dxSqr *= dxSqr;
			Real dySqr = destination->y - closeNode->getPosition()->y;
			dySqr *= dySqr;
			Real dzSqr = destination->z - closeNode->getPosition()->z;
			dzSqr *= dzSqr;
			if (dxSqr+dySqr+dzSqr<0.25f) {
				return true;
			}
		}
	}
	// destroy previous path
	destroyPath();
	if (obj->isKindOf(KINDOF_AIRCRAFT) && !obj->isKindOf(KINDOF_PROJECTILE)) {
		m_path = TheAI->pathfinder()->getAircraftPath(getObject(), destination);
	} else {
		m_path = new Path;
		m_path->prependNode( destination, LAYER_GROUND );
		Coord3D pos = *getObject()->getPosition();
		pos.z = destination->z;
		m_path->prependNode( &pos, (PathfindLayerEnum)getObject()->getLayer() );
		m_path->getFirstNode()->setNextOptimized(m_path->getFirstNode()->getNext());

		if (TheWritableGlobalData->m_debugAI==AI_DEBUG_PATHS)
		{
			TheAI->pathfinder()->setDebugPath(m_path);
		}
	}

	Coord3D dir;
	obj->getUnitDirectionVector2D(dir);
	m_path->bfmeOptimizeDir(obj, &dir, loco->getLegalSurfaces(), false);

	// timestamp when the path was created
	m_pathTimestamp = TheGameLogic->getFrame();
	vslot117();

	m_blockedFrames = 0;
	m_isBlockedAndStuck = false;
	return true;
}
