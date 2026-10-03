// Destroy the non-null elements in a half-open range and release their
// storage.  The allocator object is passed by value by the retail caller.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

class BfmeAllocL
{
public:
	BfmeAllocL(void)
	{
		m_bfmeTag = 0;
	}
	BfmeAllocL(const BfmeAllocL &that)
	{
		m_bfmeTag = that.m_bfmeTag;
	}

	char m_bfmeTag;
};

class BfmeObj927BEntry
{
public:
	unsigned char m_bfmePad[4];
	void *m_bfmeDisplayString;
};

class BfmeObj927B
{
public:
	~BfmeObj927B();
	void bfmeDtor927B();

private:
	_STL::vector<BfmeObj927BEntry *> m_bfmeEntries;
};

void __cdecl operator delete(void *block);			// retail 0x00881EB0

struct BfmeDtorThunk
{
	void destroy(void);
};

// The return byte keeps the by-value allocator live through the shared retail
// epilogue; its only known caller intentionally ignores the value.
// ?bfmeDestroyRange@@YADPAH0VBfmeAllocL@@@Z
char __cdecl bfmeDestroyRange(int *first, int *last, BfmeAllocL allocator)
{
	while (first != last)
	{
		BfmeObj927B *element = (BfmeObj927B *)*first;

		if (element)
		{
			element->BfmeObj927B::~BfmeObj927B();
			operator delete(element);
		}

		++first;
	}

	return allocator.m_bfmeTag;
}
