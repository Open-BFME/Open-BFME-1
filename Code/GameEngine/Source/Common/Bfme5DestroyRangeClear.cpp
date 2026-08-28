// A clear that destroys its range through an out-of-line helper before
// emptying the vector.
//
// The helper takes the two ends and an empty object by value: MSVC gives that
// object a stack slot, writes its one byte there and pushes the whole word,
// which is why the prologue reserves four bytes it otherwise never uses.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class BfmeAllocL
{
public:
	BfmeAllocL(void)
	{
		m_bfmeTag = 0;
	}

	char m_bfmeTag;
};

char __cdecl bfmeDestroyRange(int *first, int *last, BfmeAllocL allocator);	// retail thunk 0x0002376D -> 0x0042376D

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecL
{
public:
	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyRange(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class BfmeTargetL
{
public:
	int m_bfmeHead[6];					// +0x00
	int m_bfmeColour;					// +0x18
};

class Gen_0048FA30
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[2];					// +0x00
	BfmeTargetL *m_bfmeTarget;				// +0x08
	BfmeVecL m_bfmeVector;					// +0x0C
	int m_bfmeCount;					// +0x18
	int m_bfmeIndex;					// +0x1C
	int m_bfmeState;					// +0x20
};

// ?bfmeClear@Gen_0048FA30@@QAEXXZ
void Gen_0048FA30::bfmeClear(void)
{
	m_bfmeCount = 0;
	m_bfmeIndex = 0;
	m_bfmeState = 0;

	bfmeDestroyRange(m_bfmeVector.m_bfmeStart, m_bfmeVector.m_bfmeFinish, BfmeAllocL());

	m_bfmeVector.bfmeClear();

	m_bfmeTarget->m_bfmeColour = 0xFF000000;
}
