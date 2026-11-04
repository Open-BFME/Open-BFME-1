# 0x00292550 is ~FireSpreadUpdate, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x00292550 was `?dup_00292550@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GFireSpreadUpdate@@MAEPAXI@Z`
  (FireSpreadUpdateDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x00031AA7, and 0x00031AA7 is `jmp 0x00292550`.
- `python3 tools/ilt_oracle.py check '??1FireSpreadUpdate@@MAE@XZ' 0x00292550`
  reports CONFIRMED (exact) and CONTRADICTS the UAE spelling.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.

pin-identity-override: ??1FireSpreadUpdate@@MAE@XZ 0x00292550 caller=0x00031AA7 ilt_oracle CONFIRMED MAE@XZ at slot 39866; deleting wrapper calls it via ILT 0x00031AA7
