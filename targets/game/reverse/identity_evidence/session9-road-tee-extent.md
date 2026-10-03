# Include the road tee insertion return in its matched extent

The 2625-byte claim at RVA 0070BC00 ends after ADD ESP,44h at 0070C63E..0070C640 and omits RET10h at 0070C641..0070C643. INT3 starts at 0070C644, proving a 2628-byte executable body. The saved-register restoration at 0070C63A..0070C63D feeds this return. Local retail PE/Capstone and Ghidra read_memory at VA00B0C630 independently agree on the omitted tail. No matched row overlaps the complete span.

The existing native W3DRoadBuffer.cpp implementation already emits the complete return. Verify the full body, sibling claims and complete references; preserve its inherited identity and all source/pin declarations.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
