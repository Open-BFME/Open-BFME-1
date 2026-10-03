# RVA 0x00C61E18: Snapshot secondary-base cleanup

The matched opaque owner destructor at RVA 0x009F2800 pushes handler
0x00C61E3F. That stub loads FuncInfo 0x00E5166C, whose unwind state
1 -> 0 names action 0x00C61E18 and state 0 -> -1 names 0x00C61E10.
This explicit chain establishes the parent independently of adjacency.

The 39-byte action uses saved receiver EBP-0x10, a nullable +8 base
adjustment into EBP-0x14, and a five-byte tail jump at +0x22 through
ILT 0x00001C80 to Snapshot::~Snapshot at 0x0005C520. The virtual ABI
is named by the retail PE export `??1Snapshot@@UAE@XZ`. The distinct
ten-byte handler starts at +0x27 and is followed by INT3. Ghidra
created a 39-byte function at VA 0x01061E18 and confirms the base
adjustment and vptr cleanup; ownership comes from the decoded EH map.

Existing `Rva009F2730Destructor.cpp` already declares the virtual
Snapshot destructor and emits this cleanup. Its compiler unwind map
selects $L385 for state 1 -> 0; the row binds that label in the proven
parent group. The parent, deleting wrapper and action pass the scoped
gate, including the actual destructor tail call. No source change,
new semantic identity, assembly body or dependency pin is needed.
