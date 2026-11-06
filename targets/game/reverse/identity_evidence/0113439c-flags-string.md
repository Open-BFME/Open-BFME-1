# EFLAGS label at VA 0x0113439C

The C identity `_g_0113439C` (C `const char g_0113439C[]`) owns 7 bytes
at VA 0x0113439C in retail `.rdata`: `Flags:` plus the terminating NUL
(read via `reloc_ledger.Image.read`). The following retail byte is NUL
padding shared with the neighbor table, claimed by no row.

- Defined in
  `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp`,
  streamed by `DebugExceptionhandler::LogRegisters` before `ctx.EFlags`
  in binary (`Debug::Bin()`, width 32).
- Follows the eleven landed sibling label rows in the same TU (EAX, EBX,
  EDX, ESI, EDI, EIP, ESP, EBP, CS, DS, SS, ES, FS, GS); same extent rule
  (literal plus NUL only).

## Extent and all users

`sizeof` 7 bytes at VA 0x0113439C as proven by the data gate. Sole DIR32
consumer is `LogRegisters` in DebugExceptionhandler_LogRegisters.cpp.
