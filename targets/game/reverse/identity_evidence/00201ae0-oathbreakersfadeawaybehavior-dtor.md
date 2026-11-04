# 0x00201AE0 is ~OathbreakersFadeAwayBehavior, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x00201AE0 was `?dup_00201ae0@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched public scalar-deleting wrapper `??_GOathbreakersFadeAwayBehavior@@UAEPAXI@Z`
  (OathbreakersFadeAwayBehaviorDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x00038262, and 0x00038262 is `jmp 0x00201AE0`.
- `python3 tools/ilt_oracle.py check '??1OathbreakersFadeAwayBehavior@@MAE@XZ' 0x00201AE0`
  reports CONFIRMED (exact) and CONTRADICTS the UAE spelling.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.

pin-identity-override: ??1OathbreakersFadeAwayBehavior@@MAE@XZ 0x00201AE0 caller=0x00038262 ilt_oracle CONFIRMED MAE@XZ at slot 27016 and CONTRADICTS UAE@XZ; deleting wrapper calls it via ILT 0x00038262
