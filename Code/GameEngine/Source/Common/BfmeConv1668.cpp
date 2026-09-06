struct BfmeNodeEQB
{
	void *m_bfmeSlotEQB;
	BfmeNodeEQB *m_bfmeNextEQB;
};

extern "C" BfmeNodeEQB *g_bfmeHeadEQB;

BfmeNodeEQB * __stdcall bfmeLinkEQB(BfmeNodeEQB *node)
{
	for (BfmeNodeEQB *p = g_bfmeHeadEQB; p != 0; p = p->m_bfmeNextEQB)
		if (p == node)
			return node;
	node->m_bfmeNextEQB = g_bfmeHeadEQB;
	g_bfmeHeadEQB = node;
	return node;
}
