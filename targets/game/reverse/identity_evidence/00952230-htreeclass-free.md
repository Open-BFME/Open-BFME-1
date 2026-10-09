# 0x00952230 is HTreeClass::Free

## Caller proof

`HTreeClass::Load_W3D` (matched row, RVA 0x00955700, 375 B) calls 0x00952230
once on its hierarchy-load failure path (`python3 tools/callees.py 0x955700 375`).
Upstream `htree.cpp` Load_W3D calls `Free()` at exactly that point
(inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.cpp).
`symbols.csv` already pins `?Free@HTreeClass@@AAEXXZ` at 0x00952230.

## Not the destructor

The destructor `??1HTreeClass@@QAE@XZ` has its own matched body at 0x00952790
(42 B). Retail was linked without identical-COMDAT folding, so the same-shape
42-byte body at 0x00952230 is a separate identity; the old row only aliased it
to the destructor's object symbol (`gen-alias;object-symbol=??1HTreeClass@@QAE@XZ`).

## Placement

0x00952230 sits between the ctor (0x00952210) and Get_Bone_Index (0x00952260),
the upstream htree.cpp order (ctor, Free, Get_Bone_Index ...).
