# BFME1 complete libc init.obj -> RtcInit.cpp

Private source and evidence only. Root owns the four claimed RVAs and all
productive source, pin, data, ledger, admission, commit and publication work.
Exactly one C++ source form was tried; no codegen/flag sweep or second source
variant was needed. No Microsoft CRT implementation source was read.

## Ready source

- Private complete file: `rtc-init-CANDIDATE.cpp`; SHA256
  `4d8ada930667509f392442519f803ed9a0a175203e4ee751b4451172e7a747c4`.
- Proposed actual destination:
  `game/Libraries/Source/CRT/VS2003/RtcInit.cpp`.
- Creation patch: `rtc-init-CANDIDATE.patch` (not applied).
- Native flags: `/O1 /G7 /Ob1 /MD`; public `<rtcapi.h>` only.
- `_RTC_InitBase`: function-local `static bool init=false`, sets it true before
  invoking `_RTC_SetErrorFunc(_CRT_RTC_INIT(0,0,0,1,0))` once.
- `_RTC_Shutdown`: invokes `_CRT_RTC_INIT(0,0,0,1,1)`.
- No import-provider function, asm, fake alias, address-named datum, global
  replacement for the local flag, alternate name, extra helper, or header edit.

## Independent BFME1 facts and complete native checks

Original archive is the current actual VC7.1 `libc.lib`; exact selected member
is `..\build\intel\st_obj\init.obj`, SHA256
`77ef523b3c1c4c82e6b611beb8692376ad70ce2550c4e83a1543614e03d36cf3`.
The whole original member contains exactly two external function definitions,
38+18=56 bytes total; the candidate emits exactly the same two functions and
no further functions. Both complete raw code bodies **and all original COFF
relocation tuples** are identical, before retail address resolution.

| Original public symbol | BFME1 RVA | Complete bytes | Current ordinary name map | Independently augmented PRIVATE route map |
| --- | --- | --- | --- | --- |
| __RTC_InitBase | 009F757F | 38 | unresolved __CRT_RTC_INIT | strict exact38, no masked fallback/unresolved |
| __RTC_Shutdown | 009F75A5 | 18 | unresolved __CRT_RTC_INIT | strict exact18, no masked fallback/unresolved |

The ordinary symbol map was never changed. Only a private in-memory copy adds
the independently proven real `__CRT_RTC_INIT -> 0x009F8088` route for these
byte probes. This is **not normal admission**. Native DIR32 data operands are
copied by the ordinary byte verifier; their independent address/type/storage
proof is explicitly below, not inferred from byte equality.

Full extents: InitBase ends RET at 009F75A4; Shutdown starts immediately at
009F75A5, ends RET at 009F75B6, then a physical INT3 at 009F75B7. The original
native function sections have precisely38 and18 bytes, not cut prefixes.

InitBase relocations:

| Function offset | Kind | Original and candidate target |
| --- | --- | --- |
| +4 | DIR32 | ?init@?1??_RTC_InitBase@@9@4_NA |
| +18 | DIR32 | same exact local |
| +24 | REL32 | __CRT_RTC_INIT -> 009F8088 |
| +30 | REL32 | __RTC_SetErrorFunc -> existing009F8071 |

Shutdown has one REL32 at +10 to the same real import route009F8088.
InitBase passes five4-byte arguments `(0,0,0,1,0)` to that route, then pushes
returned EAX to the setter and cdecl-cleans24 bytes. Shutdown passes
`(0,0,0,1,1)` and cleans20 bytes. Public rtcapi.h independently declares the
five-argument cdecl callback-returning `_CRT_RTC_INIT` and the typed setter.
The header's `_RTC_error_fn` is the real cdecl variadic diagnostic callback,
not an invented void*, integer or guessed calling convention.

## Once flag: original local identity, not a new external global

Exact original and candidate COFF name:
`?init@?1??_RTC_InitBase@@9@4_NA`.

- COFF storage3=STATIC, type0, value0, no auxiliary records.
- Native `.bss` section extent1, raw_pointer0, zero relocations,
  characteristics0xC0101080; ordinary candidate has identical storage metadata.
- Original CodeView and fresh candidate `/Z7` CodeView both contain the same
  `S_LDATA32` local `init`, type index0x30 (`bool`, size1), record bytes
  `11000c1130000000000000000000696e697400`.
- Both actual retail DIR32 operands bind it to **VA0134FB84 / RVAF4FB84**.
- This lies in the virtual-only tail of retail `.data`: offset699268,
  SizeOfRawData299008, VirtualSize733184. The standard PE zero-fill semantics
  and the repository's normal `reloc_ledger.Image.read(VA,1)` prove **00**.
- `build.read_target_bytes` blindly maps beyond this section's raw extent and
  returns backing-file byte59. That value is retained only as a raw-reader
  limitation, explicitly **not** initial memory contents.

The real object is TU-local STATIC; `add_data_match` requires EXTERNAL and is
not an appropriate reason to change this storage. Existing body_guard handles
the actual local BSS case (its static uninitialised branch is skipped), while
the independent native/PE evidence above establishes its identity and zero
initialisation. Root should preserve the genuine function-local declaration,
not create a global datum/pin merely to satisfy a different data writer.

Fresh candidate CodeView proves the defined parent procedures as void/cdecl,
zero arguments. Its optimisation need not emit called extern prototypes;
the import callback ABI is established by the public header and actual call
sequence, not overclaimed as a native called-prototype CodeView record.

## Genuine original CODE-import callee and normal routing prerequisite

Target009F8088 is exactly `FF 25 50 92 35 01`, an indirect jump through
**IAT VA01359250**. The actual BFME1 PE import directory reads
`MSVCR71.dll!_CRT_RTC_INIT` there. The existing matched gen-import row at that
RVA names that same target; it is left unchanged.

Independent pristine `msvcrt.lib` native short-import member:

- x86 native **CODE** kind0, public COFF identifier `__CRT_RTC_INIT`.
- DLL `MSVCR71.dll`; normal name-type decoration yields export `_CRT_RTC_INIT`.
- Exact short member SHA256
  `65df43d1aba958c5b4ac70389c342f15c06ee2e735e2d5655c8b67d9abc1808b`.
- **Both** original archive indexes bind `__CRT_RTC_INIT` and
  `__imp___CRT_RTC_INIT` to precisely that original member.
- Original native init.obj and clean candidate both name this same real
  undefined callable; no arbitrary six-byte implementation is introduced.

Normal readonly native `pin_consistency.route_verdict` returns admissible
(`None`) for:

```
name = __CRT_RTC_INIT
address = 0x009F8088
route=MSVCR71.dll!_CRT_RTC_INIT
```

No pin was written. `pin_consistency.py --symbol __CRT_RTC_INIT` confirms no
current pin. Root must take the ordinary genuine routing dependency together
with the first new parent and run its normal pin checks and source admission.
The native check derives DLL/export, FF25 endpoint and matched gen-import
identity from current inputs; the note is not an author-supplied alias waiver.

## Donor, scope and verification limits

BFME2 donor is fixed revision147fd3e52b36ee0306aaeef5b316beb09f7c7671,
`Code/Libraries/Source/CRT/RtcInit.cpp` (history's source-introducing commit
b5a7b8290a). It supplies the simple recovered control flow, public header and
compatible flags. Its once address00A1F540 is **not** reused. Original BFME1
member, parent extents, COFF/local-CV facts, retail pointer operands, native
original CODE member, import directory and native route verifier provide the
separate target proof.

Private objects live under
`build/agent-melee-20261120/rtc-init-whole/`; JSON is
`rtc-init-whole-member-proof.json`. Reproducers are
`probe-b1-rtc-init-whole.py` and `finalize-b1-rtc-init-proof.py`.

The source under build/ is intentionally in an unwatched include-search root,
so the native builder refuses a reusable cache receipt. `compile_is_current`
is **false** there by policy. Separating private src/obj directories confirmed
this; the original suggestion of an include race was unproved and withdrawn.
These are fresh private diagnostic objects, never a reusable normal build.
All original/member/source/public-header hashes were checked unchanged after
the proof. Root still owes normal source-path verification, actual callee-route
admission, ordinary gates and its separate verified-body commits. Both bodies
should publish coherently because the old library owner is one whole member.

No isolated closure link was required or run; no game, EXE or native fixture
was executed. No normal-link, startup, runtime, memory or crash improvement is
claimed. Potential authored C++ coverage is the two56-byte parent bodies only
after Root's actual admissions; the import route is not a recovered C++ body.
