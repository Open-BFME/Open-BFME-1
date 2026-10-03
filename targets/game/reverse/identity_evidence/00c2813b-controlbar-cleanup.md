# RVA 0x00C2813B: ControlBar init string cleanup

Matched parent `ControlBar::init` at 0x004A0F70 has a six-byte
frame/alignment prefix, then pushes EH handler 0x00C281C3. This stub
loads FuncInfo 0x00E184A0. Its 19-state unwind map explicitly selects
0x00C2813B for state 15 -> 2; neighboring actions are different states
and are excluded. `eh_info.py 0x004A0F76` decodes the complete map.

Retail tests bit 2 of the lifetime word at EBP-0x8E4, clears that bit
when set, and tail-jumps through ILT 0x0000D828 with ECX=EBP-0x8E8.
The retail PE export names that entry `??1AsciiString@@QAE@XZ`.
The false arm reaches `ret` at +0x21, for 34 bytes total. The next
byte starts the distinct bit-4 state-16 action, not padding. Ghidra
decompilation confirms the lifetime guard and string release; its
aggregate function extent includes the tail-call destination, so the
linear action boundary comes from these bytes and the unwind map.

The existing native `ControlBarInit.cpp` remains byte-exact over its
3660-byte parent, and compiler state 15 -> 2 selects $L1915. That
label uniquely matches this 34-byte action within the parent group.
The cleanup row retains an opaque address name and uses the native
string lifetime; it does not author frame arithmetic or an assembly lift.
The normal scoped gate verifies the parent, action, and actual string
destructor target.
