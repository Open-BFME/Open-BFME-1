# BFME 1.03 variable-FPS timing patch

## Status and purpose

This directory contains an experimental, local-only timing patch for the
32-bit retail BFME 1.03 executable. It lets rendering run between 15 and
60 FPS while keeping authoritative gameplay at BFME's normal 5 Hz cadence.
Rendering, simulation, animation, particles, camera input, UI presentation,
loading, pause, and multiplayer admission do not all consume the same clock;
the patch separates those responsibilities instead of globally multiplying
one engine timer.

The current DLL SHA-256 is:

```text
31E73BDF8CDEEE0B373C4F13B738B79540395A27C900DA7CEEFD95955CAAC0D6
```

The patch is intentionally limited to 15-60 FPS. It does not patch BFME's
configured render cap. `FramesPerSecondLimit` must be set separately, and must
not be set above 60 for this build. A 120-FPS experiment produced a retail
access violation and was reverted; that failure is not considered solved.

## Goals

- Keep authoritative gameplay at 5 Hz at every visual rate from 15 through
  60 FPS.
- Keep movement, construction, combat timers, economy, AI, and deterministic
  state on BFME's native authoritative update path.
- Keep animation speed constant in real time from 15 through 60 FPS.
- Intentionally slow both logic and animation below 15 FPS by the same factor,
  so a machine that cannot sustain 15 FPS does not separate visible animation
  from gameplay.
- Keep camera motion real-time even below 15 FPS.
- Preserve BFME's authored 30-Hz FX/particle interpretation without editing
  any INI files.
- Preserve native multiplayer frame admission, command completeness, router
  pacing, frame ceilings, and synchronization checks.
- Preserve native single-player pause semantics while allowing the menu,
  pause ornament, spellbook, and other presentation UI to animate as retail
  expects.
- Discard time accumulated during loading, process suspension, and long stalls
  instead of performing simulation catch-up bursts.

## Non-goals

- This is not a general executable patcher and does not support unknown BFME
  builds. It verifies retail 1.03 byte signatures before installing hooks.
- It does not increase the render limit above 60 FPS.
- It does not modify weapon INIs, particle INIs, BIG archives, maps, replays,
  network packets, or authoritative object state.
- It does not replace BFME's lockstep/network implementation.
- It does not make a machine below 15 FPS simulate at 5 Hz. The slowdown below
  15 FPS is deliberate.
- It does not add multithreading.

## User-visible timing model

The core policy is:

```text
logicHz = 5                                  when visualFPS >= 15
logicHz = 5 * (visualFPS / 15)               when visualFPS < 15

slowdown = min(1, visualFPS / 15)
animationDelta = realRenderDelta * slowdown

cameraDelta = realRenderDelta                at every supported FPS
```

Representative steady-state behavior is:

| Visual FPS | Logic Hz | Logic interval | Gameplay/animation speed | Effective FX cadence | Camera speed |
|---:|---:|---:|---:|---:|---:|
| 60 | 5 | 200 ms | 1.0x | 30 Hz | 1.0x |
| 45 | 5 | 200 ms | 1.0x | 30 Hz | 1.0x |
| 30 | 5 | 200 ms | 1.0x | 30 Hz | 1.0x |
| 20 | 5 | 200 ms | 1.0x | 30 Hz | 1.0x |
| 15 | 5 | 200 ms | 1.0x | 30 Hz | 1.0x |
| 12 | 4 | 250 ms | 0.8x | 24 Hz | 1.0x |
| 10 | 3.333... | 300 ms | 0.666...x | 20 Hz | 1.0x |
| 5 | 1.666... | 600 ms | 0.333...x | 10 Hz | 1.0x |

"Effective FX cadence" means the authored 30 particle frames per animation
second multiplied by the intentional slowdown. It is not the render rate.

## Why BFME needs more than one clock

Retail BFME was authored around 30 visual frames per second and five
authoritative updates per second. One 200-ms logic interval therefore contains
six legacy client phases. Simply rendering the original update loop twice as
often creates several independent failures:

- authoritative phase 1 may execute too often;
- animations authored as increments per visual frame run too fast;
- particles whose lifetimes, bursts, and drift are expressed in authored
  frames run too fast;
- camera displacement applied once per rendered frame doubles;
- integer client-frame interpolation can alternate between old and new states;
- global clock freezing can stop UI presentation that retail intentionally
  leaves active during pause;
- global clock pass-through can leave world models animating during pause;
- a timer-owned tick can be lost when native multiplayer admission blocks it.

The patch therefore maintains several related but separate clocks:

| Clock/state | Source | Consumer | Pause/stall behavior |
|---|---|---|---|
| Render wall time | `QueryPerformanceCounter` | FPS estimator and visual timing | Rebased across gaps over 750 ms |
| Authoritative accumulator | Active render delta | Permission to offer phase 1 | Frozen or discarded at lifecycle boundaries |
| Animation delta | Render delta times slowdown | W3D/world animation | Zero during true pause |
| Visual phase | Animation delta divided by 200 ms | Client interpolation and floating text | Held during pause; reset after an admitted tick |
| FX fixed-frame clock | Animation delta | Particle manager at authored 30 Hz | No updates during true pause |
| Camera delta | Unscaled render delta | Keyboard, edge, and RMB scrolling | Real-time; independent of low-FPS slowdown |
| Shared WW3D absolute clock | Retail absolute milliseconds with active-world scaling | W3D plus APT/UI presentation | Passed through and rebased while inactive/paused |

## DLL loading and safety model

`dinput8.dll` is a proxy. BFME loads it from the game directory, and it then
loads the real system `dinput8.dll` and forwards `DirectInput8Create`. A worker
thread waits for BFME's engine globals to be initialized before applying the
patch.

The installer checks the expected retail bytes at every active hook site and
requires the original W3D frame duration to be 33 ms. If any signature differs,
the patch refuses to install instead of writing to an unknown executable.
Hooks are installed with writable/executable protection only for the required
region, followed by an instruction-cache flush.

The active installation list in `apply()` is authoritative. The source still
contains some inactive reverse-engineering helpers and proof/dump routines from
earlier experiments; a function merely existing in the source does not mean it
is installed. Current active changes are:

| Area | Retail location | Purpose |
|---|---:|---|
| GameEngine scheduler decision | RVA `0x6E910 + 0xC7` | Decide whether phase 1 is timer-due or still pending |
| GameEngine reset | RVA `0x6E7A0 + 0xA2` | Rebase all DLL-owned timing state |
| GameLogic update entry | RVA `0x38DA10` | Confirm that native admission actually executed the tick |
| WW3D absolute sync | RVA `0x8FD310` | Maintain active-world elapsed time without breaking UI/shell clocks |
| W3D model/HLOD setter | RVA `0x97A220` | Hold the known world-model feeder during true pause |
| Floating text | RVA `0x43F328` | Use continuous phase rather than alternating integer-frame position |
| Particle update call | RVA `0x6EB55D` | Dispatch authored 30-Hz particle steps |
| Particle rendering | RVA `0x6FA9B0` plus six getters | Interpolate position and continuous properties between FX steps |
| Tactical camera view | vtable slot `0x48` | Scale camera displacement by real render time |

## Authoritative 5-Hz scheduler

### Legacy phases

Phase 1 is the authoritative/network-gated phase. Phases 2 through 6 are
legacy client slices. The timer controls only phase 1.

At high visual FPS, extra rendered frames update presentation while the timer
waits for the next 200-ms authoritative opportunity. At a visual rate below
30 FPS, fewer than six render calls may occur during 200 ms, so
`complete_legacy_phases()` finishes any missing phases 2 through 6 in order
before offering phase 1. Those completion calls do not create extra
authoritative updates.

This is why "5 Hz logic" does not mean the entire engine runs only five times
per second. UI, rendering, client interpolation, audio, and other client work
continue at their appropriate presentation cadence.

### FPS measurement

Each valid render delta produces an instantaneous FPS estimate clamped to
1-240. The scheduler smooths it with an approximately half-second response:

```text
alpha = delta / (0.5 + delta)
measuredFPS += (instantFPS - measuredFPS) * alpha
```

The smoothing avoids changing low-FPS policy because of one noisy frame. A
non-positive delta or a gap over 750 ms is classified as a suspension/large
stall and is not accumulated.

### No simulation debt

The scheduler executes at most one newly admitted authoritative update at an
opportunity. It never loops GameLogic to catch up. Loading, logic replacement,
GameEngine reset, a large wall-clock gap, and a pending tick invalidated by true
pause rebase the accumulator as appropriate.

When FPS recovers from below 15, any remainder larger than the restored 200-ms
interval is clamped so low-FPS slowdown cannot become future catch-up debt.

## Multiplayer admission and the 200 -> 215 ms case

### The invariant

```text
the DLL timer says when an authoritative tick is due
BFME's native network code says when that due tick may execute
```

The DLL never calls `GameLogic::update` directly. A due opportunity is routed
through retail `GameEngine::_bfme_updateNetworkAndLogic(1)`.

For phase 1, retail BFME:

1. checks the real single-player pause state;
2. calls `TheNetwork->getFrameAdvanceCount()` when a network exists;
3. only when the returned allowance is positive, calls `beginUpdate()`,
   `Network::update(1)`, and `endUpdate()`;
4. then calls `GameLogic::update(1)`;
5. otherwise clears `GameClient::m_advanceFrame` and does not execute logic.

On a guest/non-router, `getFrameAdvanceCount()` enforces the frame ceiling and
command completeness. It may pump incoming network packets while commands are
incomplete, but it does not consume the next command set. On the packet router,
the same getter owns its 5-Hz pacing accumulator and router-stall check.

These blocked checks are intended to be polled. Retail GameEngine retains its
overdue phase state and retries on a following render.

### The earlier DLL regression

The first variable-FPS scheduler subtracted 200 ms as soon as its timer became
due and set `g_dueInFlight`. If native BFME then blocked the phase-1 attempt,
the next scheduling callback cleared `g_dueInFlight` merely to report the
block. The consumed timer interval was not restored.

The result could be:

```text
0 ms:    previous authoritative tick executes
200 ms:  DLL timer says due; native network gate says "not ready"
215 ms:  commands become ready
~216 ms: old DLL has already discarded the due opportunity
400 ms:  a new timer interval finally becomes due and can execute
```

A 15-ms command delay could therefore become almost 200 ms of additional,
unnecessary simulation delay.

### Current pending-tick solution

Creation, presentation, admission attempt, and execution are separate events.
The scheduler now has:

- `g_pendingTick`: one timer-due authoritative tick exists;
- `g_pendingInterval`: the interval that created that tick;
- `g_admissionAttemptInFlight`: the current render has presented that tick to
  native admission;
- the GameLogic entry hook: proof that native admission allowed execution.

Conceptually:

```text
accumulator += activeDelta

if no tick is pending and accumulator >= currentInterval:
    create exactly one pending tick
    remember its interval
    complete legacy phases 2..6 exactly once

if a tick is pending:
    present the same normal phase-1 opportunity to BFME

only when the GameLogic entry hook runs for that attempt:
    clear pending
    accumulator -= remembered interval
    retain a short remainder
    discard remainder if it contains another whole stale interval
```

The intended short-delay timeline is now:

```text
0 ms:    previous authoritative tick executes
200 ms:  timer creates one pending tick; native gate blocks it
215 ms:  required commands arrive
~215-216 ms, at the next render opportunity:
         the same pending tick is offered again and executes once
         accumulator remainder is about 15 ms
400 ms:  the next nominal tick becomes due
```

At 250 ms admission, roughly 50 ms remains, so the next nominal opportunity is
still around 400 ms.

For a long block:

```text
200 ms: tick becomes pending
400 ms: it is still the same pending tick; no second pending tick is created
550 ms: native BFME finally admits one tick
```

At 550 ms, subtracting the remembered 200-ms interval would leave 350 ms,
which already contains another complete interval. That remainder is stale debt
and is discarded. The scheduler executes no 551/552-ms burst and resumes with
a fresh cadence, making the next opportunity roughly 200 ms later.

### Is this better than vanilla networking?

Not in the sense of reducing ping, changing lockstep, increasing network tick
rate, or bypassing a retail safety check. Vanilla BFME already retries an
overdue phase-1 opportunity after a blocked attempt. The current change restores
that retail-like behavior after the earlier DLL accidentally lost the timer
opportunity.

It is a real improvement over the previous variable-FPS DLL: once network data
becomes ready, the avoidable extra delay is reduced from as much as nearly one
5-Hz interval (about 200 ms) to the next render opportunity. At 60 FPS that is
normally within about 16.7 ms; at 30 FPS it is normally within about 33.3 ms.
Actual network latency and BFME's admission decision remain unchanged.

### Different visual FPS in multiplayer

A player at 15 FPS and a player at 60 FPS both target 5 authoritative updates
per real second. Their render opportunities differ, but native BFME still owns
the legal lockstep advance. The patch never treats a high render rate as
permission to advance authoritative state.

Below 15 FPS, the local target intentionally falls below 5 Hz. In multiplayer,
native lockstep may consequently make other peers wait for the slow machine;
the patch does not claim to eliminate that fundamental synchronization cost.

## Animation and WW3D time

Earlier 60-FPS-only experiments used constants such as `* 0.5`, timer `* 2`,
or replacing 33 ms with alternating 16/17 ms. Those corrections work only for
one exact render rate. The current model derives animation progress from actual
render delta and the below-15 slowdown policy.

`advance_visual_time()` calculates:

- `realRenderDelta` for camera/presentation uses;
- `animationDelta` for world animation and FX;
- `frameScale = 30 * animationDelta` for diagnostics and retained legacy-path
  investigation helpers;
- `visualPhase += animationDelta / 0.2` for interpolation between logic ticks;
- an integer W3D frame duration with a fractional-millisecond remainder.

The current `apply()` path does not install the older per-controller
`frameScale` experiments. Active general animation correction comes from the
W3D frame-duration/global-clock path; the unused helpers remain in the source
as reverse-engineering evidence and should not be described as live hooks.

The fractional remainder prevents systematic drift at rates whose render
period is not an integer number of milliseconds.

WW3D also consumes absolute millisecond timestamps from multiple callers. The
hook tracks caller-local input history so one caller cannot make another
caller's transformed timeline jump. During active simulation, callers that
have not already received scaled frame time use the low-FPS slowdown. During
startup, loading, shell presentation, or true pause, the retail absolute clock
is passed through and the transformed state is rebased.

That pass-through is essential: APT/menu animation, the red pause ornament,
the spellbook opener, and the main-menu shell map consume presentation time
even when world simulation should not advance.

## FX and particles

Particle INIs express values such as `Lifetime`, `SystemLifetime`,
`BurstDelay`, color keys, alpha keys, drift, and sprite frames in an authored
frame domain. Running the particle manager once per visual render made effects
such as Elven Woods butterflies run too quickly at 60 FPS.

The patch gives the particle manager a fixed authored cadence of 30 updates per
animation second:

- 60 FPS: one FX update every two renders;
- 30 FPS: one FX update every render;
- 20 FPS: some renders execute one update and some execute two;
- 15 FPS: two FX updates per render;
- below 15 FPS: 30 Hz multiplied by the same intentional slowdown as logic and
  animation.

Multiple FX steps may be performed in one render when required, with a guard
against pathological bursts. A true pause performs no particle update and does
not accumulate pause debt.

Above 30 FPS, particle simulation cannot create a new authoritative particle
position every render. The render hook temporarily interpolates particle
positions and six continuous scalar properties between the previous and
current 30-Hz FX states, calls the original renderer, and restores raw state
after drawing. This is presentation-only; it does not rewrite the particle
simulation state.

Static fire, flares, GPU fire sprites, butterfly drift, lifetimes, bursts, and
wind therefore retain their authored 30-FPS appearance without changing INIs.

## Camera, floating text, and movement presentation

Camera scrolling in retail applies a displacement once per visual frame.
Keyboard, screen-edge, and right-mouse scrolling converge on the patched
TacticalView virtual method. The DLL scales a local copy of the displacement by
`30 * realRenderDelta`, capped only to avoid a single pathological jump. It
does not use the below-15 gameplay slowdown, so camera speed remains real-time.

Floating income numbers previously combined an integer client-frame value with
logic-frame position. At 60 FPS that could alternate between inconsistent old
and new positions and visibly move down, up, and down. The floating-text hook
uses the continuous visual interpolation phase and the actual visual period.

General unit interpolation continues to use BFME's client-frame ratio. The
patch updates that ratio from continuous phase and, critically, retains native
client bookkeeping when phase 1 is blocked or paused. It does not write an
interpolated transform back into authoritative object position.

## Pause and UI presentation

"Menu visible" and "simulation paused" are different states:

- single-player Esc: menu visible and true gameplay pause;
- multiplayer Esc: menu visible while gameplay continues;
- single-player `~`: overlay visible while gameplay continues;
- exit confirmation: presentation state changes while the underlying
  single-player match remains paused.

Several tempting global fixes were wrong:

1. Freezing the shared WW3D clock stopped world animation but also suppressed
   the red pause ornament and spellbook presentation.
2. Passing the clock through restored UI presentation but allowed soldiers to
   loop their running animation in place.
3. A global Animatable3DObj progression hook suppressed the ornament again and
   did not catch every manually driven soldier/worker animation path.
4. Bypassing too much native phase-1 behavior allowed worker/tree client state
   to twitch, especially near 15 FPS.

The final separation is:

- true pause still routes through retail `_bfme_updateNetworkAndLogic(1)`;
- retail clears `GameClient::m_advanceFrame`, holding subsequent drawable and
  interpolation advancement;
- `WindowManager::update` has already run, so menu presentation remains alive;
- DLL animation delta and particle updates are zero;
- the shared WW3D absolute clock is passed through for UI;
- only the known W3DModelDraw world-model feeder at absolute caller
  `0x00B5CA51` is held on its existing motion/frame;
- unrelated HLOD callers, including menu presentation, are not frozen;
- the DLL does not pin GameEngine's phase or interpolation ratio fields.

On unpause, clocks have been rebased and no paused wall time becomes an
animation jump, FX burst, or logic catch-up.

## Shell, loading, focus, and suspension

The main menu's Sauron's-tower fly-in is a live shell map, not a tutorial movie.
Transforming the shared WW3D clock before an active gameplay visual clock
existed could make that shell map render black. The current build passes retail
time through during shell/startup/loading and only applies active-world timing
once the simulation lifecycle is valid.

The scheduler tracks the GameLogic pointer, game mode, and loading flags.
Object replacement, mode transition, loading, and GameEngine reset rebase DLL
state. A render gap over 750 ms is classified as suspension/large stall and is
discarded. This prevents Alt-Tab or debugger suspension from generating logic,
animation, or FX debt.

The diagnostic CSV records foreground state and native pacing fields, but the
DLL intentionally does not force `m_maxFPS`, `LimitFrameRate`, or limiter
globals every frame. A previous 60 -> 30/15 -> 60 Alt-Tab report motivated the
instrumentation; the design preserves native foreground restoration rather
than masking it with a permanent 60-FPS write.

## Combat, projectiles, economy, and authoritative state

Weapon values such as `DelayBetweenShots`, `PreAttackDelay`,
`FiringDuration`, and projectile `WeaponSpeed` remain on BFME's native logic
clock. They are already expressed as milliseconds or distance per second and
are advanced by authoritative simulation. The patch adds no per-render weapon
or projectile multiplier.

The same rule applies to movement distance, construction percentage, castle
unpacking, resources, AI, pathfinding, formations, damage, and script timers:
their state changes only through the native GameLogic phase. From 15 through
60 FPS they run at normal real-time speed; below 15 they intentionally slow
with the reduced logic cadence.

## Pending-tick lifecycle rules

| Event | Pending tick | Accumulator behavior |
|---|---|---|
| Native network temporarily blocks | Retained and offered again | Active time continues accumulating |
| Native GameLogic entry occurs | Cleared | Subtract remembered interval; retain only a short remainder |
| True single-player pause while pending | Discarded | Rebased so pause creates no debt |
| Multiplayer menu without true pause | Retained normally | Gameplay continues |
| Loading transition | Discarded | Reset to zero |
| GameLogic object or mode replacement | Discarded | Reset to zero |
| GameEngine reset | Discarded | Full timing reset |
| Render/process gap over 750 ms | Discarded | Reset to zero |
| FPS crosses 15 while pending | Retained | The interval that created the tick remains fixed until completion/discard |

## Diagnostics

The DLL writes:

```text
C:\BFME1\BFME_MULTIPLAYER_TICK_DIAGNOSTIC.csv
```

The included CSV is header-only. Copy it beside `lotrbfme.exe` for a clean
test. The DLL appends rows rather than deleting earlier data.

Important event labels are:

- `TIMER_NOT_DUE`
- `TIMER_DUE_NEW`
- `TIMER_DUE_ALREADY_PENDING`
- `NATIVE_ADMISSION_BLOCKED`
- `NATIVE_ADMISSION_ALLOWED`
- `GAMELOGIC_EXECUTED`
- `PENDING_CLEARED`
- `RESET/DISCARDED_*`

The columns include wall time, active time, measured/target FPS, accumulator,
pending interval, attempt and execution counters, authoritative logic frame,
client frame, `SavedClientFrame`, W3D frame duration, native limiter state,
focus state, pause/loading classification, and animation/visual timing.

`NATIVE_ADMISSION_BLOCKED` is inferred safely: an attempt marker survived until
the next scheduler callback because the GameLogic entry hook did not run. The
logger does not call `getFrameAdvanceCount()` itself, because that getter owns
native network timing state and must not be probed twice for diagnostics.

For multiplayer tests, record host/guest role, visual FPS, approximate latency
and jitter, orders issued, visible stalls, and any desync. Return the populated
CSV after the game has closed.

## Verification performed

The deterministic test executable covers:

- 60 seconds at 60, 45, 30, 20, 15, 12, 10, and 5 FPS;
- expected logic counts of 300 per minute from 15 FPS upward;
- expected below-15 slowdown;
- real-time animation from 15 through 60 FPS;
- integer W3D-millisecond remainder accumulation;
- monotonic visual interpolation;
- completion of legacy phases 2 through 6;
- native phase-1 pause routing with WindowManager updates and no GameLogic
  execution;
- separation of UI-capable WW3D time from frozen world animation;
- low-FPS recovery without catch-up;
- discarded long stalls;
- immediate network admission;
- a tick blocked until 215 ms, retaining 15 ms and becoming due again around
  400 ms;
- a tick blocked until 250 ms, retaining 50 ms;
- repeated render-by-render blocked attempts with exactly one preparation and
  one eventual network advance;
- a tick blocked until 550 ms, followed by stale-debt discard and no burst;
- pause, lifecycle-reset, and long-stall invalidation while pending;
- below-15 pending behavior and recovery.

The current result file reports `failures=0`. The complete Open-BFME repository
verification gate also passed when the implementation commit was created.

Observed in-game testing has covered 15, 30, and 60 FPS; animation speed;
construction; shell-map presentation; butterflies and other particles; camera
speed; floating income text; single-player pause UI; soldier/worker animation;
and pause/unpause stability.

Still required for strong multiplayer confidence:

- two real BFME instances or machines;
- host near 60 FPS and guest around 20-30 FPS;
- controlled 50-150 ms latency plus jitter;
- simultaneous orders and sustained movement/combat;
- a long session while monitoring authoritative frames and synchronization;
- confirmation that no desync appears under router and guest roles.

Deterministic tests prove scheduler bookkeeping, not end-to-end network
compatibility.

## Problem and solution history

| Symptom or risk | Cause/failed direction | Current solution |
|---|---|---|
| Gameplay sped up with render FPS | Authoritative phase tied to visual frames | QPC active-time scheduler offers phase 1 at 5 Hz |
| Construction appeared stuck at 15 FPS in an earlier build | Incorrect lifecycle/phase behavior at the lower boundary | Explicit 15-FPS 5-Hz math and phase completion; deterministic 300 ticks/minute |
| Animation correct only at exactly 60 FPS | Fixed `0.5`, doubled timers, or fixed 16/17-ms assumptions | Elapsed render delta and the shared slowdown formula |
| Butterflies and FX ran too fast | Particle manager updated once per render | Independent authored 30-Hz FX clock plus interpolation |
| Camera speed changed with FPS | Displacement applied once per render | Scale by unmodified real render delta |
| Floating income text jerked down/up | Mixed integer client frame and visual position | Continuous visual phase |
| Main-menu shell map was black | Active-world transformed clock used before simulation existed | Retail clock pass-through during shell/loading |
| Pause ornament/spellbook disappeared | Shared WW3D clock frozen globally | UI clock pass-through with separate world holds |
| Soldiers ran in place during pause | UI clock pass-through also reached world model loops | Scope hold to known W3DModelDraw world feeder |
| Worker/tree twitched during pause | Native phase-1 client bookkeeping was bypassed too broadly | Restore native pause gate and `m_advanceFrame` behavior |
| Alt-Tab risked catch-up or limiter contamination | Wall-clock suspension and foreground pacing mixed together | Discard large gaps; observe native limiter/focus state without forcing it |
| 120-FPS build crashed | Unresolved retail behavior above supported range | Revert experiment; explicitly limit this build to 60 FPS |
| Multiplayer due tick could be lost | Timer interval consumed before native admission succeeded | Persistent one-tick pending state cleared only at GameLogic entry |

## Files

- `dinput8.dll`: installable proxy and runtime patch.
- `bfme60fps_time_scheduler.c`: proxy, signature checks, active hooks,
  diagnostics, and retained investigation helpers.
- `scheduler_math.h`: deterministic timing formulas shared by DLL and tests.
- `scheduler_test.c`: standalone deterministic tests.
- `scheduler_test.exe`: prebuilt test executable.
- `scheduler_test_results.txt`: known passing results.
- `dinput8.map`: linker map for resolving DLL symbols.
- `BFME_MULTIPLAYER_TICK_DIAGNOSTIC.csv`: clean diagnostic header for testers.
- `PACKAGE_README.txt`: short installation/tester instructions.
- `BFME_1.03_variable_fps_local_test.zip`: distributable tester package.

Relevant reconstructed retail sources elsewhere in this repository are:

- `Code/GameEngine/Source/Common/GameEngineUpdate.cpp`: retail client-phase
  loop and the retry behavior after a blocked phase 1;
- `Code/GameEngine/Source/Common/GameEngineFramePacing.cpp`: native
  `_bfme_updateNetworkAndLogic`, pause gate, frame pacing, and client update;
- `Code/GameEngine/Source/GameNetwork/BFMENativeNetwork_getFrameAdvanceCount.cpp`:
  guest command/frame-ceiling checks and packet-router 5-Hz readiness logic.

## Building

The current local build uses the Visual Studio 2022 32-bit toolchain and C
compilation mode:

```text
cl /TC /O2 /MT /W3 /c bfme60fps_time_scheduler.c
link /DLL /OUT:dinput8.dll /MAP:dinput8.map /EXPORT:DirectInput8Create \
     bfme60fps_time_scheduler.obj uuid.lib user32.lib

cl /TC /O2 /MT /W3 /c scheduler_test.c
link /OUT:scheduler_test.exe scheduler_test.obj
```

The only expected compiler warnings in the current build are Microsoft CRT
deprecation warnings for `_snprintf` and `fopen`.

## Rules for future changes

Any future implementation should preserve these invariants:

1. The timer decides when a tick is due; native BFME decides whether it may
   execute.
2. Never call GameLogic directly to satisfy the timer.
3. Never create more than one pending authoritative tick.
4. Clear/consume pending time only from proof of actual GameLogic entry.
5. Never repeat legacy phases 2 through 6 while retrying the same pending tick.
6. Never turn pause, loading, low FPS, or process suspension into catch-up debt.
7. Keep authoritative state separate from render interpolation.
8. Keep UI presentation time separate from frozen world animation time.
9. Keep camera timing separate from below-15 simulation slowdown.
10. Keep FX on its authored 30-Hz clock; do not compensate INIs individually.
11. Do not force native network readiness, frame ceilings, router pacing, or
    command completeness.
12. Do not claim support above 60 FPS without independently resolving and
    testing the retail crash boundary.

## Repository history

The major experimental milestones are:

| Commit | Change |
|---|---|
| `2118d6e99` | Added the initial local variable-FPS package |
| `98b14f0fa` | Added focus/pacing diagnostics and expanded visual/FX timing |
| `8b6145f34` | Recorded an unsuccessful pause-presentation experiment |
| `a56adcb66` | Separated paused UI time from world-model animation time |
| `c0dd0e3e3` | Restored native pause client bookkeeping |
| `05c164aea` | Preserved timer-due ticks across native multiplayer blocking |

These commits are intentionally on the experimental feature branch rather than
Open-BFME `master`.
