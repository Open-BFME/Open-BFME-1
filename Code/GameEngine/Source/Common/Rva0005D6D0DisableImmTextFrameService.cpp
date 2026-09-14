// cl: /DNDEBUG /MD /EHs-c-
// Late-bound ImmDisableTextFrameService(-1) call recovered from retail.

typedef unsigned long DWORD;
typedef int BOOL;
typedef void *HMODULE;
typedef int (__stdcall *FARPROC)(void);

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) BOOL __stdcall FreeLibrary(HMODULE module);
}

typedef BOOL(__stdcall *ImmDisableTextFrameServiceProc)(DWORD threadId);

// ?Rva0005D6D0DisableImmTextFrameService@@YAXXZ
void Rva0005D6D0DisableImmTextFrameService(void)
{
	HMODULE module = LoadLibraryA("IMM32.dll");
	if (module != 0) {
		ImmDisableTextFrameServiceProc disable =
			(ImmDisableTextFrameServiceProc)GetProcAddress(module,
				"ImmDisableTextFrameService");
		if (disable != 0) {
			disable((DWORD)-1);
		}
		FreeLibrary(module);
	}
}
