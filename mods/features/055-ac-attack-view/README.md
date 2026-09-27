# AC attack-view goal reservations

Ships in `mods/dist/lotrbfme.exe` after a live two-client AC retest on
2026-09-27: the player reproduced the Gondor Soldiers versus Isengard Uruks
and mill encounter and reported that the fix worked. This feature replaces
051's four melee-predicate hooks and adds four attack-view hooks. It has no
logging hooks; 054 is the separate diagnostic variant.

In the saved AC replay, four Gondor Soldiers attacking an Isengard mill were
within 1–4 game units of idle Uruks. Both native attack-view searches omitted
those Soldiers. The search reads each pathfinder cell's position ID (and, in
one search, obstacle ID), while the missing Soldiers occupied goal reservations
at cell-info `+0x14` with no position ID.

At the four cell-search sites, the callback exposes a goal-reservation ID only
when the native position and obstacle IDs are empty, its owner is a member of an enemy horde,
and that horde is in the normal object-attack state with a structure goal.
The original search still handles duplicate suppression, its 16-candidate cap,
and all later target filters. The callback never edits pathfinder cell memory.

The shared decision function in `src/view_goal.h` is compiled by both 055 and
the diagnostic 054 build. In the completed 054v10 replay with the older
retry and placement exceptions disabled, Uruks damaged Soldiers 616–619 from
frames 461–469 onward; none took damage in the control replay's AC window.
The 054v10 capture reached frame 1051 with zero dropped records. The
shared-source 054v11 replay produced the same command, damage, dispatch, and
view-override records through frame 800, and likewise had zero dropped
records through frame 883.

A later diagnostic replay recorded obstacle ID zero on all 840 overrides in
the AC encounter. The shared rule now requires that ID to be zero, preserving
the native obstacle candidate when one shares a cell with a reservation.
The guarded diagnostic build reproduced the same 840 overrides, 239 damage
records, and 47 target dispatches through frame 800. Its capture reached
frame 841 with zero dropped records.
