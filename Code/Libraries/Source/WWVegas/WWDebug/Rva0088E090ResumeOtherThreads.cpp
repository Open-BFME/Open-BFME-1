// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
// Open-BFME: thread-resume sweep at 0x0088E090. It walks the TOOLHELP32
// thread snapshot it is handed, and for every thread of this process other
// than the one it is told to leave alone it opens the thread, resumes it and
// closes the handle. OpenThread arrives as a function pointer because
// Windows 95 does not export it.

typedef void *RvaHandle;
typedef unsigned long RvaDword;

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

typedef RvaHandle(__stdcall *RvaOpenThreadFn)(RvaDword access, int inherit, RvaDword threadId);

extern "C" int __stdcall Thread32First(RvaHandle snapshot, RvaThreadEntry32 *entry);
extern "C" int __stdcall Thread32Next(RvaHandle snapshot, RvaThreadEntry32 *entry);
extern "C" __declspec(dllimport) RvaDword __stdcall ResumeThread(RvaHandle thread);
__declspec(dllimport) void __stdcall bfmeClose1033(int handle);

extern "C" void Rva0088E090ResumeOtherThreads(RvaOpenThreadFn openThread, RvaHandle snapshot,
	RvaDword processId, RvaDword keepThreadId)
{
	RvaThreadEntry32 entry;
	entry.dwSize = sizeof(RvaThreadEntry32);
	if (!Thread32First(snapshot, &entry))
		return;

	do
	{
		if (entry.th32OwnerProcessID == processId && entry.th32ThreadID != keepThreadId)
		{
			RvaHandle thread = openThread(2, 0, entry.th32ThreadID);
			ResumeThread(thread);
			bfmeClose1033((int)thread);
		}
	} while (Thread32Next(snapshot, &entry));
}
