// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /O2 /Ob0
// KERNEL32.dll InterlockedExchange import thunk at retail 0x0005B790.

#include <windows.h>

long __stdcall Rva0005B790InterlockedExchange(long *target, long value)
{
	return InterlockedExchange(target, value);
}
