// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
// Open-BFME: driver for the Assert/Crash dialog at 0x0088E1A0. It suspends
// every other thread of this process, hands the two text pointers to the
// dialog procedure at 0x0088E000 through the globals that procedure reads,
// runs the dialog, and resumes the suspended threads unless the watchdog
// thread at 0x0088E100 already did.

typedef void *RvaHandle;
typedef unsigned long RvaDword;
typedef RvaHandle(__stdcall *RvaOpenThreadFn)(RvaDword access, int inherit, RvaDword threadId);

struct RvaThreadEntry32
{
	RvaDword dwSize;
	RvaDword cntUsage;
	RvaDword th32ThreadID;
	RvaDword th32OwnerProcessID;
	long tpBasePri;
	long tpDeltaPri;
	RvaDword dwFlags;
};

struct Rva0088E100Context
{
	RvaDword processId;
	RvaDword threadId;
	RvaOpenThreadFn openThread;
	RvaHandle snapshot;
};

struct BfmeCsDWA
{
	unsigned char m_bfmeHead[0x18];
};

extern BfmeCsDWA g_bfmeCsDWC;

// The dialog procedure at 0x0088E000, matched in its own translation unit.
int __stdcall Rva0088E000DialogProc(void *hWnd, unsigned int uMsg, unsigned int wParam, long lParam);

extern "C"
{
	__declspec(dllimport) RvaHandle __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(RvaHandle module, const char *procName);
	__declspec(dllimport) RvaDword __stdcall GetCurrentProcessId(void);
	__declspec(dllimport) RvaDword __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) RvaDword __stdcall SuspendThread(RvaHandle thread);
	__declspec(dllimport) int __stdcall GetExitCodeThread(RvaHandle thread, RvaDword *exitCode);
	__declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCsDWA *lock);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(BfmeCsDWA *lock);
	__declspec(dllimport) RvaHandle __stdcall CreateThread(void *security, RvaDword stackSize,
		RvaDword(__stdcall *start)(void *), void *parameter, RvaDword flags, RvaDword *threadId);
	__declspec(dllimport) unsigned int __stdcall SetTimer(void *hWnd, unsigned int id,
		unsigned int elapse, void(__stdcall *proc)(RvaHandle, unsigned int, unsigned int, RvaDword));
	__declspec(dllimport) int __stdcall KillTimer(void *hWnd, unsigned int id);
	__declspec(dllimport) int __stdcall DialogBoxIndirectParamA(void *instance, const void *dialogTemplate,
		void *parent, int(__stdcall *dialogProc)(void *, unsigned int, unsigned int, long), long initParam);

	RvaHandle __stdcall CreateToolhelp32Snapshot(RvaDword flags, RvaDword processId);
	int __stdcall Thread32First(RvaHandle snapshot, RvaThreadEntry32 *entry);
	int __stdcall Thread32Next(RvaHandle snapshot, RvaThreadEntry32 *entry);

	// Retail calls IAT VA 0x01358CCC at RVA 0x0088E220/0x0088E32A:
	// KERNEL32!CloseHandle; WinBase.h declares BOOL WINAPI CloseHandle(HANDLE).
	__declspec(dllimport) int __stdcall CloseHandle(RvaHandle handle);

	// Driver stores at RVA 0x0088E2B4/0x0088E2B9 and dialog-procedure
	// loads at RVA 0x0088E064/0x0088E072 prove these four-byte pointers.
	// Both are initially null at retail VA 0x01336EAC/0x01336EB0.
	const char *g_rva0088E000MessageText = 0;
	const char *g_rva0088E000WindowText = 0;
	// Retail .data VA 0x012D4FD0, 360 bytes: the DLGTEMPLATEEX ("Assert/Crash",
	// MS Sans Serif 8, six controls: Skip, Ignore all, Silent, Debug break,
	// Abort, and an edit box) handed to DialogBoxIndirectParamA. Copied from
	// the image; the structure parses to exactly this extent.
	unsigned char g_Rva012D4FD0AssertCrashTemplate[360] =
	{
		0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0xC2, 0x0A, 0xC0, 0x90,
		0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x01, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00,
		0x73, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x74, 0x00, 0x2F, 0x00, 0x43, 0x00, 0x72, 0x00,
		0x61, 0x00, 0x73, 0x00, 0x68, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x4D, 0x00,
		0x53, 0x00, 0x20, 0x00, 0x53, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x73, 0x00, 0x20, 0x00, 0x53, 0x00,
		0x65, 0x00, 0x72, 0x00, 0x69, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x50, 0x10, 0x01, 0x07, 0x00, 0x32, 0x00, 0x0E, 0x00,
		0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x53, 0x00, 0x6B, 0x00, 0x69, 0x00, 0x70, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x50,
		0x10, 0x01, 0x15, 0x00, 0x32, 0x00, 0x0E, 0x00, 0x05, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00,
		0x49, 0x00, 0x67, 0x00, 0x6E, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x65, 0x00, 0x20, 0x00, 0x61, 0x00,
		0x6C, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x01, 0x50, 0x10, 0x01, 0x23, 0x00, 0x32, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0x80, 0x00, 0x53, 0x00, 0x69, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x6E, 0x00, 0x74, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x50,
		0x10, 0x01, 0x38, 0x00, 0x32, 0x00, 0x0E, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00,
		0x44, 0x00, 0x65, 0x00, 0x62, 0x00, 0x75, 0x00, 0x67, 0x00, 0x20, 0x00, 0x62, 0x00, 0x72, 0x00,
		0x65, 0x00, 0x61, 0x00, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x50, 0x10, 0x01, 0x4C, 0x00, 0x32, 0x00, 0x0E, 0x00,
		0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x41, 0x00, 0x62, 0x00, 0x6F, 0x00, 0x72, 0x00,
		0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x44, 0x08, 0xA1, 0x50, 0x07, 0x00, 0x07, 0x00, 0x03, 0x01, 0x53, 0x00, 0x64, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
	extern long g_Rva013373BCTimerTicks;
	extern unsigned char g_Rva013373C0DialogClosed;
	extern long g_Rva013373C4DialogGeneration;

	RvaDword __stdcall Rva0088E100WatchdogThread(void *parameter);
	void __stdcall Rva0088E190TimerTick(RvaHandle, unsigned int, unsigned int, RvaDword);
	void Rva0088E090ResumeOtherThreads(RvaOpenThreadFn openThread, RvaHandle snapshot,
		RvaDword processId, RvaDword keepThreadId);
}

extern "C" int Rva0088E1A0ShowAssertCrashDialog(const char *windowText, const char *messageText)
{
	RvaHandle kernel = LoadLibraryA("kernel32");
	RvaOpenThreadFn openThread = (RvaOpenThreadFn)GetProcAddress(kernel, "OpenThread");
	RvaHandle snapshot = CreateToolhelp32Snapshot(4, 0);

	RvaThreadEntry32 entry;
	entry.dwSize = sizeof(RvaThreadEntry32);

	RvaDword processId = GetCurrentProcessId();
	RvaDword threadId = GetCurrentThreadId();

	if (openThread != 0 && Thread32First(snapshot, &entry))
	{
		do
		{
			if (entry.th32OwnerProcessID == processId && entry.th32ThreadID != threadId)
			{
				RvaHandle thread = openThread(2, 0, entry.th32ThreadID);
				SuspendThread(thread);
				CloseHandle(thread);
			}
		} while (Thread32Next(snapshot, &entry));
	}

	++g_Rva013373C4DialogGeneration;
	g_Rva013373BCTimerTicks = 0;
	g_Rva013373C0DialogClosed = 0;

	Rva0088E100Context context;
	context.processId = processId;
	context.threadId = threadId;
	context.snapshot = snapshot;
	context.openThread = openThread;

	RvaDword watchdogId;
	RvaHandle watchdog = CreateThread(0, 0, Rva0088E100WatchdogThread, &context, 0, &watchdogId);
	unsigned int timer = SetTimer(0, 0, 1000, Rva0088E190TimerTick);

	LeaveCriticalSection(&g_bfmeCsDWC);

	g_rva0088E000WindowText = windowText;
	g_rva0088E000MessageText = messageText;

	int result = DialogBoxIndirectParamA(0, g_Rva012D4FD0AssertCrashTemplate, 0,
		Rva0088E000DialogProc, 0);

	unsigned char watchdogRanFirst = 0;
	RvaDword exitCode;
	if (GetExitCodeThread(watchdog, &exitCode) && exitCode == 1)
		watchdogRanFirst = 1;
	g_Rva013373C0DialogClosed = 1;

	if (timer != 0)
		KillTimer(0, timer);

	EnterCriticalSection(&g_bfmeCsDWC);

	if (openThread != 0 && watchdogRanFirst == 0)
		Rva0088E090ResumeOtherThreads(openThread, snapshot, processId, threadId);

	CloseHandle(snapshot);
	return result;
}
