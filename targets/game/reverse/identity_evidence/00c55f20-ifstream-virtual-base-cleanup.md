# RVA 0x00C55F20: ifstream virtual-base cleanup

Matched default constructor 0x0084C240 pushes handler 0x00C55F55,
which loads FuncInfo 0x00E4513C. State 0 -> -1 selects this action.
Its unchanged native source emits $L508 in compiler state 0 -> -1.

Retail tests and clears mask 1 at EBP-0x14, loads saved this from
EBP-0x10, adds 0xBC and jumps through ILT 0x000414BB to the existing
narrow basic_ios destructor at 0x00538210. The false arm returns at
0x00C55F3E, before the next separate action at 0x00C55F3F, proving
31 bytes. Ghidra agrees on the conditional virtual-base cleanup.

The EH chain proves ownership independently of adjacency. The opaque
action uses existing native C++ with no source edits, synthetic frame
or new pins. Scoped verification covers parent and cleanup.
