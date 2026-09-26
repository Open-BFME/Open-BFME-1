struct BfmeNodeYY
{
	unsigned char m_bfmeHeadYY[4];
	BfmeNodeYY *m_bfmeChildYY;
};

extern void *(__stdcall *g_bfmeLookupYY)(int kind, void *what);
extern void (__stdcall *g_bfmeReleaseYY)(void *handle);

void __stdcall bfmeFreeYY(BfmeNodeYY *node)
{
	if (node == 0)
		return;

	BfmeNodeYY *child = node->m_bfmeChildYY;
	void (__stdcall *release)(void *) = g_bfmeReleaseYY;
	void *(__stdcall *lookup)(int, void *) = g_bfmeLookupYY;

	if (child != 0)
	{
		release(lookup(0, child));
		node->m_bfmeChildYY = 0;
	}

	release(lookup(0, node));
}
