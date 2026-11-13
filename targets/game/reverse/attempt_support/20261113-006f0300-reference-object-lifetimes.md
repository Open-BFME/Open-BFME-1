# W3DDisplay::gatherDebugStats: pinned donor object-lifetime hypothesis refuted

BFME I baseline `72cdedeab4bda93ec099f6454b92cc568a8e7b96`;
runtime `openai/gpt-6.1-sol:high`. No production source, ledger, header,
string class, layout, pin or datum changed. Existing preferred source remains
`targets/game/reverse/attempts/0x006f0300.cpp` (historical score 0.7837416481).
No normal source admission or linking gain is claimed.

## Current native evidence and diagnostics

ILT oracle confirms `?gatherDebugStats@W3DDisplay@@IAEXXZ`. Existing native
`draw` at 0x006F3FC0 calls through ILT 0x00022BEC behind callback
0x0002F9F0. Decoding from the actual function start proves final **RET at
0x006F1489**, followed by INT3 from 0x006F148A. Thus the true primary extent
is **4490 bytes**; older notes calling 0x006F148A the final RET are off by one.
No extent/identity edit is made to the ledger.

Fresh direct compilation reproduces **4490B / 322 relocations / 971 masked
position differences**, first byte +0x7D (instruction +0x7A), normalized shape
0.988, 18 structural differences. A fresh private `/FAcs` listing confirms
font temporaries at the wrong stack home, selected Object spilling, and draw
register/spill differences. The native frame and copied declarations are not
newly inferred from the donor.

Current normal `build.compile_function` REL32 resolution on that private
object reports **zero unresolved symbols, masked=False, body unequal**.
This is not a DIR32/string/EH/provider-selection gate. Full raw COFF sections,
auxiliary symbols, public/data definitions and relocation graph are retained
in `build/spike3/display-stats-full-coff.log` (123998 bytes), not described as
physical-provider closure.

## New reference hypothesis and bounded trials

Pinned BFME 2 `76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherDebugStats.cpp`,
explicitly documents two moused-over lookups, one per RMB branch, later
merged by its compiler; its draw local's packing depends on those definitions.
The September BFME I bank has one lookup after the branch. This was a genuine
new source-lifetime lead, not a repeat of old rotation/EH/font-pointer sweeps.
BFME 2's different counters, 16 display strings, army/upgrades/fire-logic
sections, object layout and addresses were not imported.

| Semantic-preserving reference expression | Primary result |
|---|---|
| Duplicate moused-over lookup in RMB branches | 4506B / 324 relocs / 1380 differences |
| Selected-object assignment in short-circuit condition | 4474B / 322 / 1108 |
| Both above | 4506B / 324 / 1388 |
| Above plus body getter after position copy | same 4506B / 1388 |
| Named first FixedSys font (actual donor spelling) | unchanged 4490B / 971 |
| Scoped named second FixedSys font, ending before display allocation | unchanged |
| Both named font scopes | unchanged |
| Hovered-object assignment in short-circuit condition | unchanged |
| Both hovered/selected assignment conditions | 4474B / 1108 |
| Named hovered ObjectID before format | unchanged |
| Hovered condition plus ObjectID local | unchanged |
| Complete donor lookup/object/position/ID flow | 4506B / 324 / 1388 |

None improves the preferred bank. In BFME I's existing /O2 context, the
branch-local lookup form retains two extra relocations rather than becoming
the donor's merged code. Therefore that donor technique does not transfer as
proposed. No compiler-switch sweep, dummy local, forced root, string override,
header rewrite or body substitution was used.

## Currentness and admission limits

`finish_measure.py --one` refused a reusable receipt twice. Investigation
found matching source/object hash and header-search inventory but no `.deps`
sidecar. A direct normal compiler diagnostic reports why:
`macro or parent-traversing include has unknown search roots` and
`included header lies outside the snapshotted search roots`.
The include directories themselves all exist; this is not a missing-header
finding. Private scratch runs also report their changing source directory.
No cache/receipt/tool override or acceptance-mask change was made.

The direct fresh objects and `/FAcs` listing support the diagnostic numbers,
not reusable-cache or source admission. If future work improves the source,
it still needs reliable official-TU include context and every normal byte,
DIR32/string/EH and provider/consumer gate. Historical zero-unresolved notes
are now independently rechecked for REL32 only. Current census/whole closure
remain UNKNOWN; no cold whole-program build or image execution was attempted.

All project imports/compiler/environment construction entered the external
`/home/pispike/qa/bfme-spike3-20261113/game.sh` first, private win32 prefix,
headless/nice10/pool1 and on-disk TMPDIR. No old object/receipt was copied.

Logs: `build/spike3/display-stats-{identity,callees,diagnostic,full-probe,native-tail,listing-compile,current-rel32}.log`,
`display-stats-current-rel32.json`, `display-stats-{repro,repro-retry}.log`,
`display-{stats,font,hover}-variants.log` and their private results manifests.
The three generating helpers are retained alongside this note as `.py.txt`.
Resume only on a distinct native/source hypothesis; do not rerun these donor
branch/condition/ID/font spellings or the previously exhausted register sweeps.
