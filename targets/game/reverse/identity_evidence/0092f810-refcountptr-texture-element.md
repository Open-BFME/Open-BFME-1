# `0x0092F810` is `TextureVectorBaseCtorShim::operator=`, not `VectorClass<VProxyClass>::operator=`

`targets/game/reverse/identity_evidence/` proof for the `--correct-identity`
retirement of `??4?$VectorClass@VProxyClass@@@@QAEAAV0@ABV0@@Z` at 0x0092F810
(249 bytes). The name arrived with the 2026-08-11 Open-BFME5 `__emit` lift
`game/Libraries/Source/WWVegas/WWLib/VectorClassIntAssignmentThunk.cpp`, which
scored as a dump; the real body is clean C++ in
`game/Libraries/Source/WWVegas/WW3D2/TextureVectorBaseCtorShimAssignment.cpp`.

## 1. The element is four bytes, so the row's own name cannot be right

* `+0031` `mov esi, [ebp+8]` loads the source `VectorMax`, `+0041`
  `lea ecx, [esi*4 + 4]` and `+0049 call ??_U@YAPAXI@Z` allocate exactly
  `4 * VectorMax + 4`, `+0068` `lea ebx, [eax+4]` makes the data start four
  bytes past the block, and `+0070` `call ??_L@YGXPAXIHP6EX0@Z1@Z` receives
  `(dest, 4, VectorMax, ctor, dtor)` at 0x009F6EE4.
* The repo has already byte-proved what a `VectorClass<ProxyClass>` element
  costs, in the class's own home. The matched
  `?Resize@?$VectorClass@VProxyClass@@UAE_NHPBVProxyClass@@@Z` (0x00934630) and
  `?Clear@?$VectorClass@VProxyClass@@UAEXXZ` (0x00934780) both pass **0x74** as
  the element size to the same array-destroy helper, and
  `VectorClassProxyClearThunk.cpp` says why: `MixFileCreator::FileInfoStruct`
  is 0x10 bytes, so 0x74 is `ProxyClass` -- `StringClass Name`, `Matrix3D
  Transform` and the BFME tail the header there measures as `0x74 - 0x34`.
  A `VectorClass<ProxyClass>::operator=` allocates `0x74 * VectorMax`. This
  body allocates `4 * VectorMax + 4`. The allocation size alone refutes the
  name, with no naming evidence in the way.

## 2. The element is `RefCountPtr<TextureClass>`

* The per-element copy step at `+00b2`..`+00ca` is upstream
  `WWLib/ref_ptr.h` `RefCountPtr<T>::operator=` verbatim: `mov eax,[esi]`,
  `inc word ptr [eax+4]` (Add_Ref on the source referent), `mov ecx,[ebp]`,
  `call ?Release_Ref@TextureClass@@QAEXXZ` on the destination referent, then
  the store.
* `?Release_Ref@TextureClass@@QAEXXZ` is the matched body 0x009EB7A0, which
  tests `dword ptr [ecx+4], 0xffff` and does `dec word ptr [ecx+4]`: BFME's
  `TextureClass` carries a WORD reference count at +4, which is the
  `inc word` the loop emits inlined.
* The array-new helper's element **destructor** operand is
  `?j_00030652@@YAXXZ`, pinned in `symbols.csv` as
  `??1?$RefCountPtr@VTextureClass@@@@QAE@XZ`
  ("RefCountPtr<TextureClass> destructor passed to the CRT vector dtor
  iterator by the DX8TextureCategoryClass dtor 0x00946540"). The same helper is
  entered by the landed `?Clear` body 0x00930460 with that identical operand.
  A ctor/dtor pair in one `_L` argument list is one class.

## 3. The dispatch target is `Clear`, so the shim's four virtuals are the vector's

* The vftable at 0x0113C5FC (`??_7TextureVectorBaseCtorShim@@6B@`) holds six
  entries: slot 0 a deleting destructor (0x00930D50), slot 1
  `??8?$VectorClass@PAVPrototypeClass@@` (0x0092FC80), slot 2
  `?Resize@?$VectorClass@UFileInfoStruct@MixFileCreator@@` (0x009302C0),
  slot 3 `?bfmeClearUHA@BfmeThingUHA@@QAEXXZ` (0x00930460, the
  `if (Vector && IsAllocated) delete[] Vector` body), slot 4
  `?ID@?$VectorClass@PAVPrototypeClass@@UAEHABQAVPrototypeClass@@@Z`, slot 5 the
  by-pointer `ID`. The call at `+002a` is `call dword ptr [eax+0xc]`, so the
  body is dispatching `Clear` -- the same slot order the matched
  234-byte `VectorClass<HLodClass::ModelNodeClass>::operator=` sibling uses.

## 4. The name a UNIQUE matched caller gives it

`??0MaterialInfoClass@@QAE@ABV0@@Z` (0x00930E00, 352 bytes) is a matched,
non-ICF-folded body from `game/Libraries/Source/WWVegas/WW3D2/MaterialInfoCopyCtor.cpp`.
At `+0132` it forms `src + 0x20` (the `Textures` member), `+0135` pushes it,
`+0136` loads the destination base, `+0138` calls this body, and `+013d`/`+0143`
then copy `+0x10` and `+0x14` (ActiveCount, GrowthStep) -- the
`DynamicVectorClass` assignment, which is what tells us this body is the
`VectorClass`-level one. That caller names the symbol
`??4TextureVectorBaseCtorShim@@QAEAAV0@ABV0@@Z`, the name
`symbols.csv` already pins at 0x0092F810, and the same shim family already has
its constructor landed as `?construct@TextureVectorBaseCtorShim@@QAEXHH@Z`
(0x0092FBA0, `MaterialCollectorClass_ctor_Thunk.cpp`).

## 5. Why `caller-decided-2.md`'s kept name is not evidence

`caller-decided-2.md` kept the `VProxyClass` spelling from "1 C++ call site".
That site is 0x00930180, whose row was `dup_930180` -- a 33-byte body that does
nothing but call the base `operator=` and copy the two trailing ints, so every
`DynamicVectorClass<T>::operator=` instantiation compiles to it and the Zero
Hour link folded them. The template argument in that row's name came from the
fold, so the name it hands the callee says nothing about `T`. That row is
repointed in the same commit, to the identity its own call target proves; see
`00930180-texture-vector-assign.md`.

The other caller-decided entry the tool could not see is the shim name, which
is not a `functions.csv` row name at this address and so never entered its
tally.

## 6. The resolver consequence, and why nothing is pinned

Retiring this row removes the last ledger mapping of
`??4?$VectorClass@VProxyClass@@@@QAEAAV0@ABV0@@Z` to 0x0092F810, which the
0x00930180 row needed for its one relocation. That row is repointed here
instead, so nothing resolves that refuted name at this address any more. The
remaining user of the name is the 0x00907320 fold group, whose call encodes
0x00905C80 and is served by the `pinharvest` candidate at that address. No
`symbols.csv` row is added, so the one-name-one-body check sees no change: the
name keeps exactly the one pin it had, and the false mapping that would have
become a second pin (`size-disagreement: 0x00905C80=217; 0x0092F810=249`) is
never written.

## What the body is, in one line

`VectorClass<RefCountPtr<TextureClass> >::operator=` for the `Textures` member
of `MaterialInfoClass`: clear, allocate a new `RefCountPtr<TextureClass>`
array, then copy element-wise with upstream's `RefCountPtr` assignment.
