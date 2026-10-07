# 0x00217620 is ~CrateCollide, not ~CollideModule

The 25-byte row at 0x00217620 was `??1CollideModule@@UAE@XZ`, claimed from the
CollideModule destructor COMDAT that FireWeaponCollideDestructorThunk.cpp
emits. Retail links without identical-COMDAT folding, so the inlined
CollideModule teardown of each derived class is its own body, and symbols.csv
pinned both ??1CollideModule and ??1CrateCollide at the one ILT 0x0004B68C.

- The matched protected scalar-deleting wrapper `??_GCrateCollide@@MAEPAXI@Z`
  (CrateCollideDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x0004B68C, and 0x0004B68C is `jmp 0x00217620`.
- `python3 tools/ilt_oracle.py check '??1CrateCollide@@MAE@XZ' 0x00217620`
  reports CONFIRMED (exact); `??1CollideModule@@UAE@XZ` at the same body is
  CONTRADICTED (outside every window of the target's ILT slots).
- The body stores the three CollideModule vtables (0x010A9AF8 at +0x10,
  0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.

The ??1CollideModule pin at 0x0004B68C is removed with the row.
