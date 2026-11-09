// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the tree singleton accessor at retail 0x00077930, 133 bytes.  A
// function-local static whose constructor allocates the header node and links
// it to itself; the object is re-read from its own address before each store,
// which is what the repeated loads of 0x012ED534 are.

extern "C" int __cdecl atexit(void (__cdecl *function)(void));
void bfmeForward_00C6FC90(void);

namespace _STL {

// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}

}

struct BfmeNodeYM
{
	char m_color;					// +0x00
	BfmeNodeYM *m_parent;				// +0x04
	BfmeNodeYM *m_left;					// +0x08
	BfmeNodeYM *m_right;				// +0x0C
};

class BfmeTreeYM
{
public:
	BfmeTreeYM(void)
	{
		m_header = 0;

		m_header = (BfmeNodeYM *)_STL::vectorSmallAllocate(0x18);

		m_numNodes = 0;

		m_header->m_color = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
		// The matched retail callback forwards to this singleton's tree destructor.
		atexit(bfmeForward_00C6FC90);
	}

	BfmeNodeYM *m_header;					// +0x00
	int m_numNodes;					// +0x04
};

// ?bfmeTreeYM@@YAPAVBfmeTreeYM@@XZ
BfmeTreeYM *bfmeTreeYM(void)
{
	static BfmeTreeYM s_bfmeTreeYM;

	return &s_bfmeTreeYM;
}
