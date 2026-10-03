# RVA 0x00C55970: wide ostream virtual-base cleanup

Matched constructor 0x00843860 pushes handler 0x00C5598C, which loads
FuncInfo 0x00E44BB8. Its sole state 0 -> -1 selects this action. The
existing native stream source emits $L48038 for compiler state 0 -> -1.

Retail tests and clears mask 1 at EBP-0x14, loads saved this from
EBP-0x10, adds 4 and tail-jumps directly to the existing wide basic_ios
destructor at 0x0083F810. The conditional RET at 0x00C5598B proves
28 bytes before the separate handler. Ghidra confirms this cleanup.

The EH metadata proves ownership without inferring it from adjacency.
This opaque action uses unchanged native C++ with no new pin or
invented standalone frame. Scoped verification covers the parent,
cleanup bytes and existing destructor relocation.
