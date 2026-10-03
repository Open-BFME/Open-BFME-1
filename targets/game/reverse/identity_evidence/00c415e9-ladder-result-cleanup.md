# RVA 0x00C415E9: ladder packet result cleanup

Matched parent 0x00639190 pushes handler 0x00C41608, which loads
FuncInfo 0x00E310BC. Its state 0 -> -1 selects action 0x00C415E9.
The existing native ladder-packet source selects $L954 for that same
state and emits an exact 31-byte action.

Retail tests and clears mask 1 at EBP-0x1F4, then loads the result
pointer from EBP+4 and tail-jumps through PE-exported AsciiString
destructor ILT 0x0000D828. The false arm returns at +0x1E; a separate
ten-byte handler starts at +0x1F and is followed by INT3. Ghidra
created a 31-byte function and confirms this return-object lifetime.
Explicit EH metadata, rather than adjacency, establishes ownership.

The parent remains exact over 1583 bytes, and the ordinary scoped gate
checks its existing references and the new cleanup's actual destructor
target. This opaque cleanup row uses unchanged native C++, without
a new pin or an invented independent frame.
