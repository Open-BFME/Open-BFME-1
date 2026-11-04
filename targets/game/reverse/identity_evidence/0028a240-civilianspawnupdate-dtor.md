# 0x0028A240 is ~CivilianSpawnUpdate, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x0028A240 was a ?dup_ gen-alias of the UpdateModule destructor
COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpdateModule teardown
is its own body.

- The scalar-deleting wrapper at 0x0028A450 (slot zero of the class vtable) calls its
  complete destructor through ILT 0x000013F7, and that ILT slot is jmp 0x0028A240.
- python3 tools/ilt_oracle.py check "??1CivilianSpawnUpdate@@MAE@XZ" 0x0028A240 reports CONFIRMED
  (exact) and CONTRADICTS the other access spelling.
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.

pin-identity-override: ??1CivilianSpawnUpdate@@MAE@XZ 0x0028A240 caller=0x000013F7 ilt_oracle CONFIRMED MAE@XZ; deleting wrapper calls it via ILT 0x000013F7
