# Manager submission at RVA 0x00895D30

The retained reconstruction is a partial, not an exact recovery. Its main body has the retail extent and instruction structure, but differs in register operands. The scoped byte gate fails. The ledger and symbol pins are unchanged.

## Identity, boundary and ABI

The tested revision is ce5aa863aebd4d175719f4491bf6e7305b0e897d. The existing `bfmeSubmitEVA` pin agrees with the matched `bfmeSubmitNameEVA` caller in `game/GameEngine/Source/Common/BfmeConv1992.cpp`. That caller's complete decoded body passes the address of a four-byte pooled string as the only stack argument, loads the manager global into ECX and directly calls this target. The complete target returns with `ret 4`, has no outgoing branch or tail jump, and uses no hidden return storage. The independently decoded owner destructor at RVA 0x00896060 passes its own receiver and the string member at its head payload plus four, which agrees with this ABI. The recursive call preserves the manager receiver and passes another string address. These observations support the existing address-derived manager identity and retained method name. A caller using a different receiver adjustment or argument representation would refute that interpretation.

The complete target and each helper used for layout or ABI evidence were decoded from the current retail baseline. Their raw disassemblies and checked call inventories are retained under `build/eva-00895d30/`. The target's endpoint is its complete `ret 4` epilogue. The lookup has two complete `ret 8` exits; its caller pushes the string pointer followed by hidden return storage, and the callee writes one pointer there and leaves that storage address in EAX. Its result constructor retains the payload's dword reference count. This is a value return, not a void output-parameter lookup.

The full lookup and object destructor establish the payload's dword reference count at zero, pooled string pointer at four, kind at eight, argument at twelve, object pointer at sixteen and buffer at twenty. The destructor's complete dispatch and sized free establish the ownership behavior, including the object callback receiver adjustment of eight. The string constructor reads a terminated byte string and writes a pointer to a block with word reference count, length, capacity and flags followed by characters at eight. The string destructor decrements the word count and calls the second allocator-table slot on zero. The callback and free calls use cdecl stack arguments and caller cleanup, including the sized payload free.

For kinds three, four and five, the target reads a signed count at object plus 0x28 and a pointer at plus 0x2C. It indexes records with a stride of sixteen and uses only each record's initial string pointer. The predicate at RVA 0x00895510 independently repeats those accesses and compares strings against the candidate's member at four. The remaining record bytes and the object's preceding fields stay opaque in the bank. No STL container or payload identity is inferred from this stride.

## New evidence and measured experiments

There was no saved source for this target. Earlier records described an EH frame and refcount cleanup failure without a reusable body. The current exact lookup source in `game/GameEngine/Source/Common/Rva00893030ManagerFind.cpp` supplies a complete value-return ABI and proven receiver, node and string layouts. The new hypothesis was that making this actual lookup visible with an inline, noinline definition would let the compiler recover the native temporary lifetimes and storage reuse. A remaining oversized frame or disagreement with the retail unwind states would refute it.

The initial complete trial used opaque dependency records, two scoped handles and the matched destructor declarations. Mechanical EH choices tested exception specifications and EH flags before manual shape changes. Ordinary inline decrement and cached cleanup pointers were then tested, followed by the complete visible lookup. The latter removed the additional frame storage and string cleanup state. Its copied lookup independently passes the strict scoped byte gate at its existing retail address; it is not a new recovery. The copy is inline to avoid a second strong definition of an already owned symbol.

The finite non-EH generator offered only a lookup-local frame-array alternative. It left the target result unchanged. Restoring the lookup donor's string member wrapper also left the target result unchanged. These are the two unchanged experiments at the final register residue; no further register iteration was performed. Complete trial sources, generated choices, search manifests and unedited probe outputs remain in `build/eva-00895d30/` and the task's recorded `build/shape_search/` directories. The exact measurements and remaining offsets are in the table below, generated from the raw outputs rather than estimated.

## Exception cleanup and reopening condition

The retail unwind map has three states with predecessors minus one, zero and one. Their actions pass locals at EBP minus 0x18, minus 0x14 and minus 0x20. The first two jump through the decoded ILT to RVA 0x00784A70, which calls the complete decrement helper at RVA 0x00894D90 and drops the payload through RVA 0x00895320 on zero. The last action jumps to the complete pooled-string destructor at RVA 0x00891B80. The candidate's emitted map has the same predecessors and local offsets. Its string cleanup emits the same destructor instructions, with the established allocator global. Its handle cleanup directly inlines decrement and destruction instead of calling the retail helper pair, so that helper code and identity are not an exact reproduction. The emitted object and every cleanup instruction are retained in `build/eva-00895d30/object-05.log`.

Reopen with independently supported native accessors or an inlining configuration that changes the recorded register residue and also provides the retail handle cleanup targets. An allocation size, a fresh compiler flag guess or an unchanged spelling is insufficient. `class_gate.py` and `pin_consistency.py --check` pass. `find_declared_unmatched.py --fail` refuses the scratch candidate because it has no matched source row, as expected for this partial. No baseline, shared header, tooling or symbol pin was changed, and a full gate is not required for this bank.


## Measurements

| Trial | Emitted bytes | Non-relocation differences | First difference |
|---|---:|---:|---|
| 00 | 502 | 354 | +0x17 |
| 02 | 503 | 325 | +0x21 |
| 03 | 496 | 354 | +0x17 |
| 04 | 462 | 18 | +0x80 |
| 05 | 462 | 18 | +0x80 |

The retained trial is `trial-05.cpp`. Its measured score is 0.961038961038961. The strict gate differences are at +0x80, +0x83, +0x94, +0x98, +0xA4, +0xA7, +0xA9, +0xAC, +0xC7, +0xCE, +0xF6, +0xF9, +0x160, +0x164, +0x167, +0x169, +0x16E, +0x170.
