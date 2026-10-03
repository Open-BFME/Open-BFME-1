# Verify the complete statistics filename epilogue

The old 368-byte claim at RVA 000A29E0 cuts the two-byte MOV ESP,EBP at 000A2B4F..000A2B50 after its first byte. Retail then executes POP EBP at 000A2B51 and RET at 000A2B52; INT3 starts at 000A2B53. The complete body is 371 bytes. The final string cleanup call at 000A2B39 falls through the saved-register and FS restoration to that epilogue. All 12 direct branches target instruction starts inside the full decoded stream; no matched row overlaps it. Local PE/Capstone and Ghidra read_memory VA004A2B30 agree.

The existing native StatsCollector_createFileName.cpp emits the full body. Extend only the numeric ledger extent, reverify all scoped claims and complete references, and preserve its source, pins and inherited identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
