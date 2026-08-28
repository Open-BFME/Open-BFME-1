// Destroy the non-null elements in a half-open range and release their
// storage.  The allocator object is passed by value by the retail caller.

class BfmeAllocL
{
public:
	BfmeAllocL(void)
	{
		m_bfmeTag = 0;
	}

	char m_bfmeTag;
};

class Gen_dtor_0048f590
{
public:
	virtual ~Gen_dtor_0048f590(void);				// ILT 0x00036E9E
};

void __cdecl bfmeFreeScalar(void *block);				// retail 0x00881EB0

// The return byte keeps the by-value allocator live through the shared retail
// epilogue; its only known caller intentionally ignores the value.
// ?bfmeDestroyRange@@YADPAH0VBfmeAllocL@@@Z
char __cdecl bfmeDestroyRange(int *first, int *last, BfmeAllocL allocator)
{
	while (first != last)
	{
		Gen_dtor_0048f590 *element = (Gen_dtor_0048f590 *)*first;

		if (element)
		{
			element->Gen_dtor_0048f590::~Gen_dtor_0048f590();
			bfmeFreeScalar(element);
		}

		++first;
	}

	return allocator.m_bfmeTag;
}
