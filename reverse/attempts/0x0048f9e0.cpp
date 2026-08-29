// ?bfmeDestroyRange@@YAXPAH0VBfmeAllocL@@@Z
// partial score=0.91 date=2026-08-29
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
void j_00036e9e(void);

struct BfmeDtorThunk
{
	void destroy(void);
};

// ?bfmeDestroyRange@@YAXPAH0VBfmeAllocL@@@Z
void __cdecl bfmeDestroyRange(int *first, int *last, BfmeAllocL allocator)
{
	while (first != last)
	{
		void *element = *(void **)first;
		if (element != 0)
		{
			typedef void (BfmeDtorThunk::*DtorFn)(void);
			union { void (*asVoid)(void); DtorFn asMember; } fnCast;
			fnCast.asVoid = j_00036e9e;
			(reinterpret_cast<BfmeDtorThunk *>(element)->*fnCast.asMember)();
			bfmeFreeScalar(element);
		}
		++first;
	}
}
