# Complete AI transfer return

Retail entry0014B8C0 branches at0014B8E7 to0014B9B1 for its non-CRC
transfer arm. That arm writes the version pair, transfers two IDs and
restores FS:[0]. The303B claim ends after ADD ESP,10 at0014B9EC,
omitting RET4 at0014B9EF. INT3 starts0014B9F2: complete extent306B.
The earlier RET4 at0014B9AE terminates only the CRC arm. Both entry-to-tail
control flow and local PE bytes prove the extra three bytes belong to
this body; Ghidra read_memory0054B9D0..0054B9F7 independently agrees.

Unchanged native AI_crc_Thunk.cpp emits all306 bytes exactly. Retain its
existing identity and layout: GeneralsMD AI.cpp AI::crc provides the
Pathfinder/TAiData/AIGroup traversal with both MARKER strings. BFME adds
the IsCRC dispatch and non-CRC transfer arm; byte verification covers
both paths. This extent-only repair assigns no new field, type, callback
or callee name and changes no source/pin. Scope verification includes
all existing emissions and their references, plus the full boundary.
