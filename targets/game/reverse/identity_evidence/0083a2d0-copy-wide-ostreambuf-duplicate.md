# Wide output-iterator copy at 0x0083A2D0

The retail body starts immediately after INT3, returns at +0x69, and
is followed by INT3. All 106 bytes equal the separate copy at
0x00835EF0. The caller bodies at 0x00846B10 and 0x00846C30 call
0x0083A2D0 directly. They pass seven cdecl stack slots, including the
hidden result pointer, the two-word output iterator and the dispatch
arguments. The body uses the iterator's buffer and success byte,
writes wide characters until the input range is exhausted, and copies
the result to the hidden result buffer.

The old `?dup_0083a2d0@@YAXXZ` ledger row named the same template
COMDAT as 0x00835EF0. The existing caller pin
`bfmeRva0083A2D0CopyWide` carries the verified native ABI and distinct
address. Define it in the same translation unit as the original
numeric-facet template instantiations. This keeps 0x00835EF0's ledger
row and adds no second template COMDAT emitter. The exact private
probe changes the object definition set by this one symbol and emits
no relocations in its 106-byte body.

The local precedent is the narrow copy at 0x008460D0 in BFME1 commit
`f5d9b4afd5`. The BFME2 reference at `2bac16a6`
(`Code/Libraries/Source/WWVegas/WWLib/stlport_wide_copy_integer_and_fill.cpp`)
was checked for a shared implementation. Its numeric formatting and
padding instantiation does not identify BFME1's separate copy address.
The BFME1 retail bytes and direct caller targets establish this binding.
