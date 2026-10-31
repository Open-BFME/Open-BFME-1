# Apt GC trace: bind the installer-owned runtime hook

Base `274f3cb00`; claimed `00897360`. The existing opaque cleanup entry is
257 bytes through its tail JMP, with the separately rowed 39-byte unlink
helper in the same source. Neither function's identity or extent changes.

The native indirect printf-style call at +D7 reads VA `0133783C`. The
existing data row owns that four-byte zero-filled cell as
`void (*g_bfmeSlot04VB)(void)` in `Common/BfmeOneHundredTwentyThree.cpp`.
The 331-byte installer at `00789440` stores formatter VA `00B83210` there
at +28. Its actual formatter has the existing cdecl variadic signature.
The same owner and cast are already used by `TraceRva008C7D30.cpp` and
`BfmeR1226_bfmeLine1226.cpp`. The old C-linkage `g_bfmeCallback1226` has no
provider; it is an obsolete second spelling of this cell.

Use the owner's exact pointer type and keep the variadic cast at the call.
All 257 raw bytes are identical. Only DIR32 at +217 changes from
`_g_bfmeCallback1226` to `?g_bfmeSlot04VB@@3P6AXXZA`; its native address
does not change. All other relocations and the two retained inline/helper
code bodies are identical; no code definition is added or removed.
Normal consumer/installer verification passes 3/3 rows, 30 existing data
rows, one literal, 79 DIR32 checks and body guards. Frozen definitions pass.
No data owner, pin, alias, shared header, compiler flag or baseline changes.

Reviewed BFME 2 pin `b5a7b8290a0c4c20b03a3664609d434904e228eb`,
`Code/Libraries/Source/Apt/AptGCRva006E6E20.cpp` and `Apt.cpp`: their
collectors/teardown log through `Rva006CC110Log(int, const char *, ...)`.
That direct wrapper is different from BFME 1's runtime hook; its ABI,
addresses and class layouts are not imported. The target's existing data
row, installer, formatter and peer consumers establish this binding.

Against frozen index `afbe8bafb6` (2026-10-31 12:37), the changed consumer
previews unresolved/0 -> LINKS/296 authored bytes, including its unlink
helper. The installer unit still does not link: its old handler00..32 and
slot00/01 dependencies remain unresolved. Its data cell and installer bytes
are verified, but no complete initializer-unit closure is claimed.
The complete current object selection remains unavailable locally; this
is neither a new census nor full-image/runtime proof.

Native consumer/installer disassembly, original source/object, actual COFF
comparison and build/link logs are in ignored
`build/two-each-no-qwen-20261031-1756` and the matching diagnostic package.
Qwen and other local inference remain off; builds retain the shared ten-worker
cap without changing an Unreal process.
