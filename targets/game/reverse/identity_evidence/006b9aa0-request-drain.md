# Request drain at 0x006B9AA0

The recovery is `?process@Rva006B9AA0@@QAEXXZ` in `game/GameEngine/Source/Common/Rva006B9AA0RequestDrain.cpp`. The owner and method retain an address identity. No export, named matched caller or Zero Hour twin establishes a semantic method name. The Zero Hour `MilesAudioManager::processRequestList` was read directly; its list-only processing differs from this BFME body and does not justify that name.

The retry replaces the prior Relationship-map interpretation with native STLport pointer iterators and reloads the node payload after the dispatcher. The existing `RequestFlags006A6B40.cpp`, `MilesAudioManagerConstructor.cpp` and `Rva006B9320RequestDispatch.cpp` provide the container spellings, offsets and canonical dispatcher declaration. Those sources were read directly. The first complete experiment and the final source both match the retail extent under `probe.py`; `add_match.py` also verifies their resolved callees.

## Boundary and receiver

The complete target is `[0x006B9AA0, 0x006B9C27)`. Its last instruction is `ret` at 0x006B9C26. All direct branches stay within that range and target decoded instruction starts. There is no indirect call, tail jump, exception frame or cleanup funclet in the target. It uses ECX as the receiver and consumes no stack arguments. In the complete caller at 0x006B9C90, the aligned call at 0x006B9E20 reaches ILT 0x00019DAD, which jumps to the target. ECX receives the unchanged receiver and the caller does not consume a result. The generated niladic free-function ledger name therefore does not describe the decoded ABI.

The list sentinel is at receiver+0x4C. List nodes contain next at +0, previous at +4 and a request pointer at +8. The target loads that pointer, dispatches it, unlinks through both neighbouring pointers and releases the node with size 12. The set is at receiver+0x50. Its nodes contain next at +0 and a request pointer at +4. Its table has bucket begin/end at +4/+8 and count at +0x10. These offsets agree with the independently decoded begin and erase bodies.

## Pointer value and hashing evidence

The complete matched insertion caller at 0x006ABDA0 computes receiver+0x50 at +0x183, passes a reference to the saved request and hidden result storage, and calls ILT 0x00005A42 at +0x19B. That thunk jumps to 0x006A0730. This independently ties the construction helper to the same receiver member used by the target; address proximity and donor naming are not the link. The caller ends with ret 4 and its full checked inventory is retained as checked_insert_caller.txt.

The complete insertion helper at 0x006A0730 has two return paths, both `ret 8`, and no outgoing branch. At +0x6C it reloads the reference argument, at +0x70 it reads one pointer through that argument, and at +0x72 it stores that pointer to node+4. This is the entire value construction sequence. No second value field is copied. Node+0 is initialized and then assigned the chain head separately. The pointer value follows from these reads and writes, not from the eight-byte allocation or a donor name.

That helper hashes a non-null request through its dword at +8 and uses zero for null. Its comparison checks the two non-null requests' dwords at +8, otherwise compares the pointers. The target's iterator increment and the complete erase helper independently perform the same null-aware hash read. The source uses the established `AudioRequest006A6B40` prefix view and STLport template spellings for the emitted begin, increment and erase operations. It does not recover an insertion equality policy or the request's complete object definition.

The saved request pointer used for dispatch and deletion remains distinct from the iterator's live payload. After dispatch, increment reloads node+4 and the bucket fields, as retail does. The postfix increment snapshot supplies the old node and table to erase before destroying the saved request.

## Callee ABI and ownership

| Retail route | Decoded ABI and evidence |
|---|---|
| 0x0000BD75 to 0x006B9320 | ECX is the unchanged owner; arguments are request pointer, byte output pointer and integer 1. Every return path pops 12 bytes. The canonical declaration from `Rva006B9320RequestDispatch.cpp` is used directly through an address-preserving receiver cast. |
| 0x0000FE93 to 0x006A0400 | ECX is receiver+0x50. One hidden output pointer receives node at +0 and table at +4. Both returns pop four bytes; EAX returns the hidden output address. |
| 0x00023A38 to 0x006A0810 | ECX is receiver+0x50 and the sole stack word points to the iterator snapshot. Every return pops four bytes. Erase reads the node, unlinks it, frees it and decrements table+0x10. |
| 0x0001AE2E to 0x006912A0 | ECX is the saved request. The non-virtual destructor consumes no arguments and ends with plain `ret`. The existing matched `BfmeHostESG` declaration is an ABI view, not a new request identity. |
| 0x00881EB0 | Global operator delete reads one pointer from the caller's stack and ends with plain `ret`; the caller performs cleanup. The complete body matches the existing memory-manager declaration. |
| 0x0082E5F0 | The node deallocator reads pointer and size from the stack and ends with plain `ret`; the caller performs cleanup. Its complete body agrees with the existing STLport static declaration. |

The complete request destructor first destroys the handle at +0x0C through ILT 0x000298E8 to 0x00691130, then releases the pointer at +0x04 through its pointee's ref-counted secondary base at +0x70. The decrement addresses secondary-base+4; a non-positive count invokes virtual slot zero with integer flag 1. The target calls this already recovered destructor rather than reconstructing its members or substituting a deletion callback. The complete handle destructor at 0x00691130 has a null return and an outgoing tail jump to ILT 0x000442B0, which reaches the complete 0x006BA220 release body. That body keeps the handle receiver unchanged, decrements its count under its owner mutex and returns without popping arguments. Both extents and the thunk route are retained in the raw evidence. The target is not a constructor, so constructor unwind-state reconstruction is inapplicable.

The dispatcher contains 348 bytes of instructions followed by an eight-entry jump table at 0x006B947C. Linear decoding of its full 380-byte ledger extent fails on that data, as retained in `build/rva006b9aa0/checked_dispatch.txt`. The complete code extent separately passes `checked_callees.py`; all eight decoded table destinations are instruction boundaries within that code, and all return paths pop 12 bytes. The table is retained verbatim and parsed in `boundary_report.json`. This resolves the inventory failure without treating table bytes as instructions.

## Reproduction and refutation

Trial source, exact retail bytes, complete decoded bodies, jump-table bytes, branch/return inventory and unedited tool outputs are retained under `build/rva006b9aa0/`. `trial01.cpp` is the first measured source; `probe01.txt` and `probe_final.txt` retain both exact measurements. `add_match.txt` retains the relocation-aware landing gate. Required source and ledger checks have separate raw logs in that folder.

Refute the pointer-value claim by finding another value field read or written in the complete construction sequence. Refute the ABI by finding a complete caller that supplies a different receiver or stack contract, or a reachable return with different cleanup. Refute the extent by finding a reachable transfer outside the stated code range. A semantic name requires independent named-call, export, vtable or twin evidence. Equality of masked bytes alone is insufficient for any of these claims.
