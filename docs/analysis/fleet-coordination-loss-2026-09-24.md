# Fleet coordination-file loss, 2026-09-24

Baseline: current master `cec8b73240` in an isolated clean worktree; 28 fleet
tests and 19 subtests passed before changes. No live fleet database was read
or edited. This is a separate reservation A defect found while reviewing the
Linux containment design, not evidence about live failure frequency.

## Confirmed failure

`tools/fleet_run.py:connect` always uses SQLite create mode. In a temporary
repository, a live claim with this process's PID and a `running` record was
visible to `active_rvas`. After deleting only `build/fleet_runs.sqlite`, a
second `active_rvas` call created an empty database and returned no owner;
`claim` then accepted a replacement for the same RVA while the original PID
was alive. The same temp fixture made `tools/fleet/reconcile_legacy.py` report
zero claims and accept its guarded cutover, because its snapshot equates a
missing database with an empty one. Its `--stopped-fleet` flag is an operator
assertion, not an automatic liveness proof. These are correctness defects;
their live occurrence is unmeasured.

## Proposed narrow repair, before production edits

Persist a small coordination marker beside the database, tied to a UUID in
SQLite metadata. On every normal connection, require the marker and database
identities to agree; a missing, unreadable, or replaced database after
initialization is an error, never an empty claims table. A truly fresh
checkout with no prior run records, claims database, or old seat assignments
may initialize automatically under a dedicated cross-process lock. Existing
checkouts with historical records or an old database require a controlled,
dry-run-first initialization that reports a digest of the relevant files and
requires the exact digest plus `--stopped-fleet` to apply. Refuse initialization
while any existing claim or recorded PID is live. Preserve all records and
logs; do not auto-release or reset an old claim. Have legacy reconciliation
report coordination state in dry-run mode and reject apply while it is
missing, inconsistent, or uninitialized.

A run directory without a database is evidence that the database may have
been lost; require restoration even if the direct worker PID appears dead.
An unmarked database with release history is also evidence of prior use:
only a genuinely empty first-use file may complete automatic initialization.

Alternative of merely checking `db_path.exists()` before `sqlite3.connect`
does not detect replacement by another empty database and races a concurrent
first use. Treating a terminal old record as proof of no worker is unsafe:
the independently reproduced detached-child case can leave it terminal while
a descendant survives. Clearing old logs or claims to bootstrap is excluded.

## Adversarial review and decision

The initialization marker must be written atomically, and normal readers must
never create a replacement database when a marker exists. A crash during
first-use initialization may leave an empty database without a marker; only
a database with its UUID, zero claims, zero releases and no prior run records may finish that
initialization automatically. A marker without a matching UUID remains
blocked. Two first-use processes must serialize on an initialization lock,
then share one SQLite file. A dry-run digest must bind the operator's later
apply to current records, database and old log; any change invalidates it.
Normal reads must verify the required schema without creating missing tables;
otherwise a partial replacement file could look like an empty registry.
The explicit stopped-fleet flag cannot prove a detached process is gone, so
rollout still requires the operator to stop and inspect old workers. A live
PID or claim is a hard reject even with the flag. Different worktrees still
have different local databases; this repair makes no cross-worktree promise.

The UUID detects accidental recreation or replacement with a different file.
It is not an anti-rollback receipt for a copied older database carrying the
same UUID. Restoring a backup requires stopping the fleet and checking its
claims against run records before use. No local marker can prove ownership
across a separately running checkout.

**Proceed** as a separate small reservation repair, with real production
function tests for deletion, replacement, concurrent first use, legacy
reconciliation, and the guarded bootstrap. Publish only after an adversarial
diff review and relevant fleet tests. Do not apply initialization to any live
checkout during this task.

## Implementation review

The independent diff review found a migration blocker outside the new marker
code: a pre-lease claim with no PID and a terminal record was considered dead
by `lease_dead`. A real old-schema migration regression failed (`active_rvas`
returned empty) before repair. Both lease eras now require an unambiguous dead
positive PID before automatic takeover; nonpositive and malformed PIDs remain
busy. The previous unit test that treated a terminal no-PID record as proof of
death now requires an explicit named release after worker verification.

Additional edge reviews made automatic initialization reject old `releases`
history and any run directory lacking a database, preserved the first file
picker's non-owning `selected STEM` diagnostic, verified schema without
repairing it on normal reads, and took the dry-run digest after opening SQLite
so a WAL sidecar cannot stale the status command itself. These cases have
production-function regression tests. The relevant fleet, throughput and
harvest suite passed 89 tests plus 19 subtests; `check_csv` also passed. The
separate Linux process-containment integration is still required before the
whole reservation-lifecycle repair can be called complete.
