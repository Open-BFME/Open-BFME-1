# Radial image caller and private texture helper

The caller at RVA 0x006F1AC0 is 1416 bytes: the final RET 0x1C is at +0x585,
followed by INT3 at +0x588. Ghidra's independently created function has that
same extent. Its owner/method identity remains unproved, so the reconstruction
retains `RadialImage006F1AC0::draw`. The five calls through ILT 0x00024BCC
reach the already matched Render2DClass::Add_Tri at 0x006EB070. They pass
six two-float references and a color, consistent with its verified source.
The adapter reuses that existing symbol, rather than pinning a second name.

The score-0.99858757 stash was the starting point. After removing a stale
StringBase::str specialization (the canonical header now provides it), it
again differed only at +0xC5/+0xCB: EDX instead of EAX for the first renderer
store. In-class inline setters for **both** fields (+0 and +0x54) make the
complete 1416-byte caller exact modulo its 43 relocation sites. Only the first
setter fixes that first store but perturbs later allocations (272 differences).
The setters keep their address-qualified names and perform just the original
stores. Enum storage and a nested clamp scope leave the original two bytes.

## Private helper, RVA 0x006F18F0

The complete helper is 371 bytes: RET at +0x172, INT3 at +0x173. The caller
loads ECX with Image and pushes a hidden result address; its call at +0xDF
reaches the helper directly, then ADD ESP,4 performs caller cleanup. The helper
returns that result address in EAX. Both Ghidra and retail decoding confirm
this compiler-private convention. A static C++ function compiled with its
actual caller reproduces it without an assembly adapter.

Its native handle, texture, image and asset declarations come from the banked
paired reconstruction documented in 006f21b0-private-helper-and-frame.md.
The helper independently probes exact over all 371 bytes and 21 relocations.
It checks Image status+0x30, copies the one-word raw handle through Image+0x2C,
and increments the underlying texture's 16-bit reference count at +4. Both
paths call the established ShroudTexture::getFilter and set filter+0x10/+0x0C
to one. The loaded-texture path also calls Gen_0090E810::bfmeSetFlag(1).

The native asset-local storage uses the **existing** BfmeList950B constructor
provider at 0x00143B20 through ILT 0x0002FB80, avoiding a second ctor identity.
Its native pointer set reproduces the actual cleanup at 0x00140950 through
ILT 0x00015D7A. A local address-qualified insertion adapter calls the existing
AssetList::operator<<(AsciiString const&) at 0x00141D00 through 0x0001A44C.
This is the same layout view used by existing W3DAptComponentView3D.cpp:
20-byte storage, tree at +0, trailing word at +0x0C and flag at +0x10.
No new inheritance or constructor alias is asserted.

Image::getFilename uses existing ILT 0x000336AE -> 0x00520640 and its canonical
AsciiString return. The native BFMEGetWaterTrackTexture at 0x0090E910 returns
the retained one-word handle. Release uses the existing TextureClass::Release_Ref
binding to 0x009EB7A0. Asset tracking uses Rva0134FAA0 and the established
cdecl one-word Rva009EBAC0, keeping its address-based identity.

## Renderer texture setter, RVA 0x006EB000

The 54-byte body receives the renderer in ECX and a reference to a one-word
retained texture handle on the stack. It compares the input word to renderer
+0x4C, increments input->refs+4, releases the old texture through 0x009EB7A0,
and stores the new texture and a zero/nonzero-derived flag at +0x4C/+0x50.
Its final RET 4 is at +0x33; INT3 starts at +0x36. This independently supports
the address-qualified `Render006F1AC0::setTexture006EB000` declaration, without
asserting a new semantic identity. A body pin, rather than an ILT route alias,
can resolve the caller's observed 0x00032F51 call.
