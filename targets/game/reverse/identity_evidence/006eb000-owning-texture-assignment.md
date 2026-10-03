# RVA 0x006EB000: owning texture-reference assignment

The semantic owner and method remain unproven. `Rva006EB000::method` and
`Rva006EB000TextureRef` retain the body address; no semantic rename is claimed.
The native source lives with the WW3D texture users and includes `texture.h`.

## Boundary and ABI

Retail decoding and Ghidra show one receiver in ECX and one stack argument,
a borrowed address containing a texture pointer. The body compares that pointer
with receiver+0x4C, increments the new texture low-word reference count at +4,
releases the old texture, then reloads the borrowed pointer. RET 4 at RVA
0x006EB033 ends the 54-byte body; INT3 starts at 0x006EB036. The final stores
are pointer/EAX to +0x4C followed by zero-or-minus-one/ECX to +0x50.

## Release dependency

The sole direct call at RVA 0x006EB01E reaches 0x009EB7A0. Independent decoding
of all 36 bytes shows a low-word zero guard, `dec word [ecx+4]`, another low-word
zero test, the ownership flag 0x01000000, and a tail dispatch to vtable+0x20.
This is the existing TextureBaseClass release contract; the canonical
`texture.h` supplies Add_Ref and Release_Ref. The existing TextureBaseClass pin
is consistent. No new pin or duplicate identity is introduced; the old ledger's
additional TextureClass release alias is outside this recovery's scope.

## Source shape and verification

The served bank emits 54 bytes with four differences: its last stores are
reversed. Merely reversing the source assignments emits 52 bytes and destroys
the separate ECX mask value. Making the known release implementation visible
does not help. An inlined assignment on the one-pointer owning handle, followed
by the mask update, emits the correct EAX/ECX schedule and both stores. A native
TextureBaseClass version using a real handle member and reference argument
matches all 54 bytes, including the direct call target in the strict gate.
The handle assignment retains the source reload after release, and the outer
identity guard preserves the no-op when source and destination already agree.

## Opaque owner correction

The old bank explicitly labels its identity unknown. `BfmeHostERB` is a
bank-only generated placeholder and has no owner-name witness; it is replaced
by `Rva006EB000`, as required for an unknown owner. No recovered semantic name
is removed. The bank pointee `BfmeTexERB` is replaced by the included native
TextureBaseClass; the separate one-pointer handle remains address-qualified.
The existing m_bfmeTexERB and m_bfmeMaskERB member names remain at their original
+0x4C and +0x50 locations. The exact-snapshot name correction documents only
the placeholder-owner replacement.
