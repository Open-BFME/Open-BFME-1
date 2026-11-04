# _g_011343A4 string storage at VA 0x011343A4

The decorated identity `_g_011343A4` owns 6 bytes in retail `.rdata` at VA 0x011343A4.

## Retail facts and contract

Retail `lotrbfme.exe` holds 6 bytes at VA 0x011343A4:
`20 45 42 50 3a 00` (" EBP:\0").
`DebugExceptionhandler::LogRegisters` in `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp` references this string when formatting the EBP register (`ctx.Ebp`).

## Extent and users

6 bytes at VA 0x011343A4. Users: `DebugExceptionhandler::LogRegisters` in `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp`.
