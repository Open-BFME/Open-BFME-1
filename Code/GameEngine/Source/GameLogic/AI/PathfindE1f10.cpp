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

struct Coord3D
{
	float x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

#define PATHFIND_CELL_SIZE_F 10.0f

class Pathfinder
{
public:
	Bool sameCell( Object *obj, Coord3D from, Coord3D to );

	void bfmeQuery( Object *obj, Int *radius, Bool *center );
	bool worldToCell( const Coord3D *pos, ICoord2D *cell );
};

Bool Pathfinder::sameCell( Object *obj, Coord3D from, Coord3D to )
{
	ICoord2D fromCell;
	Bool centerInCell;
	bfmeQuery( obj, &fromCell.x, &centerInCell );

	if (!centerInCell) {
		from.x += PATHFIND_CELL_SIZE_F/2;
		from.y += PATHFIND_CELL_SIZE_F/2;
		to.x += PATHFIND_CELL_SIZE_F/2;
		to.y += PATHFIND_CELL_SIZE_F/2;
	}

	worldToCell( &from, &fromCell );

	ICoord2D &toCell = *(ICoord2D *)&from;
	worldToCell( &to, &toCell );

	return fromCell.x == toCell.x && fromCell.y == toCell.y;
}
