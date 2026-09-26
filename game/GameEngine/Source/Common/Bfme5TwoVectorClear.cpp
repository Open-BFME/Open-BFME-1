// A body that deletes the elements of two vectors and then empties both.
//
// The two counted loops come first and the two clears after, which is why the
// copier is only loaded into a register once the first clear is reached: two
// calls through the memmove import in one body get it hoisted.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeOwnedT
{
public:
	virtual ~BfmeOwnedT(void);				// slot +0x00
};

inline BfmeOwnedT **bfmeCopyOwned(BfmeOwnedT **destination, BfmeOwnedT **first, BfmeOwnedT **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedT **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecT
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeOwnedT *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeErase(BfmeOwnedT **first, BfmeOwnedT **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedT **m_bfmeStart;				// +0x00
	BfmeOwnedT **m_bfmeFinish;				// +0x04
	BfmeOwnedT **m_bfmeEnd;					// +0x08
};

class Gen_003C0F70
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[20];					// +0x00
	BfmeVecT m_bfmeFirst;					// +0x50
	BfmeVecT m_bfmeSecond;					// +0x5C
};

// ?bfmeClear@Gen_003C0F70@@QAEXXZ
void Gen_003C0F70::bfmeClear(void)
{
	for (unsigned int index = 0; index < m_bfmeFirst.bfmeSize(); ++index)
		delete m_bfmeFirst.bfmeAt(index);

	for (unsigned int other = 0; other < m_bfmeSecond.bfmeSize(); ++other)
		delete m_bfmeSecond.bfmeAt(other);

	m_bfmeFirst.bfmeClear();

	m_bfmeSecond.bfmeClear();
}
