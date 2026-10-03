# RVA 0x00C0A078: VictorySystem Snapshot cleanup

The matched complete destructor at RVA 0x001DFF40 pushes handler
0x00C0A09F, which loads FuncInfo 0x00DF8908. Its state 1 -> 0 explicitly
selects action RVA 0x00C0A078; state 0 -> -1 selects 0x00C0A070.
This proves the parent independently of address proximity.

The action is 39 bytes: a nullable +8 conversion from the saved receiver
at EBP-0x10 into EBP-0x14, followed by a tail jump at +0x22 through
ILT 0x00001C80 to the seven-byte Snapshot destructor at 0x0005C520.
The PE export is `??1Snapshot@@UAE@XZ`. A distinct ten-byte EH handler
begins at +0x27, followed by INT3 padding. Ghidra created an exact
39-byte function at VA 0x0100A078 and confirms the receiver adjustment
and Snapshot vptr cleanup; its unanalyzed xref query found no references,
so the retail EH map supplies the ownership evidence.

Existing `VictorySystemDestructors.cpp` already emits this action.
Its native compiler unwind map selects $L371 at state 1 -> 0, and the
39-byte prefix exactly matches retail including the resolved tail jump.
Both existing destructor rows and this new opaque funclet row pass the
normal scoped gate. No source change or invented semantic name is needed.
