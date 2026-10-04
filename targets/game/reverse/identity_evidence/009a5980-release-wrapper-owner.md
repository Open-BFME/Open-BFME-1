# Existing release-wrapper owner at RVA 009A5980

The complete 166-byte body at 009A4A60 makes five direct calls, at
009A4A73, 009A4A86, 009A4A99, 009A4AAC and 009A4ABF. Each target is
009A5980. Each call receives one pushed pointer and is followed by
caller cleanup of four bytes; no return value is consumed.

009A5980 is a distinct five-byte E9 wrapper to 009A58E0, followed by
eleven INT3 bytes. Calling the underlying 009A58E0 body directly would
change the retail targets and is not the proposed repair.

The existing BfmeReleaseSetBZB.cpp owns Rva009A5980 with its established
void(void*) declaration. Its independently matched 182-byte caller at
009A5B80 calls that same wrapper six times with the same cdecl ABI.
The underlying target reads its argument from ESP+4 and either delegates
to the allocator manager's deallocation slot or tail-calls the CRT free
IAT entry. The calling convention follows retail data flow, not a pin's
spelling or the fact that a relocation can be patched.

The accepted census contains exactly one retail-true provider for the
wrapper, and its selected-MAP and ledger owners agree. The whole wrapper
TU is linked. The alternate bfmeFreeOneJT spelling has no implementation,
only unresolved caller references. Rebinding the five calls and declaration
in BfmeConv2079.cpp preserves that existing owner, rather than adding an
alias, another definition or another claimed identity. The old spelling's
release role remains described here; no original vendor name is asserted.

The unchanged Bucket placement allocator is also a unique linked provider.
The complete caller, wrapper and allocator TUs pass all five matched rows
(345 + 187 + 14 bytes). In the same accepted census snapshot 82dc61ee38,
the joint source-scoped link preview changes from 201 to 546 LINKED bytes:
the caller contributes +345, and both provider totals remain unchanged.
This is scoped preview evidence, not a new full-image census.

BfmeConv2080.cpp is deliberately unchanged: its old release reference has
six additional unresolved/selected-provider blockers. The underlying free
provider in BfmeConv930.cpp has unrelated blocked siblings; this repair
does not claim to fix them or to make the whole program linkable.
