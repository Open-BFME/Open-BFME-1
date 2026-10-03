# Weather parser initializer correction (2026-10-03, v3)

Matched `INI::parseWeatherDefinition`, RVA0045B130/306B, passesVA010F6540 at operand+E2. Ghidra and the unpacked PE independently agree on the complete400-byte table and310-byte body/padding window. The normal return is0045B23E; the complete claimed extent ends with nonreturning CxxThrowException call0045B25D..0045B261, followed byINT3 at0045B262.

The old source table had13entries plus terminator (224B). Retail has24plus terminator (400B). SnowBoxDimensions/SnowBoxDensity/SnowVelocity were wrong serialized keys; retail spells SnowBoxHeight/SnowSpacing/SnowSpeed. The eleven later entries were missing. The existing scoped Snow.h already models all required fields at the actual offsets; no layout, header, semantic member name, pin or function identity changes are needed.

| Retail key | Offset | Callback VA | Callback body RVA |
|---|---:|---:|---:|
| SnowTexture | 0xC | 0xc51ee0 | 0x851ee0 |
| SnowFrequencyScaleX | 0x10 | 0xc52b20 | 0x852b20 |
| SnowFrequencyScaleY | 0x14 | 0xc52b20 | 0x852b20 |
| SnowAmplitude | 0x18 | 0xc52b20 | 0x852b20 |
| SnowPointSize | 0x1C | 0xc52b20 | 0x852b20 |
| SnowMaxPointSize | 0x20 | 0xc52b20 | 0x852b20 |
| SnowMinPointSize | 0x24 | 0xc52b20 | 0x852b20 |
| SnowQuadSize | 0x28 | 0xc52b20 | 0x852b20 |
| SnowBoxHeight | 0x2C | 0xc52b20 | 0x852b20 |
| SnowSpacing | 0x30 | 0xc52b20 | 0x852b20 |
| SnowSpeed | 0x34 | 0xc52b20 | 0x852b20 |
| SnowPointSprites | 0x38 | 0xc52e00 | 0x852e00 |
| SnowEnabled | 0x39 | 0xc52e00 | 0x852e00 |
| IsSnowing | 0x3A | 0xc52e00 | 0x852e00 |
| NumberTiles | 0x3C | 0xc52a60 | 0x852a60 |
| LightningEnabled | 0x40 | 0xc52e00 | 0x852e00 |
| LightningFactor | 0x44 | 0x436615 | 0xb8f60 |
| LightningDuration | 0x50 | 0xc52a60 | 0x852a60 |
| LightningChance | 0x54 | 0xc52b20 | 0x852b20 |
| SpellEnabled | 0x58 | 0xc52e00 | 0x852e00 |
| SpellDuration | 0x5C | 0xc52a60 | 0x852a60 |
| RampControl | 0x60 | 0xc533e0 | 0x8533e0 |
| RampSpacing | 0x70 | 0xc533e0 | 0x8533e0 |
| RampSpeed | 0x68 | 0xc533e0 | 0x8533e0 |

Every user-data word is zero; the final16bytes are zero. Callbacks retain existing canonical INI signatures. The two nontrivial additional callback families are parseGameClientRandomVariable at000B8F60 and parseCoord2D at008533E0, independently reached through the actual table pointers/ILT routes. Serialized key names do not introduce or rename C++ members.

AGENTS.md requires real source and byte verification. docs/matching.md Relocations requires checking what references point at. The ordinary code gate passed before this repair; it did not validate the complete initializer.

Validation: final scoped build passes10/10source claims, two complete code literals and30recorded DIR32 sites. A separate read-only COFF/retail comparison uses the direct+E2operand and the exact array window (not the surrounding shared .rdata section). It verifies24complete pointed-to strings,24named callback bindings following E9routes, every nonrelocation byte, and the zero terminator. All agree. The old224Bwindow has seven nonrelocation byte differences and three wrong string references; its eleven missing entries are additionally established by the array extents.

Evidence artifacts: build/audit_v3/s4_weather_raw.json, s4_weather_table_proof.json, s4_weather_table_verify.py and s4_weather_build.log. An initial adapter assumed the array began at section offsetzero and stopped at that assertion; only the corrected symbol-offset/array-window comparison is evidence.
