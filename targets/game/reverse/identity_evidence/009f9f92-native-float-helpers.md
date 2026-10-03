# Native D3DX scalar float helpers

Original `inputs/vendor/d3dx9/d3dx9.lib`, member `obj\i386\d3dxmath.obj`,
contains these distinct code COMDATs, each without any relocation:

| Section | Original symbol | Retail RVA | Bytes | Last instruction |
| --- | --- | --- | ---: | --- |
| 65 | `_atan2f@8` | 009F9F92 | 13 | RET 8 at 009F9F9C |
| 71 | `_fabsf@4` | 009F9FB6 | 9 | RET 4 at 009F9FBC |
| 77 | `_sinf@4` | 009F9FD2 | 9 | RET 4 at 009F9FD8 |
| 81 | `_sqrtf@4` | 009F9FEC | 9 | RET 4 at 009F9FF2 |

Each complete original section occurs exactly once in retail .text. The
other archive instances of fabsf/sinf/sqrtf are copies of the same COMDAT
symbol, not additional retail bodies. Thus the native symbols supply entry
and complete-return boundaries independently of neighboring RETs or a guessed
split. Ghidra read_memory at VA 00DF9F92 agrees with all 99 contiguous bytes
through the end of the last helper, including the intervening import routes.

The original stdcall float helpers consume one dword float each, or two for
atan2. Retail atan2 loads y from ESP+4 and x from ESP+8 before FPATAN, then
pops eight bytes; the others load ESP+4, apply FABS/FSIN/FSQRT, and pop four.
Their scalar result remains in ST(0). No ECX receiver or direct call is used.

The address-qualified C++ wrappers call the standard double math intrinsics
and return float. With /Oi and explicit intrinsic pragmas, MSVC 7.1 emits all
four exact native bodies on the first probe. No assembly, pins, fabricated
constant, semantic owner name or relocation masking is required. Each body
must also pass its own ordinary add_match gate before promotion.
