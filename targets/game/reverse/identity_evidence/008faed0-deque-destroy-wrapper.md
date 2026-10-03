# Native deque destruction wrapper at008FAED0

The complete native `_Destroy` COMDAT emitted by the already matched
ShroudManagerImpl008FBA40.cpp is75B and uniquely matches this unclaimed
retail interval, including its one call target008FAD20. The vendored
STLport stl/_construct.h `_Destroy(first,last)` declaration establishes
two iterator values passed by value, not two pointers or an arbitrary
number of cdecl arguments. Each native deque iterator contains four
pointers and occupies16B.

The full extent is008FAED0..008FAF1B: the final RET is008FAF1A, followed
by five INT3 bytes before008FAF20. The preceding matched46B deque
constructor ends at008FAECE, followed by two INT3 bytes. Ghidra memory
at00CFAED0 independently agrees with all80 body/padding bytes. The native
full-function COMDAT and these terminal/padding boundaries are the entry
evidence; the earlier raw REL32/absolute-reference survey found no incoming
entry references. No table/caller entry witness is asserted.

The actual target is the existing matched81B `__destroy` specialization
in RvaDequeDestroyPod.cpp. Its signature independently agrees on the two
iterator values and the third, null element-type pointer. Retail008FAD20
increments the current pointer by0x14 and sets a new node end at+0x78:
20-byte elements over120-byte nodes. Both the existing opaque20-byte
callee view and the Shroud record's five DWORD members agree. The legacy
token `Gen_t_008fb350_p12pod` is not evidence for a12-byte layout.

The new entry remains address-qualified. Its ordinary C++ call to native
_Destroy inlines the proven wrapper and forwards to that same canonical
__destroy specialization. It is colocated with the matched callee, so the
scoped gate verifies both75B and81B bodies and their binding together.
No type/header/pin duplication, guessed owner or manual iterator copy is
introduced.
