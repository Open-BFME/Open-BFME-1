# Eighty-task continuation: consumer repairs, batch 4/4

Work items 61-80; twenty existing consumer source units.
The source baseline for the complete eighty-task selection is
`0a4e37f49e549512f679a601556a4220ffdec271`. The immediate publication baseline
for this batch is `5d2e42eee29f294afc491084bcf6a6a9c5300372`.
These are data-binding repairs, not new function reconstructions or authored-byte gains.

| Task | Consumer | Existing provider contracts | Retained row RVAs |
|---|---|---|---|
| 61 | `game/GameEngine/Source/Common/R2GuardedTailCalls.cpp` | `R2Ptr012F0FE0` -> `TheGlobalWeatherSystem` (0x12f0fe0) | `0x0050D910`, `0x00516690`, `0x0055BD40`, `0x0056A810`, `0x00579040`, `0x006E17A0`, `0x000C9580`, `0x001BE3D0`, `0x00681B40`, `0x00970690`, `0x00970BE0`, `0x00971B50`, `0x004165F0`, `0x006FCE10`, `0x00417240`, `0x00730CF0`, `0x00730D10` |
| 62 | `game/GameEngine/Source/GameClient/GUI/AptMapPreview.cpp` | `g_s4Holder` -> `g_rva012F19E8WindowManager` (0x12f19e8) | `0x005207C0`, `0x00C2FFC0`, `0x00521990`, `0x005204F0`, `0x00521000`, `0x00521160`, `0x005216B0` |
| 63 | `game/GameEngine/Source/GameLogic/AI/AIFollowWaypointPathState_onEnter.cpp` | `TheCRCParameterCheck` -> `TheCRCParameterCheck` (0x12ed4fc) | `0x0017A8E0` |
| 64 | `game/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdate_update.cpp` | `ThePartitionManager` -> `ThePartitionManager` (0x12ed5b8) | `0x00297930` |
| 65 | `game/Libraries/Source/Apt/BfmeDispatchDirect1281.cpp` | `g_bfmeHolderBU` -> `g_bfmeHolderBU` (0x13377d8) | `0x008BB720`, `0x008D3050` |
| 66 | `game/GameEngine/Source/Common/GameEngine_execute.cpp` | `TheGen001336E5C` -> `g_Rva00F36E5C` (0x1336e5c) | `0x0006BC3E`, `0x0006BCB9`, `0x0006BD33` |
| 67 | `game/GameEngine/Source/Common/S3GuardedDelegatesBulk.cpp` | `TheBfmeTarget_002F1290` -> `TheLivingWorldLogic` (0x12f1028), `TheBfmeTarget_006BE210` -> `TheTerrainRenderObject` (0x12f7fe0) | `0x001BF950`, `0x001D5EE0`, `0x002DDCC0`, `0x003C6340`, `0x004125F0`, `0x00429F60`, `0x0042E700`, `0x0043A570`, `0x0043BC10`, `0x0060D600`, `0x00681960`, `0x00681B60`, `0x00681B80`, `0x00681DD0`, `0x006BC890`, `0x006C7690`, `0x006C8870`, `0x006C89D0`, `0x006C8A60`, `0x006C8A80`, `0x006C8C00`, `0x00730E00`, `0x00730E60`, `0x00730F10`, `0x00730F50`, `0x0075BE40`, `0x0094BFA0`, `0x0094BFB0`, `0x002F1290`, `0x00688AB0`, `0x006BE210`, `0x009EBB40`, `0x009EBB60` |
| 68 | `game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp` | `DebugGlobal00409E20` -> `g_Rva00F36E5C` (0x1336e5c) | `0x00694230`, `0x000BEF60`, `0x00191C10`, `0x006925F0`, `0x00693B90` |
| 69 | `game/Libraries/Source/Apt/AptInput.cpp` | `g_bfmeHolderBU` -> `g_bfmeHolderBU` (0x13377d8) | `0x008BB570`, `0x008BAAB0`, `0x008BA970`, `0x008BB3F0`, `0x008BCCC0`, `0x008D1FB0`, `0x008BA8B0`, `0x008BC360` |
| 70 | `game/GameEngine/Source/GameClient/MovieOpen0040E3B0.cpp` | `Transitions0040E3B0` -> `TheTransitionHandler` (0x12f3330), `Window0040F780` -> `ApplicationHWnd` (0x12ed238) | `0x0040E3B0`, `0x0040F780`, `0x0040E680` |
| 71 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptLoadScreenInit.cpp` | `Rva00579160TheCurrent` -> `TheSkirmishGameInfo` (0x12f7094) | `0x0051C2D0` |
| 72 | `game/GameEngine/Source/GameClient/ClientUpdate004329D0.cpp` | `GenFallback0012ED5C8` -> `TheWritableGlobalData` (0x12ed5c8) | `0x004329D0` |
| 73 | `game/GameEngine/Source/GameLogic/System/GameLogicDestructorThunk.cpp` | `g_bfmeJ1023` -> `TheLargeGroupAudio` (0x12f1044) | `0x0038F080`, `0x00C1C003`, `0x00C1BED8`, `0x00C1BFA5`, `0x00387480` |
| 74 | `game/GameEngine/Source/Common/Glo012F1024Entry_bfmeStep.cpp` | `g_bfmeGlobal_012f706c` -> `TheLivingWorldManager` (0x12f706c), `g_bfmeGlobal_012f1024` -> `TheLivingWorldCampaignManager` (0x12f1024) | `0x003AEE70`, `0x003A7320`, `0x003AE600`, `0x003AE1C0`, `0x003AD810`, `0x003AEF20`, `0x003ADC30`, `0x003AD4A0`, `0x003AE370`, `0x003ADFC0`, `0x003ADCC0`, `0x003ADDB0`, `0x003ADED0`, `0x003AE030` |
| 75 | `game/GameEngine/Source/GameNetwork/LANAPIUpdate.cpp` | `TheGameText` -> `TheGameText` (0x12f147c) | `0x006870F0` |
| 76 | `game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_attemptDamage.cpp` | `TheBfmeGameLogic` -> `TheGameLogic` (0x12f0898) | `0x00211D40` |
| 77 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006EB500.cpp` | `Glo012F1028` -> `TheLivingWorldLogic` (0x12f1028), `g_bfmeA1087` -> `TheTerrainRenderObject` (0x12f7fe0) | `0x006EB500` |
| 78 | `game/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate_update.cpp` | `Rva012ed668` -> `TheAudio` (0x12ed668) | `0x002AB690`, `0x00C6FE20`, `0x00C6FE30` |
| 79 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen_populatePlayerInfo.cpp` | `Rva012F415C` -> `parent` (0x12f415c) | `0x004E5DF0` |
| 80 | `game/GameEngine/Source/GameClient/MessageStream/CommandXlatVoice.cpp` | `g_va012F0888` -> `TheExperienceLevelSystem` (0x12f0888) | `0x005A7CF0`, `0x005A8A10`, `0x005A92D0`, `0x005AA450` |

## Independent BFME 1 evidence

24 consumer/global contracts are corrected across 84
actual reference fields. All 112 retained consumer rows preserve
their complete 45,026 compiled bytes and all relocation fields
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
is substituted. This batch contains 34 `.xdata` and
15 `.sxdata` sections; their semantics are retained.

The combined native gate passes 3478/3478 functions
across 33 function sources, verifies 30
data rows and 802 DIR32 references, and passes the body guard.
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
and section comparisons are retained under `build/codex-20261115-eighty/batch-4/`
and `W:/OpenBFME/diagnostics/continue-20261115-eighty/batch-4/`.

## Shared-global reload preservation, task 76

`ActiveBody_attemptDamage.cpp` already documented why its second spelling of
VA 0x012F0898 was retained: MSVC reloads that spelling instead of reusing the
frame-comparison load. A direct merge into TheGameLogic preserved the 1,803-byte
extent but changed 530 raw byte positions and the saved-register allocation.
That candidate was never applied.

The accepted source removes the redundant TheBfmeGameLogic declaration and
reads the existing canonical pointer at the original last-damage local via
`static_cast<GameLogic *volatile &>(TheGameLogic)`. This is qualification of
the same pointer object, not access through an unrelated pointer-reference
type. It retains all 1,803 compiled bytes, relocations and the full section
graph. The original function logic, getter calls and local GameLogic view
remain intact. The ordinary native provider/consumer gate passes.

The TU uses MSVC 13.10.3077 with `/DNDEBUG /MD /EHsc` and its WWLib include;
no flag is changed. This source-specific reload preservation is also recorded
in `docs/shape_levers.md`; no generic optimizer or concurrency claim follows.

The canonical data owner g_Rva00F36E5C is already matched at VA 0x01336E5C.
Using that existing address-derived name introduces two lexical occurrences
in GameEngine_execute and five in MilesAudioCacheReadAudioFile00694230.
The exact token in those two sources is registered through the native
`hatch_counters.py --admit --tokens` mechanism, after the consumer/provider,
complete-object and actual retail-address proofs. This creates no datum,
pin, alias or unchecked numeric access. The first scoped admission reports
the unrelated existing g_Va012A7244 token as not admitted; that token and
its register entry remain unchanged. MovieOpen already had two occurrences;
its warning and the other unchanged address-token warnings are pre-existing.
The register is changed only by its native tool.

The protected-register update is disclosed by a Verifier-Change trailer.
The first commit-message check rejected the missing disclosure; the message
was corrected and the ordinary hooks rerun without changing any checker.
