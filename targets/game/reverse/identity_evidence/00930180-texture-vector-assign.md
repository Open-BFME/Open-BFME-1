# `0x00930180` is `TextureVector::operator=`, not `DynamicVectorClass<ProxyClass>::operator=`

Proof for the `--correct-identity` retirement of the `dup_930180` row at
0x00930180 (33 bytes), which the same commit as
`0092f810-refcountptr-texture-element.md` repoints to
`??4TextureVector@@QAEAAV0@ABV0@@Z` from
`game/Libraries/Source/WWVegas/WW3D2/MaterialInfoCopyCtor.cpp`.

## The body

```
+0000 push esi / push edi / mov edi,[esp+0xc] / push edi
+0009 call 0x0092F810            <- the VectorClass-level assignment
+000e mov eax,[edi+0x10] / mov [esi+0x10],eax
+0014 mov ecx,[edi+0x14] / pop edi / mov [esi+0x14],ecx
+001b mov eax,esi / pop esi / ret 4
```

Base assignment, then `ActiveCount` (+0x10) and `GrowthStep` (+0x14) copied:
the `DynamicVectorClass` assignment, spelled out of line. That is exactly
`MaterialInfoCopyCtor.cpp`'s

```cpp
TextureVector &operator=(const TextureVector &other) {
    TextureVectorBaseCtorShim::operator=(other);
    ActiveCount = other.ActiveCount;
    GrowthStep = other.GrowthStep;
    return *this;
}
```

which compiles to 33/33 bytes, one relocation, modulo the relocation slot.

## Why the ProxyClass spelling cannot be it

* The call target is 0x0092F810, whose element is FOUR bytes (its own
  allocation is `4 * VectorMax + 4`, and its element copy is a 16-bit
  reference-count bump on a `TextureClass*`). `VectorClass<ProxyClass>`'
  element is 0x74 bytes -- proved by the matched
  `?Resize@?$VectorClass@VProxyClass@@` (0x00934630) and
  `?Clear@?$VectorClass@VProxyClass@@` (0x00934780), which pass 0x74 as the
  element size. A `DynamicVectorClass<ProxyClass>::operator=` calls THAT body,
  as the landed `?dup_00936d70@@YAXXZ` (0x00936D70, retail's
  `DynamicVectorClass<ProxyClass>::Resize`) does with
  `?Resize@?$VectorClass@VProxyClass@@` at 0x00934630. It cannot call
  0x0092F810.
* 0x00930180 has no caller at all (`tools/callers_of.py 930180` reports none).
  That is what MSVC leaves behind for an inline member whose every use was
  inlined: the `MaterialInfoClass` copy constructor at 0x00930E00 contains
  this 33-byte pattern inline (its own `call 0x0092F810` at +0x138 followed by
  the same two copies), and the out-of-line COMDAT survives unreferenced.
  `collect.cpp`'s `DynamicVectorClass<ProxyClass>::operator=` is the same 33
  bytes for every `T`, which is why its row byte-matched this address and why
  the `dup_` name was the honest label; what the row could not be is the
  ProxyClass instantiation, because the call says otherwise.

## Consequence

`collect.cpp` keeps every other row it had, including the nine names on the
0x00907320 fold (`??4?$DynamicVectorClass@VProxyClass@@` among them), whose
relocation continues to resolve through the `pinharvest` candidate at
0x00905C80. What leaves the ledger is the false mapping of
`??4?$VectorClass@VProxyClass@@@@QAEAAV0@ABV0@@Z` to 0x0092F810, which is
what makes the 0x0092F810 identity correction possible without adding a
second address to that name.
