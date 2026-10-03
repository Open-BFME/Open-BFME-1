# Include the vector overflow return at 0077BB48

The 280-byte claim at RVA 0077BA30 stops after ADD ESP,8 at 0077BB45. Fall-through reaches RET14h at 0077BB48..0077BB4A; INT3 padding begins at 0077BB4B. All decoded conditional and loop destinations are inside the complete 283-byte extent. No other matched claim intersects it. PE/Capstone decoding and Ghidra read_memory at VA 00B7BB20 agree on the return and padding boundary.

The unchanged C++ vector instantiation in Rva00253630VectorInsertOverflow.cpp emits the complete body using its existing call bindings. Its inherited 108-byte element model stays address-qualified. Only the omitted executable return is added; source, pins, names and padding coverage stay unchanged.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
