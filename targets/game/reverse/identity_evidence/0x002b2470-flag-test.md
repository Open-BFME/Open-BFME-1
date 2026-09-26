# 0x002B2470: address-qualified part flag test

The retail body is exactly 24 bytes, takes its receiver in ECX, reads an owner pointer at receiver-0x1C, tests the owner's dword at +0x12C against `0x70000000`, and returns 1 or 0. It makes no calls and ends in two ordinary `ret` instructions. The two matched `BfmePartYH` methods at 0x0029C2D0 and 0x0029CF10 use the same receiver-to-host layout, so this body lives in their source file. No named caller or declaration proves a semantic method name; the new method retains the address token.

The inlined owner accessor uses a volatile-qualified read of the existing dword and a zero-byte compiler barrier in the zero-result arm. These preserve the retail memory `test` and separate returns without changing the flag test's value. The 24/24 scratch probe was exact with no relocations, and the strict scoped gate verified all three functions in `BfmeOneHundredFifty.cpp` after replacing the generated row.
