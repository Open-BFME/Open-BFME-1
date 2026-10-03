# RVA 00C52265: native member-array cleanup

The entry stays opaque (`?dup_00C52265@@YAXXZ`). This promotes an action
already emitted by the unchanged native WaterRenderObjVirtualDestructor.cpp;
it introduces no member, type, callback alias, or source identity.

## Independent retail ownership and extent

Read from the BFME1 1.03 unpacked executable and cross-checked through the
Ghidra server read_memory API (program lotrbfme.exe):

- Parent RVA 007A5D10 begins `6A FF 68 9D 22 05 01`, installing handler
  VA 0105229D. The handler loads FuncInfo VA 0124199C.
- FuncInfo has ten states and unwind map VA 0124194C. Entry 7 at
  VA 01241984 is `{6, 01052265}`. This proves ownership without adjacency.
- Action bytes are `6828d840006a056a048b45f005cc02000050e8fa4adaffc3`.
  It pushes callback VA 0040D828, count 5, stride 4, loads the saved receiver
  from EBP-10, adds 2CC, and calls RVA 009F6D76. RET at RVA 00C5227C
  closes the 24-byte extent. Another action begins immediately at 00C5227D;
  there is no INT3 padding between the actions.
- Callback ILT RVA 0000D828 bytes `E9 63 16 05 00` reaches RVA 0005EE90,
  the existing canonical AsciiString destructor. The array helper is the
  independently proven CRT `eh vector destructor iterator`.

## Native emission and verification

The parent source already declares five AsciiString members at +2CC.
The native compiler emits this cleanup as `$L7039`: 24 bytes, 16 concrete
bytes and two relocations (AsciiString destructor DIR32 and CRT helper REL32).
The original parent passes its strict scoped build. Promotion uses add_match
with the same parent and exact emitted symbol; no source or pin edits.
Executable-section and one-row-per-address audit are required before commit.
