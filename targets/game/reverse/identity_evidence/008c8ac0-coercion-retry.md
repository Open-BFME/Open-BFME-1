# Equality coercion retry at RVA 0x008C8AC0

## Result and reopening condition

This is a measured partial reconstruction, not an exact recovery. The preferred bank retains `_FunctionAptActionEquals2`, `AptActionInterpreter`, and the descriptive names from the existing bank. The decoded action table establishes an opcode handler and its ABI, but no independent source establishes the original class or method spelling. No ledger row or pin was changed. Reopen this attempt when a specific source expression or independently established declaration explains the remaining dispatch, parser cleanup, or scheduling differences. Another unchanged register or x87 experiment is not justified.

The tested revision is `5513809748bbbee6187793df26267db7aadcf953`. The compiler is MSVC 7.1 with the bank's `/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc` flags. The actual model is `gpt-6.1-sol`. Every complete trial source, raw probe output, decoded body, and raw gate output is preserved under `build/target-008c8ac0/`. The compiler dependency cache reports unreadable or changed include search directories; the probes compile rather than relying on that cache.

## New hypothesis and evidence

The earlier bank used an incompatible number-coercion declaration, omitted the two inlined string-validation lifetimes, and constructed booleans by writing vtable addresses. The current landed neighbors and callees supply canonical coercion symbols, string ownership, and a native boolean constructor. The hypothesis was that restoring those types, ownership operations, and inlining would reduce the saved body's measured distance. Failure to improve the original bank after those changes would refute it. The measurements below support an improvement, while the strict byte gate still rejects the reconstruction.

The donor files inspected were `AddValues008C8500.cpp`, `LessThan008C8840.cpp`, `Rva008C9B70StackString.cpp`, `AptValueToInteger.cpp`, `AptValue_toNumber.cpp`, `Rva008985C0ValueString.cpp`, `AptString/EAStringCFind.cpp`, `AptBooleanCreate.cpp`, and `Rva008995E0AptBoolValueCtor.cpp` under `game/Libraries/Source/EA/Apt/`. The saved `0x008c4a30.cpp` validator was inspected against its decoded helper, rather than accepted as type evidence. No Apt source twin was found in the reference tree. `name_oracle.py` supplied no witnessed layout for the bank's owner names.

## Boundary and ABI

The target has a complete decoded extent of 2954 bytes. Its only return is at `+0xB89`; the next byte is outside the extent. Three `INT3` bytes precede the entry and six follow the return. Every outgoing direct conditional branch or direct jump in the target stays inside the extent and lands on a decoded instruction boundary. The raw instructions and boundary assertions are in `code-008c8ac0.txt` and `acceptance-evidence.log`.

The sole aligned target pointer is at VA `0x012D5B8C` in the action table based at `0x012D5A68`. The complete caller at RVA `0x008CCED0`, size 375, loads an unsigned byte opcode, pushes a context pointer and then its interpreter receiver, calls `[eax*4+0x012D5A68]`, and removes eight stack bytes. Slot `0x49` selects the target. The target reads its first pointer at entry stack offset four, has no hidden return storage or receiver adjustment, leaves its second pointer unused, and uses a bare return. This supports two four-byte pointer arguments with caller cleanup. See `table-callers.log`, `abi-008cced0.txt`, and `checked-caller-008cced0-375.log`. The table is identity evidence for dispatch position, not proof of the bank's original spelling.

The interpreter has a count at offset zero and an element pointer at offset eight. A value reads flags at offset four. Type is the low six bits, undefined is the inverse of bit 15, and pooling uses bit 30. The actual coercion helpers read a signed integer, a single precision float, or a one-byte boolean at offset eight. String tag one reads a string block pointer at offset eight; tag 42 follows the pointer at offset `0x20` before the same payload read. The string block fields actually used are a two-byte reference count at zero, a two-byte length at two, and text at eight. The unused capacity field keeps the bank's declaration and is not independently established by this target.

`toInteger` returns a four-byte integer through EAX with ECX as its receiver. `toNumber` returns a float through ST0 with ECX as its receiver. `getName` receives ECX and one output pointer and returns with four bytes of cleanup. `Find` receives ECX, a character promoted to a stack slot, and a four-byte start index, then cleans eight bytes. The CRT calls reach PE imports for `MSVCR71.dll` `isdigit` and `strtol`. Their caller cleanup is four and twelve bytes respectively. Every `isdigit` character argument is sign-extended. The `strtol` argument order is text, end-pointer storage, and radix 16; its numeric return is ignored.

The complete executable portions and trailing tables of all three coercion helpers were checked separately. Their executable sizes are 136, 108, and 1740 bytes; complete extents including tables are 198, 170, and 1866 bytes. Every table destination is an instruction boundary inside its executable portion and every tag selects a valid table index. `checked_callees.py` rejects the three combined code-and-data extents while decoding table bytes. Those failures are preserved. It passes the executable extents and the target. See `checked-helpers-summary.log` and `acceptance-evidence.log`.

Virtual slots zero and four resolve to the complete retain and release helpers at RVAs `0x008991B0` and `0x008991E0` in both installed vtables. They use ECX, no stack arguments, and no receiver adjustment. Release has two bare returns and a tail jump through slot eight. The boolean slot-eight helper at `0x008D2A90` links the object into the free list using its payload at offset eight. The base slot-eight helper at `0x00891810` forwards to three virtual slots, including one four-byte argument. The full set of deeper virtual identities remains unresolved; the bank does not claim a complete class declaration. See `abi-evidence.log` and the corresponding `abi-*.txt` files.

## Ownership and exception cleanup

The handler uses four unwind states. States zero and one clean a four-byte string handle at frame offset `-0x1C` and return to state minus one. State two cleans offset `-0x14`; state three cleans offset `-0x18` before entering state two. All four cleanup funclets tail-call the complete 22-byte string destructor at RVA `0x00891B80`. It decrements the two-byte reference count and frees a zero-count block through the string pool's second function slot. The bank gives the two validator strings and the final pair comparison separate lexical lifetimes. See `eh-retail.log` and `code-00891b80.txt`. These verified cleanup targets do not establish equality of the candidate's compiler-generated exception metadata.

The boolean constructor reads flags at offset four and stores a one-byte payload at eight. The root registry reads capacity at zero, count at four, and a pointer array at eight. A full registry clears bit 30; otherwise it stores the object pointer and increments count. Both reused and newly allocated objects follow these operations. The allocation requests twelve bytes, but the payload width is established by the constructor's byte store, not by allocation size. The bank calls the existing allocation global and references recorded DIR32 symbols for the free list, registry, empty string, and string pool. It introduces no numeric image-address literals in game source and no new pins.

## Measurements

The following table is generated from the retained raw probe outputs. Byte quality uses `tools/finish_measure.py`: one minus `(differing bytes + twice the size error) / retail size`, floored at zero. Normalized instruction similarity is a separate diagnostic and is not byte equality. Source and log paths are relative to `build/target-008c8ac0/`.

| Complete source | Raw probe | Bytes | Differing bytes | First offset | Byte quality | Instruction similarity |
| --- | --- | ---: | ---: | --- | ---: | ---: |
| `trial-00-original.cpp` | `probe-trial-00-original.log` | 3467 | 2579 | `+0x17` | 0.0000 | 0.343 |
| `trial-01-corrected.cpp` | `probe-01-corrected.log` | 2992 | 2566 | `+0x17` | 0.1056 | 0.487 |
| `trial-02-dispatch.cpp` | `probe-02-dispatch.log` | 2938 | 2558 | `+0x17` | 0.1232 | 0.746 |
| `trial-03-native-lifetimes.cpp` | `probe-trial-03-native-lifetimes.log` | 2929 | 2504 | `+0x24` | 0.1354 | 0.719 |
| `trial-04-local-order.cpp` | `probe-trial-04-local-order.log` | 2930 | 2506 | `+0x24` | 0.1354 | 0.721 |
| `trial-05-inline-equality.cpp` | `probe-trial-05-inline-equality.log` | 2961 | 2575 | `+0x24` | 0.1236 | 0.773 |
| `trial-06-native-boolean.cpp` | `probe-trial-06-native-boolean.log` | Compile failed | | | | |
| `trial-06b-native-boolean.cpp` | `probe-trial-06b-native-boolean.log` | 2969 | 2428 | `+0x24` | 0.1679 | 0.789 |
| `trial-07-bitfield.cpp` | `probe-trial-07-bitfield.log` | 2969 | 2428 | `+0x24` | 0.1679 | 0.789 |
| `trial-08-comparison-branches.cpp` | `probe-trial-08-comparison-branches.log` | 3142 | 2610 | `+0x1A` | 0.0000 | 0.775 |
| `trial-09-numeric-first.cpp` | `probe-trial-09-numeric-first.log` | 3117 | 2613 | `+0x17` | 0.0051 | 0.630 |
| `trial-10-native-subtraction.cpp` | `probe-trial-10-native-subtraction.log` | 2973 | 2419 | `+0x24` | 0.1682 | 0.792 |
| `trial-11-handle-reference.cpp` | `probe-trial-11-handle-reference.log` | 3006 | 2419 | `+0x24` | 0.1459 | 0.794 |
| `trial-12-float-threshold.cpp` | `probe-trial-12-float-threshold.log` | 2973 | 2419 | `+0x24` | 0.1682 | 0.793 |
| `trial-13-integer-difference.cpp` | `probe-trial-13-integer-difference.log` | 2974 | 2421 | `+0x24` | 0.1669 | 0.794 |
| `trial-14-retained-storage.cpp` | `probe-trial-14-retained-storage.log` | 2973 | 2419 | `+0x24` | 0.1682 | 0.793 |
| `trial-15-preserved-names.cpp` | `probe-trial-15-preserved-names.log` | 2973 | 2419 | `+0x24` | 0.1682 | 0.793 |

The exception generator tested 17 trials without an improving result. The finite bool, copy, store, loop, branch, and constant generator produced two trials without an improvement. Their complete sources and raw probe outputs are preserved in `build/shape_search/1e58c09b6dca4845a8fd9649d57ae882/` and `build/shape_search/494462bd8a9f49948b2c697c35eaac6b/`. The raw search receipts are `eh-search.log` and `family-search.log`.

Rejected hypotheses include caching operand tags, exchanging declaration order, exposing string equality through a reference, direct comparison-result branches, placing the numeric arm first, and introducing an explicit integer-difference result. The semantic corrections, native construction, and subtraction before joining numeric arms are retained. Restoring unused string storage and retaining the old free-list type name leave the final measured bytes unchanged.

## Checks and remaining blockers

The final source has the retail frame size, but the first differing instruction is at `+0x24`: retail pushes ESI before loading the top operand into ESI; the candidate loads the top operand into EBX before pushing ESI. Dispatch ordering, parser cleanup scheduling, and later branch lengths also differ. Relocation operands no longer align at many offsets, so the byte gate's offset-derived REL32 diagnostics do not identify missing callees. The complete scoped byte gate fails on the candidate, and no exact recovery or landed bytes are claimed.

`check_csv.py`, `pin_consistency.py --check`, and `class_gate.py` pass. The file-pair `name_regression.regressions` API passes after preserving the free-list type name. The documented CLI invocation with two filenames is unsupported by this revision, which requires Git revisions; its raw failure is preserved in `names-check-trial12.log`. `find_declared_unmatched.py --fail` rejects both the scratch source and the bank because no matched ledger row owns this partial reconstruction. No whitelist or baseline was changed. Final logs are `check_csv-final.log`, `pin-consistency.log`, `class-check-bank.log`, `names-pair-bank.log`, and `declared-bank.log`. The final bank reproduces the measurement in `probe-0x008c8ac0.log`; its scoped byte gate fails in `scoped-gate-bank.log`, while the retail baseline check passes. A full gate was not required because no matched game source, shared header, shim, or pin changed.
