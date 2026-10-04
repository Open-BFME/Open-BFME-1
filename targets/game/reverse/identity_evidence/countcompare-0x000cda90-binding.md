# Count-comparator external binding at RVA 0x000CDA90

This is a source-local external-reference correction, not recovery of a semantic
class identity. The old `BfmeThing934G` declaration supplied no layout or definition;
its sole method's existing pin goes to an ILT entry. Independent retail instructions
route both calls to the already-matched canonical provider below. No new name is
invented and no provider, shared header, pin, function row or guard is changed.

## Exact source snapshots

- Base: `5e51cd1ef7541a74e7557dd8240e90ed8196b2a3`
- Source: `game/GameEngine/Source/Common/Rva000CDA90Compare.cpp`
- Before SHA-256: `4f841e4332b065fb5c4c2de339355c713a4c045f0967bffd283d66f6e8301525`
- After SHA-256: `6681540a9c00a7a7c5967610f1f0f503808d54f9ac084edff7828b56cc2f4bb6`
- Correction pair: `BfmeThing934G` -> `Rva0036F910Owner`
- Old undefined member: `?bfmeOne934G@BfmeThing934G@@QAEHXZ`
- Existing provider: `?countCompleteStructures@Rva0036F910Owner@@QAEHXZ`

The exact definition of `Rva0036F910Owner` is copied from
`game/GameEngine/Source/Common/Rva0036F910StructureCompletionCount.cpp`, including
both method declarations, `typedef int ObjectID`, the fields at +0xB8/+0xBC,
and the secondary fields at +0xDC/+0xE0. No header in `game/` or the reference
include tree declares this address-derived type. The unchanged `CastleBehavior`
view is cast to this local ABI view; this does not establish their semantic type
identity. Existing unrelated declarations are unchanged. Header-adoption checks
pass without exemptions.

## Complete retail extent and physical contract

Retail caller is `[0x000CDA90, 0x000CDB77)`, 231 bytes, beginning after 16 bytes of
INT3 padding and ending in RET at 0x000CDB76 before 16 bytes of INT3 padding.
Every instruction in the extent decodes; all control-flow returns are included.
Its first two calls occur at 0x000CDAA5 and 0x000CDAAE. The incoming second and
fourth pointers are loaded into EBX and EDI. `mov ecx,ebx` and `mov ecx,edi`
pass those pointers without adjustment. There are no stack-argument pushes at
either call; EAX is copied into ESI/ECX, compared, and subtracted as an integer.
The retained 231-byte caller has the same bytes and remaining six call bindings.

ILT `[0x00048761,0x00048766)` is exactly `E9 AA 71 32 00`, jumping directly to
0x0036F910. It makes no receiver adjustment and adds no stack arguments.

Provider `[0x0036F910,0x0036F9AD)` is the complete 157-byte matched body, beginning
after padding and ending in RET at 0x0036F9AC before INT3 padding. It preserves
EBX/EDI/EBP/ESI, reads incoming ECX into EBX, and loads the begin/end pointers at
receiver+0xB8/+0xBC. Its initial `push ecx` allocates a local counter; it is popped
before the plain RET. No caller-supplied stack parameter is accessed. Both the
empty and nonempty paths return the counter in EAX. This independently supports
the existing `int __thiscall method()` physical ABI.

The provider's sole direct call passes a hash payload unchanged in ECX through
ILT 0xDE9F to existing ObjectFields body 0x1BF630 (45 bytes); its EAX result supplies
a receiver for vtable slot +0x0C. The provider's two DIR32 references continue to
use `?TheGameLogic@@3PAVGameLogic@@A` at VA 0x012F0898. These facts describe physical
operations only; this correction does not claim a stronger completion/projectile
meaning from inherited names.

### Entire retail byte strings

Caller SHA-256: `7c4b5f9b4017f99f92aaef87e71af04ecbfe7e2e1e93505c5d270c128f4feed9`

```text
538b5c240c85db565774578b7c241c85ff74468bcbe8b7acf7ff8bcf8bf0e8aeacf7ff8bc83bf174085f8bc65e2bc15bc38b83bc0000008b93b80000008b9fb80000008b8fbc0000002bcb2bc25fc1f802c1f9025e2bc15bc35f5eb8010000005bc38b44241c85c074075f5e83c8ff5bc38b7c24108b470485c074278b480485c97405e8a347f3ff8bf085f674156aff8bcfe8fd2cf5ff508bcee85bfff3ff8bd8eb0233db8b7c24188b470485c0742d8b480485c97405e86f47f3ff8bf085f6741b6aff8bcfe8c92cf5ff508bcee827fff3ff5f8bc88bc35e2bc15bc35f8bc333c95e2bc15bc3
```

ILT SHA-256: `66c888481294fe5287c52e5f2653e811d6ede982f9faa4113a7b8fc822e7c534`

```text
e9aa713200
```

Provider SHA-256: `ba09a40947977bea0ddc2ec1d3f144fa730ecece307b2f01ba9cd99aa45ec4f1`

```text
51538bd98b8bbc000000578bbbb800000033c03bf989442408747e55568b3598082f018b0f85c9745d8b86b40000008baeb80000002be833d2c1fd028bc1f7f58b86b40000008b149085d274398d4900394a0474088b1285d275f5eb2985d274258b4a0885c9741ee822e5c9ff85c0740f8b108bc8ff520c84c07404ff4424108b3598082f018b83bc00000083c7043bf875908b4424105e5d5f5b59c3
```

## Ownership and COFF audit

All four caller sections (`.drectve`, `.debug$S`, `.text`, `.debug$F`) preserve
their complete raw payloads, headers, sizes, characteristics and relocation
records. All 19 ordered symbol-table records (12 primary plus 7 auxiliary)
preserve values, types, sections, storage classes and auxiliary bytes. Only
the name of one undefined external changes. Exactly two of the nine relocation
records refer to it: REL32 at caller+0x16 and caller+0x1F. The 231-byte raw COFF
body SHA-256 remains `a2135bc67c15bb0e9e2928e94369f45724f8290f4240100e2b8855868f428d75`.
No definition, data, import, global, vtable or weak alias is added.

The entire provider object is byte-identical before/after (38 sections),
SHA-256 `b32910fcb7e74afe05f7e0fc3e6e2e218cb3d3e6d44759e57c8534d0690b0ef5`.
Its existing count-method COMDAT definitions remain in sections 35/37, selection
NODUPLICATES; its STL COMDATs and data references are unchanged.

The immutable index identifies a sole count-provider/ledger owner object 9832
(`Rva0036F910StructureCompletionCount`) for both methods, with retail COMDATs,
no owner exceptions, COMMON providers, aliases or ambiguity. TheGameLogic's
sole strong selected non-COMDAT owner is object 2311 (`GameLogic.cpp`), whose
source defines `GameLogic *TheGameLogic = NULL`; the count-provider only references
it. Existing ObjectFields provider object 5419 solely owns
`getProjectileUpdateInterface`, consistent with its 0x1BF630/45-byte row.
No owner changes in this repair.

## Gates and net link preview

- `tools/check_csv.py` passes before edits and after repair
- `tools/callees.py 0x000CDA90 231` and `0x0036F910 157` fully decode both bodies
- Pristine and final `./build.sh` over both complete sources pass 3/3 rows;
  the changed caller recompiles, all string/constant/DIR32 gates pass
- Supplemental before/after DIR32 consistency: one symbol, zero new conflicts
- `tools/pin_consistency.py --symbol` confirms the old ILT route to canonical owner
- Header adoption and member-name checks pass
- Independent read-only review confirms extent/ABI/layout and complete COFF audit

`tools/link_check.py` checks caller plus freshly built current provider together,
so both before/after previews refresh the provider fixed in the published base.
Before: caller unresolved, 0 bytes; provider links, 314 bytes already published.
After: caller links, 231 bytes; unchanged provider still 314 bytes. Net new preview is
**231 bytes**, not 545. The index file stays immutable, SHA-256
`034ebdbd7f13546b5fd7f5f79240e5d75e973fabcc4bad425a0f4ee9dd0d9573`, census
1677ebdc33 (2026-10-03 17:32); refresh is in-memory only.

Original MSVC 7.1 runs under the approved pinned wibo runtime (compatibility
adapter names are `wine`; it is not Wine). Native full LINK/census was not run
because of the known wibo TEMPFILE mapping limitation. This is a scoped byte
proof and link preview, not a claim of a fresh successful full native link.
Untracked reproducibility artifacts are in `build/countcompare-link-proof/`.
