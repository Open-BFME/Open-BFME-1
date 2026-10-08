# Preserved reconstruction for 0x0021CA50

Collection remains blocked by the STLport pause and a missing base-call route. The complete body is banked as `targets/game/reverse/attempts/0x0021ca50.cpp` under `?method@Rva0021CA50@@QAEXXZ`. This is a matching compiler shape, not a verified landing. No function ledger row, symbol pin, shared header or tooling was changed.

## Evidence and experiment

The tested revision is `b096c2e2309e884791b01ccd253b8b73b4a1c0c3` plus the saved reconstruction. The two previous records were inspected through `session_target.py`; neither had a saved body. Their identity and STL shape blockers were rechecked against the landed ContestableContain, constructor, recount, tree insertion and GameLogic lookup sources. The new hypothesis was that the complete canonical hash lookup, visible in the translation unit, and native `XferException` would recover the inlining, exception representation and aligned frame. Failure to improve the measured body would refute that hypothesis.

The shared `game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h` is included, with the independently complete inline body used by `SelectionAll00595230.cpp`. The outlined-lookup control is retained as `trial03-outlined-lookup.cpp`. The bank also uses `_BFME_RETAIL_TREE_INSERT_LAYOUT`, copied from the landed unsigned tree donor. Without it, the emitted typed `insert_unique` has the wrong internal insertion signature; the target caller itself still matches. Both variants and their raw outputs remain under `build/contestable-0021ca50/`.

| Raw probe log | Emitted/retail bytes | Result |
|---|---:|---|
| `probe01-raw.log` | 626/626 | Exact outside relocations |
| `probe02-raw.log` | 626/626 | Exact outside relocations |
| `probe03.log` | 531/626 | 211 reported differences; first +0x66; omitted bytes also fail |
| `probe04.log` | 626/626 | Exact outside relocations |
| `probe04-typed-insert.log` | 145/145 | Exact outside relocations |
| `probe04-typed-node.log` | 176/176 | Exact outside relocations |
| `probe04-typed-copy.log` | 29/29 | Exact outside relocations |
| `probe-inline-helper.log` | 82/82 | Exact outside relocations |

## Boundary, type and ABI checks

The complete target reaches its only normal return at +0x271, ending at 0x0021CCC2. Every conditional branch stays within that extent; there is no tail jump. The decoded target and `checked_callees.py` output are retained as `retail_decode.log` and `callees.log`. `abi_check.log` also records the independent boundary guard result and eligibility from `tools/eligibility.py`.

The constructor at 0x0021BEE0 installs the primary vtable 0x010AB3C0. Slot 1 routes through 0x0002D0E2 to this target without a receiver adjustment. `vtable.log` and `abi_check.log` retain that evidence. The bank keeps an address-derived method and owner because a ContestableContain method spelling and complete inherited declaration were not established. The Zero Hour tree has no ContestableContain source. Its OpenContain load-postprocess twin supports the operation sequence, not the target's identity.

The actual tree route is 0x0000EE2B -> 0x0021BE20 -> 0x0004499F -> 0x0021B600 -> 0x0002292B -> 0x0021AAA0. The complete copy helper at 0x0021AAA0 reads and writes words at value offsets 0, 4 and 8. The target constructs those as resolved Object pointer, optional resolved Object pointer, and a word whose low byte is zero. The complete recount body at 0x0021B960 reads the second pointer at node+0x14 and increments the byte at node+0x18. The key is the pointer at node+0x10 and uses unsigned ordering. Thus the value is a pointer key with an eight-byte payload containing a target pointer, byte count and padding. Neither allocation size nor the old opaque STL pin was used alone to infer this type. All copy bytes, including padding, are covered by the complete helper probe.

The pending list contains one object-ID word; the record list contains two, read at node+8 and node+12. The actual target resolves both through the canonical GameLogic hash lookup. List construction in the target writes one Object pointer, and both clear loops have trivial payload destruction. The inline lookup was decoded through every return path, uses buckets at GameLogic+0xB4/+0xB8 and returns the pointer at hash-node+8. Its full emitted body was separately probed.

The base call follows `0x00031DC2 -> 0x00248C40 -> 0x00038C12 -> 0x0021DCA0 -> 0x0002ECC1 -> 0x00225960` and is niladic thiscall with unchanged ECX. The insertion call passes a hidden eight-byte iterator/bool result and a value-reference pointer, with callee cleanup of eight bytes. Its node helper has hidden iterator storage, two node pointers, the value reference and the fourth insertion argument, with ret 0x14. The real virtual call at slot 0x5C routes through 0x00004160 to 0x002264F0. The complete callee reads the low byte of its second argument and ends with ret 0x0C; its unused third stack slot is passed zero. The canonical existing declaration is `addOrRemoveObjFromWorld(Object *, bool, bool)`. The bank models the Object vptr and the observed fields without asserting unrecovered field names.

Retail ThrowInfo 0x011DFE5C reaches the `.?AVXferException@@` type descriptor, an eight-byte catchable value, copy ILT 0x0004A26E and destructor ILT 0x00040804. The complete constructor at 0x009D6220 stores text at +0 and tag at +4. The complete copy constructor reaches 0x009D6290, which copies owned text and tag; the destructor deletes the text array. The decoded import at 0x009F6D00 is `_CxxThrowException`. The native throw uses that metadata. The target is not a constructor and has no registered unwind frame or local object cleanup. The constructor used as owner evidence is not being reconstructed in this run.

Complete helper decodes are in `helpers_decode.log`, `abi_check.log` and `remaining_helpers.log`. Matching `checked-*.log` files cover lookup, tree insertion, node insertion, value copy, recount, exception construction/copy/attachment/destruction, base operation, virtual operation, allocation and deallocation. Allocation is cdecl with one size word; deallocation is cdecl with pointer and size words. The imported variadic formatter call was checked separately from the direct call inventory.

## Remaining blockers and collection

The strict scoped gate is `scoped_gate_final.log`, produced by the repository verifier with an in-memory candidate row and unchanged ledgers. Its differing bytes are +0x10, +0x11, +0x12, +0x218, +0x219, +0x21A, +0x21B. These lie entirely in two REL32 operands. The base-call resolver lacks the actual ILT at +0x10; the insertion relocation at +0x218 has no typed pin. The required typed symbol is `?insert_unique@?$_Rb_tree@PAVObject@@U?$pair@QAVObject@@UContestableMapEntry@@@_STL@@U?$_Select1st@U?$pair@QAVObject@@UContestableMapEntry@@@_STL@@@3@U?$less@PAVObject@@@3@V?$allocator@U?$pair@QAVObject@@UContestableMapEntry@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@QAVObject@@UContestableMapEntry@@@_STL@@U?$_Nonconst_traits@U?$pair@QAVObject@@UContestableMapEntry@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@QAVObject@@UContestableMapEntry@@@2@@Z`, whose actual call target is ILT 0x0000EE2B to body 0x0021BE20. The STLport pause forbids adding or correcting this `_STL` identity now. The existing unsigned opaque tree claim also requires identity review before a typed claim is introduced.

String, constant and DIR32 address checks pass in the same scoped-gate log. `check_csv_final.log`, `pin_consistency.log` and `class_gate_final.log` preserve the other checks. The declared-definition guard reports the expected unclaimed target in `declared.log`; it cannot certify an active source without a landed row. No full gate was required because this run only adds a bank and attempt evidence. No callee recovery is counted as progress.

Reopen after the STLport header migration permits reviewing the typed tree identity and the independently decoded base route. First reproduce the bank and its helper probes, then resolve both calls through the normal pin and ledger procedures and run the strict gate. No further register spelling experiment is justified by this matching target shape.
