// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
// The script-debug-window frame pump, both halves:
//
//   0x00336F20  isTimeFrozenDebug          is the LOGIC frame held
//   0x00336F50  _bfme_isClientFrameFrozen  is the CLIENT frame held
//   0x00336F80  notifyCameraChange         poke the window when the camera moves
//   0x00339B10  _bfme_updateLogicDebugFrame
//   0x00339B90  _bfme_updateClientDebugFrame
//
// One switch drives all four: m_useLogicDebugFrame at ScriptEngine+0x17638
// decides which of the two frames the debug window is stepping. The logic half
// runs when it is set and the client half when it is clear, and each asks the
// same two exports of the same DLL -- SetFrameNumber with its own frame counter,
// then CanAppContinue into its own flag. The two frozen-tests are the same
// predicate read back, one per flag, and they were in the same file already
// while the two pumps that set those flags were in two.
//
// The frame counters are the only real asymmetry: the client half takes it from
// TheGameClient through vtable slot 26, the logic half reads TheGameLogic+0x3C
// directly.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	bool isTimeFrozenDebug(void);
	bool _bfme_isClientFrameFrozen(void);
	void _bfme_updateClientDebugFrame(void);
	void _bfme_updateLogicDebugFrame(void);
	void notifyCameraChange(void);

private:
	char m_unknown00[0x17638];
	bool m_useLogicDebugFrame;
};

typedef int (__stdcall *FarProc)(void);
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void);
	virtual unsigned int getFrame(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_unknown00[0x3C];
	unsigned int m_frame;
};

void _bfme_updateDebugWindowInputs(void);

// The subsystems the debug window is handed each frame. Only the two the pumps
// also touch are reached through the macros below; the rest keep their pinned
// extern spellings.
class AudioManager;
class GlobalData;
class NameKeyGenerator;
class View;
class TerrainLogic;

extern ScriptEngine *TheScriptEngine;
extern AudioManager *TheAudio;
extern GlobalData *TheWritableGlobalData;
extern NameKeyGenerator *TheNameKeyGenerator;
extern View *TheTacticalView;
extern TerrainLogic *TheTerrainLogic;
// 0x012EF1D8 has only address-derived pins so far (placeBuildAvailable casts
// it to a thing factory); keep the untyped pin rather than invent a class.
extern void *g_global12EF1D8;

#define TheScriptDebugWindowDLL (*(void **)0x012F0758)
#define ClientCanAppContinue (*(bool *)0x012F075C)
#define LogicCanAppContinue (*(bool *)0x012F075D)
#define TheGameClient (*(GameClient **)0x012F1464)
#define TheGameLogic (*(GameLogic **)0x012F0898)

bool ScriptEngine::isTimeFrozenDebug(void)
{
	if (m_useLogicDebugFrame && TheScriptDebugWindowDLL)
		return !LogicCanAppContinue;
	return false;
}

bool ScriptEngine::_bfme_isClientFrameFrozen(void)
{
	if (!m_useLogicDebugFrame && TheScriptDebugWindowDLL)
		return !ClientCanAppContinue;
	return false;
}

void ScriptEngine::notifyCameraChange(void)
{
	typedef void (*funcptr)(void);

	if (TheScriptDebugWindowDLL)
	{
		FARPROC proc = GetProcAddress(TheScriptDebugWindowDLL, "NotifyCameraChange");
		if (proc)
			((funcptr)proc)();
	}
}

void _bfme_updateDebugWindowInputs(void)
{
	if (!TheScriptDebugWindowDLL)
		return;

	typedef void (__cdecl *SetTheSidesListProc)(
		void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
	FarProc proc = GetProcAddress(TheScriptDebugWindowDLL, "SetTheSidesList");
	if (proc)
	{
		((SetTheSidesListProc)proc)(
			// no symbols.csv pin names this global yet; the export name
			// suggests TheSidesList but nothing in the ledger proves it
			*(void **)0x012EF428,
			TheScriptEngine,
			TheAudio,
			TheWritableGlobalData,
			TheNameKeyGenerator,
			0,
			0,
			TheTacticalView,
			TheTerrainLogic,
			g_global12EF1D8,
			TheGameLogic);
	}
}

void ScriptEngine::_bfme_updateLogicDebugFrame(void)
{
	if (!m_useLogicDebugFrame)
		return;

	void *module = TheScriptDebugWindowDLL;
	if (module)
	{
		_bfme_updateDebugWindowInputs();
		module = TheScriptDebugWindowDLL;
		typedef void (__cdecl *SetFrameNumberProc)(unsigned int frame);
		FarProc proc = GetProcAddress(module, "SetFrameNumber");
		if (proc)
			((SetFrameNumberProc)proc)(TheGameLogic->m_frame);

		module = TheScriptDebugWindowDLL;
		if (module)
		{
			typedef bool (__cdecl *CanAppContinueProc)(void);
			proc = GetProcAddress(module, "CanAppContinue");
			if (proc)
			{
				LogicCanAppContinue = ((CanAppContinueProc)proc)();
				return;
			}
			return;
		}
	}

	LogicCanAppContinue = true;
}

void ScriptEngine::_bfme_updateClientDebugFrame(void)
{
	if (m_useLogicDebugFrame)
		return;

	if (TheScriptDebugWindowDLL)
	{
		_bfme_updateDebugWindowInputs();
		typedef void (__cdecl *SetFrameNumberProc)(unsigned int frame);
		FarProc proc = GetProcAddress(TheScriptDebugWindowDLL, "SetFrameNumber");
		if (proc)
		{
			unsigned int frame = TheGameClient->getFrame();
			((SetFrameNumberProc)proc)(frame);
		}

		if (TheScriptDebugWindowDLL)
		{
			typedef bool (__cdecl *CanAppContinueProc)(void);
			FarProc continueProc = GetProcAddress(TheScriptDebugWindowDLL, "CanAppContinue");
			if (continueProc)
			{
				ClientCanAppContinue = ((CanAppContinueProc)continueProc)();
				return;
			}
			return;
		}
	}

	ClientCanAppContinue = true;
}
