// Seven sized-vector constructors.
//
// Each zeroes its two pointers, builds the proxy that holds the end pointer
// alongside the allocator, then allocates room for the requested count and
// points start, finish and end at it.
//
// The allocation picks its allocator by size: over 0x80 bytes goes to the
// large-block one, otherwise to the node one, with the size pushed once
// before the branch and each arm cleaning it. The count of zero takes a third
// arm that just yields a null block, and it has to be written as an explicit
// else -- initialising the local to zero up front hoists the xor above the
// test and loses five bytes.
//
// The element width shows up twice: once in the multiply that sizes the
// allocation and once in the scaled address that sets the end pointer. Four of
// the seven are twenty bytes wide, two are thirty-six and one is ninety-six.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

struct BfmeElem_000FD230 { int m_bfmeWords[9]; };

class BfmeAllocProxy_000FD230
{
public:
	BfmeAllocProxy_000FD230(void *allocator, BfmeElem_000FD230 *data);	// retail 0x00026B9D

	BfmeElem_000FD230 *m_bfmeEnd;					// +0x00
};

class Gen_000FD230
{
public:
	Gen_000FD230(unsigned int count, void *allocator);

private:
	BfmeElem_000FD230 *m_bfmeStart;				// +0x00
	BfmeElem_000FD230 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_000FD230 m_bfmeStorage;			// +0x08
};

struct BfmeElem_003A7A30 { int m_bfmeWords[9]; };

class BfmeAllocProxy_003A7A30
{
public:
	BfmeAllocProxy_003A7A30(void *allocator, BfmeElem_003A7A30 *data);	// retail 0x0002DE07

	BfmeElem_003A7A30 *m_bfmeEnd;					// +0x00
};

class Gen_003A7A30
{
public:
	Gen_003A7A30(unsigned int count, void *allocator);

private:
	BfmeElem_003A7A30 *m_bfmeStart;				// +0x00
	BfmeElem_003A7A30 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_003A7A30 m_bfmeStorage;			// +0x08
};

struct BfmeElem_003A7B10 { int m_bfmeWords[5]; };

class BfmeAllocProxy_003A7B10
{
public:
	BfmeAllocProxy_003A7B10(void *allocator, BfmeElem_003A7B10 *data);	// retail 0x0003B278

	BfmeElem_003A7B10 *m_bfmeEnd;					// +0x00
};

class Gen_003A7B10
{
public:
	Gen_003A7B10(unsigned int count, void *allocator);

private:
	BfmeElem_003A7B10 *m_bfmeStart;				// +0x00
	BfmeElem_003A7B10 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_003A7B10 m_bfmeStorage;			// +0x08
};

struct BfmeElem_003A7DC0 { int m_bfmeWords[5]; };

class BfmeAllocProxy_003A7DC0
{
public:
	BfmeAllocProxy_003A7DC0(void *allocator, BfmeElem_003A7DC0 *data);	// retail 0x0002BD78

	BfmeElem_003A7DC0 *m_bfmeEnd;					// +0x00
};

class Gen_003A7DC0
{
public:
	Gen_003A7DC0(unsigned int count, void *allocator);

private:
	BfmeElem_003A7DC0 *m_bfmeStart;				// +0x00
	BfmeElem_003A7DC0 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_003A7DC0 m_bfmeStorage;			// +0x08
};

struct BfmeElem_00760B20 { int m_bfmeWords[5]; };

class BfmeAllocProxy_00760B20
{
public:
	BfmeAllocProxy_00760B20(void *allocator, BfmeElem_00760B20 *data);	// retail 0x0001572B

	BfmeElem_00760B20 *m_bfmeEnd;					// +0x00
};

class Gen_00760B20
{
public:
	Gen_00760B20(unsigned int count, void *allocator);

private:
	BfmeElem_00760B20 *m_bfmeStart;				// +0x00
	BfmeElem_00760B20 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_00760B20 m_bfmeStorage;			// +0x08
};

struct BfmeElem_00760BE0 { int m_bfmeWords[5]; };

class BfmeAllocProxy_00760BE0
{
public:
	BfmeAllocProxy_00760BE0(void *allocator, BfmeElem_00760BE0 *data);	// retail 0x0002FB85

	BfmeElem_00760BE0 *m_bfmeEnd;					// +0x00
};

class Gen_00760BE0
{
public:
	Gen_00760BE0(unsigned int count, void *allocator);

private:
	BfmeElem_00760BE0 *m_bfmeStart;				// +0x00
	BfmeElem_00760BE0 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_00760BE0 m_bfmeStorage;			// +0x08
};

// ??0Gen_000FD230@@QAE@IPAX@Z
Gen_000FD230::Gen_000FD230(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_000FD230 *block;

	if (count)
		block = (BfmeElem_000FD230 *)bfmeAllocate(count * sizeof(BfmeElem_000FD230));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_003A7A30@@QAE@IPAX@Z
Gen_003A7A30::Gen_003A7A30(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_003A7A30 *block;

	if (count)
		block = (BfmeElem_003A7A30 *)bfmeAllocate(count * sizeof(BfmeElem_003A7A30));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_003A7B10@@QAE@IPAX@Z
Gen_003A7B10::Gen_003A7B10(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_003A7B10 *block;

	if (count)
		block = (BfmeElem_003A7B10 *)bfmeAllocate(count * sizeof(BfmeElem_003A7B10));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_003A7DC0@@QAE@IPAX@Z
Gen_003A7DC0::Gen_003A7DC0(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_003A7DC0 *block;

	if (count)
		block = (BfmeElem_003A7DC0 *)bfmeAllocate(count * sizeof(BfmeElem_003A7DC0));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_00760B20@@QAE@IPAX@Z
Gen_00760B20::Gen_00760B20(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_00760B20 *block;

	if (count)
		block = (BfmeElem_00760B20 *)bfmeAllocate(count * sizeof(BfmeElem_00760B20));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

// ??0Gen_00760BE0@@QAE@IPAX@Z
Gen_00760BE0::Gen_00760BE0(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_00760BE0 *block;

	if (count)
		block = (BfmeElem_00760BE0 *)bfmeAllocate(count * sizeof(BfmeElem_00760BE0));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}

struct BfmeElem_000F9F70 { int m_bfmeWords[24]; };

class BfmeAllocProxy_000F9F70
{
public:
	BfmeAllocProxy_000F9F70(void *allocator, BfmeElem_000F9F70 *data);	// retail 0x00006F5F

	BfmeElem_000F9F70 *m_bfmeEnd;				// +0x00
};

class Gen_000F9F70
{
public:
	Gen_000F9F70(unsigned int count, void *allocator);

private:
	BfmeElem_000F9F70 *m_bfmeStart;				// +0x00
	BfmeElem_000F9F70 *m_bfmeFinish;				// +0x04
	BfmeAllocProxy_000F9F70 m_bfmeStorage;			// +0x08
};

// ??0Gen_000F9F70@@QAE@IPAX@Z
Gen_000F9F70::Gen_000F9F70(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	BfmeElem_000F9F70 *block;

	if (count)
		block = (BfmeElem_000F9F70 *)bfmeAllocate(count * sizeof(BfmeElem_000F9F70));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}
