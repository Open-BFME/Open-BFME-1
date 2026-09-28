# CRT init-table dynamic initializers misnamed as Initialize functions

10 retail bodies in `0x00C6DF70-0x00C6E1D0` were landed as ordinary named
functions `?bfmeRva<RVA>Initialize@@YAXXZ`. That identity is false: each body
is the compiler-generated dynamic initializer for a namespace-scope global,
which MSVC 7.1 emits with no mangled name as `_$E<n>` in `.text$yc` (plus an
`atexit` cleanup registration). The CRT init table calls the `$E` stub, not a
named function. Relanding each as `?Rva<RVA>Init@@YAXXZ` with
`object-symbol=_$E1`, with the source defining the global so the compiler
emits the same bytes.

Evidence per body (retail disassembly via `tools/dis_retail.py`): no
one-time guard bit; `mov ecx, <global>` + ctor call + `push <cleanup>` +
`call _atexit`. Single-global TU, so the initializer is `_$E1`.

Precedent: `?bfmeInitBoxYP@@YAXXZ` at `0x00C6C350` (`object-symbol=_$E1`,
global defined with its initializer in `BfmeBoxInitYP.cpp`); the
`?Rva00C704AxFxAtexitThunk@@YAXXZ` family (`object-symbol=_$E2`, one
address-derived ledger name per TU-local `$E` label).

| RVA | size | global VA | ctor callee | cleanup |
|---|---|---|---|---|
| 0x00C6DF70 | 24 | 0x01346DB0 | `??0?$SimpleDynVecClass@PAVVertexMaterialClass@@@@QAE@H@Z` 0x0092D6B0 (decalmsh.cpp) | 0x00C712D0 |
| 0x00C6DF90 | 26 | 0x01346DC0 | `??0?$DynamicVectorClass@VVector3@@@@QAE@IPBVVector3@@@Z` via thunk 0x0002A40A (hmdldef.cpp) | 0x00C712E0 |
| 0x00C6DFB0 | 22 | 0x01346E70 | `?m@Gen_0044f3c0@@QAEPAXXZ` via thunk 0x000110D6, inlined member call | 0x00C712F0 |
| 0x00C6E010 | 26 | 0x01346E78 | `??0?$DynamicVectorClass@UTextureStatisticsStruct@@@@QAE@IPBUTextureStatisticsStruct@@@Z` 0x00937FB0 (TextureStatisticsVector.cpp) | 0x00C71310 |
| 0x00C6E070 | 26 | 0x0134B170 | `??0?$DynamicVectorClass@VVector3@@@@QAE@IPBVVector3@@@Z` via thunk 0x0002A40A | 0x00C71470 |
| 0x00C6E090 | 26 | 0x0134B158 | `??0?$DynamicVectorClass@VVector3@@@@QAE@IPBVVector3@@@Z` via thunk 0x0002A40A | 0x00C71460 |
| 0x00C6E0B0 | 26 | 0x0134B188 | `?bfmeInitAWA@BfmeThingAWA@@QAEPAV1@PAX0@Z` 0x0094E2B0 (BfmeConv427.cpp), inlined two-arg call | 0x00C71480 |
| 0x00C6E0D0 | 26 | 0x0134B1A0 | `??0?$DynamicVectorClass@K@@QAE@IPBK@Z` 0x0094E490 (meshmdl.cpp) | 0x00C71490 |
| 0x00C6E120 | 22 | 0x0134B1B8 | `??0SegLineRendererClass@@QAE@XZ` 0x0095FFD0 (seglinerenderer.cpp) | 0x00C714A0 |
| 0x00C6E1D0 | 22 | 0x0134ECF0 | `??0SimpleFileFactoryClass@@QAE@XZ` 0x009DD6C0 (ffactory.cpp) | 0x00C71550 |

All callees are independently matched ledger rows or pinned ILT thunks to
them (`tools/callees.py`). The `atexit` argument is a masked DIR32 slot; the
TU-local `_$E2` destructor helper it names carries no identity.
