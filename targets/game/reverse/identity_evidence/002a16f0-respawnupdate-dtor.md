# 0x002A16F0 is ~RespawnUpdate, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x002A16F0 was `?dup_002a16f0@@YAXXZ`, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class's inlined
UpdateModule teardown is its own body.

- The matched public scalar-deleting wrapper `??_GRespawnUpdate@@UAEPAXI@Z`
  (RespawnUpdateDeletingDestructor.cpp) calls its complete destructor through
  ILT 0x000347DE, and 0x000347DE is `jmp 0x002A16F0`.
- `python3 tools/ilt_oracle.py check '??1RespawnUpdate@@UAE@XZ' 0x002A16F0`
  reports CONFIRMED (exact).
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.

pin-identity-override: ??1RespawnUpdate@@UAE@XZ 0x002A16F0 caller=0x000347DE ilt_oracle CONFIRMED UAE@XZ at slot 42181; deleting wrapper calls it via ILT 0x000347DE
