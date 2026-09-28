# MilesAudioManager subtitle-queue drain at 0x006AF840

The 973-byte body was retained as the anonymous MASM placeholder
`?d_006af840@@YAXXZ` after its old doSpeechPlay/executeAction attribution was
disproved. This change gives it an address-derived member name,
`MilesAudioManager::rva006AF840`, and a clean C++ body. It does not claim the
semantic method name.

Owner evidence:

- Both retail callers, 0x006B4590 and the manager update at 0x006B9C90, load
  the manager into ECX right before calling ILT 0x00017F85, which jumps to
  0x006AF840.
- The body waits on and releases the handle at this+0x95C. That is the
  manager mutex the matched MilesAudioManagerConstructor.cpp stores there,
  and sibling methods (MilesAudioManagerRva006A8DC0.cpp,
  MilesAudioManagerIsCurrentlyPlaying.cpp) take the same scoped lock.
- The members it touches match that constructor's layout: the hash_map at
  +0x96C and the two vectors at +0x980 and +0x98C.
- The body builds the literal "DIALOGEVENT:" + file base name + "SubTitle",
  looks it up through TheGameText->fetch(AsciiString, Bool*), and inserts
  pair<AsciiString, UnicodeString> into the +0x96C map. The map's insert is
  the STLport hash_map one: resize to num_elements + 1, then
  insert_unique_noresize.

Its two hashtable callees now carry the corrected
hash_map<AsciiString, UnicodeString> names: resize at 0x006A7B60 and
insert_unique_noresize at 0x006AB4A0. Both were proven by the node pair copy
at 0x0069EF10, see 006a7b60-hashtable-ascii-unicode-resize.md and
006ab4a0-hashtable-ascii-unicode-insert.md.

Byte evidence: probe reports 973/973 bytes, exact outside relocation slots.
Two source changes closed it: a null-first TheGameText conditional, and a
real STLport hash_map<AsciiString, UnicodeString, rts::hash, rts::equal_to>
at +0x96C.
