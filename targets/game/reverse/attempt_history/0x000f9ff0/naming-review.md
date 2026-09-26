# 000F9FF0: remove an unsupported library identity

The old bank defined its own `_STL::pair` and assigned the record the type
`pair<const Rva000F9FF0Key, Gen_000F9C60>`. Its 0x44-byte key/0x1C-byte value
split was inferred from two member-constructor calls. Neither those calls nor
the member layout establishes a key, value, `first`, `second`, or standard
library pair. This is an identity correction, not a claim that an exact byte
match licenses renaming an established function.

Independent caller evidence establishes a 96-byte record:

- `Code/GameEngine/Source/Common/Rva000FAA30VectorCopy.cpp` copies 96-byte
  vector elements through ILT0004845F to body000F9FF0. It does not identify a pair.
- `reverse/attempts/0x000fb2e0.cpp` uses the same record layout without an
  independently recovered semantic owner.
- Retail000F9FF0 calls StringBase<char>'s copy at00887B60 for offset0, copies
  four words at4..10, separately copies a24-byte POD subobject at14, copies
  fields at2C..40, and invokes the already-matched Gen_000F9C60 copy via
  ILT0003ED92 for offset44. The latter type occupies1C bytes.
- The older `Code/gen_small/tgrid_103.cpp` / `reverse/reloc_names.csv` pair
  candidate uses synthetic four-byte-key/twelve-byte-value types. That16-byte
  scaffold contradicts this96-byte physical record and is not naming evidence.
- The Player_addRadar_Thunk consumer supplies no additional C++ pair identity.

An independent CLI review on2026-09-22 checked these consumers and concluded
that pair semantics and the owning class remain unproven. The replacement
therefore uses Rva000F9FF0, keeps the bank's m_name/m_fXX structural labels,
and retains the independently matched Gen_000F9C60 member identity. It does
not assert a MapMetaData identity based on the fuzzy Zero Hour twin.

The new constructor is181/181 bytes exact with both callee bindings checked.
The six-word subobject uses its ordinary implicit POD copy; no volatile fields,
forced stores, or generated pair wrapper are needed. The correction entry is
bound to the exact before/after snapshots. No detector or baseline changes.
