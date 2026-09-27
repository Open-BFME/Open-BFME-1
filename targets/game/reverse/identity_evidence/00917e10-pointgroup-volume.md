# PointGroup volume renderer, 0x00917E10

The complete 952-byte entry is bounded by the next function at 0x009181D0
with eight INT3 bytes after the final `ret 12` at +0x3B5. It takes a render
info reference, unsigned depth, and a third opaque integer. Its fallback
passes the same receiver and first/third arguments to the independently
matched PointGroupClass::Render. It calls the other independently matched
PointGroup helpers using the same receiver and witnessed +4/+1C/+30 fields.
The official RenderVolumeParticle twin independently explains depth clamping
at 16, camera displacement per layer, and repeated point submission. Keep
`?rva00917E10@PointGroupClass@@QAEXAAVRenderInfoClass@@IH@Z` until an identity
review chooses whether this twin and receiver evidence warrant the semantic
name; this bank asserts only the address-derived member identity.

Ghidra and the carved/generated boundary independently agree on 952 bytes.
The raw input caller at 0x005F31A0 is not needed for a guessed semantic name.
The body falls back for depth <=1 or absent TRANSFORM/BILLBOARD flags, prepares
and compresses the point buffers, sizes the output, fills diffuse and UV data,
then takes the camera position and shifts each point along the camera vector
for each layer. It transforms the shifted positions and calls the geometry
and submission helpers. All of this bank is ordinary C++; there is no new
assembly, volatile access, speculative pin, or source coverage claim.

The first native source emitted 939/952 bytes. Keeping original_loc separate
while assigning current_loc to the transformed buffer at the end of each
layer recovered retail's saved original pointer. Explicit scalar component
scales recovered the observed x87 dataflow. The result is 952/952 bytes with
12 probe-masked differing bytes, all between +0x2D6 and +0x30B in matrix Y/Z
rows. The measured positional bank score is `(952-12)/952`, or
0.9873949579831933; normalized instruction shape is separately 1.000.

The known exact compression helper at 0x00917920 remains visible as in the
landed PointGroupClassRender.cpp. Hiding helper bodies changes the frame and
pointer reload behavior. Shared-source term permutations, named scalar sum
chains, both canonical Transform_Vector overloads, a narrowly volatile
matrix load, and a strict-floating inline helper did not improve the twelve
operand bytes; rejected variants remain scratch only. Matrix3D cannot be
passed to the canonical Get_Transform Matrix4 reference API and was rejected.

Relocation closure is not claimed. Before landing, verify every DIR32 and
the emitted out-of-line `PointGroupClass::rva00914860` sizing helper call:
retail reaches the independently matched 96-byte Rva00914860Sizer body, but
this TU uses a PointGroup member view and may need a scoped contract repair.
The remaining direct targets have the independently matched/pinned family
contracts already used by the exact main Render; the submit body 0x00913AF0
is still a bank, with its existing address-derived pin. Do not create pins
from the caller's desired bytes without the ordinary independent ABI proof.
