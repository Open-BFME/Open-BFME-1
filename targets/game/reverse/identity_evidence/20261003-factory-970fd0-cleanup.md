# Factory 00970FD0 result lifetime

Addresses are RVAs in the BFME1 1.03 unpacked retail baseline. Ghidra memory
independently agrees with the raw PE bytes.

Matched native `bfmeMakeXQ` at 00970FD0 constructs its hidden return object
with the matched `Gen00970F80` constructor at 00970F80. The constructor is in
`P8ZeroingCtors.cpp`; the address in the type name is deliberately retained.
The factory pushes handler C5F051 at 00970FD2. Its FuncInfo E4E410 and map
E4E400 assign state 0 -> -1 to C5F030. The 25-byte action tests mask 1 in
EBP-10, clears it, and passes the hidden result from EBP+4 to 00970EA0.
Its conditional RET at C5F048 precedes the separate temporary action C5F049.

00970EA0 dereferences the single pointer at receiver offset zero, tests for
null, and tail-jumps to 009EB7A0. The null arm returns at 00970EAB; INT3 padding
begins at 00970EAC. This is a complete 12-byte destructor, with the same
existing `TextureClass::Release_Ref` binding already used by the native factory.
The return-object lifetime, not identical bytes alone, identifies its owner.

The old opaque row used `gen-alias;object-symbol=??1NetCommandRef@@QAE@XZ`.
The real network destructor is at 00676280 and calls NetCommandMsg::detach,
so it cannot supply this result's identity. Replace only the alias row with
the native address-named destructor in the factory TU. Preserve the real
network TU and all its other claims. No new semantic owner/member names or
alias pins are added. Reverify the 141-byte factory and 12-byte destructor,
then select and strictly verify the actual native compiler cleanup label.
