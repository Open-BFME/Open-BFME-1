// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
// Open-BFME: late-bound debugger probe at 0x0088EAF0. The body loads
// kernel32 by name, resolves IsDebuggerPresent through GetProcAddress and
// calls it. Windows 95 has no IsDebuggerPresent export, so the lookup is
// done at run time instead of through the import table.

typedef void *HMODULE;
typedef int(__stdcall *FARPROC)(void);

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *procName);
}

static int queryDebuggerFlag(HMODULE kernel)
{
	FARPROC proc = GetProcAddress(kernel, "IsDebuggerPresent");
	if (proc != 0 && proc() != 0)
		return 1;
	return 0;
}

extern "C" unsigned char Rva0088EAF0IsDebuggerPresent(void)
{
	HMODULE kernel = LoadLibraryA("kernel32");
	if (kernel != 0)
		return (unsigned char)queryDebuggerFlag(kernel);
	return 0;
}
