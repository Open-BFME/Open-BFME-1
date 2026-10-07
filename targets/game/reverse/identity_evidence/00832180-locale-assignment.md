# locale assignment at 0x00832180

The 39-byte body at 0x00832180 was filed under the address-derived name
`?set@Rva00832180@@QAEAAV1@PBQAURva00832180Unk@@@Z`. It is STLport 4.5.3's
`const locale& locale::operator=(const locale&)` (src/locale_impl.cpp).

- Shape: thiscall `ret 4`. If `this->_M_impl != L._M_impl`, it calls the old
  implementation's third virtual slot (reference decrement), reloads the
  source's implementation, calls its second slot (reference increment), stores
  it, and returns `this`. The sibling copy constructor 0x00832150 (identity
  evidence 00832150-locale-copy-constructor) uses the same second slot as the
  increment; the classic-locale builder (stlport_classic_locale_impl.cpp)
  models slots 1/2 as the implementation's incr/decr.
- Its callers (`tools/callers_of.py 0x832180`) are exactly the STLport bodies
  that replace a stored locale: both `basic_streambuf::pubimbue` (0x0083EAD0,
  0x0083FC10), `ios_base::imbue` (0x0083EC50) and `ios_base::_M_copy_state`
  (0x0083F3F0).
- symbols.csv already pins `??4locale@_STL@@QAEABV01@ABV01@@Z` to 0x00832180
  (read from the retail pubimbue REL32), and stlport_char_streambuf_pubimbue.cpp
  and stlport_ios_base_imbue.cpp reference that name, which nothing defined
  (link census: unresolved, queue row #129).

The native source in game/Libraries/Source/STLport/LocaleAssignment.cpp
reproduces all 39 bytes.
