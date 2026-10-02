# 0x007CC430 is MaskTextureShader::set(int)

The native shader registration, matched dispatcher and independently named reset
slot establish identity. The 1,267-byte SEH rendering body remains a dump.
All code addresses are retail RVAs; explicitly labelled VAs include image base
0x00400000. Values/instructions were cross-checked with retail-1.03-unpacked PE
and Capstone; Ghidra's `6E A7 44 00` search independently finds VA `0x011288BC`.

## Native object and table

Only ILT `0x0004A76E` directly reaches this body. Its stub VA `0x0044A76E`
occurs at VA `0x011288BC`, slot 0 of this four-slot shader interface table:

| Slot | Stub RVA | Body RVA | Independent identity |
|---:|---:|---:|---|
| **0** | **0x0004A76E** | **0x007CC430** | this set implementation |
| 1 | 0x000232DB | 0x007CCA60 | matched MaskTextureShader::reset |
| 2 | 0x0001458D | 0x007CC3D0 | native one-pass initializer |
| 3 | 0x00043F77 | 0x007C33F0 | shared shutdown-shaped return |

Matched opaque constructor RVA `0x007CC420` stores this table at receiver offset
zero (immediate at `0x007CC424`). The static instance at VA `0x012BC080` also
contains that vptr in retail data. No deleting-destructor slot is assumed: this
shader interface declares set, reset, init, shutdown in that order.

## Registration and matched dispatch

The 21-byte initializer `0x007CC3D0` stores instance VA `0x012BC080` into
VA `0x012F9CA0` at `0x007CC3D5`, stores pass count 1 into VA `0x012F9C58` at
`0x007CC3DF`, then returns. These are index 6 in the native shader array and
parallel pass-count array respectively.

Independently matched `W3DShaderManager::setShader`, RVA `0x00716980`, loads
`[shaderIndex*4+0x012F9C88]` at `0x0071699E`. For index 6 this is exactly the
initializer's VA `0x012F9CA0`. It pushes the caller's pass value at `0x007169B6`
and calls virtual slot 0 at `0x007169B7`. Thus this table's first slot is the
native set implementation taking one integer pass argument.

The shipped-reference ShaderTypes order names index 6 `ST_MASK_TEXTURE`, and
W3DShaderManager.cpp declares `MaskTextureShader::init` registering the same
single-pass instance in that slot. Its independently byte-matched reset body
at `0x007CCA60` is in the canonical `W3DShaderManager.cpp` TU, beside the
MaskTextureShader declaration. This owner witness is independent of the
candidate body's name. The sibling FlatShroudTextureShader::set at
`0x007C4970` and FlatTerrainShader2Stage::set at `0x007C5690` are already
matched implementations of the same interface slot.

## Conclusion and scope

The proven spelling is `?set@MaskTextureShader@@EAEHH@Z`, a private virtual
returning int and taking int. Native final RET 4 at `0x007CC920`, followed by
INT3 at `0x007CC923`, establishes 1,267 bytes. No row, pin or production source
is changed here. Future clean conversion belongs in the existing canonical
`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp` TU,
whose readable MaskTextureShader::set body is currently present-unmatched.
