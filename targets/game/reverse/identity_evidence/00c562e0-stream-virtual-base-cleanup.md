# RVA 0x00C562E0: wide fstream virtual-base cleanup

Matched constructor 0x0084D0A0 pushes handler 0x00C56315, which loads
FuncInfo 0x00E45480. State 0 -> -1 selects this action. The existing
native template source emits $L26783 for compiler state 0 -> -1.

Retail tests and clears mask 1 at EBP-0x14, loads saved this from
EBP-0x10, adds 0x98 and tail-jumps directly to the existing wide
basic_ios destructor at 0x0083F810. The conditional RET at
0x00C562FE proves 31 bytes before the next independent action.
Ghidra confirms the conditional virtual-base cleanup.

The retail and compiler EH maps prove parent ownership independently
of adjacency or identical bytes in another constructor. This opaque
action uses unchanged native C++ without new pins or an invented
standalone stack frame. Scoped verification checks parent and action
bytes and the destructor relocation.
