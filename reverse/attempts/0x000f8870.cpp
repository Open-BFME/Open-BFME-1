// ?bfmeRemoveEV@BfmeListEV@@QAEXPAXH@Z (identity unknown)
// partial score=0.95 date=2026-09-09
// 64/63. Inline while-loop (no static helper) with the sentinel test as the
// loop's own bottom check improved 67->64: retail shares one "cmp eax,ecx; je end"
// between the found and not-found exits, ours still has that check duplicated once.
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

	unsigned char m_bfmeHeadEV[8];
	BfmeNodeEV *m_bfmeNodeEV;
	unsigned char m_bfmeMidEV[4];
	int m_bfmeSizeEV;
};

void BfmeListEV::bfmeRemoveEV(void *value, int unused)
{
	BfmeNodeEV *sentinel = m_bfmeNodeEV;
	BfmeNodeEV *node = sentinel->m_bfmeNextEV;

	if (node != sentinel)
	{
		while (node->m_bfmeValueEV != value)
		{
			node = node->m_bfmeNextEV;
			if (node == sentinel)
				break;
		}
	}

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
