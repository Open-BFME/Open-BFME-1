# RVA0020DF90 forwards an x87 result

The existing ILT atRVA00034D65 is E9 ->0020DF90. The complete wrapper has38
bytes through RET4 at0020DFB3; INT3 starts0020DFB6. Ghidra FUN_0060df90 and
independent PE disassembly agree. It calls slot14 (offset38h) through the
primary receiver at this-10h, then calls ILT0002FA77 with receiver this+C8h
and arguments(input, pointer at this-8h,1). That ILT resolves to001B0200.

The old bank declared both the wrapper and its final callee void. This was
an ABI error, not an unreachable scratch-register permutation. The callee's
full232-byte extent ends at RET12 at001B02E5 and INT3 at001B02E8. Its early
path loads the single-precision input amount into ST0 at001B021B and returns
at001B0223. The other path computes a floating-point result and all exits
through001B02DE..001B02E5 leave it in ST0. The wrapper has no FSTP or other
instruction after its call that would discard that value: it forwards ST0.

This ABI is independently witnessed by the existing matched
ActiveBody::attemptHealing at0020FBC0, which consumes the same callee's float
result, and its canonical declaration/pin:
`?adjust@HealingArmor001B0200@@QAEMPAXPAVObject@@H@Z` at001B0200.
The pin's consistency check passes. Reuse it without adding another alias.
The second pointer is an Object* as established by that existing callee audit;
this TU only forward-declares Object and never redeclares its layout.

Changing both returns to float reproduces all38 bytes, including retail's
EAX/ECX argument loads where the void bank usedECX/EDX. Reusing the canonical
callee name and Object* argument retains that exact shape. The strict gate
must verify its one REL32 binding. The return value has independent image
evidence; it is not inferred from a successful compiler experiment alone.

Keep the wrapper's address-derived Rva0020DF90Part identity. The primary
slot is named only slot14 inside an address-qualified local view. No original
ActiveBody method name or field spelling is claimed for this wrapper, and
no synthetic padded member object is needed to calculate this+C8h.
