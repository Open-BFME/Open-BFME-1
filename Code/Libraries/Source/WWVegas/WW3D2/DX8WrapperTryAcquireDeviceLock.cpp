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
	static volatile unsigned long OwnerThreadId;
	static volatile unsigned LockCount;
};

unsigned char DX8Wrapper::Try_Acquire_Device_Lock(unsigned long timeout)
{
	if (WaitForSingleObject(WaitHandle, timeout) == 0x102)
		return 0;
	EnterCriticalSection(CriticalSection);
	OwnerThreadId = GetCurrentThreadId();
	++LockCount;
	LeaveCriticalSection(CriticalSection);
	return 1;
}
