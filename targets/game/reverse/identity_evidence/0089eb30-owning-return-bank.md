# Owning string return at RVA 0089EB30: improved bank, not a match

The complete retail body spans 0089EB30..0089EC4D (285 bytes), followed by
three INT3 bytes. Its plain returns occur at +52, +86 and +11C. The matched
BfmeApplyEVF caller at 008C4FA0 supplies hidden return storage, a prefix and
a string reference; EAX returns that storage. The current legacy pin uses
BfmeStrVKI, but that spelling is not authority to duplicate a destructor.

## Native lifetime evidence

The parent pushes handler VA 01057AE9. That handler loads FuncInfo VA
01246EA8: magic 19930520, maxState 1, unwind map VA 01246EA0. State 0 has
predecessor -1 and action RVA C57AD0, exactly 25 bytes:

    8b45f083e0010f840c0000008365f0fe8b4d04e998a0c3ffc3

The action tests/clears construction bit 1 at EBP-10, loads the hidden return
pointer at EBP+4 and jumps to 00891B80. The established identity at that
address is EAStringC::~EAStringC; see
[its independent return-cleanup evidence](00891b80-eastring-return-cleanup.md).
This is a real returned object's lifetime, which the old explicit-output-
pointer bank omitted. Focused Ghidra output corroborates the control flow;
the PE bytes and EH graph establish the contract.

The existing caller also has three owned temporary lifetimes. Its handler
C59BC8 loads FuncInfo E48B94 (three states). Actions C59BB0, C59BB8 and
C59BC0 each have eight bytes, using LEA EBP+4, EBP+4 and EBP+C respectively,
then tail-branching to the same 00891B80 destructor. A future integration
must preserve the caller's complete 541-byte body and all three cleanup
contracts. A TU-local ownership correction may retain its borrowed
BfmeStrVKI parameter. Do not invent inheritance, a second destructor pin,
or a broad string-family rename to avoid this obligation.

## Measured experiment

Native value return restores the missing EH prologue. Making the existing
93-byte reserve constructor's real noinline body visible removes escaped-
object reloads; the bank therefore carries the existing constructor and its
287-byte concatenation sibling as context. Both siblings pass strict
byte/call checks in the scratch object. This is not new coverage.

Bounded forms measured: standalone value return 300 bytes; direct buffer
288; visible constructor 280; memcpy-return pointer 281. Ordinary and inline
buffer/accessor variations did not close the gap. The best body remains
280 versus 285 bytes, with 76 non-relocation differences starting at +C0.
It lacks the native tail-pointer spill/reload and differs in the final
free-callback load schedule. Normalized instruction shape 0.969 is not a
byte match. The standard bank scorer measured 0.6982, improving the previous
0.08 bank; no game source, ledger row, pin or progress metric was changed.

Stop repeating the recorded pointer/accessor/register forms. A later attempt
needs a new independently justified source-shape lever, then complete parent,
callee, data-reference and EH verification before production promotion.

## Name-checker false pairing

The bank still declares EAStringC::m_pData and StringDataC::m_uRefCount.
Neither field was renamed to m_unused. The latter belongs to the distinct
BfmeStringPool3AF0 callback table, whose free callback is at +4; that view is
copied from the existing matched EAStringCReserveCtor.cpp. Its unused first
pointer word is not an owning string's data pointer or the string header's
16-bit reference count. The constructor uses the separate BfmeAllocVKJ
allocation table. Snapshot-specific corrections record only the checker's
cross-owner m_pData/m_uRefCount-to-m_unused pairings. They grant no reusable
exemption and do not establish a new semantic name.
