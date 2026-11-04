# _g_011343B4 string storage at VA 0x011343B4

The decorated identity `_g_011343B4` owns 5 bytes in retail `.rdata` at VA 0x011343B4.

## Retail facts and contract

Retail `lotrbfme.exe` holds 5 bytes at VA 0x011343B4:
`45 49 50 3a 00` ("EIP:\0").
`DebugExceptionhandler::LogRegisters` in `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp` references this string when formatting the EIP register (`ctx.Eip`).

## Extent and users

5 bytes at VA 0x011343B4. Users: `DebugExceptionhandler::LogRegisters` in `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp`.
