# Water shader literal correction

The existing 891-byte WaterRenderObjClass::ReAcquireResources claim at RVA
`0x007A0500` contains two DIR32 string operands, offsets `+0x255` and `+0x275`,
that both point to VA `0x01127D90`. The final RET is at RVA `0x007A087A`,
followed by INT3 padding. Its existing identity and extent are unchanged.

The old source literal is 188 bytes including NUL. Retail contains 209 bytes:
after `add r0.rgb, r0, r1\n` it has three tabs and the additional instruction
`+mul r0.a, r0, c1\n`, then NUL. The omitted 21 bytes therefore include an
alpha multiplication, not just trailing whitespace. Ghidra read_memory and
the unpacked PE agree on the complete literal.

The earlier verifier stripped all trailing NULs and only compared the
remaining source prefix. Both shortened shader references passed that check.
`docs/matching.md`, Relocations, requires the referenced literal to byte-equal
retail; accepting a prefix did not enforce that requirement.

Restore the missing source line with its exact three-tab indentation and
newline. The normal scoped gate now passes the unchanged 891-byte body,
eight complete string references, and four external DIR32 references. A
separate COFF-to-retail comparison checks both operand addresses and all 209
literal bytes through the terminator. No new names, pins, claims or extents
are introduced, and there is no additional function-byte coverage.
