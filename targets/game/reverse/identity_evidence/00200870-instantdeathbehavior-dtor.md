# 0x00200870 is ~InstantDeathBehavior, not an anonymous nested-inline destructor

The 25-byte row at 0x00200870 was `??1Rva00200870NestedDtor@@UAE@XZ`, an
address-derived placeholder in NestedInlineDestructors.cpp whose identity was
never recovered.

- The matched protected scalar-deleting wrapper `??_GInstantDeathBehavior@@MAEPAXI@Z`
  (0x00200C90, InstantDeathBehaviorDeletingDestructor.cpp) calls its complete destructor
  through ILT 0x0003401D, and 0x0003401D is `jmp 0x00200870`.
- `python3 tools/ilt_oracle.py check '??1InstantDeathBehavior@@MAE@XZ' 0x00200870`
  reports CONFIRMED (exact), and the public spelling
  `python3 tools/ilt_oracle.py check '??1InstantDeathBehavior@@UAE@XZ' 0x00200870`
  reports CONTRADICTED (outside every window of the target's slots), so the
  ILT order itself fixes the protected `MAE` spelling. The matched `??_G` is
  protected (MAE) too and calls the MAE name.
- The body stores the DieModule vtables (0x010A4CEC at +0x10, then 0x0109CB5C
  at +0 and 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor of a DieModule.
- The Zero Hour InstantDeathBehavior.cpp definition (an unmatched empty dtor that the link selected over retail's) is removed; that TU now only declares it.
