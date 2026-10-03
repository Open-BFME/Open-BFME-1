# DataChunkInput complete return extent

The265B claim at001032A0 stops after MOV EAX,EDI at001033A7.
The branch at00103379 reaches00103393 for the contents-name return,
which still needs POP EDI/ESI/ECX and RET8 at001033AC. The earlier
RET8 at00103390 belongs only to the EOF/empty-string arm. INT3 begins
001033AF, proving the contiguous271B extent. Local full-entry PE decode
and Ghidra read_memory0050339F..005033B8 agree.

Unchanged DataChunk.cpp emits the complete271B native implementation.
Identity retains the literal GeneralsMD Common/System/DataChunk.cpp twin
of DataChunkInput::openDataChunk: allocate a chunk, read ID/version/size,
update parent byte counts, link the chunk and return the table's name or
an empty string at EOF. The existing constructor/getName/allocation calls
and implicit string return ABI remain unchanged; no new pins or names.
Verify the full native span and all claims/references of the existing TU.
