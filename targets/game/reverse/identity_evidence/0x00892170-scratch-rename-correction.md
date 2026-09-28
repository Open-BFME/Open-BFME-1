# 0x00892170 bank-to-source pairing

The name regression checker paired the deleted experiment
`targets/game/reverse/attempts/0x00892170.cpp` with the new source
`game/Libraries/Source/Apt/Apt.cpp` and interpreted `bfmeGo1017X` becoming
`Rva00892170Store` as a rename. The experiment file contains two separate
functions, `bfmeGo1017X` and `bfmeGo1017Y`; these are not the body recovered at
0x00892170.

The functions ledger independently keeps `bfmeGo1017X` at 0x00892080 (53
bytes) and `bfmeGo1017Y` at 0x008920C0 (49 bytes), both in
`game/GameEngine/Source/Common/BfmeConv1017.cpp`. Their original names and rows
remain unchanged. The new 34-byte body at 0x00892170 has an address-derived
name because its original name is unproved. Retail disassembly shows four
global stores and `ret` at offset 0x21; `add_match.py` verified those bytes in
`Apt.cpp`.

The correction is limited to the exact old and new source snapshots recorded in
`name_corrections.json`. It records a false path pairing, not a change to either
function's identity.
