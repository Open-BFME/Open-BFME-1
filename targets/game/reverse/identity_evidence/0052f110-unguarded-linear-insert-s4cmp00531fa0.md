# 0x0052F110 is _STL::__unguarded_linear_insert<S4SortElem12 *, S4SortElem12, S4Cmp00531FA0>

Was `?bfmeUnguardedLinearInsertElem12@@YAXPAUS4SortElem12@@U1@@Z`, an invented
two-argument name no caller uses.

- Callers: the matched `__linear_insert<..., S4Cmp00531FA0>` 0x0052FE90 calls
  ILT 0x0001649B -> 0x0052F110 at 0x0052FEF7 followed by `add esp,0x14`: five
  dwords (last, the 12-byte val, the 4-byte comparator), STLport's
  `__unguarded_linear_insert(last, val, comp)`. The matched
  `__unguarded_insertion_sort_aux<..., S4Cmp00531FA0>` 0x0052FF20 calls the same
  ILT. symbols.csv already pins the STL spelling at ILT 0x0001649B.
- Body (109 bytes): STLport's loop `next = last - 1; while (comp(val, *next))
  { *last = *next; last = next--; } *last = val;` with the comparator inlined.
  The trailing comparator argument is never read, so the old two-argument
  spelling produced the same bytes.

Bytes unchanged; the name moves to the callers' spelling.
