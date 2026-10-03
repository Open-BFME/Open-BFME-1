# RVA 0x00BFD706: date formatter result cleanup

The matched `getUnicodeDateBuffer` parent at 0x0010D7A0 pushes handler
0x00BFD725, which loads FuncInfo 0x00DEADCC. State 0 -> -1 selects
action 0x00BFD706. The existing native compiler map selects $L430
for that same state. The later states clean local string objects.

The 31-byte action tests and clears mask 1 at EBP-0x3A8, loads the
result pointer from EBP+4, and tail-jumps through UnicodeString
destructor ILT 0x0003B304 to body 0x0005EEA0. Ghidra identifies the
PE-exported destructor and confirms the result-pointer/lifetime-flag
accesses. The false arm returns at +0x1E; the separate EH handler
starts at +0x1F and its ten bytes are followed by INT3 padding.

The existing native source emits the exact action, uniquely within
its proven parent group. Normal scoped verification checks the parent
and this opaque action claim, including the destructor call. No new
source, pin, semantic name or fabricated frame is needed.
