# 0x0022EF90 is TunnelContain's complete destructor

The 67-byte body was held by the address-derived placeholder
`??1Rva0022EF90FlatDtor@@UAE@XZ` in `FlatMultiVptrDestructors.cpp`.

- ILT 0x0003BF39 is one instruction, `jmp 0x0022EF90`
  (`python3 tools/dis_retail.py 3BF39 5`), and `symbols.csv` pins it as
  `??1TunnelContain@@MAE@XZ`.
- The matched scalar-deleting destructor `??_GTunnelContain@@MAEPAXI@Z`
  (0x0022F0E0, `TunnelContainDeletingDestructor.cpp`), reached from slot zero
  of vtable 0x00CADDB8 whose slots name TunnelContain, calls ILT 0x0003BF39
  before `operator delete`: the complete destructor of the same class.
- The body tail-jumps to ILT 0x00039D6A, pinned `??1OpenContain@@UAE@XZ`,
  TunnelContain's base in Zero Hour.

Protected (`MAE`): the deleting destructor and the existing pin are both
protected, matching the MemoryPool-object `~TunnelContain` declaration.
