# Native override access in 00618980

The entry keeps the opaque `Rva00618980Object::rva00618980(int)` name.
The neighboring matched 00618A90 update supplies a witnessed layout, not a
semantic owner identity for this entry. Only the low byte of the integer
argument selects the state transition. The complete retail body ends in
RET 4 at RVA 006189DE, followed by INT3 at 006189E1: exactly 97 bytes.

The receiver fields accessed are pointer +4, holder pointer +C, active byte
+10 and float +14. Deactivation clears the latter two fields, resolves the
override at +4, and reads the float at resolved-data +10. It passes the
holder's pointer at +8 and three copies of that float to ILT 0002C9DA.
Activation sets +10 and clears +14. The method does nothing when the state
is already consistent with the requested low byte.

## Independent ABI and layout evidence

The ILT target is the matched `Rva007397E0(void *, float, float, float)`
body (225 bytes). Its tree walk passes the three floats to the matched
VertexMaterialClass::Set_Emissive. The already matched Rva00618A90Update.cpp
uses precisely this typed call and the same OVERRIDE-based data layout.
The other direct target is ILT 000022BB -> matched const
Overridable::getFinalOverride at 00087A80. Native Override.h and Overridable.h
provide the inline null/next-override path and its correctly typed call.
Ghidra bytes at VA 00A189B0 independently confirm the result dword load,
holder pointer in EDX, three equal-value pushes and final holder push.

## Measured change

The preferred bank uses raw integer arguments, a volatile receiver view,
an unused volatile home and a provisional bfmeReportGN callee. It measures
97 bytes with two register differences: tag load/push ECX versus EDX.
Correcting the callee to the proven float prototype while explicitly
reinterpreting the local integer bits preserves those two differences.
Replacing the manual override resolution and volatile scaffolding with the
native OVERRIDE member, ordinary float fields and ordinary state updates
matches the complete 97 bytes modulo relocation slots. The native source
contains neither volatile accesses nor barriers nor argument-bit facades.
No new callee pin or assembly is needed.

The strict scoped build validates both direct targets and the full body.

The bank names BfmeThingGN and BfmeSourceGN are preserved for the resolved
data and render-object holder views; their layouts come from the neighboring
matched update. These are distinct types at receiver +4 and +C.
