// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the tree singleton accessor at retail 0x000777D0, 133 bytes.  A
// function-local static whose constructor allocates the header node and links
// it to itself; the object is re-read from its own address before each store,
// which is what the repeated loads of 0x012ED534 are.

extern "C" int __cdecl atexit(void (__cdecl *function)(void));
void bfmeForward_00C6FCB0(void);

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

struct BfmeNodeYK
{
	char m_bfmeColour;					// +0x00
	BfmeNodeYK *m_bfmeParent;				// +0x04
	BfmeNodeYK *m_bfmeLeft;					// +0x08
	BfmeNodeYK *m_bfmeRight;				// +0x0C
};

class BfmeTreeYK
{
public:
	BfmeTreeYK(void)
	{
		m_bfmeNode = 0;

		m_bfmeNode = (BfmeNodeYK *)_STL::__new_alloc::allocate(0x18);

		m_bfmeCount = 0;

		m_bfmeNode->m_bfmeColour = 0;
		m_bfmeNode->m_bfmeParent = 0;
		m_bfmeNode->m_bfmeLeft = m_bfmeNode;
		m_bfmeNode->m_bfmeRight = m_bfmeNode;
		// The matched retail callback forwards to this singleton's tree destructor.
		atexit(bfmeForward_00C6FCB0);
	}

	BfmeNodeYK *m_bfmeNode;					// +0x00
	int m_bfmeCount;					// +0x04
};

// ?bfmeTreeYK@@YAPAVBfmeTreeYK@@XZ
BfmeTreeYK *bfmeTreeYK(void)
{
	static BfmeTreeYK s_bfmeTreeYK;

	return &s_bfmeTreeYK;
}
