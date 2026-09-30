// Open-BFME5 conversions.

extern void *g_bfmeHandleSRA;

extern "C" __declspec(dllimport) void *__stdcall GetSystemMenu(void *h, int n);
extern "C" __declspec(dllimport) void __stdcall EnableMenuItem(void *w, int cmd, int f);

class BfmeThingSRA
{
public:
	BfmeThingSRA();
};

BfmeThingSRA::BfmeThingSRA()
{
	void *w = GetSystemMenu(g_bfmeHandleSRA, 0);
	EnableMenuItem(w, 0xf060, 1);
}
