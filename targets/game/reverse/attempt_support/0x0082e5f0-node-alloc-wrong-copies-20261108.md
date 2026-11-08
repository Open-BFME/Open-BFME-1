# __node_alloc<true,0> wrong COMDAT copies in vendor-STLport facet TUs (wave 41, 2026-11-08)

Census 88d830c8e9. Queue rows: _M_deallocate (57 KB) and _M_allocate (31 KB) wrong_selected.

## Landed (a2f578cc7)
- Cause of wrong_selected: link order is by lowest retail RVA of an object's rows
  (link_census.link_order). MoneyPutCharString.cpp carried the 0x002D8760 basic_string
  _M_range_initialize row, so it sorted ahead of both providers and its vendor-body copies of
  _M_allocate/_M_deallocate/_S_refill/_Node_Alloc_Lock dtor/_M_do_lock were the kept ones.
  Rehomed that row to PersistentStorageThread.cpp (same retail-hash copy, previous home).
  Verified with link_census.link_order on the current ledger: no wrong copy precedes either provider.
- Providers made self-contained: unlock call names row 0x0082AD50 (?m@Gen_0082ad50, via
  NodeAllocMutex : Gen_0082ad50) and _S_free_list is defined.
- LINKED preview is UNKNOWN until the next census (changed names are stale in the index;
  --refresh needs a warm worktree).

## Still open: ~30 vendor-STLport TUs emit wrong copies (they are `losers`, not selection)
Money*/Num*/stlport_* facet TUs (list: comdat verdict wrong for _M_deallocate in the census index)
each compile STLport's own _alloc.c body (/O2 shape, calls _STLP_mutex_spin::_M_do_lock) where
retail kept the 85-byte /Og- body. Each such TU also emits wrong string dtor / lock dtor /
_M_allocate copies. Findings, all measured on MoneyPutCharString.cpp (do_put 0x008379C0):
- /D_STLP_LINK_TIME_INSTANTIATION removes the copy but also other vendor bodies; 3 small TUs
  (StdioIstreambufDestructor, X4TimeFacets, STLportFormatFloatFixed) still byte-verify, the rest
  fail to compile or change the frame. Not committed (those files carry many other losers).
- `extern template` of the member, or a body-less explicit specialization: copy is not emitted
  but do_put frame becomes 0x110 (retail 0xc8). `__declspec(nothrow)` on a body-less
  specialization restores 0xc8; remaining diff is register allocation (retail keeps the three
  use_facet results in esi/ebx/edi, ours spills the second), i.e. the compiler used the visible
  vendor callee's clobber set. A visible non-vendor body (Og- retail shape, noinline) gives
  edi/esi swap. Any visible callee changes $L funclet numbering (eh_state_pins --fix fixes pins).
- Conclusion: a per-TU no-emit lever that keeps the vendor callee's clobber/nothrow profile is
  needed; none found. Payoff is small per file (most carry 6-70 other losers).
