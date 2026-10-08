# 0x00216AF0 is ~SquishCollide, not an anonymous CollideModule teardown alias

The 25-byte row at 0x00216AF0 was `?dup_00216AF0@@YAXXZ`, a gen-alias of the
CollideModule destructor COMDAT emitted by FireWeaponCollideDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
CollideModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GSquishCollide@@MAEPAXI@Z`
  (0x00216C90, SquishCollideDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0002421C, and 0x0002421C is `jmp 0x00216AF0`.
- `python3 tools/ilt_oracle.py check '??1SquishCollide@@MAE@XZ' 0x00216AF0`
  reports CONFIRMED (exact).
- The body stores the three CollideModule vtables (0x010A9AF8 at +0x10,
  0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
