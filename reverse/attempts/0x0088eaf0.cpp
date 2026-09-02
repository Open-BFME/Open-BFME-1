// ?Rva0088EAF0IsDebuggerPresent@@YAHXZ
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: late-bound IsDebuggerPresent. LoadLibraryA("kernel32"),
// GetProcAddress, then the indirect call. Answers true only if all three
// succeed. The LoadLibrary failure path is a separate xor-al return.

typedef int BOOL;
typedef void *HMODULE;
typedef int (__stdcall *FARPROC)(void);

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *procName);
}

// ?Rva0088EAF0IsDebuggerPresent@@YAHXZ
int Rva0088EAF0IsDebuggerPresent(void)
{
	HMODULE module = LoadLibraryA("kernel32");
	if (!module)
		return 0;

	FARPROC proc = GetProcAddress(module, "IsDebuggerPresent");
	if (proc && proc())
		return 1;
	return 0;
}
