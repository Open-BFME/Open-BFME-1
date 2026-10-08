# 0x0020CC30 is ~SpawnTownsmenBehavior, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x0020CC30 was `?dup_0020cc30@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GSpawnTownsmenBehavior@@MAEPAXI@Z`
  (SpawnTownsmenBehaviorDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x00007D8D, and 0x00007D8D is `jmp 0x0020CC30`.
- `python3 tools/ilt_oracle.py check '??1SpawnTownsmenBehavior@@MAE@XZ' 0x0020CC30`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
