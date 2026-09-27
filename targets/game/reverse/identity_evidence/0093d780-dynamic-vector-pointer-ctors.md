# DynamicVectorClass<T *> constructors named by the vtables they install

Every `DynamicVectorClass<T *>(unsigned, T * const *)` body is the same 93 bytes
for every pointer `T`, so the bytes cannot name `T`. Retail was linked without
identical-COMDAT folding, so each instantiation has exactly one vtable pair. A
constructor names its instantiation by the pair it stores: the VectorClass table
(code +0x09) and the DynamicVectorClass table (code +0x43).

| body | VectorClass table | DynamicVectorClass table | named before | identity |
|---|---|---|---|---|
| 0x0093D780 | 0x0107385C | 0x0113CDF4 | `<unsigned long>` | `<Render2DClass *>` |
| 0x0094E490 | 0x0113D080 | 0x0113D0B0 | `<LegacyMaterialClass *>` | `<unsigned long>` |
| 0x0096E000 | 0x0113E690 | 0x0113E6A8 | `<HAnimComboDataClass *>` | `<LegacyMaterialClass *>` |
| 0x009745E0 | 0x0113EAE0 | 0x0113EB10 | `<RenderObjClass *>` | `<HAnimComboDataClass *>` |
| 0x00981490 | 0x0113F0B8 | 0x0113F12C | `<VertexMaterialClass *>` | `<RenderObjClass *>` |

Owners whose member or local types Zero Hour declares name the tables:

- `MeshLoadContextClass::MeshLoadContextClass` (0x00970180) stores 0x0113E6A8 at
  member +0x94, 0x0113C644 at +0xAC, 0x0113C614 at +0xC4 and 0x0113D0B0 at +0xDC,
  0x18 bytes apart. meshmdlio.cpp declares `LegacyMaterials<LegacyMaterialClass *>`,
  `Shaders<ShaderClass>`, `VertexMaterials<VertexMaterialClass *>` and
  `VertexMaterialCrcs<unsigned long>` in that order.
- 0x0094E490 is also the constructor called by the static initializer at
  0x00C6E0D0 for the global at 0x0134B1A0, which has an atexit destructor. Zero Hour
  meshmdl.cpp has `static DynamicVectorClass<unsigned long> _TempClipFlagBuffer`.
- `Render2DSentenceClass::Allocate_New_Surface` (0x00941A00) builds a local
  `PendingSurfaceStruct`, whose only vector is
  `DynamicVectorClass<Render2DClass *> Renderers`. It stores 0x0113CDF4 when it
  builds the local (code +0x1B2) and 0x0107385C when it destroys it (code +0x207).
- `HAnimComboClass::HAnimComboClass` (0x009747F0 and 0x00974820) stores 0x0113EB10,
  and `~HAnimComboClass` (0x00974F10) stores 0x0113EAE0, in its only member,
  `DynamicVectorClass<HAnimComboDataClass *> HAnimComboData`.
- `AggregateDefClass::Build_Subobject_List` (0x009817D0) stores 0x0113F12C for its
  two `DynamicVectorClass<RenderObjClass *>` locals, `orig_node_list` and `node_list`
  (code +0x74 and +0x135). It stores 0x0113F0B8 when it destroys them (code +0x386).

The pairs agree: each constructor's VectorClass table is the one its owner's
destructor stores. No retail call reaches 0x0093D780, 0x0096E000, 0x009745E0 or
0x00981490. The one call to 0x0094E490 comes from the raw-byte initializer above.
So no REL32 resolution depends on the old names.

`DynamicVectorClass<FontCharsBuffer *>` is 0x0113CDDC, and its VectorClass table is
0x0113CDC4. `FontCharsClass::FontCharsClass` (0x00940610) stores 0x0113CDDC at
member +0x10, and `~FontCharsClass` (0x00940010) stores 0x0113CDC4 there. That
member is `BufferList`, its only vector. The constructor at 0x00907440 stores
0x0113A0FC/0x0113A3A0, and the VectorClass constructor at 0x009062F0 stores
0x0113A0FC. So their `<FontCharsBuffer *>` and `<Render2DClass *>` names are
retired. This file does not decide the other names those two bodies carry.
