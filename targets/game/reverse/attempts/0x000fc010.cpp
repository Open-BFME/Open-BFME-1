// ?buildTiledLocations@BuildAssistant@@UAEPAUTileBuildInfo@1@PBVThingTemplate@@MPBUCoord3D@@1MHPAVObject@@@Z
// partial score=0.9634 date=2026-10-05
// cl: /DNDEBUG /MD /EHsc
// readable body of ?buildTiledLocations@BuildAssistant@@UAEPAUTileBuildInfo@1@PBVThingTemplate@@MPBUCoord3D@@1MHPAVObject@@@Z: game/GameEngine/Source/Common/System/BuildAssistant.cpp
//
// BuildAssistant::buildTiledLocations, retail 0x000FC010 (519 bytes).
//
// Identity: the BuildAssistant vtable 0x010860D8 slot 14 routes here through
// ILT 0x00015DD9 (slot 18 is the matched sellObject); ret 0x1C takes Zero
// Hour's seven arguments, the body grows m_buildPositions (+0x08) and
// m_buildPositionSize (+0x0C), asks slot 10 isLocationLegalToBuild with the
// 0x1F option mask and returns the function-static TileBuildInfo at VA
// 0x012ED840 -- Zero Hour's tiling loop step for step. See
// targets/game/reverse/identity_evidence/000fc010-buildassistant-buildtiledlocations.md.
//
// BFME differences, all read from the retail body:
//  * Coord3D has an empty constructor and destructor (0x00083330 and
//    0x0005BC40), so the position array is built and destroyed through the
//    eh vector iterators with an array cookie;
//  * the line direction is the placement vector itself, normalized in place
//    by the out-of-line Coord3D::normalize (0x000FB930);
//  * TerrainLogic::getGroundHeight is virtual slot +0x18.

#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
// A struct, as the pinned callers' mangled names (PBUCoord3D) require.
struct Coord3D
{
	Coord3D();
	~Coord3D();
	void normalize();

	Real x;
	Real y;
	Real z;
};
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}

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
/** Given the start and end of a line, compute the tiled positions of objects along it,
	* stopping at the first position that is not legal to build at */
//-------------------------------------------------------------------------------------------------
// ?buildTiledLocations@BuildAssistant@@UAEPAUTileBuildInfo@1@PBVThingTemplate@@MPBUCoord3D@@1MHPAVObject@@@Z
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

	}  // end if
	Coord3D *positions = m_buildPositions;

	Real placementX = end->x - start->x;
	Real placementY = end->y - start->y;
	Real placementLength = (Real)sqrt( placementX * placementX + placementY * placementY );
	Int tilesNeeded = (Int)(placementLength / tilingSize) + 1;
	if( tilesNeeded > maxTiles )
		tilesNeeded = maxTiles;
	Coord3D pos;
	Coord3D v;
	v.x = placementX;
	v.y = placementY;
	Int tilesUsed = 1;
	positions[ 0 ] = *start;
	v.z = 0.0f;
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
