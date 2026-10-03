# Complete the banner timer destructor exception epilogue

The 210-byte claim at RVA 00583DD0 ends inside MOV FS:[0],ECX at 00583E9E..00583EA4. The deallocation arm and conditional branch at 00583E4E reach the shared epilogue 00583E97. Retail then completes the FS restore, adds 14h to ESP and returns at 00583EA8. INT3 padding starts at 00583EA9, establishing 217 executable bytes; the earlier return belongs to another deallocation arm. All decoded branch targets are inside this body, with no other matched overlap. Local PE/Capstone and Ghidra memory at VA 00983E80 independently witness the tail.

The unchanged BannerUI.cpp native source already includes this epilogue. Verify its full emission and all sibling claims and references; no source, pins or inherited identity is changed.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
