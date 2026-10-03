# GameLOD parser table windows (v3, 2026-10-03)

The old source's early terminators and null priority-name pointers are positively
contradicted by the unpacked BFME1 image. This repairs data used by three existing
INI parsers, without changing their names, extents, or shared headers.

## Independently established lookup boundary

Ghidra decompilation and a separate Capstone decode of retail RVA00850880 agree:
EAX supplies the table; +08/+0C loads its first key and tests for zero; on a
nonmatching key, 008508BF loads [EDI+10], 008508C2 advances EDI by16, and
008508C5/C7 tests the new key and loops. There is no record-count argument.
At a null key, 008508C9 reads the callback at+4. A nonnull callback is a default
handler; a null callback returns no match. Thus the entire zero-key record need
not be all zero (relevant to the separate Armor audit).

The three callers invoke INI::initFromINI at RVA008520A0, whose native wrapper
passes their table through to 00851910; that parser invokes the above lookup.
The multi-table list count is a count of table pointers, not FieldParse entries.
This distinguishes lookup termination from accidental neighboring-data scanning.

## Retail windows and old contradictions

| Existing parser | RVA/size | Direct table VA | First record | Final RET / following INT3 |
|---|---|---|---|---|
| INI::parseStaticGameLODDefinition | 0007CEC0/191 | 01076760 | 0 | 0007CF7E / 0007CF7F |
| INI::parseDynamicGameLODDefinition | 0007D470/191 | 01076890 | 19 | 0007D52E / 0007D52F |
| INI::parseAudioLODDefinition | 0007D560/209 | 010768D0 | 23 | 0007D630 / 0007D631 |

Static records0..18 flow straight into dynamic records19..22, which flow into
audio records23..25. The only zero-key terminator is record26 at VA01076900.
The whole shared window is432 bytes. Ghidra read_memory and the independent PE
read agree on all432 bytes. The prior source inserted zero records at19 and23,
so it stopped before keys retail still searches. Preserve the observed lookup
behavior, even if the original arrangement was unintended.

The static MinParticlePriority and MinParticleSkipPriority entries additionally
carry userData VA01110208, whereas source stored NULL. This address is the
15-pointer ParticlePriorityNames list: NONE, WEAPON_EXPLOSION, SCORCHMARK,
DUST_TRAIL, BUILDUP, DEBRIS_TRAIL, UNIT_DAMAGE_FX, DEATH_EXPLOSION, SEMI_CONSTANT,
CONSTANT, WEAPON_TRAIL, AREA_EFFECT, CRITICAL, ALWAYS_RENDER, NULL. Every complete
string including its NUL matches the already included GeneralsMD declaration.
This is an in-exe name-table witness, not a guessed layout or member identity.

## Repair and verification

Keep the established static table as the shared432-byte storage. Preserve the
dynamic and audio entry-window names as const pointers at records19 and23.
Use the existing ParticlePriorityNames array for both nonnull userData slots.
No shared layout/enum/header is changed, and no ledger/data-row coverage added.

The ordinary scoped build verifies131/131 existing source claims, two code
literal references and22 anchored DIR32 references. A separate bounded COFF/PE
comparison follows all three compiled parser operands, including their addends,
to the same storage. It verifies26 complete key strings,26 callback bindings,
both complete15-slot priority lists, every remaining scalar byte, and the final
16-byte zero record. parseStaticGameLODLevel's callback ILT004497BF reaches the
existing0007BCF0 body; other callbacks are parseInt00852A60, parseReal00852B20,
parseBool00852E00 and parseIndexList00851050. No new callback alias is invented.

Reproduction artifacts: build/audit_v3/s5_gamelod_verify.py,
s5_gamelod_proof.json, s5_gamelod_before.cpp/.obj and s5_gamelod_build.log.
Function-byte matches alone did not prove these initializers; this extra bounded
reference proof is required by docs/matching.md's relocation rule.
