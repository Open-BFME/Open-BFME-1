// ?Draw@DX8Wrapper@@CAXHGGGGH@Z
// partial score=0.72 date=2026-09-09
// Retail 0x00906B40 size 526; last compile 540 bytes (14 over).
//
// This supersedes the earlier 0.48 stash: the earlier attempt invented free
// globals and a fake VertexBufferClass/IDirect3DDevice8, which never had a
// chance of byte-matching. dx8wrapper.cpp already carries a "present-unmatched"
// Draw ported straight from Zero Hour (~line 2131) using the REAL DX8Wrapper
// class/RenderStateStruct from dx8wrapper.h -- port onto THAT instead.
//
// Header change needed (dx8wrapper.h, DX8Wrapper private section):
//   static void Draw(
//       int primitive_type,              // was `unsigned` -- real row mangles H not I
//       unsigned short start_index,
//       unsigned short polygon_count,
//       unsigned short min_vertex_index,
//       unsigned short vertex_count,
//       int apply_render_state=1);       // NEW 6th arg; BFME-only, ZH's Draw has 5.
//   (Draw_Triangles x2 / Draw_Strip keep calling Draw with 5 args -- the
//   default covers them, no other edits needed. This is a shared-header edit,
//   full gate.)
//
// dx8wrapper.cpp Draw body changes vs the present-unmatched ZH text:
//   1. New material low-diffuse skip block before Apply_Render_State_Changes():
//        extern unsigned char g_Va0133F42C;      // no pin needed, DIR32 masked
//        extern float g_bfmeScaleBK;               // already pinned 0x1075C70
//        if (g_Va0133F42C) {
//            VertexMaterialClass *mat = render_state.material;
//            if (!mat) return;
//            Vector3 emissive;
//            mat->Get_Emissive(&emissive);           // NOT Get_Diffuse
//            if (emissive.X<g_bfmeScaleBK && emissive.Y<g_bfmeScaleBK && emissive.Z<g_bfmeScaleBK) return;
//        }
//      g_Va0133F42C is the SAME global SmallLeafBodies2.cpp reads as
//      Rva006D1C10GetFlag (0x0133F42C) -- reuse that extern, do not repin.
//   2. Remove `#ifdef MESH_RENDER_SNAPSHOT_ENABLED`/`#endif` around the
//      ValidateDevice block -- just wrap it in a bare `{ }`. WWDEBUG_SAY is a
//      no-op macro in this build so the whole HRESULT switch compiles away;
//      retail's single g_Va0133F451 (SnapshotActivated) test survives.
//   3. Split the tail on the new apply_render_state param:
//        if (!*(unsigned char *)&apply_render_state) {   // see note below
//            DX8_RECORD_RENDER(polygon_count,vertex_count,render_state.shader);
//            DX8_RECORD_DRAW_CALLS();
//            DX8CALL(DrawPrimitive((D3DPRIMITIVETYPE)primitive_type,min_vertex_index,polygon_count));
//            return;
//        }
//        switch (render_state.vertex_buffer_types[0]) { ...unchanged ZH switch... }
//      `if (!apply_render_state)` alone (plain int test) compiles the param
//      into a register (mov esi,[esp+N]; test esi,esi) and costs 14 bytes vs
//      retail's bare `cmp byte ptr [esp+N],0`. Casting through
//      `*(unsigned char*)&apply_render_state` gets MSVC to emit the same byte
//      compare and closed that 14-byte gap outright -- keep this cast.
//
// Symbol pins needed (reverse/symbols.csv, additive, CRLF):
//   ?Draw_Sorting_IB_VB@DX8Wrapper@@CAXIGGGG@Z,0x00904660,<note>
//     (already-declared header member; retail's SORTING/DYNAMIC_SORTING arm
//     calls RVA 0x00904660, currently gen_asm d_00904660/d_00904510.asm 550B)
//   ?Record_DX8_Polys_And_Vertices@Debug_Statistics@@YAXHHABVShaderClass@@@Z,0x009373A0,<note>
//     (matched row 0x009373A0 is pinned under d_009373a0 + an object-symbol
//     note that has an extra "@1@" back-reference from statistics.cpp's
//     NESTED forward-declared ShaderClass; dx8wrapper.cpp's ShaderClass is
//     top-level so the compiler emits ...ABVShaderClass@@@Z WITHOUT the "1" --
//     pin that exact string or the call stays unresolved.)
//   Apply_Render_State_Changes@DX8Wrapper@@SAXXZ is ALREADY pinned to
//   0x00904890 -- no action needed there.
//
// REMAINING BLOCKER (not closed, needs a fresh 40-min slot):
//   compiled ValidateDevice lands at vtable+0x11C (slot 71); retail calls it
//   at +0x118 (slot 70) -- one slot EARLY somewhere before it in
//   reference/shims/d3d8_shim_validated.h. DrawPrimitive/DrawIndexedPrimitive
//   land at +0x134/+0x138; retail wants +0x144/+0x148 -- a 4-SLOT gap that
//   opens up between ValidateDevice and DrawPrimitive (retail has 11 slots
//   between them incl. ValidateDevice, the shim only has 6: GetInfo +
//   4 palette methods, the plain D3D8 SDK count). This mirrors the existing
//   DevReserved37..43 hack applied around SetTransform/SetRenderState --BFME's
//   real device vtable inserts ~5 MORE reserved slots somewhere between
//   SetTextureStageState/ValidateDevice and DrawPrimitive that the shim does
//   not yet model. That header is SHARED (d3d8_shim_validated.h, full gate) and
//   used by ~15+ other DX8Wrapper .cpp files already matched on the SLOTS
//   BEFORE this range -- inserting reserved slots here needs corroboration
//   from another D3D8 method call in that exact range (e.g. GetInfo,
//   SetPaletteEntries, or another Draw* body) before editing it blind.
//   Once the shim is fixed this body should drop to at or near zero diffs;
//   everything else (control flow, field layout, the two REL32 pins above)
//   already matches through the whole function shape.
