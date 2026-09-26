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

	__declspec(dllimport) void __stdcall bfmeClose1033(int handle);

	extern const char *g_rva0088E000MessageText;
	extern const char *g_rva0088E000WindowText;
	extern unsigned char g_Rva012D4FD0AssertCrashTemplate[];
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
				bfmeClose1033((int)thread);
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

	bfmeClose1033((int)snapshot);
	return result;
}
