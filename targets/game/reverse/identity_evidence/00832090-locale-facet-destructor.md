# locale::facet destructor at 0x00832090

The 7-byte body at 0x00832090 was filed under the address-derived name
`??1Rva00832090TailBase@@UAE@XZ`. It is STLport 4.5.3's
`locale::facet::~facet()` (src/locale_impl.cpp, an empty body).

- The body is `mov dword ptr [ecx], 0x0112E940 / ret`: a destructor that
  re-seats the vptr and returns. 0x0112E940 is `??_7facet@locale@_STL@@6B@`,
  the facet vftable retail RTTI names (symbols.csv, dir32_addresses.csv).
- Every matched STLport facet destructor calls it as its base destructor
  (`tools/callers_of.py 0x832090`): `??1?$ctype@G@_STL@@MAE@XZ` (0x00840900),
  both `codecvt` (0x00843D90, 0x00843E30), `collate<char>` (0x008441B0), both
  `numpunct` (0x008444E0, 0x008444F0), the four `moneypunct` (0x00847F30,
  0x00847FD0, 0x00848070, 0x00848110) and both `messages` (0x00848A30,
  0x00848B20). Each derives from `locale::facet` in STLport, and nothing else
  is common to all of them.
- symbols.csv already pins `??1facet@locale@_STL@@MAE@XZ` to 0x00832090, and
  those destructors' sources reference that name, which nothing defined
  (link_census: unresolved).

The row keeps its source and bytes; the address-derived base class is
replaced by STLport's own `locale::facet` declaration.
