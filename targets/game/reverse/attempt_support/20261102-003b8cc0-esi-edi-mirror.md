# 0x003B8CC0 (276 B) `Rva003B8CC0Owner::run` -- ESI/EDI mirror bank

Bank: `targets/game/reverse/attempts/0x003b8cc0.cpp` (s544, claude-opus-5-5),
276/276 B, 6 relocations, 30 non-relocation bytes, shape 0.991.

## Established from retail
- Boundary: RET at +0x113, INT3 after; 276 B.
- Caller: ILT 0x000281D7 is stored at 0x010ED7BC/0x010ED7D8/0x010ED7F4
  (stride 0x1C dispatch table, slot 0); no vtable owner or name.
- Calls: atEnd 0x00064880 (ILT 0x00030D23), Rva00064390 ctor (ILT 0x0001F7D0),
  tree lookup 0x00064BF0 via ILT 0x00026887 (same typed member-pointer route
  as matched 0x003BBE50), copyTo 0x000643F0 (ILT 0x00025531), reporter
  Rva007397E0 (ILT 0x0002C9DA), `_Rb_global<bool>::_M_increment`.
- Layout used: +0 vptr (slot 2 takes one int), +4 tree, +0x10 cursor,
  +0x14/+0x18 vector of 20-byte entries {int, Item* (slot 29 -> refcounted
  result: +4 count, slot 0 release), set<4-byte key>}.

## Residue
Whole-body register mirror: retail keeps `this` in EDI and the tree pointer,
the slot-29 result and the outer index temp in ESI; ours swaps them. Every
other instruction, the frame (0x2C), the late EBP/EBX pushes and the
strength-reduced loops already match.

## Inert (all still 30 bytes)
tree pointer/reference local; `self` alias; `__fastcall` free function taking
the owner; tree as a second base; direct member lookup instead of the union
member pointer; result/iterator/index hoisted; item local; float triple;
`register` result; const_iterator; reversed compares; inline/forceinline
report, unref, loop and post-early-return helpers; refcount handle object
(339 B, worse); shape_search (73 trials over two choice sets);
rotation_sweep 36 toggles + pairs; /G5 /G7 /Ob1 /EHsc /GF; /Os /Og- /Oy-
change the body.

Matched neighbour 0x003B8E20 (BfmeConv1108.cpp) shows the same
`this`-in-EDI idiom where the loop node is the heaviest web; a hypothesis
not yet tested is a source in which the slot-29 result or the node outweighs
`this` before CSE.
