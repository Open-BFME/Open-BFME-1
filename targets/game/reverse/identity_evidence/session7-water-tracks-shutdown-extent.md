# Complete the water-track renderer shutdown extent

The 219-byte claim at RVA 007AC560 cuts the reached CALL [EDX] at 007AC63A..007AC63B. Retail then stores EBX through [ESI] at 007AC63C, restores EDI/ESI/EBX and returns at 007AC641. Conditional branches at 007AC631 and 007AC636 also reach the omitted tail. INT3 padding starts at 007AC642, establishing the complete 226-byte span. Every decoded branch target is inside this extent and no other live claim intersects it. Local PE/Capstone and Ghidra read_memory at VA 00BAC620 agree.

The unchanged W3DWaterTracks.cpp native shutdown implementation already includes the final vertex-buffer release and clear. Verify the full span and all sibling claims with existing reference bindings; source, pins and inherited names are unchanged. Only executable bytes are added to the claim, with no alignment padding.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
