class BfmeUiDZE
{
public:
	void bfmeShowDZE(void *a, const char *msg, int b, void *p, int c, int d, int e, int f);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// Retail's show-argument global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).
// The canonical int is cast to the callee's `void *a` at the use; the load is
// `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;

static __forceinline void *bfmeArgDZE()
{
	return (void *)g_aptPalantirWindow;
}

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrDZE[];

extern "C" unsigned char bfmeMsgDZEa[];
extern "C" unsigned char bfmeMsgDZEb[];
extern "C" unsigned char bfmeMsgDZEc[];
extern "C" unsigned char bfmeMsgDZEd[];

void bfmeGoDZEa(int a)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	((BfmeUiDZE *)g_rva012F19E8WindowManager)->bfmeShowDZE(bfmeArgDZE(), (const char *)bfmeMsgDZEa, 1, &a, 0, 0, 0, 0);
}

void bfmeGoDZEb(int a)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	((BfmeUiDZE *)g_rva012F19E8WindowManager)->bfmeShowDZE(bfmeArgDZE(), (const char *)bfmeMsgDZEb, 1, &a, 0, 0, 0, 0);
}

void bfmeGoDZEc(int a)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	((BfmeUiDZE *)g_rva012F19E8WindowManager)->bfmeShowDZE(bfmeArgDZE(), (const char *)bfmeMsgDZEc, 1, &a, 0, 0, 0, 0);
}

void bfmeGoDZEd(int a)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	((BfmeUiDZE *)g_rva012F19E8WindowManager)->bfmeShowDZE(bfmeArgDZE(), (const char *)bfmeMsgDZEd, 1, &a, 0, 0, 0, 0);
}

