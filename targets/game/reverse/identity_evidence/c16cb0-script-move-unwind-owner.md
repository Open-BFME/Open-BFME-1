# Unit-move ownership and the C16CB0 unwind action

The retained native `ScriptActions::doMoveUnitTowardsNearest` method is at
RVA 0x00302D70 (314 bytes). Its existing dedicated source reproduces the
full body. The historical ScriptActions.cpp copy emits 871 bytes and was
selected ahead of that owner. Native executeAction calls at 0x0030A072
and 0x0030A095 route through 0x00009179 to 0x00302D70. The two named C++
call sites remain declared and resolve to the retained definition.

## Unwind owner

The 314-byte unit-move prologue names handler 0x00C16CD0, which loads
FuncInfo 0x00E06A84. The native four-state map at 0x00E06A64 has predecessors
-1, 0, 1, 2 and actions 0x00C16CB0, 0x00C16CB8, 0x00C16CC0, 0x00C16CC8.
State 0 destroys the incoming by-value string. RVA 0x00C16CB0 is exactly
8 bytes: `lea ecx,[ebp+0xC]; jmp 0x0000D828`. That thunk reaches the real
AsciiString destructor at 0x0005EE90. The next action starts at 0x00C16CB8.
The other actions use stack offsets -0x28, -0x34, -0x1C and destructor
routes 0x000EC7D0, 0x00149FE0, 0x002ED580.

In the authentic current unit-move object, parent section 29 references
its named handler at section 30, offset 32. The handler references FuncInfo
at section 31, offset 32. Its four-state map at section 31, offset 0 names
actions at section 30, offsets 0, 8, 16, 24. Both metadata sections are
associative COMDATs belonging to parent section 29. State 0 is `$L731`.
Its sole in-extent relocation at offset 4 names `AsciiString::~AsciiString`
and resolves all 8 bytes exactly to native. The local ordinal is a hint.
The parent, state map, stack offset, complete extent and destructor route
establish ownership. The old 871-byte parent's two-state map cannot replace
that proof.

Only C16CB0 among the 170 old ScriptActions rows belongs to the removed
parent's internal dependency graph. Its identity and 8-byte extent remain
unchanged. The supported same-identity row replacement moves its source to
the real parent. The other five funclets stay with their own parents. All
172 rows across ScriptActions and the two dedicated move-method sources
retain their native coverage.

## Deliberate boundary

The team-move definition is unchanged. Removing both wrong methods also
removed incidental polygon-filter and ObjectTypes providers. A complete
97-object comparison of that rejected experiment exposed an incompatible
AIGuard constructor copy and a competing getNthInList definition. The
polygon table changed from an incorrect allow-first view to an incomplete
destructor-first view, while the old array scanner still calls slot zero.
That requires a separate coherent ABI repair. The unchanged team method
naturally preserves the existing table and getNthInList providers, preventing
destructor-first selection against AIGuard's slot-zero scanner and the
competing getNthInList provider selection. No forced emitter is added.

This repair changes no vendor/header, AIGuard body, alias, pin or verifier.
It does not solve team-move or polygon-filter ABI debt, add native byte
coverage, or establish a transitive linked image.
