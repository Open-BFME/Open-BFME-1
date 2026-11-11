# Script node constructor duplicate emission

Queue rank 13 at census 90c15cdeca reports duplicate definitions of
`??0Rva003529B0@@QAE@PBV0@@Z`, whose 57-byte owner is
`Rva003529B0Copy.cpp` at RVA 0x003529B0. Preserve that owner.

Adding `__forceinline` alone to the constructor views in
`Rva003529B0Clone.cpp` and `Rva0035CEE0StringRecordCopy.cpp` preserves
their bytes but still emits both extra definitions (COFF symbol inspection).
Adding `__declspec(dllimport)` as well removes the constructor symbols
entirely from both consumer objects, without adding imported constructor
references. The clone passes 1/1 rows and the record copy passes 2/2 rows
through normal scoped builds. `eh_state_pins.py --fix` uniquely repins the
record copy's existing cleanup from $L6951 to $L6948 using unwind state 2;
its bytes remain verified.

BFME 2 revision 76f0baefa6, corresponding
`Code/GameEngine/Source/Common/Rva003529B0Clone.cpp`, was reviewed. It
uses the later ScriptGroup representation and does not supply this emission
repair. No donor layout or name was imported. BFME 1 ownership and consumer
bytes come from its existing ledger and normal verification. The current
link preview is checked separately; removal of duplicate symbols alone does
not establish a linked-byte total.

Compiler context: existing MSVC 7.1 flags retained, clone /O2 /EHsc /MD;
record copy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB,
existing STLport selection retained. No shared header edits.
