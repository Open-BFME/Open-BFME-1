# RVA 0x00190F10: parser wrapper and native append visibility

This body remains address-named. The matched constructor at 0x00190E10
installs table VA 0x0109BFBC, whose second slot contains ILT VA 0x00422F02,
which jumps to this wrapper. Its version-one water-area construction follows
the tail of the Zero Hour PolygonTrigger::ParsePolygonTriggersDataChunk twin;
that does not establish the BFME derived parser method name.

The complete body ends with RET 8 at 0x0019109B and INT3 at 0x0019109E:
398 bytes. Ghidra reports a body_size of 395, which is not sufficient evidence
for the contiguous extent. read_memory and retail PE bytes establish the return
and padding addresses above; no claim is made that Ghidra omitted the return.
Use the independently verified contiguous 398-byte range.

At wrapper 0x00190F32 two arguments are pushed, ECX is retained as the receiver,
and CALL 0x00013B10 reaches 0x00190700. AL is tested immediately afterward.
The callee saves ECX at 0x0019071E and returns AL, ending with RET 8 at
0x00190C9B followed by INT3. This independently establishes the opaque
Rva00190700Guard::guard(void*, void*) Boolean thiscall declaration. Its one new
pin names the actual body at 0x00190700, not another semantic identity or an
unsupported route exemption. The existing generated row is not promoted.

The bank emitted 398 bytes with 17 differences: its byte store to node+0x32
preceded the first append-call argument setup. Exposing the actual non-inlined
85-byte Gen_0018F210::bfmeAppendVector3 definition from
Bfme5IndexedVector3Setter.cpp restores the exact scheduling. That helper grows
storage when full, marks the native dirty datum, copies one three-int point,
increments the count and stores the dirty byte. It does not retain the input
pointer. Merely exposing the node constructor leaves all 17 differences.

The new TU retains existing callee names, declares the actual GlobalData pointer
and uses its partial address-qualified field view only at the loads. The dirty
datum is the existing g_Rva00EEF418; the bank's old dirty/global-pointer aliases
are not added as pins. The existing append ledger provider remains unchanged.

Strict validation passes the complete 398-byte wrapper with two float constants
and nine DIR32 references. A separate selected-row audit of the visible helper
emission passes all 85 bytes, its native grow call, and both dirty-datum
references; this is verification only, not a second helper ledger claim.
