// cl: /DNDEBUG /MD /EHsc
// readable body of ?prependNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// Open-BFME: Path::prependNode, retail 0x0026E4D0, 104 bytes.
//
// Same inlined PathNode constructor as Path_appendNode (0x24 bytes, INT_MAX at
// +0x20). BFME also wires the optimized link to the old head so the optimized
// chain is not left pointing at the previous start after a prepend.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D &operator=(const Coord3D &other) { x = other.x; y = other.y; z = other.z; return *this; }

	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	PathNode(const Coord3D *pos, PathfindLayerEnum layer)
	{
		m_next = 0;
		m_prev = 0;
		m_nextOpti = 0;
		m_pos = *pos;
		m_layer = layer;
		m_canOptimize = false;
		m_costSoFar = 0x7FFFFFFF;
	}

	PathNode *m_next;
	PathNode *m_prev;
	PathNode *m_nextOpti;
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	void prependNode(const Coord3D *pos, PathfindLayerEnum layer);

private:
	char m_slice_pad[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

// ?prependNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z
void Path::prependNode(const Coord3D *pos, PathfindLayerEnum layer)
{
	PathNode *node = new PathNode(pos, layer);
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
