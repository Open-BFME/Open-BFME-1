# Save/load menu caller binds to the existing byte setter

The two existing 63-byte rows at 005696D0 and 00569680 in
`HideSaveLoadMenu.cpp` both tail-jump at +39 hexadecimal to ILT 000290D2.
That thunk reaches the existing eight-byte `Rva00465B80::apply()` provider
in `TinyByteFieldSetters.cpp`: `c6 81 ac 01 00 00 01 c3`, a byte-1 store
at ECX+1AC followed by RET. The receiver is already loaded from 012F19E8.
The old undefined `WindowManager::hideQuitMenu()` declaration has the same
niladic thiscall ABI.

The caller now references that existing physical provider. Its local class
matches the provider's declaration, with no claim about the original semantic
owner. All globals retain their existing names and types. The menu flag,
reload of its global, additional zero store, shell flag, and receiver load
are unchanged.

Unchanged before/after scoped gates pass 45/45 rows: both caller rows and
all 43 rows of the provider TU. Both complete caller extents also resolve
strictly without masking; the existing second row's `gen-alias` fallback is
not used. No ledger or alias is added or changed. Eight DIR32 sites across
the two rows pass the normal address gate.

The complete caller object has identical raw section bytes and the same sole
function definition. Across its entire relocation inventory, only REL32 +3A
hexadecimal changes, from the undefined old method to the existing provider.
Data references, directives, and runtime/EH metadata are unchanged; no helper,
vtable, or EH code is introduced. The caller COFF header timestamp advances
42 seconds between these compilations; whole-object file equality is not
claimed. Provider source/object are byte-identical, and its
complete eight bytes independently match retail with no relocations.

The declared-function preflight passes. This is a binding repair with zero
new conversion bytes; the historical queue estimate is not a fresh link
preview, and no measured linked-byte gain is claimed.
