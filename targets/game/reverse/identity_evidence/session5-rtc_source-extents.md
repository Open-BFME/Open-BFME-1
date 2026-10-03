# Restore the complete CRT source-line lookup cleanup

The790B claim at009F8517 ends before PUSH EDI at009F882D. Retail
continues through allocation and interface cleanup to its shared epilogue,
RET009F8865. Entry-reachable branches009F854F/009F857A/009F858C target
009F885B, and009F8633 reaches009F885E. The next code is an import thunk
at009F8866. Original libc.lib pdblkup.obj emits the full847B; local PE
and Ghidra tails agree. No padding is included.

The inherited _RTC_GetSrcLine identity remains backed by the original
archive symbol. Complete archive comparison agrees on675concrete bytes;
its relocations are masked by the existing library verifier, so this
result is not an independent relocation-binding proof. No source/pin edits.
