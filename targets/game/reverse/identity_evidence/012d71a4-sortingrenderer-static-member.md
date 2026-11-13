# 0x012D71A4 — SortingRendererClass::_EnableTriangleDraw static member name

The private static bool `SortingRendererClass::_EnableTriangleDraw` (declared in
`game/Libraries/Source/WWVegas/WW3D2/sortingrenderer.h:34`, defined in
`sortingrenderer.cpp:152`) is the retail datum at VA 0x012D71A4. Its mangled name
`?_EnableTriangleDraw@SortingRendererClass@@0_NA` carried no address, so the dir32
consistency check reported "nothing in the ledger owns 0x012D71A4" and the finding
sat in `body_guard_baseline.csv`.

No dir32_addresses.csv row or data_rows.csv row owns 0x012D71A4 under any other
name, and the member is private (`@@0`), which `tools/add_data_match.py`'s probe
grammar does not admit, so a data row cannot back the descriptive spelling. The
established convention for WW3D static members is the address-derived
`?Rva<VA>@Class@@0_NA` (197 rows in dir32_addresses.csv, e.g.
`?Rva012D6D84@WW3D@@0_NA`), which passes the encoded-address rule because the
name spells the base retail reads.

Correction: rename the member to `Rva012D71A4` in the header declaration, the two
inline accessors, the out-of-line definition, and the one use at
`sortingrenderer.cpp:808`. The emitted DIR32 operand is unchanged (the byte gate
masks it), so all 41 rows of sortingrenderer.cpp still byte-match; the rename only
makes the dir32 check's encoded-address rule see 0x012D71A4 == base.

Verified: scoped `./build.sh game/Libraries/Source/WWVegas/WW3D2/sortingrenderer.cpp`
with the baseline line deleted — Functions OK 41/41, DIR32 addresses OK (330
references), body guard OK (0 baselined findings).
