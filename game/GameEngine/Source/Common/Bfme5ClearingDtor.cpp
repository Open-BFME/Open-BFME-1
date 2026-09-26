// A clearing destructor over two bases.
//
// The body is one statement: clear the list the first base keeps. Everything
// around it is bookkeeping -- the two most-derived vptrs at entry, then the
// second base's own vptr as it is destroyed inline, then the first base's
// destructor out of line.
//
// The clear is the list's, not the list's destructor: it walks and frees the
// nodes and re-points the sentinel at itself, but never frees the sentinel.
// The unwind frame is there for the two bases, which is why the state word
// starts at one rather than zero.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeClearNodeB
{
	BfmeClearNodeB *m_bfmeNext;				// +0x00
	BfmeClearNodeB *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeClearListB
{
public:
	void bfmeClear(void)
	{
		BfmeClearNodeB *node = m_bfmeNode->m_bfmeNext;

		while (node != m_bfmeNode)
		{
			BfmeClearNodeB *current = node;

			node = node->m_bfmeNext;

			bfmeDeallocate(current, sizeof(BfmeClearNodeB));
		}

		m_bfmeNode->m_bfmeNext = m_bfmeNode;
		m_bfmeNode->m_bfmePrev = m_bfmeNode;
	}

	BfmeClearNodeB *m_bfmeNode;				// +0x00
};

class BfmeDBaseA
{
public:
	virtual ~BfmeDBaseA(void);				// retail 0x00033F6E

	BfmeClearListB m_bfmeList;				// +0x04
	char m_bfmePad[0x1C];					// +0x08
};

class BfmeDBaseB
{
public:
	virtual ~BfmeDBaseB(void) {}
};

class Gen_0042B9F0 : public BfmeDBaseA, public BfmeDBaseB
{
public:
	virtual ~Gen_0042B9F0(void);
};

// ??1Gen_0042B9F0@@UAE@XZ
Gen_0042B9F0::~Gen_0042B9F0(void)
{
	m_bfmeList.bfmeClear();
}
