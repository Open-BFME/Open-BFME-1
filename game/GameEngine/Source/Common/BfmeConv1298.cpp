// Open-BFME5 conversions.

extern void *ApplicationHWnd;

extern "C" __declspec(dllimport) void *__stdcall GetSystemMenu(void *h, int n);
extern "C" __declspec(dllimport) void __stdcall EnableMenuItem(void *w, int cmd, int f);

class BfmeThingSRA
{
public:
	BfmeThingSRA();
};

BfmeThingSRA::BfmeThingSRA()
{
	void *w = GetSystemMenu(ApplicationHWnd, 0);
	EnableMenuItem(w, 0xf060, 1);
}
