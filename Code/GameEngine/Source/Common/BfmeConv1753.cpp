struct BfmeDevBQ;

struct BfmeVtblBQ
{
	void *m_bfmeSlotsBQ[89];
	void (__stdcall *m_bfmeSetBQ)(BfmeDevBQ *self, void *value);
};

struct BfmeDevBQ
{
	BfmeVtblBQ *m_bfmeVtblBQ;
};

struct BfmeStateBQ
{
	unsigned char m_bfmeHeadBQ[0x14];
	void **m_bfmeSourceBQ;
	char m_bfmeBusyBQ;
};

extern BfmeStateBQ *g_bfmeStateBQ;
extern int g_bfmeModeBQ;
extern BfmeDevBQ *g_bfme936Ptr;
extern int g_bfme936Count;

void __cdecl bfmeApplyBQ(void)
{
	if (g_bfmeStateBQ == 0)
		return;

	if (g_bfmeModeBQ != 0 && g_bfmeModeBQ != 2)
		return;

	if (g_bfmeStateBQ->m_bfmeBusyBQ)
		return;

	g_bfme936Ptr->m_bfmeVtblBQ->m_bfmeSetBQ(g_bfme936Ptr,
		*g_bfmeStateBQ->m_bfmeSourceBQ);

	++g_bfme936Count;
}
