# Three S4 push-heap comparator bindings

## Scope

`game/GameEngine/Source/Common/S4StlSortHelpers.cpp` retains all 24 existing
matched rows, opaque template/POD identities, four-byte functor state and all
anchors/siblings. Only three comparator references change:

| Existing 98 B `__push_heap` root | Old comparator | Existing native comparator | Original ILT | Full provider |
| --- | --- | --- | --- | --- |
| `003408C0` / `S4Cmp003408C0` | `S4Cmp003408C0::operator()` | `Q4Sort0034BFC0::operator()` | `00024B81` | `0033D5E0`, 122 B |
| `004529D0` / `S4Cmp004529D0` | `S4Cmp004529D0::operator()` | `Q4Sort004566F0::operator()` | `00024055` | `00451F60`, 122 B |
| `007534F0` / `S4Cmp007534F0` | `S4Cmp007534F0::operator()` | `Q4Sort00755050::operator()` | `0002952D` | `00752B80`, 465 B |

The fourth 98 B root `00452A50` already calls the existing
`S4Cmp00452A50::operator()` through `00039CB1 -> 00451E90` (164 B); it remains
unchanged. These are the same four independently proved predicate bodies used
by the preceding insertion-sort binding repair, but each push-heap route and
argument slot is separately verified here.

The ledger identities are the actual `_STL::__push_heap<int*,int,int,S4Cmp...>`
instantiations, NOT the `s4ph...` anchors. Changing an anchor's identity, adding
forwarding operators, inventing inheritance, or replacing the old template
argument types would not be this repair. Instead the supervisor authorized one
bounded consumer-template experiment: exactly three inline explicit
specializations of the EXISTING emitted signatures. Their loops are copied
from this checkout's `inputs/vendor/stlport/stl/_heap.c` with only the predicate
call changed to the existing public native method on the same functor slot.
No algorithm/order/signed arithmetic/copy/calling-convention change is made.
The existing `S4_PUSH_HEAP` macro still emits the same anchors; its previously
embedded four POD declarations are spelled out unchanged before the three
specializations. No macro/helper/function identity is added.

Native comparator declarations are pointer-only method views; no layout,
`sizeof`, inheritance, state initialization or original EA type relationship
is imported. Existing providers do not read the incoming functor state. The
old address-bearing template/POD names stay opaque: this does not resolve
semantic element/functor identity or promote inferred EA names. The inherited
identity-suspect note on related adjust-heap `009F3190` and the uncertainty
explicit in this TU/session5 extent evidence are not retired by these edges.

## Native ABI and full-body proof

`callees.py` was run on each affected complete 98 B root before editing.
Strict comparison checks ALL 24 consumer rows: exact bytes, zero masking and
zero unresolved relocations. Each of the four push-heap roots has exactly one
predicate call, at REL32 operand offset `2C` hex, and retains its original ILT.

The actual incoming arguments are `first`, `hole`, `top`, `value`, then the
four-byte comparator. On the comparison path, ESI/EDI/EBX/EBP have been saved.
EBX is `first` (loaded at entryESP+4), EDI `hole` (entryESP+8), and EBP `value`
(entryESP+16). `mov eax,[ebx+esi*4]` reads the parent value; `push ebp; push eax`
passes `(parent,value)` in native right-to-left order. Then
`lea ecx,[esp+2Ch]` addresses **entryESP+20**, the original fifth argument slot:
four saved registers plus two predicate words account for the displacement.
No functor copy, receiver adjustment, extra state read or temporary is added.

Every full 98 B root preserves both cdecl RET0 exits. The signed parent
calculation remains `lea (hole-1); cdq; sub; sar 1`, and all element copies and
loop order are byte-identical. All four complete native comparators are strict
and unmasked: 122/122/164/465 B, with respectively 1/1/2/12 normal RET8 exits.
These return paths consume precisely the two pushed dwords. No prefix-only
provider check or incoming-state assumption substitutes for the complete body
and existing source evidence.

## Whole-object footprint and selection metadata

Actual before/current COFF comparison keys sections by their exact exported
COMDAT definition identity (or associated section owner), NOT by their physical
section number. **Physical section emission order/numbering changes**, and is
not claimed identical. The complete inventory preserves the object footprint
and COMDAT selection metadata/eligibility beyond the intended three external
references; it does NOT establish a current-link winner or whole-image layout:

- All **116 sections**: 58 non-debug and 58 debug, every raw code/data/directive
  byte, every relocation and all section characteristics are identical by key.
- All **116 complete section-definition auxiliary records** match, including
  length, relocation/line counts, checksum, COMDAT selection, reserved/high
  fields and association identities (section indices resolve to the same key).
- All **57 external definitions**, types/storage/relative offsets and anchors
  remain identical. Exactly three old undefined names become the three native
  operator names; there is no other undefined-reference change.
- No weak external or new alias/helper/specialization copy is emitted. The
  baseline's twelve compiler `/alternatename` directives for OTHER pre-existing
  specializations remain byte-for-byte unchanged; none is added or edited.

Normalized all-section inventory SHA256:
`be46831d402b0be9ecb942dafac67603228a6320161a23dcb16538eccd5f5307`.
This comparison does not rewrite object metadata or weaken a verifier; the
normal gate independently verifies all existing rows against retail.

## Reference-source and prior-evidence pass

Read-only BFME 2 revision `76f0baefa6f285d54bc1ca922397674312a5913f`:
`Code/GameEngine/Source/Common/LargeGroupAudioSoundKeyPair.cpp` and
`.../Rva0021956EPushHeap.cpp`, plus the narrow push-heap search results.
The former has explicit specializations with a loaded-temporary/break spelling;
the latter has a cdecl function-pointer predicate. Neither variant, calling
convention, address, template identity or layout is transferred. This change
uses BFME 1's own vendored loop and existing native providers. The earlier
BFME 1 `session5-native_sort-extents.md`, relevant attempt entries and
`s4-insertion-comparator-bindings.md` were reviewed. No donor tree/build input,
header/provider unit, pin/alias, root identity or verifier exemption changes.

## Validation and accounting

Normal before/after unified gate: **35/35 functions across five TUs**, including
all 24 consumer rows and the actual four unchanged comparator provider units;
6 DIR32 references, 4 float constants, no skipped string refs and no baselined
body findings. `find_declared_unmatched.py` reports all definitions matched.
Actual builds retain `// cl: -GX-` and the existing STLport context, private
WoW64 prefix, `WINEARCH=win64`, `BUILD_POOL=2`, `WINEDEBUG=-all`, empty desktop
displays; no compiler variant or shared-input repair is introduced.

Before preview: **0/5 clean**, 228.8 s; after: **0/5 clean**, 225.1 s.
Both have 4 UNKNOWN / 1 independent-debt verdicts and all five selection sets
have stale census evidence: 22,757 cold/changed ledger objects cannot be read.
Historical LINKED **2,008 -> 2,008** remains unchanged, not current confirmed
coverage. Exactly three obsolete operator unresolved diagnostics disappear;
every duplicate/COMDAT/other selected diagnostic remains, with none added.
No new matched bytes, current linked-byte gain or closure is inferred. The
consumer's independent ownership/COMDAT/other missing-helper debt is unchanged.
Actual chosen providers and whole-image layout remain unverified under UNKNOWN;
matching selection metadata is not a current-link selection verdict.

Private diagnostics under `build/sol12h-bindings/`:
`pushheap-{before-build,after-build,link-before,link-after}.log`,
`pushheap-{routes,footprint}.log`, `pushheap-footprint.json`,
`pushheap-before.{cpp,obj}`, `pushheap-{sources,rvas,callees,prior-attempts,donor-search}.txt`,
`check_pushheap_routes.py`, `check_pushheap_footprint.py` and exact claim log.
