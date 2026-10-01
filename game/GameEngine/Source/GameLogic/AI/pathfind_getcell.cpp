// cl: /EHsc /Iinputs/reference/shims/pathfind
// readable body of ?clip@Pathfinder@@QAEXPAUCoord3D@@0@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// Keep the CRT-based inline helper local to this TU.
static float fast_float_floor(float f);
#include "GameLogic/AIPathfind.h"

// Retail's PathfindLayer::getCell (0x003FBAB0), Pathfinder::getCell (0x003D4E80)
// and Pathfinder::worldToCell (0x003D7EC0) are inline, never-inlined bodies in
// retail's pathfinder TUs: every emission is an ANY COMDAT with the same bytes.
// Their rows now live with the TUs that emit them (PathfinderPickBridge.cpp,
// PathfindCheckDestination.cpp, PathfinderRva003D84A0.cpp); a second, strong
// definition here made every strict link fail with LNK2005.

void Pathfinder::clip( Coord3D *startPosition, Coord3D *endPosition )
{
	ICoord2D fromCell, toCell;
	ICoord2D clipFromCell, clipToCell;
	fromCell.x = REAL_TO_INT_FLOOR(startPosition->x/PATHFIND_CELL_SIZE);
	fromCell.y = REAL_TO_INT_FLOOR(startPosition->y/PATHFIND_CELL_SIZE);
	toCell.x = REAL_TO_INT_FLOOR(endPosition->x/PATHFIND_CELL_SIZE);
	toCell.y = REAL_TO_INT_FLOOR(endPosition->y/PATHFIND_CELL_SIZE);
	if (ClipLine2D(&fromCell, &toCell, &clipFromCell, &clipToCell,&m_extent)) {
		if (fromCell.x!=clipFromCell.x || fromCell.y != clipFromCell.y) {
			startPosition->x = clipFromCell.x*PATHFIND_CELL_SIZE + 0.05f;
			startPosition->y = clipFromCell.y*PATHFIND_CELL_SIZE + 0.05f;
		}
		if (toCell.x!=clipToCell.x || toCell.y != clipToCell.y) {
			endPosition->x = clipToCell.x*PATHFIND_CELL_SIZE + 0.05f;
			endPosition->y = clipToCell.y*PATHFIND_CELL_SIZE + 0.05f;
		}
	}
}
