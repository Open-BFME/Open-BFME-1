# Startup exit-table native type correction

The earlier WinMainStartup.cpp.txt donor adaptation used `typedef int (__cdecl *ExitProc)()` and was type-wrong for __onexitbegin/end despite exact code. Do not use that earlier template without startup-exit-types.patch. No successful byte check is a substitute for this correction.

Both original native msvcrt members `atonexit.obj` and `crtexew.obj` independently record the same global type: nonconst32-bit pointer to nonconst32-bit pointer to void-cdecl-no-argument callback (pointer attrs0xA at both levels). This differs from the public `_onexit_t` int-return callback ABI, which the native `_onexit` function itself does use. Original CodeView data and function records preserve this distinction.

The smallest source correction changes the Startup ExitProc typedef to void-return and the Shims global declaration from opaque void* to a typed pointer to void callback pointer. No executable statement changes. `startup-exit-types.patch` contains exactly this edit in two production paths; only the parent applies it.

Private `startup-exit-types-compile-proof.json`: Startup under unchanged normal flags passes2/2 strict with complete raw code and every relocation identical to the current normal object. Corrected Shims under diagnostic Z7 passes20/20 strict and all raw code/relocations equal the current normal object. Its sole use is comparison of pointers, so the native table type is now explicit without changing behavior.

`startup-exit-types-CV-proof.json` compares the exact full data type graph for original atonexit, original crtexew, corrected Startup Z7 object and corrected Shims Z7 object. All agree on the void-return table type. A separate Startup Z7 check retains exact86/511B and strict matches; its sole relocation-name change is the compiler-local SEH table label `$T55007` to `$T55008`. The normal production-flags probe retains the label too. Z7 is diagnostic only and absent from the patch.

The startup source uses no local definitions of these data, so the native atonexit COMMON remains the owner until a separately reserved complete-member reconstruction succeeds. No data duplication, import alias, new pin, guard exception or gate change is introduced. Normal parent build/source/provider/data checks remain the admission authority. No new exact byte/task or runtime claim is made for this correction.

Replacement source templates and all proof SHA256 values are in startup-type-correction-manifest.json. The previous startup manifest's bytes/SEH findings concern identical executable code; this addendum supersedes its insufficient global-type audit and its old source hash. Preserve both records to retain the correction trail.
