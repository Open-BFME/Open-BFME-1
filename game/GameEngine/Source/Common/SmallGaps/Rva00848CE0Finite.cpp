// cl: /O2 /EHsc /MD
// 0x00848CE0 -- STLport _Stl_is_inf over a double: pass the incoming double
// through to the CRT _finite import and fold the int result into a bool.
// IDENTITY IS NOT RECOVERED for the wrapper name; the spelling is the
// address-derived placeholder. The _finite import is what retail calls
// through IAT slot 0x013592CC.
//
// WHAT THE BYTES SHOW. The body loads the 8-byte double at [esp+4], rebuilds
// it on the frame (`sub esp,8 / fstp [esp]`), calls _finite, drops the frame,
// then folds eax with `neg eax / sbb eax,eax / inc eax`. That tail is the
// MSVC 7.1 `!call()` shape from shape_levers.md: the CRT returns nonzero for
// finite, and the wrapper returns that value negated into a bool.
//
// Compare the sibling at 0x00848D30, which calls _fpclass through slot
// 0x013592D0 and pre-adjusts the class code (`sub eax,4`) before the same
// fold: it classifies one fpclass value, while this body tests finiteness.

extern "C" __declspec(dllimport) int __cdecl _finite(double);

// ?dup_00848ce0@@YA_NN@Z
bool dup_00848ce0(double value)
{
	return !_finite(value);
}
