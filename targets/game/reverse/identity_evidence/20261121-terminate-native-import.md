# Native terminate import callable

Ready for root-only ordinary new-body admission. Private first source form and
diagnostic Z7 compile both match the complete six-byte native callable strictly:
no masked fallback and no unresolved target. No productive source, ledger, pin,
claim, Git state, shared compiler object or original library was changed.

Proposed source: `game/Libraries/Source/CRT/VS2003/TerminateImport.cpp`.
Candidate SHA256:
`10879e752b3919b4d1600a86cb47dff75270c3c3764e16083b45e410397190c9`.
Files: `TerminateImport-CANDIDATE.cpp`, `TerminateImport-CANDIDATE.patch`,
`proof.json`; repro `../probe-b1-terminate-provider.py`.

The existing native language reference is BFME2 donor revision
`147fd3e52b36ee0306aaeef5b316beb09f7c7671`,
`Code/Libraries/Source/CRT/CxxThrowExceptionImport.cpp` and
`reverse/attempt_support/0x0062af26-d3dx-imports/README.md`. VC7.1 __identifier
spells an actual native import-pointer name containing decoration characters.
The C declaration's ordinary leading underscore produces exactly the native
COFF name; this is not a linker alias or forced binding. Root explicitly
approved this exact genuine strong-UNDEF-reference approach before compilation.

Independent B1 identity and ABI:

- Retail RVA009F7EDA is exactly `FF2524923501`, through IAT VA01359224.
  The actual PE import directory identifies MSVCR71.dll!?terminate@@YAXXZ.
- Original msvcrt.lib native i386 CODE short-import member SHA256
  `3f9c480fae4759682d55c27f45d0a79d0668704da59123da8a96f797fef4a993`
  publishes `?terminate@@YAXXZ` and `__imp_?terminate@@YAXXZ` in both original
  archive indexes. No library or original CODE fact is changed.
- Public VC7.1 eh.h declares `__declspec(noreturn) void __cdecl terminate(void)`
  and `typedef void (__cdecl *terminate_function)()`. /D_CRTIMP= makes the public
  function declaration local; it does not change the real imported IAT pointer.
- The original ehvecdtr.obj filter and ArrayUnwind SEH path independently carry
  REL32 references under exactly `?terminate@@YAXXZ`, selecting RVA009F7EDA.

The actual candidate object contains exactly one real external code definition,
`?terminate@@YAXXZ`, complete6B `FF2500000000`, and exactly one strong undefined
IAT external, `__imp_?terminate@@YAXXZ`. Its only code relocation is
`DIR32 +2 -> __imp_?terminate@@YAXXZ` with zero addend. No substitute datum,
static IAT definition, weak edge, alternate spelling, DEF, FORCE or INCLUDE is
used. Candidate CodeView proves the function and IAT pointee agree exactly:
void return, cdecl CC0, zero arguments. Both normal/Z7 code and relocation
contracts agree.

Root's reserved new-body admission:

`python3 tools/add_match.py "?terminate@@YAXXZ" 0x009F7EDA 6 game/Libraries/Source/CRT/VS2003/TerminateImport.cpp --model MODEL --notes "Native MSVCR71.dll terminate callable; original CODE-import member and both indexes; exact IAT VA01359224; public eh.h cdecl void zero-argument ABI; BFME2 native __identifier reference donor147fd3e"`

Then normal source verification and
`python3 tools/import_binding.py check game/Libraries/Source/CRT/VS2003/TerminateImport.cpp`
must establish ordinary current-object and source-owned/selected-IAT/PE proof.
The previous route-pin refusal remains unchanged and is not bypassed; this is
an actual new source body with the real native callable name. No private
build/ object supplies normal currency or admission evidence. No full-image,
runtime, crash or performance result is claimed.

Normal root follow-up: native eligibility reports this complete address outside
retired/no-ground-truth/deferred work and without an existing row. Ordinary
add_match admitted1/1 exact6B with its real name. The unchanged import_binding
check then passed the ordinary current source/object gate and actual isolated
strict link, proving that the selected source-owned callable reaches precisely
MSVCR71.dll!?terminate@@YAXXZ through its genuine strong IAT cell. Frozen input
hash equality passed; no original library was edited and no fixture executed.
The resulting receipt is preserved in session diagnostics. These are normal
source/provider proofs, not a whole-game link or runtime result.
