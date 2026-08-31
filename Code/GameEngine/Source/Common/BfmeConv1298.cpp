// Open-BFME5 conversions.

extern void *g_bfmeHandleSRA;

__declspec(dllimport) void *__stdcall bfmeFindSRA(void *h, int n);
__declspec(dllimport) void __stdcall bfmeShowSRA(void *w, int cmd, int f);

class BfmeThingSRA
{
public:
	BfmeThingSRA();
};

BfmeThingSRA::BfmeThingSRA()
{
	void *w = bfmeFindSRA(g_bfmeHandleSRA, 0);
	bfmeShowSRA(w, 0xf060, 1);
}
