# AC attack-view goal reservations

Unshipped pending a live two-client AC retest. This feature replaces 051's four
melee-predicate hooks and adds four attack-view hooks; build it instead of
051–054. It has no logging hooks. The full diagnostic variant is 054v11.

In the saved AC replay, four Gondor Soldiers attacking an Isengard mill were
within 1–4 game units of idle Uruks. Both native attack-view searches omitted
those Soldiers. The search reads each pathfinder cell's position ID (and, in
one search, obstacle ID), while the missing Soldiers occupied goal reservations
at cell-info `+0x14` with no position ID.

At the four cell-search sites, the callback exposes a goal-reservation ID only
when the native position ID is empty, its owner is a member of an enemy horde,
and that horde is in the normal object-attack state with a structure goal.
The original search still handles duplicate suppression, its 16-candidate cap,
and all later target filters. The callback never edits pathfinder cell memory.

The shared decision function in `src/view_goal.h` is compiled by both 055 and
the diagnostic 054v11 build. In the completed 054v10 replay with the older
retry and placement exceptions disabled, Uruks damaged Soldiers 616–619 from
frames 461–469 onward; none took damage in the control replay's AC window.
The 054v10 capture reached frame 1051 with zero dropped records. The
shared-source 054v11 replay produced the same command, damage, dispatch, and
view-override records through frame 800, and likewise had zero dropped
records through frame 883. Live two-client validation remains.
