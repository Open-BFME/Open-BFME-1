// Open-BFME5 conversions.

class BfmeX1085;

class BfmeR1085
{
public:
	void bfmeOpen1085(BfmeX1085 *a);
	void bfmeShut1085(BfmeX1085 *a);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the open/shut calls through it, so the pointee stays the local BfmeR1085 view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the open/shut interface argument, so the int is
// cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;
extern char g_bfmeF1085;
extern char g_bfmeG1085;
extern char g_bfmeH1085;

void bfmeGo1085A(void)
{
	if (g_bfmeH1085) {
		((BfmeR1085 *)g_rva012F19E8WindowManager)->bfmeOpen1085((BfmeX1085 *)g_aptPalantirWindow);
		g_bfmeF1085 = 1;
		g_bfmeH1085 = 0;
	} else if (!g_bfmeF1085) {
		return;
	}
	if (!g_bfmeG1085) {
		((BfmeR1085 *)g_rva012F19E8WindowManager)->bfmeShut1085((BfmeX1085 *)g_aptPalantirWindow);
		g_bfmeG1085 = 1;
	}
}

class BfmeSub1085
{
public:
	void bfmeSet1085(int a);
};

struct BfmeF1085
{
	char m_bfmePad[0x20];
	BfmeSub1085 m_bfme20;
};

class BfmeE1085
{
public:
	char m_bfmePad[0x204];
	BfmeF1085 *m_bfme204;
};

class BfmeP1085
{
public:
	virtual void bfmeSlot1085_0(void);
	virtual void bfmeSlot1085_1(void);
	virtual void bfmeSlot1085_2(void);
	virtual void bfmeSlot1085_3(void);
	virtual void bfmeSlot1085_4(void);
	virtual void bfmeSlot1085_5(void);
	virtual void bfmeSlot1085_6(void);
	virtual void bfmeSlot1085_7(void);
	virtual void bfmeSlot1085_8(void);
	virtual void bfmeSlot1085_9(void);
	virtual void bfmeSlot1085_10(void);
	virtual void bfmeSlot1085_11(void);
	virtual void bfmeSlot1085_12(void);
	virtual void bfmeSlot1085_13(void);
	virtual void bfmeSlot1085_14(void);
	virtual void bfmeSlot1085_15(void);
	virtual void bfmeSlot1085_16(void);
	virtual void bfmeSlot1085_17(void);
	virtual void bfmeSlot1085_18(void);
	virtual void bfmeSlot1085_19(void);
	virtual void bfmeSlot1085_20(void);
	virtual void bfmeSlot1085_21(void);
	virtual void bfmeSlot1085_22(void);
	virtual void bfmeSlot1085_23(void);
	virtual void bfmeSlot1085_24(void);
	virtual void bfmeSlot1085_25(void);
	virtual BfmeE1085 * bfmeSlot1085_26(int a);
	void bfmeUse1085(BfmeE1085 *a, int b);
};

// retail 0x012F076C: EA's ScriptEngine *TheScriptEngine, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp. BfmeP1085 is
// this TU's local view of the pointee; cast at the use.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void __stdcall bfmeGo1085B(int a, int b, char c)
{
	BfmeE1085 *e = ((BfmeP1085 *)TheScriptEngine)->bfmeSlot1085_26(a);

	if (!e)
		return;
	if (!e->m_bfme204)
		return;
	e->m_bfme204->m_bfme20.bfmeSet1085(1);
	if (c)
		((BfmeP1085 *)TheScriptEngine)->bfmeUse1085(e, b * 5);
	else
		((BfmeP1085 *)TheScriptEngine)->bfmeUse1085(e, b);
}
