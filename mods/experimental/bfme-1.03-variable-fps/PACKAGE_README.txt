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
- BFME game mode 7 remains active single-player; only shell mode 4 suspends
  the scheduler by game-mode classification.
- All WW3D sync callers feed one monotonic output clock. Switching callers
  rebases the input clock without moving animation time forward or backward.
- A true pause uses the retail phase-1 pause gate. Logic slices, interpolation,
  and WW3D elapsed animation time are held until unpause.
- Floating income text uses continuous visual interpolation instead of the
  alternating integer client-frame denominator.

Verification
------------
The included deterministic test results cover 60, 45, 30, 20, 15, 12, 10,
and 5 FPS, pause preservation, low-FPS recovery, and discarded stalls.

dinput8.dll SHA-256:
90EC422D91F452D5D0F2478EDC7AA49818D71F588F84D9A0E9FB4AE988A9022F

This is a local test package. It does not modify lotrbfme.exe or any
Open-BFME repository branch.
