// cl: /DNDEBUG /MD /EHsc
// Three identical 19-byte guarded frees at 0x0084D220, 0x0084D2F0 and
// 0x0084D340. IDENTITY IS NOT RECOVERED: no caller, string or vtable names
// the holder, so every name is derived from its own address.
//
// WHAT THE BYTES SHOW. Each body reads one incoming dword, tests it, and on
// null falls through to `ret`. On non-null it tail-jumps through the IAT slot
// for bfmeFree1035 (pinned at 0x00F593D4), reusing its own argument slot for
// the callee's argument. That is `if (p != 0) bfmeFree1035(p);` in tail
// position: the argument is already where the __cdecl callee expects it, so
// no push is needed. The trailing `ret` after the jmp is padding counted in
// the 19-byte extent.
//
// SEPARATE FUNCTIONS, NOT ALIASES. Three distinct addresses that coincide in
// bytes only because a guarded free has nothing else to say.

extern "C" __declspec(dllimport) void __cdecl free(void *p);

// ?dup_0084d220@@YAXPAX@Z
void dup_0084d220(void *p)
{
	if (p != 0)
		free(p);
}

// ?dup_0084d2f0@@YAXPAX@Z
void dup_0084d2f0(void *p)
{
	if (p != 0)
		free(p);
}

// ?dup_0084d340@@YAXPAX@Z
void dup_0084d340(void *p)
{
	if (p != 0)
		free(p);
}
