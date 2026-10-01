// Six more sized-vector constructors, over widths a scaled address cannot
// express.
//
// Same shape as the ones whose element width folds into a lea: zero the two
// pointers, build the end-pointer proxy, allocate for the count and point
// start, finish and end at the block, with the count of zero taking its own
// arm. Here the width is 0x8C, 0xB4, 0xBC, 0xDC or 0x128, so both the size and
// the end offset come out of an imul, and the end pointer is stored before the
// other two rather than after -- the multiply is what the scheduler works
// around.
//
// The narrowest of them, at 0x38, is thirty bytes longer than the rest: its
// multiply is small enough that MSVC duplicates the whole tail into each arm
// instead of jumping to a shared one. That falls out of the same source.

void *__cdecl operator new(unsigned int bytes);				// retail 0x00881F30
namespace _STL { class __new_alloc { public: static void *allocate(unsigned int bytes); }; }			// retail 0x0082E540

static inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return ::operator new(bytes);

	return _STL::__new_alloc::allocate(bytes);
}

#define BFME_INITIALIZE_ALLOC_PROXY(ROW, STORAGE, ALLOCATOR) ((ROW *)&(STORAGE))->m((int)(ALLOCATOR), 0)

struct BfmeElem_0013B110 { char m_bfmeBytes[0x128]; };

class Gen_0013a400
{
public:
	void *m(int allocator, int data);
};

class BfmeAllocProxy_0013B110
{
public:
	BfmeElem_0013B110 *m_bfmeEnd;					// +0x00
};

class Gen_0013B110
{
public:
	Gen_0013B110(unsigned int count, void *allocator);

private:
	BfmeElem_0013B110 *m_bfmeStart;				// +0x00
	BfmeElem_0013B110 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_0013B110 m_bfmeStorage;			// +0x08
};

struct BfmeElem_0013B200 { char m_bfmeBytes[0xBC]; };

class Gen_0013a420
{
public:
	void *m(int allocator, int data);
};

class BfmeAllocProxy_0013B200
{
public:
	BfmeElem_0013B200 *m_bfmeEnd;					// +0x00
};

class Gen_0013B200
{
public:
	Gen_0013B200(unsigned int count, void *allocator);

private:
	BfmeElem_0013B200 *m_bfmeStart;				// +0x00
	BfmeElem_0013B200 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_0013B200 m_bfmeStorage;			// +0x08
};

struct BfmeElem_001938A0 { char m_bfmeBytes[0x8C]; };

class Gen_00193110
{
public:
	void *m(int allocator, int data);
};

class BfmeAllocProxy_001938A0
{
public:
	BfmeElem_001938A0 *m_bfmeEnd;					// +0x00
};

class Gen_001938A0
{
public:
	Gen_001938A0(unsigned int count, void *allocator);

private:
	BfmeElem_001938A0 *m_bfmeStart;				// +0x00
	BfmeElem_001938A0 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_001938A0 m_bfmeStorage;			// +0x08
};

struct BfmeElem_003617C0 { char m_bfmeBytes[0xB4]; };

class Gen_003616a0
{
public:
	void *m(int allocator, int data);
};

class BfmeAllocProxy_003617C0
{
public:
	BfmeElem_003617C0 *m_bfmeEnd;					// +0x00
};

class Gen_003617C0
{
public:
	Gen_003617C0(unsigned int count, void *allocator);

private:
	BfmeElem_003617C0 *m_bfmeStart;				// +0x00
	BfmeElem_003617C0 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_003617C0 m_bfmeStorage;			// +0x08
};

struct BfmeElem_003B3B40 { char m_bfmeBytes[0xDC]; };

class Gen_003a6680
{
public:
	void *m(int allocator, int data);
};

class BfmeAllocProxy_003B3B40
{
public:
	BfmeElem_003B3B40 *m_bfmeEnd;					// +0x00
};

class Gen_003B3B40
{
public:
	Gen_003B3B40(unsigned int count, void *allocator);

private:
	BfmeElem_003B3B40 *m_bfmeStart;				// +0x00
	BfmeElem_003B3B40 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_003B3B40 m_bfmeStorage;			// +0x08
};

// ??0Gen_0013B110@@QAE@IPAX@Z
Gen_0013B110::Gen_0013B110(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	BFME_INITIALIZE_ALLOC_PROXY(Gen_0013a400, m_bfmeStorage, allocator);
	BfmeElem_0013B110 *block;

	if (count)
		block = (BfmeElem_0013B110 *)bfmeAllocate(count * sizeof(BfmeElem_0013B110));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_0013B200@@QAE@IPAX@Z
Gen_0013B200::Gen_0013B200(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	BFME_INITIALIZE_ALLOC_PROXY(Gen_0013a420, m_bfmeStorage, allocator);
	BfmeElem_0013B200 *block;

	if (count)
		block = (BfmeElem_0013B200 *)bfmeAllocate(count * sizeof(BfmeElem_0013B200));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_001938A0@@QAE@IPAX@Z
Gen_001938A0::Gen_001938A0(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	BFME_INITIALIZE_ALLOC_PROXY(Gen_00193110, m_bfmeStorage, allocator);
	BfmeElem_001938A0 *block;

	if (count)
		block = (BfmeElem_001938A0 *)bfmeAllocate(count * sizeof(BfmeElem_001938A0));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_003617C0@@QAE@IPAX@Z
Gen_003617C0::Gen_003617C0(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	BFME_INITIALIZE_ALLOC_PROXY(Gen_003616a0, m_bfmeStorage, allocator);
	BfmeElem_003617C0 *block;

	if (count)
		block = (BfmeElem_003617C0 *)bfmeAllocate(count * sizeof(BfmeElem_003617C0));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_003B3B40@@QAE@IPAX@Z
Gen_003B3B40::Gen_003B3B40(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	BFME_INITIALIZE_ALLOC_PROXY(Gen_003a6680, m_bfmeStorage, allocator);
	BfmeElem_003B3B40 *block;

	if (count)
		block = (BfmeElem_003B3B40 *)bfmeAllocate(count * sizeof(BfmeElem_003B3B40));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

struct BfmeElem_00760CA0 { char m_bfmeBytes[0x38]; };

class Gen_0075da60
{
public:
	void *m(int allocator, int data);
};

class BfmeAllocProxy_00760CA0
{
public:
	BfmeElem_00760CA0 *m_bfmeEnd;				// +0x00
};

class Gen_00760CA0
{
public:
	Gen_00760CA0(unsigned int count, void *allocator);

private:
	BfmeElem_00760CA0 *m_bfmeStart;				// +0x00
	BfmeElem_00760CA0 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_00760CA0 m_bfmeStorage;			// +0x08
};

// ??0Gen_00760CA0@@QAE@IPAX@Z
Gen_00760CA0::Gen_00760CA0(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	BFME_INITIALIZE_ALLOC_PROXY(Gen_0075da60, m_bfmeStorage, allocator);
	BfmeElem_00760CA0 *block;

	if (count)
		block = (BfmeElem_00760CA0 *)bfmeAllocate(count * sizeof(BfmeElem_00760CA0));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}
