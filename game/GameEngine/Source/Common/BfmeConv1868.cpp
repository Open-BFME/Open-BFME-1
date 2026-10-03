struct BfmeNodeYY
{
	unsigned char m_bfmeHeadYY[4];
	BfmeNodeYY *m_bfmeChildYY;
};

extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) int __stdcall HeapFree(
	void *heap, unsigned long flags, void *block);

void __stdcall bfmeFreeYY(BfmeNodeYY *node)
{
	if (node == 0)
		return;

	BfmeNodeYY *child = node->m_bfmeChildYY;
	if (child != 0)
	{
		HeapFree(GetProcessHeap(), 0, child);
		node->m_bfmeChildYY = 0;
	}

	HeapFree(GetProcessHeap(), 0, node);
}
