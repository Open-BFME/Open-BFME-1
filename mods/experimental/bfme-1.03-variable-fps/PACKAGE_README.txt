BFME 1.03 variable-FPS local timing patch
==========================================

Install
-------
1. Close lotrbfme.exe.
2. Copy dinput8.dll next to lotrbfme.exe (normally C:\BFME1\dinput8.dll).
3. For a clean multiplayer diagnostic run, also copy the included header-only
   BFME_MULTIPLAYER_TICK_DIAGNOSTIC.csv next to lotrbfme.exe. The DLL appends
   timing/admission events to that file.
4. Remove or rename dinput8.dll to uninstall.

Tester return files
-------------------
After reproducing the multiplayer test and closing the game, send back:
- BFME_MULTIPLAYER_TICK_DIAGNOSTIC.csv from the game directory.
- Host/guest role, approximate FPS, latency/jitter settings, and whether a
  visible stall, drift, or desync occurred.

Delete the populated CSV and restore the included header-only copy before a
new independent test session. Keep FramesPerSecondLimit between 15 and 60;
this build does not support or test rates above 60 FPS.

Behavior
--------
- Authoritative gameplay cadence is 5 Hz from 15 FPS upward.
- Below 15 FPS, gameplay intentionally slows by visualFPS / 15.
- Animation uses measured render time and stays real-time from 15 FPS upward.
- Below 15 FPS, animation uses the same visualFPS / 15 slowdown as gameplay.
- The legacy six-phase dispatch is completed below 30 FPS without adding
  authoritative phase-1 ticks.
- A timer-due authoritative tick remains pending while BFME's native network
  admission gate waits for commands, frame ceiling, or router pacing. The
  same phase-1 opportunity is retried without repeating legacy phases 2..6;
  timer time is consumed only when GameLogic actually enters. Short waits
  retain their cadence remainder, while waits of another full interval or
  more discard stale debt instead of bursting catch-up ticks.
- A true pause routes through BFME's native phase-1 pause gate. WindowManager
  and UI presentation continue, while the gate clears GameClient::m_advanceFrame
  so drawable and interpolation state do not advance on following paused
  renders. Authoritative logic, world drawables, particles, and interpolation
  remain held. The shared retail WW3D absolute clock continues for APT/menu
  presentation, while visual-delta and particle gates keep world timing stopped.
  W3DModelDraw's world-animation feeder at caller 0x00B5CA51 is held on the
  existing motion/frame during true pause; other HLOD callers remain untouched.
  The DLL does not pin the GameEngine client phase or interpolation ratio.
- Shell and loading screens retain the retail real-time WW3D clock, so the
  main-menu Sauron's-tower camera movie advances before gameplay exists.
- An unpaused shell map receives the same 5-Hz logic cadence as gameplay;
  opening the in-game menu still freezes through the actual pause state.
- Floating income text uses continuous visual interpolation instead of the
  alternating integer client-frame denominator.
- FX particle simulation now follows the ParticleSystem.ini authored cadence
  of 30 FX frames per second. It is independent of both visual FPS and the
  5-Hz authoritative gameplay scheduler; no INI values are modified.
- At 60 FPS the FX manager advances every other render, at 30 FPS once per
  render, and at 15 FPS twice per render. Below 15 FPS it uses the same FPS/15
  intentional slowdown as gameplay and animation.
- Particle positions and continuous render properties interpolate between FX
  updates above 30 FPS. A true pause preserves the FX accumulator and performs
  no particle updates, so it creates neither animation progress nor resume debt.
- Keyboard, screen-edge, and right-mouse camera scrolling now consume elapsed
  real render time instead of applying one fixed displacement per rendered
  frame. Camera speed therefore remains constant at every supported FPS and
  does not inherit the below-15-FPS gameplay/animation slowdown.
- Weapon attack timers and projectile speeds remain on BFME's native,
  deterministic 5-Hz logic clock. Their millisecond and distance/second INI
  values already convert at 5 Hz, so no gameplay or network compensation is
  applied.

Verification
------------
The included deterministic test results cover 60, 45, 30, 20, 15, 12, 10,
and 5 FPS, native phase-1 pause routing with continuous WindowManager updates
and no GameLogic phase calls, low-FPS recovery, discarded stalls, immediate
network admission, admission delays to 215/250/550 ms, repeated blocked
retries, pause/lifecycle/stall invalidation, and below-15-FPS recovery.

Known test result: restoring native phase-1 client bookkeeping while retaining
the UI-capable shared clock eliminated the observed pause entry/exit twitch and
intermittent Elven Woods tree blip in a quick in-game test. The red ornament,
spellbook presentation, stationary world state, and paused animations remained
correct.

This diagnostic build also writes
C:\BFME1\BFME_MULTIPLAYER_TICK_DIAGNOSTIC.csv. It records timer offers,
blocked/allowed native admission, actual GameLogic entry, pending creation and
clearing, accumulator/remainder, logic and client frames, SavedClientFrame,
focus, retail frame-limiter fields, measured render timing, and W3D frame time.
The probes do not bypass or invoke the native admission gate themselves.

dinput8.dll SHA-256:
31E73BDF8CDEEE0B373C4F13B738B79540395A27C900DA7CEEFD95955CAAC0D6

This is a local test package. It does not modify lotrbfme.exe or any
Open-BFME repository branch.
