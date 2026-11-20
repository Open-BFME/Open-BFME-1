# Whole native crtexew.obj GUI startup reconstruction

2026-11-20 private worker handoff. Root owns central reservations for
RVA0x009F726E and0x009F72C4, lease08033328bf8e4bd18d3f35d6a986e2ce, production
source, normal admissions, body commits and publication. This worker performed
only read-only analysis and TWO private whole-TU compilation attempts. No
production/ledger/pin/claim/Git/shared-cache changes, runtime or boot smoke.

Ready source: WinMainStartup.cpp.txt, byte-identical to
build/agent-transport-20261120/startup-WinMainStartup.cpp. Proper destination:
game/Libraries/Source/CRT/VS2003/WinMainStartup.cpp.
Source SHA256: fa7f26055e7e0c590101c76d8be444633011e495a2379047823800e981c83ef9.

## Scope and existing coverage

Original msvcrt.lib member build\intel\dll_obj\crtexew.obj has exactly two
code sections: PRIVATE `_check_managed_app`,RVA0x009F726E,86B, and public
`_WinMainCRTStartup`,RVA0x009F72C4,511B. Both current rows are library coverage,
not already reconstructed C++. The helper ends exactly at the entry start;
the entry includes its real SEH filter/handler through its final RET at+0x1FE.
The old466B Ghidra extent stopped inside that filter and is not used.

This candidate reconstructs597 EXISTING library-covered bytes as C++. It does
not add597 total exact bytes. Root must measure normal native progress after
normal acceptance before crediting any landing. The actual game's `_WinMain@16`
at000600F0 is a different provider and is not reconstructed or stubbed here.
Most earlier WinMain attempt-log blockers concern that game function, not this
CRT unit. The relevant B1 startup defaults/fmode prerequisites are already
properly source-owned and independently evidenced in their existing documents.

Original member SHA256:
2cbdfc510b39eed6f0afd0f894dcda2e98ef1eb0d366acedfaa68567a25aca90.
The native archive, donor and public SDK header hashes are in the manifest.
No Microsoft CRT implementation source was read.

## No new global/data owner

The native member has a single4B COMMON `___defaultmatherr` in addition to
its code/private scope table. That tentative contribution coalesces with the
strong one-valued default flag already provided by StartupDefaults.c. The new
C++ unit merely declares the existing flag; it does not create another copy.
The same existing file supplies the independently proven complete3B _matherr
and _setargv routines; they remain intact native providers, not fabricated
early-return hooks for this reconstruction.

Existing source-owned native defaults are reused by their exact names and
addresses: __fmode0134FBAC; __commode0134FBA8; __adjust_fdiv013571F8;
___defaultmatherr012DBDE0; __newmode0134FBA4; __dowildcard0134FBA0.
Current data rows and actual native bytes are recorded per DIR32 site.
The XI/XC sentinels are the existing CInitExe.c data owners. RTC Initialize and
Terminate remain the real current providers from the separate member recovery.
There are ZERO new external data definitions or COMMONs in the candidate.

`___onexitbegin` atVA01357214 and `___onexitend` atVA01357204 are real4B COMMONs
from the original atonexit.obj, not globals this new TU should define. Their
native COFF storage/value fields and loader-zero retail values are independently
checked and hash-bound. Existing B1 CRT shims already reference the first as a
pointer; this port only declares the typed exit-table pointers and performs the
native all-ones initialization. No existing data owner or shim is replaced.

## Donor/public declarations and bounded probes

Frozen BFME2 donor147fd3e52b36ee0306aaeef5b316beb09f7c7671,
Code/Libraries/Source/CRT/WinMainStartup.cpp SHA256
ad1c1dbc4f4b2ae8ce503184621b6e2c6c614a5f06dcfa93edbbed34d62feac2.
Read its complete source, both86/511B ledger rows and tracked
reverse/attempt_support/0x00629306-crt-startup/{readme.md,check_startup.py}.
Those establish full-member source placement, public SDK PE/Win32 declarations,
native command-byte/DBCS handling, private-helper linkage, complete SEH and
the COMMON/default-provider relationships. The donor is shallow; no original
CRT landing commit is asserted from its truncated local history.

Probe1 failed BEFORE object production: B1's existing //cl parser splits all
whitespace, so the donor-style quoted SDK path was split into invalid flags
and fell back to incomplete sweep windows.h declarations. No function match
was produced. Probe2 used the ALREADY SUPPORTED normal path
inputs/toolchains/vs2003/native/Vc7/PlatformSDK/Include, resolved by the current
toolchain include resolver to the same actual tracked SDK. No tool/parser,
global flags, fake header or include whitelist was changed.

Probe2 preserves /O1 /G7 /Ob2 /MD /D_CRTBLD. The actual SDK windows.h,winnt.h,
winbase.h hashes are recorded. Compile-time assertions independently check4B
pointers,68B STARTUPINFOA, its dwFlags+44/wShowWindow+48, DOS e_lfanew+60,
NT optional-header+24 and PE32/PE32plus directory-count offsets92/108. The source
retains the genuine PE/CLR managed-app test and all original startup/error/exit
paths. No aborting substitute provider or mocked game entrypoint is introduced.
No further reconstruction compilation was performed after probe2.

## Exact code and every relocation binding

Both complete authored code sections are RAW-BYTE identical to the original
archive object before relocation. Native compile_function reports86/86 and
511/511B strict_equal=true,masked=false,unresolved=[]. The static helper retains
storage3 and does not become a public alias. There are exactly two defined
code symbols and no extra code/data emission.

All41 original relocation positions and kinds agree with the authored object.
All names agree too except the independently resolved compiler-local SEH-table
label and ONE existing-provider adaptation described next. All11 REL32 sites
resolve normally to the actual current native providers; all30 DIR32 sites
have separate original/retail/owner/import proof in startup-bindings-proof.json.

The BFME2 __XcptFilter name has no current ordinary B1 symbol-map candidate.
B1 instead already has the verified typed address-owned provider
`?Rva009F7EEC_XcptFilter@@YAHKPAX@Z` in XcptFilterImportThunk.cpp,6B at009F7EEC.
The source declares its actual int/cdecl(unsigned long,void*) interface and
calls it at the original entry's+0x1D3 REL32 position. Its complete native body
ff2558923501 goes through IAT01359258 to MSVCR71.dll!_XcptFilter. This is an
existing true provider at the identical target; no alias,pin or import binding
was added. No existing source/provider was changed.

Every IAT operand is matched to the real PE import by both slot VA and original
COFF imported name (normal C/stdcall decoration only). This includes the two
imported DATA exports _acmdln and _adjust_fdiv as well as callable CRT/Win32
imports. All owned globals and function-pointer operands are separately bound
to their current ordinary ledger rows. Native atonexit COMMONs are checked
against their original definitions rather than given false new data owners.
The existing _initterm/_amsg_exit providers remain their genuine native import
veneers; any future source-owner improvement is separate from this member and
is not claimed as additional coverage here.

## Complete private SEH scope

The source contains the real __try/__except CRT entry. A separate read-only
COFF graph proof resolves ALL12B of its private scope table atVA011458B0:
ffffffff8a74df009e74df00. Enclosing state is-1, filter is the OWN entry+0x1C6
(VA00DF748A), handler its+0x1DA(VA00DF749E). Both code pointers are proved from
local same-code-section symbols/addends before comparing the whole table to
retail. This is not a DIR32-mask-only or generic empty C++-EH proof. The table
remains compiler-private data; no new external data row or label pin is proposed.

## Reproduction and normal handoff

startup-readonly-context.py records the original member's entire code/public/
COMMON/undefined/import context. startup-whole-unit-proof.json records the
SECOND and final private whole-TU probe, source/original/SDK hashes, complete
raw/strict code results and exact footprint. startup-bindings-proof.py is purely
read-only over that object and original PE/archive; it does NOT compile or run
anything. startup-package.py creates the unchanged source copy and hash-bound
startup-package-manifest.json. No runtime, boot smoke, or substituted-WinMain
focused link was performed or claimed.

startup-admission-commands.py.txt contains Root-only NORMAL CLI arguments for
two --replace-existing admissions at the already named RVAs, normal source
declaration check and combined existing-provider checks. There is no data-row
admission for this TU. Root gives each verified body its own commit and keeps
the whole member publication coherent. This worker ran none of those writers,
normal production gates or Git actions. A full-image link/runtime result remains
outside this private matching proof.
