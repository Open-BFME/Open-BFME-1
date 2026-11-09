# Narrow output-iterator assignment emitters

Census 88d830c8e9 marks `Rva00848510.cpp` (113 B) and
`Rva00846E80CopyWrappers.cpp` (284 B) as non-linking. Both emit an
out-of-line narrow iterator assignment that disagrees with the retail
52-byte body at 0x00835550. Commit `c2a501e9c` already gives the
retail copy an owner. Retail's 113-byte fill loop at 0x00848510 and
114-byte copy loop at 0x008460D0 inline the assignment.

A member extern-template declaration removes the conflicting definition
but makes these loops call the assignment, producing 53 and 56 bytes.
An imported force-inline specialization inlines the assignment but
calls `basic_streambuf<char>::sputc`, yielding 89 and 90 bytes. A class
extern-template declaration and a plain force-inline specialization keep
both retail loops but leave the competing definition in each object.
The member/class extern-template results also hold when the declaration
is placed after the callers. No source variant was retained.

A successful repair must keep the inlined stream-buffer write and
remove only the non-retail external copy. The BFME2 pinned provider
was checked and already underlies the existing BFME1 owner; it does
not address these two callers.
