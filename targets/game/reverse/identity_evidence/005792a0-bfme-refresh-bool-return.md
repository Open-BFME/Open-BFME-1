# 0x005792A0 BfmeAptScreenSkirmish::_bfme_refresh returns bool

Correction: `?_bfme_refresh@BfmeAptScreenSkirmish@@QAEXXZ` ->
`?_bfme_refresh@BfmeAptScreenSkirmish@@QAE_NXZ` (same class and method name,
return type void -> bool).

Retail evidence (BFME 1 1.03 image):

- Body 0x005792A0..0x005792DA (58 B): calls SkirmishScreenState's predicate
  through ILT 0x0003029C on this+0x25C, `test al,al; jne`, and on false
  returns with AL still holding the predicate's result. On true it resets the
  +0x3AC animation (vtable slot 3) and calls ILT 0x0003AB48 -> 0x0052AAD0,
  the matched `?apply@SkirmishScreenState@@QAE_NPAXH@Z` (bool), then returns
  without touching EAX. Both exits therefore return a bool in AL.
- Caller: the BfmeAptScreenSkirmish vtable slot 5 body at 0x0057EDB0 calls
  ILT 0x00040E7B (-> 0x005792A0) at +0x12F and tests AL (`test al,al; je`)
  before switching to mode 7. A void callee would leave that test undefined.
- The previous source reached the same bytes only by calling both callees
  through union-punned member pointers; the rewrite uses the ledger names
  (`shouldRefresh` pin at ILT 0x0003029C, matched `apply` at 0x0052AAD0) and
  byte-matches 58/58 with relocations.

Class and method name are unchanged; only the return type is corrected.
