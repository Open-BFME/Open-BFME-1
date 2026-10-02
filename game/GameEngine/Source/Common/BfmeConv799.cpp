// cl: /MD
#include <stdio.h>

class BfmeUiDZF
{
public:
	void bfmeShowDZF(void *a, const char *msg, int b, void *p, int c, int d, int e, int f);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// Retail's show-argument global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).
// The canonical int is cast to the callee's `void *a` at the use; the load is
// `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;

static __forceinline void *bfmeArgDZF()
{
	return (void *)g_aptPalantirWindow;
}

extern "C" unsigned char bfmeFmtStrDZF[];

extern "C" unsigned char bfmeMsgDZFa[];
extern "C" unsigned char bfmeMsgDZFb[];
extern "C" unsigned char bfmeMsgDZFc[];
extern "C" unsigned char bfmeMsgDZFd[];

void bfmeGoDZFa(int a)
{
	char buf[16];
	_snprintf(buf, 16, (const char *)bfmeFmtStrDZF, a);
	((BfmeUiDZF *)g_rva012F19E8WindowManager)->bfmeShowDZF(bfmeArgDZF(), (const char *)bfmeMsgDZFa, 1, buf, 0, 0, 0, 0);
}

void bfmeGoDZFb(int a)
{
	char buf[16];
	_snprintf(buf, 16, (const char *)bfmeFmtStrDZF, a);
	((BfmeUiDZF *)g_rva012F19E8WindowManager)->bfmeShowDZF(bfmeArgDZF(), (const char *)bfmeMsgDZFb, 1, buf, 0, 0, 0, 0);
}

void bfmeGoDZFc(int a)
{
	char buf[16];
	_snprintf(buf, 16, (const char *)bfmeFmtStrDZF, a);
	((BfmeUiDZF *)g_rva012F19E8WindowManager)->bfmeShowDZF(bfmeArgDZF(), (const char *)bfmeMsgDZFc, 1, buf, 0, 0, 0, 0);
}

void bfmeGoDZFd(int a)
{
	char buf[16];
	_snprintf(buf, 16, (const char *)bfmeFmtStrDZF, a);
	((BfmeUiDZF *)g_rva012F19E8WindowManager)->bfmeShowDZF(bfmeArgDZF(), (const char *)bfmeMsgDZFd, 1, buf, 0, 0, 0, 0);
}

