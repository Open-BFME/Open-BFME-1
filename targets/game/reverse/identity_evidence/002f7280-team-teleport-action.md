# RVA 0x002F7280 implements action 502, TEAM_TELEPORT_TO_WAYPOINT

This proves the dispatch operation and ScriptActions receiver, not the original
BFME method spelling. The ledger's address-derived name is retained. Facts
were read from the unpacked retail executable with pefile/capstone and checked
against Ghidra's 152-byte function at VA 0x006F7280. Image base: 0x00400000.

## Native dispatch proof

`ScriptActions::executeAction` at RVA 0x00303BF0 loads the action type from
`[esi+4]` into EDX at 0x00303C12, checks it against 0x21E, and jumps through
`[edx*4+0x0070D6A0]` at 0x00303C24. Entry **502** of this retail table is
VA **0x0070CE41** (table entry VA 0x0070DE78).

That branch calls ILT RVA 0x0002BA9E at 0x0030CE5E or 0x0030CE81;
the ILT jumps to RVA 0x002F7280. Both branches pass ECX = EBP, the dispatcher
receiver saved from ECX at 0x00303C1C. The dispatcher is currently a certified
byte dump; its symbol is not a matched clean C++ caller witness. The action
index and transfers here are independent retail-byte facts, not its source's
callee names.

The branch loads the first parameter pointer from `[esi+0x0C]` and passes it
without adjustment (or passes zero for an absent parameter). It loads the
second parameter pointer from `[esi+0x10]`, **adds 0x10**, and passes that
adjusted pointer (including in the missing-parameter branch). Correspondingly,
the helper copies a string from argument 1 +0x10 and another from argument 2
without adjustment. The older symmetric AsciiString-reference declaration
is contradicted by the BFME caller and helper bytes.

## The retail action name

`TEAM_TELEPORT_TO_WAYPOINT\0` occurs at RVA 0x00CD1030 (VA 0x010D1030).
Its only dword reference is the push at RVA 0x0031DB84, in
`ScriptEngine::init`, RVA 0x003107F0, a matched clean C++ implementation.
That implementation assigns this exact string to `m_actionTemplates[502]`,
with a team parameter (3) and waypoint parameter (7), at
`game/GameEngine/Source/GameLogic/ScriptEngine/script_engine.cpp:4975`.
The retail push and corresponding AsciiString assignment target
`[esi+0xF34C]` at 0x0031DB89. This confirms the source's action-name assignment
against the image, rather than identifying an operation from adjacency.

## Helper behavior and limits

The helper looks up its team via global VA 0x012F076C, virtual slot +0x44,
and its waypoint via global VA 0x012EF4CC, virtual slot +0x7C. It walks the
team's object chain from +0x0C, passing waypoint+0x0C and zero to ILT
0x0001621B -> RVA 0x001D0520 for each member. It advances using the retail
inherited-vbptr/member-pointer sequence. The set-position route corroborates
the teleport operation, but its existing BfmeHostTP name is not original
BFME spelling evidence. The body ends in `ret 8` at 0x002F7315, with INT3
padding beginning at 0x002F7318.

There is no separate vtable slot or string establishing a method spelling.
The shared ObjectDlinkPmf model explains iteration; it does not justify
inventing a ScriptActions method or changing the canonical callee identity.
Earlier banks also miss the frame/member-pointer register shape. This pass
adds identity evidence only, with no source or ledger rename.
