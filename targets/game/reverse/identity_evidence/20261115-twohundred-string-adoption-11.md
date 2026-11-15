# Canonical narrow-string adoption: tasks 108-120 of 200

Immediate baseline `3e55a9958dedcbfaea0d1a77ea6ecf4139ce66b2`.
Replace private AsciiString and local StringBase definitions with the existing
BFME 1 ascii_string.h. Neither shared header nor compiler flags change. The
source edits preserve existing names and signatures; no aliases or pins are authored.
A source-unit adoption is one task. Dependent cleanup locator repairs are not
counted again. This is reconciliation of existing code, not new authored-byte progress.

| Task | Source | Retained RVAs | Native new / corrected retail copies |
|---|---|---|---|
| 108 | `game/GameEngine/Source/Common/Rva00467270AsciiStringFormat.cpp` | `0x00467270` | 3 / 0 |
| 109 | `game/Libraries/Source/WWVegas/WWLib/Rva00018ADEAsciiStringUpperBoundThunk.cpp` | `0x00018ADE` | 0 / 0 |
| 110 | `game/GameEngine/Source/GameLogic/ArmyNameFromIndex.cpp` | `0x003601A0` | 0 / 0 |
| 111 | `game/GameEngine/Source/GameLogic/Object/GenericObjectCreationNuggetAnimSetCopy.cpp` | `0x001D6B80` | 2 / 0 |
| 112 | `game/GameEngine/Source/GameLogic/ScriptEngine/LuaCurDrawableSetTransitionAnimState.cpp` | `0x002E3950` | 0 / 0 |
| 113 | `game/GameEngine/Source/Common/Rva14B630StringRecordCopy.cpp` | `0x0014B630` | 3 / 0 |
| 114 | `game/GameEngine/Source/Common/Rva0036CCC0PairCopy.cpp` | `0x0036CCC0` | 3 / 0 |
| 115 | `game/GameEngine/Source/GameNetwork/FileCommandMapIndex.cpp` | `0x00669B50` | 3 / 0 |
| 116 | `game/GameEngine/Source/GameClient/GUI/HeaderTemplateManagerGetFontFromTemplate.cpp` | `0x0048C9E0` | 2 / 0 |
| 117 | `game/GameEngine/Source/Common/System/GeometryRecordCopy.cpp` | `0x000FD650` | 3 / 0 |
| 118 | `game/GameEngine/Source/Common/SkirmishBattleHonors_rankDisplay.cpp` | `0x0009D450` | 2 / 0 |
| 119 | `game/GameEngine/Source/GameClient/Gen00595870DequePushBackAux.cpp` | `0x00594220` | 2 / 0 |
| 120 | `game/GameEngine/Source/GameLogic/System/BuildableStatusHashMap.cpp` | `0x003872F0`, `0x00390660`, `0x00C1C0F0` | 2 / 0 |

## Target, compiler and object evidence

Independent BFME 1 native header evidence establishes the four-byte narrow
string object, its StringBase<char> base at +0, and the original copy/release
call contracts. Per-unit native CodeView controls confirm size4 and no virtual
pointer. A size1 incomplete facade is allowed only when every original runtime
section and relocation is unchanged, so no size-dependent use is introduced.
Private controls share one physical compiler-input path and original logical
source context. A separate final comparison uses normal native build objects.

All 15 existing retained rows keep their 1,303 code bytes.
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
This batch has 25 additional retail-proven copies and
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

The final combined ordinary gate passes 189/189
functions across 17 sources, 342 DIR32 references
and the body guard, including the unchanged four canonical provider sources.
1 unique stale/wrong cleanup locators are updated only by
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

Before: 9/13 LINKS, 833 bytes.
After at the same frozen census: 9/13 LINKS, 833 bytes.
No previously linkable unit is lost. These are bounded previews, not a new
complete census or whole-image/runtime/crash-fix proof.
Staged current-provider preview: 13/13 UNKNOWN, 0/13 LINKS, 0/13 blocked. Unknown results authorize no LINKED claim.

The complete census43711614660 at7c314a3e6c confirms the preceding +450B,
but predates this round's header adoptions. Its total is3,088,824 LINKED B;
the full-file confirmation is recorded in 20261115-450-byte-census-confirmation.md.

| Cleanup RVA | Object label before -> proven after | Parent state evidence |
|---|---|---|
| `0x00C1C0F0` | `$L6704` -> `$L7239` | `??A?$hash_map@VAsciiString@@W4BuildableStatus@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@_STL@@@_STL@@QAEAAW4BuildableStatus@@ABVAsciiString@@@Z` states `[0]` |

## Standalone facade to native hierarchy

The removed AsciiString facade has no base. Native CodeView must show either
one4B pointer field at +0 and sizeof4, or an empty incomplete size1 facade.
The canonical class has StringBase<char> at +0 and sizeof4, as independently
established by the settled native headers and verified retail providers.
An incomplete facade additionally requires exact complete runtime inventory
identity. For every source, the original ordinary runtime graph and retained
rows still agree: no copy/refcount, return convention, hidden parameter or
exception-cleanup code change is admitted. Companion Unicode layouts remain
exact. Thus this is an evidence-backed type adoption, not an assertion that
the removed facade already described the canonical inheritance.

The native pre-commit gate detected a pre-existing stale absent-from-retail marker on the already matched Rva14B630StringRecord copy constructor. Only that contradictory marker was removed, preserving source line count and all executable code. The combined native gate was rerun. This is not an additional task.
