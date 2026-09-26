// Two more destructors that copy an empty range over themselves.
//
// Both call a copy helper with the same member for both ends of its range, so
// the comparison of a register against itself and the subtraction that yields
// zero survive inlining. One copies elements with a counted loop, the other
// bytes through the imported copier; in the counted one the tautology shows up
// after the shift that turns a pointer difference into a count.
//
// The second also deletes every element first. Its bound is kept in a local
// that is reassigned from the member inside the loop -- the delete can move
// the member, so the reload is real, and the local is what puts the bound in a
// register for the entry test as well.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

struct BfmeElem8P { int m_bfmeA; int m_bfmeB; };

inline BfmeElem8P *bfmeCopyElems(BfmeElem8P *destination, const BfmeElem8P *first, const BfmeElem8P *last)
{
	int count = last - first;

	if (count > 0)
	{
		do
		{
			*destination = *first;

			++first;
			++destination;
		}
		while (--count);
	}

	return destination;
}

class Gen_003BA860
{
public:
	~Gen_003BA860(void);

private:
	BfmeElem8P *m_bfmeStart;				// +0x00
	BfmeElem8P *m_bfmeFinish;				// +0x04
	BfmeElem8P *m_bfmeEnd;					// +0x08
};

// ??1Gen_003BA860@@QAE@XZ
Gen_003BA860::~Gen_003BA860(void)
{
	m_bfmeFinish = bfmeCopyElems(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);

	BfmeElem8P *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeElem8P) * (m_bfmeEnd - start));
}

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);


class BfmeOwnedP
{
public:
	virtual ~BfmeOwnedP(void);				// slot +0x00
};

inline BfmeOwnedP **bfmeCopySlots(BfmeOwnedP **destination, BfmeOwnedP **first, BfmeOwnedP **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedP **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecOfPtr
{
public:
	~BfmeVecOfPtr(void)
	{
		BfmeOwnedP **start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(BfmeOwnedP *) * (m_bfmeEnd - start));
	}

	BfmeOwnedP **m_bfmeStart;				// +0x00
	BfmeOwnedP **m_bfmeFinish;				// +0x04
	BfmeOwnedP **m_bfmeEnd;					// +0x08
};

class BfmeBaseO
{
public:
	virtual ~BfmeBaseO(void) {}
};

class Gen_007875E0 : public BfmeBaseO
{
public:
	virtual ~Gen_007875E0(void);

private:
	BfmeVecOfPtr m_bfmeVector;				// +0x04
};

// ??1Gen_007875E0@@UAE@XZ
Gen_007875E0::~Gen_007875E0(void)
{
	BfmeOwnedP **it = m_bfmeVector.m_bfmeStart;
	BfmeOwnedP **last = m_bfmeVector.m_bfmeFinish;

	while (it != last)
	{
		delete *it;

		last = m_bfmeVector.m_bfmeFinish;

		++it;
	}

	m_bfmeVector.m_bfmeFinish = bfmeCopySlots(m_bfmeVector.m_bfmeStart,
		m_bfmeVector.m_bfmeFinish, m_bfmeVector.m_bfmeFinish);
}
