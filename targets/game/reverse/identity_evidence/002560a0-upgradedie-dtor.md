# 0x002560A0 is ~UpgradeDie, not an anonymous nested-inline destructor

The 25-byte row at 0x002560A0 was `??1Rva002560A0NestedDtor@@UAE@XZ`, an
address-derived placeholder in NestedInlineDestructors.cpp whose identity was
never recovered.

- The matched protected scalar-deleting wrapper `??_GUpgradeDie@@MAEPAXI@Z`
  (0x002561D0, UpgradeDieDeletingDestructor.cpp) calls its complete destructor
  through ILT 0x0001B7B6, and 0x0001B7B6 is `jmp 0x002560A0`.
- `python3 tools/ilt_oracle.py check '??1UpgradeDie@@MAE@XZ' 0x002560A0`
  reports CONFIRMED (exact). The ILT order cannot separate the public `UAE`
  spelling, but the matched `??_G` is protected (MAE) and calls the MAE name.
- The body stores the DieModule vtables (0x010A4CEC at +0x10, then 0x0109CB5C
  at +0 and 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor of a DieModule.
