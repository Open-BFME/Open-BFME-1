BFME 1.03 variable-FPS local timing patch
==========================================

Install
-------
1. Close lotrbfme.exe.
2. Copy dinput8.dll next to lotrbfme.exe (normally C:\BFME1\dinput8.dll).
3. Remove or rename dinput8.dll to uninstall.

Behavior
--------
- Authoritative gameplay cadence is 5 Hz from 15 FPS upward.
- Below 15 FPS, gameplay intentionally slows by visualFPS / 15.
- Animation uses measured render time and stays real-time from 15 FPS upward.
- Below 15 FPS, animation uses the same visualFPS / 15 slowdown as gameplay.
- The legacy six-phase dispatch is completed below 30 FPS without adding
  authoritative phase-1 ticks.
- A true pause bypasses GameLogic phase dispatch while retaining BFME's native
  client-frame presentation updates. Authoritative logic, world drawables,
  particles, interpolation, and WW3D elapsed animation time remain held, while
  APT/menu and Anim2D UI presentation can continue as retail expects.
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
and 5 FPS, pause preservation, presentation-only pause routing with no
GameLogic phase calls, low-FPS recovery, and discarded stalls.

Known test result: the presentation-only pause-routing experiment did not
restore the missing single-player pause ornament in the in-game user test.
It is retained here as a tested negative result, not as a confirmed fix.

This diagnostic build also writes C:\BFME1\BFME_FOCUS_DIAGNOSTIC.csv. It
records focus state, the retail frame limiter fields, measured render timing,
the scheduler accumulator, and W3D frame time. The probes are read-only and do
not change focus, pacing, presentation, or timing behavior.

dinput8.dll SHA-256:
F1296DBA9BE8E94167CB68CE7A20F265796125A11EDE2B26937BA388143610E6

This is a local test package. It does not modify lotrbfme.exe or any
Open-BFME repository branch.
