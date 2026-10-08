# 0x001F6740 is ~BuildingBehavior, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x001F6740 was `?dup_001f6740@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GBuildingBehavior@@MAEPAXI@Z`
  (BuildingBehaviorDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x0003C592, and 0x0003C592 is `jmp 0x001F6740`.
- `python3 tools/ilt_oracle.py check '??1BuildingBehavior@@MAE@XZ' 0x001F6740`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
