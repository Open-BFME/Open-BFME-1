# Include the vector overflow return at 007761E8

The 280-byte claim at RVA 007760D0 ends after ADD ESP,8 at 007761E5. RET14h at 007761E8..007761EA is reached by fall-through; INT3 padding begins at 007761EB. All decoded conditional and loop targets remain inside the complete 283-byte body, and no other live claim intersects it. PE/Capstone decoding and Ghidra read_memory at VA 00B761C0 independently agree.

The unchanged C++ vector instantiation in Rva00253630VectorInsertOverflow.cpp already emits the whole function with its existing call bindings. Keep its address-qualified 44-byte element model. This extent correction adds the return without claiming padding or changing names, source or pins.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
