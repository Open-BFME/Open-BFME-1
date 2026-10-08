// Open-BFME5 conversions.

class BfmeX1085;

// retail ILT 0x0002144A -> 0x00467460 and ILT 0x00012733 -> 0x00465C50 are
// the matched WindowManager::hideAptWindow and showAptWindow rows
class WindowManager
{
public:
	bool hideAptWindow(int window);
	bool showAptWindow(int window);
};

class BfmeR1085 : public WindowManager
{
};

#define bfmeOpen1085(a) hideAptWindow((int)(a))
#define bfmeShut1085(a) showAptWindow((int)(a))

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the open/shut calls through it, so the pointee stays the local BfmeR1085 view
// and the access is cast at the use.
extern WindowManager *g_rva012F19E8WindowManager;
// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the open/shut interface argument, so the int is
// cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;
extern unsigned char g_aptPalantirClosed;
extern unsigned char g_aptPalantirShowRequested;
extern unsigned char g_aptPalantirCloseRequested;

void bfmeGo1085A(void)
{
	if (g_aptPalantirCloseRequested) {
		((BfmeR1085 *)g_rva012F19E8WindowManager)->bfmeOpen1085((BfmeX1085 *)g_aptPalantirWindow);
		g_aptPalantirClosed = 1;
		g_aptPalantirCloseRequested = 0;
	} else if (!g_aptPalantirClosed) {
		return;
	}
	if (!g_aptPalantirShowRequested) {
		((BfmeR1085 *)g_rva012F19E8WindowManager)->bfmeShut1085((BfmeX1085 *)g_aptPalantirWindow);
		g_aptPalantirShowRequested = 1;
	}
}

enum CommandSourceType {};

// retail ILT 0x00024D70 -> 0x000D87E0 is the matched AICommandInterface::aiIdle
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class BfmeSub1085 : public AICommandInterface
{
};

#define bfmeSet1085(a) aiIdle((CommandSourceType)(a))

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
};

// retail 0x012F076C: EA's ScriptEngine *TheScriptEngine, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp. BfmeP1085 is
// this TU's local view of the pointee; cast at the use.
class Object;

// retail ILT 0x00044A1C -> 0x00339980 is the matched ScriptEngine::setSequentialTimer
class ScriptEngine
{
public:
	void setSequentialTimer(Object *obj, int frameCount);
};

#define bfmeUse1085(a, b) setSequentialTimer((Object *)(a), (b))

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
		TheScriptEngine->bfmeUse1085(e, b * 5);
	else
		TheScriptEngine->bfmeUse1085(e, b);
}
