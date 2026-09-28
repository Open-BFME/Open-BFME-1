# 0x006141F0: hash_map<int, BfmeItemAM *>::operator[]

The 99-byte STLport `hash_map<int, T>::operator[]` at `0x006141F0` was claimed
under a synthetic mapped type,
`??A?$hash_map@HW4Gen_e_006141f0@@...`. The row's own note and source comment
state that the enum `Gen_e_006141f0` exists only to give the instantiation a
distinct decoration. The row is corrected to the real instantiation:
`??A?$hash_map@HPAVBfmeItemAM@@U?$hash@H@_STL@@U?$equal_to@H@3@V?$allocator@U?$pair@$$CBHPAVBfmeItemAM@@@_STL@@@3@@_STL@@QAEAAPAVBfmeItemAM@@ABH@Z`.

## Evidence

1. **The caller that uses it.** `BfmeSinkAM::registerItem` (0x006176A0,
   landed in the same commit) calls ILT `0x000033BE` -> `0x006141F0` with
   `ecx = this + 0x210` and `&handle`. It then stores the newly built 0xA0-byte
   item pointer through the returned reference (`mov [eax], esi`). Just before
   that, the same body walks the same table inline as a `hash_map<int, T>` find
   (bucket vector at +0x214/+0x218, node key at +4).
2. **The map's type is already established.** The landed
   `BfmeSinkAM::bfmeDrop` (0x00617A10, BfmeSinkAMDrop.cpp) models the +0x210
   member as `_STL::hash_map<int, BfmeItemAM *>`. It links that table's erase
   through the pinned
   `?erase@?$hashtable@U?$pair@$$CBHPAVBfmeItemAM@@@_STL@@...`. Retail was
   linked without identical-COMDAT folding, so the operator[] called on that
   member is that one instantiation's operator[].
3. **The bytes are unchanged.** An explicit member instantiation of
   `hash_map<int, BfmeItemAM *>::operator[]` byte-matches retail 0x006141F0
   (99 B, exact modulo relocations).

## The insertion callee

The operator[] calls `_M_insert` through ILT `0x000065E6` -> `0x00613250`.
That ILT's existing pin used the same synthetic `Gen_e_006141f0` payload. It is
renamed in place to the `pair<const int, BfmeItemAM *>` spelling: same address,
and no name is added.

The body at 0x00613250 is matched under another synthetic payload
(`Open2Mapped613250`). Because there is no ICF, it must be this same
instantiation's `_M_insert`. That row is left for a separate correction.
