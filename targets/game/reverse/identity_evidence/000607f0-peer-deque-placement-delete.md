# Scalar placement delete at RVA 000607F0

The unchanged native `deque<PeerResponse>::_M_push_back_aux_v` at
RVA 00648920 copies a PeerResponse into a deque slot with the actual C++
placement-new expression in `_Construct`. Its retail prologue pushes handler
C42142; that handler loads FuncInfo E31BF0. Unwind map E31BE0 state 1
(predecessor 0) selects action C4212B.

The complete 23-byte action loads two saved placement pointers from
EBP-340 and EBP-344, pushes them, calls ILT 0002AAA9, discards eight stack
bytes, and returns at C42141. The next instruction at C42142 begins the
handler. ILT 0002AAA9 branches to 000607F0. This call belongs to the failed
placement construction, independently of the empty callee bytes.

The corresponding compiler action is `$L891` in this parent's EH section.
Its REL32 symbol is `??3@YAXPAX0@Z`, standard scalar placement
`operator delete(void*, void*)`. The toolchain's `Vc7/include/new` supplies
the empty inline definition. The same unchanged TU emits its one-byte
COMDAT; retail is RET at 607F0 and INT3 at 607F1 through 607FF.
Ghidra and independent PE reads agree. A single canonical body pin binds
this independently identified callee; no synthetic wrapper or new source is
needed. The anonymous generated provider remains unchanged. Its replacement
would invalidate 394 existing callers' object evidence; the normal gate was
still waiting for the host build lock, so that broader replacement was
withdrawn before any commit. This scoped repair claims no provider conversion.

This independently corroborates the LivingWorldPlayerArmy placement-new
proof recorded in b1 commit 953785e601. The new pin and native action must
pass pin consistency and their normal commit gates.
