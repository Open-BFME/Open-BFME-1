# Ten existing-data-provider consumer repairs

Baseline: af61ce85bd, BFME 1 retail 1.03 unpacked. Ten scoped source-unit tasks
replace obsolete global references with the existing, uniquely owned data
ledger symbols. No new function identity, data definition, pin, alias, header
or compiler setting is introduced.

| Task | Scope | Verified row RVAs | Complete bytes | Data owner(s) |
|---|---|---|---:|---|
| 1 | Settings millisecond-to-second factor: `game/GameEngine/Source/GameClient/Rva0040B5A0Init.cpp` | `0x0040B5A0` | 441 | `g_millisecondsToSeconds` |
| 2 | Highlight refresh flag: `game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilterPreRender.cpp` | `0x007D6E40` | 409 | `g_bfmeDirtyCU` |
| 3 | Heightmap dispatch flag: `game/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMapUpdateCenter.cpp` | `0x006D2A00` | 1,984 | `g_aiTargetDispatchSuppressed` |
| 4 | AimWeapon numeric weight: `game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorUpdate.cpp` | `0x001ED230` | 570 | `g_bfmeDirectionWeight1285` |
| 5 | Flame-cleanup Lua notification: `game/GameEngine/Source/GameLogic/Object/Update/FlameCleanup00293E50.cpp` | `0x00293E50` | 463 | `TheLuaScriptEngine` |
| 6 | LivingWorld singleton: `game/GameEngine/Source/Common/Rva003BDC50.cpp` | `0x003BDC50` | 124 | `g_rva012F7048LivingWorld` |
| 7 | ERD helper upper bound: `game/GameEngine/Source/Common/BfmeConv1675.cpp` | `0x0061CD80` | 68 | `g_bfmeDefaultBU` |
| 8 | Palantir percentage rounding: `game/GameEngine/Source/GameClient/GUI/AptPalantirSetRankProgress.cpp` | `0x00588890`, `0x00588940` | 156 | `g_rva0107533C` |
| 9 | Display-update zero/one constants: `game/GameEngine/Source/GameClient/Rva0040EE90OwnerUpdate.cpp` | `0x0040E260`, `0x0040E2F0`, `0x0040EE90` | 515 | `g_rva01075350`, `g_bfmeDefaultBU` |
| 10 | Readiness network-pointer check: `game/GameEngine/Source/Common/Bfme5EightyThree.cpp` | `0x0035EFF0`, `0x003D6440`, `0x003C7D50`, `0x00383610` | 243 | `TheNetwork` |

## Target facts and preservation

The sixteen retained rows cover 4,973 complete bytes. Private old/new
object comparisons preserve those bytes and all relocations except 18
references being bound to the existing owner names. Each changed DIR32
operand was checked directly in the corresponding complete retail body:
its four-byte address equals the owner's recorded VA. Initial data values
and widths come from the existing matched data rows and are reverified at
their providers. Names retain their existing provenance; no EA identity
is inferred from equal constants or byte equality.

A complete COFF section comparison also preserves every non-debug section's
bytes, characteristics and relocation targets after the intended global
renames. Compiler-local targets are compared by section content and offset.
This includes the two .xdata sections in the flame-cleanup unit. External
definition/reference sets are unchanged apart from those global references.

Lua keeps its existing local call view by projecting the canonical pointer
value. LivingWorld reads the canonical pointer through a volatile-qualified
view of that same pointer type before projecting its value to the local
call view; its repeated loads remain separate. The existing, previously
justified stack-scheduling assembly block keeps its instructions and only
changes the data symbol. The readiness function tests the existing network
pointer for nonnull instead of reading its storage under an integer alias.

The native combined gate passes 48/48 rows across nineteen distinct source
files, including the 32 provider rows, thirteen data rows, one string,
fourteen compiler float references and 138 DIR32 references. The ten
consumer files were rebuilt explicitly. Their declared-unmatched checks
find no open body; existing recorded inline/static exclusions remain.

## Donor review

BFME 2 reference f6c3838e7b was checked successfully on 2026-11-13
and is within the 72-hour freshness window. Its
`Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilterPreRender.cpp`
uses the same shared bool spelling `g_bfmeDirtyCU` for read/clear operations
at its own different address. `Code/GameEngine/Source/GameLogic/System/GameLogic.cpp`
declares `NetworkInterface *TheNetwork` and `LuaScriptEngine *TheLuaScriptEngine`.
The corresponding heightmap source and the donor's typed-global rewrite
mechanism were also reviewed; no different-game address or layout is copied.
The donor's `Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp`
has a TU-static 1.0f constant with the `g_bfmeDefaultBU` spelling. Its static
linkage is not transplanted: BFME 1's existing sole data owner is used.
Opaque BFME 1 call views, method identities and constructor relationships
remain as established by BFME 1 evidence. The donor supports the repair
pattern, while BFME 1's own data ownership and retail operands prove each binding.

## Linking boundary

An original-source baseline was reconstructed from Git's working-tree
filters and checked against each recorded pre-edit source hash. It was
rebuilt and measured with native `link_check.py --census-only` against
the 2026-11-14 12:41 index at 1a248a7b47: zero of ten units link, 0 -> 0 bytes.
The verified working sources were then restored and rebuilt normally.

The current-object preview against that same census index reports one of
ten units linking: `Rva0040EE90OwnerUpdate.cpp`, 0 -> 515 predicted bytes.
The other nine still have independent globals, helper, duplicate or COMDAT
blockers. This prediction is not a new census or a full executable link.
The staged native preview returns UNKNOWN for all ten units after 120 seconds;
it also reports 22,032 changed/new ledger objects unreadable locally. Thus the
515-byte result remains a frozen-index prediction, not a current-provider
or published LINKED result. No full rebuild was substituted for that missing proof.
No runtime, FPS, memory, leak or crash-fix claim follows from this batch.

Local reproducible evidence: `build/codex-20261114-ten/` retains the original
objects and private candidates; `W:/OpenBFME/diagnostics/continue-20261114-ten/`
retains per-task old/new relocation proofs, source hashes, complete section
comparison, native build outputs and original/current link previews.
