# BfmeCellGrid destructor at RVA 0x001B1AC0

The existing `symbols.csv` pin names `??1BfmeCellGrid@@QAE@XZ` at ILT RVA 0x000046E2. Retail's matched scalar-deleting destructor at RVA 0x001DE390 calls that ILT with the grid receiver in ECX before conditionally calling operator delete. The matched `VictorySystem::reset` at RVA 0x001DE5B0 calls the same ILT with each non-null grid receiver before operator delete. The matched constructor at RVA 0x001B1830 establishes the grid allocation and its 0x1C-byte layout.

Retail bytes at RVA 0x000046E2 are `E9 D9 D3 1A 00`, jumping to RVA 0x001B1AC0. The five-byte destructor is `E9 D5 AE E6 FF`, jumping to ILT RVA 0x0001C99A. That ILT jumps to the already matched `BfmeCellGrid::_bfme_reset` at RVA 0x001B14F0. The destructor preserves the receiver in ECX, takes no stack arguments, and tail-calls storage reset. Defining `BfmeCellGrid::~BfmeCellGrid()` to call `_bfme_reset()` retains the destructor identity and its retail call route.

This replaces the generated `?j_001b1ac0@@YAXXZ` row at the same five-byte extent with a compiled C++ destructor. It does not change either matched caller or the reset body. A different jump chain, a caller requiring stack arguments or a different receiver, or a compiled destructor that fails the byte and relocation gate would refute this identification.
