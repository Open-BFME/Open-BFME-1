# 0x008961E0 `?helper@Gen_00896320@@QAEXPAX00@Z` (316 B), link queue #136

Range insert into the Gen_00896320 small vector (count +0, capacity +4,
data +8, one inline item +0x0C): `helper(&first, &last, &pos)`.
n = last - first; if n == 0 return.  If count + n < capacity: pos == end ->
Rva00895430Copy(first, last, end); else bfmeCopyBackVPD(pos, end,
&data[(pos - data) + n]) then Rva00895430Copy(*first, *last, *pos)
(reloaded through the argument pointers).  Each arm then builds a cleared
item (EH states 0 and 1, both cleanup ??1RefHandle008958D0 0x00784A70 on the
same slot), assigns it to data[count + n] via bfmeAssignVGO, stores count.
Otherwise newCap = (int)(capacity * 2.0f) (fild/fadd st,st/__ftol2), at
least count + n; rva00896100(newCap); recurse with &newPos.

Bank: `targets/game/reverse/attempts/0x008961e0.cpp` (shape 0.846, same
`const item; assign; __assume(p == 0)` sentinel as matched rva00896100).

Remaining mismatch: retail cross-jumps the two arms' sentinel tails (state
store precedes `jmp`, temps both in the `pos` argument home [esp+0x30]);
ours puts the second-arm temp in the `from` spill slot [esp+0x10], keeps the
state store sunk after `push`, and duplicates the tail plus epilogue
(351 vs 316 B).  Grow path likewise: retail's newPos uses the pos home,
ours the capacity spill [esp+0x14].

Ruled out (all 351 B or worse): reversed branch polarity, single shared temp
after the if/else (308 B, frame 0x10), pointer params instead of
references, no named capacity local, named from/to locals, local copy of
*pos for the compare, non-const temps, goto/if(0) arm layout, inline
finish() helper (with __assume the EH frame vanishes entirely, 236 B),
__assume before the assign, no __assume (dtor calls appear), one ?:
expression with both temps (conditional-destroy flags).
Next hypotheses: the original item type/dtor elision mechanism differs
(retail has EH states but no normal-path dtor call), or temp-slot packing
depends on a different param/local declaration set.

## 2026-10-31 (s506, later): visible bfmeAssignVGO -> shape 0.964

Making `BfmeRefVGO::bfmeAssignVGO` (retail 0x00892B90, BfmeConv1355.cpp)
visible in the TU as a `__declspec(noinline)` definition with its real body
fixes the whole fast path: both arms' sentinel temps land in the `pos` home,
the state stores stay before the cross-jumped tail, and +0x00..+0xE4 is
byte-exact (bank: attempts/0x008961e0.cpp, 314 vs 316 B, 54 non-reloc bytes,
all in the grow path). Visible stubs of the two copy callees did nothing.

Remaining: grow path only. Retail `mov edx,[pos]; mov ecx,[esi+8];
mov edi,[edx]; sub edi,ecx` (m_begin in a register) and `newWhere` stored in
the `pos` home ([esp+0x30]); ours `sub edi,[esi+8]` and `newWhere` in the dead
capacity spill [esp+0x14]. Inert: named old-begin local, block-scoped or
split-declared newWhere, `m_begin + index`, copying where/begin to locals;
the ?: capacity spelling and writing through `&pos` are worse.

Landing needs the assign body visible without a second strong definition:
move `Gen_00896320::helper` into BfmeConv1355.cpp (or another TU that owns
0x00892B90) rather than duplicating the definition.
