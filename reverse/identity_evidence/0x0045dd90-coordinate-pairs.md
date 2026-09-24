# Coordinate-pair updater at 0x0045DD90

The 161-byte retail body starts at 0x0045DD90, ends in a plain `ret`, and
reads three pointer arguments at the caller's stack offsets +4, +8 and +12.
The two call sites at 0x00463850+0x270 and 0x00463E30+0x17B each push three
values before ILT 0x0001F339 and add 12 to `esp` afterward. This establishes
the `__cdecl` call ABI. Both callers remain anonymous, so `Rva0045DD90` stays
in the source function and record names.

The first argument carries a GameWindow pointer at +0x10 and two float pairs
at +0x14 and +0x1C. The body compares each pair with the corresponding input,
stores changed values, converts the floats to integers through four calls to
`__ftol2`, and calls ILTs 0x0001949D and 0x000482AC. Those ILTs are pinned to
the matched `GameWindow::winSetPosition` and `GameWindow::winSetSize` bodies.
The scoped gate must verify all six physical call relocations; the probe alone
masks relocation bytes.
