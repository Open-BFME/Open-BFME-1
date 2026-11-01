# 0x0113C614 vftable: VertexMaterial identity settled, six slot renames remain

Follow-up to material-vector-table-identity-20261029-round2.md (link_queue #30,
`??_7?$DynamicVectorClass@PAVVertexMaterialClass@@@@6B@`). Inspected BFME 1
d98e3d8b15 on 2026-11-01. No source edit: the two queued consumer TUs are
already correct, and the remaining work is six slot-row identity corrections
plus a provider fix, which is identity-lane work, not a link-lane edit.

## Table identity: settled as DynamicVectorClass<VertexMaterialClass*>

- game/Libraries/Source/WWVegas/WW3D2/matinfo.h is the upstream Zero Hour
  header (EA's own): MaterialInfoClass holds
  `DynamicVectorClass<VertexMaterialClass *> VertexMaterials`.
- The matched clean-C++ MaterialInfoClass ctor stores table 0x0113C614 into
  that member (byte-match proves the address; the header proves the type).
- The BFME 2 donor's MaterialInfoClassCtor.cpp
  (open-bfme-2 beed8a16790a6812231ac7b05e3e6893e4cb5d1b, same path under
  Code/) references the identical
  `??_7?$DynamicVectorClass@PAVVertexMaterialClass@@@@6B@` spelling.
- Upstream GeneralsMD WWLib/Vector.H declares DynamicVectorClass's six
  virtuals in order: dtor, operator==, Resize, Clear, ID(ptr), ID(ref).
  All six retail slots hold exactly those method kinds in that order
  (table below). The competing `PAVPrototypeClass` dir32 spelling at the
  same VA is referenced by no game/ TU.

## Current state (verified this session)

- matinfo.cpp and MeshLoadContextLifecycle.cpp still emit digest
  b91e8deb677b, retail-truth verdict wrong (unchanged since 2026-10-29).
- MaterialInfoClassCtor.cpp / MaterialInfoCopyCtor.cpp only REFERENCE the
  table (undefined externs); they emit no copy. No consumer-side repair
  exists: consumers cannot change COMDAT selection, and their spelling is
  the proven-correct one.

## The six slots (RVA = VA - 0x400000)

| slot | address    | current row label              | true identity (derived) |
|------|------------|--------------------------------|--------------------------|
| 0    | 0x009305B0 | ??_G VectorClass\<ShaderClass> | ??_G DynamicVectorClass\<VertexMaterialClass*> (scalar dtor; see note 1) |
| 1    | 0x0092F6B0 | == VectorClass\<RenderObjClass*> | == VectorClass\<VertexMaterialClass*> (base, not overridden; note 2) |
| 2    | 0x00930290 | Resize DynamicVector\<PrototypeLoaderClass*> | Resize DynamicVector\<VertexMaterialClass*> |
| 3    | 0x00930240 | Clear DynamicVector\<PrototypeClass*> | Clear DynamicVector\<VertexMaterialClass*> |
| 4    | 0x00930210 | ID DynamicVector\<PrototypeLoaderClass*> | ID VectorClass\<VertexMaterialClass*> (base ID(ptr); note 2) |
| 5    | 0x00930270 | ID VectorClass\<Render2DClass*> (gen-alias dup) | ID DynamicVector\<VertexMaterialClass*> (ID(ref); note 3) |

Note 1: slot 0's 30-byte body is scalar-shaped (call dtor; test flag;
conditional delete; ret 4; no loop) with `CC` padding after, no adjacent
??_E. MSVC dtor-slot flavor confirmed empirically in-tree: InactiveBody
vftable 0x010A8B74 slot 0 holds ILT 0x0003648A -> 0x00213E10, the ??_G
row. So slot 0 takes the ??_G spelling (still worth one more vftable
spot-check at rename time).

Note 2: DynamicVector does not override operator==, and its ID(ptr)
override is an inline forward (`return VectorClass<T>::ID(ptr)`), which
emits no body: slots 1 and 4 point at BASE-class VectorClass methods.
Their true manglings use `?$VectorClass@PAVVertexMaterialClass@@`, not
`?$DynamicVectorClass@...`.

Note 3: ID flavor order needs one read at rename time. The ZH header
orders ID(ptr) then ID(ref), but the current labels put a ref-flavored
(ABQ) ID at slot 4 and a ptr-flavored (PBQ) ID at slot 5. Either the
labels' flavors are wrong too, or BFME 1's vector.h orders them
differently. Read the 38-byte (0x930210) and 25-byte (0x930270) bodies:
ID(ptr) compares the pointer itself, ID(ref) dereferences first.

## Way forward

1. Six add_match --correct-identity corrections (one per slot) with
   per-row identity evidence: vtable-slot proof above + byte comparison
   against the same-kind bodies of other instantiations. Retail links
   without ICF, so each address holds exactly one instantiation's body
   and the vftable proves which one.
2. Then give one TU the correct six-virtual class view so its emitted
   vftable COMDAT judges retail's (or remove the wrong emitters if the
   corrected rows make them redundant), and re-check providers and the
   two consumer TUs together.
3. This link_queue entry clears once the selected copy is retail's; no
   consumer edit is part of it.

Donor review: donor MaterialInfo ctor/matinfo sources confirm the table
spelling only; the donor was not used for slot bodies. BFME 1 native
evidence (header, ctor store, slot bytes, InactiveBody vftable rule)
carries the identities above.
