BFME1 SMOOTH 60 FPS  (rev 3)  -  test build
============================================

What this is
------------
A patched copy of Battle for Middle-earth I v1.03 (lotrbfme.exe) that renders
skirmish / single-player at 60 fps with smooth unit motion, at the correct game
speed, with animations at normal speed.  The retail game is locked to ~38 fps
because its frame limiter is also its game-speed clock: one loop iteration is
one render AND one simulation sub-step, so raising the cap fast-forwards the
game and removing it runs everything 3-4x too fast.

Nothing in the simulation is changed.  Every modification is on the client /
render side of the engine.  Your original exe is not touched.


Install
-------
1. Copy  lotrbfme-smooth60.exe  into your BFME1 folder next to lotrbfme.exe
   (the folder that holds lotrbfme.exe, e.g. D:\BFME1).
2. Run  "Launch BFME - Smooth60.bat"  from the same folder, or run
   lotrbfme-smooth60.exe directly.  It uses the same data, options and
   saves as the normal exe.  Add  -win  for windowed mode.
3. To go back to stock, just run lotrbfme.exe as before.  Delete the
   -smooth60 exe to uninstall.

Verify the file: SHA-256 is listed in SHA256.txt.


Multiplayer
-----------
The build is safe to run in multiplayer: the simulation code is untouched and
the pacing logic below switches itself OFF whenever a network game is active,
so patched and unpatched players stay in lockstep.  BUT the smoothing only
applies to skirmish and single player.  In a network game you get a 60 fps
render cap (camera, cursor, UI at 60) while unit motion still moves in the
retail cadence, because in multiplayer the network, not this patch, decides
when simulation steps run.  Making multiplayer motion smooth is the next
piece of work, not in this build.  Also: third-party online launchers or
anti-cheat that check the exe hash will see a modified exe.


Known issues in this test build
-------------------------------
* Heal spell: reports that clicking the spellbook Heal onto a soldier does
  not activate.  Under investigation; it is not caused by the animation
  clock change (verified with a variant that leaves that alone).  Please
  report whether other targeted spells / powers behave the same.
* A faint trace of stagger may remain on marching troops.
* Buildings and animations run at true 1.0x now; if you are used to the
  retail 38 fps cap they can look slightly quicker.


What was changed, technically
-----------------------------
All changes are appended code sections ("code caves") in the exe with 5-byte
jump detours into them.  No original instruction is edited except the
detour entry points.  Retail RVAs below are relative to the 0x400000 image
base.

1. Render cap 60 (GameEngine::update, RVA 0x0006E910)
   A small cave writes the engine's FramesPerSecondLimit (GameEngine+0x08)
   to 60 for skirmish / single player and for network games, 30 otherwise
   (menus).  Retail 1.03 uses 38.

2. Wall-clock pacing of the simulation sub-steps
   (_bfme_updateNetworkAndLogic, RVA 0x0006BAE0)
   BFME's engine runs a six-phase cycle: each loop iteration calls the game
   logic with a phase number 1..6; phase 1 advances the logical frame (5 Hz),
   phases 2..6 do collision and the update-module queues.  In retail the
   frame limiter paces these at 38 per second, which is why the cap is also
   the game clock.  The cave replaces that coupling with a
   QueryPerformanceCounter accumulator: a phase is admitted every
   QPF/30 ticks (33.33 ms), so six phases = 200 ms = one logical frame,
   exactly retail game speed, while the render loop is free to run at 60.
   A phase that is not yet due is retried on the next iteration.  In a
   network game the cave steps aside entirely and the stock network pacing
   runs (this is what keeps multiplayer lockstep intact).  timeBeginPeriod(1)
   is requested once for timer resolution.

3. Continuous client-frame interpolation ratio
   (_bfme_updateClientSubsystems entry, RVA 0x0006B910)
   This is the piece that makes units smooth.  A moving unit's position is
   only integrated once per 200 ms logical frame; what you see in between is
   the engine's OWN interpolation of previous->current transforms, driven by
   GameEngine::m_clientFrameRatio (GameEngine+0x38).  Retail sets that ratio
   to phase/6 after each phase, i.e. it moves in 33 ms steps, so at 60 fps
   every other rendered frame was a duplicate: the "stagger".  The cave
   writes the ratio at the start of every client update as
       (lastAdmittedPhase + fractionOfCurrentStep) / 6
   where the fraction comes from the same QPC accumulator as (2).  The ratio
   now advances continuously with the wall clock and the engine's existing
   interpolation lands on a fresh position every rendered frame.  No render
   object transforms are touched, nothing is patched back afterwards, and no
   latency is added.

4. Animation clock steering (same cave as 3)
   W3D animations play against WW3D::SyncTime, which the client advances by a
   fixed 33 ms constant ([0x012BB1CC]) once per client frame.  At 60 client
   frames per second that made every animation run ~1.9x fast.  Each client
   frame the cave now sets that constant to the animation-time deficit
   against real elapsed time (a small feedback controller), so animations,
   rivers, torches and particles run at 1.0x regardless of frame rate.  In
   menus / multiplayer the constant is put back to 33.

Why this route and not others (all tried and measured on the way here):
 - Removing the limiter: 3-4x fast-forward (the limiter IS the game clock).
 - Doubling the sub-step count with a halved animation constant: correct
   speed and smooth, but every effect authored in sub-steps (Lifetime,
   SystemLifetime, BurstDelay: ~6,000 INI values) runs at double speed.
 - Blending render-object transforms after the fact at the view draw
   (rev 1 / rev 2): rev 1 used the wrong alpha and made stagger worse; rev 2
   worked but costs 40 ms of visual latency and two transform writes per
   moving model per frame.  Rev 3 fixes the alpha at its source instead.

Source
------
Open-BFME repository:  mods/features/050-ratiocont/src/ratiocont.cpp (3+4),
tools/astra_ratiocont_patch.py (installer), tools/astra_patch.py (1+2),
docs/interp-seams.md (the static reverse-engineering audit behind it).
Payloads are compiled with the game's own toolchain (MSVC 7.1), no CRT,
and laid into RWX sections named .bfmemod and .bfmerc.
