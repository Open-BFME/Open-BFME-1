# RVA 0x001CB270: opaque named-bit transfer

The retail start is 0x001CB270. The save branch iterates through 0x130 bits,
tests each enabled bit, reads its name through the table at VA 0x012A6918, and
transfers an AsciiString. The load branch clears the bitset, transfers names,
looks up their bit index, and sets each bit or throws on an invalid name.
The CRC branch delegates to the bitset transfer. These instructions support
the algorithm and 304-bit cardinality, but do not establish the table's owner.
The source therefore retains the start address in Rva001CB270BitFlags.

Retail disassembly at 0x001CB440 shows the final throw setup and a five-byte
call at 0x001CB45B ending at 0x001CB460. Thus the instruction body is 496
bytes from its start. Retail 0x001CB460 is INT3, also emitted by MSVC after
the noreturn throw call. The source's verified 497-byte extent includes this
throw-site INT3, consistent with the matched 0x001CB730 sibling. Padding is
excluded from authored-byte progress. The old 496-byte scaffold stops before
that emitted byte; the range adjustment does not claim an additional code byte.

The clean C++ implementation follows the byte-matched sibling's virtual slots,
aligned version record, string lifetime and STLport bitset operations. The
scoped strict byte gate independently verifies its instructions and relocation
targets. No EA class identity is claimed from the FRONTCRUSHED string anchor.
