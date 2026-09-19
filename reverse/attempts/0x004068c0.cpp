// ??0PathfindZoneManager@@QAE@XZ
// partial score=0.96 date=2026-09-19
// cl: /DNDEBUG /MD /EHsc
// Byte-exact reconstruction of the BFME PathfindZoneManager constructor.



typedef unsigned short zoneStorageType;

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};
}

struct BfmeZonePointerMatrix
{
	zoneStorageType *value[12][6];
};

struct BfmeTreeNode
{
	unsigned char color;
	unsigned char padding[3];
	BfmeTreeNode *parent;
	BfmeTreeNode *left;
	BfmeTreeNode *right;
};

class Rva00405E70Tree
{
public:
	Rva00405E70Tree()
	{
		m_header = 0;
		m_header = (BfmeTreeNode *)_STL::__new_alloc::allocate(0x34);
		m_nodeCount = 0;
		m_header->color = 0;
		m_header->parent = 0;
		m_header->left = m_header;
		m_header->right = m_header;
	}
	~Rva00405E70Tree();

private:
	BfmeTreeNode *m_header;
	unsigned int m_nodeCount;
	unsigned int m_compare;
};

#pragma comment(linker, "/alternatename:??1Rva00405E70Tree@@QAE@XZ=?j_000429e7@@YAXXZ")

class Rva00406510Vector
{
public:
	Rva00406510Vector()
		: m_start(0), m_finish(0), m_end(0)
	{
	}
	~Rva00406510Vector();

	private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

#pragma comment(linker, "/alternatename:??1Rva00406510Vector@@QAE@XZ=?j_0003b04d@@YAXXZ")

void *operator new[](unsigned int size);

class PathfindZoneManager
{
public:
	PathfindZoneManager();

private:
	unsigned char m_stateEnabled;
	unsigned char m_secondaryStateEnabled;
	unsigned char m_statePadding[2];
	int m_currentZone;
	int m_nextFrameToCalculateZones;
	int m_zonesAllocated;
	int m_reserved08;
	int m_reserved0c;
	zoneStorageType m_zoneEquivalency[24000];
	zoneStorageType m_groundEquivalency[24000];
	zoneStorageType m_waterEquivalency[24000];
	int m_maxZone;
	BfmeZonePointerMatrix m_first;
	BfmeZonePointerMatrix m_second;
	BfmeZonePointerMatrix m_third;
	Rva00405E70Tree m_tree;
	volatile int m_reserved23608;
	Rva00406510Vector m_secondVector;
	Rva00406510Vector m_firstVector;
	void *m_blockOfZoneBlocks;
	void *m_zoneBlocks;
	int m_zoneBlockExtentX;
	int m_zoneBlockExtentY;
	int m_reserved23634;
	BfmeZonePointerMatrix m_fourth;
};

PathfindZoneManager::PathfindZoneManager()
	: m_stateEnabled(0),
	  m_secondaryStateEnabled(0),
	  m_currentZone(-1),
	  m_maxZone(0),
	  m_reserved23608(0),
	  m_secondVector(),
	  m_firstVector()
{
	m_blockOfZoneBlocks = 0;
	m_zoneBlocks = 0;
	m_reserved23634 = 0;
	m_reserved08 = 0;
	m_reserved0c = 0;
	m_nextFrameToCalculateZones = 0;
	m_zonesAllocated = 0;
	m_zoneBlockExtentX = 0;
	m_zoneBlockExtentY = 0;

	for (int column = 0; column < 6; ++column)
	{
		for (int row = 0; row < 12; ++row)
		{
			m_first.value[row][column] = new zoneStorageType[24000];
			m_second.value[row][column] = new zoneStorageType[24000];
			m_third.value[row][column] = new zoneStorageType[24000];
			m_fourth.value[row][column] = new zoneStorageType[24000];
		}
	}

	for (int i = 0; i < 24000; ++i)
	{
		m_zoneEquivalency[i] = 0;
		m_groundEquivalency[i] = 0;
		m_waterEquivalency[i] = 0;
	}
}
