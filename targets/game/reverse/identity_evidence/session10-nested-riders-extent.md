# Verify the complete nested rider cleanup tail

The old 322-byte claim at RVA 0024C940 cuts ADD ESP,18h at 0024CA81..0024CA83 after its first byte. RET at 0024CA84 is followed by INT3 padding at 0024CA85, establishing 325 executable bytes. The final node deallocation call at 0024CA6B returns into the saved-register/FS epilogue before this terminal cleanup. All 13 direct branches target instruction starts in the full decoded stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA0064CA60 agree.

The existing native Rva0024C940ProcessNestedRiders.cpp emits the full tail. Extend only the ledger extent and verify all scoped claims and complete references. Source, pins and the inherited address-qualified identity remain unchanged.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
