# SpawnTownsmen update retry at 0x0020CE30

The retained reconstruction is a partial. No new source recovery or byte equality is claimed. The counter-reference form reproduces the shape reported for the earlier unsaved `v41` trial, while improving the preferred saved body. The remaining allocation and scratch-register differences still block landing.

## Revision and retry hypothesis

The tested base is `c5c53d331c52664b4e2a4440f1d1ad603549e958`. The actual model is `gpt-6.1-sol`. Current landed declarations and the constructor at 0x0020CC70 address the old ownership and callee-declaration gaps. The new experiments test complete callee visibility, the canonical GameLogic declaration, the payload representation, and a fully inlined counter helper with an output reference. The hypothesis would be refuted by a decoded ABI disagreement or by compiler outputs that fail to improve the saved reconstruction. Constructor visibility removes the required EH frame; GameLogic and ThingFactory visibility do not fix the remaining register choices.

## Boundary, identity and ABI

`build/r0020ce30-retry/decoded.log` retains complete decoded extents and the vtable jump chains. The target spans 456 bytes. Its two returns are at +0x1B3 and +0x1C7. All conditional branches and ordinary jumps remain inside that span; it has no tail jump. The receiver arrives in ECX at the update-interface subobject, with module data at ECX-0x0C and Object at ECX-8. Neither return pops stack arguments. Both produce a full EAX value, and the fallback is 30.

The complete 76-byte constructor installs the primary vtable VA 0x010A6DD4, behavior-interface table at +0x0C, and update-interface table VA 0x010A6D04 at +0x10. The update table's slot zero reaches 0x0020CE30 through ILT 0x000416DC. The primary table's slot four reaches the landed name-key body at 0x0020CCE0, which references the retail literal `SpawnTownsmenBehavior`. The vendored UpdateModule declaration gives the update interface's first slot as `UpdateSleepTime update()`. This supports the method identity independently of the generated dump name. No SpawnTownsmen source twin exists in the inspected GeneralsMD tree.

The target's actual REL32 calls and direct memmove IAT call are in `checked-0020ce30.log`. Complete decoded bodies and checked callee outputs are retained for list initialization (16 bytes), find (33), node construction (93), overflow copy (265), list add (301), object lookup (82), template lookup (284), newObject (278), setPosition (272), the owner constructor (76), cleanup (11), and the base terrain-height implementation (27). Each checked extent decodes completely. The decoded branches and returns stay within those extents. The checked output alone is not a boundary certificate.

The list initializer returns its receiver in EAX and writes both words of the eight-byte allocation. Its target is reached through ILT 0x00048135. The old linker's alternatename has been removed from the retained candidate. Landing would require independently resolving `??0BfmeListAK@@QAE@XZ` to this constructor route; no new pin was added. The source-level BfmeListAK name is the repository's existing adapter identity, not a claim about an EA class name.

The find helper reads a four-byte key at node+0x0C, follows next at +0x10, returns the node in EAX, and uses `ret 4`. The add helper consumes key then value on the stack and uses `ret 8`. Object lookup consumes the iterated four-byte value as an ObjectID, reads its hash-node key at +4 and Object pointer at +8, and uses `ret 4`. Template lookup consumes one AsciiString reference and returns a ThingTemplate pointer. NewObject takes template, team, a reference to the three-word status mask, and a four-byte extra argument; it uses `ret 0x10`. SetPosition consumes one Coord3D pointer and uses `ret 4`. The indirect terrain call has ECX as receiver, X and Y as four-byte floats, and a null normal pointer; its result remains on the x87 stack. The canonical terrain-height signature and slot six are corroborated by the landed TerrainLogic implementation and its complete decoded body, which uses `ret 0x0C`.

## Container and cleanup evidence

Node construction initializes vector begin, end and capacity at +0, +4 and +8; stores the single key at +0x0C; and clears next at +0x10. The complete overflow copy helper at 0x000BBE70 reads exactly one word from the value reference at +0x92, writes exactly one word at +0x94, and advances the destination by four at +0x96. Its prefix and suffix copies use memmove, its capacity arithmetic scales by four, and it has no second value field or element cleanup call. The add helper's direct construction paths also write one word and advance end by four. This refutes a pair-valued payload. The retained vector of void pointers is a representation adapter for four-byte values cast to ObjectID, not independent proof of the native template argument's pointer category. Integral and unsigned payload variants produce the saved body's same bytes and supply no new type evidence. No `_STL` ledger row or pin was added or changed.

`eh-retail.log` gives one unwind state. State zero cleans up the allocation saved in the constructor temporary; the complete cleanup at 0x00C0C300 pushes that pointer, calls scalar delete at RVA 0x00881EB0, restores the stack, and returns. The main body sets state zero before the list constructor and resets it to -1 afterwards. No vector or spawned-object destructor is attached to that state. The visible-constructor experiment removes this frame and is rejected. `object-evidence.log` decodes the retained candidate's COFF unwind map and cleanup, asserts its sole predecessor is -1, and verifies the complete eleven-byte cleanup against retail with the scalar-delete relocation checked separately. Unknown concrete terrain overrides and the original SpawnTownsmen data declaration were not independently reconstructed; there is no exact landing claim.

## Measurements and rejected shapes

The masked byte fraction below counts un-emitted target bytes as wrong. The authoritative bank quality uses `finish_measure.py`'s separate formula, `1 - (differing bytes + 2 * size error) / retail size`, floored at zero. It is 0.6404 for the retained candidate and 0.2675 for the original bank. The bank metadata and immutable measured archive record that quality. Misaligned relocation operands in nonmatching shapes make both measures diagnostic scores, not relocation verification. The retained body's first unmasked difference is +0x1D. Its normalized comparison reports seven structural differences: the EDI save schedule, literal zero versus ECX at +0x11B, terrain-vtable temporary placement, and argument staging near +0x18C. Its final return is one byte earlier than retail.

| Trial source | Emitted bytes | Differing bytes in overlap | Missing target bytes | Masked byte fraction | Bank quality | Raw probe |
|---|---:|---:|---:|---:|---:|---|
| `0x0020ce30.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/baseline.log` |
| `ctor-visible.cpp` | 398 | 327 | 58 | 0.1557 | 0.0285 | `build/r0020ce30-retry/ctor-visible.log` |
| `lookup-canonical.cpp` | 398 | 327 | 58 | 0.1557 | 0.0285 | `build/r0020ce30-retry/lookup-canonical.log` |
| `lookup-visible.cpp` | 398 | 328 | 58 | 0.1535 | 0.0263 | `build/r0020ce30-retry/lookup-visible.log` |
| `external-canonical.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/external-canonical.log` |
| `external-visible.cpp` | 451 | 332 | 5 | 0.2610 | 0.2500 | `build/r0020ce30-retry/external-visible.log` |
| `external-ob1.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/external-ob1.log` |
| `external-og-off.cpp` | 545 | 393 | 0 | 0.1156 | 0.0000 | `build/r0020ce30-retry/external-og-off.log` |
| `count-helper.cpp` | 341 | 265 | 115 | 0.1667 | 0.0000 | `build/r0020ce30-retry/count-helper.log` |
| `find-visible.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/find-visible.log` |
| `integral-payload.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/integral-payload.log` |
| `unsigned-payload.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/unsigned-payload.log` |
| `count-forceinline.cpp` | 457 | 290 | 0 | 0.3632 | 0.3596 | `build/r0020ce30-retry/count-forceinline.log` |
| `refresh-forceinline.cpp` | 222 | 184 | 234 | 0.0833 | 0.0000 | `build/r0020ce30-retry/refresh-forceinline.log` |
| `count-reference.cpp` | 451 | 324 | 5 | 0.2785 | 0.2675 | `build/r0020ce30-retry/count-reference.log` |
| `count-reference-null.cpp` | 455 | 162 | 1 | 0.6425 | 0.6404 | `build/r0020ce30-retry/count-reference-null.log` |
| `count-reference-both.cpp` | 455 | 177 | 1 | 0.6096 | 0.6075 | `build/r0020ce30-retry/count-reference-both.log` |
| `newobject-visible.cpp` | compile failure |  |  | 0.0000 | 0.0000 | `build/r0020ce30-retry/newobject-visible.log` |
| `newobject-visible.cpp` | 455 | 162 | 1 | 0.6425 | 0.6404 | `build/r0020ce30-retry/newobject-visible.log` |
| `candidate.cpp` | 455 | 162 | 1 | 0.6425 | 0.6404 | `build/r0020ce30-retry/candidate.log` |
| `candidate.cpp` | 455 | 162 | 1 | 0.6425 | 0.6404 | `build/r0020ce30-retry/final-candidate.log` |

The EH generator's eight bounded trials are preserved in `eh-search.log` and `eh-choices.json`; the two bounded family trials are in `family-search.log` and `family-choices.json`. These were bounded probes, not an exhaustive search. Their manifests and all trial sources remain under `build/shape_search/`. The full newObject donor was copied from its actual landed source, adapted to the shared Object slots, and independently probes 278/278 bytes exactly in `newobject-helper.log`; making it visible leaves the target's residual unchanged. No helper was simplified merely to advertise register preservation.

## Checks and reopening condition

`scoped-gate-raw.log` records a failed 1/1 ordinary byte check of the candidate through `build.verify_functions`, using an in-memory candidate row and leaving the ledger untouched. It also reports the missing list-constructor pin. `class-gate.log`, `check-csv-final.log` and `pin-consistency-final.log` pass. The retained candidate includes the shared Coord3D and GameLogic declarations. The current `name_regression.py` CLI accepts Git revisions rather than file paths; its repository comparison function reports no descriptive-name regressions between the original bank and retained source in `object-evidence.log`. The declared-unmatched source check rejects a scratch candidate owning zero ledger rows, so this is a bank rather than an accepted source. A full gate is not required for a bank and was not run. All raw probes, trial sources, decoded instructions and checks are preserved under `build/r0020ce30-retry/`; the running verdict is `build/verdict.txt`.

Reopen with evidence for a native expression or compiler-visible declaration that changes the ESI/EDI allocation or the three late scratch-register residues while retaining the decoded ABI and constructor cleanup. Repeating entry versus branch counter initialization, local-order sweeps, the now-measured callee-visibility experiments, or integral versus pointer payload spelling has no remaining justification. The inlined helper is a source arrangement, not a recovered native out-of-line function.
