# Batch-2 queue triage: 1 solve, 9 evidenced blocks (2026-11-11)

Solved and pushed: `54d155c7a9` (dir32 `0x00C6B810` piChannelUserChangedNickA respell).

## New evidence (produced this session, not in the ledger)

### 1. name_lane pre-commit check never accepts recorded C/C++ names
`tools/name_lane.py check --staged` builds `allowed` from EA-doc words,
retail imports, header-declared names, and WORDS scraped from symbols.csv +
dir32_addresses.csv. Two defects make recorded names invisible:
- C names: the scrape keeps the COFF underscore (`_piChatDisconnectedA`)
  but C sources spell them bare (`piChatDisconnectedA`) → never matches.
- C++ names: `\b[A-Za-z_]\w*\b` cannot match inside `??0Foo`/`?Foo@@...`
  because the leading `?`/digit glues to the name (no word boundary).
Net: placeholder→recorded-name respells ALWAYS fail the hook (observed on
StructureCollapseFXVector/OCLVector, piChatDisconnectedA,
piChatPrivateMessageA — all reverted). Non-placeholder→non-placeholder
respells pass (observed: piUserChangedNickCallback →
piChannelUserChangedNickA landed). `muse-spark` is rejected by
`model_id()`, so lane submission is closed to this worker; `name_votes.csv`
and `name_agreed.csv` contain no votes for the mappings above.

### 2. Rva008B5940Lookup.cpp is dup-fragile (do not edit yet)
Respelling `Callback00CB5760/70` to the matched `Rva008B5760Get` /
`rva008B5770NamedProperty` (rows exist, 6B/265B matched) breaks three
`?dup_00C58xxx` funclet attributions in the same TU (A/B build: pristine
4/4 OK, edited 3/4 FAIL on `$L408/409/410` ambiguity; baseline deletion
ruled out as cause by source-only rebuild). The three callback bodies
themselves are DONE (aptPlay 53B, Rva008B5760Get 6B,
rva008B5770NamedProperty 265B, all matched). Unblock: convert the dup
scaffolds to real bodies first.

### 3. AsciiString default-ctor `0x00417BD9` referrer hunt (repair line 38 area)
`??0BFMERetailAsciiString@@QAE@XZ` is absent from WaterRenderObjConstructor's
object (it already uses recorded `??0AsciiString`) — that TU is exonerated.
The symbol IS referenced by 10+ other objects; the `0x00417BD9` site needs
per-file retail comparison to identify. Candidate objects contain the
spelling (grep `build/match/*.obj` for the mangled name).

### 4. WaterSetting dtor debt contradicts 3 matched rows
All `WaterSetting`-spelling TUs build DIR32-clean; the only live
`??1WaterSetting` references are Water.obj's own vtable slot/definition.
Retail reads `0x0043D4B0` (`_bfmeDtorDAB`) where our vtable points at our
`??1WaterSetting` (`0x0045CC80`, matched with `??0WaterSetting` 174B and
`??_GWaterSetting` 30B). A naive respell breaks the matched rows: needs
vtable re-verification, not a rename.

### 5. Link queue is systematically stale
Ranks 10, 12, 16, 17 each verified to a single retail-proven definition
that already sorts first in link order (e.g. rank 10's 35B dtor in
Rva00784A70Cleanup.cpp; rank 12/16/17 consumers are declare-only). The
census (90c15cdeca) predates the fixes. No source change can retire these;
needs `link_check --refresh` (≈649 stale objects).

## Queues confirmed dry for quick solves
carved/structural/reloc/lift/similar tiers (12–374 prior verdicts or
no-identity unwind fragments), land_ambiguous (0/30 landed), ea_queue
(empty), WorldBuilder (no source tree, no ledger rows), bfme2 exact-unique
(needs full ports; scan refreshed: 52,585 bodies).
