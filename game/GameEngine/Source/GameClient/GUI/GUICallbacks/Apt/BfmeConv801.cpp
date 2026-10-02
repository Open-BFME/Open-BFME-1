class BfmeUiEAC
{
public:
	void bfmeShowEAC(void *a, const char *msg, int n, void *p, int c, int d, int e, int f);
	void bfmeListEAC(void *a, const char *msg, int n, void *p, void *q, int c, int d, int e);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the show/list calls through it, so the pointee stays the local BfmeUiEAC view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
extern void *g_bfmeArgEAC;

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrEAC[];
extern "C" unsigned char bfmeMsgEACa[];
extern "C" void *bfmeTabEAC[];
extern "C" unsigned char bfmeMsgEACb[];

void bfmeGoEACa(int a)
{
	if (a >= 1 || a <= 100)
	{
		sprintf((char *)&a, (const char *)bfmeFmtStrEAC, a);
		((BfmeUiEAC *)g_rva012F19E8WindowManager)->bfmeShowEAC(g_bfmeArgEAC, (const char *)bfmeMsgEACa, 1, &a, 0, 0, 0, 0);
	}
}

void bfmeGoEACb(int a, int i)
{
	sprintf((char *)&a, (const char *)bfmeFmtStrEAC, a + 1);
	((BfmeUiEAC *)g_rva012F19E8WindowManager)->bfmeListEAC(g_bfmeArgEAC, (const char *)bfmeMsgEACb, 2, &a, bfmeTabEAC[i], 0, 0, 0);
}
