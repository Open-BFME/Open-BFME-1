# Include both insertion-sort register restores and returns

Both 75-byte claims end at POP ESI (0053176A and 0057429A), omitting
POP EBP, POP EBX and RET at 0053176D / 0057429D. INT3 padding starts
0053176E / 0057429E, so the complete extents are exactly 78 bytes.
The full local retail decodes and Ghidra memory at 00931760 / 00974290
agree on the shared ending. There are no intervening ledger claims.

The unchanged S4StlSortHelpers.cpp instantiates STLport insertion sort
from the existing vendor header; its original COFF bodies match all
78 bytes after the normal relocation verification. This is not an
archive-masked comparison. The source explicitly preserves uncertainty
about semantic element/comparator identity; retain those inherited
address-bearing spellings and do not promote a new owner or type name.
AGENTS.md requires a complete byte-verified claim; the old prefix omitted
the return from the claimed body. No source, header or pin changes.
