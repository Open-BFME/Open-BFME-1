# 0x001FAD80 is ~EnragedBehavior, not an anonymous UpdateModule teardown alias

The 25-byte row at 0x001FAD80 was ?dup_001fad80@@YAXXZ, a gen-alias of the
UpdateModule destructor COMDAT emitted by AutoAbilityBehaviorDestructorThunk.cpp.
Retail links without identical-COMDAT folding, so each derived class inlined
UpdateModule teardown is its own body.

- The matched public scalar-deleting wrapper ??_GEnragedBehavior@@UAEPAXI@Z
  (EnragedBehaviorDeletingDestructor.cpp, 0x001FAD50) calls its complete
  destructor through ILT 0x0000E822, and 0x0000E822 is jmp 0x001FAD80.
- python3 tools/ilt_oracle.py check "??1EnragedBehavior@@UAE@XZ" 0x001FAD80
  reports CONFIRMED (exact).
- The body stores the three UpdateModule vtables (0x0109CB5C at +0, 0x0109CA98
  at +0xC, 0x0109CBAC at +0x10) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor.

pin-identity-override: ??1EnragedBehavior@@UAE@XZ 0x001FAD80 caller=0x0000E822 ilt_oracle CONFIRMED UAE@XZ; deleting wrapper calls it via ILT 0x0000E822
