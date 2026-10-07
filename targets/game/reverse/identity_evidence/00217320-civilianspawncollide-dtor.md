# 0x00217320 is ~CivilianSpawnCollide, not an anonymous CollideModule teardown alias

The 25-byte row at 0x00217320 was `?dup_00217320@@YAXXZ`, a gen-alias of the
CollideModule destructor COMDAT emitted by FireWeaponCollideDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
CollideModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GCivilianSpawnCollide@@MAEPAXI@Z`
  (0x002174D0, CivilianSpawnCollideDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0003A6B1, and 0x0003A6B1 is `jmp 0x00217320`.
- `python3 tools/ilt_oracle.py check '??1CivilianSpawnCollide@@MAE@XZ' 0x00217320`
  reports CONFIRMED (exact).
- The body stores the three CollideModule vtables (0x010A9AF8 at +0x10,
  0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
