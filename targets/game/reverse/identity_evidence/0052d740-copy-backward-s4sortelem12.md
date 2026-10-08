# 0x0052D740 is _STL::__copy_backward<S4SortElem12_00532740 *, ..., int>

The row was ledgered as a three-argument free function
`?bfmeCopyBackVOS@@YAPAUBfmeElemVOS@@PBU1@0PAU1@@Z` (BfmeConv1543.cpp), an
invented name no matched caller uses.

- Body (92 bytes): STLport's random-access `__copy_backward`: n = last - first,
  then n times `*--result = *--last` memberwise (byte +0, StringBase<char>::set
  0x00887C90 on +4, dword +8), returning result.
- Caller: matched `__linear_insert<S4SortElem12_00532740 *, ...,
  S4Cmp00532740>` 0x00531860 calls ILT 0x0003EF95 -> 0x0052D740 with five
  pushed arguments (first, last, last + 1, tag, (int *)0): STLport's
  `__copy_backward(first, last, result, random_access_iterator_tag, Distance *)`.
  symbols.csv already pins that STL spelling at the ILT.
- Element: (byte, string, dword) is the S4SortElem12_00532740 layout
  (00532740-s4sortelem12-layout-split.md); BfmeElemVOS was the same layout.

The body's bytes are unchanged; only the name moves to the caller's spelling.
