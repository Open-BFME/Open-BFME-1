// cl: /O2 /EHsc /MD
// Four 35-byte CRT conversion wrappers: 0x00848DA0 and 0x00848E00 forward to
// _ecvt through IAT slot 0x013592B8, 0x00848DD0 and 0x00848E30 forward to
// _fcvt through slot 0x013592C8. IDENTITY IS NOT RECOVERED for the wrapper
// names; every name is derived from its own address.
//
// WHAT THE BYTES SHOW. Each body reads the incoming double at [esp+4], the
// digit count at [esp+0xC], and the two out-pointers at [esp+0x10]/[esp+0x14],
// pushes the three dwords, rebuilds the double on the frame (`sub esp,8 /
// fstp [esp]`), calls the import, and drops all 20 bytes (`add esp,0x14`).
// That is a plain four-argument forwarder returning the CRT pointer:
//
//     char *wrapper(double value, int digits, int *decimal, int *negative)
//     {
//         return _ecvt(value, digits, decimal, negative);
//     }
//
// SEPARATE FUNCTIONS, NOT ALIASES. Four distinct addresses in two identical
// pairs; they coincide in bytes only because a CRT forward has nothing else
// to say. Compare the landed _finite/_fpclass siblings at 0x00848CE0 and
// 0x00848D30, which fold an int result into a bool instead.

extern "C" __declspec(dllimport) char *__cdecl _ecvt(
	double, int, int *, int *);
extern "C" __declspec(dllimport) char *__cdecl _fcvt(
	double, int, int *, int *);

// ?dup_00848da0@@YAPADNHPAH0@Z
char *dup_00848da0(double value, int digits, int *decimal, int *negative)
{
	return _ecvt(value, digits, decimal, negative);
}

// ?dup_00848dd0@@YAPADNHPAH0@Z
char *dup_00848dd0(double value, int digits, int *decimal, int *negative)
{
	return _fcvt(value, digits, decimal, negative);
}

// ?dup_00848e00@@YAPADNHPAH0@Z
char *dup_00848e00(double value, int digits, int *decimal, int *negative)
{
	return _ecvt(value, digits, decimal, negative);
}

// ?dup_00848e30@@YAPADNHPAH0@Z
char *dup_00848e30(double value, int digits, int *decimal, int *negative)
{
	return _fcvt(value, digits, decimal, negative);
}
