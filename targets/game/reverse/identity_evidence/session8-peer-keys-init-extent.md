# Include both Peer key initialization return paths

The 229-byte piKeysInit claim at RVA 008655C0 cuts MOV EAX,1 at 008656A1..008656A5. Retail restores ESI and returns at 008656A7, then has the failure arm POP EDI; XOR EAX,EAX; POP ESI; RET at 008656A8..008656AC. Four conditional branches inside the initializer target that omitted failure arm. INT3 starts at 008656AD and the next function begins at 008656B0, proving the complete 237-byte body. All initializer branches remain in this extent and no matched row overlaps it. Local PE/Capstone and Ghidra read_memory at VA 00C65680 agree.

The unchanged GameSpy Peer C source already emits both complete exits. Verify the entire translation unit and existing references, retaining its current upstream identity, source provenance and call bindings.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
