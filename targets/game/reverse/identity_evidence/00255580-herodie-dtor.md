# 0x00255580 is ~HeroDie, not an anonymous nested-inline destructor

The 25-byte row at 0x00255580 was `??1Rva00255580NestedDtor@@UAE@XZ`, an
address-derived placeholder in NestedInlineDestructors.cpp whose identity was
never recovered.

- The matched protected scalar-deleting wrapper `??_GHeroDie@@MAEPAXI@Z`
  (0x00255760, HeroDieDeletingDestructor.cpp) calls its complete destructor
  through ILT 0x0003EEA5, and 0x0003EEA5 is `jmp 0x00255580`.
- `python3 tools/ilt_oracle.py check '??1HeroDie@@MAE@XZ' 0x00255580`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The body stores the DieModule vtables (0x010A4CEC at +0x10, then 0x0109CB5C
  at +0 and 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor of a DieModule.
