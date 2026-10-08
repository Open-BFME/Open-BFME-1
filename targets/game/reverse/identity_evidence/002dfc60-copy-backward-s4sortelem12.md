# 0x002DFC60 is STLport's __copy_backward over S4SortElem12 (address-scoped name)

The row was ledgered as a three-argument free function
`?bfmeCopyBackVOT@@YAPAUBfmeElemVOT@@PBU1@0PAU1@@Z` (BfmeConv1545.cpp), an
invented name no matched caller uses; its caller spelled the ILT with an
address-scoped placeholder `_STL::BfmeCopyBackward002DFC60` that nothing defined.

- Body (92 bytes): STLport's random-access `__copy_backward`: n = last - first,
  then n times `*--result = *--last` memberwise (dword +0, StringBase<char>::set
  0x00887C90 on +4, byte +8), returning result. Twin of 0x0052D740
  (0052d740-copy-backward-s4sortelem12.md) over the other 12-byte layout.
- Caller: matched `__linear_insert<S4SortElem12 *, S4SortElem12,
  S4Cmp002E1690>` 0x002E0FE0 calls ILT 0x00002289 -> 0x002DFC60 with five
  pushed arguments (first, last, last + 1, tag, (int *)0): STLport's
  `__copy_backward(first, last, result, random_access_iterator_tag, Distance *)`.
- Element: (dword, string, byte) is the S4SortElem12 layout
  (00532740-s4sortelem12-layout-split.md); BfmeElemVOT was the same layout.

Bytes unchanged. The STL template spelling over the placeholder element
S4SortElem12 is CONTRADICTED by ilt_oracle (the real element type name is
unknown), so the definer takes the address-scoped spelling its caller and the
ILT 0x00002289 pin already use: `_STL::BfmeCopyBackward002DFC60` with the
STLport five-argument signature.
