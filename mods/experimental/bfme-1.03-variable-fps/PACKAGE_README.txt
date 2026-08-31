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
- A true pause uses the retail phase-1 pause gate. Logic slices, interpolation,
  and WW3D elapsed animation time are held until unpause.
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
and 5 FPS, pause preservation, low-FPS recovery, and discarded stalls.

This diagnostic build also writes C:\BFME1\BFME_FOCUS_DIAGNOSTIC.csv. It
records focus state, the retail frame limiter fields, measured render timing,
the scheduler accumulator, and W3D frame time. The probes are read-only and do
not change focus, pacing, presentation, or timing behavior.

dinput8.dll SHA-256:
197EBDE42048655345A1A820FF6C51371910B436A6D834C4A052B9881AD84CB3

This is a local test package. It does not modify lotrbfme.exe or any
Open-BFME repository branch.
