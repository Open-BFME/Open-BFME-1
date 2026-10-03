# RVA 0x00C31BF0: istringstream virtual-base cleanup

Matched constructor 0x0053FB00 pushes handler 0x00C31C22, which loads
FuncInfo 0x00E21B1C. Its state 0 -> -1 selects this action. Existing
native constructor source emits $L514 for compiler state 0 -> -1.

Retail tests and clears mask 1 at EBP-0x14, loads saved this from
EBP-0x10, adds 0x74 and tail-jumps through ILT 0x000414BB to the
existing narrow basic_ios destructor at 0x00538210. The conditional
RET at 0x00C31C0B proves 28 bytes before the next independent action.
Ghidra confirms the conditional virtual-base cleanup.

The EH chain proves parent ownership without relying on adjacency.
This opaque cleanup uses unchanged native C++ with no new pins or
synthetic standalone frame. Scoped verification checks the parent,
action bytes and existing destructor relocation.
