# 0x0049A330 / 0x0049A260: STLport vector<int> integral range constructor

BFME 1 target evidence (retail 1.03 unpacked):

- 0x0049A260 (94 B, ret 0xC): `allocate(n*4)` with the 128-byte
  `__node_alloc` / `operator new` split, stores start and end-of-storage,
  `rep stos` fills n dwords with the by-value second argument, stores finish.
  That is STLport 4.6 `vector<_Tp>::_M_initialize_aux(_Integer n, _Integer
  val, const __true_type&)` (`stl/_vector.h`).
- 0x0049A330 (85 B, ret 0xC): EH frame, zeroes the three vector words, then
  calls ILT 0x00014100 (-> 0x0049A260) with (first, last, &last-slot): the
  `vector(_InputIterator, _InputIterator, const allocator_type&)` constructor
  dispatching on `_Is_integer<int>` with the dead argument slot as the
  `__true_type` temporary.
- `tools/ilt_oracle.py check`: the int/int spellings are CONFIRMED (exact) at
  ILT 0x00014100 and ILT 0x0004665A; every unsigned/long/unsigned-long mix of
  element and iterator type is CONTRADICTED for 0x0049A260.
- No direct callers of either ILT exist in retail .text (unreferenced COMDAT
  pair), so no caller TU is claimed.

Byte evidence: both bodies compile EXACT (relocations masked) from the vendored
STLport headers in `game/Libraries/Source/WWVegas/WWLib/VectorIntegerInsertOverflowThunk.cpp`
(`/EHsc`, `// stlport`) via explicit instantiation.

The previous `Gen_0049A330` view (Bfme5SehStarters.cpp) and its
`?bfmeStart@Gen_0049A330@@` pin at ILT 0x00014100 were placeholder names for
the same two bodies.
