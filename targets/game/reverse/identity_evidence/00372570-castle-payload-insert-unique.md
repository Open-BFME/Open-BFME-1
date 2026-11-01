# 0x00372570: map<int, Rva0036DEF0Payload> insert_unique, not the opaque Value instantiation

BFME 1 target evidence (retail 1.03 unpacked):

- 0x00372570 (145 B) was rowed as
  `insert_unique@_Rb_tree<int, pair<const int, Rva00372570Value>>`
  (RvaTreeInsertUniqueSigned.cpp). That TU's own header documents that
  these 145 bytes touch only the int key and hand misses to _M_insert,
  so the bytes cannot distinguish mapped types: identity is not
  recoverable from the body alone.
- The body is reached through ILT 0x00033D16 (`e9 55e83300`).
  Two retail callers use exactly that slot: the matched INI parser
  0x00374CF0 (CastleBehaviorParseCastleToUnpackForFaction.cpp) and the
  22-byte gen-shim 0x00374AE0 (unknown type, asserts nothing).
- The matched caller names the symbol: 0x00374CF0 builds
  `Rva0036DEF0Payload { AsciiString m_text; uint m_first, m_second }`
  (12 B, member accesses proven by its own 410 bytes) and inserts it
  into `map<int, Rva0036DEF0Payload>`. A matched caller naming the
  symbol is the strongest evidence.
- Width agrees independently: Rva00372570Value is a 12-byte opaque
  body sized from _M_insert's node allocation, the same 12 bytes the
  Payload occupies. The sibling make_pair pin (ILT 0x00045507 ->
  0x0036DEF0, "aggregate string payload copy") is Payload-consistent.
- Byte proof: with /D_STLP_USE_STATIC_LIB this TU's
  Payload insert_unique is 145 B with zero non-relocation differences
  to retail 0x00372570 (previously 146 B calling _M_decrement through
  __imp_; retail and the RvaTree copy call it statically). The 410-byte
  caller stays exact under the same flag.

Donor evidence (open-bfme-2 6584c197419be3fc15b423d5142c7de896336fc3):

- CastleBehavior.cpp:508 carries only the `CastleToUnpackForFaction`
  field-table entry. No equivalent parser, map, or donor body exists.
  Not applicable; identity rests on BFME 1 caller evidence alone.

Correction:

- Row 60397 is re-homed to the Payload insert_unique name with
  CastleBehaviorParseCastleToUnpackForFaction.cpp as provider via
  add_match --correct-identity. RvaTreeInsertUniqueSigned.cpp keeps
  emitting its Value-named copy (same bytes, different decorated name)
  for its own use; with no row left under the Value name that copy is
  address-less and harmless.
- The symbols.csv pin binds the Payload name at ILT 0x00033D16 with
  route=0x00372570 so references resolve to the call address retail
  encodes (admissible per pin_consistency rule (b): E9 stub whose
  target now rows this very symbol).
