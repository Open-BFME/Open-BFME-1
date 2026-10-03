# RVA 0x00C561A0: stream virtual-base cleanup

Matched constructor 0x0084CBC0 pushes handler 0x00C561D5, which loads
FuncInfo 0x00E45374. Its state 0 -> -1 selects this action. The existing
native constructor source emits $L1026 for compiler state 0 -> -1.

Retail tests and clears mask 1 at EBP-0x14, loads saved this from
EBP-0x10, adds 0x94 and tail-jumps through the existing wide
basic_ios binding: directly to destructor 0x0083F810. The conditional
RET at 0x00C561BE proves 31 bytes before the next distinct action.
Ghidra confirms the conditional cleanup; any extent expanded through
the tail call is not used as the action boundary.

Explicit EH metadata proves parent ownership, not adjacency. This
opaque cleanup uses unchanged native C++ and adds no new pin or
synthetic standalone frame. Scoped verification checks parent and
action bytes and the existing destructor relocation.
