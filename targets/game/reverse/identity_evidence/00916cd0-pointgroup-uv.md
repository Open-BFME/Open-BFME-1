# PointGroup UV helper, 0x00916CD0

The independently matched `PointGroupClass::Render(RenderInfoClass &, int)`
at 0x00917B70 calls this helper at +0x26C with ECX=this and the current frame
pointer, active point count, and its opaque second argument. The existing
address-derived pin `?rva00916CD0@PointGroupClass@@QAEXPAEHH@Z` has that same
12-byte argument ABI. The implementation retains that public opaque word;
retail uses a nonzero value as an address of four floats. This proves the
memory use without inventing a semantic rectangle class. There are no callees.

The full body is 1453 bytes, ending in `ret 12` at +0x5AA and followed by
three INT3 bytes before 0x00917280. Ghidra agrees on this complete extent.

Name-oracle witnesses FrameRowColumnCountLog2 at +0x20. Independently matched
Set_Frame_Row_Column_Count_Log2 at 0x00912130 clamps that field to 0..4.
Set_Point_Frame at 0x00912060 and Get_Point_Frame at 0x00912070 independently
prove DefaultPointFrame at +0x49. PointMode at +0x2C is established by its
matched accessors. Unused +0x24/+0x28 members retain address-derived names.
Canonical Vector2/3/4, VectorClass, and ShareBufferClass headers are included;
the PointGroup local view is needed because pointgr.h omits BFME's helpers,
as in the existing matched PointGroupClassRender.cpp.

All five DIR32 sites have independent data witnesses:

- +0x6 names VertexUV+4, VA 0x0134369C. The matched sizing helper 0x00914860
  loads ECX=0x01343698 at +0x39 before resizing the VectorClass<Vector2>.
- +0x42/+0x291 name the triangle frame table, VA 0x01341238.
- +0x13F/+0x3FA name the quad frame table, VA 0x0134124C.

The independently matched initializer 0x00917280 stores its allocated triangle
and quad arrays at 0x00917573 and 0x00917596 respectively. Its source builds
three and four Vector2 values per frame, agreeing with the strides here.
The shutdown body at 0x00912CF0 deletes these same tables. Each repeated
relocation subtracts a zero addend and resolves to the same table address.

The native source follows retail's actual behavior. When the incoming frame
pointer is nonzero, it duplicates frame zero and does not read the per-point
frame bytes. With a null pointer it selects DefaultPointFrame masked by the
frame grid, optionally modifies that table entry in place using the four-float
bounds, then duplicates it. This differs from the Zero Hour twin, which reads
per-point frame indices and lacks the bounds adjustment. Ordinary pointer
loops let VC7.1 unroll the copies; no instruction lifting or explicit unrolled
assembly was used. The first native probe matched all 1453 bytes modulo the
five independently checked data relocations. No new pin or helper claim is
needed; this replaces one generated dump range with one real native body.
