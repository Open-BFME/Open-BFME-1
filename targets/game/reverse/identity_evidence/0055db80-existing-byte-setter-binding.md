# HideQuitMenu calls the existing 00465B80 byte setter

The matched 21-byte caller at 0055DB80 used the undefined spelling
`WindowManager::hideQuitMenu`. Its only branch leaving the body is the tail
jump at +0F to ILT 000290D2. That thunk jumps to 00465B80, the existing
eight-byte `Rva00465B80::apply()` in `TinyByteFieldSetters.cpp`.

The complete target is `c6 81 ac 01 00 00 01 c3`: it stores byte 1 at
ECX+1AC and returns, with no stack arguments or return-value contract.
This is the same niladic thiscall ABI as the old declaration. The caller
already loads ECX from global 012F19E8. The normal symbol map includes the
existing provider's ILT route; no pin or alias is added.

The caller now names that physical provider. Its local declaration preserves
the existing provider's field layout; it does not identify the original
semantic class. The global declarations retain their original pointer types
and names. The condition still reads global 012F4AD4, and both DIR32 addresses
remain unchanged.

Before and after the change, the unchanged scoped gate passes all 44 rows:
the caller's one row and all 43 rows of the existing provider TU. The complete
21-byte caller resolves exactly to retail, and the physical provider's complete
eight bytes match with no relocations. The provider source and object are
unchanged.

Every raw section of the caller object, including its debug sections, is
byte-identical. Across the complete relocation inventory, the sole change is
REL32 at +10 hexadecimal, from the undefined old spelling to the existing
provider. The two data relocations, sole function definition, directives,
and metadata are unchanged. No extra function, vtable, or EH helper is emitted.
The declared-function check passes both before and after.

The checked-in queue identified this stale undefined name, but its historical
byte estimate is not a current link preview. This repair claims zero new
conversion bytes and zero measured linked bytes; no full link census was run.
