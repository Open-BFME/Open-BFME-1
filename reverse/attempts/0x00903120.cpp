// ?Try_Acquire_Device_Lock@DX8Wrapper@@SAEK@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00903120: try-acquire the DX8 device lock with a timeout.

extern "C" unsigned long __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *criticalSection);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *criticalSection);

class DX8Wrapper
{
public:
	static unsigned char Try_Acquire_Device_Lock(unsigned long timeout);

private:
	static void *WaitHandle;
	static char CriticalSection[24];
	static unsigned long OwnerThreadId;
	static unsigned LockCount;
};

// ?Try_Acquire_Device_Lock@DX8Wrapper@@SAEK@Z
unsigned char DX8Wrapper::Try_Acquire_Device_Lock(unsigned long timeout)
{
	if (WaitForSingleObject(WaitHandle, timeout) == 0x102)
		return 0;
	EnterCriticalSection(CriticalSection);
	*(volatile unsigned long *)&OwnerThreadId = GetCurrentThreadId();
	++LockCount;
	LeaveCriticalSection(CriticalSection);
	return 1;
}
