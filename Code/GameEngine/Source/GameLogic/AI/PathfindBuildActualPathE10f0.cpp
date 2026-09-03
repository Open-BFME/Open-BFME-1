// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003E10F0: Pathfinder::buildActualPath.
//
class Object;
class PathfindCell;

typedef int Int;
typedef bool Bool;
typedef int LocomotorSurfaceTypeMask;

struct Coord3D { float x, y, z; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	Path();
	void optimize( const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );
	void bfmeOptimizeDir( const Object *obj, const Coord3D *dir,
		LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );

	Int m_pad[9];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Path *buildActualPath( const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces,
		const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked );

	void prependCells( Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D( void ) const;
};

Path *Pathfinder::buildActualPath( const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces,
	const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked )
{
	Path *path = new Path;

	prependCells( path, fromPos, goalCell, center );

	path->optimize( obj, acceptableSurfaces, blocked );

	Coord3D dir = *((const Thing *)obj)->getUnitDirectionVector2D();

	path->bfmeOptimizeDir( obj, &dir, acceptableSurfaces, blocked );

	return path;
}
