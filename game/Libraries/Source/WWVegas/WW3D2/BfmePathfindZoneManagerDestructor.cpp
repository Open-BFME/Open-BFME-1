// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef unsigned int UnsignedInt;

void operator delete(void *value);
void operator delete[](void *value);

class BfmeZoneManagerReset
{
public:
	void reset(void);
};

#pragma comment(linker, "/alternatename:?reset@BfmeZoneManagerReset@@QAEXXZ=?j_0000742d@@YAXXZ")

template <bool threads, int instance>
class BfmeNodeAllocator
{
public:
	static void __cdecl deallocate(void *node, UnsignedInt bytes);
};

#pragma comment(linker, "/alternatename:?deallocate@?$BfmeNodeAllocator@$00$0A@@@SAXPAXI@Z=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

struct BfmeZonePointerMatrix
{
	void *value[12][6];
};

struct BfmeVectorElement
{
	char value[16];
};

class BfmeVector
{
public:
	~BfmeVector()
	{
		BfmeVectorElement *start = m_start;
		if (start != 0) {
			UnsignedInt bytes = (UnsignedInt)((m_end - start) * sizeof(BfmeVectorElement));
			if (bytes > 0x80)
				::operator delete(start);
			else
				BfmeNodeAllocator<true, 0>::deallocate(start, bytes);
		}
	}

	BfmeVectorElement *m_start;
	BfmeVectorElement *m_finish;
	BfmeVectorElement *m_end;
};

class Rva00405B70Tree
{
public:
	~Rva00405B70Tree();

private:
	void *m_data[4];
};

#pragma comment(linker, "/alternatename:??1Rva00405B70Tree@@QAE@XZ=?j_00034e05@@YAXXZ")

class BfmePathfindZoneManager : public BfmeZoneManagerReset
{
public:
	~BfmePathfindZoneManager();

private:
	char m_prefix[0x2329c];
	BfmeZonePointerMatrix m_first;
	BfmeZonePointerMatrix m_second;
	BfmeZonePointerMatrix m_third;
	Rva00405B70Tree m_tree;
	BfmeVector m_secondVector;
	BfmeVector m_firstVector;
	char m_gap[0x14];
	BfmeZonePointerMatrix m_fourth;
};

// ??1BfmePathfindZoneManager@@QAE@XZ
BfmePathfindZoneManager::~BfmePathfindZoneManager()
{
	reset();
	for (int column = 0; column < 6; ++column) {
		for (int row = 0; row < 12; ++row) {
			delete [] m_fourth.value[row][column];
			m_fourth.value[row][column] = 0;
			delete [] m_first.value[row][column];
			m_first.value[row][column] = 0;
			delete [] m_second.value[row][column];
			m_second.value[row][column] = 0;
			delete [] m_third.value[row][column];
			m_third.value[row][column] = 0;
		}
	}
}
