// cl: /DNDEBUG /MD /EHsc
/* ScriptEngine::forceUnfreezeTime, retail 0x00337040, 28 bytes.

   Identified against the Generals Zero Hour source, whose ScriptEngine.cpp
   carries this body verbatim: guard on the debug DLL handle, GetProcAddress
   for "ForceAppContinue", call it if it resolved.  BFME kept it unchanged, and
   the literal is referenced from this body alone.

   The global is the one ScriptEngineAppendDebugMessage.cpp next door already
   names, TheScriptDebugWindowDLL at 0x00EF0758.

   The trailing call is a TAIL call -- retail jumps to the resolved address
   rather than calling it -- which is what a void member with no stack
   arguments compiles to and what pins the funcptr as taking none.

   0x00336F80 is the same body against "NotifyCameraChange" and is left alone:
   BFME added that hook and Zero Hour has no counterpart to name it from. */

typedef int (__stdcall *FARPROC)();
typedef void *HMODULE;

extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(
	HMODULE module, const char *procName);

extern HMODULE TheScriptDebugWindowDLL;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void forceUnfreezeTime(void);
};

void ScriptEngine::forceUnfreezeTime(void)
{
	typedef void (*funcptr)(void);

	if (TheScriptDebugWindowDLL)
	{
		FARPROC proc = GetProcAddress(TheScriptDebugWindowDLL, "ForceAppContinue");
		if (proc)
			((funcptr)proc)();
	}
}
