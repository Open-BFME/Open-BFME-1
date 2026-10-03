# TerrainShaderPixelShader::set — RVA 0x007E2180

Retail extent is 2531 bytes: entry 0x007E2180; common ret 4 epilogue and cold single-noise/base-only tails end with the jump at 0x007E2B5E, followed by INT3 at 0x007E2B63. Decode against retail-1.03-unpacked.

## Identity

Zero Hour W3DShaderManager.cpp supplies TerrainShaderPixelShader::set: base texture stages 0/1, view inverse, terrain noise modes, noise1/noise2 texture transforms, and the three shader handle members. BFME vtable VA 0x01128D00 slot 0 contains stub VA 0x00414178 -> body 0x007E2180. Matched ctor RVA 0x007E2170 installs this table. Slot 1 contains stub VA 0x0043C19B -> already-matched TerrainShaderPixelShader::reset at RVA 0x007E2020 (187 bytes), independently corroborating the family owner. Slot 2 uses stub 0x0043311D -> init body 0x007E1F60. Ghidra and raw retail independently show that init loading shaders\terrain.pso, shaders\terrainnoise.pso, shaders\terrainnoise2.pso into this+8, +0xC, +0x10. The strings are at VA 0x01128CE8, 0x01128CC8, 0x01128CA8. These agree with the ZH family and set's three handle reads. No constructor or sibling identity is changed here.

## BFME differences and ABI

BFME uses device vtable slots 44/45 for transforms, 65 for texture binding, 67 for texture-stage state, 69 for sampler state, 107 for pixel shader, 109 for its constants. The local address-qualified interface view represents those observed slots, without modifying the shared D3D8 shim. Sampling states are uncached; texture-stage states retain their snapshots and cache. Transform counters update before the native call.

The six bfmeGet calls return an owning one-pointer handle through hidden sret. Getter 0x0090DC60 receives the handle address, loads its contained pointer, and returns null for a null handle; release 0x009EB7A0 has thiscall/no-stack-args ABI and the 16-bit reference decrement with conditional virtual tail. Existing TU handle/getter/release declarations are reused, without adding identities or pins. updateNoise1 and setTerrainTextureFilters use existing declarations. The noise2 calls through ILT RVA 0x000051FF use the already-matched `Rva007DCF00TextureMatrix::build(Rva007DCF00Matrix *, Rva007DCF00Matrix *, bool)` at RVA 0x007DCF00. Its native ret12, matrix input/output accesses and complete 281-byte body corroborate the three-stack-argument thiscall ABI; the existing opaque identity is retained. The already-matched FlatTerrainShader2Stage::set at 0x007C5690 independently uses this same declaration and route; its TU-local declaration is moved above both callers. No extra pin or callee identity is introduced.

The full-noise path broadcasts a float from TheWritableGlobalData+0x48, or literal float zero (VA 0x01075350) when null, into pixel constant 0. name_oracle has no BFME witness for +0x48, so the offset remains explicit; the ZH field hint is not asserted as a name. The snapshot constructor at body+0x757 needs its pointer read before the terminator read; local ordered volatile reads preserve that witnessed order. Other TU bodies keep their existing helpers.

## Verification

Standalone compiler object measured 2531/2531 bytes with zero differences outside all 218 relocation sites. After correcting the call to the existing opaque matrix-helper identity, add_match passed the scoped build: 45/45 functions, 871 DIR32 address references, 12 string literals and 25 float constants; no skipped string references. No assembly, generated-source changes, shared header edits, or baseline expansion.
