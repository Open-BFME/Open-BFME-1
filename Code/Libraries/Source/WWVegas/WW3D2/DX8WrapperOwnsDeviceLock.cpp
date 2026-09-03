// cl: /DNDEBUG /MD /EHsc
// Retail 0x009031A0: current thread owns the DX8 device lock.

extern "C" unsigned long __stdcall GetCurrentThreadId(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
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
