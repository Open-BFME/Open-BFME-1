// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void _bfme_updateLogicDebugFrame(void);

private:
	char m_unknown00[0x17638];
	bool m_useLogicDebugFrame;
};

typedef int (__stdcall *FarProc)(void);
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

extern void _bfme_updateDebugWindowInputs(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_unknown00[0x3C];
	unsigned int m_frame;
};

#define TheScriptDebugWindowDLL (*(void **)0x012F0758)
#define LogicCanAppContinue (*(bool *)0x012F075D)
#define TheGameLogic (*(GameLogic **)0x012F0898)

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
