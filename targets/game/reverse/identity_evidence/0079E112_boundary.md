# Boundary correction for assigned dump 0x0079E112

The 518-byte dump is a suffix of the 552-byte function at RVA 0x0079E0F0.
The common end is 0x0079E318 (exclusive). This is a boundary correction only;
no original semantic class identity is asserted.

Retail baseline: inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe.

Independent entry evidence: ILT thunk 0x0000B6B8 jumps to 0x0079E0F0.
The preceding body at 0x0079DEE0 ends before this entry.

The omitted 34 bytes at 0x0079E0F0 establish the exception frame, reserve
0x54 bytes of locals, save EBX, clear EBX, and compare the asset subsystem
pointer against zero. The old entry at 0x0079E112 begins PUSH ESI and consumes
that comparison's ZF at 0x0079E115. It cannot be a standalone C++ function.
The common epilogue restores FS:[0], pops EBX, releases 0x60 bytes, and returns.

A complete C++ reconstruction in
`game/GameEngine/Source/GameClient/GUI/PalantirSceneInit0079E0F0.cpp`
compiles to exactly 552 bytes matching the full retail range. Its native STL
asset-set lifetime explains the prologue and cleanup, while the literal
palantir, render-object transform, scene and camera allocations, and final
Rva00596970::create call explain the body.

The old scaffold row is explicitly retracted before tools/add_match.py adds
and byte-verifies the complete claim. add_match does not support moving a
replacement start RVA, and no tool or gate is modified or bypassed.

model=gpt-6-astra-medium
