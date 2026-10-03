# Complete Radar event reset extent

The old135-byte claim at001076F0 ends on DEC EDI at00107776. The loop
continues with JNE00107720 at00107777, then POP EDI/ESI/EBX and RET at
0010777C. INT3 starts0010777D: full141 bytes. Local full-entry decoding
proves the loop edge and terminal epilogue. Ghidra entry/end005076F0..
0050777C agrees, while its135-byte address-set count omits alignment bytes.

The unchanged native Radar.cpp body emits all141 bytes exactly, with no
relocation slots in this function. Correct only its ledger extent. Retain
the existing identity: the GeneralsMD Common/System/Radar.cpp twin clears
ring indices and all event state, and the current matched Radar::reset calls
clearAllEvents. BFME's existing local source additionally releases retained
event references. This repair neither invents field/callback names nor
changes the inherited local view, virtual call ABI, shared headers or pins.

The scoped gate checks all Radar.cpp claims; complete-boundary validation
must include the missing loop branch and return epilogue.
