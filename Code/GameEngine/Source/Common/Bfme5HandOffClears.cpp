// Two more clears: one hands every element to a singleton through a vftable
// slot, the other releases two strings after emptying.
//
// The singleton is re-read on every pass because the call can replace it, and
// the span is recomputed too, so both are source-level reads rather than
// hoisted locals. The second keeps its bound in a local reassigned from the
// member inside the loop, and reaches the two strings through the folded body
// AsciiString::releaseBuffer already sits on.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeElemY;

class BfmeSinkY
{
public:
	virtual ~BfmeSinkY(void);				// slot +0x00
	virtual void bfmeSlot04(void);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot0C(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot1C(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot2C(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot38(void);
	virtual void bfmeSlot3C(void);
	virtual void bfmeSlot40(void);
	virtual void bfmeSlot44(void);
	virtual void bfmeSlot48(void);
	virtual void bfmeHandOff(BfmeElemY *element);		// slot +0x4C
};

extern BfmeSinkY *g_bfmeSinkY;					// retail 0x012ED668

inline BfmeElemY **bfmeCopyElems(BfmeElemY **destination, BfmeElemY **first, BfmeElemY **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeElemY **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecY
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeElemY *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeErase(BfmeElemY **first, BfmeElemY **last)
	{
		m_bfmeFinish = bfmeCopyElems(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeElemY **m_bfmeStart;				// +0x00
	BfmeElemY **m_bfmeFinish;				// +0x04
	BfmeElemY **m_bfmeEnd;					// +0x08
};

class Gen_00613CC0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[166];					// +0x000
	BfmeVecY m_bfmeVector;					// +0x298
};

// ?bfmeClear@Gen_00613CC0@@QAEXXZ
void Gen_00613CC0::bfmeClear(void)
{
	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
		g_bfmeSinkY->bfmeHandOff(m_bfmeVector.bfmeAt(index));

	m_bfmeVector.bfmeClear();
}

class Gen_0081DBE0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
protected:
	void releaseBuffer(void);				// retail 0x00887940

private:
	void *m_bfmeData;					// +0x00

	friend class Gen_0081DBE0;
};

class BfmeOwnedZ
{
public:
	virtual ~BfmeOwnedZ(void);				// slot +0x00
};

inline BfmeOwnedZ **bfmeCopyOwned(BfmeOwnedZ **destination, BfmeOwnedZ **first, BfmeOwnedZ **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedZ **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecZ
{
public:
	void bfmeErase(BfmeOwnedZ **first, BfmeOwnedZ **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedZ **m_bfmeStart;				// +0x00
	BfmeOwnedZ **m_bfmeFinish;				// +0x04
	BfmeOwnedZ **m_bfmeEnd;					// +0x08
};

class Gen_0081DBE0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[2];					// +0x00
	AsciiString m_bfmeNameA;				// +0x08
	AsciiString m_bfmeNameB;				// +0x0C
	int m_bfmeCount;					// +0x10
	BfmeVecZ m_bfmeVector;					// +0x14
};

// ?bfmeClear@Gen_0081DBE0@@QAEXXZ
void Gen_0081DBE0::bfmeClear(void)
{
	BfmeOwnedZ **it = m_bfmeVector.m_bfmeStart;
	BfmeOwnedZ **last = m_bfmeVector.m_bfmeFinish;

	while (it != last)
	{
		delete *it;

		last = m_bfmeVector.m_bfmeFinish;

		++it;
	}

	m_bfmeVector.bfmeClear();

	m_bfmeNameA.releaseBuffer();

	m_bfmeNameB.releaseBuffer();

	m_bfmeCount = 0;
}
