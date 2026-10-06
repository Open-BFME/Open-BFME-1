# Font insertion family: stopped native experiment

This preserves a failed family implementation for another matching attempt.
It changes no production source, function ledger, pin, baseline, or link metric.
The complete candidate is the `source` field in the immutable archive
`targets/game/reverse/attempt_history/0x00940b40/96b7450aa447c56aaabd8cf8ed3dae63de1bb5628721848cd114dfc2efe919da.json`.
The adjacent `00940b40-font-family-bank.json` binds its source hash, compiled
object hash, complete principal bytes, call targets, and emitted sections.

The normal `re_log.py record --stash` workflow measured the candidate and
created both that archive and an active stash. The unchanged `check_csv` guard
then required deleting the active stash because 00940B40 already has an exact
generated C++ owner. The immutable archive remains; no guard was changed.
The verdict's `stash=` token records that original temporary path and its
`alternative=` token identifies the retained source archive. This evidence
does not make the address available to the automatic finish queue.

The measured base is recorded in that JSON. The bank uses the normal original
VC7.1 compiler path and existing approved GUID runtime. It is a diagnostic
experiment, not a production gate receipt. Model provenance is the generic
`Codex` label; this session does not expose a verified model variant.

## Result and exact stopping point

| Retail RVA | Complete extent | Result | Resolved call relocations |
| --- | ---: | --- | ---: |
| 0093FD80 | 178 | Exact | 5 |
| 0093FE40 | 148 | Exact | 2 |
| 009401F0 | 601 | Exact | 16 |
| 00940790 | 31 | Exact | 1 |
| 00940B40 | 121 | 106 bytes equal; 15 differ | 1 |

All 25 principal call relocations resolve to the addresses actually encoded
by retail. Five proposed function addresses are supplied as explicit diagnostic
bindings; this does not register those names as real physical providers.
Existing allocator, copy, rebalance, increment, and decrement routes use the
normal symbol map. None of these comparisons masks bytes or unresolved calls.
The 601-byte body includes all four calls to 0093FE40, nine to 0093FD80,
two increments at 0082B870, and one decrement at 0082B8E0.

The only 121-byte differences are offsets 73 through 87 inclusive. Retail
stores the hint node, forms and pushes the result buffer, then initializes
the temporary mapped pointer to zero. This candidate initializes that zero
first, then stores the hint and forms/pushes the result buffer. The stack
displacement changes with the push. The call operand at +89, target 009401F0,
and every byte after this scheduling region match. Both complete extents are
121 bytes. The score is therefore 106/121, not the higher instruction-shape
similarity printed by `probe.py`.

Three bounded value-construction forms were measured: aggregate initialization,
a two-argument value constructor, and a temporary value passed at the insertion
expression. All retain those 15 entry-body differences. The constructor forms
also make the 178-byte insertion outline its creation helper, yielding a
159-byte body with two unresolved new-helper calls. They are rejected; the bank
keeps the aggregate form and all four exact dependent bodies. No stronger
existing bank for this address was present or replaced.

The hinted 601-byte insertion initially differed in six bytes because a key
was returned by value. Returning a const reference to the genuine key member,
and using the canonical unsigned-short comparison functor, recovers its complete
retail instruction order. No forced inlining, volatile access, inline assembly,
alias, or new pin was used.

## What the representation establishes

The new address-qualified value contains an unsigned-short key at zero and a
pointer at four; its size is eight. The new node genuinely derives from the
canonical 16-byte `_STL::_Rb_tree_node_base` and contains that value, making
a 24-byte node. Static size checks and the exact allocation/access instructions
confirm those target-ABI sizes and offsets. The node is not a C++03 POD because
of inheritance; its default constructor and destructor remain trivial.

At both 0093FD80 allocation sites, placement construction begins the complete
node, base, and value lifetimes before the landed 0093DD20 byte-storage helper
copies the key and pointer representations. The arguments address the whole
value subobjects. There is no reinterpretation of a fake const STL pair, typed
write to an object whose lifetime has not begun, or pointer-reference cast in
the rebalance root argument. The allocator route remains the existing private
`__node_alloc<true,0>::_M_allocate` at 0082E540 through its canonical public API.
Its pre-existing ledger/physical-owner debt is not fixed by this experiment.

This is a conditional, modular lifetime argument: entry must supply the genuine
shared tree and nodes, and the eight-byte source value must contain a valid
target-ABI key and pointer representation. Null, record pointers, and retail's
stored -1 sentinel are the observed values; the sentinel must never be
dereferenced, used in pointer arithmetic, or deleted. Keys are not mutated after
insertion. Whole-program font and existing external-helper ODR correctness is
not established.

## Unfinished acceptance work

The compiler emits 16 code definitions across 34 total COFF sections. Five are
the principal bodies above; the other 11 inline/helper copies are inventoried
with bytes, hashes, and relocations, but are not accepted as new physical
owners. The principal bodies emit no EH handler/data references. This does not
prove the remaining family cleanup metadata.

The owning font constructor and destructor, shared finder/getter, tree erase,
sentinel release, destructor forwarder, and their unwind actions were not
implemented or compiled in this attempt. The proposed complete family remains
six changed/new source TUs, with 21 TUs and 2,331 existing rows requiring final
verification. The complete header, caller, metadata, donor-row, duplicate-owner,
and production gates were not run because the principal 121-byte body failed.
ConnectionManager and every other production source remain unchanged.

00940790 is independently bounded by the preceding proven destructor and
INT3 padding, its own complete RET 12 and following padding, and the next
proven start at 009407B0. Its sole call is 009407A4 to 009401F0. An existing
31-byte object copy corroborates every byte after that relocation is resolved.
It has no observed incoming E8/E9 or absolute VA/RVA references and no carved
or Ghidra entry. The normal new-row `add_match` route can accept independent
boundary evidence after implementation verification; no carved start was
invented, and the unrelated donor name at 00668A30 must not be reused.

Do not activate the exact dependent bodies piecemeal. Finish the 121-byte entry
and genuine owning lifecycle together, reconcile every emitted consequence,
and then run the unchanged complete family gates. This bank earns zero new
production conversion bytes and zero linked bytes.
