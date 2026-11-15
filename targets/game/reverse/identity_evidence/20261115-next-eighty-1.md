# BFME 1 continuation: tasks 1-22 of 80

Immediate baseline `3ec594ba25a3edd51d90306bb517d53af2bacfbb`.
The complete selection begins at `3ec594ba25a3edd51d90306bb517d53af2bacfbb`.
These are existing source binding and function-identity metadata repairs.
No new function reconstruction, authored-byte, runtime or crash-fix gain is claimed.

## Tasks 1-20: existing data-owner consumers

| Task | Source | Binding at independently decoded BFME 1 VA |
|---|---|---|
| 1 | `game/GameEngine/Source/Common/S3LinkedSingletonCtor.cpp` | `TheBfmeSingletonHead` -> `g_bfmeHeadCA` at `0x012F3350` |
| 2 | `game/GameEngine/Source/Common/BfmeOwnerVW.cpp` | `g_bfmeListVW` -> `g_bfmeHeadCA` at `0x012F3350` |
| 3 | `game/GameEngine/Source/Common/Rva008B2EA0Factory.cpp` | `g_bfmeRegistryVNF` -> `g_rva01337810GcRoots` at `0x01337810`; `g_aptStringFreeList` -> `g_rva01338478NodeHead` at `0x01338478` |
| 4 | `game/GameEngine/Source/Common/Rva008AAEC0MakeString.cpp` | `g_pool01337A30` -> `g_rva01337A30AllocPair` at `0x01337A30`; `g_bfmeRegistryVNF` -> `g_rva01337810GcRoots` at `0x01337810`; `g_aptStringFreeList` -> `g_rva01338478NodeHead` at `0x01338478` |
| 5 | `game/GameEngine/Source/Common/Bfme5FortyEight.cpp` | `g_bfmeListDQ` -> `g_bfmeHeadCA` at `0x012F3350` |
| 6 | `game/GameEngine/Source/Common/BfmeTwoStringVX.cpp` | `g_bfmeListVX` -> `g_bfmeHeadCA` at `0x012F3350` |
| 7 | `game/GameEngine/Source/Common/BfmeConv1236.cpp` | `g_bfmeArenaCursor` -> `g_bfmeArenaCursor` at `0x013378D4` |
| 8 | `game/GameEngine/Source/Common/BfmeConv1038.cpp` | `g_bfmeA1038` -> `g_bfmeHolderBU` at `0x013377D8`; `g_bfmeC1038` -> `g_bfmeArenaCursor` at `0x013378D4` |
| 9 | `game/GameEngine/Source/GameClient/InGameUIBodies.cpp` | `g_bfmeStateDO` -> `TheLivingWorldLogic` at `0x012F1028` |
| 10 | `game/GameEngine/Source/Common/R1SmallFieldInitialisers.cpp` | `g_Glo00EF3350` -> `g_bfmeHeadCA` at `0x012F3350` |
| 11 | `game/GameEngine/Source/GameLogic/Object/ObjectSetTriggerAreaFlagsForChangeInPosition.cpp` | `TheTerrainLogic` -> `TheTerrainLogic` at `0x012EF4CC`; `g_bfmeOwnerBR` -> `TheLuaScriptEngine` at `0x012F060C` |
| 12 | `game/GameEngine/Source/Common/BfmeConv816.cpp` | `g_bfmeCountELH` -> `number_of_DX8_calls` at `0x01340594` |
| 13 | `game/GameEngine/Source/Common/GlobalDwordGetters.cpp` | `g_Va012F49E4` -> `g_obj12F49E4` at `0x012F49E4`; `g_Va0130A5A0` -> `g_Va0130A5A0` at `0x0130A5A0` |
| 14 | `game/GameEngine/Source/Common/SmallLeafBodies2.cpp` | `g_Va012F13FC` -> `g_bfmeDirtyCU` at `0x012F13FC` |
| 15 | `game/GameEngine/Source/Common/SmallLeafBodies.cpp` | `g_Va012F13FC` -> `g_bfmeDirtyCU` at `0x012F13FC`; `g_Va012D6DA8` -> `g_flag12D6DA8` at `0x012D6DA8`; `g_Va012ED611` -> `TheBfmeOverrideCopyInProgress` at `0x012ED611` |
| 16 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp` | `g_rva00889690` -> `g_Rva00F36E5C` at `0x01336E5C`; `g_bfmeA1087` -> `TheTerrainRenderObject` at `0x012F7FE0` |
| 17 | `game/GameEngine/Source/GameLogic/AI/AIInternalMoveToState_onEnter.cpp` | `g_012F0239` -> `Glo012F0239` at `0x012F0239` |
| 18 | `game/GameEngine/Source/GameLogic/Object/Rva001D48A0Xfer.cpp` | `TheGameLogic` -> `TheGameLogic` at `0x012F0898`; `TheTerrainLogic` -> `TheTerrainLogic` at `0x012EF4CC` |
| 19 | `game/Libraries/Source/Apt/Rva008AE2E0BoundsGetter.cpp` | `g_bfmeStack008AE2E0` -> `g_bfmeB1038` at `0x01337A04` |
| 20 | `game/GameEngine/Source/GameLogic/System/GameLogic.cpp` | `g012F076C` -> `TheScriptEngine` at `0x012F076C`; `g012F7714` -> `TheNetwork` at `0x012F7714`; `g012ED62C` -> `TheRecorder` at `0x012ED62C`; `g012ED63C` -> `TheStatsCollector` at `0x012ED63C` |

33 actual consumer/global contracts change across 72 DIR32 fields.
All 441 retained rows preserve their complete 58,457 bytes.
Each changed operand was decoded inside its own complete retail function and equals
the existing data owner's exact VA. Ownership and type come from BFME 1 data_rows.csv
and its cited independent store/constructor/registration evidence; a donor name is not proof.
Old local receiver/layout views remain through pointer-value conversions. There is no
unrelated pointer-cell reference pun, new definition, alias, symbol pin, header or compiler flag.
The unsigned-char views preserve the original raw one-byte reads and writes through the
existing bool objects, including the noncanonical-byte store; they do not normalize bool values.
The arena iterator keeps its original 96-byte stride when using the existing char cursor.
Pointer stores retain the old conversion before converting to the owning pointer type.
The Direct3D unsigned call counter retains the original modulo-32-bit increment.

Complete ordered non-debug COFF sections compare for size, flags, bytes and relocation
graphs, along with every defined external's section/value/type. Only the documented
data-symbol targets change. Compiler-local targets compare by section/value/type.
SafeSEH .sxdata entries are COFF symbol indices and compare by their resolved handler
targets. All 64 .xdata and 9 .sxdata sections retain their semantics.

Private compilation of GameLogic.cpp initially changed the __FILE__ literal. A private
#line wrapper restored the original source path. A separate unedited control under the
same private context reproduced the four-byte instruction-order difference in an unrelated
unmatched startNewGame body. Edited versus unedited controls were identical after the
intended mapping. The normal build at the real source path then preserved the entire
original non-debug object graph, including that unmatched body; no #line enters game source.

## Reference review and work selection

The BFME 2 reference remains `f6c3838e7b58025531e09913bc42b810f1a01216`,
last successfully checked 2026-11-13T19:10:55Z, within the 72-hour window.
The existing typed data-owner pattern is materially reused; addresses and layouts are
established independently in BFME 1. Relevant donor paths reviewed include
`Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp` (unsigned number_of_DX8_calls),
`Code/GameEngine/Source/GameNetwork/Network.cpp`, and
`Code/GameEngine/Source/GameLogic/System/GameLogic.cpp` (shared subsystem owners).
A donor declaration supplies a lead, never BFME 1 pointer-cell or ABI proof.
The new BFME 2 reference scan examines 53,034 bodies and 770,769 placements:
4,808 exact-unique, 25,590 near, 739,768 exact-multi, 450 truncated and 153 string conflicts.
The inspected top-ranked exact leads are already matched. Zero Hour compile/match/packets
was also refreshed: 26,402 compiled functions, no exact-unique unclaimed bucket, and one
unclaimed packet at 0067EE40 whose 29-byte candidates do not establish the 937-byte extent.
Its existing manually annotated tracked packet is preserved; regenerated output stays diagnostic.
The unchanged DXGetErrorString9W library-member blocker and two disproven near leads are
not retried. Unused declarations in Snow/ControlBar and a pointer-cell-address ABI candidate
are excluded. Prior attempt records were filtered by the actual selected RVAs and bindings.
These repairs preserve established bodies, field offsets, callees and identities.

## Frozen-index link preview

Original consumers before edits: 1/20 link, LINKED 1,521 -> 1,521 bytes.
Repaired against the same index: 3/20 link, LINKED 1,521 -> 1,971 bytes.

## Retail unwind-state identity corrections

The native eh_state_pins.py writer alone updates the object-symbol notes.
For each row the original parent's retail handler -> FuncInfo -> unwind map identifies
the action at the same state index in the native compiled object. maxState and all
toState entries agree; all ledgered parents that constrain the action agree on one label.
Byte-equal twins are distinguished by this state evidence, never by choosing the first
matching body or by adjacency. Existing semantic names and parent assignments are retained.
Prior attempts and landing evidence were reviewed for all 60 selected funclet RVAs.
Four preliminary stale candidates became proven after a normal cache-refresh build and
were excluded. Only still-wrong or stale uniquely state-proven bindings are repaired.
The remaining unprovable and unrelated/missing-object rows are not modified.

| Task | Retail action | Source | Previous -> proven object label | Retail parent states |
|---|---|---|---|---|
| 21 | `0x00C4C5F8` `?dup_00C4C5F8@@YAXXZ` (11B) | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp` | `$L67028` -> `$L67031`; stale; twin-proven | `?allocateRoadBuffers@W3DRoadBuffer@@IAEXXZ: [1]` |
| 22 | `0x00C4C603` `?dup_00C4C603@@YAXXZ` (11B) | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp` | `$L67029` -> `$L67032`; stale; twin-proven | `?allocateRoadBuffers@W3DRoadBuffer@@IAEXXZ: [2]` |

This batch repairs 2 bindings covering 22 existing function bytes; 0 labels still named another object label and 2 actions have byte-equal twins.
These are metadata identity repairs, not newly recovered byte counts.

## Native verification and limits

The combined ordinary gate passes 848/848 functions across 39 sources,
81 data rows, 1605 DIR32 references and the body guard.
Staged current-provider preview: 20/20 UNKNOWN, 0/20 LINKS, 0/20 blocked. The 120-second deadline expired before a current-provider verdict.

Latest complete census observed remains [43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489),
input 1a248a7b476727c19e37a16744c71686fa8f3f5e, snapshot 2026-11-14 12:41 UTC:
3,086,248 LINKED bytes in 15,516 files. It predates both the earlier predicted +515B
and the previous eighty-task batch's +1,492B frozen-index previews; neither is a new
full-census result. Bounded previews establish neither a full-image link nor a game start,
FPS, memory, leak or crash fix.

Detailed original/final objects and proof records remain in `W:/OpenBFME/diagnostics/continue-20261115-eighty-next/batch-1/`
and `build/codex-20261115-eighty-next/`. Shared native objects were produced only by the
ordinary build; isolated compiler experiments never wrote its cache.
