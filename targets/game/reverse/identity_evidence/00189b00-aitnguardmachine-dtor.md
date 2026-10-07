# 0x00189B00 is AITNGuardMachine::~AITNGuardMachine (public)

The 11-byte body at RVA 0x00189B00 (previously the address-derived
`??1Rva00189B00TailDtor@@UAE@XZ`) is `??1AITNGuardMachine@@UAE@XZ`. The
30-byte scalar-deleting destructor at 0x00189E10 is
`??_GAITNGuardMachine@@UAEPAXI@Z`; the prior claim `...@@MAEPAXI@Z` had the
right class and member but the wrong access.

- Bytes: `mov dword ptr [ecx],0x0109B4B0 / jmp ILT 0x00031D5E` (StateMachine
  dtor): a derived destructor re-seating vftable 0x0109B4B0.
- 0x0109B4B0 is AITNGuardMachine's vftable: the matched
  `??0AITNGuardMachine@@QAE@PAVObject@@@Z` (0x0018AFB0) installs it, and
  symbols.csv pins `??_7AITNGuardMachine@@6B@` there (RVA 0x00C9B4B0).
- The matched scalar-deleting destructor at 0x00189E10 calls this body
  through ILT 0x0003D4C9 (`jmp 0x00189B00`).
- Access: retail's incremental-link thunk table orders thunks by decorated
  name. `python3 tools/ilt_oracle.py check '??1AITNGuardMachine@@UAE@XZ'
  0x00189B00` prints CONFIRMED (exact, p_false=1.57e-03) and the MAE spelling
  prints CONTRADICTED. `check '??_GAITNGuardMachine@@UAEPAXI@Z' 0x00189E10`
  prints CONFIRMED (exact, p_false=1.83e-03) and MAE prints CONTRADICTED.

The body comes from VptrTailJumpDestructors.cpp. AITNGuard.cpp's ZH copy
does not match (it stores [ecx+4] instead of tail-jumping), so it is removed.
The stale dir32 records `??_7Rva00189B00TailDtor@@6B@` and
`?g_AITNGuardMachineVTable@@3HA` at 0x0109B4B0 are deleted. The ctor TU now
stores `??_7AITNGuardMachine@@6B@`.
