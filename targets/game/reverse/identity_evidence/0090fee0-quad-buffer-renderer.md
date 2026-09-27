# Quad-buffer renderer at 0x0090FEE0

The full body is 3,619 bytes: `ret 4` at 0x00910D00 (+0xE20), followed by
thirteen INT3 bytes and the next entry at 0x00910D10. Ghidra's 3,606-byte
function listing is short; the independently decoded carve and common tail
prove the full extent. ECX is the receiver. One stack slot is popped and never
read, so the bank uses address-derived `Rva0090FEE0Renderer::render(unsigned)`.
No semantic owner name is claimed. The caller at 0x005F1370 independently
forwards its first argument to the call at 0x005F26FE after loading the renderer
from VA 0x012F6D88. Ghidra's apparent fastcall/no-stack-argument signature is
not the retail ABI.

Three independently matched siblings establish the receiver, despite twenty
previous identity-only verdicts stopping at an incomplete destructor view.
The 48-byte constructor at 0x0090F650 writes six zero dwords at +0..14,
shader bits from VA 0x012D6E2C to +18, then four 1.0 floats at +1C..28. The
138-byte setter at 0x0090F8C0 stores a nonnegative signed primitive count at
+10 and applies four RefCountClass assignments at +0/+4/+8/+C. The complete
215-byte destructor at 0x0090F680 releases those four buffers and the texture
at +14. Its legacy 0x18-byte declaration describes only released members;
it does not contradict the constructor's independently proven 0x2C extent.
The bank uses canonical ShareBufferClass<Vector3/Vector4/Vector3/Vector2>
for positions, colors, normals, and UVs: their +0xC array pointer and record
strides 12/16/12/8 are directly read by the rendering loops.

The aligned caller loads colors from VA 0x012F6DCC and positions from
0x012F6DC8 at 0x005F26D3, pushes 0,0,colors,positions,count, loads the same
renderer, and calls the setter at 0x005F26EB. It emits eight vertices/two
primitives per particle and flushes at 512 primitives. This independent
caller corroborates the array order, count, texture-reference contract, and
one forwarded argument without relying on desired caller bytes.

The matched 339-byte initializer at 0x0090F760 creates two 3,072-index
buffers and writes 512 quad patterns. Its existing typed globals are
Rva01341214IndexBuffer (DX8IndexBufferClass*) and
Rva01341218SortingIndexBuffer (SortingIndexBufferClass*); the bank reuses
them. Each batch allocates four vertices per primitive and submits two
triangles. Retail passes delta*6 as the final draw count; the source keeps
that observed argument, rather than silently substituting delta*4.

The full native reconstruction restores world/view transforms, forces the
observed shader primary-gradient bits and disables culling, supplies the
prelit material and texture, chooses the ordinary or sorting index buffer,
then uploads chunks of at most 512 primitives. It copies all positions,
converts optional colors or fills the default color, copies optional normals
or fills (0,0,1), and copies optional UVs or cycles the four corner coordinates.
It uses the independently proven 12-byte center contract for sorting at
0x0093B340, not the incompatible legacy SphereClass reference declaration.
Both transforms are restored after the final batch.

The only assembly is existing, bounded compiler machinery: the CMOV clamp
arm independently matched in full Clamp_Color at 0x0090F310 (328 bytes;
94-byte arm begins at 0x0090F3FA), plus the canonical DX8Wrapper x87 color
packer. The renderer and its loops remain ordinary native C++. Native clamp
expressions compile to branches instead of the required CMOV arm; the bank
retains the already proven donor rather than transcribing the whole body.
Nearby independently matched native helpers corroborate each operation:
copyVec3Strided 0x0090FB60/49, color conversion 0x0090FBA0/571,
triple fill 0x0090FDE0/44, pair copy 0x0090FE10/43, and UV extract/reset
0x0090FE40/61. Making their capture structure visible did not improve this
caller. The by-value Vector4 contract of 0x0090F460/492 supplied a useful
new color-copy lifetime lever and is retained.

Final measured bank: 3,611 bytes, 1,113 probe-masked differing positions,
0x150-byte local frame, eight-byte extent deficit. Positional score is
`1-(1113+8)/3619 = 0.6902459242884775`; normalized instruction shape is
separately .974, with 26 structural differences. The first native attempt
was 3,572 bytes/.894 shape. The first complete optional-buffer model was
3,621/.973 but had 2,703 differing positions. By-value color capture reduced
that to 1,223; separate source advancement plus a Vector2 UV state produced
the selected 1,113-difference bank. No byte-match credit is claimed.

Remaining differences are prologue register-save scheduling, chunk-min
materialization, captured FVF/cursor lifetimes, UV stride hoisting, and stack
slots. Failed bounded levers include receiver-independent loop direction,
signed/unsigned counters, typed cursors, iterator helpers, direct versus
helper copies, count/delta declaration lifetimes, constructor placement,
by-reference versus by-value color captures, and /Os. The latter changes
the EH frame and is rejected. A 3,602-byte alternative with by-value color
and postincrement inside the call restores the prologue but has a 0x14C
frame and 1,223 differing positions; it is worse than the selected source.

No matched source or pin was changed. Before landing, run full scoped byte
verification and close every DIR32, especially the sorting gate at
VA 0x012D6D75, using independent witnesses. The typed index globals have the
matched initializer and destructor witnesses above. This bank is evidence
only and adds no native coverage.
