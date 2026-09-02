// cl: /DNDEBUG /MD /EHsc
// Retail 0x009031A0: current thread owns the DX8 device lock.

extern "C" unsigned long __stdcall GetCurrentThreadId(void);

class DX8Wrapper
{
public:
	static int Owns_Device_Lock(void);

private:
	static unsigned long OwnerThreadId;
	static unsigned LockCount;
};

// ?Owns_Device_Lock@DX8Wrapper@@SAHXZ
int DX8Wrapper::Owns_Device_Lock(void)
{
	if (GetCurrentThreadId() == OwnerThreadId && LockCount > 0)
		return 1;
	return 0;
}
