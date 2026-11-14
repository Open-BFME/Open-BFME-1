# Twenty existing-singleton consumer repairs

Baseline: bccd6d679ed3a4c138e1a090d6b8e10c2e4ff986; BFME 1 retail 1.03 unpacked.
The twenty tasks below are twenty existing consumer-unit repairs, not twenty
newly reconstructed functions. Twenty-three distinct consumer/global bindings
are corrected across thirty actual reference fields. No new data definitions,
function identities, pins, aliases, shared headers or compiler flags are added.

| Task | Consumer source | Scope | Retained RVAs | Existing data owners |
|---|---|---|---|---|
| 1 | `game/GameEngine/Source/Common/BfmeConv485.cpp` | Palantir dispatch guard | `0x0043B4A0` | `TheAptPalantir` |
| 2 | `game/GameEngine/Source/GameClient/GUI/AptPalantirOnButtonCommand.cpp` | Palantir command selection | `0x00563A50` | `TheAptPalantir` |
| 3 | `game/GameEngine/Source/GameClient/GUI/AptPalantirOnButtonHeroSelect.cpp` | Palantir hero selection | `0x00563AB0` | `TheAptPalantir` |
| 4 | `game/GameEngine/Source/GameClient/GUI/AptPalantirOnRegionPortraitClosed.cpp` | Palantir region portrait | `0x00563B20` | `TheAptPalantir` |
| 5 | `game/GameEngine/Source/Common/BfmeConv1713.cpp` | Weather countdown stop | `0x006E1620` | `TheGlobalWeatherSystem` |
| 6 | `game/GameEngine/Source/Common/BfmeConv961.cpp` | Living-world manager and state | `0x00383980` | `TheLivingWorldManager`, `g_rva012F7048LivingWorld` |
| 7 | `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldPointerVectorApplyFound.cpp` | Campaign pointer-vector lookup | `0x003B8260` | `TheLivingWorldCampaignManager` |
| 8 | `game/GameEngine/Source/Common/BfmeConv932.cpp` | Experience-level query | `0x00087E80`, `0x00171380`, `0x001B2010`, `0x0017DB10` | `TheExperienceLevelSystem` |
| 9 | `game/GameEngine/Source/Common/BfmeConv988.cpp` | Large-group audio removal | `0x00296280`, `0x00296550`, `0x00173A20` | `TheLargeGroupAudio` |
| 10 | `game/GameEngine/Source/Common/BfmeConv1086.cpp` | Lua object removal | `0x001BF300` | `TheLuaScriptEngine` |
| 11 | `game/GameEngine/Source/Common/BfmeTimerAZTick.cpp` | Weather countdown tick: volatile load | `0x006E1670` | `TheGlobalWeatherSystem` |
| 12 | `game/GameEngine/Source/Common/BfmeConv991.cpp` | Smudge manager update | `0x00465B30`, `0x006FA060`, `0x007E38F0` | `TheSmudgeManager` |
| 13 | `game/GameEngine/Source/Common/BfmeConv1227.cpp` | Picker callback dispatcher | `0x008D3220` | `g_bfmeHolderBU` |
| 14 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva00522110MessageBoxText.cpp` | Message-box state pointer | `0x00522110` | `g_rva012F49D0` |
| 15 | `game/GameEngine/Source/Common/BfmeConv1097.cpp` | Thing-factory list traversal | `0x002FE7D0` | `TheThingFactory` |
| 16 | `game/GameEngine/Source/Common/BfmeConv1233.cpp` | APT deallocation hook | `0x008B99B0` | `g_rva01337A30AllocPair` |
| 17 | `game/GameEngine/Source/Common/BfmeConv1062.cpp` | Palantir level-path mode | `0x007B77F0`, `0x008A4860`, `0x00564800` | `TheAptPalantir` |
| 18 | `game/GameEngine/Source/Common/BfmeConv1100.cpp` | Living-world state and logic | `0x002EDDB0`, `0x0060D410` | `g_rva012F7048LivingWorld`, `TheLivingWorldLogic` |
| 19 | `game/GameEngine/Source/GameLogic/LivingWorld/Rva0061A0F0Dispatch.cpp` | Campaign name/entry dispatch | `0x0061A0F0` | `TheLivingWorldCampaignManager` |
| 20 | `game/GameEngine/Source/Common/BfmeConv1060.cpp` | Palantir mode and transition handler | `0x00564860`, `0x0048BD00` | `TheAptPalantir`, `TheTransitionHandler` |

## BFME 1 evidence and preservation

The existing matched data records establish each owner independently from
BFME 1 constructor/registration strings, stores, vtables or address-derived
cell evidence. Names without a recovered EA identity remain address-derived.
Each changed field was decoded inside its complete retail function: its
DIR32 operand equals the exact existing owner VA, not merely an equal value.
The source now requests that owner's decorated symbol and pointer type.
Local member-call and layout views are retained by pointer-value conversions;
no original class/layout identity is inferred from the successful byte check.

All 31 retained consumer rows preserve their complete 2,279 bytes and all
relocations other than the thirty deliberate data-symbol bindings. The
ordered non-debug COFF sections preserve bytes, sizes, characteristics and
relocation targets; local targets retain section number/offset and all defined
external symbols retain section/value/type. This comparison includes both
consumer `.xdata` sections. Undefined external sets differ only by the
intended global mappings. Provider definitions are unchanged.

The combined native build gate passes 97/97 functions across 31 function TUs
and verifies 28 data rows (35 scoped sources including data-only providers),
22 literal references, one empty-string reference and 178 DIR32 references.
All twenty declared-unmatched checks pass. Four existing provider funclet
labels are resolved by the native gate to their current compiler-local labels;
their verified bodies and ledger records are unchanged.

`BfmeTimerAZTick.cpp` retains its original volatile pointer load before the
local pointee conversion. Applying volatility to the canonical pointer
lvalue via `static_cast<RetailGlobalWeatherSystem *volatile &>` and then
converting the loaded value preserves the existing 108-byte instruction order.
This avoids accessing the cell through a differently typed pointer lvalue.
The measured case and exact compiler flags are recorded in `docs/shape_levers.md`.

Prior attempt records and the linked 0061A0F0 loop handoff were reviewed.
Their established control-flow, callee ABI and compiler decisions are retained;
no previously blocked reconstruction is retried as a naming exercise.

## Reference review and rejected candidates

The BFME 2 donor remains f6c3838e7b58025531e09913bc42b810f1a01216,
last checked 2026-11-13T19:10:55Z, within the 72-hour freshness window.
Its `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_Rva0035B03E.cpp`
declares `AptPalantir *TheAptPalantir` and converts the loaded value into its
local view. `Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp` owns
`LargeGroupAudio *TheLargeGroupAudio`;
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudge.cpp` owns
`SmudgeManager *TheSmudgeManager` and documents removal of a duplicate helper.
Its `Code/GameEngine/Include/Common/LivingWorldCampaignManager.h` records
a different cell (0x00E02D6C) and allocation size (0x30). BFME 1 owns a
different cell (0x012F1024) and 0x2C-byte allocation; no BFME 2 address,
layout or header is imported. These are shared ownership-pattern leads,
while the BFME 1 ledger and the actual retail operands prove these repairs.

The discovery scan excluded unused declarations and typedef spellings that
already emit the same COFF symbol. A bare-name candidate for TheTacticalView
was rejected: different decorated variants map to different retail cells.
The actual View* spelling resolves to 0x012F1600, not the shadow-manager
cell 0x01306EEC. The private discovery inventory was corrected before any
edit; no such view/shadow adaptation is present. CRC pointer consumers
already using their canonical owner were also excluded.

## Link measurement boundary

Latest completed Daily link census at the initial check:
[run 43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489),
input 1a248a7b476727c19e37a16744c71686fa8f3f5e, snapshot
2026-11-14 12:41 UTC. It contains 3,086,248 LINKED bytes in 15,516 files.
It predates faa6230837 and bccd6d679e. The earlier predicted additional
515 bytes remain unconfirmed by a later complete census.

All twenty original consumers were measured before edits against that
frozen index: 0/20 link, 0 -> 0 bytes. The repaired frozen-index preview also reports 0/20 link, 0 -> 0 bytes;
independent helper names, other globals and selected COMDAT copies remain
blockers. The staged current-provider preview reports UNKNOWN for all twenty
files after its 120-second deadline. No additional linked unit or linked byte
is claimed. These previews do not prove
a full-image link or runtime behavior; no FPS, memory, leak or crash-fix
claim follows from this batch.

Private source candidates, original and final-native objects, per-field
retail-address proofs and complete section comparisons remain under
`build/codex-20261115-twenty/` and
`W:/OpenBFME/diagnostics/continue-20261115-twenty/`.

GitHub and origin/master were checked again before publication: the same
43590726489 run remains the latest; no post-faa6230837 census is listed.
