// cl: /DNDEBUG /MD /EHsc
// readable body of ?appendNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?prependNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
//
// The two ends of a Path: appendNode (retail 0x0016A4B0, 180 bytes) links a new
// node onto the tail, prependNode (retail 0x0026E4D0, 104 bytes) onto the head.
// They allocate the same node from the same inlined constructor and touch the
// same four Path fields, and each carried its own copy of PathNode, Path and
// Coord3D -- two copies of a node layout that had to agree.
//
// The node's position and layer are set by its constructor rather than after
// it. Every one of those stores sits inside the block guarded by the
// allocation's null check, which is where MSVC puts a constructor and nowhere
// else -- written the reference's way, as two setters on the returned pointer,
// they land outside it and appendNode grows nine bytes.
//
// The node's shape comes out of that inlined constructor: next, prev and the
// optimized link zeroed at +0, +4 and +8, the position at +0x0C, the layer at
// +0x18, a flag byte at +0x1C and +0x20 seeded with INT_MAX, in 0x24 bytes.
//
// Both bodies differ from the reference in the same direction, which is easier
// to see with them side by side: BFME maintains the optimized chain as it
// splices. The reference's append walks the whole path from its head to find
// the end; here the tail already kept at this+0x08 is linked to directly, the
// head at +0x04 is only written when the path was empty, and the optimized-path
// hook runs on the old tail before the new one is stored. Prepend wires the new
// node's optimized link to the old head for the same reason, so the optimized
// chain is not left pointing at the previous start.
//
// appendNode reads the tail once into a local for the link: read twice, as two
// member accesses, the compiler reloads it between the two stores and the body
// grows three bytes.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	// Member-wise: retail stores the three fields straight into the node at
	// +0x0C, +0x10 and +0x14 rather than materialising the address a block
	// copy of the whole struct needs.
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

	const Coord3D *getPosition(void) const { return &m_pos; }

	void setNextOptimized(PathNode *node);			// ILT 0x0002E5FA

	PathNode *m_next;					// this+0x00
	PathNode *m_prev;					// this+0x04
	PathNode *m_nextOpti;					// this+0x08
	Coord3D m_pos;						// this+0x0C
	PathfindLayerEnum m_layer;				// this+0x18
	Bool m_canOptimize;					// this+0x1C
	Int m_costSoFar;					// this+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	void appendNode(const Coord3D *pos, PathfindLayerEnum layer);
	void prependNode(const Coord3D *pos, PathfindLayerEnum layer);

private:
	char m_slice_pad[4];					// retail this+0x00, untouched
	PathNode *m_path;					// this+0x04
	PathNode *m_pathTail;					// this+0x08
	Bool m_isOptimized;					// this+0x0C
};

// ?appendNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z
void Path::appendNode( const Coord3D *pos, PathfindLayerEnum layer )
{
	if (m_isOptimized && m_pathTail)
	{
		/* Check for duplicates. */
		if (pos->x == m_pathTail->getPosition()->x && pos->y == m_pathTail->getPosition()->y) {
			return;
		}
	}
	PathNode *node = new PathNode( pos, layer );

	PathNode *tail = m_pathTail;
	if (tail)
	{
		tail->m_next = node;
		if (node)
			node->m_prev = tail;
	}

	if (m_isOptimized && m_pathTail)
	{
		m_pathTail->setNextOptimized(node);
	}

	m_pathTail = node;

	if (m_path == 0)
		m_path = node;
}

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
