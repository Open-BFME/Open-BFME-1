# 0x00216760 is ~HordeMemberCollide, not an anonymous CollideModule teardown alias

The 25-byte row at 0x00216760 was `?dup_00216760@@YAXXZ`, a gen-alias of the
CollideModule destructor COMDAT emitted by FireWeaponCollideDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
CollideModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GHordeMemberCollide@@MAEPAXI@Z`
  (0x00216890, HordeMemberCollideDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0002BA71, and 0x0002BA71 is `jmp 0x00216760`.
- `python3 tools/ilt_oracle.py check '??1HordeMemberCollide@@MAE@XZ' 0x00216760`
  reports CONFIRMED (exact).
- The body stores the three CollideModule vtables (0x010A9AF8 at +0x10,
  0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
