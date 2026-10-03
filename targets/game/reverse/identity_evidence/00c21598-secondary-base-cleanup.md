# RVA 0x00C21598: secondary-base cleanup

The existing matched destructor at 0x0042B9F0 pushes handler 0x00C215BF,
which loads FuncInfo 0x00E11960. Its unwind state 1 -> 0 explicitly
selects 0x00C21598; state 0 -> -1 selects 0x00C21590. Thus the parent
is metadata-proven, not inferred from adjacent code.

The 39-byte cleanup null-checks the saved receiver at EBP-0x10, adds
0x24 for the secondary base, saves that pointer at EBP-0x14, and ends
in a five-byte tail jump at +0x22. A separate EH handler begins at
+0x27 and is followed by INT3 padding. Ghidra decompilation confirms
the saved-frame accesses and the base vptr restoration.

The jump reaches ILT RVA 0x0003A0FD, whose E9 reaches body 0x003828E0.
Independent decoding of that complete seven-byte body shows only
`mov [ecx],0x010EAD58; ret`, then INT3. The matched parent restores this
same vptr at receiver+0x24 on its normal cleanup path. The unwind map
and base adjustment independently establish a secondary-base destructor
contract. Its original class identity is unknown; vtable 0x010EAD58
alone does not justify naming it Snapshot or another real class.

The existing local BfmeDBaseB view is therefore qualified by namespace
Rva003828E0. This keeps its inherited spelling without asserting an EA
identity, and the added destructor binding names its independently proven
body address. There is no new function-ledger identity at the callee.
The pin is a dependency of this real unwind call, not an alternate-name
linker workaround. The original parent remains byte-exact.

The compiler unwind state 1 -> 0 selects the exact action label recorded
in the new row; normal scoped verification checks its real tail-call
binding in addition to the instruction bytes.
