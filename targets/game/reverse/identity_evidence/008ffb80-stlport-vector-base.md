# 0x008FFB80 / 0x008FFA50: `_Vector_base` was not renamed

The name-regression check paired the deleted bank
`targets/game/reverse/attempts/0x008ffb80.cpp` with
`game/Libraries/Source/STLport/Rva00900FF0VecOfVecCount.cpp` and reported
`_Vector_base -> Rva008FFB80StringBase`. That pairing is a false positive.

- The old bank declared a TU-local stand-in `namespace _STL { template <class T, class Alloc> class _Vector_base {...}; }`
  so it could compile without STLport headers.
- Both new sources (`Rva00900FF0VecOfVecCopy.cpp`, the 0x008FFB80 body, and
  `Rva00900FF0VecOfVecCount.cpp`, the 0x008FFA50 body) `#include <vector>` and
  derive `Rva00900FF0VecOfVec` from the REAL STLport
  `_STL::_Vector_base<..., _STL::allocator<...> >`. The name `_Vector_base` is
  kept; only the redeclared stand-in is gone.
- `Rva008FFB80StringBase` is a new address-token struct in the count-ctor TU
  for the 12-byte narrow-string element buffer (`{start, finish,
  endOfStorage}`); it replaces the old bank's field list on
  `Gen_t_008ff3e0_p12cd`, not `_Vector_base`. The copy-ctor TU uses the real
  `_STL::string` for the same element.

Both rows are byte-verified `matched` in `targets/game/reverse/functions.csv`
(`??0Rva00900FF0VecOfVec@@QAE@ABV0@@Z` at 0x008FFB80, `@@QAE@H@Z` at 0x008FFA50).
