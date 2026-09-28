# hashtable<pair<const AsciiString, UnicodeString>>::resize at 0x006A7B60

The 418-byte body was claimed as
`hashtable<GameSpyGroupRoom, AsciiString, rts::hash<AsciiString>,
Rva006A7B60ExtractKey, equal_to<AsciiString>>::resize`. That modelled value
type came from the StringBase<char> copy at 0x00887B60. The copy is really
only the AsciiString key that rts::hash<AsciiString> takes by value. Resize
never copies a value.

Evidence for the true instantiation:

- **Node copy.** The insert_unique_noresize at 0x006AB4A0 builds nodes through
  ILT 0x00035B0C, then 0x006A15D0 (_Construct), then ILT 0x0001183D, reaching
  the out-of-line pair copy constructor at 0x0069EF10. That copy constructor
  copy-constructs StringBase<char> at +0 (0x00887B60) and StringBase<G> at +4
  (0x00888400), so the stored value is pair<const AsciiString, UnicodeString>.
- **Caller.** 0x006AF840 (the MilesAudioManager subtitle-queue drain) builds
  exactly that pair and inserts it into the hash_map at manager+0x96C. The
  insert is the STLport hash_map::insert: resize(num_elements + 1) through
  ILT 0x0001547E, which reaches this body, followed by insert_unique_noresize.
  A clean C++ build of that caller on a real
  `_STL::hash_map<AsciiString, UnicodeString, rts::hash<AsciiString>,
  rts::equal_to<AsciiString> >` is exact at 973/973 bytes outside relocation
  slots, and it references this resize under the replacement name.
- **Re-typed build.** The same explicit STLport instantiation, re-typed to
  that value, compiles to this body exactly: probe reports 418/418 bytes,
  exact outside relocations.

The byte range is unchanged. The two generated hash_map<int, p12cd> pins that
also name this address are left for their own cleanup.
