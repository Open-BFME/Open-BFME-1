# Eighty-task continuation: consumer repairs, batch 1/4

Work items 1-20; twenty existing consumer source units.
The source baseline for the complete eighty-task selection is
`0a4e37f49e549512f679a601556a4220ffdec271`. The immediate publication baseline
for this batch is `0a4e37f49e549512f679a601556a4220ffdec271`.
These are data-binding repairs, not new function reconstructions or authored-byte gains.

| Task | Consumer | Existing provider contracts | Retained row RVAs |
|---|---|---|---|
| 1 | `game/GameEngine/Source/Common/BfmeConv561.cpp` | `TheLivingWorldCampaignManager` -> `TheLivingWorldCampaignManager` (0x12f1024) | `0x00383950`, `0x00366130` |
| 2 | `game/GameEngine/Source/Common/BfmeConv1330.cpp` | `g_bfmeObjUDB` -> `TheTerrainRenderObject` (0x12f7fe0) | `0x006BE230`, `0x007D4620`, `0x00618EA0`, `0x001AA3E0` |
| 3 | `game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0025D6E0FreezingRainApply.cpp` | `g_bfmeModeAZC` -> `TheGlobalWeatherSystem` (0x12f0fe0) | `0x0025D6E0` |
| 4 | `game/GameEngine/Source/Common/BfmeConv817.cpp` | `g_bfmeMgr12F0898` -> `TheGameLogic` (0x12f0898), `g_global12EF1D8` -> `TheThingFactory` (0x12ef1d8) | `0x001DC9E0`, `0x001F6220`, `0x001DD1B0`, `0x001E4040` |
| 5 | `game/GameEngine/Source/Common/BfmeConv995.cpp` | `g_bfmeDrop995` -> `TheDisplayStringManager` (0x12f12cc) | `0x0069B170`, `0x00510C10`, `0x00537AB0` |
| 6 | `game/GameEngine/Source/Common/BfmeConv1081.cpp` | `g_bfmeJ1081` -> `TheExperienceLevelSystem` (0x12f0888) | `0x002F0400`, `0x00323FB0` |
| 7 | `game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00259CD0BoundsCentreApply.cpp` | `g_bfmeModeAZC` -> `TheGlobalWeatherSystem` (0x12f0fe0) | `0x00259CD0` |
| 8 | `game/GameEngine/Source/Common/BfmeConv830.cpp` | `g_mgr12F076C` -> `TheScriptEngine` (0x12f076c) | `0x002EE3F0`, `0x002EE510`, `0x002EE610`, `0x002EE5E0`, `0x002EE650` |
| 9 | `game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorNearestTemplate0036FE10.cpp` | `TheBfmeGameLogic` -> `TheGameLogic` (0x12f0898) | `0x0036FE10` |
| 10 | `game/GameEngine/Source/Common/BfmeConv980.cpp` | `g_bfmeFindA980` -> `TheThingFactory` (0x12ef1d8), `g_bfmeFindB980` -> `TheThingFactory` (0x12ef1d8) | `0x000F9570`, `0x000F9620`, `0x002DCD50` |
| 11 | `game/GameEngine/Source/Common/System/BfmeConv411.cpp` | `g_bfmeOneAOA` -> `TheAptPalantir` (0x12f4b98) | `0x00107340` |
| 12 | `game/GameEngine/Source/Common/INI/INIModifierList.cpp` | `TheRva00369860Registry` -> `TheAttributeModifierDefinitionStore` (0x12f07e4) | `0x0036B7C0` |
| 13 | `game/GameEngine/Source/Common/BfmeRva008C3AF0Unlink.cpp` | `g_bfme1211` -> `g_rva01337810GcRoots` (0x1337810) | `0x008C39E0`, `0x008C3AF0` |
| 14 | `game/GameEngine/Source/Common/BfmeConv1052.cpp` | `g_bfmeN1052` -> `TheAptPalantir` (0x12f4b98) | `0x00221870`, `0x005790B0`, `0x00800CA0`, `0x003BEF30`, `0x00579720` |
| 15 | `game/GameEngine/Source/Common/BfmeConv1014.cpp` | `g_bfmeStore1014` -> `TheGameLogic` (0x12f0898) | `0x002B0D00`, `0x004C8760`, `0x006C8B70`, `0x001A3730` |
| 16 | `game/GameEngine/Source/Common/Rva003C1A50_tick.cpp` | `TheLivingWorldCampaignManager` -> `TheLivingWorldCampaignManager` (0x12f1024) | `0x003C03C0` |
| 17 | `game/GameEngine/Source/Common/BfmeConv827.cpp` | `g_mgr12F4B98` -> `TheAptPalantir` (0x12f4b98) | `0x002EFBE0`, `0x002EF3E0`, `0x002EF7B0`, `0x002EF7F0`, `0x002F1120`, `0x002EFDB0` |
| 18 | `game/GameEngine/Source/Common/Rva006E6A80.cpp` | `ClientAt012F1464` -> `TheGameClient` (0x12f1464) | `0x006E6A80` |
| 19 | `game/GameEngine/Source/Common/BfmeConv1023.cpp` | `g_bfmeC1023` -> `TheNetwork` (0x12f7714), `g_bfmeJ1023` -> `TheLargeGroupAudio` (0x12f1044) | `0x0018D460`, `0x00491F70`, `0x004CAF00`, `0x002962C0` |
| 20 | `game/GameEngine/Source/GameLogic/AI/AICombineStateInternalUpdate.cpp` | `TheActionManager` -> `TheActionManager` (0x12ed700) | `0x0016F340` |

## Independent BFME 1 evidence

23 consumer/global contracts are corrected across 29
actual reference fields. All 52 retained consumer rows preserve
their complete 4,094 compiled bytes and all relocation fields
except the intended data-symbol bindings. Each changed DIR32 operand was
decoded inside its own complete retail function and equals the existing
owner's exact VA. Equal values or a same-name donor object are insufficient.
The existing BFME 1 data ledger supplies independent registration, constructor,
store, vtable and pointer-cell identity evidence. Opaque identities stay opaque.

The source requests the existing owner's decorated symbol and pointer type;
the receiver/layout views remain the prior local types through pointer-value
conversions. Providers, method identities, arguments and field offsets are
retained. No new data definition, symbol pin, linker alias, header or compiler
flag is introduced. These repairs introduce no pointer-cell access through
an unrelated pointer reference. A null store writes zero to the canonical lvalue.

Whole-object checks compare ordered non-debug sections, their sizes, flags,
bytes, relocation graphs, and the section/value/type of every defined external.
Local targets compare by section and offset. `.sxdata` contains COFF symbol
indices rather than runtime addresses: its entries compare by their resolved
handler targets, allowing only symbol-table renumbering. No exception target
is substituted. This batch contains 2 `.xdata` and
1 `.sxdata` sections; their semantics are retained.

The combined native gate passes 342/342 functions
across 34 function sources, verifies 29
data rows and 348 DIR32 references, and passes the body guard.
The initial eighty-consumer/provider baseline passed 4,604/4,604 functions
and 67 data rows. All eighty source declaration checks were run; existing
marked/whitelisted bodies are retained without adding function definitions.
Existing compiler-local funclet labels are resolved by the native checker;
no stale label is treated as a byte or exception mismatch.

Prior attempts were filtered by the selected RVAs and reviewed for the actual
binding names. Earlier register-allocation, incomplete-boundary and identity
blockers are not retried or bypassed: established bodies and callees remain.

## BFME 2 reference review

The read-only reference remains `f6c3838e7b58025531e09913bc42b810f1a01216`,
checked 2026-11-13T19:10:55Z and within the 72-hour window. The shared typed
data-owner pattern is reused, with independent BFME 1 target proof. Reviewed
paths include `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_Rva0035B03E.cpp`
(Palantir pointer-value local view), `Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`
(LargeGroupAudio owner), `Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp`
(interface factory), `Code/GameEngine/Source/GameClient/GameClient.cpp`
(GameClient/GlobalData declarations), and
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp`
(SkirmishGameInfo owner). The reference's ActionManager placement is explicitly
unverified there; BFME 1's own `identity_evidence/012ed700-pointer-global.md`
is the binding evidence instead. `identity_evidence/012f7194-gamespy-info.md`
independently proves BFME 1's factory, stored interface and pointer cell.
The donor GlobalData cell at 0x00DFE758 differs from BFME 1's 0x012ED5C8;
campaign allocation sizes/layouts also differ. No donor address or layout is
copied, and no BFME 2 development or test-server change is made.

The selection excludes unused declarations, already identical emitted symbols,
ambiguous bare names, and twenty-five other initial candidates.
All selected mappings have an actual reference in a retained matched row.

## Link measurements and limits

Latest complete census remains [run 43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489),
input 1a248a7b476727c19e37a16744c71686fa8f3f5e, snapshot
2026-11-14 12:41 UTC, 3,086,248 LINKED bytes in 15,516 files.
It predates faa6230837, bccd6d679e and 0a4e37f49e. The prior predicted
additional 515 bytes remain unconfirmed by a subsequent full census.

Original consumers measured before any of the eighty edits: 0/20
link in the frozen-index preview, LINKED 0 -> 0 bytes.
Repaired objects against that same frozen index: 0/20 link,
LINKED 0 -> 0 bytes.
Staged current-provider preview: 20/20 UNKNOWN, 0/20 LINKS, 0/20 blocked. The 120-second deadline expired before any current-provider verdict.
These are bounded previews. They are not a new complete census, full-image
link, runtime, FPS, memory, leak or crash-fix result.

Original sources/objects, final-native objects, per-field retail-address proofs
and section comparisons are retained under `build/codex-20261115-eighty/batch-1/`
and `W:/OpenBFME/diagnostics/continue-20261115-eighty/batch-1/`.
