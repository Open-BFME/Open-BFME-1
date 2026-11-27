# Complete native RunTmChk initsect.obj reconciliation

2026-11-20 private worker handoff. Root holds the six central reservations,
lease3cd7663c517d41d3b11afaf5a04770e0, and exclusively owns production, normal
admission, Git and publication. This worker changed none of those. Ready source:
RtcSections.cpp.txt, identical to build/agent-transport-20261120/rtc-RtcSections.cpp.
Proper destination: game/Libraries/Source/CRT/VS2003/RtcSections.cpp.
Final source SHA256:
1fbccad2c24d9b5e1c1b6a0ca37adbca76e6c4588805dc5f0e7d23500f3d2431.

## Whole original member and current coverage

The source reconstructs the complete native RunTmChk.lib member
..\build\intel\dll_obj\initsect.obj: two functions and four strong external
data objects, no additional external code/data. Its SHA256 is
efc01337217523dc22b222bdcad9a515ae4f84cf551cc765195f8831efd4731f.
The original library SHA256 is in rtc-readonly-context.json and the manifest.

| Original COFF name | RVA | Bytes | Current source/status |
| --- | --- | ---: | --- |
| __RTC_Initialize | 009F7F0A | 68 | RunTmChk.lib; library, no authored C++ |
| __RTC_Terminate | 009F7F4E | 68 | same library; opaque RunTmChk_twin row with object-symbol=__RTC_Terminate |
| ___rtc_iaa | 00DDF278 | 4 | VA011DF278, .rtc$IAA -> .rdata |
| ___rtc_izz | 00DDF4F4 | 4 | VA011DF4F4, .rtc$IZZ -> .rdata |
| ___rtc_taa | 00DDF5F8 | 4 | VA011DF5F8, .rtc$TAA -> .rdata |
| ___rtc_tzz | 00DDF874 | 4 | VA011DF874, .rtc$TZZ -> .rdata |

Native progress.source_lane reports library for both functions; neither is an
existing C++ success. The default open_dumps predicate excludes library rows;
this is the explicitly assigned original-CRT-source reconciliation lane, not
a renewed dump-queue claim. Relevant old attempts only repaired61->68B extents
and recorded two locate_source blockers for the Terminate DIR32 debt. No prior
C++ reconstruction was found. Original extent evidence remains
session5-rtc_init-extents.md. The private row reads and local-claim check preceded
any reconstruction probe; Root then confirmed all six reservations.

After proper normal acceptance the candidate moves136 existing exact function
bytes from prebuilt library to genuine C++. It owns16 data bytes. It adds no
second native-byte coverage, runtime feature, crash fix or memory optimization.
All four data rows and both functions must be reconciled together before
publication: leaving one function in the archive can select its whole member
and duplicate already-authored definitions. Root decides a coherent preparation
and per-body commit sequence under the current project/user rules.

## Independent identity resolves the historical twin

Identity correction at `0x009F7F4E`: retire the exact old claim
`?RunTmChk_twin_009f7f4e@@YAXXZ` in favor of `__RTC_Terminate`.
The following independent native startup bindings prove that replacement.

The old library check masked the two bodies' relocations and correctly did not
infer the second function's identity from their equal opcodes. This recovery
does not infer it from the same shape again.

Original crtexew.obj at the current native PE entry _WinMainCRTStartup,
RVA009F72C4, has an external REL32 __RTC_Initialize at+0xAF that resolves
DIRECTLY to009F7F0A. Its separate external DIR32 __RTC_Terminate at+0xE1 is
VA00DF7F4E, i.e.RVA009F7F4E, passed as the atexit callback. Native COFF names,
positions, kinds and actual retail operands are recorded in rtc-readonly-context.
These are independent, already-identified startup references, not aliases
created from these two candidate bodies or existing data-address guesses.

Those independently identified functions' original member relocations then bind
Initialize to IAA/IZZ and Terminate to TAA/TZZ. At+0x0F their raw COFF addend is
4, giving opening operands011DF27C /011DF5FC. At+0x16 the ending addends are0,
giving011DF4F4 /011DF874. Thus the actual start datums are011DF278 /011DF5F8.
Each row owns only4B, not the much larger range of other units' callbacks.

Correct the old opaque row to the real __RTC_Terminate identity through normal
--replace-rva/--correct-identity/--identity-evidence; do not retain an alias.
Its existing dir32 debt key uses the code VA00DF7F4E. After the real function
row is admitted, retire that debt with repair_queue pass-test. Do NOT invent
a data row over executable code merely because the queue's generic text says
to give a datum a data row.

## Types and storage, including a donor correction

The original object defines exactly four4B null arrays in .rtc$IAA/IZZ/TAA/TZZ,
each with flags0x40300040: initialized, readable,4-byte aligned, NOT writable.
Its .drectve is the actual /MERGE:.rtc=.rdata directive. The authored declarations
reproduce all four original section names, complete flags,4B extents, values
and empty relocation sets under the normal native compiler. No whitelist,
address rename, section exception, import trick or gate change is used.

Native CodeView adds an important type fact beyond the B2 source: the array
elements are CONST near32 function pointers, pointer_attrs0x40A, to void/cdecl
zero-argument functions. The B2 declarations have read-only sections but omit
the C++ pointer const qualifier. The final B1 source uses explicit `extern const
RtcCallback` arrays and `const RtcCallback*` iterators. Explicit extern preserves
the native strong external C linkage of namespace-scope constants. All four
array contracts and both void/cdecl/no-argument function types/code sizes match
the ORIGINAL native CodeView records exactly. A private /Z7-only probe proves
this; production source has no /Z7. Both source bodies remain byte-identical
after the const repair. See rtc-codeview-type-proof.json.

## Complete C++ code and real SEH proof

Native compiler13.10.3077, /O1 /G7 /Oy- /Ob1 /MD, preserving the inspected B2
CRT profile explicitly in the B1 TU. No global option was changed. Each body
is a genuine C++ pointer loop beginning at start+1 and excluding end. Each
nonzero callback is enclosed in its own __try / __except(1), after which the
loop continues. There are no naked, __emit, inline-assembly or lifted bodies.

Both full68B code sections are RAW-BYTE identical to their native member,
including original in-place addends. Every external relocation name, offset
and kind also matches the original. Ordinary native compile_function for the
authored C++ rows independently reports strict_equal=true, masked=false,
unresolved=[],68B each. There are exactly two emitted code definitions.
Each complete compiled function ends in RET+0x43: Initialize ends at009F7F4E,
Terminate at009F7F92, exactly the next independently proven boundaries. The
filter/handler bytes inside each68B extent are included; no epilogue is cut.

DIR32 matching alone does not prove the two private compiler scope tables.
rtc-seh-and-provider-proof.py separately resolves and compares ALL12B per table:

- Initialize scope VA01145C80: ffffffff377fdf003b7fdf00.
- Terminate scope VA01145C90: ffffffff7b7fdf007f7fdf00.

Both have enclosing state-1; filter points to the OWN function+0x2D and handler
to its+0x31. Each relocation is proved as a pointer into its own complete code
section before the12B table is compared with retail. No generic C++-FuncInfo
graph is claimed as proof for this SEH form. These are private compiler data,
not new external data-ledger ownership claims or new label pins.

The compiler-generated REL32 calls resolve normally to the current native
__SEH_prolog at009F7E88(59B) and __SEH_epilog at009F7EC3(17B). Their original
libc.lib/sehprolg.obj row/member/archive hashes and existing-library comparisons
are recorded; the latter are accurately labeled library-masked. The prolog's
one handler DIR32 is independently bound to the complete FF25 import thunk
at VA00DF6C50, bytesff25c0923501, and IAT013592C0 -> MSVCR71.dll!_except_handler3.
No provider, pin, helper identity or import entry was changed.

## Complete-member native link contract

rtc-link-member-probe.py performs two real, non-executed MSVC7.1 links with
original RunTmChk.lib,msvcrt.lib and kernel32.lib. The synthetic harness supplies
one named probe callback per .rtc$IMC/.rtc$TMC and calls the REAL two routines;
it does not stub any member function, sentinel or CRT/Win32 provider.

The control map gives both functions and all four sentinels to
RunTmChk:initsect.obj. The candidate map gives all SIX to the authored object,
with the original initsect member unselected and no duplicate/unresolved
definition. In both PEs each .rtc start is zero, its probe callback is at+4,
its ending sentinel at+8, all merged into non-writable .rdata. This proves
bounded sorted-range, strong-ownership and section contracts, not the full
game's eventual initializer order, final image placement or startup. No EXE
was executed. A first control correctly exposed ordinary Win32 imports;
adding the genuine kernel32.lib resolved them, with no test replacement.

## BFME2 evidence and reproducible artifacts

Frozen donor HEAD147fd3e52b36ee0306aaeef5b316beb09f7c7671,
Code/Libraries/Source/CRT/RtcSections.cpp SHA256
2da89f3a8acd1319b940ccc55df2e9fb8acf6e329acdd30a45c70a93095ab55d.
Read the complete unit, its four data rows, both native-code rows, and
reverse/attempt_support/0x00629bf0-crt-runtime/{readme.md,check_sections.py}.
That tracked evidence explains the+4 addends, complete member retirement,
true per-callback SEH and bounded genuine link proof. B1 addresses, original
CodeView const types, native bodies and scope tables are independently
reconciled here; no donor address or claimed runtime outcome is transplanted.
The donor is shallow; its original CRT commit history is unavailable locally.

Private reproductions, repository cwd and normal environment.ps1, BUILD_POOL<=4:

1. rtc-readonly-context.py -- original rows/member hashes and startup/boundary
   identities; no compiler or mutation.
2. rtc-native-source-probe.py -- normal-flags private source compile, both strict
   functions, complete original raw-code/external-relocation contract and data.
3. rtc-codeview-type-proof.py -- private diagnostic /Z7 copy; all six actual types.
4. rtc-seh-and-provider-proof.py -- both complete scopes, bounds and existing
   runtime provider/import bindings; only private extraction outputs.
5. rtc-link-member-probe.py -- original/member control and candidate links/maps.
6. rtc-package.py -- ready source copy and hash-bound rtc-package-manifest.json.

rtc-admission-commands.py.txt contains normal CLI argument lists for Root's
review: four data admissions, two function admissions with real identity
correction, the exact Terminate debt pass-test, normal data/source checks and
original startup-consumer build. Root decides coherent preparation/commits.
This worker ran NONE of those writers, commits, production gates or claims.

## Root staged normal admission outcome

The initializer was admitted and committed independently first, with all
four typed4-byte data objects. The termination body was then added as its
own source change and admitted with the exact old identity named above.
Both complete normal rows pass2/2 with all4 DIR32 references; all4 data
objects pass. Native repair_queue pass-test removes exactly the preexisting
__RTC_Terminate code-address debt line. The original511-byte startup plus
the completed RTC unit pass together3/3 and32 DIR32 references; declared-
unmatched reports no remaining definition. The final source matches the
private full-member source SHA256 above. Publish the coupled member only
after its separate termination commit is verified.

The historical deletion record for __RTC_Terminate at009F7F4E forbade
restoring an identity inferred only from archive order/masked twins. The
original PE-entry atexit DIR32 relocation plus the independently different
TAA/TZZ references now distinguish that identity, as documented above.
Following check_csv's explicit revival requirement, Root removed exactly
that one old deletion record through terminator-preserving ledger_io.
The generated placeholder and superseded opaque-twin deletion records
remain. No reusable gate exemption or new alias/pin was introduced.
