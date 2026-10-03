# Debug frame-entry lookup full boundary

The previous91-byte claim at0088AEC0 ends after the first byte of
MOV ESI,EDX at0088AF1A. That block is reached by the lookup-success branch
at0088AEE3. The full block is MOV ESI,EDX then JMP0088AF04 at0088AF1C;
it rejoins the common status-update/return path, whose RET16 is0088AF17.
INT3 begins0088AF1E. The complete contiguous extent is94 bytes.
Ghidra entry/end00C8AEC0..00C8AF1D corroborates it; its91-byte address-set
count excludes the alignment gap and must not be used as a span.

The existing native source already emits the exact94-byte body. Retain it
unchanged and correct only the ledger extent. Independent identity evidence
is the GeneralsMD Libraries/Source/debug/debug_debug.h GetFrameEntry twin
(lines1006 onward): LookupFrame over10007 buckets, AddFrameEntry on absence,
UpdateFrameStatus for Unknown, then return the entry. Existing source uses
that same native flow and layout. Calls remain00889F20/0088A7E0 under their
existing source declarations/pins; callees.py was consulted and no new pin
or callee identity is introduced. The current callee ledger has differing
labels, which this extent-only repair does not reinterpret.

A scoped strict gate must verify all94 bytes and the complete control-flow
boundary, including the backward jump into the existing return path.
