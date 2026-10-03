# RVA 0x00C56060: stream virtual-base cleanup

Matched constructor 0x0084C6F0 pushes handler 0x00C56095, which loads
FuncInfo 0x00E45258. Its state 0 -> -1 selects this action. The existing
native constructor source emits $L21881 for compiler state 0 -> -1.

Retail tests and clears mask 1 at EBP-0x14, loads saved this from
EBP-0x10, adds 0xC0 and tail-jumps through the existing narrow
basic_ios binding: ILT 0x000414BB to destructor 0x00538210. The conditional
RET at 0x00C5607E proves 31 bytes before the next distinct action.
Ghidra confirms the conditional cleanup; any extent expanded through
the tail call is not used as the action boundary.

Explicit EH metadata proves parent ownership, not adjacency. This
opaque cleanup uses unchanged native C++ and adds no new pin or
synthetic standalone frame. Scoped verification checks parent and
action bytes and the existing destructor relocation.
