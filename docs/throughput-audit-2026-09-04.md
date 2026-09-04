# Conversion throughput audit, 2026-09-04

The best next investment is better reuse and work assignment, followed by better
diagnostics. The repository already has incremental compiler caching, family
scanning, source packets, near-match stashes, and specialized fleet lanes. Adding
another generic queue or telling agents to work harder would miss the problems
below.

This audit uses committed snapshot `676412e5a735b586348b4a3af64075bbca6f0c3b`
from Open-BFME/Open-BFME-1. It was fetched and checked in a separate worktree;
the main checkout's 487 status entries were preserved. Local fleet claim files
were read separately. No fleet process was started, stopped, or reconfigured.
The source patch is local and has not been published.

## What the project is actually gaining

`tools/progress.py HEAD..HEAD` reports 5,083,669 rebuildable code bytes, **52.40%**
of the padding-excluded denominator of 9,702,173 bytes. The breakdown is:

| Category | Bytes | Percent of real code |
|---|---:|---:|
| Authored C++ | 2,507,435 | 25.84% |
| Vendored source | 281,688 | 2.90% |
| Generated C++ | 1,243,107 | 12.81% |
| Attached prebuilt libraries | 1,051,439 | 10.84% |
| Retail-byte dumps | 3,390,996 | 34.95% |
| Unclaimed | 1,227,508 | 12.65% |

This is ledger-derived coverage, not proof of a complete working game or a fresh
full build. `check_csv.py` passed for the snapshot: 161,832 function rows and
82,745 symbol rows.

Two adjacent committed windows show accelerating progress:

| UTC window | Rebuildable bytes gained | Approximate bytes/hour |
|---|---:|---:|
| Sep 3 18:52:48 to Sep 4 06:53:17 | 56,046 | 4,667 |
| Sep 4 06:53:17 to Sep 4 19:03:12 | 118,769 | 9,763 |

The second window gained 118,619 authored-C++ bytes but only 242 net new exact
coverage bytes: almost all its progress was converting already-bounded dumps.
That is useful work. It also explains why total exact coverage is a poor measure
of current conversion throughput. The observed rate rose about 2.09x; this is
not a controlled estimate of the benefit of any particular fleet change, and
should not be extrapolated into a completion date.

Reproduce with `tools/progress.py` over these ranges:

```
dc50a5bb428472dcc61ea645989e27c4bb03bcb2..6f69ae792581daae6c5413ed66674c14e5000f80
6f69ae792581daae6c5413ed66674c14e5000f80..676412e5a735b586348b4a3af64075bbca6f0c3b
```

## Tested improvement: repair the family scanner's boundary filter

`tools/family_scan.py` tested the final raw byte for C3/C2/E9/EB, or its
penultimate byte for FF. That rejects ordinary `ret 4`, `ret 8`, and most tail
jumps because their final bytes are operands. It can also accept a nonterminal
instruction whose immediate happens to end in C3.

The patch decodes the complete body and checks whether its final instruction is
`ret` or `jmp`, in all four scan modes. It preserves pin, attempt, local-static,
size, and padding exclusions. Decoding is a candidate filter, not independent
proof of a function's identity or start address.

Same snapshot, default operand mode and 8..160-byte range:

| Result | Before | After |
|---|---:|---:|
| Bodies admitted to grouping | 935 | 2,203 |
| Families with fresh members | 29 | 74 |
| Fresh members in those families | 58 | 156 |
| Bytes in fresh family members | 5,947 | 15,293 |

The corrected terminal test admits 1,269 previously excluded bodies totaling
127,581 bytes after the local-static exclusion, and rejects one former false
positive. Other filters still keep many of these out of the fresh family queue.
The 2.69x increase in fresh candidates is **not a measured conversion speedup**.
No ledger progress is claimed for this tooling change.

Validation: 20 pytest cases pass, including return cleanup, direct/indirect
jumps, opcode-looking immediates, truncated instructions, and a CLI regression
in every scan mode. `git diff --check` passes.

## Promising result: reuse already working C++ as a source donor

A prototype compared the newly admitted bodies with existing nongenerated
`Code/*.cpp` rows, excluding files containing assembly markers. Matching the
operand-normalized instruction shape found **60 candidate bodies / 4,443 bytes**
with an existing C++ donor. This is deliberately a shortlist, not an identity
claim: types, constants, callees and calling conventions still need checking.

One concrete experiment was better than a similarity score. Compiling the
existing `Code/GameEngine/Source/Common/Rva006472C0DequeIntPushBackAux.cpp` with
the repo's MSVC 7.1 toolchain emitted 101 bytes matching all five newly exposed
targets outside relocation slots:

```
0x00089CE0  0x0035AE40  0x0035AEC0  0x0035B2A0  0x0035B320
```

The donor's own claimed function at `0x006472C0` passed the normal scoped build:
`Functions: OK 1/1 matched`, with source and string-reference checks passing.
The five targets have NOT passed per-target relocation and identity validation;
they remain dumps. In particular, the donor's `int` type cannot be assigned to
all five just because the generated instructions match.

Recommendation: add an existing-source donor index to worker briefs, alongside
the existing Zero Hour twin and neighbour evidence. Key its cache by retail and
source revisions. Show operand differences and call destinations; always retain
per-body identity checks and normal byte verification. Start with these five
targets as a bounded evaluation before expanding the mechanism.

## Other recommendations, in priority order

1. **Replace independent permanent claims with one shared claim lifecycle.**
   File claims use file stems, mid claims use RVAs, class claims use vtables,
   and finish claims use another RVA list. A shared mutex protects individual
   writes but does not make these different ownership domains mutually
   exclusive. `pick_mid.py` does not consult finish/file/class assignments;
   `pick_finish.py` does not consult mid assignments. The local files contain
   one mid/finish overlap, which establishes overlapping assignment history,
   not simultaneous execution. At the committed snapshot, 65 of 97 mid claims,
   141 of 222 finish claims, and 107 of 118 big claims still point to assembly.
   These are not measured failure rates: some may be active, deferred, or have
   landed later. Use atomic RVA ownership with owner, full timestamp, heartbeat,
   and release. Requeue only after a new donor, dependency, stash, or strategy
   revision; avoid blindly repeating failed work when a timer expires.

2. **Spend more conversion capacity on medium bodies with known context.**
   Streaming just matched `.asm` rows gives 2,123 bodies in the 300..999-byte
   band totaling 1,105,620 bytes. In contrast, 2,316 bodies below 64 bytes total
   only 55,196 bytes. The default brief sorts smallest first; its first 40 rows
   can repeatedly favour tiny work. Mid/class lanes already exist: measure and
   expand their share, with source donors and actual class/callee relationships.
   Address density inside an arbitrary dump bucket is a weaker proxy for shared
   layout knowledge than membership in a demonstrated class or template family.

3. **Make probe diagnoses conservative and actionable.**
   `probe.classify` labels `mov eax,1; ret` versus `mov eax,2; ret` as
   `register-mirror`. Its fallback increments the rename count even when the
   difference is a literal or a different operation. The confidence calculation
   measures byte coverage, not evidence for a register mapping. Add explicit
   literal/offset/opcode/control-flow cases and reserve register-mirror for a
   consistent register substitution. Report unknown when the pattern is not
   established. This helps the 182 current 0.9+ partials with existing stashes
   (39,750 bytes) without treating their self-reported scores as byte proof.

4. **Consolidate attempt parsing before refining the queue model.**
   `re_log.py` distinguishes boundary refutations from temporary blockers and
   supports latest-verdict-wins and void records. `family_scan.load_attempted`
   independently treats every historical blocked record as permanent and extracts
   every eight-digit address from the entire line, including evidence references.
   It can therefore suppress a related family based on a cited address rather
   than the attempted boundary. Mid selection searches evidence prose for
   `blocked` rather than using the status field. Use one boundary-aware parser,
   preserve explicit shape-level refutations separately, and retest retractions.
   Keep this separate from the tested terminal-filter patch.

5. **Make publication a short transaction over verified, immutable inputs.**
   `harvest.py` holds `reverse/.add_match.lock` through commit, fetch, rebase and
   push; workers need the same lock to land a body. It stages all tracked Code
   edits even if they are in flight. Its post-rebase checker invokes the main
   checkout's absolute `tools/check_csv.py` path with the other worktree as cwd;
   that checker derives ROOT from its own file, so it checks the main checkout.
   Snapshot explicit completed artifacts under the lock, validate and publish
   from the isolated snapshot using its own tools, then reconcile under a short
   lock with revision checks. Measure lock wait before claiming a speed gain.
   The active checkout also had no configured `core.hooksPath` and only sample
   default hooks: tracked hooks are not automatically active. A startup check
   should verify that the intended gates actually run. This audit did not change
   that shared configuration.

6. **Investigate the local-static compiler-symbol blocker as a separate slice.**
   `family_scan.registers_a_local_static` excludes `_atexit` callers because
   generated `_$E<n>` helper names collide across translation units in the global
   DIR32 consistency map. The corrected small-body scan excludes 11 such bodies.
   Use COFF linkage/storage-class evidence to distinguish local symbols from
   external ones; prototype scope-aware checking while keeping external-symbol
   contradictions fatal. Do not simply expand the whitelist. This could remove
   a construct-wide blocker, but no fix or conversion benefit is proven here.

## How to judge the next experiment

Use net unique rebuildable bytes accepted on origin per worker-hour and per
unit of compute cost. Also record first compile, compile/diff iterations, lock
wait, rejection cause, donor used, and final commit. Keep identity-only repairs
and source conversions separately visible. The existing yield model was fitted
to 743 drift outcomes and explicitly lacks a time-cost model; it is not a
calibrated model for the current dump-conversion fleet.

There are already 1,436 duration-bearing log entries among 1,902 entries referring
to current assembly rows. Those include annotations and self-reported times, so
they are a starting point for structured telemetry, not an unbiased training
dataset. Run equal-capacity trials of current selection versus medium/class work
with donors and conservative probe feedback. Do not promise a multiplier before
the accepted-byte and cost measurements exist.

Local reproduction artifacts are under `build/audit_*.py` and
`build/audit_*.json` in this audit worktree; `build/family_candidates_fixed.txt`
contains the regenerated candidate list. These scratch artifacts are not game
source, ledger claims, or deployed fleet changes.
