# 0x00261750 / 0x00261CC0: distance-record vector and its builder

BFME 1 retail 1.03 facts:

- 0x00261CC0 (298 B, two `ret 0Ch` exits) is reached only through ILT
  0x0002A036 from the matched caller `Rva00261F40Owner::selectAt00261E40`
  (0x00261E40), which passes the context collection, the subject and a
  local result vector. It reads subject X/Y at +0x38/+0x3C, pushes
  {float squared XY distance, &entry->destination} records and sorts them
  with the matched comparator 0x00260650 (push imm at +0xBF/+0xD7/+0xF7).
- Its push_back overflow calls ILT 0x00024537 -> 0x00261750 (305 B). The
  only other REL32 caller of that ILT is 0x00261A02 (inside 0x002619D0).
  Retail was linked without identical-COMDAT folding, so 0x00261750 is the
  `vector<record>::_M_insert_overflow` instantiation for this 8-byte POD
  record (block copies, no element copy-constructor calls). The OCL
  Upgrades instantiation is a separate body at 0x00262FE0; the old
  `?dup_00261750` row merely aliased its byte-equal object symbol.
- Sort helpers: ILT 0x00038BF4 -> 0x00261AE0 (introsort loop), ILT
  0x000391E9 -> 0x00260910 (unguarded linear insert), ILT 0x00044A03 ->
  0x002618D0 (insertion sort, two sites).

Reconstruction (game/GameEngine/Source/GameLogic/Object/SpecialPower/
Rva00261CC0BuildPairs.cpp) compiles both bodies byte-exact (modulo
relocations). Shape levers that turned the 0.15 bank / 0.930 diagnostic
exact: subject position read through an inline `getPosition()` pointer
(gives retail's `add eax,38h` and input-in-EBX/output-in-EDI allocation),
Vector3 temporaries (32-byte ESP frame, Z stores dead), POD record instead
of `_STL::pair` (pair adds copy-ctor machinery and an aligned frame).

Record, owner and subject names stay address-derived: the original types
are unproven. The comparator keeps its matched pair-typed name; the
builder passes it through a function-pointer cast (same leading float key).

Follow-up lead: the three sort helpers compile byte-exact in this TU under
their STLport template names, but their ledger rows still carry placeholder
names in other units (`Gen00261AE0`, `GenInsert00260910`,
`rva002618D0ForEach`), so this unit pins its template names at the ILTs
without `route=`; re-homing those rows is a separate multi-consumer change.
