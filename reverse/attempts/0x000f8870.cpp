// ?bfmeRemoveEV@BfmeListEV@@QAEXPAXH@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// 67/63. Loop, unlink, deallocate and size decrement all match; MSVC duplicates
// the pop esi / ret 8 epilogue for the loop-exhausted path where retail shares one.
// Pin: ?bfmeDeallocEV@@YAXPAXI@Z,0x0082E5F0 (STL node deallocate).
void __cdecl bfmeDeallocEV(void *block, unsigned int size);

class BfmeNodeEV
{
public:
	BfmeNodeEV *m_bfmeNextEV;
	BfmeNodeEV *m_bfmePrevEV;
	void *m_bfmeValueEV;
};

class BfmeListEV
{
public:
	void bfmeRemoveEV(void *value, int unused);

	static BfmeNodeEV *bfmeFindEV(BfmeNodeEV *sentinel, void *value)
	{
		for (BfmeNodeEV *n = sentinel->m_bfmeNextEV; n != sentinel; n = n->m_bfmeNextEV)
			if (n->m_bfmeValueEV == value)
				return n;
		return sentinel;
	}

	unsigned char m_bfmeHeadEV[8];
	BfmeNodeEV *m_bfmeNodeEV;
	unsigned char m_bfmeMidEV[4];
	int m_bfmeSizeEV;
};

void BfmeListEV::bfmeRemoveEV(void *value, int unused)
{
	BfmeNodeEV *sentinel = m_bfmeNodeEV;
	BfmeNodeEV *node = bfmeFindEV(sentinel, value);

	if (node != sentinel)
	{
		BfmeNodeEV *next = node->m_bfmeNextEV;
		BfmeNodeEV *prev = node->m_bfmePrevEV;
		prev->m_bfmeNextEV = next;
		next->m_bfmePrevEV = prev;
		bfmeDeallocEV(node, 12);
		--m_bfmeSizeEV;
	}
}
