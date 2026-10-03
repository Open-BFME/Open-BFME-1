# Include the vector overflow return at 0024037F

The 335-byte claim at RVA 00240230 ends after ADD ESP,8 at 0024037C. Its fall-through RET14h occupies 0024037F..00240381, followed by INT3 padding at 00240382. Thus the complete body is 338 bytes; all decoded conditional/loop targets remain within that extent. Local PE/Capstone and Ghidra read_memory at VA 00640360 agree, and no other live claim intersects the full interval.

The unchanged native STLport vector instantiation in Rva00240230VectorInsertOverflow.cpp emits the complete 338-byte body with existing relocation bindings. Preserve the address-qualified 28-byte element model: the source explicitly leaves its payload identity unrecovered. This adds the actual return only, without changing source, pins, names or claiming padding.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
