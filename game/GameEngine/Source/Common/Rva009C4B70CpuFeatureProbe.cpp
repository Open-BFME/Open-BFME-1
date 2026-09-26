// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x009C4B70 is the cdecl CPU-feature probe called by
// bfmeQueryCpuTierFlags.  CPUID is inline because MSVC 7.1 has no intrinsic
// for it; the surrounding vendor test and SEH remain ordinary C++.
// Keeping the leaf-1 flag test adjacent to CPUID reproduces the retail SEH
// frame and register lifetimes. Moving its result to a C++ local emits 192B
// instead of160B (parent-cpu160 probe), so this short hardware-specific block
// also retains its conditional store and alignment nop.

#include <excpt.h>

extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int);

// ?Rva009C4B70CpuFeatureProbe@@YAHXZ
int __cdecl Rva009C4B70CpuFeatureProbe(void)
{
	char vendor[13];
	int result;

	result = 0;
	__try
	{
		__asm
		{
			lea	esi, vendor
			mov	eax, 0
			cpuid
			mov	dword ptr [esi], ebx
			mov	dword ptr [esi+4], edx
			mov	dword ptr [esi+8], ecx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return result;
	}

	if (strncmp(vendor, "GenuineIntel", 12) == 0
		|| strncmp(vendor, "AuthenticAMD", 12) == 0)
	{
		__asm
		{
			mov	eax, 1
			cpuid
			test	edx, 04000000h
			je	no_sse2
			mov	result, 1
		no_sse2:
			nop
		}
	}

	return result;
}
