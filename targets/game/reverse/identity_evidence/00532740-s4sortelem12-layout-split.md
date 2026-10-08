# S4SortElem12 names two record types: split off S4SortElem12_00532740

`S4SortElem12` is a placeholder (no reference source names it). The ledger
used it for two different 12-byte record types, so the inline special
members `??0/??1/??4S4SortElem12` had two different bodies under one name and
the link kept only one (hard_rows.md #875, followups.md T6).

## Two layouts, each proven by byte-verified bodies

- (dword, string, byte): the 0x002E1690 / 0x002E0CD0 family. Rows
  0x002E00E0 swap, 0x002E0250 push_heap, 0x002E07A0 adjust_heap,
  0x002E0BC0 pop_heap, 0x002E0CD0 make_heap, 0x002E0FE0 linear_insert,
  0x002E1170 insertion_sort, 0x002E0730, 0x002E01A0, 0x002E1B60. These
  keep the name `S4SortElem12`; nothing about them changes.
- (byte, string, dword): the 0x00532740 family. Every body below is matched
  with the byte at +0, the StringBase<char> at +4 and the dword at +8 (for
  example 0x00531D80 loads the record byte with `mov cl,[esi-0Ch]` and the
  dword with `mov eax,[esi+8]` relative to the element, and the comparator
  inlined in 0x0052FC70 / 0x0052F280 tests the +0 byte before comparing the
  +4 string without case).

## The 0x00532740 family is one type (call graph)

- __final_insertion_sort<..., S4Cmp00532740> 0x00532740 calls
  __insertion_sort 0x00532080 and __unguarded_insertion_sort_aux 0x00530050.
- __introsort_loop 0x00533520 calls __median 0x0052FB30,
  __unguarded_partition 0x0052FC70 and __partial_sort 0x00532F40.
- __unguarded_partition 0x0052FC70 calls the swap 0x0052E370
  (`bfmeSwapElem12`); __partial_sort 0x00532F40 calls the pop_heap
  0x00531A40 (`bfmePopHeap00531A40`), which calls __adjust_heap 0x00530350,
  which calls __push_heap 0x0052F600.
- __insertion_sort 0x00532080 reaches __linear_insert 0x00531860, which
  calls __unguarded_linear_insert 0x0052F280 and __copy_backward (ILT
  0x0003EF95).
- gen00531C50 (make_heap) calls __adjust_heap 0x00530350; gen00531D80
  (pop_heap_aux) calls 0x00531A40.

All of these instantiate one element type, distinct from the (dword, string,
byte) record. It gets the address-derived name `S4SortElem12_00532740`,
after the family's __final_insertion_sort at retail 0x00532740 (the anchor
whose comparator S4Cmp00532740 already carries that address).

## What changes

Only the type's spelling in the mangled names of these rows and of the ILT
pins that route to them (symbols.csv: __copy_backward, __insertion_sort,
__linear_insert, __median, __partial_sort, __push_heap,
__unguarded_insertion_sort_aux, __unguarded_linear_insert,
__unguarded_partition, bfmePopHeap00531A40). Code bytes are unchanged: every
touched TU re-verifies with ./build.sh. The S4PopHeapAuxElem12.cpp and
S4MakeHeapElem12.cpp views now use the same S4Name view as the WWLib sort
layers (89d88dcd24) so the type's inline special members are one COMDAT
body. The orphaned non-ledger second copy of gen005726F0 in
S4MakeHeapElem12.cpp is removed; its ledger row lives in
S4MakeHeapElem12Sort.cpp.
