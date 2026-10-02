# DisplayStringManager destructor at RVA 0x00410290

The existing 11-byte row `??1Rva00410290TailDtor@@UAE@XZ` names an address-based derived destructor in `VptrTailJumpDestructors.cpp`. This correction preserves its extent and coverage, moving it to the existing canonical DisplayStringManager TU.

Independent identity and ABI evidence from retail-1.03-unpacked:

- Matched `W3DDisplayStringManager::~W3DDisplayStringManager` at RVA 0x006F57B0 (176 bytes) tears down its derived members and calls ILT RVA 0x000472E9. That five-byte thunk jumps to RVA 0x00410290. The typed source declares W3DDisplayStringManager as derived from DisplayStringManager, establishing the base destructor identity independently of byte matching.
- Matched `DisplayStringManager::DisplayStringManager` at RVA 0x00410240 (26 bytes) installs vtable VA 0x010F1014. The candidate destructor starts by writing precisely VA 0x010F1014 through ECX.
- The matched scalar-deleting destructor at RVA 0x004102A0 (30 bytes), reached through slot zero of that table via ILT RVA 0x0003981A, calls the same ILT RVA 0x000472E9 before optional scalar deletion.
- The candidate ends with a direct tail jump from RVA 0x00410296 to the independently matched `SubsystemInterface::~SubsystemInterface` at RVA 0x009A1A40 (14 bytes). ECX is unadjusted and no arguments are added: this is the virtual `__thiscall` base destructor route. The existing canonical header already declares DisplayStringManager as derived from SubsystemInterface.
- Ghidra records the boundary RVA 0x00410290, size 11 (`FUN_00810290`). `callees.py 0x00410290 11` completes decoding; there are no direct CALL instructions because the final transfer is a JMP. The retail tail route was separately decoded with Capstone from baseline bytes.

The replacement is the empty typed destructor using the existing header. The old address-derived macro is removed only after successful byte verification of the canonical provider. No shared headers or pins change, and all remaining macro-backed rows retain their source and identities.
