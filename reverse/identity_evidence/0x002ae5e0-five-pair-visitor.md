# 0x002AE5E0 paired pointer-range visitor

The complete 112-byte retail body ends in `ret`. Its entry loads three cdecl
arguments: a record pointer, then two callback arguments. Five iterations
advance by 12 bytes through two contiguous arrays of pointer ranges. The first
array begins at record+0x50; the second begins at record+0x8C. Each non-null
element receives the two callback arguments in the same order.

The first call encodes ILT 0x00040412 and reaches matched body 0x001D6860;
the second encodes ILT 0x00022D86 and reaches matched body 0x00428250.
Both callees consume ECX as their receiver and end in `ret 8`. The already
matched 0x00208F90 asset walker uses the same two structural delegate
signatures. This corroborates the ABI and range layout, but no independent
named caller proves this visitor's owner or method identity. The new name
therefore retains `002AE5E0`.

The clean C++ visitor matches all 112 bytes after relocation resolution, with
both retail ILT call sites verified by the strict scoped gate.
