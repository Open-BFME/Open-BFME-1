// A based list constructor.
//
// The base runs first, then the most-derived vftable goes in, then the list
// member builds its sentinel. Everything after that is the body: two pointers
// nulled and the list cleared.
//
// The two nulls sit after the list member is built rather than before it, so
// they are body statements and not member initialisers -- members would have
// been initialised in declaration order, ahead of the list at +0x10.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeCtorNodeD
{
	BfmeCtorNodeD *m_bfmeNext;				// +0x00
	BfmeCtorNodeD *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeCtorListD
{
public:
	BfmeCtorListD(void)
	{
		m_bfmeNode = 0;

		BfmeCtorNodeD *node = (BfmeCtorNodeD *)bfmeAllocNode(sizeof(BfmeCtorNodeD));

		node->m_bfmeNext = node;
		node->m_bfmePrev = node;

		m_bfmeNode = node;
	}

	~BfmeCtorListD(void);

	void bfmeClear(void)
	{
		BfmeCtorNodeD *node = m_bfmeNode->m_bfmeNext;

		while (node != m_bfmeNode)
		{
			BfmeCtorNodeD *current = node;

			node = node->m_bfmeNext;

			bfmeDeallocate(current, sizeof(BfmeCtorNodeD));
		}

		m_bfmeNode->m_bfmeNext = m_bfmeNode;
		m_bfmeNode->m_bfmePrev = m_bfmeNode;
	}

	BfmeCtorNodeD *m_bfmeNode;				// +0x00
};

class BfmeCtorBaseD
{
public:
	BfmeCtorBaseD(void);					// retail 0x009A1A30
	virtual ~BfmeCtorBaseD(void);

private:
	int m_bfmeField;					// +0x04
};

struct BfmeArrayElementD
{
	char m_bfmeData[0x0c];

	~BfmeArrayElementD(void) {}
};

class Gen_000FDA80 : public BfmeCtorBaseD
{
public:
	Gen_000FDA80(void);
	virtual ~Gen_000FDA80(void);

private:
	BfmeArrayElementD *m_bfmeA;			// +0x08
	void *m_bfmeB;						// +0x0C
	BfmeCtorListD m_bfmeList;				// +0x10
};

// ??0Gen_000FDA80@@QAE@XZ
Gen_000FDA80::Gen_000FDA80(void)
{
	m_bfmeA = 0;
	m_bfmeB = 0;

	m_bfmeList.bfmeClear();
}

// ??1Gen_000FDA80@@UAE@XZ
Gen_000FDA80::~Gen_000FDA80(void)
{
	if (m_bfmeA)
	{
		delete[] m_bfmeA;
		m_bfmeA = 0;
		m_bfmeB = 0;
	}
}
