// A byte-element sized-vector constructor.
//
// Same family as the other sized-vector constructors, with three differences.
// The allocator comes first and the count second. The element is one byte, so
// there is no multiply anywhere and the largest count the allocator could
// serve is the whole address space -- which is why the guard compares against
// -1 and MSVC does not fold it away. And the count of zero writes nothing at
// all: the three pointers are already null from the member initialisers, so
// the stores sit inside the guard rather than after it.
//
// The zero test is written as greater-than-zero, not not-equal: that is the
// difference between the jbe retail emits and the je a not-equal gives.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

class BfmeAllocProxy1
{
public:
	BfmeAllocProxy1(void *allocator, char *data);		// retail 0x000281E6

	char *m_bfmeEnd;					// +0x00
};

class Gen_005C46C0
{
public:
	Gen_005C46C0(void *allocator, unsigned int count);

private:
	char *m_bfmeStart;					// +0x00
	char *m_bfmeFinish;					// +0x04
	BfmeAllocProxy1 m_bfmeStorage;				// +0x08
};

// ??0Gen_005C46C0@@QAE@PAXI@Z
Gen_005C46C0::Gen_005C46C0(void *allocator, unsigned int count)
	: m_bfmeStart(0), m_bfmeFinish(0), m_bfmeStorage(allocator, 0)
{
	if (count <= (unsigned int)-1 && count > 0)
	{
		char *block = (char *)bfmeAllocate(count);

		m_bfmeStart = block;
		m_bfmeFinish = block;
		m_bfmeStorage.m_bfmeEnd = block + count;
	}
}
