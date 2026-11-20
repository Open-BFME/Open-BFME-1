# Native CRT initializer sentinels: four complete data objects

2026-11-20, read-only/private-probe worker handoff. Root exclusively owns
reservations, production source, ledgers, normal admission, commits and release.
This worker changed none of those. All compiler/linker outputs are private
under build/agent-transport-20261120; reports are here in agents/transport.

## Actionable family and exact home

Proposed production source:
`game/Libraries/Source/CRT/VS2003/CInitExe.c`.
Ready source is `build/agent-transport-20261120/crt-CInitExe.c`; copy it unchanged.
Its proper native unit is the public msvcrt.lib member
`build\intel\dll_obj\cinitexe.obj`, which defines ONLY these four data objects.
It defines no code, callback, additional hidden state or other external datum.
The authored source is based on native metadata/retail, not Microsoft CRT
implementation source. All four strong definitions belong together so the
original archive member remains unselected when the source is linked.

| COFF symbol | C spelling | VA | Actual RVA | Bytes | Original subsection |
| --- | --- | --- | --- | ---: | --- |
| ___xc_a | __xc_a | 012A5000 | 00EA5000 | 4 | .CRT$XCA |
| ___xc_z | __xc_z | 012A617C | 00EA617C | 4 | .CRT$XCZ |
| ___xi_a | __xi_a | 012A6280 | 00EA6280 | 4 | .CRT$XIA |
| ___xi_z | __xi_z | 012A6384 | 00EA6384 | 4 | .CRT$XIZ |

The repair queue's target_rva column is a VA for this DIR32 family. Use the
VA form above with `add_data_match --va`, never --rva0x012A5000. Each ownership
extent is one pointer,4B. The entire large ranges between boundaries contain
other objects' initializer contributions and are NOT owned by these data rows.
All four have separate current dir32 debt lines, no named data-row owner and
no function-ledger owner at their true RVAs. Only after normal CLI admission
and each successful pass-test may Root count four debt retirements; no new
function bytes, whole-image link gain or runtime gain is claimed.

## Complete original object and type contract

Original archive:
inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/lib/msvcrt.lib.
cinitexe.obj SHA256:
713513ef14ba3396136739764ce3215f1ef768cf95334ffe91277a4eb2805cf3.

Each original public COFF symbol has storage EXTERNAL(2), value0, its own
initialized section of exactly4B, bytes00000000, no relocations and flags
0xC0300040: initialized data, read/write, 4-byte alignment. The source's four
sections compare exactly with those names, flags, sizes, bytes and relocation
sets under the native compiler. There are no ordinary functions, dynamic
initializers or additional callback pointers in this data-only source.

Original .drectve explicitly contains `/merge:.CRT=.data`; the source carries
that exact merge via the ordinary compiler directive. No tool whitelist,
section admission exception, import/pin, gate change or address rename is used.
Other archive-wide CRT exclusion/default-library directives were not copied
into this data-only owner; the ordinary /MD environment remains in effect.

Native CodeView independently establishes all FOUR data types, including XI:
one-element4B arrays of near32 pointers to a void-returning, cdecl, zero-argument
procedure. Native .debug$S names the _PVFV typedef. The complete array -> pointer
-> procedure records decode to size4, pointer_attrs0xA, return void, calling
convention0, parameter_count0. A private /Z7-only type probe reproduces all four
identical contracts. /Z7 is diagnostic only and absent from the production
proposal. Source typedef and sizeof assertions are therefore evidence-backed,
not an opaque integer/zero stand-in. See crt-codeview-type-proof.json and its
reproducer; no shared class-layout cache was used.

## Native consumers and boundary operands

The current ledger owns `_WinMainCRTStartup`,511B,RVA009F72C4, from the genuine
msvcrt.lib crtexew.obj. Its unmodified original DIR32 relocations bind:

- +0xD2 -> ___xi_z, raw COFF addend0, retail VA012A6384.
- +0xD7 -> ___xi_a, raw COFF addend0, retail VA012A6280.
- +0x121 -> ___xc_z, raw COFF addend0, retail VA012A617C.
- +0x126 -> ___xc_a, raw COFF addend0, retail VA012A5000.

The two following calls reach the native msvcr71 _initterm import. They consume
the XI and XC sorted ranges; the opening zero entry is skipped and the ending
sentinel is excluded. These addresses are decoded from native relocation sites,
not guessed from adjacent zero bytes. The four retail destinations are .data,
with all4 bytes zero. Source spells all four COFF names in its provenance
comment as well as their correct C definitions, so the ordinary pass-test's
git-grep source discovery can locate each C/COFF-mangled datum once staged.

## Real isolated linker verification

crt-link-contract-probe.py performs two native MSVC7.1 links with the ORIGINAL
msvcrt.lib, no execution, no test stub for any sentinel/provider:

1. Control: a private entry references all four boundaries and contributes one
   real C callback in .CRT$XIC and one C++ callback in .CRT$XCU. The archive's
   actual cinitexe.obj is selected; the map identifies it as owner of all four.
2. Candidate: same inputs plus the authored source's data object. All symbols
   are supplied once by that object, cinitexe.obj remains unselected, and the
   link succeeds with no duplicate/unresolved definitions.

Both complete maps and PE images show identical addresses and table bytes:
each start is zero, its callback follows at+4, its end at+8; XI/XC contributions
are correctly sorted and merged into writable .data. ICF is disabled as in
native retail. This proves the bounded section/linker-sentinel and archive
selection contract, rather than only four equal zeros. It does not prove the
whole game's final initializer ordering, linked placement or successful start.
crt-link-contract-proof.json preserves exact commands, publics, owners and data.

## BFME2 reference pass

Read-only donor HEAD147fd3e52b36ee0306aaeef5b316beb09f7c7671:

- Code/Libraries/Source/CRT/RtcSections.cpp and its four typed data rows at
  donor VAs00CFD04C/54/58/60 demonstrate genuine allocated sorted sentinels and
  complete ownership of initsect.obj with its two SEH callback walkers.
- Code/Libraries/Source/CRT/WinMainStartup.cpp declares all XI/XC boundaries as
  the same void/cdecl callback-pointer arrays and uses the same two _initterm
  ranges. Its provenance is retail/COFF and public declarations.
- reverse/attempt_support/0x00629bf0-crt-runtime/readme.md records ordinary
  data gates, the +4 opening addends and a bounded successful link while retiring
  native CRT members together. The startup readme records a real duplicate
  caused by separating a callback from its strong archive-owned flag, repaired
  by reconciling the complete member. That is why all four cinitexe data
  definitions are proposed together here.

No direct XC/XI data-row donor was found. The donor repository is shallow; local
history does not expose its original CRT landing commits. These frozen source
and tracked verification records are the inspected donor evidence. Native B1
metadata independently establishes every type/address/section above; no B2
address, path, member length or runtime outcome is transplanted.

## Related RTC family, separate prerequisite

Native initsect.obj also defines four4B read-only .rtc sentinels, but it owns
both68B _RTC_Initialize/_RTC_Terminate code bodies as well. Data-only duplicate
definitions would select the original member for those functions and collide;
reconcile that complete unit separately, following the actual B2 donor.
Correct B1 VAs: ___rtc_iaa011DF278, ___rtc_izz011DF4F4,
___rtc_taa011DF5F8, ___rtc_tzz011DF874. The opening consumer relocations have
COFF ADDEND+4. Current startup_tables.delimiters reports the advanced operands
011DF27C/011DF5FC; those are NOT the opening sentinel's base. Use the native
addend subtraction in crt-coff-contract.json. No RTC source or tool change is
proposed by this handoff, and these are not additional completed tasks.

## Normal Root admission and verification

After central claims and placing/staging the proper source/evidence,
crt-admission-commands.py.txt contains exact sequential NORMAL CLI argument
lists: four add_data_match calls (--va, size4), then four exact served
repair_queue pass-tests, check_csv, ordinary data verification and the exact
original511B startup-consumer build. No direct ledger/baseline editing occurs.
This worker has NOT executed that writer script or any of those mutations.

The normal admission tool's refusal must be reported as a prerequisite rather
than bypassed with a rename/pragma exemption. Normal full project/provider
checks and publication remain Root's responsibility. Source/body proofs here
are private, current and bounded; the four debt retirements are not yet landed.

## Root normal admission outcome

All four data objects passed add_data_match --va --size4 under the ordinary
build profile; data_rows now owns exactly16 bytes in this one source. All
four native repair_queue pass-tests passed and removed only their own
DIR32 debt lines. The original511-byte _WinMainCRTStartup archive member
passes the normal build.cmd row selector, all28 native DIR32 references and
body_guard with no baselined findings. No handwritten ledger or baseline
edit was used. This is four data/debt repairs, not recovered C++ code bytes.
