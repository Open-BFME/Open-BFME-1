# Elven text scale: preserve the separate readonly datum

The matched 1170-byte body at RVA `0x00471900` multiplies its scale by the
float at VA `0x010F7540`: instruction `D8 0D 40 75 0F 01` at RVA
`0x00471946`. Ghidra memory and the unpacked retail PE both contain
`00 00 40 3F` at that address (0.75f). The body ends at RET `0x00471D91`,
followed by INT3 padding at `0x00471D92`.

The previous numeric pointer bypassed relocation handling. Replacing it with
a scalar literal preserves the instruction bytes but produces the pooled
`__real@3f400000` symbol, whose existing DIR32 anchor is the different
VA `0x0109F748`; the strict gate correctly rejects that binding. Making the
read volatile changes the instruction schedule and does not match.

A TU-local one-element const array retains the existing address-qualified
source name `ElvenTextScale010F7540`. It emits a distinct four-byte readonly
`.rdata` datum, `_ElvenTextScale010F7540`, with flags `0x40300040`, and the
multiply uses a real DIR32 relocation at body `+0x48`. The array is a source
representation of the witnessed scalar storage, not evidence for an original
EA array declaration. No volatile, assembly, new pin, or shared-header change
is used.

The normal scoped gate verifies all 1170 function bytes, seven string literals,
four pooled float references, and thirteen externally named DIR32 references.
Because TU-local data is outside the last check, a separate COFF/retail proof
follows the relocation at `+0x48`, its symbol value and addend, and compares
all four bytes at the resulting local `.rdata` window with the actual retail
operand target. Both contain `0000403f`; the section is readable and not
writable. Thus the repair proves the new reference as well as the function.
The function identity and extent remain unchanged; no byte coverage is added.
