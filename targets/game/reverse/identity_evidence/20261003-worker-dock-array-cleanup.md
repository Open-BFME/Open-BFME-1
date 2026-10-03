# Worker array cleanup and callback

All addresses are RVAs in the BFME1 1.03 unpacked image. Raw PE and Ghidra
memory agree on the complete action and callback.

The matched native WorkerAIUpdate destructor at 002C7A80 pushes handler
C1408C at 002C7A82. FuncInfo E03774/map E03754 state 1 -> 0 selects C14058.
This 24-byte action passes saved receiver EBP-10 plus 368, count nine, stride
16, callback VA40FD6C to the vector destructor iterator. RET C1406F ends it
before the different member cleanup at C14070.

ILT 0000FD6C jumps to 002C7A70, which contains exactly RET followed by fifteen
INT3 bytes. The next parent starts at 002C7A80. This callback is the destructor
of the parent's real array element, not an arbitrary empty function selected
because its bytes happen to agree. Zero Hour WorkerAIUpdate.h independently
contains the three-by-three dock-point information array with Boolean valid
and Coord3D location, corroborating the 16-byte element shape.

The native parent already declares its element as BfmeWorkerDockPoint, with
the correct array count, size and offset. Retain that local view spelling and
define its destructor with the observed empty body. Preserve the existing
address-derived Rva002C7A70NoOp ledger identity with the native destructor as
object selector; no retail type spelling is asserted. Retire the orphaned
standalone no-op source once this callback and the unchanged 259-byte parent
verify. No new pin, duplicate destructor alias or dummy parent is introduced.
