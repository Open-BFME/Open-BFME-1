// A destructor that deletes what its vector holds, empties it and then lets
// the vector member go away.
//
// The unwind state word tells the parts apart: it holds 1 while the body runs
// -- the delete walk and the clear -- drops to 0 for the member's own
// destructor, which is the release of the block by size, and returns to -1
// before the base destructor. The most-derived vftable goes in at the entry
// because the base is polymorphic.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeOwnedAA
{
public:
	virtual ~BfmeOwnedAA(void);				// slot +0x00
};

inline BfmeOwnedAA **bfmeCopyOwned(BfmeOwnedAA **destination, BfmeOwnedAA **first, BfmeOwnedAA **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedAA **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecAA
{
public:
	~BfmeVecAA(void)
	{
		BfmeOwnedAA **start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(BfmeOwnedAA *) * (m_bfmeEnd - start));
	}

	void bfmeErase(BfmeOwnedAA **first, BfmeOwnedAA **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedAA **m_bfmeStart;				// +0x00
	BfmeOwnedAA **m_bfmeFinish;				// +0x04
	BfmeOwnedAA **m_bfmeEnd;				// +0x08
};

class BfmeBaseAA
{
public:
	virtual ~BfmeBaseAA(void);				// retail 0x009A1A40

private:
	int m_bfmeField;					// +0x04
};

class Gen_0039C6D0 : public BfmeBaseAA
{
public:
	virtual ~Gen_0039C6D0(void);

private:
	BfmeVecAA m_bfmeVector;					// +0x08
};

// ??1Gen_0039C6D0@@UAE@XZ
Gen_0039C6D0::~Gen_0039C6D0(void)
{
	BfmeOwnedAA **it = m_bfmeVector.m_bfmeStart;
	BfmeOwnedAA **last = m_bfmeVector.m_bfmeFinish;

	while (it != last)
	{
		delete *it;

		last = m_bfmeVector.m_bfmeFinish;

		++it;
	}

	m_bfmeVector.bfmeClear();
}
