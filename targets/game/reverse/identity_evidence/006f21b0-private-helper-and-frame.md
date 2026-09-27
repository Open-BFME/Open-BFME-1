# W3DDisplay D4: private helper and frame recovery

This is banked evidence, with zero native byte credit. The complete renderer
extent remains RVA006F21B0..006F26D0 (1312 bytes): 1285 executable bytes,
three alignment bytes, then six switch addresses. The existing dump ledger
still has 1285 and must be corrected only with a successful landing.

Investigation ran from 01:24:50 to 01:52:51 UTC on 2026-09-27 (28 minutes).
Model: GPT-6. Ghidra was opened read-only with no analysis; baseline SHA256
c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9.

## New source evidence

The static native helper at006F18F0 has the complete371-byte body. Compiling
it beside its actual caller gives ECX=Image, a hidden return pointer on the
stack, plain RET, and caller ADD ESP,4. This closes the earlier claimed
compiler blocker without an adapter or assembly. An unused standalone static
helper is omitted by VC7.1, so an artificial emitter was not added.

Providing the already matched, complete252-byte Add_Tri at006EB070 lets the
compiler reuse the six Vector2 temporaries across the two calls. The caller's
frame drops from88 to the retail58, and total size from1396 to1312. Both Add_Tri
and the texture helper probe exact. Merely adding scopes around the calls or
naming their vectors does not reduce the frame.

The final renderer retains171 positional byte differences outside its68
relocation bytes; concrete agreement is (1244-171)/1244 =0.862540192926045.
Code-only normalized instruction agreement is0.9713467048710601, but that is
not the bank score. The first difference is +C7: retail loads ECX from the
handle and copies it to EDX; native loads EBP and copies it to EAX. A later
EAX/ECX/EDX cycle changes rectangle loads and triangle argument scheduling.
The x87 clipping operations and both triangle/quad call offsets agree.

A nested pair update, explicit old/new pointer locals, a value getter, pointer
conversion, member and out-of-line setter bodies, bool field types, UV getter,
rectangle declaration order, real Add_Quad visibility and real Release_Ref
visibility did not close the residue. A pointer-reference setter changed the
behavioral alias model and shortened the source to1304; it was rejected.

## Callee and data checks

- Helper raw-texture branch reads Image+2C as a pointer to a one-word retained
  texture handle. Image status+30 and UV+14 are named by the layout oracle.
- Helper's aligned constructor call +83 routes through ILT0002FB80 to143B20.
  Its complete65-byte body builds a20-byte AssetList: pointer-set at0,
  field0C=0, changed+10=1. Independent AssetList operator141D00 and pointer-set
  destructor140950 establish the layout; the legacy ctor name is BfmeList950B.
- Strict helper verification resolves every other REL32. Only the unpinned
  AssetList ctor name remains. No pin was added, and no speculative alias is
  retained in the bank. Future landing can carry this single independently
  supported repair after pin-consistency checks.
- Image::getFilename at520640 is reached via336AE with its existing native
  AsciiString result ABI. String cleanup resolves to887940. Pointer-set
  destruction via15D7A resolves to140950.
- Four getFilter calls reach90DD50: the one-word handle selects texture+1C or
  its static fallback. The stores atfilter+10/+0C set1. The flag helper90E810
  normalizes its byte input into texture+38. Texture release9EB7A0 is the
  independently matched36-byte word-refcount leaf. BFMEGetWaterTrackTexture
  at90E910 is the existing native309-byte retained-result function.
- Global0134FAA0 is the Rva009EB960 pointer installed by the independently
  matched Display init. Rva009EBAC0 remains address-derived; its established
  cdecl one-word ABI forwards the address of the AssetList unchanged.

## Preferred bank

The former0.98 score measured normalized instruction agreement and retained
an incorrect member-return cleanup convention. It is not comparable to the
new concrete-byte score. re_log archived the old source before recording the
new alternative. The preferred pointer was explicitly updated to the new,
fully measured caller/helper source despite the numerically smaller score.
The old archive99c965290bcd48352c9b39ab4f5181f579f398b86f7889e088239dbaa5b5e8a2
remains unchanged. Both address banks carry this complete paired source.
