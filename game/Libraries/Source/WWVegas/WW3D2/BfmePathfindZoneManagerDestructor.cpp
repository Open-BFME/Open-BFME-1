// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef unsigned int UnsignedInt;

void operator delete(void *value);
void operator delete[](void *value);

// Retail reaches both base cleanup routines through incremental-link thunks;
// the call sites below name the thunk addresses directly.
extern void j_0000742d();
extern void j_00034e05();

class BfmeZoneManagerReset
{
};

namespace _STL
{
// The node allocator's pool entry points are private STLport members; this
// TU-local friend helper reaches _M_deallocate under its real name.
template <bool threads, int instance> class __node_alloc;
static void zonePoolDeallocate(void *block, UnsignedInt bytes);
template <bool threads, int instance>
class __node_alloc
{
	friend void zonePoolDeallocate(void *, UnsignedInt);
	static void __cdecl _M_deallocate(void *node, UnsignedInt bytes);
};
static inline void zonePoolDeallocate(void *block, UnsignedInt bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

struct BfmeZonePointerMatrix
{
	void *value[12][6];
};

struct BfmeVectorElement
{
	char value[16];
};

namespace {
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
				_STL::zonePoolDeallocate(start, bytes);
		}
	}

	BfmeVectorElement *m_start;
	BfmeVectorElement *m_finish;
	BfmeVectorElement *m_end;
};
}

class Rva00405B70Tree
{
public:
	~Rva00405B70Tree()
	{
		typedef void (Rva00405B70Tree::*Dtor)(void);
		union { void (*fn)(); Dtor call; } dtor = { j_00034e05 };
		(this->*dtor.call)();
	}

private:
	void *m_data[4];
};

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
	typedef void (BfmeZoneManagerReset::*Reset)(void);
	union { void (*fn)(); Reset call; } reset = { j_0000742d };
	(static_cast<BfmeZoneManagerReset *>(this)->*reset.call)();
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
