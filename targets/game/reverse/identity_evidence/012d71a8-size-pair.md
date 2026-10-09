# Two DWORDs at VA 012D71A8 and 012D71AC

The complete matched 17-byte cdecl setter at RVA 00938A50 reads its
unsigned argument from [ESP+4], stores EAX to VA 012D71AC, shifts EAX
right by one, and stores it to VA 012D71A8. It ends in RET at 00938A60,
followed by INT3 padding. Both stores independently prove four-byte
mutable unsigned storage with no pointer interpretation.

The two recorded globals occupy adjacent, nonoverlapping DWORDs.
The separate recorded global g_Va012D71B0 begins immediately after
them. sortingrenderer.cpp independently reads the half-value through
its existing unsigned-int declaration for the polygon-count limit.
The existing W3DDisplay initializer calls this setter with value 1
when the corresponding option is enabled.

Retail .data initially holds 00004000 at VA 012D71A8 and 00008000
at VA 012D71AC (16384 and 32768). Define the existing symbols as
unsigned int with those initializers. Each compiler sizeof probe must
report four bytes. No names, pins, aliases, headers, address globals,
or DIR32 records change.
