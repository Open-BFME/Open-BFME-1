extern "C" __declspec(dllimport) int __cdecl vsprintf(void *buffer, void *what, void **out);
// retired debt _g_bfmeBufferEQH: reference recorded ?g_bfmeBufferEQH@@3PAEA
unsigned char g_bfmeBufferEQH[1024];

struct BfmeSinkEQH
{
	virtual void bfmeSlot0EQH(void);
	virtual void bfmeSlot1EQH(void);
	virtual void bfmeSendEQH(void *buffer);
};

void __cdecl bfmeReportEQH(BfmeSinkEQH *sink, void *what, void *out)
{
	if (vsprintf(g_bfmeBufferEQH, what, &out) >= 0)
		sink->bfmeSendEQH(g_bfmeBufferEQH);
}
