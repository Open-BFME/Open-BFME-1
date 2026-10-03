# RVA 0x00C55D60: ofstream virtual-base cleanup

Matched constructor 0x0084BB90 pushes handler 0x00C55D95, which loads
FuncInfo 0x00E44F88. Its unwind state 0 -> -1 selects 0x00C55D60.
The existing native file-stream constructor source emits $L1106 for
compiler state 0 -> -1 and reproduces the 31-byte action.

Retail tests and clears mask 1 at EBP-0x14, loads saved this at
EBP-0x10, adds 0xB8 and jumps through ILT 0x000414BB to the existing
basic_ios<char> destructor at 0x00538210. Its false arm returns at
0x00C55D7E; the next independent action begins at 0x00C55D7F.
Ghidra confirms the conditional virtual-base cleanup but follows its
tail call into the destructor, so the raw instruction boundary and
unwind entries, not that expanded Ghidra extent, define these 31 bytes.

This is an opaque EH action of the unchanged matched C++ constructor.
No new semantic binding or synthetic standalone frame is introduced.
The scoped gate verifies the existing parent claims and destructor
relocation along with the new action.
