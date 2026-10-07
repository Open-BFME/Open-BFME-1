# 0x0015B9D0 is AIGuardMachine::~AIGuardMachine

The 11-byte body at RVA 0x0015B9D0 (previously the address-derived
`??1Rva0015B9D0TailDtor@@UAE@XZ`) is `??1AIGuardMachine@@UAE@XZ`.

- Bytes: `mov dword ptr [ecx],0x01095FE0 / jmp StateMachine dtor`: a derived
  destructor re-seating vftable 0x01095FE0.
- 0x01095FE0 is AIGuardMachine's vftable: the matched
  `??0AIGuardMachine@@QAE@PAVObject@@VAsciiString@@@Z` (0x0015D1D0) installs it.
- The matched scalar-deleting destructor `??_GAIGuardMachine@@UAEPAXI@Z`
  (0x0015C030) calls this body through ILT 0x00035D46 (`?j_00035d46`,
  target 0x0055B9D0 VA), and symbols.csv already pins
  `??1AIGuardMachine@@UAE@XZ` at 0x0015B9D0 from the GiantBirdGuardMachine
  ctor unwind handler.

The stale dir32 record `??_7Rva0015B9D0TailDtor@@6B@` at 0x01095FE0 is
deleted; the vftable keeps its real name `??_7AIGuardMachine@@6B@`, which the
ctor TU already references.
