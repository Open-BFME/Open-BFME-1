# Exported Coord3D float constructor at 000642F0

Retail baseline SHA256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

Independent raw PE export parsing by ENGINE and math proves ordinal 221 names `??0Coord3D@@QAE@MMM@Z`. Its RVA `000156C7` contains `E9 24 EC 04 00`, routing to `000642F0`. The body is 25 bytes, followed by INT3 padding:

`8B 54 24 08 8B C1 8B 4C 24 04 89 08 8B 4C 24 0C 89 50 04 89 48 08 C2 0C 00`.

It copies three incoming words into this+0/+4/+8, returns this in EAX and pops 12 bytes. The export independently establishes the float constructor identity; bitwise MOV instructions alone would not distinguish the integer constructor shapes.

Retail has no identical-COMDAT folding. Under docs/naming_evidence.md, retire exactly these three unsupported competing rows at 000642F0/25 with evidence tombstones:

- `??0BlockHeader@TagBlockFile@@QAE@HHH@Z`, tagblock.cpp.
- `??0ResolutionDescClass@@QAE@HHH@Z`, dxwrapper.cpp.
- `??0Vector3i@Strip@@QAE@HHH@Z`, stripoptimizer.cpp.

None of those exact names has a raw PE export or an explicit symbols.csv/dir32_addresses.csv pin. Their source definitions and every other row remain intact. Their actual retail addresses are unknown; no replacement address, identity, alias or pin is invented.

The true Coord3D row retains its name, export route, extent and status. Its unchanged natural inline provider in ParticleSystemComputeParticleVelocity.cpp emits the exact 25-byte body with zero relocations (COFF section 3); only the redundant strong definition in coord3d.cpp is removed. No header, forced helper, generated source or other donor definition changes.

All five affected sources passed 187/187 rows before retirement, with 234 literals, 28 constants, 447 DIR32 checks and one data row. Current frozen a23092df4e joint baseline: coord3d24 blockers, Particle provider5, tagblock7, dxwrapper123; stripoptimizer links134 bytes. The three deleted rows contribute no unique retail coverage because the true constructor covers the same25 bytes. Removing the unsupported linked stripoptimizer row may reduce scoped linked accounting by25 bytes; that is correction of ownership accounting, not erased source or lost unique retail coverage.

Surviving-use audit: raw executable E8 scan finds no direct call to either642F0 or its ILT156C7. Current tagblock/dxwrapper/stripoptimizer COFF relocations to each exact retired three-integer constructor name occur only in .debug$F metadata, not code or data. Source constructor uses remain inline and untouched; no callable pin or ledger route silently binds these names to642F0. The unsupported original standalone names remain unresolved identities.

After retirement, all184 remaining rows across the five sources pass with the same234 literals,28 constants,447 DIR32 references and one data row. identity_guard requires lowering one_identity.surplus2502 to2499; this is the exact three-row retirement and no other baseline change.

Final current joint refresh: coord3d24->23 blockers, Particle provider5->4, tagblock7->7, dxwrapper123->123, stripoptimizer remains clean. Scoped linked accounting is134->109 bytes, delta **-25 bytes**, entirely the retired unsupported Strip::Vector3i claim. No other source gains or new blockers are attributed; the true25-byte constructor remains byte-verified in its natural ParticleSystem provider.
