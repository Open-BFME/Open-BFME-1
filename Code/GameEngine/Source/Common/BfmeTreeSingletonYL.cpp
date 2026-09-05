// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the tree singleton accessor at retail 0x00077880, 133 bytes.  A
// function-local static whose constructor allocates the header node and links
// it to itself; the object is re-read from its own address before each store,
// which is what the repeated loads of 0x012ED534 are.

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

struct BfmeNodeYL
{
	char m_bfmeColour;					// +0x00
	BfmeNodeYL *m_bfmeParent;				// +0x04
	BfmeNodeYL *m_bfmeLeft;					// +0x08
	BfmeNodeYL *m_bfmeRight;				// +0x0C
};

class BfmeTreeYL
{
public:
	BfmeTreeYL(void)
	{
		m_bfmeNode = 0;

		m_bfmeNode = (BfmeNodeYL *)_STL::__new_alloc::allocate(0x18);

		m_bfmeCount = 0;

		m_bfmeNode->m_bfmeColour = 0;
		m_bfmeNode->m_bfmeParent = 0;
		m_bfmeNode->m_bfmeLeft = m_bfmeNode;
		m_bfmeNode->m_bfmeRight = m_bfmeNode;
	}

	~BfmeTreeYL(void);

	BfmeNodeYL *m_bfmeNode;					// +0x00
	int m_bfmeCount;					// +0x04
};

// ?bfmeTreeYL@@YAPAVBfmeTreeYL@@XZ
BfmeTreeYL *bfmeTreeYL(void)
{
	static BfmeTreeYL s_bfmeTreeYL;

	return &s_bfmeTreeYL;
}
