# Bounded renderer helper investigation

The preferred 0x008FEF60 bank still emits 244 bytes with 11 aligned
relocation operands and one differing instruction byte. Retail returns at
+0xF3. Its conditional branch at +0x79 skips the handle reload at +0x81
and reaches the test at +0x85; the bank instead branches to the reload.
This remains a real control-flow/code-generation difference.

The direct caller at 0x008FF060 occupies 144 bytes and returns at +0x8F.
It holds the receiver in ESI, passes a stack texture-handle address in EBX,
pushes the index, calls 0x008FEF60 and cleans the argument. Replacing the
bank's synthetic caller with a typed C++ approximation of this actual
caller left the 244-byte target and branch mismatch unchanged. The caller
approximation emitted 141 bytes with 95 differences and is not a matched
replacement.

Cached handle pointers, inline refcount helpers, null-after-release,
accessor/equality forwarding and split returns did not improve the target.
Post-decrement made it worse: 262 bytes, 106 differences and five shifted
relocation sites. The preferred existing bank remains the best source.

There is separate integration debt even if the branch is solved. The bank
redeclares canonical renderer classes. `rendobj.h` has unidentified virtual
slots at +0x10 and +0x14, so the bank's `Mesh_Self` name for +0x14 is not
independently established. `matinfo.h::Get_Texture(int)` declares a raw
pointer, whereas retail ILT 0x000366DD routes to the owning four-byte
handle return at 0x007A0340. The call site to 0x0092C3E0 pushes two
arguments, while its existing matched declaration takes none. These
contracts require independent proof and canonical integration; copying
the bank's private class declarations into production would not solve them.

No new body, symbol pin or completion credit results from this pass. A
later attempt should begin with the unchanged preferred 0x008FEF60 bank
and address the remaining branch plus these ABI constraints together.
