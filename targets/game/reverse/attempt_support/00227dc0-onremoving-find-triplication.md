# Task 48: onRemoving wrong_selected — find-template triplication vs ilt_guard

Queue rank 48: `?onRemoving@OpenContain@@UAEXPAVObject@@@Z` (0x227DC0, 525 B),
`wrong_selected` on `GarrisonContain_onRemoving.cpp` (383 B). Fifth investigation
(after queue #63/#73/#35 bids + this session); the natural fix verifies but the
pre-commit `ilt_guard` refuses it. Do not retry blind source variations.

## Verdict chain (proven)

- Provider `OpenContainOnRemoving.cpp` spells `map<Int,unsigned>` (`Rva002231C0RiderTimeMap`)
  and calls `find` at body offset +0x182/+0x183. Retail encodes ILT `0x26530`, whose E9
  stub lands `0x2231C0` (bytes `e98bcc1f00`, verified in the image).
- The ledger rowed the unsigned-find name at `0x195120` (71 B, PeerDefs emission, whose
  object-symbol is the `map<int,GameSpyStagingRoom*>` find). Census judge
  (`RetailTruth.addresses`) takes ledger rows first: expected `{0x195120}` vs retail
  `0x26530` -> `wrong`, hence `comdat`+`selected onRemoving (not retail's)` on both the
  provider and the GarrisonContain consumer.
- The same 71 bytes exist at THREE addresses: `0x195120` (row), `0x2231C0` (dup_ + pin),
  `0x473990` (dup_ + pin via ILT `0xF03D`). Retail bytes at all three verified identical.
  Four objects emit the COMDAT, all retail-verdict in the census index.

## Consumers (complete; `rg` over `game/`)

- `OpenContainOnRemoving.cpp`: unsigned-find -> retail ILT `0x26530` -> `0x2231C0`.
- `FontLibraryBFMERetail_getFont.cpp` (`bfmeFindRecord`): same name -> retail ILT `0xF03D`
  -> `0x473990` (per that pin's note).
- `ContainInsert2265F0.cpp` spells the pair type but only calls inlined `empty()`.
- `Rva00196C60.cpp` spells a different instantiation (nested-vector value) with its own
  pin at `0x195120`; unaffected by any row move.
- PeerDefs' own `m_stagingRooms.find` calls bind to its self-emitted COMDAT (no find
  verdicts at baseline). No other TU calls the Room-pointer find (five pair-type
  spellers checked; HordeContain's finds are on unrelated `set<int>` trees).

## Resolution mechanics (read from the tools, not guessed)

- Byte-gate (`build.py` REL32 resolver): row addresses first, then EVERY pin, per call
  site, first displacement reproducing retail wins. Both consumers pass the gate today
  and after every row move tried (2/2, 1/1, 2/2, 180/180 all green).
- Census judge (`link_census.RetailTruth`): ledger row SET if any row carries the name,
  else the FIRST pin only (`pins()` uses `setdefault`), plus `route=` targets.
  Stub-standing applies both directions (`_lands`).
- `route=` admissibility (`pin_consistency.route_verdict`): the stub target must already
  carry the pinned name. A `route=0x2231C0` pin at ILT `0x26530` was refused because
  `0x2231C0` is `dup_`-rowed. So with no row, the judge sees only `{0xF03D}`: FontLibrary
  would heal but onRemoving stays wrong. Moving the row to `0x2231C0` heals onRemoving
  (FontLibrary unchanged, still wrong) — zero-sum is unavoidable while the judge takes
  one address per name.

## The verified-but-refused fix (reverted)

1. `add_match ?dup_195120 0x195120` (`--correct-identity` + identity evidence): retires
   the refuted unsigned claim (zero unsigned-consumers call `0x195120`), keeps the
   Room-pointer object-symbol. PeerDefs still 181/181.
2. `add_match <unsigned-find> 0x2231C0` from `OpenContainOnRemoving.cpp`
   (`--replace-rva` + `--correct-identity dup_2231c0`; note: the dup name is undecorated
   `dup_2231c0`, the decorated guess is rejected): the TU's own unsigned-find COMDAT
   (object section 57, 71 B) was extracted and compared byte-identical to retail
   `0x2231C0`. TU gate 2/2 (onRemoving + find).
3. Observed `link_check` flips (live ledger, stale census otherwise): provider lost both
   `comdat` and `selected` onRemoving verdicts (3 unrelated unresolved remain);
   queue file lost `selected`, went `LINKED PREVIEW UNKNOWN` (0 -> 0 bytes, no gain
   claimed). PeerDefs and FontLibrary verdicts unchanged.

## The refusal: ilt_guard contradicts every instantiation at every address

Pre-commit `ilt_guard`: the unsigned-find name at `0x2231C0` is "outside every window
of the target's slots 30575:19159-19167". Direct oracle probes:

| name | 0x195120 | 0x2231C0 | 0x473990 | 0x4D7DE0 |
|---|---|---|---|---|
| map<int,unsigned> find | CONTRADICTED | CONTRADICTED | CONTRADICTED | — |
| map<int,Room*> find | CONTRADICTED | CONTRADICTED | CONTRADICTED | CONFIRMED (exact) |
| map<int,int> find | CONTRADICTED | CONTRADICTED | CONTRADICTED | — |
| map<int,long> find | — | CONTRADICTED | — | — |

(p_false ~4-6e-4 each; 8 probes, expected-false ~3e-3 — a legitimate small search.)
The donor (`inputs/reference/open-bfme-2` beed8a16, `Contain/OpenContainOnRemoving.cpp`)
was transferred FROM BFME1 and uses a signed int-word lookup, but int-find is
contradicted too, so the donor offers no committable spelling either.

## Unblocking conditions (verifier/oracle lane, not link lane)

- The three 71 B bodies look like incremental-link re-materializations of one template:
  one hash-table entry, three addresses across links; the oracle's one-slot window
  cannot name any of them. Options: oracle exemption/secondary-slot model for
  multi-address identical bodies; or candidate-set judging (ledger set + all pins)
  instead of first-pin; or per-consumer resolution.
- Until then: keep `dup_` on the unprovable addresses, keep pins as the byte-gate's
  candidates, and do not re-attempt row moves or consumer respells — the TU already
  self-emits the find (same-object binding does not dodge name resolution either).
- FontLibrary's `bfmeFindRecord` (0xF03D provider) is the documented remainder on the
  other side of the same name; any future per-consumer design must serve both.

Re-logged as `blocked "false-reject ilt_guard"` on `?onRemoving@OpenContain` 0x227DC0.
t=~120 model=muse-spark-1.3.
