# locale copy constructor at 0x00832150

The 32-byte body at 0x00832150 was filed under the address-derived name
`??0Rva00832150@@QAE@PBQAURva00832150Unk@@@Z`. It is STLport 4.5.3's
`locale::locale(const locale&)` (src/locale.cpp).

- Shape: a `ret 4` thiscall constructor that stores 0 to `this->_M_impl`, loads
  the source object's first dword, calls that object's second virtual slot (the
  implementation's reference increment), stores it and returns `this`. That is
  `_M_impl(0)` followed by `_M_impl = _S_copy_impl(L._M_impl)`.
- Its callers (`tools/callers_of.py 0x832150`) are the STLport bodies that
  return a `locale` by value: `basic_ios<char>::imbue` (0x0053F690),
  `ios_base::imbue` (0x0083EC50), `basic_ios<wchar_t>::imbue` (0x0083F880),
  both `basic_streambuf::pubimbue` (0x0083EAD0, 0x0083FC10) and
  `basic_streambuf<wchar_t>::getloc` (0x0083FE90). Each copies a locale member
  into its hidden return slot, so the callee is the locale copy constructor.
- symbols.csv already pins `??0locale@_STL@@QAE@ABV01@@Z` to 0x00832150 (read
  from the pubimbue REL32), and the FXParticleSystem ostream bodies reference
  that name, which nothing defined (link_census: unresolved).

The row keeps its source file and bytes.
