// cl: /DNDEBUG /MD /EHsc
// readable body of ?buildTiledLocations@BuildAssistant@@UAEPAUTileBuildInfo@1@PBVThingTemplate@@MPBVCoord3D@@1MHPAVObject@@@Z: game/GameEngine/Source/Common/System/BuildAssistant.cpp
// Evidence: targets/game/reverse/identity_evidence/000fc010-normalize-visibility.md
#include <new>
#include <math.h>

#include "../../../Include/Common/ScalarTypes.h"




#define NULL 0
#define DEBUG_ASSERTCRASH(condition, message) ((void)0)

#include "../../../../Libraries/Source/WWVegas/WWMath/coord3d.h"
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &that)
{
    struct Raw { unsigned int x, y, z; };
    *(Raw *)this = *(const Raw *)&that;
    return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &that)
{
    *(Coord3DBase *)this = that;
    return *this;
}
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
__declspec(noinline) inline void Coord3D::normalize()
{
    float len = (float)sqrt(x * x + y * y + z * z);
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

class ThingTemplate;
class Object;
class Player;

enum LegalBuildCode
{
	LBC_OK = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// BFME's getGroundHeight occupies slot +0x18 (see iterateFootprint, 0x000FC780).
class TerrainLogic
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void slot3(); virtual void slot4(); virtual void slot5();
	virtual Real getGroundHeight( Real x, Real y, Coord3D *normal = NULL ) const;
};
extern TerrainLogic *TheTerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
public:
	struct TileBuildInfo
	{
		Int tilesUsed;
		Coord3D *positions;
	};

	enum LocalLegalToBuildOptions
	{
		TERRAIN_RESTRICTIONS	= 0x00000001,
		CLEAR_PATH						= 0x00000002,
		NO_OBJECT_OVERLAP			= 0x00000004,
		USE_QUICK_PATHFIND		= 0x00000008,
		SHROUD_REVEALED				= 0x00000010
	};

	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void slot3(); virtual void slot4(); virtual void slot5();
	virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void slot9();
	virtual LegalBuildCode isLocationLegalToBuild( const Coord3D *worldPos,
																								 const ThingTemplate *build,
																								 Real angle,
																								 UnsignedInt options,
																								 Object *builderObject,
																								 Player *player );
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual TileBuildInfo *buildTiledLocations( const ThingTemplate *thingBeingTiled,
																							Real angle,
																							const Coord3D *start,
																							const Coord3D *end,
																							Real tilingSize,
																							Int maxTiles,
																							Object *builderObject );

private:
	UnsignedInt m_unmodelled04;
	Coord3D *m_buildPositions;
	Int m_buildPositionSize;
};

//-------------------------------------------------------------------------------------------------
/** Tiling wall object helper function, we can use this to "tile" walls when building.
	* This function will fill out the ARRAY world positions named 'positions' starting
	* at the 'start' point in the world and going to the 'end' point in the world.  No
	* more than 'maxTiles' will be considered and if the position of any one of
	* the objects in the chain is illegal the chain stops there.  The number of objects
	* actually used for the tiling is returned along with a pointer to the array
	* of positions in the tile build info.
	*
	* REQUIRES: Note that the array at 'postions' must be large enough to hold 'maxTiles'
	* entries of positions 
	*/
//-------------------------------------------------------------------------------------------------
// ?buildTiledLocations@BuildAssistant@@UAEPAUTileBuildInfo@1@PBVThingTemplate@@MPBVCoord3D@@1MHPAVObject@@@Z
BuildAssistant::TileBuildInfo *BuildAssistant::buildTiledLocations( const ThingTemplate *thingBeingTiled,
																																		Real angle,
																																		const Coord3D *start,
																																		const Coord3D *end,
																																		Real tilingSize,
																																		Int maxTiles,
																																		Object *builderObject )
{

	// sanity
	if( start == NULL || end == NULL )
		return 0;

	//
	// we will fill out our own internal array of positions, it better be big enough to
	// accomodate max tiles, if it's not lets make it bigger!
	//
	if( maxTiles > m_buildPositionSize )
	{

		// delete the old array
		delete [] m_buildPositions;

		// create a new one
		m_buildPositions = new Coord3D[ maxTiles ];
		m_buildPositionSize = maxTiles;

		//
		// lets try to at least keep sanity here so that we don't have a completely unbounded
		// allocation spot in the code here
		//
		DEBUG_ASSERTCRASH( m_buildPositionSize < 200, ("Do you really need to tile this many objects!!!") );

	}  // end if
	Coord3D *positions = m_buildPositions;

	// compute a vector from the start of the line in the world to the end
	Real placementX = end->x - start->x;
	Real placementY = end->y - start->y;
	//
	// get the lengh of the placement vector in the world, we'll use this to see how
	// many objects we'll need to fill the entire line
	//
	Real placementLength = (Real)sqrt( placementX * placementX + placementY * placementY );
	//
	// first see how many objects we're going to need to go from the placement
	// line start to the placement line end, we are guaranteed to have one thing (+1)
	//
	Int tilesNeeded = (Int)(placementLength / tilingSize) + 1;
	// we have a max that we are allowed to build to
	if( tilesNeeded > maxTiles )
		tilesNeeded = maxTiles;
	Coord3D pos;
	Coord3D v;
	v.x = placementX;
	v.y = placementY;
	// we're guaranteed to have at least one object so lets take care of that position now
	positions[ 0 ] = *start;
	//
	// march down each object and set the position based on its position in the line.
	// note that we're skipping the first one because we've already set it explicitly
	// and are guaranteed to have at least one object
	//
	Int tilesUsed = 1;  // actual objects "tiled", we are guaranteed to have at least one
	v.z = 0.0f;  //end->z - start->z;
	v.normalize();
	for( Int i = 1; i < tilesNeeded; i++ )
	{

		// compute position of object
		pos.x = v.x * (tilingSize * i) + start->x;
		pos.y = v.y * (tilingSize * i) + start->y;
		pos.z = TheTerrainLogic->getGroundHeight( pos.x, pos.y );

		// check for a legal position to be at and stop the tiling process if that becomes broken
		if( isLocationLegalToBuild( &pos, thingBeingTiled, angle,
																BuildAssistant::USE_QUICK_PATHFIND |
																BuildAssistant::TERRAIN_RESTRICTIONS |
																BuildAssistant::CLEAR_PATH |
																BuildAssistant::NO_OBJECT_OVERLAP |
																BuildAssistant::SHROUD_REVEALED,
																builderObject,
																NULL ) != LBC_OK )
			break;

		// save the position in the output array
		positions[ i ] = pos;

		// we have now actually used one more "tile"
		tilesUsed++;

	}  // end for i

	// return a struct filled out with the actual tiles used and the array of locations
	static TileBuildInfo tileInfo;
	tileInfo.tilesUsed = tilesUsed;
	tileInfo.positions = positions;
	return &tileInfo;

}  // end buildTiledLocations
