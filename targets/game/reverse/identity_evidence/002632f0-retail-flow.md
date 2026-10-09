# 0x002632F0: retail control flow and banked reconstruction

## Result and reopening condition

The preferred attempt is a partial, not a source recovery. Its complete eight-case body emits 1000 bytes for the 988-byte retail extent, with 338 differing non-relocation bytes and 21 displaced relocation sites. The measured quality is 0.6336, compared with 0.3927 for the previous bank. The first differing byte is +0x2B in an early-exit displacement. The first substantive scheduling difference is +0x9C, where retail loads the AI global between two coordinate stores and the draft completes more of the copy first. The waypoint distance loop and upgrade loop also retain different local offsets, argument preparation and register lifetimes. Reopening needs evidence or a source expression that reproduces the coordinate-copy lifetime and these load/call schedules. Repeating the rejected raw-copy, field-copy, subtraction, receiver-staging or EH spellings does not address that condition.

The tested revision is `dbfea2ff0cfbd7707f89cdc5cea96c69a4446798`. The actual model is `gpt-6.1-sol`. Investigation began at 2026-10-09 03:16:22 UTC; this note was prepared at 2026-10-09 03:55:08 UTC, after 38.77 clock-measured minutes. No function ledger row or symbol pin was changed. No body was landed.

## Retry hypothesis and evidence that can refute it

The retry tested whether proven neighboring layouts and a compiler-generated three-word coordinate copy could repair the old switch-copy scheduling blocker, while fully decoding the previously inferred pathfinder helper and vector payload. The landed module-data constructor and destructor confirm the mode at +0x220 and string-vector storage at +0x224. The complete terrain return helpers produce a 12-byte result through caller-provided storage, return that storage in EAX and pop two argument words. They read and write three coordinate fields at +0, +4 and +8. The original explicit raw assignment and the canonical native-coordinate declarations inhibit the source-level copy shape used by the best trial. A repeatable compiler result no closer than the original bank would refute the copy hypothesis; it was supported by the improvement from 592 differences to 338, but the remaining schedules prevent an exact claim.

The newer matched `PathfinderIterateCircular1.cpp` body supplies independently inspectable traversal code reached by 0x003DAD60. Its presence addresses the earlier inferred-callee evidence gap, not the remaining target scheduling. The native constructor/copy-helper trial used complete decoded helpers rather than a donor label, and its 972-byte result with 666 differences refutes that declaration shape for this target. The explicit controlling-player getter restores retail's call-before-argument-push order but worsens the whole-body measurement to 1004 bytes and 342 differences. Typing module-data fields changes no emitted bytes. Staging the terrain return and AI receiver shrinks the frame incorrectly and worsens the comparison.

## Boundary and target ABI

`build/ocl-2632f0/target.decode` decodes all 953 code bytes from 0x002632F0 to 0x002636A9. The sole return is `RET 8` at 0x002636A6. Every direct conditional branch stays within that code extent, with early exits joining the epilogue at +0x3A4; there is no outgoing tail jump. Bytes 0x002636A9 through 0x002636AB are `8D 49 00`, a three-byte alignment LEA, not INT3. The eight-word jump table occupies 0x002636AC through 0x002636CB. Its decoded destinations are 0x00263365, 0x00263372, 0x002633B8, 0x00263450, 0x0026346D, 0x0026349D, 0x002633FD and 0x002634B6, all instruction boundaries within the complete body. Code, padding and table account for 988 bytes.

The checked-callees request for all 988 bytes rejects the embedded table as instructions (`checked-target.log`). The code-only request for 953 bytes succeeds (`checked-code.log`). Probe's endpoint warning likewise decodes table bytes as an instruction and does not refute the separately decoded table boundary. Both raw outputs remain intact.

The complete constructor at 0x002628E0 writes vtable VA 0x010B6010 to object +0x10. Slot 13 (+0x34) reaches ILT 0x0002780E and then this target. The complete landed caller at 0x00262D60 invokes that slot with a coordinate pointer and a 32-bit options word; it uses the secondary receiver unchanged and pops its own two arguments. This independently supports the OCLSpecialPower location-method identity and two-word target ABI. The EA label is additional evidence, not the ABI proof. The bank retains its existing address-derived owner and method names; the rejected historical angle argument is absent. Raw evidence is `2628e0.decode`, `ocl-vtable.log` and `caller-262d60.decode` under `build/ocl-2632f0/`.

Receiver-relative fields are object at -8 and module data at -0xC; `findOCL` receives this-0x10. The base dispatch ILT 0x000170DA reaches 0x0026A620, whose complete 80-byte body has `RET 8` and the same secondary receiver. Slot +0x34 reaches the 253-byte terrain helper 0x001A3770; slot +0x38 reaches 0x001A38B0 (151 bytes). Both return the three-field result in hidden storage with `RET 8`, rather than a register-only scalar result. Slot +0x7C reaches 0x001AA900 (294 bytes), accepting one by-value four-byte string handle and releasing it on every return path. The target constructs TopArmySpawnPoint, BottomArmySpawnPoint, LeftArmySpawnPoint and RightArmySpawnPoint handles. Waypoint coordinates are at +0xC. Full helper decodes and corresponding `checked-*.log` files are retained.

## Callees, indirect dispatch and canonical declarations

ILT 0x0000E4E4 reaches 0x003DAD60. Its full 170-byte body has two `RET 4` paths with boolean AL results, takes one writable coordinate pointer and reads/writes all three float fields. Its calls into world-to-cell conversion and circular traversal, plus its indirect terrain-height call, were decoded separately. The target ignores the boolean result at all three sites. The bank binds the observed member-call ABI through the existing ILT symbol without adding a guessed semantic pin. `3dad60.decode` and `checked-0x003dad60.log` retain the complete evidence.

The length helper at 0x000C3D10 reads x and y, takes no stack argument and returns a float in ST0. The complete native coordinate constructor/copy/assignment helpers at 0x0008A410, 0x0005BC20, 0x007E5960 and 0x007E5990 copy all three words and return the receiver with `RET 4`; the default constructor/destructor helpers at 0x00083330 and 0x0005BC40 are empty. The best bank includes the existing POD `game/Libraries/Include/Lib/Coord3D.h` instead of a private redeclaration. `Coord3DBase` remains a typedef to preserve the saved body's descriptive name. Native WWMath declaration trials remain saved as rejected alternatives. This is banked layout evidence, not approval to replace the project's canonical class integration during a later landing.

The six-word cdecl wrapper at 0x00262890 pops its stack in its caller and reaches ILT 0x0003E360, which routes to the full 62-byte body at 0x001D6770. That body iterates four-byte element pointers and calls virtual slot +4 with five words, then returns with `RET 20`. Existing competing FXList and ObjectCreationList pins do not independently identify those indirect callees or their argument types. The bank keeps the address-derived wrapper name and binds the existing ILT 0x000443E1 rather than inventing a pin. The five-word wrapper at 0x001F1E80 reaches ILT 0x00002A59 and the full 57-byte body at 0x001D67C0, which forwards four words to virtual slot +0xC and ends with `RET 16`. The donor's comment naming 0x005D67C0 is not the actual decoded retail target. These indirect payload semantics remain an unresolved identity/type check for promotion, even if a future probe matches the bytes.

The complete 18-byte controlling-player getter at 0x001BE3F0 reads object +0x23C, returns a pointer and tail-jumps through its independent lookup route. The complete 238-byte add-upgrade body at 0x000D24C0 has two stack words and `RET 8`. Lookup 0x0010B0E0 is a full 68-byte one-reference-argument method with `RET 4`; it reads the string handle, constructs its name key, traverses the linked payload chain and returns the upgrade pointer. Its actual target ILT uses existing spelling `j_0002F95A`; the final candidate corrects an initially unresolved lowercase thunk spelling. No pin was added for this correction. All corresponding complete decodes and checked-callees outputs are retained.

## Container payload and exception cleanup

The target calls vector-copy ILT 0x00015474, which reaches the complete 162-byte constructor at 0x000D2E70. Its allocation/base helper at 0x000CC650 is 130 bytes; its allocator helper at 0x000CA2C0 is seven bytes. The actual element constructor reached by the copy loop is 0x00887B60, fully decoded for 121 bytes. After its locking setup it reads precisely source[0], writes precisely destination[0], and increments the dword reference count in the non-null pointed buffer. It reads or writes no second element field. The loop advances by four bytes. This is independent scalar string-handle payload evidence; neither allocation size nor a matching template name was used to choose between a handle and a small pair.

The vector destructor at 0x000658A0 is fully decoded for 149 bytes. It calls the complete 134-byte release helper at 0x00887940 for each four-byte handle before freeing allocation storage. The release helper decrements the pointed reference count, frees at zero and clears the object's handle. All conditional paths, allocator thresholds and returns were inspected. The C-string constructor at 0x00888BC0 was decoded in full for 72 bytes and compared with the existing string declarations.

Target EH handler 0x00C0F838 uses FuncInfo 0x00DFE898. Its sole live state 0 unwinds to -1 through cleanup 0x00C0F830, which passes EBP-0x64 to ILT 0x00026AB2 and vector destructor 0x000658A0. That receiver corresponds to the target's local vector at ESP+0x20 in the decoded frame. Coordinates have no extra destructor state; the terrain method owns each by-value string parameter's release. Vector-copy FuncInfo 0x00DE7300 has two states: state 0 frees base allocation through 0x00BF9990 to 0x000657A0; state 1 uses 0x00BF9998 to call the empty destroy-range helper at 0x000607F0 before falling to state 0. The latter helper is one byte (`RET`), not the neighboring bytes of another function. Raw unwind tables and cleanup decodes are `eh-target.log`, `eh-vector-copy.log`, `c0f830.decode`, `bf9990.decode`, `bf9998.decode`, `657a0.decode` and `607f0.decode`.

The candidate delegates vector copy and destruction to the native AsciiString/vector calls. Its emitted cleanup bytes have not been proved identical to retail. No `_STL` ledger row or symbol was added or changed. The active STLport-family pause therefore does not prevent preserving this partial, but existing STL identities still require the repository's normal approval and gate procedures before promotion.

## Measured experiments

Each table entry is computed from the unedited raw probe output; source with the same trial stem is retained under `build/ocl-2632f0/`. The final binding trial is also copied verbatim to `bank-ready-trial.cpp`. Quality is the repository's measured ranking, not the proportion of source recovered or proof of identity.

| Trial | Emitted bytes | Differing bytes | Measured quality | Raw probe |
| --- | ---: | ---: | ---: | --- |
| baseline | 984 | 592 | 0.3927 | `build/ocl-2632f0/baseline.log` |
| retail-order | 984 | 599 | 0.3856 | `build/ocl-2632f0/retail-order.log` |
| field-assignment | 976 | 625 | 0.3431 | `build/ocl-2632f0/field-assignment.log` |
| field-assignment-order | 976 | 623 | 0.3451 | `build/ocl-2632f0/field-assignment-order.log` |
| implicit-assignment | 1000 | 489 | 0.4808 | `build/ocl-2632f0/implicit-assignment.log` |
| implicit-assignment-order | 1000 | 338 | 0.6336 | `build/ocl-2632f0/implicit-assignment-order.log` |
| canonical-memcpy | 984 | 592 | 0.3927 | `build/ocl-2632f0/canonical-memcpy.log` |
| canonical-order-memcpy | 984 | 599 | 0.3856 | `build/ocl-2632f0/canonical-order-memcpy.log` |
| canonical-force | 984 | 592 | 0.3927 | `build/ocl-2632f0/canonical-force.log` |
| loop-field-copy | 968 | 661 | 0.2905 | `build/ocl-2632f0/loop-field-copy.log` |
| canonical-inherited | 1000 | 338 | 0.6336 | `build/ocl-2632f0/canonical-inherited.log` |
| canonical-pod | 1000 | 338 | 0.6336 | `build/ocl-2632f0/canonical-pod.log` |
| loop-aggregate | 968 | 661 | 0.2905 | `build/ocl-2632f0/loop-aggregate.log` |
| loop-subtract | 952 | 642 | 0.2773 | `build/ocl-2632f0/loop-subtract.log` |
| upgrade-getter | 1004 | 342 | 0.6215 | `build/ocl-2632f0/upgrade-getter.log` |
| typed-delta | 968 | 661 | 0.2905 | `build/ocl-2632f0/typed-delta.log` |
| typed-delta-getter | 972 | 669 | 0.2905 | `build/ocl-2632f0/typed-delta-getter.log` |
| native-getter | 972 | 666 | 0.2935 | `build/ocl-2632f0/native-getter.log` |
| typed-module-data | 1000 | 338 | 0.6336 | `build/ocl-2632f0/typed-module-data.log` |
| typed-module-getter | 1004 | 342 | 0.6215 | `build/ocl-2632f0/typed-module-getter.log` |
| staged-edge | 900 | 663 | 0.1508 | `build/ocl-2632f0/staged-edge.log` |
| staged-edge-getter | 904 | 665 | 0.1569 | `build/ocl-2632f0/staged-edge-getter.log` |
| bound-path-helper | 1000 | 338 | 0.6336 | `build/ocl-2632f0/bound-path-helper.log` |
| bound-final | 1000 | 338 | 0.6336 | `build/ocl-2632f0/bound-final.log` |
| final | 1000 | 338 | 0.6336 | `build/ocl-2632f0/final.log` |
| bank-ready | 1000 | 338 | 0.6336 | `build/ocl-2632f0/bank-ready.log` |

EH choices were generated first with `eh_levers.py` and tested with a finite six-trial search. Their raw outputs and immutable trial sources remain in `build/shape_search/4d6245af82cb48bc81f9d741247dfaa0/`; `eh-search.log` and `eh-manifest.json` retain the receipt. The mechanical EH variants did not improve the measured original-bank quality. The family generator on the canonical POD candidate produced no applicable source-level choices (`family-generator.log` and `family-choices.json`), so no successful family-search result is claimed. Artificial inherited-coordinate source was rejected as unsupported layout despite matching the best masked shape; it is preserved only as an experiment.

## Verification limits

`class-final.log`, `check-csv-final.log`, `pin-consistency-final.log` and `name-final.log` record passing checks. This checkout's `name_regression.py` CLI takes Git revisions, not file paths; `name-canonical.log` preserves the failed file-path invocation. The final file comparison uses that tool's `regressions(original_bank, candidate)` function and reports an empty result. The scoped byte gate failed for the target's remaining size and instruction mismatches. An early binding gate (`scoped-gate.log`) also reported two unresolved declarations; the final bindings remove both. The final raw gate on the saved bank is `build/ocl-2632f0/scoped-gate-bank.log`, with exit status 1 and one failed byte comparison. It reports no unresolved calls. No full gate was required for a bank/evidence-only change, and no hook or baseline was bypassed.

`declarations-baseline.log` records the unmatched-declarations check on the original scratch bank. It rejects the bank's declaration-only convenience views because the bank is not ledger source; it is not a passing source-promotion check. A future landing must integrate or remove those views and rerun the required declaration/class/name checks. Byte equality, indirect dispatcher semantic identities and that source integration are unresolved checks, not claimed recoveries.
