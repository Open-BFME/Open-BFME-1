// cl: /DNDEBUG /MD
//
// Retail 0x003E1F10: "are these two world positions in the same pathfind cell?"
//
// A BFME helper built out of the opening of ZH's cell lookups (AIPathfind.cpp
// 8483/8690): ask the pathfinder for the object's radius and centre flag --
// through Pathfinder::bfmeQuery, BFME's out-of-line form of ZH's inlined
// getRadiusAndCenter -- nudge the two positions to the cell centre when the
// object does not centre in its cell (ZH's `adjustTo.x += PATHFIND_CELL_SIZE_F/2`
// pair, here applied to both endpoints), then worldToCell both and compare the
// cell indices.  `ret 0x1C` fixes the argument list at 28 bytes, so both Coord3Ds
// come in by value and the adjustment is done in place on the incoming copies.
//
// Codegen notes (retail gets by with only 8 bytes of locals):
//   * the destination cell is written over the now-dead by-value copy of `from`
//     (retail's second worldToCell writes to the parameter home at [esp+0x14]),
//     so toCell is bound as a reference into `from` rather than being a local;
//   * the radius output shares storage with fromCell.x -- retail hands
//     bfmeQuery the same slot it later fills with the source cell index.
// Declaring an independent `Int radius` or an independent `ICoord2D toCell`
// costs 4 and 12 extra bytes of frame respectively and breaks the match.
//
// Bool is a byte here: retail returns in al (B0 01 / 32 C0), which a C++ `bool`
// return does not produce for the `&&` expression.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;
typedef unsigned char Bool;

class Object;

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

#define PATHFIND_CELL_SIZE_F 10.0f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool sameCell( Object *object, Coord3D fromPosition, Coord3D toPosition );

	void bfmeQuery( Object *object, Int *radius, Bool *centerInCell );
	bool worldToCell( const Coord3D *worldPosition, ICoord2D *cellIndex );
};

Bool Pathfinder::sameCell( Object *object, Coord3D fromPosition, Coord3D toPosition )
{
	ICoord2D fromCell;
	Bool centerInCell;
	bfmeQuery( object, &fromCell.x, &centerInCell );

	if (!centerInCell) {
		fromPosition.x += PATHFIND_CELL_SIZE_F/2;
		fromPosition.y += PATHFIND_CELL_SIZE_F/2;
		toPosition.x += PATHFIND_CELL_SIZE_F/2;
		toPosition.y += PATHFIND_CELL_SIZE_F/2;
	}

	worldToCell( &fromPosition, &fromCell );

	ICoord2D &toCell = *(ICoord2D *)&fromPosition;
	worldToCell( &toPosition, &toCell );

	return fromCell.x == toCell.x && fromCell.y == toCell.y;
}
