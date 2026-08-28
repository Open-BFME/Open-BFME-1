# Readability drain: Tier 0 and Tier 1 to exhaustion

Audit and measurements: `Legibility Ledger` artifact, 28 Aug 2026, at `402b2ea`.
All figures below were measured on this tree; the spikes cited ran green and were
reverted.

## What we are draining

| Lane | Work items | Evidence source | Ledger cost |
|---|---|---|---|
| T0-fields | 1,326 struct members at proven offsets | binary `FieldParse` × upstream `offsetof` | none (but full gate: they live in headers) |
| T0-vocab | 4,267 functions (1,010,142 B) whose upstream body names every local | `reference/CnC_Generals_Zero_Hour` | none |
| T1-merge | 922 files → 177 TUs | `// readable body of …: DEST` comments | 1 row per moved fn |

T2 is dropped. The `FieldParse` vote names 87 classes and effectively all of them
are already declared under that name somewhere in `Code/` or `reference/shims/`;
the vote confirms identities rather than discovering them. The 18,426 anonymous
functions remain an open investigation, not a drain, and are out of scope.

**The phases in `plans/` supersede this document.** It is the brainstorm; where
the two disagree, `plans/` is what was validated.

## Architecture

```
                    lotrbfme.exe                reference/CnC_Generals_Zero_Hour
                         │                                    │
              FieldParse tables                    offsetof(Class, m_member)
              (296, 4116 entries)                  + real function bodies
                         └──────────────┬─────────────────────┘
                                        │ join on the INI key string
                                        ▼
                            tools/fieldnames.py  ──► reverse/field_names.csv
                                        │                    (checked in, regenerable)
                    ┌───────────────────┼───────────────────┐
                    ▼                   ▼                   ▼
              T0 appliers          T1 merge_cluster     T2 class rename
              (agent edits)        (file surgery)       (row + pins)
                    └───────────────────┼───────────────────┘
                                        ▼
                        .githooks/pre-commit  ── the only gate that matters
                          ├── conversion_gate.py
                          ├── check_csv.py --staged
                          ├── pin_consistency.py --check
                          └── ./build.sh <scoped files>
                                        ▼
                        tools/readability_metric.py  ──► commit trailer
```

## Rejected: `tools/header_scope.py`

Proposed as an enabler, then cut. Three measurements killed it:

1. **Only 1 of the last 299 commits touched a `.h` (0.3%)**, and this drain is
   `.cpp`-only by construction — merge-only T1 never creates or edits a header.
2. `to_compile` in `tools/build.py:1348` is the **post-cache** set, so a narrow
   header already recompiles ≤8 TUs and takes no lock. The lock only bites for
   widely-included headers.
3. Fatally: inverting `.deps.json` to answer "which TUs include header X?" is only
   sound if every sidecar is current. `compile_is_current` (`build.py:711-731`)
   trusts a sidecar only after checking its `cmd` fingerprint, `source` hash and
   every dep hash. A stale-but-parseable sidecar records the **old** include set,
   so a `.cpp` that has gained `#include "Foo.h"` since its last compile would be
   silently skipped — exactly the regression the blanket rule exists to prevent.
   Under a continuous fan-out, stale sidecars are the normal state.

Kept here as a record so it is not re-proposed. The original sketch follows.

### Original sketch (do not implement)

`.githooks/pre-commit:64` forces `./build.sh` (whole tree) for any `*.h` or
`reference/shims/*` change. `tools/build.py:1348` takes a host-wide exclusive
lock whenever a build compiles more than 8 TUs.

`build/match/*.deps.json` already records every TU's full include set from
`cl /showIncludes` — 4,936 sidecars, 1,460 distinct included files. **837 of
those 1,460 headers are included by ≤8 TUs**, i.e. below the lock threshold.

New rule:

```
*.h staged
  └─ every ledger source → obj_path() → .deps.json      (reuse build.py's own
     │                                                    encoder; the sidecar
     │                                                    stores source as a
     │                                                    HASH, not a path)
     ├─ any sidecar missing or unparseable  → FULL GATE, loud
     ├─ dependent TU count > 8              → FULL GATE, loud
     └─ otherwise → ./build.sh <those TUs>, no lock, seconds
```

No silent fallback: every path to the full gate prints why.

### Red / green

- **RED** — `tools/tests/test_header_scope.py` writes a fixture header, a TU
  that includes it, and a sidecar; shifts a member offset in the header so the
  emitted bytes change; asserts the scoped gate **fails**.
- **RED** — deletes the sidecar; asserts the tool returns `full` and prints the
  reason, rather than verifying zero TUs and passing.
- **RED** — synthesises 9 dependent TUs; asserts `full` (lock threshold).
- **GREEN** — restores the header; asserts the scoped gate passes and selected
  exactly the expected TU set.
- **GREEN, once, on the real tree** — after the first real header lands, run
  `./build.sh` with no arguments and confirm green.

## `tools/readability_metric.py`

Each commit must carry the metric it moved. The audit's `bri.py` re-reads all
8,827 files and exceeded 10 minutes under load — unusable per commit. Reading
every file costs 0.9 s, so the cost is the scanning, not the I/O.

Cache per-file counters keyed by git blob hash under `build/readability/`;
recompute only files whose hash changed. A commit touching 20 files then costs
well under a second.

Six axes, unchanged from the audit: Body, Ident, Types, Iface, Local, SSoT.

Emits one line for the commit message:

```
readability: Local 33.0 -> 33.4 (+0.40 pp), SSoT 21.0 -> 21.2, files -18
```

### Red / green

- **RED** — fixture tree with a known-bad file; assert each axis returns the
  hand-computed value. Corrupt the cache with a stale hash; assert it
  recomputes rather than trusting the cache.
- **GREEN** — run twice with no edits; assert identical output and that the
  second run reads zero files.
- **GREEN** — apply a known edit (split one `char pad[N]` into two named
  fields); assert only Types moves, and by the predicted amount.

## `tools/merge_cluster.py` — the T1 driver

Already prototyped during the audit. Does every step that is not a judgement
call, and deliberately **does not** synthesise the merged body — a guessed union
of shims byte-matches while being wrong.

- `--list` — destinations with ≥2 files, largest first (177 clusters)
- `--plan DEST` — the cluster's files, declarations common to all (free to
  hoist), and declarations needing reconciliation
- `--apply DEST --into PATH` — repoint ledger rows **binary-safe** (a
  `csv.writer` round-trip converts CRLF to LF and `check_csv` rejects it),
  delete originals, `git add` the merged file

The merged TU never touches a `.h`, so this lane stays on the 3-second scoped
path throughout.

### Red / green

- **RED** — fixture cluster where two siblings declare the same member at
  *different* offsets; assert `--plan` reports it as needing reconciliation and
  `--apply` refuses.
- **RED** — assert a `csv.writer`-style write is rejected by `check_csv`
  (guards the CRLF trap that bit the audit).
- **GREEN** — the `TeamPrototype` cluster: 3 files, 242 lines → 1 file, 102
  lines, `Functions: OK 3/3 matched across 1 source file(s)`, `check_csv: OK`,
  `pin_consistency: OK`. This exact case ran green during the audit.

## `tools/fieldnames.py` — the T0 evidence

`docs/ini_schema.md` already holds 1,736 field entries read from the exe, but
its generator was deleted (`a4b1dde`), so it is not regenerable. This tool
replaces it and goes further: 296 tables / 4,116 entries, joined against
upstream `offsetof` to produce **member names**, which the doc lacks.

Emits `reverse/field_names.csv`: `table_rva, ini_key, bfme_offset, upstream_class,
upstream_member, votes, margin`.

**The offset always comes from the BFME binary and only the name from upstream.**
BFME moved fields; taking an upstream offset would silently corrupt layouts.

### Red / green

- **RED** — assert a key whose upstream entry maps to two different classes is
  emitted as ambiguous, not guessed.
- **RED** — assert the tool refuses to emit a row where the BFME offset is
  absent, rather than falling back to the upstream offset.
- **GREEN** — `WeaponTemplate`: assert `AttackRange → +0x14 → m_attackRange`,
  matching `reference/…/GameLogic/Object/Weapon.cpp:177`. Verified by hand
  during the audit.
- **GREEN** — assert the class vote returns `GlobalData` 193v/7v and
  `WeaponTemplate` 49v/2v.

## Fan-out protocol

The repo takes continuous pushes from other agents; AGENTS.md requires small,
rebasable changes.

- **Partition T1 by destination cluster, never by file.** Two agents merging
  into the same destination collide on the ledger. Ledger rows for one cluster
  are scattered (lines 20074, 23789, 40417, …), so disjoint clusters auto-merge.
- **Partition T0-fields by owning struct**, T0-vocab by upstream source file.
- Ten agents at a time. Each: `git pull --rebase`, one work item, gate, commit,
  push, pull --rebase.
- Never `git add .` — stage explicit paths (AGENTS.md).

## Commit protocol

One work item per commit. Message body ends with the metric trailer from
`readability_metric.py`. Example:

```
Merge 21 Player instance-list walkers into Common/RTS/Player.cpp

readability: Local 33.0 -> 33.4 (+0.40 pp), files 8827 -> 8807 (-20)
```

## Known hazards, all hit during the audit

1. **Upstream vocabulary transfers; upstream *ordering* does not.** Naming
   `VictoryConditionsInterface` slots from upstream declaration order created a
   duplicate `hasSinglePlayerBeenDefeated` and silently rebound a virtual call —
   `ff 50 2c` became `ff 50 14`. Name only slots the body proves.
2. **Type renames change mangled names of everything typed by them**, including
   globals. `GameLogicFrameSlice` → `GameLogic` broke the pin for
   `?TheGameLogic@@3PAV…@@A` and collided with an existing pin at a different
   address. Type renames are T2, never T0.
3. **Name collisions are the real risk of mass renaming**, and
   `pin_consistency.py` already catches them — it rejected
   `MemoryPool::freeBlock` because that name already covers nine functions of
   five sizes. Run `--check` before every push; never add to
   `pin_consistency_baseline.csv` to go green.
4. **Edit `reverse/functions.csv` as bytes.** CRLF loss fails `check_csv`.

## Order of work

1. `readability_metric.py` — nothing else can report its effect without it.
2. `merge_cluster.py` → drain 177 clusters.
3. `fieldnames.py` → drain 1,326 fields, batched one header per commit.

T0-vocab (4,267 functions) needs no tool: the evidence is the upstream body.
Run it as an agent lane against `reverse/field_names.csv`-style worklists once
the metric exists to score it.
