# Inline-only model-condition helpers: suppress incompatible COMDATs

Queue37, claim FCBFE81B. Three BFME1 update TUs inline model-condition flag
updates but also emit standalone Object::setModelConditionState COMDATs
using incompatible partial Object/flag views. Retail has no standalone row
for that setter. Existing Object.cpp already documents removal of the Zero
Hour drawable-forwarding implementation. Keep target-specific inline access
at each verified call site and prevent standalone copies with
__declspec(dllimport) __forceinline, the measured lever in shape_levers.md.
Apply the same suppression to Radar/Slaved's local ModelConditionFlags
set/test helpers, eliminating their additional unowned COMDAT conflicts.

The first Prone trial suppresses the setter but moves BitFlags::test out of
line, losing constant folding and the exact73-byte body. Force-inline its
existing test/set methods as well; the complete start/stopProneEffects,
extendRadar and onObjectCreated rows then pass4/4, with3 DIR32 references
and2 float constants. COFF symbol inspection of all3 final objects finds no
setModelConditionState symbol and no generated __imp_ reference. No new
function, name, import, datum, pin, layout or compiler flag is introduced.

Before Slaved link_check: setModelConditionState duplicate plus differing
setter and ModelConditionFlags set/test COMDATs,0 linked bytes. After uses
current3 objects; stale Oct19 census prevents complete selection evidence,
so linked-byte progress remains unknown.

Donor provenance: latest reviewed a9286edec5374324e40c1f5dd29c3a8ab5582283,
Code/GameEngine/Source/GameLogic/Object/Upgrade/GarrisonUpgrade.cpp,
ArmorUpgradeUpgradeImplementation.cpp and AI/AIAttackStateOnExit.cpp use
the same inline-only setter suppression; existing local IosBaseCopyState.cpp
and shape_levers record prior BFME2 donor5452ce5952 technique. Donor field
layouts/flag indices are not imported. BFME1's per-TU declarations/flags,
existing local headers, addresses and complete call-site bytes establish
this adaptation. Build expected donor remains verified59e3f8f825; latest
was reviewed through separate donor-latest tree. No private donor trial
cache or donor build dependency was changed.
