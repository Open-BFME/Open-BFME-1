# _g_01134280 string storage at VA 0x01134280

The decorated identity `_g_01134280` owns 2 bytes in retail `.rdata` at VA 0x01134280.

## Retail facts and contract

Retail `lotrbfme.exe` holds 2 bytes at VA 0x01134280:
`25 00` ("%\0").
`DebugExceptionhandler::LogRegisters` in `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp` references this prefix string when setting binary formatting prefix (`SetPrefixAndRadix(g_01134280, 2)`).

## Extent and users

2 bytes at VA 0x01134280. Users: `DebugExceptionhandler::LogRegisters` in `game/Libraries/Source/WWVegas/WWDebug/DebugExceptionhandler_LogRegisters.cpp`.
