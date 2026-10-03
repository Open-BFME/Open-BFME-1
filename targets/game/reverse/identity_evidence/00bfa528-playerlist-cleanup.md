# RVA 0x00BFA528: PlayerList Snapshot cleanup

Retail parent `??1PlayerList@@UAE@XZ`, RVA 0x000DF9A0 (138 bytes),
pushes handler VA 0x00FFA54F. This handler loads FuncInfo VA 0x011E7E28.
Its unwind map has state 0 -> -1/action RVA 0x00BFA520 and state 1 ->
0/action RVA 0x00BFA528. This explicitly proves the parent and state.

The 39-byte action tests saved this at EBP-0x10, performs a null-preserving
+8 base conversion into EBP-0x14, and tail-jumps at +0x22 through ILT RVA
0x00001C80. The handler begins immediately at +0x27; after its ten bytes
comes INT3 padding. The retail PE export directory names that ILT
`??1Snapshot@@UAE@XZ`; its jump reaches RVA 0x0005C520, whose seven bytes
store Snapshot vtable VA 0x01073744 and return. Ghidra decompilation of
VA 0x00FFA528 confirms this saved-frame/base adjustment and vptr cleanup.
Its aggregate body size includes the jumped-to destructor, so the linear
tail-jump boundary is taken from the actual retail bytes.

The existing PlayerList destructor TU already emits the action, but its
local Snapshot destructor declaration was nonvirtual and therefore named
an unresolved, different callee. Making that declaration virtual follows
the PE export; no new pin or header change is needed. The available
Snapshot headers retain the nonvirtual Zero Hour contract, so they cannot
express this BFME contract (see docs/header_adoption.md on unsettled
Snapshot headers). The parent and deleting destructor remain byte-exact.

After this declaration correction, the compiler unwind map selects $L390
for state 1 -> 0, and its 39-byte prefix exactly reproduces the action.
The row keeps an opaque RVA identity, native C++ source, explicit parent
and state-proven object label. Normal verification also resolves its
Snapshot destructor tail jump.
