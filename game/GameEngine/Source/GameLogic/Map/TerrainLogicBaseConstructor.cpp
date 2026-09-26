// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Open-BFME5: TerrainLogicBase::TerrainLogicBase, retail 0x001ADB80.
// The layout and member initialization are corroborated by TerrainLogic::reset
// and the matched derived TerrainLogic constructor at 0x006BE070.

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};
}

class TerrainLogicBaseFirst
{
public:
	virtual ~TerrainLogicBaseFirst();
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
};

struct TerrainWaterSlot
{
	void *m_water;
	float m_level;
	float m_minX;
	float m_minY;
	float m_angle;
};

class TerrainVectorStorage
{
public:
	TerrainVectorStorage() : m_begin(0), m_end(0), m_storageEnd(0) {}
	~TerrainVectorStorage();

private:
	void *m_begin;
	void *m_end;
	void *m_storageEnd;
};

struct TerrainListNode
{
	TerrainListNode *m_next;
	TerrainListNode *m_previous;
	int m_value;
};

class TerrainList
{
public:
	TerrainList()
	{
		m_head = 0;
		TerrainListNode *node =
			(TerrainListNode *)_STL::__new_alloc::allocate(sizeof(TerrainListNode));
		node->m_next = node;
		node->m_previous = node;
		m_head = node;
	}
	~TerrainList();

private:
	TerrainListNode *m_head;
};

struct TerrainTreeNode
{
	unsigned char m_colour;
	TerrainTreeNode *m_parent;
	TerrainTreeNode *m_left;
	TerrainTreeNode *m_right;
	char m_payload[8];
};

class TerrainTree
{
public:
	TerrainTree()
	{
		m_header = 0;
		m_header = (TerrainTreeNode *)_STL::__new_alloc::allocate(sizeof(TerrainTreeNode));
		m_count = 0;
		m_header->m_colour = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
		m_unknown0c = 0;
		m_unknown10 = 0;
		m_unknown14 = 0;
	}
	~TerrainTree();

private:
	TerrainTreeNode *m_header;
	int m_count;
	int m_compare;
	int m_unknown0c;
	int m_unknown10;
	int m_unknown14;
};

class TerrainLogicBase : public TerrainLogicBaseFirst, public SubsystemInterface
{
public:
	TerrainLogicBase();
	virtual ~TerrainLogicBase();

private:
	int m_unknown08;
	void *m_waypointListHead;
	void *m_bridgeListHead;
	void *m_mapData;
	TerrainVectorStorage m_firstVector;
	TerrainVectorStorage m_secondVector;
	int m_numWaterToUpdate;
	int m_activeBoundary;
	bool m_waterGridEnabled;
	char m_pad39[3];
	int m_field3c;
	int m_field40;
	bool m_bridgeDamageStatesChanged;
	char m_pad45[3];
	TerrainList m_list;
	TerrainWaterSlot m_water[64];
	int m_waterCount;
	TerrainTree m_tree;
	int m_boundary[0x4e2];
	int m_field18f0;
	bool m_field18f4;
	char m_pad18f5[3];
	int m_field18f8;
	int m_field18fc;
};

TerrainLogicBase::TerrainLogicBase() :
	m_firstVector(),
	m_secondVector(),
	m_field3c(1),
	m_field40(0)
{
	m_field18f4 = false;
	m_numWaterToUpdate = 0;
	m_bridgeDamageStatesChanged = false;

	for (int j = 0; j != 64; ++j)
	{
		m_water[j].m_water = 0;
		m_water[j].m_level = 0.0f;
		m_water[j].m_minX = 0.0f;
		m_water[j].m_minY = 0.0f;
		m_water[j].m_angle = 0.0f;
	}

	m_waterCount = 0;
	m_activeBoundary = 0;
	m_waypointListHead = 0;
	m_waterGridEnabled = false;
	m_bridgeListHead = 0;
	m_mapData = 0;

	for (int k = 0; k != 0x4e2; ++k)
		m_boundary[k] = -1;

	m_field18f0 = 0;
	m_field18f8 = 0;
}
