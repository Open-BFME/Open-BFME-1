# Include the SpecialPowerStore lookup return

The 298-byte claim at RVA 000EBA20 ends after ADD ESP,14h at 000EBB47. Its fall-through RET4 occupies 000EBB4A..000EBB4C, and INT3 padding starts 000EBB4D. The entry has an EH registration prologue; the terminal path restores the saved registers and FS registration before that omitted return. Thus the full contiguous body is 301 bytes. Local PE/Capstone and Ghidra read_memory at VA 004EBB30 agree, and no live row overlaps the interval.

The unchanged native SpecialPower.cpp emission matches all 301 bytes with its existing bindings. Retain the existing SpecialPowerStore::findSpecialPowerTemplatePrivate identity and adapted native lookup/source declarations. This is solely an omitted-return extent repair, not a source or ABI change.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
