// ?reset@Rva00406B10PathfindZoneManager@@QAEXXZ
// partial score=0.35 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef unsigned int UnsignedInt;

void operator delete(void *value);
void operator delete[](void *value);

// Retail 0x00040138: per-element destructor the array-delete helper calls
// for each of the 0x228-byte zone blocks.
extern void j_00040138(void);

class Rva00406B10ZoneBlock
{
public:
	~Rva00406B10ZoneBlock()
	{
		typedef void (Rva00406B10ZoneBlock::*DtorFn)();
		union { void (*freeFn)(void); DtorFn memberFn; } thunk;
		thunk.freeFn = j_00040138;
		(this->*thunk.memberFn)();
	}

	unsigned char m_body[0x228];
};

struct BfmeVectorElement
{
	char value[16];
};

class BfmeVector
{
public:
	BfmeVectorElement *m_start;
	BfmeVectorElement *m_finish;
	BfmeVectorElement *m_end;
};

// upstream layout: matches the STLport _Rb_tree_node_base header this build
// uses elsewhere: color (padded to a dword), parent, left, right.
class Rva00405B70Node
{
public:
	void *m_color;
	Rva00405B70Node *m_parent;
	Rva00405B70Node *m_left;
	Rva00405B70Node *m_right;
};

class Rva00405B70Tree
{
public:
	Rva00405B70Node *m_header;
	UnsignedInt m_size;
	void *m_pad8;
	void *m_padc;
};

extern void j_0001b9b9(void);

template <bool threads, int instance>
class BfmeNodeAllocator
{
public:
	static void __cdecl deallocate(void *node, UnsignedInt bytes);
};

#pragma comment(linker, "/alternatename:?deallocate@?$BfmeNodeAllocator@$00$0A@@@SAXPAXI@Z=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

class Rva00406B10PathfindZoneManager
{
public:
	void reset(void);

private:
	char m_prefix[0x23624 - 0];
	Rva00406B10ZoneBlock *m_zoneBlocks;
	UnsignedInt *m_pointerArray;
	UnsignedInt m_pointerArrayField8;
	UnsignedInt m_pointerArrayFieldC;
	char m_padTail[0x23638 - 0x23634];
};

// Retail 0x00406B10 (246B), reached through the ILT thunk at 0x0000742D that
// BfmeZoneManagerReset::reset() aliases to (BfmePathfindZoneManagerDestructor.cpp
// establishes that alias and the surrounding class fields at +0x23624 as an
// opaque m_gap; this body proves what that gap actually holds). Frees the
// zone-block array (each element destructed through its own thunk), frees a
// second plain pointer array, clears two counters, sets two flag bytes and a
// dword flag near the object head, runs a self-cancelling vector-compaction
// loop that always computes a zero count (retail bug: the "finish" pointer
// gets subtracted from itself instead of from "start", so the copy body
// never actually executes), then destroys the red-black tree at +0x235FC
// node by node (right subtree through its own recursive-erase ILT thunk,
// left subtree iteratively) and reinitialises it as an empty circular
// sentinel. No caller/class identity survived the prior identity sweep
// beyond the alternatename evidence above (blocked once: t=12m
// model=gpt-5); every name here is address-derived.
void Rva00406B10PathfindZoneManager::reset(void)
{
	if (m_zoneBlocks != 0)
	{
		delete[] m_zoneBlocks;
		m_zoneBlocks = 0;
	}

	delete[] reinterpret_cast<char *>(m_pointerArray);
	m_pointerArray = 0;
	m_pointerArrayField8 = 0;
	m_pointerArrayFieldC = 0;

	m_prefix[0] = 1;
	m_prefix[1] = 1;
	*reinterpret_cast<int *>(m_prefix + 4) = -1;

	BfmeVector *secondVector = reinterpret_cast<BfmeVector *>(m_prefix + 0x2360c);
	BfmeVectorElement *rangeFinish = secondVector->m_finish;
	BfmeVectorElement *dst = secondVector->m_start;
	int count = (int)(rangeFinish - rangeFinish);
	BfmeVectorElement *src = rangeFinish;
	for (; count > 0; --count)
	{
		*dst = *src;
		++src;
		++dst;
	}
	secondVector->m_finish = dst;

	Rva00405B70Tree *tree = reinterpret_cast<Rva00405B70Tree *>(m_prefix + 0x235fc);
	if (tree->m_size != 0)
	{
		Rva00405B70Node *node = tree->m_header->m_parent;
		if (node != 0)
		{
			do
			{
				typedef void (Rva00405B70Tree::*EraseFn)(Rva00405B70Node *);
				union { void (*freeFn)(void); EraseFn memberFn; } erase;
				erase.freeFn = j_0001b9b9;
				(tree->*erase.memberFn)(node->m_right);

				Rva00405B70Node *left = node->m_left;
				BfmeNodeAllocator<true, 0>::deallocate(node, 0x34);
				node = left;
			}
			while (node != 0);
		}

		tree->m_header->m_left = tree->m_header;
		tree->m_header->m_parent = 0;
		tree->m_header->m_right = tree->m_header;
		tree->m_size = 0;
	}
}
