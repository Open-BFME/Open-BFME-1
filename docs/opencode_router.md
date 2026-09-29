# OpenCode Go / free Zen worker router

`tools/opencode_router.py` is a standard-library scheduler for bounded tasks
assigned by Codex, Claude, or a human. It does not select RE candidates or
integrate code. Keep using `next_work.py`, `brief.py`, `callees.py`, `probe.py`,
and the existing byte gates. The parent reviews results, verifies identities,
tests, and owns commits and integration.

## Setup

Requires Python 3.10+, OpenCode **v2** (tested with 2.0.18), Git, and Linux with
writable delegated cgroup v2. It reuses `fleet_cgroup.py` containment and
`fleet_run.py` claims. There is no process-group-only alternative. On a systemd
host without delegation, start the scheduler inside a delegated user scope,
for example `systemd-run --user --scope -p Delegate=yes <router command>`.
Windows users need a Linux/WSL environment with delegation.

1. Connect **OpenCode Go** using OpenCode's `/connect`.
2. Disable **Use balance** in the Go console. This account option permits paid
   overage even when the client requests a Go model. The CLI cannot verify it.
3. Copy the example configuration and acknowledge that setting locally:

   ```sh
   mkdir -p build
   cp tools/opencode_router/go.json build/opencode-router.json
   # Edit build/opencode-router.json: set "go_overage_disabled": true.
   python3 tools/opencode_router.py --config build/opencode-router.json discover
   ```

The example acknowledgment is deliberately false. No credential belongs in
router configuration. OpenCode reads its existing credentials. Only explicit
`opencode-go/…` and verified-free `opencode/…` IDs are accepted; every invocation passes `--model`. An injected
OpenCode policy denies other providers and nested subagents. Policies also deny
Git tool commands; the worker prompt assigns VCS responsibility to the parent.
OpenCode policies are not an OS sandbox against hostile code, and Console
policies can override local policies. Use a trusted local OpenCode setup.

## Parent-agent commands

Give Codex or Claude this instruction after setup:

> Use `python3 tools/opencode_router.py --config build/opencode-router.json run bulk --target <canonical-RVA-or-file> --task-file build/task.txt` to delegate one bounded task. Inspect `show JOB_ID`, review the retained workspace, run the scoped gate, and integrate valid work yourself. Use `submit` plus `fleet` for concurrent tasks; do not select individual models unless a task requires it.

Examples (global options precede the subcommand):

```sh
python3 tools/opencode_router.py --config build/opencode-router.json run bulk \
  'Inspect tools/callees.py and report its input/output contract. Do not edit files.'
python3 tools/opencode_router.py --config build/opencode-router.json run reasoning \
  --target 0x00123456 --task-file build/task.txt
python3 tools/opencode_router.py --config build/opencode-router.json run escalation \
  --target 0x00123457 --task-file build/stubborn-task.txt
python3 tools/opencode_router.py status
python3 tools/opencode_router.py show JOB_ID
```

`run` enqueues and waits, participating in scheduling if no other scheduler
holds the lock. `submit` only enqueues. Both print a durable job ID immediately.
Exit codes: 0 completed/submitted, 1 failure or needs review, 2 pending after the
bounded duration (or another scheduler owns `fleet`), 130 interrupted `run`.
The worker's `success` is a **self-report**, not byte-match proof.

For parallel work, submit several **different targets**, then:

```sh
python3 tools/opencode_router.py submit bulk --target SourceFileA --task-file build/task-a.txt
python3 tools/opencode_router.py submit reasoning --target SourceFileB --task-file build/task-b.txt
python3 tools/opencode_router.py --config build/opencode-router.json fleet --workers 4 --duration 30m
python3 tools/opencode_router.py --config build/opencode-router.json status --json > build/router-report.json
```

`fleet` processes the queue until empty or its duration expires. It accepts new
submissions while running; it is not an idle daemon. `--workers` may lower the
configured global cap. Duration expiry stops active workers and requeues them
within the retry budget; it does not abandon unbounded background work. An
optional host-CPU admission limit can lower dispatch concurrency on a saturated
machine; it never stops a running worker (see below).

Task files avoid shell quoting problems and argv size limits. The router uses
argument arrays and feeds task text on stdin, never through a shell. For actual
RE assignments include the existing brief, RVA/size, source file scope, gate
command, and completion criteria. Use the same canonical `--target` for the
same unit of work. An RVA is normalized; an arbitrary key is case-sensitive.
Without a target, only identical task text is deduplicated. The router cannot
infer overlapping functions from unrelated prose. For a file containing several
bodies, use a shared file key and coordinate its individual RVAs with existing
fleet selection. Local fleet claims use the selected key; cross-host claims
remain the parent's responsibility through `tools/claims.py`.

`--redundant` explicitly permits a second target owner. It still needs a separate
workspace. `--model opencode-go/ID` explicitly overrides tier reservations but
requires that model to be enabled and still obeys concurrency and cooldowns.

## Workspaces, ownership, and recovery

By default each job receives a retained detached Git worktree at the submitting
repository's **HEAD at submission time**. Repository identity and that SHA are
persisted before dispatch; a later scheduler HEAD cannot change the task's base.
Uncommitted parent changes are not copied. All retries
reuse that job's workspace, so failed source experiments remain available.
`--cwd /absolute/prepared/worktree` uses a parent-prepared workspace instead.
The scheduler serializes overlapping workspace paths, even for redundant jobs.
An explicit retained Git workspace records its own HEAD. Legacy jobs with an
existing workspace may retry there without inventing an original base. Legacy
jobs without a workspace or recorded base must be reviewed and resubmitted
with refreshed task evidence; they do not silently use today's HEAD.
It sets both the process cwd and `PWD`: OpenCode run uses the latter to choose
its session location, so changing cwd alone does not isolate linked worktrees.
It never deletes worktrees or worker artifacts; remove reviewed worktrees using
normal Git worktree commands when finished.

The default state directory is `opencode-router/` under the **common Git
directory**, shared by linked worktrees. Separate clones must explicitly share
one `--state` on the same host if they are to share limits; a job records the
clone it was submitted from (`repository`, `submission_root`, `base_sha`) and
whichever scheduler dispatches it creates the workspace from THAT clone at that
base, so a scheduler running in another clone does not reject it. A submission
root that has moved, a recorded workspace that is no longer a worktree root of
its repository, or one whose HEAD left the recorded base, parks the job as
`needs_review` with its edits intact instead of failing it. A recorded Git
workspace (a router worktree, or a `--cwd` inside a checkout) whose `.git` is
missing or broken, or that now resolves to another worktree, is also parked;
only a `--cwd` that was outside every repository at submission is scratch. Use one configuration
for all clients. State is local SQLite/WAL, not a network-filesystem service.
A durable identity marker rejects a missing/replaced database. Do not delete
state while workers exist. Back up SQLite with its backup API or while stopped.

One OS lock owns scheduling. Submissions/status use separate SQLite connections.
Each worker launches through the existing blocked cgroup bootstrap: PID and
containment are durable before execution is released. Claims remain held until
the whole cgroup is verified empty, including detached descendants. A small
timeout supervisor survives scheduler crashes. Ctrl-C/SIGTERM stop all workers
owned by that scheduler, preserve output, and record interrupted attempts.

A restart requeues interrupted attempts only if containment is verifiably empty.
A live/unknown worker becomes `needs_review`, keeps its target/workspace lock,
and counts against concurrency. Inspect its transcript and cgroup. Once it is
empty, explicitly run `resume JOB_ID`; this command verifies emptiness and
releases ownership before requeueing. Unknown/missing containment requires
operator investigation, never automatic duplicate execution. `cancel JOB_ID`
works for queued/finished jobs while the scheduler is stopped.

**Interruption spends nothing.** An interrupted attempt — scheduler duration
expiry, operator stop, or a restart that verified empty containment — is
recorded for audit, but it is not evidence against a model or a task. It does
not increment `failures` or `availability_failures`, does not promote the job's
tier, and by itself sets no model cooldown, so repeated restarts can neither terminally
retire a job nor escalate model selection. The job returns to `queued` under the
same ID and keeps its target/workspace ownership; an interruption arriving for
an already terminal job never resurrects it. Only `failure`, `timeout` and
`output_limit` spend the task-failure budget (`retries`, `reasoning_after`,
`escalation_after`) and the `failure_cooldown`; `quota`, `unavailable` and
`variant_unavailable` spend only the availability budget. `status` reports
`interruptions` separately from `task_failures` per model and per
model+variant+class, so historical rows are reclassified at read time and no
stored counter is rewritten. `needs_review` and `cancelled` remain terminal and
still hold the model back, because ownership of the worker is unresolved.

A genuine quota event survives a simultaneous interruption as separate
`quota_observed` evidence. It still controls account pacing, model cooldowns
and slow start, while the interrupted job spends neither retry budget.
`show JOB_ID` queries only that job and its attempts; it does not gather fleet
statistics, probe other workers or refresh remote account data.

Because interruption is free, a crash-looping scheduler requeues a job forever.
That is deliberate — an unbounded retry loop must not be mistaken for task
evidence — and the bound, if ever wanted, belongs in operator policy
(`cancel JOB_ID`), not in the accounting.

A restart records `interrupted` for every attempt whose containment it verified
empty, even when the surviving transcript contains a timeout or transport error
from before the crash. That lost accounting is deliberate: the scheduler that
observed the event is gone, and a requeue costs only a redispatch. A timeout
observed by a live scheduler is still counted as a timeout.

Legacy fleet interoperability uses the claims root saved on first invocation.
If the legacy fleet runs in a different checkout, pass `--claims-root PATH` on
first use. Existing coordination state is validated by `fleet_run`; the router
does not migrate/reset it. Follow that tool's stopped-fleet migration procedure
if needed. The router does not change candidate eligibility rules.

## Routing and configuration

The separate JSON configuration contains all model IDs and policy knobs:

- `workers`, per-model `concurrency`: total and individual concurrent caps.
- `enabled`: disable a model without changing code.
- `tier`: bulk, reasoning, or escalation; escalation models are reserved.
- `weight`: dispatch share among otherwise tied models. Old configurations without
  `cost_aware` retain the original tier/idle-capacity/weighted-dispatch ordering.
- `reserve`: concurrent slots reserved for escalation (not guessed token quota).
- `timeout`, `max_output_bytes`: per-attempt wall time and combined stdout/stderr
  cap (default 15 minutes / 32 MiB).
- `retries`: task retries after the initial attempt. `reasoning_after` and
  `escalation_after`: task failures before promotion (defaults 2 and 3).
  Only `failure`, `timeout` and `output_limit` count here; a scheduler
  interruption is lifecycle, not a task failure (see Lifecycle).
- `availability_retries`: separate quota/unavailable retry bound (default 20).
- `cooldown`: seconds before reconsidering quota/unavailable models (default 300).
- `failure_cooldown`: brief cooldown for genuine worker failures (default 20).

After a rate limit (`quota`), a model restarts at **one** slot when its cooldown
expires, and its cap doubles for every attempt started since that quota that
finished without one or has run 60 s; a new quota restarts the ramp. Without it,
every cooldown expiry launched the whole per-model cap at once: measured
2026-09-27, 15 of 16 Muse free launches were refused with 429 inside 5 s, and
each refusal spent one of that job's `availability_retries`.

Quota errors do not spend the reasoning-failure budget. Structured error events
are classified by status/type/message; text *discussing* quotas is not an error.
A model in cooldown is skipped immediately while other jobs/models proceed.
Expired model cooldowns permit another request only when the shared account gate also allows it. If every eligible model is unavailable,
the queue waits until recovery or the scheduler duration expires. Bounded attempt
counts prevent endless retry cycles. No model is removed permanently by an outage.
Regional restrictions and authentication/model-not-found errors are availability
failures, distinct from 429/usage limits and unsuccessful task work.

To add/change models, run `discover`, copy exact catalog IDs into the local JSON,
set tier/limits/weights, and use a harmless explicit-model smoke task. Removed
models fail availability checks cleanly. The public catalog establishes valid IDs,
not access for a particular account. Fresh standalone catalog requests can return
empty snapshots before plugins settle. This does not disable public-catalog IDs.

### Cost-first Go policy

The shipped config enables `cost_aware`. Routine bulk **and reasoning** use Muse
Spark 1.3 Contributor, DeepSeek V4.1 Flash, MiMo V2.6 Flash, GPT-6 Luna and
Qwen3.8 Flash, with DeepSeek V4 Flash secondary. Spare capacity on a more
expensive model is not a reason to assign it routine work.

`relative_cost` is a coarse, configurable preference weight, **not dollars per
job**. Initial weights reflect the parent's 2026-09-27 dashboard observations
and preferred pool. Request lengths/cache hits vary; the small sample does not
establish model quality. `effectiveness` defaults to 1; parents may calibrate it
from substantial verified BFME evidence later. Selection tries alternatives to
models with task failures, then minimizes `relative_cost / effectiveness`;
concurrency and dispatch `weight` break ties. No automatic optimizer is enabled.
Missing cost metadata excludes a model from automatic cost-aware routing.

`escalation_only` prevents ordinary bulk/reasoning assignments. Automatic access
requires an escalation-tier job and structured task-failure handoffs from at
least `cheap_failures_before_escalation` distinct economical models (default 2).
Quota/availability errors, interruptions, timeouts, repeated failures of just
one model, and failures without evidence do not unlock expensive workers.
Cheap untried models are still preferred. The configured escalation ladder is
GLM-5.3 Flash (4), Qwen3.7 Plus (6), MiniMax M3 (8), Kimi K2.6 (20), then
Kimi K2.7 Code (30). Cooldowns, concurrency and retry budgets still apply;
increase a bounded retry budget explicitly if a valuable task warrants climbing
further. An explicit `run/submit escalation` is the parent's authorization for
costlier reasoning; describe prior failures/potential gain in the task file.
An explicit `--model` overrides tier preferences, including for bulk, but never
bypasses the shared budget gate.

Models without dashboard calibration (LongCat, MiMo Pro, DeepSeek Pro, Kimi K3,
Grok, GLM-5.3 and Qwen Max) are retained but disabled. To enable one, verify its
cost, assign `relative_cost`, keep `escalation_only: true`, and enable it.
Go work stays on Go. Zen work is restricted to runtime-verified free models;
paid Zen entries cannot be enabled under the current billing policy.

Bulk retains low/medium reasoning, reasoning prefers high, and the example now
prefers **high** for escalation before provider-specific fallback. MiniMax keeps
`thinking`; models with no variants keep their defaults. Parents can explicitly
set xhigh/max for a justified blocker. Cost selection never bypasses capability
checks.

OpenCode v2.0.18 exposes historical costs through
`opencode stats --days 0 --models --cost --json` and JSONL
`step_finish.part.cost`. The router sums distinct step IDs per attempt into
`reported_cost_usd`, with `costed_steps`; absent data is null, never assumed free.
These are **local estimates**, not remaining Go allowance or an authoritative
account charge. Interrupted streams can omit final usage. Status groups costs
and outcomes by model + variant + category + tier and reports cost coverage.
Old attempts remain unknown rather than being repriced using today's weights.
Routing weights are snapshotted into each new attempt's result.

Attach verified outcomes with the existing measurement command:

```sh
python3 tools/opencode_router.py measure ATTEMPT_ID --exact-match yes \
  --bytes-gained 187 --useful-investigation yes --evidence 'scoped gate report'
```

Byte gain is a signed net change, distinct from fractional `--improvement`.
`status --json` includes success/exact-match/byte-gain/useful-investigation rates
per reported USD over cost-bearing attempts only; missing measurements are not
asserted successes. Rates are exploratory, not automatic routing inputs. Do not
sum the same integrated byte gain across redundant attempts. Worker success is
still a self-report; exact matches and useful investigations require parent review.

### Shared Go budget

The router enforces the **account-wide** Go allowance before new assignments,
including explicit `--model` requests. A quota on one model pauses every metered
Go model; it never assumes other models have independent usable allowances.
Active useful workers are not stopped merely because pacing changes.

Discovery on 2026-09-27 found the official upstream implementation of
[`GET https://opencode.ai/zen/go/v1/usage`](https://github.com/anomalyco/opencode/blob/b471c2b4495747353af768fbf2e0790c9d820ce2/packages/console/app/src/routes/zen/go/v1/usage.ts).
Its bearer-authenticated response is:

```json
{"usage": {
  "rolling": {"status": "ok", "percent": 63, "resetsAt": "2026-09-27T18:00:00Z"},
  "weekly": {"status": "ok", "percent": 28, "resetsAt": "2026-09-28T00:00:00Z"},
  "monthly": {"status": "ok", "percent": 11, "resetsAt": "2026-10-15T00:00:00Z"}
}}
```

This is an illustrative fixture, not this account's measurements. The route is
verified in provider source (including its migrated-Console proxy), not advertised
as a separately versioned usage contract in the public Go guide. The installed
CLI is v2.0.18. Its `stats --cost --json` and local database describe local
sessions, not account entitlement. No CLI command for the three Go meters was
found. The source route supplies the same subscription counters used by the
console; no dashboard rendering, scraping, LLM or inference request is involved.
The read-only smoke request with the installed Console OAuth credential returned
HTTP 403. Successful live authentication with a Go key remains to be verified
locally; failures stay visible and never create fabricated usage values.

The documented [Console Usage API](https://opencode.ai/v2/docs/console/usage/)
exports workspace CSV using a service-account key. It reports charges, not these
three Go entitlement meters. Export ranges start at UTC midnight; treating them
as Go rolling windows would be wrong. The member Budgets API is also not the Go
subscription. Neither is used to invent remaining allowance. Provider-specific
per-model included-dollar tables are not independent routing budgets.

#### Local authentication and paid-overage protection

1. In the **same workspace as the workers**, obtain the Go API key through the
   Go console. Set `OPENCODE_GO_USAGE_API_KEY` in the scheduler's environment
   through your local secret manager or a private environment file. Do not put
   the key in a command-line argument, repository, router JSON, or task prompt.
   This monitor does not need a separate Console usage-export service account.
2. Keep **Use balance disabled** in the Go console. Keep automatic balance
   reload/top-up disabled too. The [Go guide](https://opencode.ai/docs/go/)
   documents balance fallback after limits; the
   [Zen guide](https://opencode.ai/docs/en/zen/) documents automatic reload.
3. Preserve the existing local `go_overage_disabled: true` acknowledgment only
   after verifying that account setting. The sample remains false. The meters
   endpoint does **not** expose Use balance, and the router cannot verify or
   turn it off. The server-side setting is essential even for in-flight workers.

The monitor sends only a bounded GET to the fixed HTTPS URL. Redirects are
rejected. It never changes billing, purchases credits, switches accounts, calls
paid inference or logs response bodies/credentials. The monitoring variable is
removed from worker environments. OpenCode retains its existing inference
credentials. All launches require an explicit configured ID and allow only its selected
provider. Following the explicit Zen request, Space Bunny Free is enabled on
Zen with recorded zero-price evidence; its Go route remains disabled.

Without the monitoring variable, the router remains usable: submissions persist,
status reports `credentials_missing`, and economical jobs run one at a time.
Unknown-cost or expensive models wait. Add calibrated `relative_cost` metadata
for old configurations if economical models cannot yet be identified. Credentials
must identify the same account across orchestrators; the endpoint does not return
an account identifier with which to validate that association automatically.

#### Values, cache and policy

`percent`, `status`, and `resetsAt` are **provider-supplied** for each window.
Remaining percent is calculated as `100 - percent`, inheriting provider rounding;
it is not a finer-grained entitlement. Age, freshness, and pacing mode are local
calculations. Actual billed dollars/model and per-task Go depletion are not
returned by this endpoint. Recent per-model USD and existing success/byte metrics
remain **local estimates**, grouped by model + variant + category + tier, with
missing cost coverage explicit. They never decide whether the account is empty.
There is no speculative allocation of simultaneous account usage to one worker.

`go_budget` is an optional object; these are its defaults:

```json
{
  "refresh_seconds": 300,
  "stale_seconds": 900,
  "timeout_seconds": 10,
  "normal_remaining": 70,
  "economical_remaining": 30,
  "restricted_remaining": 10,
  "economical_max_cost": 2,
  "restricted_cheap_failures": 3
}
```

There was no published rate limit for the Go usage route in the inspected source.
Five-minute refreshes are shared through a SQLite lease under the router state
root; simultaneous clients do not each poll. Numeric or HTTP-date Retry-After extends the
interval. Cached `budget`/`status` calls do not query OpenCode. Fleet refresh runs
in a background thread so monitoring cannot delay supervision. Failures preserve
the previous observation and expose `refresh_failed`; data becomes stale at 15
minutes, on clock rollback, or when a reported reset timestamp is reached. Stale
values remain labeled as such. No reset timestamp ever causes a local refill.
The provider's calendar/anchor rules are deliberately not reimplemented.

| 5h remaining | New metered assignments |
| --- | --- |
| >70% | Existing economical/evidence-based selection |
| 30–70% | Cheap pool first; expensive work requires escalation and `--budget-justification` |
| 10–<30% | Cheap ordinary workers; expensive escalation additionally requires structured failures from 3 distinct economical models |
| >0–<10% | One economical worker; every task requires `--budget-justification` describing expected verified gain |
| 0% or any provider window exhausted | Queue all metered work until a fresh successful usage GET confirms recovery |
| Missing/stale data | One economical worker; suppress expensive and unknown-cost models |

Economical means calibrated `relative_cost <= 2` and not escalation-only; names
never imply price. Prior model failures, effectiveness, variants, reservations,
cooldowns and retry evidence remain in force. A free model may later be explicitly
configured with `metered: false` plus nonempty `unmetered_evidence` documenting
its verified entitlement; it bypasses the shared Go gate, but keeps other routing
checks. Models without an explicit declaration default to metered. A zero local cost does not prove
that a model is free.

Go inference quota/rate-limit errors override cached values immediately and durably;
even a response already in flight before that error cannot clear it. They retain
the existing separate availability retry accounting and preserve queued work.
There is no blind inference probe for recovery. If credentials are missing after
a quota error, configure them and wait for a fresh successful meter check.
An HTTP 429 from the **monitoring GET** itself is an API polling failure, not
proof of account allowance exhaustion. Idle exhausted scheduling sleeps between
checks; it does not cycle through models or consume attempts.

```sh
# Compact cached JSON for frequent orchestrator calls (no network):
python3 tools/opencode_router.py --config build/opencode-router.json budget
# Request a read-only refresh if due; still respects the shared interval:
python3 tools/opencode_router.py --config build/opencode-router.json budget --refresh
# Full human-readable status:
python3 tools/opencode_router.py --config build/opencode-router.json status
```

Compact status includes meters, freshness/source, quota latch, active model +
variant, the first 20 queued jobs and total queue count, budget restrictions for
ordinary work, and last-24h local estimated costs with task classes. Deferred jobs
keep `budget.*` machine-readable reasons in their notes. `run` also returns the
reason and budget snapshot if its waiting duration expires. Useful tasks may
continue to be submitted; budget deferral does not spend task retries.

#### Updating active installations

Old configurations lacking `cost_aware` retain their previous behavior. Copy the
new `models`, `cost_aware`, `cheap_failures_before_escalation` and `cost_basis`
fields into your local config, preserving credentials-free local settings and
`go_overage_disabled`. Schedulers load config once: apply after the current
scheduler finishes; do not interrupt useful workers merely to reload policy.
Queues choose models at dispatch and need no state rewrite. Explicit queued
`--model` requests obey the new shared budget gate. The measurement table and nullable/defaulted job metadata are additive; old writers
and old attempt records still work. The usage cache is a separate `go-budget.sqlite`
in the shared router state directory. Old running scheduler processes retain their
old code and cannot enforce the new gate: let useful work finish, then start the
next scheduler with the updated executable. Separate clones must share `--state`
for one account, just as they must share concurrency limits.

### Optional host CPU admission

The fleet loads its worker count once and dispatches up to `min(--workers,
workers)`. `cpu_admission` adds a **rolling, hysteretic admission limit** at or
below that cap, so a host that is actually saturated backs off new dispatch
instead of queueing work behind a machine that cannot run it. It is **off
unless `cpu_admission.enabled` is true**, and while off no host CPU is read at
all: `config()` validates the block, `control()` returns `None`, and the fleet
behaves exactly as before.

```json
{
  "cpu_admission": {
    "enabled": true,
    "grow_below": 0.9,
    "shrink_at": 0.98,
    "samples": 4,
    "grow_samples": 3,
    "shrink_samples": 2,
    "grow_step": 1,
    "shrink_step": 2,
    "min_admission": 1,
    "max_admission": null,
    "interval_seconds": 5.0
  }
}
```

| Rolling mean of the last `samples` windows | Admission limit |
| --- | --- |
| below `grow_below` for `grow_samples` consecutive windows | `+grow_step`, up to the ceiling |
| at or above `shrink_at` for `shrink_samples` consecutive windows | `-shrink_step`, down to `min_admission` |
| between the thresholds, or neither sustained | held |

The shrink default is larger than the growth default, so the fleet gives
concurrency back faster than it takes it, and a host hovering at the threshold
does not oscillate. The configured cap is a hard ceiling: the limit **starts**
there, so a fleet that is not saturated is unaffected, and growth only recovers
slots a sustained saturation removed. `max_admission` lowers that ceiling
deliberately for a host that should never run the full cap. The effective bound
at dispatch is `min(--workers, workers, admission limit)`.

**A lower limit never stops a running worker.** It only delays the next
launch; in-flight workers drain naturally and finish. The limit is applied
before model selection and never overrides anything else: per-model concurrency
and `reserve`, cooldowns, cost-aware selection, retry budgets, the shared Go
budget and the account-wide quota gate all keep their existing force. An
admission limit of 1 still runs work; it does not stall the fleet.

Host CPU is the kernel's `/proc/stat` aggregate line, first eight jiffy
counters. `guest`/`guest_nice` are **excluded** because the kernel already
counts guest time inside `user`/`nice` and including them would double count;
`iowait` counts as idle (waiting for IO is not compute pressure); `steal` counts
as busy. A counter reset, a malformed line or an unreadable `/proc/stat` is
reported as an explicit `supported: false` with the reason, and never throttles
and never claims CPU control it does not have. Sampling needs two readings, so
the first window is a baseline, not a measurement.

**Two scales, both named.** `cpu_percent` is a true 0..100 percentage.
`window_mean` is the 0..1 *fraction* over the rolling window, because that is
the scale `grow_below` and `shrink_at` are compared against; the thresholds in
the configuration are fractions too. `0.9` as a threshold and `90.0` as a
reported percentage are the same line on the same graph.

The limit is published to a separate `cpu-admission.sqlite` in the shared state
directory -- exactly as the Go budget cache is, and with no router schema change
-- so any client sees the current value:

```sh
python3 tools/opencode_router.py --config build/opencode-router.json status \
  | grep 'Host CPU admission'
python3 tools/opencode_router.py --config build/opencode-router.json budget \
  | python3 -c 'import json,sys; print(json.load(sys.stdin)["cpu_admission"])'
```

`status` and the compact `budget` JSON both carry a `cpu_admission` object:
`cpu_percent`, `window_mean`, `admission_limit`, `admission_maximum`, `cap`,
`controlling`, `state`, `stale`, `age_seconds` and the `reason` when nothing is
controlling. Each attempt additionally records the limit, the CPU reading and
the monitoring `error` that admitted it, so a dispatch can be explained after
the fact -- including a dispatch that happened while the monitor was broken.

**The status read is genuinely read-only.** It opens the cache `mode=ro` with a
short bounded lock wait, so it cannot create the state directory, the file or
the table, cannot take a write lock, and cannot stall behind a scheduler that is
mid-publish. A state directory with nothing published yields
`state: unpublished` and creates nothing; a read-only cache file is still
readable; a scheduler holding the lock is reported as `cache_busy`. Every field
in the cache is type- and range-checked on the way out, so a hand-edited or
truncated row is reported as `cache_invalid` instead of being multiplied,
compared or printed.

**Control is only claimed when it is real.** `controlling` is true only for
`state: controlling`, which requires a readable report, a fresh
`observed_at`, `supported: true` and no monitoring error. Every other condition
is named rather than inferred:

| `state` | meaning |
| --- | --- |
| `disabled` | `cpu_admission.enabled` is false; the cap is the only limit |
| `unpublished` | enabled, but no scheduler has published a reading yet |
| `controlling` | fresh, supported, no error: the admission limit is live |
| `unsupported` | this host does not report a measurable CPU aggregate; the limit stays at the cap |
| `stale` | the last reading is older than 3 intervals, or timestamped in the future |
| `error` | the report could not be read or validated, or the last monitoring tick failed |

A fresh-looking number from a host that cannot be measured is `unsupported`, not
control, and the numbers are still readable so the last known state is visible.

**A monitoring failure is reported, not swallowed.** The scheduler catches
everything CPU monitoring can raise, because host CPU measurement must never
stop dispatch or worker supervision. Silence would be its own lie, so the
controller records `monitoring_error` (with the exception in `error_detail`),
publishes it like any other report, and the status view shows `state: error`
with `controlling: false` until a working sample clears it. The limit is not
revoked and no worker is touched: a blind monitor never throttles.

Like every other option, this is read once at scheduler start. An old running
scheduler keeps its fixed cap and cannot enforce the limit: let useful work
finish, then start the next scheduler with the updated executable. The
`cpu-admission.sqlite` file is additive; deleting it only loses the published
reading until the next scheduler writes one. During a mixed-code window a
scheduler older than the percent scale publishes 0..1 where a current reader
expects 0..100, so the human line can read low or absurdly high; the admission
limit, `supported`, `stale` and `controlling` are unaffected. Restart the
scheduler to settle the scale.

### Zen routes and free-model validation

The explicit 2026-09-27 Zen request adds all **82 model IDs** from the public
`https://opencode.ai/zen/v1/models` catalog to the configuration. Catalog presence
proves an ID exists, not that it is free or available to this account. The 81
entries without runtime zero-price verification are registered but disabled.
Enabling a metered Zen entry is rejected by configuration validation; this is not
an authorization to spend a paid balance.

`opencode/space-bunny-free` is enabled and explicitly `metered: false`. OpenCode's
runtime `model.list` advertises zero input, output, cache-read and cache-write
prices and five reasoning variants: **low, medium, high, xhigh, max**. The router
rechecks enabled Zen pricing at scheduler startup, even if variant discovery is
disabled. Missing, malformed, nonzero, or unavailable price metadata blocks Zen
assignments. A free-looking name alone never establishes free billing. Do not
change local provider endpoints; these checks assume the trusted OpenCode catalog.

Each worker's provider policy allows only its selected provider. There is no
switch to paid Zen on Go exhaustion. Explicit free Zen work can proceed while Go
is exhausted; a quota/funds error on Zen cools down that model without falsely
marking the separate Go account exhausted. Existing Go quota events still block
metered Go workers.

```sh
python3 tools/opencode_router.py --config build/opencode-router.json run bulk \
  --model opencode/space-bunny-free#low 'Your bounded task'
```

A free Zen model that the account's runtime catalog **omits** (so no zero price
can be read) may carry `zen_free_override` with the operator's evidence text,
alongside `metered: false` and `unmetered_evidence`. It is admitted only when a
catalog was read successfully and does not list that ID: a listed model is
priced by the catalog and the override never overrules it, and an unread
catalog proves nothing, so Zen still fails closed.

All five declared suffixes can be requested using the same syntax. They share
one configured concurrency pool; they are not five independent model budgets.
An explicit unavailable variant is deferred with
`routing.requested_variant_unavailable`, rather than silently changing effort.
Default preferences are medium for bulk and high for reasoning/escalation. The
relative routing weight is a provisional preference, not a price or proof of
BFME quality. Existing parent-verified progress metrics continue to apply.

A one-shot, tools-denied test of `opencode/space-bunny-free#low` succeeded with
`SPACE_BUNNY_OK` and local reported cost zero. The Go version previously returned
HTTP 402; these are distinct provider routes. This smoke establishes connectivity,
not reconstruction quality. The main queue was not run as part of the test.
Zen regression coverage includes catalog registration, missing/nonzero price
rejection, all five explicit variants sharing capacity, provider isolation, and
independent Go/Zen quota handling.

### Reasoning variants

OpenCode **v2.0.18** selects variants with `--model provider/model#variant`.
There is no separate `--variant` flag in this version. After the existing model
selection, the router chooses a supported variant using the job's **current tier**:

| Tier | Preference, in order |
| --- | --- |
| bulk | medium, low, minimal, none |
| reasoning | high, medium, low, minimal |
| escalation | max, xhigh, high, medium, low, minimal |

Only names in the model's capabilities are eligible. If none fit, omit the suffix
and keep OpenCode's default behavior; bulk does not automatically select max just
because it is the only listed variant. A model's per-tier preference overrides
the first choice; an unsupported preference falls through to the table.
Reasoning/escalation do not fall back to explicit `none`: when stronger levels
have provider-specific names, keep the default until an override supplies one.

`variant_discovery` defaults to `true`. Once per scheduler invocation, the router
reads the location-scoped `opencode api model.list` snapshot from the background
service (the CLI may start that service). It makes no inference request. Only Go
model IDs and variant names are retained in memory. The catalog is read through
a private temporary file because v2.0.18 can truncate large JSON output to pipes.
No database transaction is held during discovery; it times out after 10 seconds.
An empty/malformed snapshot, unavailable CLI, or API failure uses configured
capabilities instead. Missing metadata means the existing unqualified launch.

Optional fields on an individual model entry:

```json
{
  "variants": ["low", "medium", "high", "xhigh"],
  "variant_preferences": {
    "bulk": "medium",
    "reasoning": "high",
    "escalation": "xhigh"
  }
}
```

Add these fields to the existing entry alongside its ID, tier and limits.
`variants` supplies fallback capabilities and, when discovery works, restricts
the runtime list by intersection. An empty array disables explicit variants.
A preference of `null` keeps the unqualified model for that tier. Set global
`variant_discovery: false` to use only explicit Go capabilities. Enabled Zen
models still require a runtime catalog check for their free pricing. Preferences alone
never assert support. Existing IDs containing `#variant` remain accepted as an
explicit preference/capability when runtime metadata is absent.

Run `discover` to inspect current capabilities and effective choices. The example
Go config avoids copying catalog metadata; its MiniMax M3 override maps bulk to
`none` and reasoning/escalation to `thinking`, its provider-specific names.
Observed catalog examples on 2026-09-27:

| Model | Bulk / reasoning / escalation |
| --- | --- |
| Muse Spark 1.3 Contributor | medium / high / high |
| GPT 6 Luna | medium / high / high |
| GLM-5.3-Flash | low / high / high |
| Qwen3.8 Flash | medium / medium / xhigh |
| MiMo V2.6 Flash, Kimi K2.7 Code | default / default / default (no listed variants) |

Catalog capability is not account access or proof of equivalent reasoning budgets
across providers. No variant outcome changes model weights automatically.

A structured variant rejection removes that choice for the job's later attempts;
the next eligible model uses its own supported fallback. If necessary, retry
without a suffix. These errors use the existing availability retry bound, without
counting as failed reconstruction or cooling down the entire model. Quota errors
still record the existing model cooldown and additionally latch shared exhaustion. Providers never change here.

### Agent steps and running fleets

Reasoning effort and agent iterations are independent. The router sets no agent
`steps` limit. The inspected build agent also has no configured limit. OpenCode's
runner applies its step ceiling only when `steps` is present; otherwise a turn
continues until completion, interruption, or another limit. Router wall-time and
output limits still apply. At a configured final step, OpenCode disables tools
and requests a text summary; new user input resets the allowance.

No step budget is changed by this feature. Per-tier step budgets could later
bound unproductive exploration and encourage a final handoff before timeout,
but should be measured separately from variant choice.

Existing CLI commands remain available; shared budget checks now constrain model selection. State gains one nullable
attempt column under the existing short initialization lock. Old attempts remain
`variant: null` (default/unknown); measurements and statistics are preserved.
Old schedulers can continue inserting their explicit columns. New schedulers
discover variants at startup; running workers keep their launch settings. There
is no need to stop other fleets or reset state to deploy this change.

## Reviewing and integrating a job

`tools/router_integrate.py` is the parent step the router leaves open. It trusts
nothing a worker reported:

```sh
python3 tools/router_integrate.py review JOB_ID      # exit 0 only if a target landed and nothing needs a human
python3 tools/router_integrate.py integrate JOB_ID --dry-run
python3 tools/router_integrate.py integrate JOB_ID --push --measure
```

`review` diffs the workspace against its base (staged work included, so a worker
that ran `git add` is still seen), runs the scoped gate on every touched source
in the workspace, and flags renamed rows, new inline asm/naked code, lifts left
behind and mutating git commands. Every changed path is routed explicitly: `game/`,
`worldbuilder/`, `targets/` and `inputs/reference/shims/` are ported and
staged; an untracked top-level scratch file is skipped with a note; anything
else (vendored references, `tools/`, `docs/`, hooks) is a review problem and
`integrate` refuses it rather than dropping it. A port that carried only `game/`
and `targets/` once left a shim-header edit behind: the hook compiled the
working tree and passed while the commit could not build. Naked code added to a
*modified* source and a gutted index (hundreds of staged deletions of files
still on disk) are flagged too. `integrate` ports the work onto a clean
detached worktree at `origin/master` (`build/wt/integrate`): source edits as a
3-way patch, new files copied, deletions applied, ledger rows moved line by line
with their CRLF endings so concurrent upstream rows survive. It then runs
`check_csv`, the scoped gates again on the new base, and an ordinary commit so
the hooks run the full verification. A hook request for
`tools/adopt_header.py --fix-staged` is applied once; a name regression is never
documented automatically -- read the worker's identity evidence and record the
correction yourself (`docs/naming_evidence.md`). `--push` rebases and retries
a push only on a proven stale-base race (Git's fetch-first, non-fast-forward or
stale-info rejection, or the pre-push hook's `PUSH RACE` ancestry guard), up to
`--push-retries` attempts; validator, auth, transport and bare lock failures
stop at once with the push output, keeping the commit locally. `--measure` records the verified result on the job's last attempt.
Neither command modifies or deletes the job workspace.

## Evidence and performance records

Every attempt preserves `prompt.txt`, raw `events.jsonl`, `stderr.txt`, model, variant,
category/tier, start/end time, exit status, session ID, workspace and outcome.
Workers emit a final `ROUTER_RESULT` JSON line with approaches, files touched,
compiler/test results, remaining differences, disproved hypotheses and discoveries.
The next attempt receives that structured history plus artifact paths and text
excerpts, including when a crash prevents a structured report. Malformed/missing
reports never become successes merely because OpenCode exited zero.

`status --json` exports jobs, attempts, model counts/durations and measurements,
plus `configurations` grouped by model + selected variant + original category +
current tier. These include success/failure counts, duration, variant rejections
and parent-verified exact-match counts. Attempt records expose `duration_seconds`;
`show JOB_ID` includes variant history. Unqualified/old attempts are not claimed
to have used a particular provider reasoning effort.
Join attempts by job and start time to examine retries, promotion, source and
destination model, and per-category success. These data support later tuning;
there is no claim that initial weights predict BFME performance.

Exact match, match improvement, and compile iteration counts default to **null**.
The parent can attach verified measurements after reviewing real tool evidence:

```sh
python3 tools/opencode_router.py measure ATTEMPT_ID --exact-match yes \
  --improvement 0.04 --iterations 3 --evidence 'build/probe-report.json; scoped gate EXACT'
```

Improvement is a fraction (0.04 means four percentage points), not bytes. Omit
unmeasured values. These are explicitly parent-supplied measurements, not parsed
model assertions; preserve the named gate/probe report.

## Verification and sources

Run focused tests with:

```sh
python3 -m unittest discover -s tools/tests -p 'test_opencode*.py' -v
```

Tests use a fake CLI with real subprocesses and the repository's cgroup helpers;
they require delegation like production. They cover account quota deferral/recovery, cooldown,
retry bounds/promotion, handoff, concurrency, duplicate/overlapping work, shell
metacharacters, protocol failures, detached children, scheduler SIGKILL with a
surviving timeout supervisor, Ctrl-C, and state-loss refusal.
Variant tests additionally cover per-tier/per-model selection, unsupported choices,
catalog outages, old-state migration with concurrent readers, legacy writers,
quota deferral/recovery, promotion, argument construction and grouped statistics.

Verified 2026-09-27 against OpenCode v2.0.18: CLI help, stdin task input, JSONL
text/error events, explicit models, configuration injection, and public catalog.
All 20 configured IDs were present in the Go catalog. Real concurrent router
smokes succeeded on `opencode-go/mimo-v2.6-flash` and
`opencode-go/glm-5.3-flash`; `opencode-go/deepseek-v4.1-flash` returned a regional
availability restriction. No large fleet or intentional real quota exhaustion
was run. Simulated 429 tests now prove shared deferral and meter-confirmed recovery without consuming an account limit.
The variant extension also passed tiny real router runs on
`opencode-go/gpt-6-luna#high` (reasoning) and
`opencode-go/glm-5.3-flash#low` (bulk), with both selected variants independently
confirmed through OpenCode's `session.get` API. These are invocation checks,
not evidence that either configuration is better at BFME reconstruction.

Primary references: [Go IDs, limits and paid-overage setting](https://opencode.ai/v2/docs/console/go),
[v2 API](https://opencode.ai/v2/docs/api),
[provider policies](https://opencode.ai/v2/docs/policies),
[configuration](https://opencode.ai/v2/docs/config).
Variant syntax and provider semantics: [models](https://opencode.ai/v2/docs/models).
Step behavior: [agents](https://opencode.ai/v2/docs/agents),
[runner source](https://github.com/anomalyco/opencode/blob/dev/packages/core/src/session/runner/llm.ts).

Prior economics validation (before shared pacing): 38 focused tests passed,
including the former per-model failover behavior, now superseded by shared deferral. A one-request real smoke
selected Muse `#medium` and returned `provider.quota` (429, Go usage limit
exceeded); no further quota probing or large fleet was launched.

Shared-budget validation: 57 focused tests cover parsing, all threshold edges,
missing credentials, stale/cache failures, source timestamps and timezone edges,
quota races/recovery, explicit overrides, free-model evidence, and existing
variant/cost/containment behavior. The monitoring smoke uses status only; no
new inference or deliberate allowance consumption is required.


## Integration and publication checks

`tools/router_integrate.py` locks each destination across review, port, commit
and push. It requires a clean detached destination whose HEAD is already
contained in the chosen base. Retained edits, staged work, unfinished Git
operations and unpushed commits are refused and left recoverable. `--keep`
explicitly combines unstaged work and stops before committing. Conflicting
upstream additions and symlinked port paths require manual review. Source
changes during review or port require a new review; every touched-source gate
and ledger check must exit successfully.

Publication receipts never remove selected rows from the ordinary gate.
Compile/object reuse remains enabled. String and constant bytes, baseline
identity, DIR32 mappings/whitelists and combined-row agreement are checked on
every publication attempt, even when all receipts hit. Scoped consistency
checks do not write the full address-ledger proposal. Invalid receipts miss;
unrecordable evidence after successful verification is distinct from a failed
verification. Rules, toolchains and file fingerprints are shared only within
an invocation and validated again for mutation before recording.
