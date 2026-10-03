# C25560 mapped counted-pointer cleanup

The matched WindowManager::bindShown caller at RVA 46DA70 uses the
Rva0046C000Mapped hash-map specialization at WindowManager+08. It stores a
single counted callback pointer, with the reference count at pointee+4 and
the deleting virtual call at slot zero. The caller's complete 251-byte
native body was independently reverified; the existing opaque type is kept.

Parent 46D0C0 pushes handler C25592, which selects FuncInfo E157E0 and
unwind map E157D0. State 0 (predecessor -1) names action C25560 through
the pointer at E157D4, independently found in Ghidra. Bit 1 of EBP-18
guards the mapped temporary at EBP+4. RET C25578 bounds 25 bytes before
the separate state-1 action. Its tail ILT 19029 reaches body 45F170.

Ghidra and the retail PE agree on all 26 bytes of 45F170: load the counted
pointer, test null, decrement its count, and call deleting slot zero if
the count is nonpositive. RET 45F189 is followed by INT3 padding.
Caching the pointer and expressing decrement as an assignment makes the
native Rva0046C000Mapped destructor reproduce those bytes exactly, with
no relocation sites. Both direct byte comparison and build.py's strict
compile_function/verified_patch_eligible path pass independently of the
cleanup. One body pin binds that destructor to 45F170; the existing opaque
body row is retained, with no second ledger identity or additional coverage.

This TU-local repair follows the independently reviewed sibling technique
in b5 commit 1eb928b41e, but concerns Rva0046C000Mapped, not Rva0046AF20Mapped.
Integration must preserve both destructor edits and all distinct cleanup
rows, then reselect emitted labels if necessary.
