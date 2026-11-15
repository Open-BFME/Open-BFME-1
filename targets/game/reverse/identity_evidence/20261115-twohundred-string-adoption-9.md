# Canonical narrow-string adoption: tasks 95-102 of 200

Immediate baseline `8a6eec11f92fc6299c09a01d046927a00dffbec5`.
Replace private AsciiString and local StringBase definitions with the existing
BFME 1 ascii_string.h. Neither shared header nor compiler flags change. The
source edits preserve existing names and signatures; no aliases or pins are authored.
A source-unit adoption is one task. Dependent cleanup locator repairs are not
counted again. This is reconciliation of existing code, not new authored-byte progress.

| Task | Source | Retained RVAs | Native new / corrected retail copies |
|---|---|---|---|
| 95 | `game/GameEngine/Source/GameClient/GUI/BfmeAptScreenLanLobby_applySlotStartPos.cpp` | `0x00517050` | 1 / 0 |
| 96 | `game/GameEngine/Source/GameClient/DrawableInitStaticImages.cpp` | `0x00415D50` | 0 / 0 |
| 97 | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptRecordTableAddScriptNode.cpp` | `0x0035D1E0`, `0x0035D26D` | 0 / 0 |
| 98 | `game/GameEngine/Source/Common/RTS/Rva000C5EF0ActionManager.cpp` | `0x000C5EF0` | 2 / 0 |
| 99 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/GetAdditionalDisconnectsFromUserFile.cpp` | `0x004DB560`, `0x000A31F0`, `0x000A3470` | 1 / 0 |
| 100 | `game/GameEngine/Source/GameClient/GUI/OnlineChatRva0052E990.cpp` | `0x0052E990` | 2 / 0 |
| 101 | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsHasCommandPointsToBuildTeam.cpp` | `0x003262C0` | 1 / 0 |
| 102 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/DifficultySelectSystem_Thunk.cpp` | `0x004C72C0` | 0 / 0 |

## Target, compiler and object evidence

Independent BFME 1 native header evidence establishes the four-byte narrow
string object, its StringBase<char> base at +0, and the original copy/release
call contracts. Per-unit native CodeView controls confirm size4 and no virtual
pointer. A size1 incomplete facade is allowed only when every original runtime
section and relocation is unchanged, so no size-dependent use is introduced.
Private controls share one physical compiler-input path and original logical
source context. A separate final comparison uses normal native build objects.

All 11 existing retained rows keep their 4,212 code bytes.
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
This batch has 7 additional retail-proven copies and
0 changed copies proven retail-correct after adoption.
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

The final combined ordinary gate passes 185/185
functions across 12 sources, 437 DIR32 references
and the body guard, including the unchanged four canonical provider sources.
0 unique stale/wrong cleanup locators are updated only by
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

Before: 7/8 LINKS, 2,934 bytes.
After at the same frozen census: 7/8 LINKS, 2,934 bytes.
No previously linkable unit is lost. These are bounded previews, not a new
complete census or whole-image/runtime/crash-fix proof.
Staged current-provider preview: 8/8 UNKNOWN, 0/8 LINKS, 0/8 blocked. Unknown results authorize no LINKED claim.

The complete census43711614660 at7c314a3e6c confirms the preceding +450B,
but predates this round's header adoptions. Its total is3,088,824 LINKED B;
the full-file confirmation is recorded in 20261115-450-byte-census-confirmation.md.

## Unchanged wide-string companions

1 units also contain a private UnicodeString view. The narrow-string
header only forward-declares that type, so its source definition is retained.
Independent CodeView controls require its size, base identities/offsets, direct
fields, virtual pointer and slots to remain exactly equal. Ordinary runtime
graphs and retained rows still pass the same full comparison. This is not
an adoption or layout claim for the separate canonical UnicodeString header.
