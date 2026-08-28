// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	bool isTimeFast(void);
};

class BfmeGameLogicPause
{
public:
	bool isGamePaused(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_unknown00[0xC59];
	bool m_tivoFastMode;
};

typedef int (__stdcall *FarProc)(void);
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

#define TheScriptDebugWindowDLL (*(void **)0x012F0758)
#define AppIsFast (*(bool *)0x012F0768)
#define TheGameLogic (*(BfmeGameLogicPause **)0x012F0898)
#define TheGlobalData (*(GlobalData **)0x012ED5C8)

bool ScriptEngine::isTimeFast(void)
{
	if (!TheGameLogic->isGamePaused() && TheGlobalData->m_tivoFastMode)
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
