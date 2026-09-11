// ??1TerrainLogic@@UAE@XZ
// partial score=0.96 date=2026-09-09
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

class TerrainResetTarget
{
public:
	void reset();
};

#pragma comment(linker, "/alternatename:?reset@TerrainResetTarget@@QAEXXZ=?j_0001b707@@YAXXZ")

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
};

#pragma comment(linker, "/alternatename:??1TerrainTreeFinalizer@@UAE@XZ=?j_0000e2ff@@YAXXZ")

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

class TerrainAsciiString
{
public:
	~TerrainAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
};

#pragma comment(linker, "/alternatename:?releaseBuffer@TerrainAsciiString@@AAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

class TerrainList
{
public:
	~TerrainList()
	{
		clear();
		if (m_head)
			_STL::__node_alloc<true, 0>::deallocate(m_head, 0xc);
	}
	void clear();

private:
	void *m_head;
};

#pragma comment(linker, "/alternatename:?clear@TerrainList@@QAEXXZ=?j_0000aae7@@YAXXZ")

class TerrainTreeRange
{
public:
	__forceinline ~TerrainTreeRange()
	{
		if (m_begin)
			_STL::__node_alloc<true, 0>::deallocate(
				m_begin, (m_capacity - m_begin) * 48);
		reinterpret_cast<TerrainTreeFinalizer *>(
			reinterpret_cast<char *>(this) - 0xc)->~TerrainTreeFinalizer();
	}

	TerrainTreeRangeElement *m_begin;
	TerrainTreeRangeElement *m_end;
	TerrainTreeRangeElement *m_capacity;
};

class TerrainTree
{
public:
	__forceinline ~TerrainTree() {}

	void *m_header;
	int m_count;
	int m_compare;
	TerrainTreeRange m_range;
};

class TerrainLogic : public TerrainSnapshot, public SubsystemInterface
{
public:
	virtual ~TerrainLogic();

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
	TerrainAsciiString m_filenameString;
	bool m_bridgeDamageStatesChanged;
	char m_pad45[3];
	TerrainList m_list;
	char m_water[0x500];
	int m_waterCount;
	TerrainTree m_tree;
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
	(reinterpret_cast<TerrainResetTarget *>(reinterpret_cast<char *>(this) + 4))->reset();
}
