// Open-BFME5: clean C++ reconstruction of TerrainLogic's BFME destructor.
// Retail resets the SubsystemInterface subobject first, then destroys the
// tree range, waypoint list, filename, boundary vector, and base subobject.
// cl: /DNDEBUG /MD /EHsc

#include <new>

class TerrainSnapshot
{
public:
	virtual ~TerrainSnapshot() {}
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

namespace _STL
{
	template <bool Threads, int Instance>
	class __node_alloc
	{
		static void _M_deallocate(void *, unsigned int);

	public:
		static void deallocate(void *p, unsigned int n)
		{
			if (n > 128)
				::operator delete(p);
			else
				_M_deallocate(p, n);
		}
	};
}

struct TerrainVectorElement
{
	char bytes[8];
};

struct TerrainTreeRangeElement
{
	char bytes[48];
};

class TerrainTreeFinalizer
{
public:
	~TerrainTreeFinalizer();

private:
	char m_data[0xc];
};

#pragma comment(linker, "/alternatename:??1TerrainTreeFinalizer@@QAE@XZ=?j_0000e2ff@@YAXXZ")

class TerrainVectorStorage
{
public:
	~TerrainVectorStorage()
	{
		if (m_start)
			_STL::__node_alloc<true, 0>::deallocate(
				m_start, (m_capacity - m_start) * sizeof(TerrainVectorElement));
	}

	TerrainVectorElement *m_start;
	TerrainVectorElement *m_finish;
	TerrainVectorElement *m_capacity;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
};


class Member48
{
public:
	~Member48()
	{
		clearA();
		if (m_head)
			_STL::__node_alloc<true, 0>::deallocate(m_head, 0xc);
	}
	void clearA();

private:
	void *m_head;
};

class TerrainTreeRange
{
public:
	__forceinline ~TerrainTreeRange()
	{
		if (m_begin)
			_STL::__node_alloc<true, 0>::deallocate(
				m_begin, (m_capacity - m_begin) * 48);
	}

	TerrainTreeRangeElement *m_begin;
	TerrainTreeRangeElement *m_end;
	TerrainTreeRangeElement *m_capacity;
};

class TerrainLogic : public TerrainSnapshot, public SubsystemInterface
{
public:
	virtual ~TerrainLogic();
	virtual void reset();

private:
	void *m_waypointListHead;
	void *m_bridgeListHead;
	void *m_mapData;
	char m_data[0xc];
	TerrainVectorStorage m_secondVector;
	int m_numWaterToUpdate;
	int m_activeBoundary;
	bool m_waterGridEnabled;
	char m_pad39[3];
	int m_field3c;
	BFMERetailAsciiString m_filenameString;
	bool m_bridgeDamageStatesChanged;
	char m_pad45[3];
	Member48 m_list;
	char m_water[0x500];
	int m_waterCount;
	TerrainTreeFinalizer m_treeFinalizer;
	TerrainTreeRange m_treeRange;
	int m_boundary[0x4e2];
	int m_field18f0;
	bool m_field18f4;
	char m_pad18f5[3];
	int m_field18f8;
	int m_field18fc;
	float m_field1900;
};

TerrainLogic::~TerrainLogic()
{
	(reinterpret_cast<TerrainLogic *>(reinterpret_cast<char *>(this) + 4))
		->TerrainLogic::reset();
}
