// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef int (__stdcall *FarProc)(void);
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

#define TheScriptDebugWindowDLL (*(void **)0x012F0758)

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
			*(void **)0x012EF428,
			*(void **)0x012F076C,
			*(void **)0x012ED668,
			*(void **)0x012ED5C8,
			*(void **)0x012ED600,
			0,
			0,
			*(void **)0x012F1600,
			*(void **)0x012EF4CC,
			*(void **)0x012EF1D8,
			*(void **)0x012F0898);
	}
}
