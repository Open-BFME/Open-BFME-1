# Include the vector overflow return at 00253258

The 280-byte claim at RVA 00253140 ends after ADD ESP,8 at 00253255. RET14h at 00253258..0025325A is reached by fall-through; INT3 padding begins at 0025325B. All conditional and loop targets remain within the complete 283-byte extent, with no intersecting live claim. Local PE/Capstone and Ghidra read_memory at VA 00653230 agree.

The unchanged native C++ vector instantiation in Rva00253630VectorInsertOverflow.cpp already emits the complete body. Keep its inherited address-qualified element identity and existing call bindings. The correction claims the missing return, not padding; it changes neither source nor pins.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
