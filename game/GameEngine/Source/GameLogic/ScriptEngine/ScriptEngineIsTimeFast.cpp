// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	bool isTimeFast(void);
};

// TU-local view of the GameLogic singleton's pause query used here.
class BfmeGameLogicPause
{
public:
	bool isGamePaused(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_unknown00[0xC59];
	bool m_tivoFastMode;
};

typedef int (__stdcall *FarProc)(void);
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

extern void *TheScriptDebugWindowDLL;
extern bool g_012F0768;
// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
class GameLogic;
extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
#define AppIsFast g_012F0768
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

static __forceinline BfmeGameLogicPause *bfmePauseView(void)
{
	return (BfmeGameLogicPause *)TheGameLogic;
}

bool ScriptEngine::isTimeFast(void)
{
	if (!bfmePauseView()->isGamePaused() && TheGlobalData->m_tivoFastMode)
		return true;

	void *module = TheScriptDebugWindowDLL;
	if (module)
	{
		typedef bool (__cdecl *RunAppFastProc)(void);
		FarProc proc = GetProcAddress(module, "CanAppContinue");
		proc = GetProcAddress(TheScriptDebugWindowDLL, "RunAppFast");
		if (proc && ((RunAppFastProc)proc)())
		{
			AppIsFast = true;
			return true;
		}
		if (AppIsFast)
			AppIsFast = false;
	}
	return false;
}
