# Eighty-task continuation: consumer repairs, batch 2/4

Work items 21-40; twenty existing consumer source units.
The source baseline for the complete eighty-task selection is
`0a4e37f49e549512f679a601556a4220ffdec271`. The immediate publication baseline
for this batch is `4fe02b9d8613c2ece434c2f6a1d6a7bcc5260613`.
These are data-binding repairs, not new function reconstructions or authored-byte gains.

| Task | Consumer | Existing provider contracts | Retained row RVAs |
|---|---|---|---|
| 21 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineChat.cpp` | `TheGameSpyInfo` -> `TheGameSpyInfo` (0x12f7194) | `0x005369A0` |
| 22 | `game/GameEngine/Source/Common/BfmeConv1020.cpp` | `g_bfmeJ1020` -> `TheExperienceLevelSystem` (0x12f0888) | `0x00490580`, `0x00490740`, `0x00381260`, `0x005701D0` |
| 23 | `game/GameEngine/Source/GameClient/GUI/Palantir/PalantirRankAndButtons00590480.cpp` | `g_obj12F4C38` -> `g_purchaseScienceWindow` (0x12f4c38) | `0x00590480` |
| 24 | `game/Libraries/Source/Apt/AptTick00894660.cpp` | `g_bfmeHolderBU` -> `g_bfmeHolderBU` (0x13377d8) | `0x00892A70`, `0x00894660`, `0x00C56F20` |
| 25 | `game/GameEngine/Source/Common/BfmeConv1058.cpp` | `g_bfmeJ1058` -> `TheExperienceLevelSystem` (0x12f0888) | `0x0039B610`, `0x001B23B0`, `0x005053C0`, `0x0075C940` |
| 26 | `game/GameEngine/Source/Common/Gen0000D33CCtor004354F0.cpp` | `Rva0048EC80TheManager` -> `TheDisplayStringManager` (0x12f12cc) | `0x00434FF0`, `0x004354F0` |
| 27 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenLeave.cpp` | `TheLivingWorldLogic` -> `TheLivingWorldLogic` (0x12f1028) | `0x00573000` |
| 28 | `game/Libraries/Source/Apt/BfmePrepareSlots1281.cpp` | `g_bfmeHolderBU` -> `g_bfmeHolderBU` (0x13377d8) | `0x008BBDB0` |
| 29 | `game/GameEngine/Source/Common/BfmeConv414.cpp` | `g_bfmeSinkAM` -> `TheLivingWorldManager` (0x12f706c), `g_bfmeOneAQA` -> `g_rva012F7048LivingWorld` (0x12f7048) | `0x0060D360`, `0x003C9320` |
| 30 | `game/GameEngine/Source/Common/Rva00367810EntriesStartNewGame.cpp` | `Glo012F1028` -> `TheLivingWorldLogic` (0x12f1028) | `0x00367470` |
| 31 | `game/Libraries/Source/Apt/AptCIH.cpp` | `g_manager013377D8` -> `g_bfmeHolderBU` (0x13377d8) | `0x008C3F10` |
| 32 | `game/GameEngine/Source/Common/R1ForwardToStoredObject.cpp` | `g_Glo00EF7048` -> `g_rva012F7048LivingWorld` (0x12f7048) | `0x0021A2D0`, `0x002EFF00`, `0x002F0930`, `0x000A14D0`, `0x000A14F0`, `0x0015C260`, `0x00238AC0`, `0x002BA1E0`, `0x0015B750`, `0x0025FA60`, `0x0046B3B0` |
| 33 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerStartRenderToTexture.cpp` | `TheBfmeGlobal_012f7fe0` -> `TheTerrainRenderObject` (0x12f7fe0) | `0x007171F0` |
| 34 | `game/Libraries/Source/Apt/Rva00893020KeyPairChecks.cpp` | `g_bfmeStringPool1284` -> `g_rva01337A30AllocPair` (0x1337a30) | `0x00893020`, `0x008951F0`, `0x00892FD0`, `0x00895790` |
| 35 | `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarDrawEvents.cpp` | `Glo012F4B98` -> `TheAptPalantir` (0x12f4b98) | `0x006C3170`, `0x00C70920`, `0x006C1B50`, `0x00107550` |
| 36 | `game/GameEngine/Source/Common/System/SaveGame/GameStateInit.cpp` | `TheWeatherSystem` -> `TheGlobalWeatherSystem` (0x12f0fe0) | `0x001112D0` |
| 37 | `game/GameEngine/Source/GameLogic/System/GameLogicPeerCRC.cpp` | `TheNetwork` -> `TheNetwork` (0x12f7714) | `0x0038B430` |
| 38 | `game/GameEngine/Source/GameLogic/World/ParseObjectDataChunk_Thunk.cpp` | `TheThingFactory` -> `TheThingFactory` (0x12ef1d8) | `0x00454760` |
| 39 | `game/GameEngine/Source/GameLogic/Object/SpecialPower/GrabPassengerSpecialPowerDoSpecialPowerAtObject.cpp` | `TheActionManager` -> `TheActionManager` (0x12ed700) | `0x0025F6C0` |
| 40 | `game/Libraries/Source/EA/Apt/Rva008C6320.cpp` | `g_bfmeHolderBU` -> `g_bfmeHolderBU` (0x13377d8) | `0x008C6320`, `0x008C4DA0`, `0x008D0B00` |

## Independent BFME 1 evidence

21 consumer/global contracts are corrected across 58
actual reference fields. All 48 retained consumer rows preserve
their complete 12,219 compiled bytes and all relocation fields
except the intended data-symbol bindings. Each changed DIR32 operand was
decoded inside its own complete retail function and equals the existing
owner's exact VA. Equal values or a same-name donor object are insufficient.
The existing BFME 1 data ledger supplies independent registration, constructor,
store, vtable and pointer-cell identity evidence. Opaque identities stay opaque.

The source requests the existing owner's decorated symbol and pointer type;
the receiver/layout views remain the prior local types through pointer-value
conversions. Providers, method identities, arguments and field offsets are
retained. No new data definition, symbol pin, linker alias, header or compiler
flag is introduced. No pointer cell is accessed through an unrelated pointer
reference. A null store, where present, writes zero to the canonical lvalue.

Whole-object checks compare ordered non-debug sections, their sizes, flags,
bytes, relocation graphs, and the section/value/type of every defined external.
Local targets compare by section and offset. `.sxdata` contains COFF symbol
indices rather than runtime addresses: its entries compare by their resolved
handler targets, allowing only symbol-table renumbering. No exception target
is substituted. This batch contains 11 `.xdata` and
8 `.sxdata` sections; their semantics are retained.

The combined native gate passes 442/442 functions
across 33 function sources, verifies 28
data rows and 394 DIR32 references, and passes the body guard.
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
Repaired objects against that same frozen index: 1/20 link,
LINKED 0 -> 377 bytes.
Staged current-provider preview: 20/20 UNKNOWN, 0/20 LINKS, 0/20 blocked. The 120-second deadline expired before any current-provider verdict.
These are bounded previews. They are not a new complete census, full-image
link, runtime, FPS, memory, leak or crash-fix result.

Original sources/objects, final-native objects, per-field retail-address proofs
and section comparisons are retained under `build/codex-20261115-eighty/batch-2/`
and `W:/OpenBFME/diagnostics/continue-20261115-eighty/batch-2/`.

The hatch checker notes a stale emit allowance of 605 for
`ParseObjectDataChunk_Thunk.cpp`. The saved original source already contains
zero __emit occurrences; this batch does not claim their removal and does
not edit the unrelated register.

The AptTick exception funclet row 0x00C56F20 has a 22-byte retained extent.
The object reader also returns trailing handler bytes; the private row
comparison is bounded to the ledger extent, while the full section graph
continues to verify those trailing bytes and their resolved targets.
