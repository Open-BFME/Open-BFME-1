# C249B8 guarded functor cleanup

Retail `462710` is the already matched STLport `for_each` instantiation in
`Rva00462710ModeCheckForEach.cpp`. It calls the already matched
`Rva0045F0A0::process` at `45F0A0` through ILT `E54D`.
The independently recovered callback in `Rva0045F0A0ModeCheck.cpp` establishes
its receiver layout: byte enabled flag at zero, AsciiString at four. The
for_each copy/return and normal destruction use StringBase<char> copy and
releaseBuffer on that same member. No semantic class name is introduced.

The parent EH prologue targets handler `C249D1`, which loads FuncInfo
`E14B3C`; unwind map `E14B2C` state 0 (predecessor -1) points to `C249B8`.
Ghidra raw pointer search independently finds VA `01214B30`.
The action tests/clears bit 1 of EBP-10 and destroys the hidden return object
at EBP+4, tail jumping through ILT `4A6EC`. Its RET at `C249D0` gives 25 bytes;
the handler follows, then INT3 padding. Native compiler label is `$L7129`.

ILT `4A6EC` targets `45E6D0`: `add ecx,4; jmp 887940` (8 bytes), followed by
INT3 padding. `887940` is the established StringBase<char>::releaseBuffer.
This is the destructor of the caller-proven address-named functor, not a
releaseBuffer synonym. The native `??1Rva0045F0A0@@QAE@XZ` is independently
verified as an ordinary function with the strict selected-row verifier:
8/8 bytes including its releaseBuffer relocation pass. This test writes no
second ledger body. The existing `Rva0045E6D0::invoke` row is retained.

One direct body pin binds that destructor at `45E6D0`. No route exemption,
source modification, semantic rename, or shared header change is needed.
