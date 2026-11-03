# 0x0028A5A0 CivilianSpawnUpdate::update (1025 B)

Identity correction: the row was the naked `__emit` lift `??1CivilianSpawnUpdate@@UAE@XZ`
in `CivilianSpawnUpdateDestructorThunk.cpp`. The body is
`?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ`.

## BFME 1 target evidence
- `ilt_oracle.py check ?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ 0x0028A5A0`:
  CONFIRMED (p_false 8.48e-04, exact). The old destructor name is CONTRADICTED (outside every
  window of the target's slots).
- The matched constructor 0x0028A2F0 installs UpdateModuleInterface table 0x010BCD40 at
  this+0x10. Its slot 0 is ILT 0x000089B8, which jumps here. The primary scalar-deleting slot
  goes through ILT 0x0001EBC8 to 0x0028A450, not to this body (earlier `identity-suspect` verdict).
- The receiver is the secondary interface: module data at -0xC, Object at -8. The return value
  is either 0x3FFFFFFF (UPDATE_SLEEP_FOREVER) or the word at +0x10 (object +0x20), which the
  constructor seeds from GetGameLogicRandomValue over the module data's +0x08 delay. Both random
  draws pass the `F:\bfme\...\Object\Update\CivilianSpawnUpdate.cpp` __FILE__ string
  (VA 0x010BCCE0), lines 0x55 and 0x74.
- Boundary: the final RET is at +0x400, followed by INT3. That gives 1025 bytes, and the ledger
  extent is unchanged.

## Donor evidence (BFME 2, Open-BFME-2 59e3f8f825)
- `Code/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp`:
  CivilianSpawnUpdate::update (BFME 2 0x0047FAFE, 761 B, WorldBuilder-named, matched there).
  The donor supplies the control flow:
  - pick a random civilian template;
  - iterate the partition with the alive/not-self/RunToFilter filters within MaximumDistance;
  - pick a random run-to object;
  - create the new object half a bounding radius ahead of the spawner;
  - set locomotor set 4 and a model condition;
  - aim at the target, ignore it as an obstacle, then move there (CMD_FROM_AI) or destroy the
    civilian.
- The donor also supplies the field names from its parse table: SpawnDelayTime +0x08,
  RunToFilter +0x0C, MaximumDistance +0x10, and Civilian names +0x14. The BFME 1 module-data
  constructor 0x0028A480 has the same shape: it stores 300 to +0x10 and three zero words to the
  vector at +0x14.
- The donor's `memset` of the zeroed creation mask is what gives retail's store schedule. A
  constructor that stores the three words one by one interleaves them differently: 31
  bytes differ at +0x18E.

## Structural inference (BFME 1 retail body, not donor)
- Object layout: id +0x74, geometry +0xAC (`BfmeGeometryInfo::boxMajorRadius`),
  model-condition words +0x110, AI +0x204, team +0x23C.
- The pathfinder is at TheAI+0x0C. chooseLocomotorSet is AI slot 127 (+0x1FC). The
  ignore-obstacle id is set through the pathfinder's +0x844 setter (`Rva003D5620DwordSlot`,
  as in AIUpdate.cpp).
- The partition result is the refcounted BfmeWideResult hit list (8-byte entries), released
  inline, as in ObjectCountNearbyEnemies.cpp.
- The filters are Rva0025ED50RootFilter, Rva0025ED50ObjectFilter and Rva00265150RJFilter, with
  their vtables pinned.
- The model-condition bit is word 2 bit 12. The donor's counterpart is PANICKING; that name is
  not proven for BFME 1, so the source does not use it.
