// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00401C70 (946 bytes): the BFME Path's save/load transfer.
//
// Identity: the matched AICommandParmsStorage::doXfer (0x00187860) calls it
// through ILT 0x00045FD9 on the 0x24-byte Path it news when the xferred
// hasPath flag is set, which is where Zero Hour calls Path::xfer
// (AIPathfind.cpp).  The body is that function reshaped: count the nodes,
// write them tail first on save, prepend them on load, then the isOptimized
// pair.  BFME's Path is not Zero Hour's Snapshot (there is no vptr: the Int at
// +0x00 is xferred last), so the method keeps the address token of the name
// the caller already uses.  BFME replaced Zero Hour's PathNode::m_id numbering
// with two maps (node -> index on save, index -> node on load), whose
// operator[] and tree destructors are instantiated here and reached only from
// this body.  PathNode and the first Path members follow the matched
// PathNodeInsertion.cpp (appendNode 0x0016A4B0, prependNode 0x0026E4D0).

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	// Member-wise, as in PathNodeInsertion.cpp: retail copies the three
	// fields one by one rather than through a materialised source address.
	Coord3D &operator=(const Coord3D &other) { x = other.x; y = other.y; z = other.z; return *this; }

	Real x, y, z;
};

// Built by a constructor, as in TeamRelationMap_xfer.cpp.
struct XferVersion
{
	XferVersion(UnsignedByte current) : m_version(current), m_currentVersion(current) {}
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual Xfer &xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void slot26();
	virtual Xfer &xferReal(Real *value);
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual Xfer &xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &xferBool(Bool *value);
};

// The layer goes through one of the 25-byte slot-0x90 forwarders
// (MidVirtualSlot90Forwarders.cpp); its identity is not recovered.
class MidVirtualSlot90Receiver;
void Rva0010BF60(MidVirtualSlot90Receiver *receiver, void *context);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer)
	{
		m_next = 0;
		m_prev = 0;
		m_nextOpti = 0;
		m_pos = *position;
		m_layer = layer;
		m_canOptimize = false;
		m_costSoFar = 0x7FFFFFFF;
	}

	const Coord3D *getPosition(void) const { return &m_pos; }
	PathfindLayerEnum getLayer(void) const { return m_layer; }
	Bool getCanOptimize(void) const { return m_canOptimize; }
	void setCanOptimize(Bool canOpt) { m_canOptimize = canOpt; }
	PathNode *getNextOptimized(void) const { return m_nextOpti; }
	PathNode *getPrevious(void) const { return m_prev; }
	PathNode *getNext(void) const { return m_next; }

	PathNode *m_next;					// this+0x00
	PathNode *m_prev;					// this+0x04
	PathNode *m_nextOpti;					// this+0x08
	Coord3D m_pos;						// this+0x0C
	PathfindLayerEnum m_layer;				// this+0x18
	Bool m_canOptimize;					// this+0x1C
	Int m_costSoFar;					// this+0x20
};

typedef _STL::map<PathNode *, Int> PathNodeIndexMap;
typedef _STL::map<Int, PathNode *> PathIndexNodeMap;

class Path
{
public:
	void xfer00401C70(Xfer *xfer);

private:
	Int m_int00;						// this+0x00, xferred last
	PathNode *m_path;					// this+0x04
	PathNode *m_pathTail;					// this+0x08
	Bool m_isOptimized;					// this+0x0C
	Bool m_bool0D;						// this+0x0D
	PathNode *m_node10;					// this+0x10
	Coord3D m_coord14;					// this+0x14
	Real m_real20;						// this+0x20
};

// ?xfer00401C70@Path@@QAEXPAVXfer@@@Z
void Path::xfer00401C70(Xfer *xfer)
{
	if (xfer->isDoingCRC())
		return;

	{
		XferVersion version(1);
		xfer->xferVersion(&version);
	}

	Int count = 0;
	PathNode *node = m_path;
	while (node)
	{
		count++;
		node = node->getNext();
	}
	xfer->xferInt(&count);

	if (xfer->isSaving())
	{
		PathNodeIndexMap nodeIndex;
		node = m_pathTail;	// written backwards
		while (node)
		{
			nodeIndex[node] = count;
			xfer->xferInt(&count);
			Coord3D pos;
			pos = *node->getPosition();
			xfer->xferCoord3D(&pos);
			PathfindLayerEnum layer = node->getLayer();
			Rva0010BF60((MidVirtualSlot90Receiver *)xfer, &layer);
			Bool canOpt = node->getCanOptimize();
			xfer->xferBool(&canOpt);
			Int id = -1;
			if (node->getNextOptimized())
				id = nodeIndex[node->getNextOptimized()];
			xfer->xferInt(&id);
			UnsignedInt cost = node->m_costSoFar;
			xfer->xferUnsignedInt(&cost);
			count--;
			node = node->getPrevious();
		}
		Int id10 = 0;
		if (m_node10)
			id10 = nodeIndex[m_node10];
		xfer->xferInt(&id10);
	}
	else
	{
		PathIndexNodeMap indexNode;
		while (count)
		{
			Int nodeId;
			xfer->xferInt(&nodeId);
			Coord3D pos;
			xfer->xferCoord3D(&pos);
			PathfindLayerEnum layer;
			Rva0010BF60((MidVirtualSlot90Receiver *)xfer, &layer);
			Bool canOpt;
			xfer->xferBool(&canOpt);
			Int optId = -1;
			xfer->xferInt(&optId);
			UnsignedInt cost = 0x7FFFFFFF;
			xfer->xferUnsignedInt(&cost);

			PathNode *newNode = new PathNode(&pos, layer);
			indexNode[nodeId] = newNode;
			newNode->setCanOptimize(canOpt);
			newNode->m_costSoFar = cost;

			PathNode *optNode = 0;
			if (optId > 0)
			{
				PathIndexNodeMap::iterator it = indexNode.lower_bound(optId);
				if (it != indexNode.end() && !(optId < it->first))
					optNode = it->second;
			}

			PathNode *head = m_path;
			newNode->m_nextOpti = head;
			newNode->m_next = head;
			if (head)
				head->m_prev = newNode;
			m_path = newNode;
			if (m_pathTail == 0)
				m_pathTail = newNode;
			if (optNode)
				newNode->m_nextOpti = optNode;
			count--;
		}
		Int id10;
		xfer->xferInt(&id10);
		m_node10 = id10 ? indexNode[id10] : 0;
	}

	xfer->xferBool(&m_isOptimized).xferBool(&m_bool0D).xferCoord3D(&m_coord14).xferReal(&m_real20);
	xfer->xferInt(&m_int00);
}
