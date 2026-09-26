// A three-member destructor.
//
// The body is one statement -- clear the first list -- and everything after it
// is the three members going away in reverse declaration order, then the
// base's vftable going back in as it is destroyed inline.
//
// The state word counts the members: three while the body runs, then two, one
// and zero as each is destroyed, and those later stores are byte-wide because
// only the low byte changes. Two of the three members are the same type, which
// is why the first and last destructor calls share a target.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeNodeE
{
	BfmeNodeE *m_bfmeNext;					// +0x00
	BfmeNodeE *m_bfmePrev;					// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeListE
{
public:
	~BfmeListE(void);					// retail 0x00013449

	void bfmeClear(void)
	{
		BfmeNodeE *node = m_bfmeNode->m_bfmeNext;

		while (node != m_bfmeNode)
		{
			BfmeNodeE *current = node;

			node = node->m_bfmeNext;

			bfmeDeallocate(current, sizeof(BfmeNodeE));
		}

		m_bfmeNode->m_bfmeNext = m_bfmeNode;
		m_bfmeNode->m_bfmePrev = m_bfmeNode;
	}

	BfmeNodeE *m_bfmeNode;					// +0x00
};

class BfmeThingE
{
public:
	~BfmeThingE(void);					// retail 0x0000E68D

private:
	int m_bfmeField;
};

class BfmeBaseE
{
public:
	virtual ~BfmeBaseE(void) {}
};

class Gen_000F8A40 : public BfmeBaseE
{
public:
	virtual ~Gen_000F8A40(void);

private:
	BfmeListE m_bfmeFirst;					// +0x04
	BfmeThingE m_bfmeSecond;				// +0x08
	BfmeListE m_bfmeThird;					// +0x0C
};

// ??1Gen_000F8A40@@UAE@XZ
Gen_000F8A40::~Gen_000F8A40(void)
{
	m_bfmeFirst.bfmeClear();
}
