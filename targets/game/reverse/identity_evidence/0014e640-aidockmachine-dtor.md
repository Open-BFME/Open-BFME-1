# AIDockMachine's protected complete destructor owns the 11-byte body at 0014E640

Retail image: inputs/baselines/bfme1/retail-1.03-unpacked lotrbfme.exe.

## Body

0014E640: `mov dword ptr [ecx],0x1095a38` / `jmp 0x431d5e`
(tools/dis_retail.py 0x0014E640 11). VA 0x01095A38 is ??_7AIDockMachine@@6B@,
the vtable the matched AIDockMachine constructor at 0x0014F7C0 installs; the
jump goes through ILT 0x00031D5E to StateMachine's destructor. A destructor
re-seating its own class's vptr before tail-jumping to its base is the
complete destructor of that class.

## Caller and ILT

- The matched ??_GAIDockMachine@@MAEPAXI@Z at 0x0014F120 calls ILT 0x0000B7C6
  (tools/dis_retail.py 0x0014F120 30); ILT 0x0000B7C6 jumps to 0x0014E640.
  symbols.csv already pins ??1AIDockMachine@@MAE@XZ at that ILT.
- tools/ilt_oracle.py check '??1AIDockMachine@@MAE@XZ' 0x0014E640:
  CONFIRMED p_false=3.26e-04 (exact).

## Previous row

??1Rva0014E640TailDtor@@UAE@XZ (VptrTailJumpDestructors.cpp) was an
address-derived placeholder for the same bytes, with no caller naming it.
AIDock.cpp's Zero Hour ~AIDockMachine copy was present-unmatched and is
removed so retail's body is the only definition.
