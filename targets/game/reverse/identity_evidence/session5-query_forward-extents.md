# Include the complete query-forwarder RET4

The 43-byte claim at008BD460 contains only the opcode byte of RET4
at008BD48A. The instruction ends008BD48D and INT3 padding follows;
next code starts008BD490. Local retail PE and Ghidra memory at00CBD460
agree, establishing45B. The body calls008BD0F0 and008BD400, restores
ESI and ECX, then returns through that same RET4. No live claim overlaps.

The unchanged BfmeQueryForward1279.cpp native COFF emission matches all
45B with its ordinary relocation verification. Preserve the inherited
BfmeWrapper1279/bfmeForwardValue1279 spelling without claiming a new
semantic identity; byte equality alone does not establish those names.
AGENTS.md requires the complete byte-verified body. No source/header/pin
changes and no padding are included in this extent correction.
