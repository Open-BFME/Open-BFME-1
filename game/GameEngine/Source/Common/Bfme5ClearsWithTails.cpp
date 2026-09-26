// Two more vector clears that copy an empty range over themselves, each with
// work of its own around the walk.
//
// The first counts its elements instead of walking a cursor: the span is
// recomputed on every pass, so it is the condition of a for loop rather than a
// hoisted local, and the unsigned compares make the index unsigned even though
// the shift that divides the pointer difference is signed. It ends in a tail
// call, which is why the pops come before the jump.
//
// Two details of that one are worth keeping. The store of the new finish stays
// ahead of the load for the tail call only when it is written by a method of a
// member subobject; done at this level -- even from an inline method of this
// class, or through a pointer to the member -- MSVC sinks it past the load and
// the test. And the span and the element have to be reached through accessors
// on that subobject, otherwise the start pointer is kept in a register across
// the loop instead of being reloaded on every pass.
//
// The second stops an owned object first and deletes its elements by hand --
// the destructor call and the free are separate, so the element type's
// destructor is not virtual and the pointer stays in a callee-saved register
// across both calls.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0

class BfmeOwnedE
{
public:
	virtual ~BfmeOwnedE(void);				// slot +0x00

	void bfmeNotify(void);					// retail thunk 0x000263EB -> 0x003C9320
};

inline BfmeOwnedE **bfmeCopySlots(BfmeOwnedE **destination, BfmeOwnedE **first, BfmeOwnedE **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedE **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecE
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeOwnedE *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeClear(void)
	{
		m_bfmeFinish = bfmeCopySlots(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);
	}

	BfmeOwnedE **m_bfmeStart;				// +0x00
	BfmeOwnedE **m_bfmeFinish;				// +0x04
	BfmeOwnedE **m_bfmeEnd;					// +0x08
};

class Gen_003C0EF0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeVecE m_bfmeVector;					// +0x0C
	int m_bfmeGap[4];					// +0x18
	BfmeOwnedE *m_bfmeSink;					// +0x28
};

// ?bfmeClear@Gen_003C0EF0@@QAEXXZ
void Gen_003C0EF0::bfmeClear(void)
{
	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
		delete m_bfmeVector.bfmeAt(index);

	m_bfmeVector.bfmeClear();

	BfmeOwnedE *sink = m_bfmeSink;

	if (sink)
		sink->bfmeNotify();
}

class BfmeElemF
{
public:
	~BfmeElemF(void);					// retail thunk 0x000452FA -> 0x0037B990
};

inline BfmeElemF **bfmeCopyElems(BfmeElemF **destination, BfmeElemF **first, BfmeElemF **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeElemF **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeStopF
{
public:
	void bfmeStop(void);					// retail thunk 0x00015E2E -> 0x0037C600
};

class Gen_002901C0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[24];					// +0x00
	BfmeElemF **m_bfmeStart;				// +0x60
	BfmeElemF **m_bfmeFinish;				// +0x64
	BfmeElemF **m_bfmeEnd;					// +0x68
	BfmeStopF *m_bfmeStopper;				// +0x6C
};

// ?bfmeClear@Gen_002901C0@@QAEXXZ
void Gen_002901C0::bfmeClear(void)
{
	BfmeStopF *stopper = m_bfmeStopper;

	if (stopper)
	{
		stopper->bfmeStop();

		m_bfmeStopper = 0;
	}

	BfmeElemF **it = m_bfmeStart;

	while (it != m_bfmeFinish)
	{
		BfmeElemF *element = *it;

		if (element)
		{
			element->~BfmeElemF();

			bfmeFreeScalar(element);
		}

		++it;
	}

	m_bfmeFinish = bfmeCopyElems(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);
}
