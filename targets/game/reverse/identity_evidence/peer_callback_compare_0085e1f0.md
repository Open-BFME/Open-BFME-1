# Peer callback ID comparator at 0x0085E1F0

The matched C caller `_piIsCallbackFinished` at RVA 0x0085E200, extent 51,
passes VA 0x00C5E1F0 as the comparison callback to `_ArraySearch` at RVA
0x0086A2E0. The caller constructs a `piCallbackData` key, stores its operation
ID at offset 0x14, and searches the connection's callback list at offset 0x1818.
Its existing C source names that callback `piIsCallbackFinishedCompareCallback`.
The unchanged DIR32 record independently binds that exact C symbol to
VA 0x00C5E1F0.

Retail's complete 15-byte body at RVA 0x0085E1F0 reads the two cdecl arguments,
loads the left record's dword at +0x14, subtracts the right record's dword at
+0x14, and returns. This is the callback-ID comparator required by that caller.
The recovered C function probes EXACT, with no relocations.

The previous row `?dup_0085e1f0@@YAXXZ` was a `gen-alias` with
`object-symbol=_gpiTransferCompare`, pointing to `gp/gpiTransfer.c`. That GP
function already owns a separate 15-byte retail body at RVA 0x008F3D20.
Although these two bodies have identical instructions, retail did not fold
identical functions. The Peer caller and its existing DIR32 record prove the
Peer identity at 0x0085E1F0; the GP source/body cannot own both addresses.

Verification: `callees.py 0x0085E200 51` identifies `_ArraySearch`;
`callees.py 0x0085E1F0 15` finds no calls. Independent retail disassembly
confirms the pushed callback address, both +0x14 ID loads, and both distinct
15-byte boundaries. No pins, DIR32 records, or GP source were changed.

Model: gpt-6.1-sol via Codex CLI
