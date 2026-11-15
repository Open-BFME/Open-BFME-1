# Canonical narrow-string adoption: tasks 9-28 of 200

Immediate baseline `07607fe7605517fda1538e2367fe6eaa70024011`.
Replace private AsciiString and local StringBase definitions with the existing
BFME 1 ascii_string.h. Neither shared header nor compiler flags change. The
source edits preserve existing names and signatures; no aliases or pins are authored.
A source-unit adoption is one task. Dependent cleanup locator repairs are not
counted again. This is reconciliation of existing code, not new authored-byte progress.

| Task | Source | Retained RVAs | Native new / corrected retail copies |
|---|---|---|---|
| 9 | `game/GameEngine/Source/GameClient/GUI/Rva56E070FinishState14.cpp` | `0x0056C210` | 2 / 1 |
| 10 | `game/GameEngine/Source/GameClient/GUI/OnlineLoginGadgetsState.cpp` | `0x0054DA10` | 1 / 0 |
| 11 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/ShowSkirmish.cpp` | `0x00579440` | 1 / 0 |
| 12 | `game/GameEngine/Source/GameClient/GUI/ShowLanLobby.cpp` | `0x00516C10` | 1 / 0 |
| 13 | `game/GameEngine/Source/GameClient/GUI/ShowOnlineShell.cpp` | `0x0055C180` | 1 / 0 |
| 14 | `game/GameEngine/Source/Common/VersionGetAsciiVersion.cpp` | `0x00BF7D38`, `0x000AEC40` | 0 / 0 |
| 15 | `game/GameEngine/Source/Common/BfmeOwnVVBDestructor.cpp` | `0x00190490`, `0x00C06C16` | 0 / 0 |
| 16 | `game/GameEngine/Source/Common/VersionConstructor.cpp` | `0x000AEA60` | 0 / 0 |
| 17 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/ShowCampaignReview.cpp` | `0x0050DCB0` | 1 / 0 |
| 18 | `game/GameEngine/Source/Common/Rva00474A90PopHeapAux.cpp` | `0x00474A90` | 0 / 0 |
| 19 | `game/GameEngine/Source/GameLogic/Object/ExperienceTrackerBFMEDtor.cpp` | `0x001B22F0` | 0 / 0 |
| 20 | `game/GameEngine/Source/Common/S4PopHeapElem12.cpp` | `0x00531A40` | 0 / 0 |
| 21 | `game/GameEngine/Source/Common/MultiplayerColorPairConstructor.cpp` | `0x0008E630`, `0x0008E560`, `0x0008E440` | 0 / 0 |
| 22 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DFloorDrawDestructor.cpp` | `0x007518D0`, `0x00751A40` | 2 / 1 |
| 23 | `game/GameEngine/Source/GameNetwork/GameInfoCopyCtor.cpp` | `0x004F9A70` | 2 / 1 |
| 24 | `game/GameEngine/Source/GameClient/GUI/Rva0051D960ShellPush.cpp` | `0x0051D9D0`, `0x0051D960` | 1 / 0 |
| 25 | `game/GameEngine/Source/Common/S4AdjustHeap002E07A0.cpp` | `0x002E07A0` | 0 / 0 |
| 26 | `game/GameEngine/Source/GameClient/GUI/BfmeAptScreenCampaignReviewDestructor.cpp` | `0x0050DBD0`, `0x0050E1A0` | 1 / 0 |
| 27 | `game/GameEngine/Source/Common/Rva002E0BC0PopHeap12.cpp` | `0x002E0BC0` | 0 / 0 |
| 28 | `game/GameEngine/Source/GameClient/GUI/OnlineConnectingPlayerStatus.cpp` | `0x00538490` | 1 / 0 |

## Target, compiler and object evidence

Independent BFME 1 native header evidence establishes the four-byte narrow
string object, its StringBase<char> base at +0, and the original copy/release
call contracts. Per-unit native CodeView controls confirm size4 and no virtual
pointer. A size1 incomplete facade is allowed only when every original runtime
section and relocation is unchanged, so no size-dependent use is introduced.
Private controls share one physical compiler-input path and original logical
source context. A separate final comparison uses normal native build objects.

All 27 existing retained rows keep their 2,719 code bytes.
Every original ordinary code/data section, relocation site/kind and local
target retains its graph position. Shared external identities retain their
offset/type. SafeSEH indices compare resolved handlers; other EH data and local
action offsets are compared through the same parent-rooted graph. Local section
numbers and compiler-label spellings may differ, but roles and offsets may not.

Changes or additions to COMDAT implementations are admitted only when the
repository's relocation-aware link_census.RetailTruth reports retail and finds
an existing matched ledger identity, including its registered implementation
object-symbol. This checks full bytes and every resolvable target against retail,
rather than trusting a candidate pin that the ordinary byte gate could mask.
For example, a destructor must jump to the original releaseBuffer entry, not
merely to a differently named destructor whose own body tail-jumps there.
This batch has 14 additional retail-proven copies and
3 changed copies proven retail-correct after adoption.
These are existing function identities and do not count as newly reconstructed functions.
No new unknown/wrong implementation is accepted. An existing definition may
disappear only when it is a canonical copy proven wrong and no retained row is lost.

VC7 may duplicate the existing canonical header's three template fallback
directives. Only exact aliases already emitted by unchanged verified providers
are allowed; newly duplicated aliases are unreferenced by the consumer. Other
directive tokens must remain equal. The inequality alias remains unknown to
alias_guard; no new caller route or pin is claimed for it. Less/equality are ok.
No verifier, alias guard or baseline changes. Private proof controls reject
a changed parent opcode, a damaged new helper, an altered compiler alias and
a shifted exception-table local target.

## Ordinary gates and exception locators

The final combined ordinary gate passes 201/201
functions across 24 sources, 363 DIR32 references
and the body guard, including the unchanged four canonical provider sources.
2 unique stale/wrong cleanup locators are updated only by
eh_state_pins.py --fix using the same retail parent state indices. All source
rows were reserved before experiments. Original native gates, final gates,
CodeView data, complete COFF proof records and row-specific prior attempts
are retained under build/codex-20261115-twohundred/ and this round's diagnostics.

## Reference and discovery context

Read-only BFME 2 reference f6c3838e7b58025531e09913bc42b810f1a01216 remains
within the 72-hour check window. Code/Libraries/Source/WWVegas/WWLib/string_base.h
and docs/recipes.md inform the shared owner pattern, while BFME 1's own settled
headers and retail facts determine inheritance, buffer layout, addresses and ABI.
No donor address, private buffer representation or flag is copied. The BFME 2
binary-reference scan was refreshed after the earlier ledger edits (53,034 bodies).
The existing Zero Hour pass remains a discovery lead, not identity proof.
Unchanged DXERR/near blockers are not retried. Candidate compile/layout/object
failures retain their diagnostics and edits are not applied. No failed attempt
is counted as a completed adoption.

## Link preview

Before: 14/20 LINKS, 1,693 bytes.
After at the same frozen census: 14/20 LINKS, 1,693 bytes.
No previously linkable unit is lost. These are bounded previews, not a new
complete census or whole-image/runtime/crash-fix proof.
Staged current-provider preview: 20/20 UNKNOWN, 0/20 LINKS, 0/20 blocked. Unknown results authorize no LINKED claim.

The complete census43711614660 at7c314a3e6c confirms the preceding +450B,
but predates this round's header adoptions. Its total is3,088,824 LINKED B;
the full-file confirmation is recorded in 20261115-450-byte-census-confirmation.md.

| Cleanup RVA | Object label before -> proven after | Parent state evidence |
|---|---|---|
| `0x00BF7D38` | `$L658` -> `$L879` | `?getAsciiVersion@Version@@QAE?AVAsciiString@@XZ` states `[0]` |
| `0x00C06C16` | `$L673` -> `$L907` | `??1BfmeOwnVVB@@UAE@XZ` states `[2]` |
