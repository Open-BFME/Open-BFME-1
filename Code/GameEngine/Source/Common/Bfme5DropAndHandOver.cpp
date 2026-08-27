// A body that drops every element of two vectors, empties the second, hands
// the first to the object in front of it and drops one more element.
//
// Dropping an element is one inlined helper appearing four times: an owned
// element is deleted through its vftable, a borrowed one gives its reference
// back and keeps what the release returns. Neither arm tests the element for
// null, so the source never did.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeRefAB
{
public:
	virtual ~BfmeRefAB(void);

	__declspec(noinline) BfmeRefAB *bfmeRelease(void);	// retail thunk 0x00032D1C -> 0x00432D1C

	BfmeRefAB *m_bfmeRef;
	bool m_bfmeOwned;
};

// ?bfmeRelease@BfmeRefAB@@QAEPAV1@XZ
__declspec(noinline) BfmeRefAB *BfmeRefAB::bfmeRelease(void)
{
	if (m_bfmeOwned)
	{
		delete this;
		return 0;
	}
	if (m_bfmeRef)
		m_bfmeRef = m_bfmeRef->bfmeRelease();
	return this;
}

class BfmeElemAB
{
public:
	virtual ~BfmeElemAB(void);				// slot +0x00

	BfmeRefAB *m_bfmeRef;					// +0x04
	bool m_bfmeOwned;					// +0x08
};

inline void bfmeDrop(BfmeElemAB *element)
{
	if (element->m_bfmeOwned)
	{
		delete element;
	}
	else if (element->m_bfmeRef)
	{
		element->m_bfmeRef = element->m_bfmeRef->bfmeRelease();
	}
}

inline BfmeElemAB **bfmeCopyElems(BfmeElemAB **destination, BfmeElemAB **first, BfmeElemAB **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeElemAB **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecAB
{
public:
	void bfmeErase(BfmeElemAB **first, BfmeElemAB **last)
	{
		m_bfmeFinish = bfmeCopyElems(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeElemAB **m_bfmeStart;				// +0x00
	BfmeElemAB **m_bfmeFinish;				// +0x04
	BfmeElemAB **m_bfmeEnd;					// +0x08
};

class BfmeSinkAB
{
public:
	void bfmeTake(BfmeVecAB *vector);			// retail thunk 0x00014E1B -> 0x00414E1B

	int m_bfmeFields[3];					// +0x00
};

class Gen_003CFC90
{
public:
	void bfmeRelease(void);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeSinkAB m_bfmeSink;					// +0x0C
	BfmeVecAB m_bfmeFirst;					// +0x18
	BfmeVecAB m_bfmeSecond;					// +0x24
	BfmeElemAB *m_bfmeExtra;				// +0x30
};

// ?bfmeRelease@Gen_003CFC90@@QAEXXZ
void Gen_003CFC90::bfmeRelease(void)
{
	BfmeElemAB **it = m_bfmeFirst.m_bfmeStart;

	while (it != m_bfmeFirst.m_bfmeFinish)
	{
		bfmeDrop(*it);

		++it;
	}

	BfmeElemAB **other = m_bfmeSecond.m_bfmeStart;

	while (other != m_bfmeSecond.m_bfmeFinish)
	{
		bfmeDrop(*other);

		++other;
	}

	m_bfmeSecond.bfmeClear();

	m_bfmeSink.bfmeTake(&m_bfmeFirst);

	bfmeDrop(m_bfmeExtra);
}
