# 0x008D1F10 BfmeNode1220::rva008D1F10 (107 B) -- EXACT

Symbol: `?rva008D1F10@BfmeNode1220@@QAE_NI@Z`. Ledger row today:
`?d_008d1f10@@YAXXZ` (gen_asm d_008c4940.asm). Flags `/O2 /DNDEBUG /DWIN32
/D_WINDOWS /MD`, the same as the matched sibling 0x008D2070
(game/Libraries/Source/EA/Apt/BfmeNode1220_bfmeAllows.cpp).

Best candidate: build/wf/008d1f10/best.cpp. probe: `result EXACT` at 107/107.

## The residue and the fix
The bank (0.9813) kept 2 bytes for many sessions: retail
`mov edx,[edx*8+0x12d5d54]; lea eax,[edx*4+0x1338480]`, ours
`mov eax,[...]; lea eax,[eax*4+...]`. Every earlier trial changed the tail
(index locals, slot reuse, helpers, signedness, &values[], do/while, flags).
The cause was in the prologue: the bank declared the owner pointer as
`BfmeOwner1220 * volatile m_owner`, copied from the sibling, where it helps
that sibling's scheduling. Declare `m_owner` without volatile and write the
tail as a single expression,
`return (bool)bfmeTest1220( g_bfmeValues1220 + g_bfmeSlots1220[ slot ].m_index, 0 );`,
and the body is exact. The tail's register choice depends on the owner load's
volatile-ness, which no tail spelling could reach. This is a measured effect;
the cause is a hypothesis.

Measured grid (owner volatile / slots volatile / tail):
- vol / vol / named valueIndex: 2 (bank); inline: 4
- nonvol / nonvol / named valueIndex: 4 (lea edx; push edx)
- nonvol / vol or nonvol / inline expression: EXACT
- nonvol / any / inline GetString(id) returning EAStringC* (BFME 2 idiom): EXACT
- nonvol / any / named `int id` or slot reuse: 4
- `mask == table[j].m_flags` operand order: 1 byte off at +0x31 (operands swapped)
- first-loop spellings (count local, owner local, braces): inert

## Other hypotheses tested here
- EAStringC element type for 0x01338480 (Rva00C6DC90ArrayInit.cpp) with
  owner volatile: 2 (inert)
- result local / bool local / ternary / if-return: 4 to 14
- pointer local for &values[i]: 6

## Coexistence with the sibling
Both bodies in one TU cannot match yet. With the bfmeAllows TU and a
non-volatile owner, rva008D1F10 is EXACT but bfmeAllows1220 has 9 diffs.
With the volatile owner, bfmeAllows is EXACT but this body has 4 diffs.
Land this body in its own TU, or first rework the sibling to drop its
volatile owner.

## Landing notes (read-only checks)
(a) `tools/ilt_oracle.py check`: UNTESTABLE (not a thunk target). No ILT pin
    is needed.
(b) No out-of-line helper copies are emitted. `BfmeOwner1220::bfmeList1220`
    is an inline accessor with no ledger row, and it inlines. The callee
    `?bfmeTest1220@BfmeNode1220@@QAEHPAHH@Z` (0x0089C290) is matched in
    game/GameEngine/Source/Common/BfmeSlotTaggedReplace.cpp. It is declared
    only, not defined, here.
(c) Object relocs: +0x34 and +0x4E `?g_bfmeSlots1220@@3RCUBfmeSlot1220@@C`
    (data_rows.csv 0x012D5D50, matched, plus dir32_addresses.csv), +0x57
    `_bfmeObjDAE` (dir32_addresses.csv 0x01338480), and +0x5D DISP32 to
    bfmeTest1220. The slot table must stay declared `volatile`, because the
    recorded definition is volatile-qualified (`RC...C` mangling). A
    non-volatile extern would be an undefined name at link time.
(d) Suggested TU: a new game/Libraries/Source/EA/Apt/BfmeNode1220_rva008D1F10.cpp
    next to BfmeNode1220_bfmeAllows.cpp. That sibling's volatile owner breaks
    this body (see above).
