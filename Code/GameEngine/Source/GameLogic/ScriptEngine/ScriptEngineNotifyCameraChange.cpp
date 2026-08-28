// cl: /DNDEBUG /MD /EHsc
// BFME's ScriptEngine debug-DLL hook for the NotifyCameraChange export.

typedef int (__stdcall *FARPROC)();
typedef void *HMODULE;

extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(
	HMODULE module, const char *procName);

extern HMODULE TheScriptDebugWindowDLL;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void notifyCameraChange(void);
};

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
