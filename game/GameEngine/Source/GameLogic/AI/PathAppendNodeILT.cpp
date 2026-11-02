// cl: /DNDEBUG /MD /EHsc

typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"


enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Path
{
public:
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};

class PathAppendNodeILT
{
public:
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};

// Retail 0x0003833E is a five-byte ILT that forwards to Path::appendNode at
// 0x0016A4B0. The Pathfinder::setDebugPath caller and jump target prove this
// forwarding member's ABI and identity.
void PathAppendNodeILT::appendNode(
	const Coord3D *position, PathfindLayerEnum layer)
{
	((Path *)this)->appendNode(position, layer);
}
