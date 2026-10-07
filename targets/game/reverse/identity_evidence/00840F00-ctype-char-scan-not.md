# ctype<char>::scan_not at 0x00840F00

The 35-byte body at 0x00840F00 was filed as `?invoke@Open2381C0Impl@@QAEXHPAX0@Z`
(address-derived; its notes already called it the STLport ctype scan_not
helper). It is STLport 4.5.3's
`const char* ctype<char>::scan_not(mask, const char*, const char*) const`
(src/ctype.cpp: `find_if(low, high, not1(_Ctype_is_mask(m, table())))`).

- Shape: thiscall `ret 0Ch`; builds the {mask, this->_M_ctype_table (+0xC)}
  predicate, wraps it in unary_negate and calls the matched
  `__find_if<const char*, unary_negate<_Ctype_c_is_mask>>` instantiation
  (CtypeCharFindIfNot.cpp). The sibling scan_is at 0x00840ED0 (matched,
  CtypeCharFindIf.cpp) is the same 35 bytes without the negation.
- Callers (`tools/callers_of.py 0x840F00`): `_M_ignore_buffered<char,
  _Is_not_wspace, _Scan_for_not_wspace>` (0x00539BC0) and 0x005381C0, which
  loads a ctype pointer from its object and passes 8 (ctype_base::space) with
  the range: STLport's `_Scan_for_not_wspace::operator()`, which is
  `_M_ctype->scan_not(ctype_base::space, first, last)`.
- symbols.csv already pins `?scan_not@?$ctype@D@_STL@@QBEPBDW4mask@ctype_base@2@PBD1@Z`
  to 0x00840F00; Rva0053CA40NumericInput.cpp and stlport_basic_istream_get_char.cpp
  reference that name, which nothing defined (link census: unresolved, queue
  row #80).

game/Libraries/Source/STLport/CtypeCharScanNot.cpp reproduces all 35 bytes.
