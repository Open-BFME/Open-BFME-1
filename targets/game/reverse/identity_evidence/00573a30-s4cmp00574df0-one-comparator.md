# S4Cmp00573A30 and S4Cmp00574DF0 are one comparator type

Both are address-derived placeholder names for the comparator of the
twelve-byte (int key, int, int) S4SortElem12 heap/sort family, and both TUs
define it identically (`left.m_bfmeKey < right.m_bfmeKey`, one pointer of
state). Retail has no identical-COMDAT folding, so one template body serves
exactly one instantiation, and retail's ILT ties the two names to the same
bodies (thunk targets read from the image):

- ILT 0x00035BC0 (pinned `sort_heap<S4SortElem12 *, S4Cmp00574DF0>`) jumps to
  0x00573A30, ledgered as `sort_heap<S4SortElem12 *, S4Cmp00573A30>`.
- ILT 0x0002E2C6 (pinned `__make_heap<..., S4Cmp00574DF0, ...>`) jumps to
  0x005726F0 (gen005726F0, S4MakeHeapElem12Sort.cpp, which used S4Cmp00573A30).
- ILT 0x0003DF00 jumps to 0x00571B70, matched as
  `__adjust_heap<S4SortElem12 *, int, S4SortElem12, S4Cmp00574DF0>`
  (stlport_adjust_heap_s4sortelem12.cpp), but was pinned under the
  S4Cmp00573A30 spelling for S4MakeHeapElem12Sort.cpp's call.

So S4Cmp00573A30 is respelled S4Cmp00574DF0 in its two TUs, the two matched
rows (sort_heap 0x00573A30, __pop_heap 0x005725F0) and the ILT pin. Bytes are
unchanged.
