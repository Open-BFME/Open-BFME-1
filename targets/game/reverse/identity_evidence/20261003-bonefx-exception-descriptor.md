# BoneFXDamage exception descriptor contradiction

The existing 154-byte `?onObjectCreated@BoneFXDamage@@MAEXXZ` at RVA
`0x00250880` compiles an `INIException` with a trivial implicit destructor.
Its COFF `__TI1?AVINIException@@` is a 16-byte ThrowInfo: offset +4 is literal
zero, with no relocation. Its only relocation is the catchable-type array
at +12. This contradicts the runtime destruction callback in retail.

The instruction at VA `0x006508FC` pushes ThrowInfo VA `0x011DFC30` (operand
at body +0x7D). Its full DWORDs are `0, 0x0041460F, 0, 0x011DFC28`.
Ghidra and the unpacked retail PE independently agree on all 16 bytes.
ILT `0x0041460F` jumps to RVA `0x00061BD0`, a ten-byte body:
`mov eax,[ecx]; push eax; call 0x00C81EF0; pop ecx; ret`, followed by INT3.
This is a real array-release callback, not a null destruction operation.

The catchable array has count 1 and pointer `0x011DFC08`. Its record is
`0, 0x012A6FD4, 0, -1, 0, 8, 0x00448621`; the type descriptor contains the
complete native RTTI spelling `.?AVINIException@@`. Thus the descriptor really
belongs to the named eight-byte exception; it is not a pointer to arbitrary
neighboring data. The parent ends at RET VA `0x00650919`, followed by INT3 at
`0x0065091A`. Existing cleanup RVA `0x00C0E680` resets the static-init guard;
it is not evidence of exception-object destruction.

The pre-integration fresh-input object hash is
`1480ab500b8be9c8ddf81ac1518f22f62278b8b4e8e28030e66f1ea5d6ba79ae`.
The branch function/reference checks passed both TU claims, while data_check
reported the independently anchored ThrowInfo +4 mismatch. After the authorized clean rebase, the scoped build again passes both
claims, two complete strings and two DIR32 references. The static-guard cleanup
label heals from `$L358` to `$L362`; that is byte evidence, not a new identity. Instruction comparison does
not verify the complete referenced exception descriptor.

AGENTS.md requires the covered type's canonical header; both existing
`shims/ini/Common/INIException.h` and `shims/iniexception/Common/INIException.h`
declare the missing destructor. Merely including that declaration would still
need complete callback/copy/RTTI verification: the current named destructor row
at RVA `0x00139FF0` has a conditional null guard and differs from this runtime
callback. The `0x00061BD0` row remains address-derived. This finding supplies
no speculative second identity or fallback pin.

Repair needs the authentic exception lifetime and independently resolved data
callbacks together. No source, identity, extent, pin or baseline is changed by
this evidence-only record. The historical read-only scan also found four
references to this same false descriptor in TerrainRoads parsers `0x00601D40`
and `0x00601E90`; those are follow-up candidates, not additional fixes here.
