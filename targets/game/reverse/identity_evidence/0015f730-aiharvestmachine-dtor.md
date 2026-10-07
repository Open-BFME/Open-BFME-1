# 0x0015F730 is AIHarvestMachine::~AIHarvestMachine

The 11-byte body at RVA 0x0015F730 (previously the address-derived
`??1Rva0015F730TailDtor@@UAE@XZ`) is `??1AIHarvestMachine@@MAE@XZ`.

- Bytes: `mov dword ptr [ecx],0x01096650 / jmp StateMachine dtor`: a derived
  destructor re-seating vftable 0x01096650.
- 0x01096650 is AIHarvestMachine's vftable: the matched
  `??0AIHarvestMachine@@QAE@PAVObject@@@Z` (0x0015FE90) installs it, and
  symbols.csv pins `??_7AIHarvestMachine@@6B@` there.
- The matched protected scalar-deleting destructor
  `??_GAIHarvestMachine@@MAEPAXI@Z` (0x0015FA60) calls this body through ILT
  0x000289FC, where symbols.csv already pins `??1AIHarvestMachine@@MAE@XZ`
  (ILT jumps to 0x0015F730).

The stale dir32 record `??_7Rva0015F730TailDtor@@6B@` at 0x01096650 is deleted.
