# Canonical narrow-string adoption: tasks 29-41 of 200

Immediate baseline `b4de6134756cede1ad97ea8241544e8ed0b7214d`.
Replace private AsciiString and local StringBase definitions with the existing
BFME 1 ascii_string.h. Neither shared header nor compiler flags change. The
source edits preserve existing names and signatures; no aliases or pins are authored.
A source-unit adoption is one task. Dependent cleanup locator repairs are not
counted again. This is reconciliation of existing code, not new authored-byte progress.

| Task | Source | Retained RVAs | Native new / corrected retail copies |
|---|---|---|---|
| 29 | `game/GameEngine/Source/GameClient/GUI/OnlineConnectingPlayerName.cpp` | `0x005383F0` | 1 / 0 |
| 30 | `game/GameEngine/Source/Common/BfmeSortElem20TailCopy.cpp` | `0x002E7320` | 0 / 0 |
| 31 | `game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSchemeManagerInit.cpp` | `0x004ADD60` | 3 / 0 |
| 32 | `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldRegionManager_ParseNamedSubBlock.cpp` | `0x00C1F24B`, `0x003C9980`, `0x003C64D0`, `0x003C6EA0` | 0 / 0 |
| 33 | `game/GameEngine/Source/Common/VersionSetVersion.cpp` | `0x000AEB50`, `0x00BF7CF0` | 0 / 0 |
| 34 | `game/GameEngine/Source/GameClient/GUI/GameWindowTransitionGroupDestructor.cpp` | `0x0048AB20` | 1 / 0 |
| 35 | `game/GameEngine/Source/GameClient/GUI/OnlineChatDestructor.cpp` | `0x0052D7C0`, `0x0052E490` | 1 / 0 |
| 36 | `game/GameEngine/Source/GameClient/GUI/InGameChatDestructor.cpp` | `0x00511F50` | 1 / 0 |
| 37 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineQuickMatchDestructor.cpp` | `0x005587F0` | 1 / 0 |
| 38 | `game/GameEngine/Source/GameClient/GUI/OnlineHomeDestructor.cpp` | `0x00545FF0`, `0x00546690` | 1 / 0 |
| 39 | `game/GameEngine/Source/GameNetwork/GameSpy/GameSpyGameSlotCopyCtor.cpp` | `0x004FA0A0` | 2 / 1 |
| 40 | `game/GameEngine/Source/Common/BfmeOwnVUM_ctor.cpp` | `0x00362DC0` | 2 / 1 |
| 41 | `game/GameEngine/Source/GameClient/GUI/Rva00517720ClientStateName.cpp` | `0x00517720`, `0x00C2F368` | 2 / 0 |

## Target, compiler and object evidence

Independent BFME 1 native header evidence establishes the four-byte narrow
string object, its StringBase<char> base at +0, and the original copy/release
call contracts. Per-unit native CodeView controls confirm size4 and no virtual
pointer. A size1 incomplete facade is allowed only when every original runtime
section and relocation is unchanged, so no size-dependent use is introduced.
Private controls share one physical compiler-input path and original logical
source context. A separate final comparison uses normal native build objects.

All 20 existing retained rows keep their 2,920 code bytes.
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
This batch has 15 additional retail-proven copies and
2 changed copies proven retail-correct after adoption.
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

The final combined ordinary gate passes 194/194
functions across 17 sources, 366 DIR32 references
and the body guard, including the unchanged four canonical provider sources.
3 unique stale/wrong cleanup locators are updated only by
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

Before: 7/13 LINKS, 1,424 bytes.
After at the same frozen census: 7/13 LINKS, 1,424 bytes.
No previously linkable unit is lost. These are bounded previews, not a new
complete census or whole-image/runtime/crash-fix proof.
Staged current-provider preview: 13/13 UNKNOWN, 0/13 LINKS, 0/13 blocked. Unknown results authorize no LINKED claim.

The complete census43711614660 at7c314a3e6c confirms the preceding +450B,
but predates this round's header adoptions. Its total is3,088,824 LINKED B;
the full-file confirmation is recorded in 20261115-450-byte-census-confirmation.md.

| Cleanup RVA | Object label before -> proven after | Parent state evidence |
|---|---|---|
| `0x00C1F24B` | `$L5133` -> `$L5273` | `?parseNamedSubBlock@LivingWorldRegionManager@@SAXPAVINI@@PAX1PBX@Z` states `[1, 2]` |
| `0x00C2F368` | `$L386` -> `$L905` | `?Rva00517720ClientStateName@@YA?AVAsciiString@@W4Rva00517720ClientState@@@Z` states `[0]` |
| `0x00BF7CF0` | `$L663` -> `$L883` | `?setVersion@Version@@QAEXHHHHVAsciiString@@000@Z` states `[0]` |
