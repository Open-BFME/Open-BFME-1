# Wide STLport global lifetimes

`game/stlport/X4Iostream.cpp` already defines all eight native STLport4.5.3
stream globals in its `STLPORT_NO_INIT` segment. The four wide stream
initializers below each call the typed constructor with null streambuf and
hidden complete-object flag 1, then register the paired compiler cleanup.
These are anonymous compiler helpers, so address-derived initializer ledger
names select their TU-local COFF artifacts through `object-symbol=`.

| Global | Retail initializer / COFF | Stored initializer pointer RVA | Global VA | Cleanup / COFF |
|---|---|---|---|---|
| `_STL::wcin` | 0x00C6D960 / `_$E13` | 0x00F5E010 | 0x0130BFA8 | 0x00C70D90 / `_$E14` |
| `_STL::wcout` | 0x00C6D980 / `_$E16` | 0x00F5E014 | 0x0130BE70 | 0x00C70DB0 / `_$E17` |
| `_STL::wcerr` | 0x00C6D9A0 / `_$E19` | 0x00F5E018 | 0x0130C010 | 0x00C70D10 / `_$E20` |
| `_STL::wclog` | 0x00C6D9C0 / `_$E22` | 0x00F5E01C | 0x0130BD38 | 0x00C70D30 / `_$E23` |

Retail initializers end with RET at +0x19 and INT3 at +0x1A (26 bytes).
Each cleanup ends with a tail JMP at +0x17 and INT3 at +0x1C (28 bytes).
The input cleanup installs vtable VA0x0112F2FC and passes global+8 to the
wide `basic_ios` destructor at RVA0x0083F810. Output cleanups install
VA0x0112F30C and pass global+4 to that same typed destructor. It is already
matched and pinned independently in `stlport_basic_ios_destructors.cpp`.
The input constructor RVA0x008438F0 and output constructor RVA0x00843860
are likewise existing matched native STLport bodies. Both canonical stream
global names and the old wrapper storage aliases are already recorded at
these same DIR32 addresses; no new pins, guessed type names or layout shims
are needed.

Strict gates verify each initializer and cleanup separately, including all
call and global/vtable relocation bindings; the final X4Iostream gate passes
19/19 functions. Superseded manual wide cleanup wrappers are removed from
BfmeConv918.cpp, whose remaining three bodies also pass their scoped gate.
Cleanup ledger names are retained. Their replacement adds no conversion
bytes; the four former gen-dump initializers contribute 104 bytes.
