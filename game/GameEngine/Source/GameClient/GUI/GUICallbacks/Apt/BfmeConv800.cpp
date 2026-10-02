class BfmeUiEAA
{
public:
	void bfmeShowEAA(void *a, const char *msg, int n, void *p, const char *s, int c, int d, int e);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// Retail's show-argument global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).
// The canonical int is cast to the callee's `void *a` at the use; the load is
// `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;

static __forceinline void *bfmeArgEAA()
{
	return (void *)g_aptPalantirWindow;
}

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrEAA[];
extern "C" unsigned char bfmeOnEAA[];
extern "C" unsigned char bfmeOffEAA[];
extern "C" unsigned char bfmeOnEAB[];
extern "C" unsigned char bfmeOffEAB[];

extern "C" unsigned char bfmeMsgEAAa[];
extern "C" unsigned char bfmeMsgEAAb[];
extern "C" unsigned char bfmeMsgEAAc[];
extern "C" unsigned char bfmeMsgEAAd[];

void bfmeGoEAAa(int a, bool flag)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	((BfmeUiEAA *)g_rva012F19E8WindowManager)->bfmeShowEAA(bfmeArgEAA(), (const char *)bfmeMsgEAAa, 2, &a,
		flag ? (const char *)bfmeOnEAA : (const char *)bfmeOffEAA, 0, 0, 0);
}

void bfmeGoEAAb(int a, bool flag)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	((BfmeUiEAA *)g_rva012F19E8WindowManager)->bfmeShowEAA(bfmeArgEAA(), (const char *)bfmeMsgEAAb, 2, &a,
		flag ? (const char *)bfmeOnEAB : (const char *)bfmeOffEAB, 0, 0, 0);
}

void bfmeGoEAAc(int a, bool flag)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	((BfmeUiEAA *)g_rva012F19E8WindowManager)->bfmeShowEAA(bfmeArgEAA(), (const char *)bfmeMsgEAAc, 2, &a,
		flag ? (const char *)bfmeOnEAA : (const char *)bfmeOffEAA, 0, 0, 0);
}

void bfmeGoEAAd(int a, bool flag)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	((BfmeUiEAA *)g_rva012F19E8WindowManager)->bfmeShowEAA(bfmeArgEAA(), (const char *)bfmeMsgEAAd, 2, &a,
		flag ? (const char *)bfmeOnEAA : (const char *)bfmeOffEAA, 0, 0, 0);
}

