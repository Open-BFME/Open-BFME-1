# OpenCode Go worker router

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
`opencode-go/…` IDs are accepted; every invocation passes `--model`. An injected
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
within the retry budget; it does not abandon unbounded background work.

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
repository's **HEAD**. Uncommitted parent changes are not copied. All retries
reuse that job's workspace, so failed source experiments remain available.
`--cwd /absolute/prepared/worktree` uses a parent-prepared workspace instead.
The scheduler serializes overlapping workspace paths, even for redundant jobs.
It sets both the process cwd and `PWD`: OpenCode run uses the latter to choose
its session location, so changing cwd alone does not isolate linked worktrees.
It never deletes worktrees or worker artifacts; remove reviewed worktrees using
normal Git worktree commands when finished.

The default state directory is `opencode-router/` under the **common Git
directory**, shared by linked worktrees. Separate clones must explicitly share
one `--state` on the same host if they are to share limits. Use one configuration
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
- `availability_retries`: separate quota/unavailable retry bound (default 20).
- `cooldown`: seconds before reconsidering quota/unavailable models (default 300).
- `failure_cooldown`: brief cooldown for genuine worker failures (default 20).

Quota errors do not spend the reasoning-failure budget. Structured error events
are classified by status/type/message; text *discussing* quotas is not an error.
A model in cooldown is skipped immediately while other jobs/models proceed.
Expired cooldowns permit another request. If every eligible model is unavailable,
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
An explicit `--model` remains an intentional override, including for bulk.

Models without dashboard calibration (LongCat, MiMo Pro, DeepSeek Pro, Kimi K3,
Grok, GLM-5.3 and Qwen Max) are retained but disabled. To enable one, verify its
cost, assign `relative_cost`, keep `escalation_only: true`, and enable it.
All invocations remain restricted to Go; none can select a paid provider.

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

The current public Go docs still describe **per-model** dollar limits; a shared
account budget has not been verified. Regardless of limit topology, this policy
optimizes economical progress, not quota consumption. There is no supported
remaining-Go-allowance endpoint verified here; keep response-driven cooldowns.

#### Updating active installations

Old configurations lacking `cost_aware` retain their previous behavior. Copy the
new `models`, `cost_aware`, `cheap_failures_before_escalation` and `cost_basis`
fields into your local config, preserving credentials-free local settings and
`go_overage_disabled`. Schedulers load config once: apply after the current
scheduler finishes; do not interrupt useful workers merely to reload policy.
Queues choose models at dispatch and need no state rewrite. Explicit queued
`--model` requests remain overrides and must be reviewed separately. The new
measurement table is additive; old writers and old attempt records still work.

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
`variant_discovery: false` to use only explicit capabilities. Preferences alone
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
still use the existing model cooldown/failover path. Providers never change here.

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

Existing CLI commands and model selection are unchanged. State gains one nullable
attempt column under the existing short initialization lock. Old attempts remain
`variant: null` (default/unknown); measurements and statistics are preserved.
Old schedulers can continue inserting their explicit columns. New schedulers
discover variants at startup; running workers keep their launch settings. There
is no need to stop other fleets or reset state to deploy this change.

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
python3 -m unittest discover -s tools/tests -p test_opencode_router.py -v
```

Tests use a fake CLI with real subprocesses and the repository's cgroup helpers;
they require delegation like production. They cover quota failover, cooldown,
retry bounds/promotion, handoff, concurrency, duplicate/overlapping work, shell
metacharacters, protocol failures, detached children, scheduler SIGKILL with a
surviving timeout supervisor, Ctrl-C, and state-loss refusal.
Variant tests additionally cover per-tier/per-model selection, unsupported choices,
catalog outages, old-state migration with concurrent readers, legacy writers,
quota failover, promotion, argument construction and grouped statistics.

Verified 2026-09-27 against OpenCode v2.0.18: CLI help, stdin task input, JSONL
text/error events, explicit models, configuration injection, and public catalog.
All 20 configured IDs were present in the Go catalog. Real concurrent router
smokes succeeded on `opencode-go/mimo-v2.6-flash` and
`opencode-go/glm-5.3-flash`; `opencode-go/deepseek-v4.1-flash` returned a regional
availability restriction. No large fleet or intentional real quota exhaustion
was run. Simulated 429 tests prove failover without consuming an account limit.
The variant extension also passed tiny real router runs on
`opencode-go/gpt-6-luna#high` (reasoning) and
`opencode-go/glm-5.3-flash#low` (bulk), with both selected variants independently
confirmed through OpenCode's `session.get` API. These are invocation checks,
not evidence that either configuration is better at BFME reconstruction.

Supported Go docs expose usage in the console; `stats` reports historical local
usage, not remaining Go allowance. No reliable supported remaining-quota endpoint
was found in CLI help or the published v2 API, so the router uses actual failures
and cooldowns rather than estimating remaining tokens or scraping private state.

Primary references: [Go IDs, limits and paid-overage setting](https://opencode.ai/v2/docs/console/go),
[v2 API](https://opencode.ai/v2/docs/api),
[provider policies](https://opencode.ai/v2/docs/policies),
[configuration](https://opencode.ai/v2/docs/config).
Variant syntax and provider semantics: [models](https://opencode.ai/v2/docs/models).
Step behavior: [agents](https://opencode.ai/v2/docs/agents),
[runner source](https://github.com/anomalyco/opencode/blob/dev/packages/core/src/session/runner/llm.ts).

Economics validation (2026-09-27): 38 focused tests passed, including simulated
quota failover with cost-aware routing and variants. A one-request real smoke
selected Muse `#medium` and returned `provider.quota` (429, Go usage limit
exceeded); no further quota probing or large fleet was launched.
