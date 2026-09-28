# 055-ac-attack-view: units attacking a building can be hit (AC fix)

In AC ("attack cancel"), units attacking a structure could not be hit back by
the enemy melee horde fighting them. This keeps melee horde members attacking an
enemy horde while that enemy attacks a structure.

Build a test executable from the repository root. It carries the AC fix alone,
without the bundle's other features:

```sh
python3 tools/modbuild.py --only 055-ac-attack-view -o build/ac-fix.exe
```
## How it fixes AC

A reported AC encounter showed two failure paths. First, the melee target search
could miss an enemy attacking a structure because that enemy was represented in
a pathfinder cell by a goal reservation rather than the position or obstacle ID
the search normally checks. The fix lets that search consider the reserved
object only when the cell has neither ordinary ID, the object belongs to an
enemy horde attacking a structure, and the game's normal target checks pass.

Second, a horde member that had a target could stop attacking when the target
moved out of weapon range. The game prevented that member from calculating its
own path, then prevented it from reacquiring a target because it still belonged
to a horde. The fix permits the original path calculation when the member's
horde has an attack order against the target's enemy horde. The game's pathfinder
and subsequent attack states then run normally. These conditions depend on
horde orders and enemy relationships, not on a specific faction, unit type, or
formation.

The feature also contains four hooks that temporarily change the melee
target predicate for an enemy attacking a structure. They restore the predicate
bit afterward. They were present in the tested build, but their independent
contribution has not been measured.

## Verification and scope

In an offline replay of that encounter, four of ten Uruks were actively
attacking at frame 500 without the member-path change; all ten were attacking
with it. Hits on the Soldiers during frames 456–623 rose from 55 to 82, while
hits on the mill stayed at 61. A live two-client test of the complete feature
then showed the Uruks continuing to attack as intended. The Uruk player issued
one attack order at frame 2543 and no further order through frame 2661; the
Uruks dealt 20 hits to the Soldiers in that interval. Both clients' diagnostic
logs reported zero dropped events. The replay and logs are local test artifacts,
not part of this repository.

Compiled-hook tests also check that the detours return to the original game
instructions. The offline and live tests cover the reported AC encounter.
Allowing an ordered horde member to path independently could also affect
formation movement in other horde-versus-horde fights; those cases have not
been tested, so the feature remains opt-in.
