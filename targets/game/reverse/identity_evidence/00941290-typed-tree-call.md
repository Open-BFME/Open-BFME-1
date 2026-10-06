# RVA 00941290: bind the existing tree-search call

GPT-6, 2026-10-06. This is a callable-provider correction in the existing
81-byte FontCharsClass_Get_Char_Data_BFME.cpp body. The function's current
name, layout and coverage are retained. No new conversion or LINKED-byte
gain is claimed.

## Exact change and ABI

The call at RVA 009412AD passes the font's +0x450 map address in ECX and
the address of its unsigned-short character parameter on the stack. The
60-byte target at 0093DCE0 reads the key, returns a node/header pointer in
EAX, performs no writes, and ends with RET4. Its physical provider is now
`Rva0093DCE0Tree::find(const unsigned short &) const`.

The caller includes that provider's existing header and calls it through
the same map address. Only the returned pointer is cast to the existing
FontCharDataMapNode view, which continues to read its payload at +0x14.
The unused nonvirtual FontCharDataMap::find declaration is removed; this
does not change the map's data layout. No helper, virtual function, friend,
visibility change, inheritance claim or replacement pin is introduced.
After confirming that this was the old method's only source user, its
obsolete nominal pin is retired. The real provider's row supplies the address.

## Preserved loader and font scope

The second direct call at 009412C0 still names the same loadCharacterData
member and targets 00940D40. Retail passes the original character by value
and the same font receiver in ECX. That loader reads a word argument,
preserves the receiver in EBP, accesses the map at +0x450, returns through
EAX and ends with RET4 at offset 0x548. Its declaration, pin and generated
assembly provider remain unchanged. This patch does not repair that
loader's nominal source binding.

The font data members, header comparison, payload load, alternate-font loop
and complete member signature are unchanged. The separate canonical
render2dsentence.h layout/API cannot replace this existing BFME view as-is:
it lacks the map and loadCharacterData member and gives Get_Char_Data a
different access/return-tag spelling. The incompatible-layout cases described
in docs/header_adoption.md remain outside this patch. No new FontCharsClass
declaration or original-owner/name claim is made. Its existing ODR/name
disagreement is not solved by a correct physical call route.

## Verification

The current before object is already 81 bytes, and strict resolution of its
two calls reproduces the complete retail body. An older 86-byte experiment
is not evidence about this current source/compiler result.

The first unchanged source gate after the edit passes all 81 bytes. The
combined gate passes all 43 rows across the caller, physical tree provider,
two iterator wrappers and unchanged ConnectionManager translation unit,
including string/constant, DIR32 and body checks. All five objects passed
normal dependency validation in that combined run; its zero recompiles do
not replace the preceding fresh caller compile.

Independent object review passes all 81 resolved bytes and every complete
section, including debug sections. Symbol definitions and auxiliary records
are unchanged after substituting the single undefined tree-call name at
offset 30. The loader relocation at offset 49 is identical. The existing
tree header is unchanged; its dependent set adds only this caller, growing
from three to four sources. There is no current accepted linking index, so these checks do
not establish a final selected-provider or LINKED-byte result.

Receipts and before/after artifacts are under
`build/font-map-caller-00941290-20261006/` in the working checkout.
