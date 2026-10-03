// Open-BFME5 conversions.

class BfmeHub993
{
public:
	virtual void bfmeVH0993();
	virtual void bfmeVH1993();
	virtual void bfmeVH2993();
	virtual void bfmeVH3993();
	virtual void bfmeVH4993();
	virtual void bfmeVH5993();
	virtual void bfmeVH6993();
	virtual void bfmeVH7993();
	virtual void bfmeVH8993();
	virtual void bfmeVH9993();
	virtual void bfmeVH10993();
	virtual void bfmeVH11993();
	virtual void bfmeVH12993();
	virtual void bfmeVH13993();
	virtual void bfmeVH14993();
	virtual void bfmeVH15993();
	virtual void bfmeVH16993();
	virtual void bfmeVH17993();
	virtual void bfmeVH18993();
	virtual void bfmeVH19993();
	virtual void bfmeVH20993();
	virtual void bfmeVH21993();
	virtual void bfmeVH22993();
	virtual void bfmeVH23993();
	virtual void bfmeVH24993();
	virtual void bfmeVH25993();
	virtual void bfmeVH26993();
	virtual void bfmeVH27993();
	virtual void bfmeVH28993();
	virtual void bfmeVH29993();
	virtual void bfmeVH30993();
	virtual void bfmeVH31993();
	virtual void bfmeVH32993();
	virtual void bfmeVH33993();
	virtual void bfmeVH34993();
	virtual void bfmeVH35993();
	virtual void bfmeVH36993();
	virtual void bfmeVH37993();
	virtual void bfmeVH38993();
	virtual void bfmeVH39993();
	virtual void bfmeVH40993();
	virtual void bfmeVH41993();
	virtual void bfmeVH42993();
	virtual void bfmeVH43993();
	virtual void bfmeVH44993();
	virtual void bfmeVH45993();
	virtual void bfmeFix993(int r);
	virtual void bfmeVH47993();
	virtual void bfmeEnd993(int a, int b);
	virtual void bfmeVH49993();
	virtual void bfmeVH50993();
	virtual void bfmeVH51993();
	virtual void bfmeVH52993();
	virtual void bfmeVH53993();
	virtual void bfmeVH54993();
	virtual void bfmeVH55993();
	virtual void bfmeVH56993();
	virtual void bfmeVH57993();
	virtual void bfmeVH58993();
	virtual void bfmeVH59993();
	virtual int bfmeAsk993();
};

// The global at retail 0x012F148C is InGameUI *TheInGameUI, defined once in
// game/GameEngine/Source/GameClient/InGameUI.cpp.  Only the linked name may be
// referenced here; BfmeHub993 above stays as this TU's local view of the
// pointee, so the uses cast.
class InGameUI;

extern InGameUI *TheInGameUI;

class BfmeA993
{
public:
	void bfmeGo993A(int unused);

	char m_bfmePad[0x24];
	char m_bfmeOn;
};

void BfmeA993::bfmeGo993A(int unused)
{
	m_bfmeOn = 1;

	int r = ((BfmeHub993 *)TheInGameUI)->bfmeAsk993();

	if (!r)
		((BfmeHub993 *)TheInGameUI)->bfmeFix993(r);

	((BfmeHub993 *)TheInGameUI)->bfmeEnd993(0, 0);
}

class BfmeAskB993
{
public:
	char bfmeAsk993B();
};

class BfmeLog993
{
public:
	void bfmeLog993B(int a, char *fmt, int n, char *s, int p, int q, int r, int t);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the log call through it, so the pointee stays the local BfmeLog993 view and
// the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

extern BfmeAskB993 *g_bfmeAskB993;
// Retail 0x012B7D80; canonical spelling `int g_aptPalantirWindow`
// (?g_aptPalantirWindow@@3HA), defined in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp.
extern int g_aptPalantirWindow;
extern char g_bfmeStrA993B[];
extern const char g_rva01080FC0[2];
extern char g_bfmeFmt993B[];

void bfmeGo993B(void)
{
	char *s = g_bfmeAskB993->bfmeAsk993B() ? g_bfmeStrA993B : const_cast<char *>(g_rva01080FC0);

	((BfmeLog993 *)g_rva012F19E8WindowManager)->bfmeLog993B(g_aptPalantirWindow, g_bfmeFmt993B, 1, s, 0, 0, 0, 0);
}
