# Eighty-task continuation: consumer repairs, batch 3/4

Work items 41-60; twenty existing consumer source units.
The source baseline for the complete eighty-task selection is
`0a4e37f49e549512f679a601556a4220ffdec271`. The immediate publication baseline
for this batch is `4a6318db523a089e15a992867d7ec6b5c63c6e56`.
These are data-binding repairs, not new function reconstructions or authored-byte gains.

| Task | Consumer | Existing provider contracts | Retained row RVAs |
|---|---|---|---|
| 41 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawTransformChange.cpp` | `TheTerrainRenderObject` -> `TheTerrainRenderObject` (0x12f7fe0) | `0x00763620` |
| 42 | `game/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMapUpdateCenter.cpp` | `Rva012ED5C8` -> `TheWritableGlobalData` (0x12ed5c8) | `0x006D2A00` |
| 43 | `game/GameEngine/Source/GameClient/GUI/Palantir/GameClientUpdate00598950.cpp` | `TheLivingWorldLogic` -> `TheLivingWorldLogic` (0x12f1028), `Campaign00598950` -> `TheLivingWorldCampaignManager` (0x12f1024) | `0x00598950` |
| 44 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenInGameChatRefreshFriendsList.cpp` | `TheGameSpyInfo` -> `TheGameSpyInfo` (0x12f7194) | `0x00515810` |
| 45 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchAcceptJoinGame.cpp` | `TheGameSpyInfo` -> `TheGameSpyInfo` (0x12f7194) | `0x0053DFC0` |
| 46 | `game/GameEngine/Source/GameClient/MovieFrame0040E9E0.cpp` | `EngineGlobal007629F0` -> `TheGameEngine` (0x12ed524) | `0x0040E9E0` |
| 47 | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGarrisonNearestBuilding_Thunk.cpp` | `ThePartitionManager` -> `ThePartitionManager` (0x12ed5b8) | `0x00302630` |
| 48 | `game/Libraries/Source/EA/Apt/ArrayProperties008BA0B0.cpp` | `g_bfmeResult1233` -> `g_bfmeFallbackDB` (0x13379bc) | `0x00C59160`, `0x00C5916F`, `0x00C5917E`, `0x00C5918D`, `0x00C5919C`, `0x00C591AB`, `0x00C591BA`, `0x00C591C9`, `0x00C591D8`, `0x00C591E7`, `0x00C591F6`, `0x00C59205`, `0x008BA0B0` |
| 49 | `game/GameEngine/Source/GameLogic/LivingWorld/INILivingWorldPlayerArmy.cpp` | `TheLivingWorldCampaignManager` -> `TheLivingWorldCampaignManager` (0x12f1024) | `0x003651E0`, `0x003649D0`, `0x00362B20`, `0x003B5FA0`, `0x00364AC0`, `0x00364DE0`, `0x003619C0`, `0x003B43D0`, `0x00362BE0`, `0x00366410`, `0x00365570` |
| 50 | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceLoadPostProcess.cpp` | `g_owner002E4030` -> `TheLuaScriptEngine` (0x12f060c) | `0x0027A5E0` |
| 51 | `game/GameEngine/Source/GameNetwork/LANAPIBfmeSerializedGameInfo.cpp` | `g_bfme935GlobC` -> `g_rva012F4998LanLobby` (0x12f4998) | `0x00689170` |
| 52 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchRva0053E870.cpp` | `TheGameSpyInfo` -> `TheGameSpyInfo` (0x12f7194) | `0x00C31A80`, `0x0053E870` |
| 53 | `game/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp` | `ThePartitionManager` -> `ThePartitionManager` (0x12ed5b8) | `0x00295760` |
| 54 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowRender007B6520.cpp` | `terrain012F7FE0` -> `TheTerrainRenderObject` (0x12f7fe0) | `0x007B6520` |
| 55 | `game/GameEngine/Source/Common/Rva006E2540.cpp` | `ClientAt012F1464` -> `TheGameClient` (0x12f1464) | `0x006E2540` |
| 56 | `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogicRva003C3850.cpp` | `TheLivingWorldLogic` -> `TheLivingWorldLogic` (0x12f1028) | `0x003C3850` |
| 57 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Glo00EF4988RemoveFriends.cpp` | `TheGameSpyInfo` -> `TheGameSpyInfo` (0x12f7194) | `0x005143D0`, `0x00514560` |
| 58 | `game/GameEngine/Source/Common/R1GuardedPointerTailCalls.cpp` | `g_Glo00EF3330` -> `TheTransitionHandler` (0x12f3330) | `0x00691030`, `0x00691130`, `0x00382980`, `0x0050D3B0`, `0x00514D60`, `0x00514D80`, `0x00584E20`, `0x00730FE0`, `0x00754A10`, `0x001BF380`, `0x003BCA20`, `0x003D5780`, `0x004AD970`, `0x005376D0`, `0x00609850`, `0x0060D5E0`, `0x0060D620`, `0x006819B0`, `0x00681A80`, `0x006C8BE0`, `0x0076EFE0`, `0x007D2340`, `0x007D2350` |
| 59 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby_getGameInfoRva00516850.cpp` | `g_bfmeR1078` -> `g_rva012F19E8WindowManager` (0x12f19e8) | `0x00516850`, `0x00519150` |
| 60 | `game/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdateChangeVisualDisguise.cpp` | `TheThingFactory` -> `TheThingFactory` (0x12ef1d8) | `0x00267B10` |

## Independent BFME 1 evidence

21 consumer/global contracts are corrected across 40
actual reference fields. All 67 retained consumer rows preserve
their complete 18,786 compiled bytes and all relocation fields
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
is substituted. This batch contains 37 `.xdata` and
14 `.sxdata` sections; their semantics are retained.

The combined native gate passes 1168/1168 functions
across 29 function sources, verifies 25
data rows and 507 DIR32 references, and passes the body guard.
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
LINKED 0 -> 1,115 bytes.
Staged current-provider preview: 20/20 UNKNOWN, 0/20 LINKS, 0/20 blocked. The 120-second deadline expired before any current-provider verdict.
These are bounded previews. They are not a new complete census, full-image
link, runtime, FPS, memory, leak or crash-fix result.

Original sources/objects, final-native objects, per-field retail-address proofs
and section comparisons are retained under `build/codex-20261115-eighty/batch-3/`
and `W:/OpenBFME/diagnostics/continue-20261115-eighty/batch-3/`.

## Array-properties compiler context, task 48

The 1,824-byte lookup row at 0x008BA0B0 has twelve existing 15-byte cleanup
rows 0x00C59160..0x00C59205. The first typed-global trial shifted their
compiler-local $L pins by two; the native reader refused to select among
identical bodies. Returning the new AptValue pointer implicitly as void*
reduced the shift by one but still left an ambiguous anchor. Neither trial
was applied or admitted with an exception.

The successful source retains the explicit pointer-value conversion and
removes the unused `void *Rva00897640(unsigned);` prototype. That identifier
occurs only in its declaration in the original TU and emitted no external
reference. With this minimal cleanup, all twelve original cleanup pins
hold their existing bodies and the ordinary native verifier passes. The
main body and its jump-table target graph are unchanged; arbitrary local
jump-label spellings are compared by their actual COFF section and offset.
The complete consumer object retains every non-debug section's semantics,
including its unwind tables. No ledger pin or checker is changed.

MSVC 13.10.3077; `/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`. This is an
observed preservation of this source's compiler context, not a general rule
for numbering labels. Successful and failed candidates remain in
`build/codex-20261115-eighty/batch-3/task-48-*`.

The hatch checker reports existing, unregistered address-global and class-gate
allowances in the movie-frame, flat-height-map, LAN serialization/lobby and
HeightDie units. Every reported token has the same occurrence count in the
saved original and repaired source. No allowance is introduced or enlarged.
The garrison thunk already had zero __emit occurrences before this repair;
its stale register allowance of 451 is not credited as a removal here.
