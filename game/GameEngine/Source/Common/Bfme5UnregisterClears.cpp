// Two clears that give each element up before deleting it.
//
// Neither delete tests for null: the guard around the whole body of the loop
// has already done it, so MSVC drops the test the delete would emit. The first
// keeps its bound in a local reassigned from the member inside the loop, which
// is what puts it in a register for the entry test too; the second reads the
// member both times.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class BfmeOwnedP
{
public:
	virtual ~BfmeOwnedP(void);				// slot +0x00
};

void __cdecl bfmeUnregister(BfmeOwnedP *element);		// retail thunk 0x00006500 -> 0x00406500

class BfmeManagerP
{
public:
	void bfmeRemove(BfmeOwnedP *element);			// retail thunk 0x000218B9 -> 0x004218B9
};

extern BfmeManagerP *g_bfmeManagerP;				// retail 0x012F0898

inline BfmeOwnedP **bfmeCopyOwned(BfmeOwnedP **destination, BfmeOwnedP **first, BfmeOwnedP **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedP **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecP
{
public:
	void bfmeErase(BfmeOwnedP **first, BfmeOwnedP **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedP **m_bfmeStart;				// +0x00
	BfmeOwnedP **m_bfmeFinish;				// +0x04
	BfmeOwnedP **m_bfmeEnd;					// +0x08
};

class Gen_00371120
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[58];					// +0x000
	BfmeVecP m_bfmeVector;					// +0x0E8
};

// ?bfmeClear@Gen_00371120@@QAEXXZ
void Gen_00371120::bfmeClear(void)
{
	BfmeOwnedP **it = m_bfmeVector.m_bfmeStart;
	BfmeOwnedP **last = m_bfmeVector.m_bfmeFinish;

	while (it != last)
	{
		BfmeOwnedP *element = *it;

		if (element)
		{
			bfmeUnregister(element);

			g_bfmeManagerP->bfmeRemove(element);

			delete element;
		}

		last = m_bfmeVector.m_bfmeFinish;

		++it;
	}

	m_bfmeVector.bfmeClear();
}

class BfmeSubQ
{
public:
	virtual ~BfmeSubQ(void);				// slot +0x00
	virtual void bfmeRelease(void);				// slot +0x04
};

class Gen_0055CCE0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[150];					// +0x000
	bool m_bfmeFlag;					// +0x258
	BfmeVecP m_bfmeVector;					// +0x25C
	int m_bfmeGap;						// +0x268
	BfmeSubQ *m_bfmeSub;					// +0x26C
};

// ?bfmeClear@Gen_0055CCE0@@QAEXXZ
void Gen_0055CCE0::bfmeClear(void)
{
	m_bfmeFlag = false;

	BfmeSubQ *sub = m_bfmeSub;

	if (sub)
	{
		sub->bfmeRelease();

		m_bfmeSub = 0;
	}

	BfmeOwnedP **it = m_bfmeVector.m_bfmeStart;

	while (it != m_bfmeVector.m_bfmeFinish)
	{
		delete *it;

		++it;
	}

	m_bfmeVector.bfmeClear();
}
