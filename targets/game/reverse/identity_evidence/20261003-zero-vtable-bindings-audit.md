# Zero stores masked as vtable addresses (2026-10-03, v3)

Existing tools/null_reloc.py explicitly rejects source vtable relocations that mask literal-zero retail stores. That check began at4c85b408e3 on2026-08-29 (46.27% retrospective rebuildable coverage); its baseline/unreadable limits permit old debt. The bounded current-object audit independently confirms14such claims across two bodies, plus the separately documented AudioManager table-getter return10. All14vtable claims survive theAugust1old cohort.

No real owner is inferred here. Byte equality after replacing an immediate with a vtable address does not prove a virtual constructor. AGENTS.md also forbids ICF-derived duplicate identities.

## RVA00061D90 — 9bytes

Retail/Ghidra bytes: `8B C1 C7 00 00 00 00 00 C3`, thenINT3. MOV EAX,ECX; store literal0 at[EAX]; RET at61D98, padding starts61D99. Five current source claims place a vtable DIR32 at+4.

## RVA00087A50 — 18bytes

Retail/Ghidra bytes: `8B C1 8B 4C 24 04 C7 00 00 00 00 00 89 48 04 C2 04 00`, thenINT3. It stores literal0 at[EAX], copies the argument to[EAX+4], returnsEAX and RET4 at87A5F; padding begins87A62. Nine current source claims place a vtable DIR32 at+8.

## Confirmed current claims

| RVA | Existing row | Compiled vtable symbol |
|---|---|---|
| 0x00087A50 | `??0?$BlitPlainXlat@E@@QAE@PBE@Z` | `??_7?$BlitPlainXlat@E@@6B@` |
| 0x00087A50 | `??0?$BlitPlainXlat@G@@QAE@PBG@Z` | `??_7?$BlitPlainXlat@G@@6B@` |
| 0x00087A50 | `??0?$BlitTransRemapDest@E@@QAE@PBE@Z` | `??_7?$BlitTransRemapDest@E@@6B@` |
| 0x00087A50 | `??0?$BlitTransXlat@E@@QAE@PBE@Z` | `??_7?$BlitTransXlat@E@@6B@` |
| 0x00087A50 | `??0?$BlitTransXlat@G@@QAE@PBG@Z` | `??_7?$BlitTransXlat@G@@6B@` |
| 0x00087A50 | `??0?$RLEBlitTransRemapDest@E@@QAE@PBE@Z` | `??_7?$RLEBlitTransRemapDest@E@@6B@` |
| 0x00087A50 | `??0?$RLEBlitTransXlat@E@@QAE@PBE@Z` | `??_7?$RLEBlitTransXlat@E@@6B@` |
| 0x00087A50 | `??0?$RLEBlitTransXlat@G@@QAE@PBG@Z` | `??_7?$RLEBlitTransXlat@G@@6B@` |
| 0x00061D90 | `??0AggregateLoaderClass@@QAE@XZ` | `??_7AggregateLoaderClass@@6B@` |
| 0x00061D90 | `??0ChunkInputStream@@QAE@XZ` | `??_7ChunkInputStream@@6B@` |
| 0x00087A50 | `??0CullLinkClass@@QAE@PAVCullSystemClass@@@Z` | `??_7CullLinkClass@@6B@` |
| 0x00061D90 | `??0FileFactoryClass@@QAE@XZ` | `??_7FileFactoryClass@@6B@` |
| 0x00061D90 | `??0InputStream@@QAE@XZ` | `??_7InputStream@@6B@` |
| 0x00061D90 | `??0ParticleEmitterLoaderClass@@QAE@XZ` | `??_7ParticleEmitterLoaderClass@@6B@` |

Each source object has an ordinary current receipt or an exact unchanged object hash from a completed fresh-input audit; the relocation target is local initialized .rdata and its addend lies within that data. Ghidra independently agrees with both complete retail bodies and following padding. Neither zero is an __except_list/TIB offset.

These are positive data-binding contradictions, not merely unproven names. Remove or rehome each contradicted semantic claim only with its own actual caller/vtable evidence. Do not mass-rename other claims on these addresses or infer the real owner from the stores. Ledger edits remain blocked locally by held inherited aliases003C8340/00803080. No source, pin, ledger or baseline change is included.

Raw evidence: build/audit_v3/s4_zero_vtable_raw.json, s4_local_address_audit.json. The first address-audit harness stopped at a relocation beyond a short claim; the corrected pass bounds every operand to the claimed bytes, matching the existing verifier treatment of later functions sharing a COMDAT section. Out-of-claim relocations are counted/excluded, not new extent findings.
