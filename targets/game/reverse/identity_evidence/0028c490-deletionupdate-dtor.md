# 0x0028C490 is ~DeletionUpdate, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x0028C490 was `?dup_0028c490@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GDeletionUpdate@@MAEPAXI@Z`
  (DeletionUpdateDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x00021B93, and 0x00021B93 is `jmp 0x0028C490`.
- `python3 tools/ilt_oracle.py check '??1DeletionUpdate@@MAE@XZ' 0x0028C490`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.
