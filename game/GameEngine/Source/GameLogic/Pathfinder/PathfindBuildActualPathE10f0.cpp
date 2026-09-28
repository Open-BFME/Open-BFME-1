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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	Path();
	void optimize( const Object *object, LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );
	void bfmeOptimizeDir( const Object *object, const Coord3D *unitDirection,
		LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );

	Int m_pad[9];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Path *buildActualPath( const Object *object, LocomotorSurfaceTypeMask acceptableSurfaces,
		const Coord3D *startPosition, PathfindCell *goalCell, Bool centerInCell, Bool blocked );

	void prependCells( Path *path, const Coord3D *startPosition, PathfindCell *goalCell, Bool centerInCell );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D( void ) const;
};

Path *Pathfinder::buildActualPath( const Object *object, LocomotorSurfaceTypeMask acceptableSurfaces,
	const Coord3D *startPosition, PathfindCell *goalCell, Bool centerInCell, Bool blocked )
{
	Path *path = new Path;

	prependCells( path, startPosition, goalCell, centerInCell );

	path->optimize( object, acceptableSurfaces, blocked );

	Coord3D dir = *((const Thing *)object)->getUnitDirectionVector2D();

	path->bfmeOptimizeDir( object, &dir, acceptableSurfaces, blocked );

	return path;
}
