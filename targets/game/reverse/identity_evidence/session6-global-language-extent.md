# Complete the GlobalLanguage exit cleanup extent

The old 631-byte claim ends after POP EBX at RVA 00439CA6. Retail then executes ADD ESP,260h at 00439CA7 and RET at 00439CAD; INT3 padding starts 00439CAE. The complete extent is 638 bytes. Local PE/Capstone and Ghidra read_memory at VA 00839C90 agree through the return and following padding. The existing entry is an EH prologue at 00439A30, and no other live row intersects this full interval.

The unchanged GlobalLanguage_onGameEngineExit.cpp native COFF emission reproduces the complete 638-byte span with its original relocation bindings. Preserve the existing source, identity and pins; this is an omitted-epilogue correction, with no padding claimed.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
