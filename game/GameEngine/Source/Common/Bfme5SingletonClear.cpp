// A vector clear that hands every element to a singleton before emptying, and
// one that swaps its vector aside first.
//
// The singleton pointer is loaded once ahead of the loop and reloaded after
// each call, so the test at the top of the loop is a real source guard rather
// than a hoisted one: the callee can replace it. The span is recomputed on
// every pass, which makes it the condition of a for loop, and the unsigned
// compares make the index unsigned.
//
// In the second, the two inlined halves of the swap have to go through a
// helper taking references. Written as three statements in the body of the
// swap they come out in a different order: MSVC pulls the second pair's load
// of the other vector ahead of the first pair's second store.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class BfmeItemH
{
public:
	int m_bfmePad[2];					// +0x00
	int m_bfmeHandle;					// +0x08
};

class BfmeSingletonH
{
public:
	void bfmeRemove(int handle);				// retail thunk 0x00010FFA -> 0x003C6D40
};

extern BfmeSingletonH *g_bfmeSingletonH;			// retail 0x012F706C

inline BfmeItemH **bfmeCopyItems(BfmeItemH **destination, BfmeItemH **first, BfmeItemH **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeItemH **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecH
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeItemH *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeErase(BfmeItemH **first, BfmeItemH **last)
	{
		m_bfmeFinish = bfmeCopyItems(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeItemH **m_bfmeStart;				// +0x00
	BfmeItemH **m_bfmeFinish;				// +0x04
	BfmeItemH **m_bfmeEnd;					// +0x08
};

class Gen_003C0DB0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[14];					// +0x00
	BfmeVecH m_bfmeVector;					// +0x38
};

// ?bfmeClear@Gen_003C0DB0@@QAEXXZ
void Gen_003C0DB0::bfmeClear(void)
{
	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
	{
		if (g_bfmeSingletonH)
			g_bfmeSingletonH->bfmeRemove(m_bfmeVector.bfmeAt(index)->m_bfmeHandle);
	}

	m_bfmeVector.bfmeClear();
}

class BfmeOwnedI
{
public:
	virtual ~BfmeOwnedI(void);				// slot +0x00
};

void __cdecl bfmeSwapEnds(BfmeOwnedI ***left, BfmeOwnedI ***right);	// retail thunk 0x00032FE7 -> 0x00432FE7

inline BfmeOwnedI **bfmeCopyOwned(BfmeOwnedI **destination, BfmeOwnedI **first, BfmeOwnedI **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedI **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

inline void bfmeSwapSlot(BfmeOwnedI **&left, BfmeOwnedI **&right)
{
	BfmeOwnedI **slot = left;

	left = right;
	right = slot;
}

class BfmeVecI
{
public:
	void bfmeSwap(BfmeVecI *other)
	{
		bfmeSwapSlot(m_bfmeStart, other->m_bfmeStart);
		bfmeSwapSlot(m_bfmeFinish, other->m_bfmeFinish);

		bfmeSwapEnds(&m_bfmeEnd, &other->m_bfmeEnd);
	}

	void bfmeErase(BfmeOwnedI **first, BfmeOwnedI **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedI **m_bfmeStart;				// +0x00
	BfmeOwnedI **m_bfmeFinish;				// +0x04
	BfmeOwnedI **m_bfmeEnd;					// +0x08
};

class Gen_003C1190
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[20];					// +0x00
	BfmeVecI m_bfmeSpare;					// +0x50
	BfmeVecI m_bfmeVector;					// +0x5C
};

// ?bfmeClear@Gen_003C1190@@QAEXXZ
void Gen_003C1190::bfmeClear(void)
{
	m_bfmeSpare.bfmeSwap(&m_bfmeVector);

	BfmeOwnedI **it = m_bfmeVector.m_bfmeStart;
	BfmeOwnedI **last = m_bfmeVector.m_bfmeFinish;

	while (it != last)
	{
		delete *it;

		last = m_bfmeVector.m_bfmeFinish;

		++it;
	}

	m_bfmeVector.bfmeClear();
}
