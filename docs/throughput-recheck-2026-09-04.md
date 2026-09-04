# Throughput audit: independent recheck and compute-efficiency recommendations

The defects are well supported. A large speed multiplier is not established.
The highest-confidence next work is repairing information loss between sessions
and between the scheduler and workers, then measuring a bounded compiler-search
experiment. More generic agent sessions are not the first intervention I would
choose from this evidence.

## What survived rechecking, and what needs qualification

All numerical rechecks use the first audit's fixed commit `676412e5a`, so concurrent
upstream landings do not change the denominator mid-experiment. Origin advanced
during this review; the files behind the scanner, stash, probe, class-launcher,
and object-sweep findings were unchanged in the checked outgoing difference.
No running fleet was changed.

| Finding | Confidence | Evidence and limitation |
|---|---|---|
| Scanner's terminal-byte test is wrong | Very high | GNU objdump, independently of Capstone, confirmed terminal returns/jumps on all 1,269 newly admitted bodies; zero disagreements. The 20 regression cases pass again. |
| Fixed queue grows from 58 to 156 fresh family members | Very high for this snapshot | Reproduced. This is queue reach, not an accepted conversion count or fleet speed measurement. |
| Scanner fix immediately accelerates the current fleet | Not established | No calls to `family_scan` were found in the tracked fleet path or brief generator. It needs an actual consumer. |
| Existing deque source matches the five targets outside relocations | Very high | Recompiled and reproduced on all five; 93 of 101 bytes remain after the two REL32 slots are masked. |
| Those five targets are ready to land unchanged | False under current pins | Strict `build.compile_function` passes the donor control but fails all five targets. Each has one map-reallocation call not accepted for the donor's `deque<int>` callee. No pins or ledger rows were altered. |
| Reusing compiled source is a new capability missing from the repo | Too broad | `obj_sweep.py` already searches compiled objects and validates permitted relocations. The incremental opportunity is near-match retrieval for worker briefs and adaptation when existing symbols do not fit. |
| Medium/class work will outperform other lanes per dollar | Plausible, not proven | The bytes available and context advantage justify a trial. Function size alone does not measure time, failure probability, or compute cost. |
| Harvest checks the wrong worktree after rebase | Very high | It calls the original checkout's absolute checker path; the checker sets ROOT from `__file__`, not cwd. |

The source-reuse experiment is useful, but it is not yet a project-scale
breakthrough. Its five targets total 505 bytes, and none was landed by the audit.
The corrected scanner's extra fresh family members represent 9,346 bytes at this
snapshot. Neither result by itself explains or resolves millions of remaining
bytes.

Independent reproducer: `py -3 build/audit_crosscheck.py`. It writes
`build/audit_crosscheck.json` and changes only audit scratch artifacts. Its bank
test runs under a temporary directory, not the shared attempts log.

## Newly verified loss of useful work

**The stash retains the latest body, not the best body or alternative bodies.**
`re_log._bank` unconditionally writes `reverse/attempts/<rva>.cpp`; it has no
existing-score check, version retention, or per-boundary lock. A temporary test
banked a 0.99 body followed by a different 0.80 body: the stash contained only
the latter. Among 1,179 scored partial log entries, 13 successive partial pairs
at the same RVA and declared size have decreasing reported scores. These are
subjective scores, so this does not prove 13 objectively better bodies were
lost. It does demonstrate why destructive replacement is the wrong archive.

Keep immutable candidate bodies keyed by source hash, plus an explicit preferred
candidate for each target/toolchain/header configuration. Save materially
different alternatives. Record measured size, relocation validity, and instruction
diff alongside the author's explanation; preserve a lower-scoring alternative
when it uses a promising different model. Git history can recover committed
versions, but it cannot recover every overwrite between harvests.

**Class context is generated and then dropped.** `pick_class.py` prints an RVAS
line followed by NOTE and a slot table. In `seat.sh`, the class branch reads
RVAS twice but never assigns NOTE from the picker output before expanding
`--note "$NOTE ..."`. The deployed copy has the same omission. Inspection of
19 local class briefs found zero containing the picker's `CONTEXT: WARM CLASS`
note. The HLodClass picker file contains the class description and slot table;
its corresponding worker brief starts with a blank note followed by generic
instructions. Per-body context still supplies a vtable hint and a command to
retrieve the table, so the information is recoverable manually, but it is not
delivered as intended.

The ranker also sorts by remaining dump bytes; the picker takes the first
unclaimed entry. That is not an explicit ranking by known class context. In a
fresh audit ranking, the first two entries have no recovered class names. Repair
the handoff first, then compare context-weighted selection rather than assuming
the lane name guarantees warm work.

**Repeated sessions overwrite diagnostic history.** The seat log has 907
non-picker/non-unblock start events, representing 820 distinct
engine-seat-target-pass keys: 87 starts reuse a key, across 47 keys. The launcher
uses that same key for the output filename and redirects with `>`, replacing
the earlier transcript. Some retries are appropriate and may progress different
bodies within a file; these counts do not measure wasted sessions. They do show
that the current transcript archive cannot reliably reconstruct each run. Give
every run a unique ID, full timestamps, immutable brief, exit status and usage
record, then associate its actual accepted commits with that ID.

The local log directory contains approximately 2.07 GB across 1,008 files.
Log size is not a token or dollar measure. No credible wasted-compute percentage
can be calculated from those bytes or start counts alone.

## Non-obvious changes worth testing

1. **Use compiler output as search memory.** Cache both successful and failed
   candidate evaluations with target bytes, compiler binary, flags, dependencies,
   source, and relocation symbols in the key. Also deduplicate emitted instruction
   shapes: ten different C++ spellings that compile identically are one explored
   result. Share this across sessions so new agents do not pay for old experiments.
   The current dependency cache avoids stale rebuilds, but `probe.py` still calls
   `compile_source` directly and does not provide a persistent cross-session search
   history of failed variants.

2. **Move small source-shape experiments out of long AI conversations.** Once
   an agent supplies a credible body and identifies a narrow mismatch, let a
   bounded program test admissible declaration order, temporary placement, branch
   form, and other known MSVC levers. Preserve the best result and stop on a budget
   or a plateau in distinct compiled outputs. Return to an agent when a new type,
   dependency, calling convention, or control-flow hypothesis is needed. There
   are many one-off variant files in scratch, but no comparable general search
   service was found wired into the tracked fleet.

   This is an established matching-decompilation technique: decomp-permuter
   supports manual and random source permutations, but its documented targets
   are MIPS, PowerPC and ARM32, not this MSVC/x86 workflow:
   https://github.com/simonlindholm/decomp-permuter

   Transmuter documents C++ mutation, a custom compiler command, source-hash
   deduplication, multiple retained candidates and bounded search:
   https://github.com/macabeus/transmuter

   Neither was installed or validated against MSVC 7.1 here. Use these as design
   references, not a claim of a drop-in solution. Reuse this repo's compiler and
   strict byte/identity gates. Do not enable assembly-injection transformations
   or silently accept semantic changes just because a similarity score improves.

3. **Schedule investigations by shared uncertainty.** `dump_families.py`
   already exposes the graph: at the audit snapshot, 47 dump bodies totaling
   114,770 bytes share `DX8Wrapper::Apply_Render_State_Changes`. This is a
   relationship, not proof that this already-known callee blocks all 47. Use
   repeated attempt diagnoses to locate an actual common missing layout, compiler
   construct or dependency, solve that once, and propagate an executable example
   to the affected bodies. Measure downstream accepted bytes per investigation.

4. **Build a measured stopping policy.** Replace the combination of a long
   session cap and subjective 0.9 scores with progress in verified assumptions,
   resolved dependencies, and distinct improving compiled outputs. A retry should
   name what changed since the prior attempt. Use short deterministic searches
   for small residual differences and deliberate deeper sessions for structural
   unknowns; a common wall-clock cap cannot distinguish them well.

5. **Retain a fixed evaluation set before changing the whole fleet.** Select
   20-30 current partials across size and mismatch categories, record their
   starting bodies and compiler output, and compare equal-budget sessions with
   and without preserved alternatives, complete briefs and compiler search.
   Track net accepted bytes, compute usage, wall time and identity failures.
   Then test concurrency separately. A worker-count increase without this
   attribution can hide declining marginal productivity behind a rising total.

Confidence is very high that the handoff, destructive stash replacement, and
transcript replacement mechanisms exist. Confidence is moderate that the
proposed search and scheduling changes improve bytes per unit of compute on this
remaining corpus. The magnitude remains unmeasured; there is no defensible 2x,
5x, or cost-saving percentage to promise yet.

Recommended order: preserve candidates and run records; repair class-context
delivery and publication validation; instrument the actual worker loop; test
bounded compiler search and shared-blocker assignments. Keep existing agents
running unless separately instructed to change them.
