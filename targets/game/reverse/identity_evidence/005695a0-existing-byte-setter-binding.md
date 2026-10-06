# Surrender callback binds to the existing byte setter

The complete 116-byte callback at 005695A0 calls ILT 000290D2 at +39
hexadecimal after loading ECX from global 012F19E8. The thunk reaches
00465B80, the existing eight-byte `Rva00465B80::apply()` definition in
`TinyByteFieldSetters.cpp`. Its complete body is
`c6 81 ac 01 00 00 01 c3`: store byte 1 at ECX+1AC, then RET.

The undefined `WindowManager::hideQuitMenu()` spelling and this existing
provider have the same niladic thiscall ABI. The caller now declares the
existing address-qualified provider with its existing layout and calls it
using the same receiver. This does not establish the manager's original
semantic class. All global names and pointer types remain unchanged.

Both the menu path and the subsequent surrender-message path remain intact.
The call through ILT 000032AB, both virtual dispatches, their arguments and
all field stores are unchanged. No header, vtable, destructor, or lifetime
reconstruction is involved in this correction.

Before/after scoped gates pass all 44 rows: the callback and all 43 rows of
the provider TU. The complete callback resolves strictly without masking,
and all seven DIR32 sites pass the address check. Declared-function preflight
passes before and after.

Every caller raw section is byte-identical. Across the complete relocation
inventory, only REL32 +3A hexadecimal changes from the undefined method name
to the existing provider. Data references, other calls, directives and
runtime/EH metadata are unchanged. The COFF header timestamp advances 56
seconds between these compilations, so whole-object file equality is not
claimed. No additional code or metadata definition is emitted. The provider
source and complete object remain unchanged; its eight bytes independently
match retail with no relocations.

The supported historical queue supplied this lead. No fresh link census or
link-clean preview was run, and this repair claims zero new conversion or
measured linked bytes. No row, pin, alias, or baseline is changed.
