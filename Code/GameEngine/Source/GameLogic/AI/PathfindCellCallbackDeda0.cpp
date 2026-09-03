// cl: /DNDEBUG /MD
//
// Retail 0x003DEDA0: BFME's member-ified Pathfinder::groundPathPassableCallback.
//
// ZH (AIPathfind.cpp:9626) writes it as a static CellAlongLineProc taking
// (pathfinder, from, to, to_x, to_y, userData) over a GroundPathPassableStruct
// payload:
//
//   Int curDiameter = pathfinder->clearCellForDiameter(d->crusher, to_x, to_y,
//                                                      to->getLayer(), d->diameter);
//   if (curDiameter == d->diameter) return 0;
//   if (from && to->getLayer() != LAYER_GROUND && from->getLayer() == to->getLayer())
//     return 0;
//   return 1;
//
// BFME turned the userData struct into the `this` of a member taking
// (from, to, to_x, to_y) -- `ret 0x10` -- keeping the pathfinder as the payload's
// first field and the diameter as its second, and hoisted the layer test in
// front of the clearCellForDiameter call, which folds the two `return 0` exits
// into one and lets the tail be a plain `!= m_diameter`.  ZH's single
// `!= LAYER_GROUND` became the closed range 2..15 (the wall/bridge layers), and
// the crusher argument is a literal 0 with a sixth literal 1 appended.
//
// getLayer() is the bitfield at PathfindCell+0x0C, shift 6, width 6; the explicit
// shift/mask accessor reproduces `shr eax,6; and eax,0x3f` exactly.
//
// clearCellForDiameter must only be declared -- a definition in this TU would
// emit no relocation and could never resolve to retail's ILT.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getLayer( void ) const { return (m_bits >> 6) & 0x3f; }

	char m_pad[12];
	unsigned int m_bits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Int clearCellForDiameter( Int crusher, Int cellX, Int cellY, Int layer, Int diameter, Int attackerOnWall );
};

class GroundPathPassableStruct
{
public:
	Int cellCallback( PathfindCell *from, PathfindCell *to, Int to_x, Int to_y );

	Pathfinder *m_pathfinder;		// 0x00
	Int m_diameter;					// 0x04
};

Int GroundPathPassableStruct::cellCallback( PathfindCell *from, PathfindCell *to, Int to_x, Int to_y )
{
	if (from && to->getLayer() >= 2 && to->getLayer() <= 15 && from->getLayer() == to->getLayer()) {
		return 0;
	}

	return m_pathfinder->clearCellForDiameter( 0, to_x, to_y, to->getLayer(), m_diameter, 1 ) != m_diameter;
}
