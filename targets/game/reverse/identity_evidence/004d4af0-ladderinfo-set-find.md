# 0x004D4AF0: set<const LadderInfo *>::_M_t.find (const)

Retail 0x004D4AF0 (71 bytes, `ret 8`) is an STLport `_Rb_tree::find` body
(pointer key compared unsigned at node+0x10, hidden iterator result). Its row
was `?dup_004d4af0@@YAXXZ`, a gen-alias home borrowing StateMachine.cpp's
State-map find COMDAT.

## Facts from BFME 1 retail

- Matched callers: `PopulateCustomLadderListBox` (0x004D5FCB, 0x004D6087),
  `PopulateCustomLadderComboBox` (0x004D6682) and
  `BfmeQuickMatchLadderPanel::populateLadderList` (0x00508F1D) reach it
  through ILT 0x0002BF35 while testing ladder membership in a
  `set<const LadderInfo *>` (Zero Hour LadderList/PopulateLadder sources).
- `tools/ilt_oracle.py check` CONFIRMS the decorated
  `_Rb_tree<const LadderInfo *, ..., _Identity, less, allocator>::find<const LadderInfo *>`
  const name at 0x004D4AF0 (p_false 4.6e-4, exact slot).
- Retail has no identical-COMDAT folding, so the address is that set's own
  find, not the State map's.

## Source

PopulateCustomLadderListBox.cpp already instantiates the Zero Hour
`std::set<const LadderInfo *>` and emits this COMDAT byte-identical to
0x004D4AF0.
