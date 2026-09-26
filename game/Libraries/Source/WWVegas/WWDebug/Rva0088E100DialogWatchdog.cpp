// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
// Open-BFME: the watchdog behind the WWDebug crash dialog. The dialog driver
// at 0x0088E1A0 suspends every other thread, starts a one-second timer whose
// callback is the tick counter below, and starts the watchdog thread. When the
// tick counter stops advancing the message pump is stuck, so the watchdog lets
// the suspended threads run again.

typedef void *RvaHandle;
typedef unsigned long RvaDword;
typedef RvaHandle(__stdcall *RvaOpenThreadFn)(RvaDword access, int inherit, RvaDword threadId);

struct Rva0088E100Context
{
	RvaDword processId;
	RvaDword threadId;
	RvaOpenThreadFn openThread;
	RvaHandle snapshot;
};

extern "C"
{
	// Written by the dialog driver at 0x0088E1A0 and by the timer callback.
	extern long g_Rva013373BCTimerTicks;
	extern unsigned char g_Rva013373C0DialogClosed;
	extern long g_Rva013373C4DialogGeneration;

	__declspec(dllimport) void __stdcall Sleep(RvaDword milliseconds);

	void Rva0088E090ResumeOtherThreads(RvaOpenThreadFn openThread, RvaHandle snapshot,
		RvaDword processId, RvaDword keepThreadId);
}

extern "C" void __stdcall Rva0088E190TimerTick(RvaHandle, unsigned int, unsigned int, RvaDword)
{
	++g_Rva013373BCTimerTicks;
}

extern "C" RvaDword __stdcall Rva0088E100WatchdogThread(void *parameter)
{
	Sleep(3000);

	long generation = g_Rva013373C4DialogGeneration;
	long seconds = 3;
	while (!g_Rva013373C0DialogClosed)
	{
		if (seconds - g_Rva013373BCTimerTicks >= 3)
		{
			if (!g_Rva013373C0DialogClosed && generation == g_Rva013373C4DialogGeneration)
			{
				const Rva0088E100Context *context = (const Rva0088E100Context *)parameter;
				Rva0088E090ResumeOtherThreads(context->openThread, context->snapshot,
					context->processId, context->threadId);
				return 1;
			}
			break;
		}
		Sleep(1000);
		++seconds;
	}

	return 0;
}
