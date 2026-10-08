# 0x00255A40 is ~RefundDie, not an anonymous nested-inline destructor

The 25-byte row at 0x00255A40 was `??1Rva00255A40NestedDtor@@UAE@XZ`, an
address-derived placeholder in NestedInlineDestructors.cpp whose identity was
never recovered.

- The matched protected scalar-deleting wrapper `??_GRefundDie@@MAEPAXI@Z`
  (0x00255B70, RefundDieDeletingDestructor.cpp) calls its complete destructor
  through ILT 0x00001B4F, and 0x00001B4F is `jmp 0x00255A40`.
- `python3 tools/ilt_oracle.py check '??1RefundDie@@MAE@XZ' 0x00255A40`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The body stores the DieModule vtables (0x010A4CEC at +0x10, then 0x0109CB5C
  at +0 and 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53, the
  ObjectModule destructor: an empty derived destructor of a DieModule.
