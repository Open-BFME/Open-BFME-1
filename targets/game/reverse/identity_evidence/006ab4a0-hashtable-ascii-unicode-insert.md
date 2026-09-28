# hashtable<pair<const AsciiString, UnicodeString>>::insert_unique_noresize at 0x006AB4A0

The 270-byte body was claimed as the insert_unique_noresize of an
AsciiString -> AudioEventInfo* hashtable. Its own node construction refutes
that value type:

- **Node copy.** `_M_new_node` calls ILT 0x00035B0C. That reaches _Construct at
  0x006A15D0, which calls ILT 0x0001183D, reaching the out-of-line pair copy
  constructor at 0x0069EF10. That copy constructor copy-constructs
  StringBase<char> at +0 (0x00887B60) and then StringBase<G> at +4
  (0x00888400), so the stored value is pair<const AsciiString,
  UnicodeString>. An AudioEventInfo* value would be a plain dword copy.
- **Callers.** There are three, and all insert that pair:
  - The MilesAudioManager subtitle-queue drain at 0x006AF840. It builds
    pair<AsciiString, UnicodeString> and inserts it into the hash_map at
    manager+0x96C, with STLport's inline hash_map::insert: resize(num + 1),
    then this function.
  - Two out-of-line hash_map::insert copies at 0x006AC740 and 0x006AF510.
    Both call the sibling resize at 0x006A7B60 first. That resize was
    corrected to hashtable<pair<const AsciiString, UnicodeString>, ...> on
    the same evidence.
- **Re-typed build.** The existing byte-proven model TU, re-typed from
  AudioEventInfo* to UnicodeString, compiles to this body exactly: 270/270
  bytes, exact outside relocations.

The two ILT pins this body's model calls through, `_M_bkt_num_key` at
0x0004B308 and `_Construct` at 0x00035B0C, carried only the AudioEventInfo*
spelling for this body. They move to the same corrected instantiation. The
byte range is unchanged.
