# DXC file cleanup: one existing destructor call

This is one source/link repair, with **0 new body or exact bytes**. Four existing
rows in `game/GameEngine/Source/Common/BfmeConv793.cpp` retain their 97-byte extent
sum. Only the 24-byte call at RVA `0x0013ADE0` changes its C++ callee spelling.
No function/data/route ledger, header, compiler option, pin or baseline changes.

## Original identity and receiver

The full original 24-byte body reads `FILE*` at receiver `+0x48`, calls `fclose`,
restores the unchanged receiver in ECX and tail-jumps via ILT `0x0000B488` to
`0x0013A8E0`. The existing owned provider is
`??1Open2Dtor13A8E0@@QAE@XZ`, 180 bytes, in `Open2Destructors.cpp`.
Its native whole file has six strict matching rows. Its existing ten string
subobject destructions access `0,4,8,C,10,1C,20,28,3C,44`; its original EH graph
has nine unwind states. This proves a destroyed prefix, not an original total
class size or inheritance model.

Independent original parent `0x0013C720` (1344 bytes) has five EH states:
state0 action `0x00C038E0` takes `[ebp-0xC4]` to ILT `0x00031476` -> `0x0013ADE0`;
state3 action `0x00C038FB` takes `[ebp-0x54]` directly to the same complete
destructor through ILT `0x0000B488`. No parent or cleanup recovery is claimed.

The source uses only a declaration of that existing nonvirtual destructor and
an explicit unchanged-receiver call. It instantiates no such view, asserts no
storage/inheritance/vtable, and does not invent an inline helper or EA name.
The other three rows at `0x009F69D3/22`, `0x00694D40/28`, `0x00849E60/23` are
unchanged. All four ranges are disjoint and were already C++ exact.

## Whole normal object: real extra emission, explicitly accounted

All nine old runtime/FPO sections retain their raw data, flags, COMDAT selection
and association, apart from exactly one bound REL32 name at main offset20.
The compiler moves that main section from5 to11 and its FPO from6 to12;
these real section-order changes are recorded, not silently normalized away.
The actual includes and full original compiler profile are unchanged.

MSVC also emits a new 30-byte ANY COMDAT
`??_GOpen2Dtor13A8E0@@QAEPAXI@Z`, plus its 16-byte ASSOCIATIVE FPO section.
It calls the same complete destructor and global `operator delete`.
The initial whole-graph-equality assertion correctly failed on this emission;
the candidate was not changed. The runtime graph is **not unchanged**.
There is no matching retail identity or ledger owner for this generated copy.

The admitted basis is exclusively the native current `link_references` /
`keep_rule` policy: **all 22,997 current objects**, no missing or
stale object, full native weak/alternatename edges, and repeated validated COFF
snapshots and source/tool/input/object hashes. That actual complete reference
closure does not reach this copy. Native `keep_rule` reports `unreferenced`,
with no losing copy. The separate code/FPO can be discarded by the link.
No marker, pin, alias, allowance, partial inventory or index/unreferenced-set
edit was made. This is a snapshot-specific reachability proof, not a recovered
30-byte original body or a claim about future callers.

## Native verification and limits

- Original source normal build4/4; candidate normal build4/4 and4 DIR32 checks.
- Existing real destructor provider normal build6/6.
- Native `find_declared_unmatched.py --fail` reports all matched. This is only
  source hygiene; it does not by itself own or admit compiler-generated code.
- Normal `link_check.py SOURCE` before: unlinked0->0, fake old callee unresolved.
- Normal `link_check.py --refresh --refresh-compile SOURCE` after: 224 current
  TUs rebuilt; all1888 data rows verified; all22997 current objects read;
  source LINKS0->97, exit0. This is a current per-file preview, not a new census.
- The separate full native reference receipt is mandatory in addition to LINKS.
- No full-image link, startup, runtime, memory or crash improvement is asserted.
- 97 bytes remain existing coverage; the additional30/FPO has0 body credit.

## Reference and reproducibility

Historical BFME2 donor is `e2e99959950e6eebfe1ced5663aa05de320afc52`.
Its same-address `Open2Destructors.cpp` entry is `present-unmatched`, and therefore
was rejected as independent retail/name proof. The positive identity/ABI proof
comes from BFME1 original calls and its already verified owned provider.
No BFME2 code/profile was transferred. One required native reference refresh
scanned53315 bodies/790847 placements; native input validation passed.

The private diagnostic root is `W:/OpenBFME/diagnostics/one-per-project-20261124-185505/bfme1`. It preserves original/candidate
objects, actual include receipts, original caller/dtor/parent-EH outputs, full
currency/object/reference inventories, exact native driver and logs. Their
hashes are in MANIFEST.json; large inventories and binaries remain private.
`NATIVE-REFERENCES.json` records the complete native APIs, hashes and limits.

The first global-receipt attempt stopped before graph judgment: `object_inputs`
could not read 7 current native entries whose successful compilation
used the normal include-retry context. The native census checker already
validated them, but that extraction helper requires exact base-command equality.
The retained first refusal was not ignored. The successful private extraction
uses each such entry only after the unchanged `census_receipts.Receipts.current`
again proves the exact source, object digest, full PP stream, actual command
context and every input file. No private flag whitelist, missing-input fallback,
receipt/sidecar edit, tool patch, additional body variant or selective inventory
was used. All actual opened files are included in the common hash snapshots.

Reproduce with the repository environment and normal commands:
`python3 tools/build.py game/GameEngine/Source/Common/BfmeConv793.cpp`,
`python3 tools/build.py game/GameEngine/Source/Common/Open2Destructors.cpp`,
`python3 tools/find_declared_unmatched.py --fail SOURCE`, and
`python3 tools/link_check.py --refresh --refresh-compile SOURCE`.
Then use the unchanged native `ledger/objects/stale_objects/read_facts/`
`ledger_owners/link_references/validate_fact_snapshots/keep_rule` methods over
the complete current inventory, with the same no-missing/no-stale and stable
input/object gates. Never treat a merely local no-incoming-edge result as this
complete proof. No source/flag variant was used after the frozen candidate.
