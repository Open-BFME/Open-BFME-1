# RVA 0x00C2D42B: lobby callback string cleanup

Retail parent 0x004FC7C0 (`WOLLobbyMenuSystem`) pushes handler
0x00C2D4FD, which loads FuncInfo 0x00E1D5F0. Unwind state 3 -> 0
explicitly names action 0x00C2D42B. The matching compiler map of
`WOLLobbyMenuSystem.cpp` selects $L40069 for exactly that state.

The 34-byte retail action tests and clears bit 1 at EBP-0x1CC, then
tail-jumps with ECX=EBP-0x1B8 through the PE-exported AsciiString
destructor ILT 0x0000D828. The false arm ends with ret at +0x21.
At +0x22 begins the separate state-4 cleanup 0x00C2D44D. Ghidra
created a 34-byte function and confirms the lifetime flag and string
release; explicit EH metadata supplies its parent identity.

Existing native C++ supplies the complete source and exact action.
The new opaque row pins the state-proven label; scoped verification
checks all existing source claims plus this action and its real
destructor target. No source or dependency-binding change is needed.
