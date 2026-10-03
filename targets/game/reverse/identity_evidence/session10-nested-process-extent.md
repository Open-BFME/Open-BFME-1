# Include the nested processing return in its extent

The old 294-byte claim at RVA 0024C2A0 ends after ADD ESP,14h at 0024C3C3..0024C3C5. RET 8 at 0024C3C6..0024C3C8 is omitted; INT3 begins 0024C3C9. This proves the complete 297-byte body. Early JE branches at 0024C2C8 and 0024C2D8 reach the saved-register/FS epilogue, also reached after the final node-deallocation call at 0024C3AF. All ten direct branches target instruction starts within the complete decoded stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA0064C3A0 agree.

The existing native Rva0024C2A0ProcessNested.cpp emits the full return. Extend only the ledger extent and verify all scoped claims and complete references; preserve source, pins and the inherited address-qualified identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
