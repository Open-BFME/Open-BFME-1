// Six ring-block constructors.
//
// Each nulls its block pointer, allocates a block, zeroes the count, and then
// initialises the block: a byte, a dword, and two self-links that make it an
// empty circular list.
//
// The member is re-read before every one of those four stores rather than kept
// in a register, which is what writing them through the member expression
// gives -- the stores go through a pointer the compiler cannot prove disjoint
// from the member itself. The size chooses the allocator, as elsewhere, and
// the three bodies that take two arguments are two bytes longer than the three
// that take none.

typedef bool Bool;

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30

struct BfmeRingBlock
{
	Bool m_bfmeFlag;					// +0x00
	int m_bfmeWord;						// +0x04
	BfmeRingBlock *m_bfmeNext;				// +0x08
	BfmeRingBlock *m_bfmePrev;				// +0x0C
};


class Gen_00127680
{
public:
	Gen_00127680(int first, int second);

private:
	BfmeRingBlock *m_bfmeBlock;				// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_0012A720
{
public:
	Gen_0012A720(void);

private:
	BfmeRingBlock *m_bfmeBlock;				// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_00586540
{
public:
	Gen_00586540(int first, int second);

private:
	BfmeRingBlock *m_bfmeBlock;				// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_00587CD0
{
public:
	Gen_00587CD0(void);

private:
	BfmeRingBlock *m_bfmeBlock;				// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_00605500
{
public:
	Gen_00605500(int first, int second);

private:
	BfmeRingBlock *m_bfmeBlock;				// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_00605FF0
{
public:
	Gen_00605FF0(void);

private:
	BfmeRingBlock *m_bfmeBlock;				// +0x00
	int m_bfmeCount;					// +0x04
};

// ??0Gen_00127680@@QAE@HH@Z
Gen_00127680::Gen_00127680(int first, int second)
{
	m_bfmeBlock = 0;

	m_bfmeBlock = (BfmeRingBlock *)bfmeNewAlloc(0x84);

	m_bfmeCount = 0;

	m_bfmeBlock->m_bfmeFlag = false;
	m_bfmeBlock->m_bfmeWord = 0;
	m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
	m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
}

// ??0Gen_0012A720@@QAE@XZ
Gen_0012A720::Gen_0012A720(void)
{
	m_bfmeBlock = 0;

	m_bfmeBlock = (BfmeRingBlock *)bfmeNewAlloc(0x84);

	m_bfmeCount = 0;

	m_bfmeBlock->m_bfmeFlag = false;
	m_bfmeBlock->m_bfmeWord = 0;
	m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
	m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
}

// ??0Gen_00586540@@QAE@HH@Z
Gen_00586540::Gen_00586540(int first, int second)
{
	m_bfmeBlock = 0;

	m_bfmeBlock = (BfmeRingBlock *)bfmeAllocNode(0x50);

	m_bfmeCount = 0;

	m_bfmeBlock->m_bfmeFlag = false;
	m_bfmeBlock->m_bfmeWord = 0;
	m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
	m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
}

// ??0Gen_00587CD0@@QAE@XZ
Gen_00587CD0::Gen_00587CD0(void)
{
	m_bfmeBlock = 0;

	m_bfmeBlock = (BfmeRingBlock *)bfmeAllocNode(0x50);

	m_bfmeCount = 0;

	m_bfmeBlock->m_bfmeFlag = false;
	m_bfmeBlock->m_bfmeWord = 0;
	m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
	m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
}

// ??0Gen_00605500@@QAE@HH@Z
Gen_00605500::Gen_00605500(int first, int second)
{
	m_bfmeBlock = 0;

	m_bfmeBlock = (BfmeRingBlock *)bfmeAllocNode(0x70);

	m_bfmeCount = 0;

	m_bfmeBlock->m_bfmeFlag = false;
	m_bfmeBlock->m_bfmeWord = 0;
	m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
	m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
}

// ??0Gen_00605FF0@@QAE@XZ
Gen_00605FF0::Gen_00605FF0(void)
{
	m_bfmeBlock = 0;

	m_bfmeBlock = (BfmeRingBlock *)bfmeAllocNode(0x70);

	m_bfmeCount = 0;

	m_bfmeBlock->m_bfmeFlag = false;
	m_bfmeBlock->m_bfmeWord = 0;
	m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
	m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
}
