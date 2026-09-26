// Two vector destroys that hand the range to a destroy helper.
//
// Each passes start, finish and the address of a one-byte local to the helper,
// then frees the block by size the same way the matching allocate chooses its
// allocator. That third argument is a lea into the four bytes the prologue
// reserved -- an uninitialised char whose address is all the callee wants.
//
// The element is four bytes wide, which the shift pair around the size names,
// and each arm of the size test carries its own epilogue.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

void __cdecl bfmeDestroyRange(int *first, int *last, char *tag);	// retail 0x000247E9

class Gen_000BCBC0
{
public:
	void bfmeDestroy(void);

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

// ?bfmeDestroy@Gen_000BCBC0@@QAEXXZ
void Gen_000BCBC0::bfmeDestroy(void)
{
	char tag;

	bfmeDestroyRange(m_bfmeStart, m_bfmeFinish, &tag);

	int *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
}

void __cdecl bfmeDestroyRange2(int *first, int *last, char *tag);	// retail 0x000096FB

class Gen_006A76E0
{
public:
	void bfmeDestroy(void);

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

// ?bfmeDestroy@Gen_006A76E0@@QAEXXZ
void Gen_006A76E0::bfmeDestroy(void)
{
	char tag;

	bfmeDestroyRange2(m_bfmeStart, m_bfmeFinish, &tag);

	int *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
}
