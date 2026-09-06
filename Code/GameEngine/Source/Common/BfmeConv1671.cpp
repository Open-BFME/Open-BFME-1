extern "C" __declspec(dllimport) int __cdecl bfmeCheckEQH(void *buffer, void *what, void **out);
extern unsigned char g_bfmeBufferEQH[];

struct BfmeSinkEQH
{
	virtual void bfmeSlot0EQH(void);
	virtual void bfmeSlot1EQH(void);
	virtual void bfmeSendEQH(void *buffer);
};

void __cdecl bfmeReportEQH(BfmeSinkEQH *sink, void *what, void *out)
{
	if (bfmeCheckEQH(g_bfmeBufferEQH, what, &out) >= 0)
		sink->bfmeSendEQH(g_bfmeBufferEQH);
}
