// Six sized-vector constructors initialize storage and allocate by element count.

void *__cdecl operator new(unsigned int bytes);

namespace _STL
{
class __new_alloc { public: static void *allocate(unsigned int bytes); };
}

class Gen_000f9420 { public: void *m(int allocator, int data); };
class Gen_003a6230 { public: void *m(int allocator, int data); };
class Gen_003a6250 { public: void *m(int allocator, int data); };
class Gen_003a62b0 { public: void *m(int allocator, int data); };
class Gen_0075d920 { public: void *m(int allocator, int data); };
class Gen_0075d9a0 { public: void *m(int allocator, int data); };


static __forceinline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return ::operator new(bytes);

	return _STL::__new_alloc::allocate(bytes);
}

struct BfmeElem_003A7A30 { int m_bfmeWords[9]; };

class BfmeAllocProxy_003A7A30
{
public:

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

// ??0Gen_003A7A30@@QAE@IPAX@Z
Gen_003A7A30::Gen_003A7A30(unsigned int count, void *allocator)
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	((Gen_003a6230 *)&m_bfmeStorage)->m((int)allocator, 0);
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
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	((Gen_003a6250 *)&m_bfmeStorage)->m((int)allocator, 0);
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
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	((Gen_003a62b0 *)&m_bfmeStorage)->m((int)allocator, 0);
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
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	((Gen_0075d920 *)&m_bfmeStorage)->m((int)allocator, 0);
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
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	((Gen_0075d9a0 *)&m_bfmeStorage)->m((int)allocator, 0);
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
	: m_bfmeStart(0), m_bfmeFinish(0)
{
	((Gen_000f9420 *)&m_bfmeStorage)->m((int)allocator, 0);
	BfmeElem_000F9F70 *block;

	if (count)
		block = (BfmeElem_000F9F70 *)bfmeAllocate(count * sizeof(BfmeElem_000F9F70));
	else
		block = 0;

	m_bfmeStart = block;
	m_bfmeFinish = block;
	m_bfmeStorage.m_bfmeEnd = block + count;
}
