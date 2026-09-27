// cl: /O2 /EHsc /MD
// 0x00848D30 -- one fpclass value classified into a bool: pass the incoming
// double through to the CRT _fpclass import, adjust the class code (`sub
// eax,4`), then fold with `neg eax / sbb eax,eax / inc eax`. IDENTITY IS NOT
// RECOVERED for the wrapper name; the spelling is the address-derived
// placeholder. The _fpclass import is what retail calls through IAT slot
// 0x013592D0.
//
// WHAT THE BYTES SHOW. Same frame as the 0x00848CE0 _finite sibling (load the
// 8-byte [esp+4] double, `sub esp,8 / fstp [esp]`, call, `add esp,8`), then
// the classification offset before the shared bool fold. Compare the landed
// isInfinite (SmallGaps/isInfinite.cpp), which compares `_fpclass(x)` against
// 4 and 0x200 with branches; this body subtracts one class code and folds, so
// it tests exactly one fpclass value.

extern "C" __declspec(dllimport) int __cdecl _fpclass(double);

// ?dup_00848d30@@YA_NN@Z
bool dup_00848d30(double value)
{
	return (_fpclass(value) - 4) == 0;
}
