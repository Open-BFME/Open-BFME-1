# RVA 0x00C566A8: store destructor cleanup

Matched parent 0x00880FC0 pushes handler 0x00C566CF, which loads
FuncInfo 0x00E45A64. Its unwind state 1 -> 0 explicitly names action
0x00C566A8; state 0 -> -1 names 0x00C566A0. The parent is the existing
opaque `Open2Store880FC0` destructor in `Open2Twins006.cpp`.

The action has 39 bytes: null-check saved receiver EBP-0x10, nullable
+8 base adjustment into EBP-0x14, and a tail jump at +0x22 through
ILT 0x00001C80 to Snapshot destructor body 0x0005C520. The PE export
identifies the virtual-destructor ABI. The distinct ten-byte handler
begins at +0x27 and is followed by INT3 padding. Ghidra created a
39-byte function at VA 0x010566A8 and confirms the frame/base access
and vptr cleanup. Its unanalyzed xref query had no references; the
retail EH records establish ownership.

The TU-local nonvirtual Snapshot destructor was replaced with the existing
`Source/Common/System/snapshot.h` declaration. All six existing parent
and deleting-destructor claims remain exact. The new cleanup row binds
the actual compiler label selected by state 1, preserving an opaque RVA
identity and checking the real Snapshot tail call through the scoped gate.
