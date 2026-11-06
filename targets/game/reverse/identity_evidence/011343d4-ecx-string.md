# ECX label at VA 0x011343D4

The C identity `_g_011343D4` (C `const char g_011343D4[]`) owns 6 bytes
at VA 0x011343D4 in retail `.rdata`: ` ECX:` plus the terminating NUL
(read via `reloc_ledger.Image.read`). The following retail bytes are NUL
padding shared with the neighbor table, claimed by no row.

- Defined in
  `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp`,
  streamed by `DebugExceptionhandler::LogRegisters` before `ctx.Ecx`
  (width 8).
- Follows the twelve landed sibling label rows in the same TU (EAX, EBX,
  EDX, ESI, EDI, EIP, ESP, EBP, Flags, CS, DS, SS, ES, FS, GS); same
  extent rule (literal plus NUL only).

## Extent and all users

`sizeof` 6 bytes at VA 0x011343D4 as proven by the data gate. Sole DIR32
consumer is `LogRegisters` in DebugExceptionhandler_LogRegisters.cpp.
