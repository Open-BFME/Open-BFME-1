# 0x002A0180 is ~RadarUpdate, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x002A0180 was `?dup_002a0180@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GRadarUpdate@@MAEPAXI@Z`
  (RadarUpdateDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x0000B037, and 0x0000B037 is `jmp 0x002A0180`.
- `python3 tools/ilt_oracle.py check '??1RadarUpdate@@MAE@XZ' 0x002A0180`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
