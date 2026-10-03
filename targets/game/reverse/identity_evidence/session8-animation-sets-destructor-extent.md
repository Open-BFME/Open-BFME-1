# Complete the animation-set destructor exception epilogue

The old 210-byte claim at RVA 001D79C0 ends inside the seven-byte MOV FS:[0],ECX at 001D7A8E..001D7A94. The non-null deallocation path and branch at 001D7A3E reach the epilogue at 001D7A87; retail restores FS, adds 14h to ESP at 001D7A95 and returns at 001D7A98. INT3 padding begins at 001D7A99, proving the complete 217-byte body. The earlier return at 001D7A7C belongs to a different deallocation path; it is not the final extent. All decoded branch targets fall within the full body and no other matched claim overlaps. Local PE/Capstone and Ghidra read_memory at VA 005D7A70 independently agree.

The unchanged GenericObjectCreationNuggetAnimSetsDestructor.cpp native source already emits the omitted cleanup. Verify the complete span and sibling references without changing its source, inherited names or pins.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
