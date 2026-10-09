# RVA 0024ABA0 native transfer retry

The tested revision is `871e04e61d8563350f71ca698afcd652e9016d94`. This is a partial reconstruction, not an exact recovery or a ledger identity correction. The generated row remains unchanged. The source retains `Rva0024ABA0::method`; its canonical Xfer parameter gives the emitted symbol `?method@Rva0024ABA0@@QAEXPAVXfer@@@Z`.

## New hypothesis and result

The earlier bank used manual container views, linker aliases, an eight-byte array temporary, a signed list count, and direct map-count transfer. Current landed neighbours supply native lists at +EC and +104, the shared Object and Xfer declarations, the corrected ObjectID-transfer return contract, and an existing independently qualified signed-map lookup pin. The retry hypothesis was that the native container expressions and the decoded lifetimes would remove the frame mismatch. Unchanged instruction structure and the earlier mismatch would refute it.

The hypothesis explains most of the mismatch. The target also contains a version transfer missing from the old bank. Its save-map branch serializes a copied pair without updating the map; the old bank added a lookup and assignment there. The map count is a local, not the member at +FC. Native unsigned list-count iteration, list erase and push_back, and the corrected map branches reproduce the entire instruction sequence after local displacements are normalized. Separate object-ID locals inside the save and load loops give the best retained source. Later lifetime and storage trials did not close the remaining displacement differences.

## Boundary, owner and caller

The complete 559-byte target decodes through two `ret 4` exits at +1D4 and +22C. Every direct conditional branch and unconditional jump stays inside that extent. Padding begins immediately afterward at RVA 0024ADCF. There is no target exception-registration prologue, unwind state, tail call or indirect jump.

The primary vtable at VA 010B02A8 has ILT 0003E99B in slot 3 (+0C); the thunk reaches this target. The complete named constructor at RVA 0024A560 installs that primary table at +0 and initializes the list at +EC, tree at +F8, count at +FC, and ID list at +104. The complete named destructor at 0024A180 is additional owner evidence. This supports HordeSiegeEngineContain ownership, but this retry does not assign an EA method name to the opaque bank.

The complete 19-byte Snapshot-transfer caller at RVA 009D6410 loads its Snapshot argument into ECX, pushes its Xfer receiver and calls virtual slot +0C. Together with the installing table, this proves the target receiver adjustment is zero and its one stack argument is Xfer*. The caller ignores the target's return value. The target has no hidden result storage; its opaque method retains a void declaration rather than claiming an unsupported returned value.

## Container fields and actual construction chain

The +EC list contains pointers: the target reads node+8, dereferences that value at +74, and transfers the resulting ObjectID. The shared Object header independently witnesses `m_id` at +74. The landed restore neighbour converts IDs from +104 into Object* values appended at +EC. On load, the target unlinks a node, deallocates its twelve-byte storage, then invokes the existing GameLogic destruction contract on the saved object. The decoded 190-byte GameLogic callee takes Object* through `ret 4` and performs deferred destruction. Erasing a node does not itself delete its Object.

The +104 list construction is fully inline in the target: its value address is node+8, and the only value write copies one dword from the ObjectID transfer local. The actual transfer helper routes ILT 0000C9B4 to complete body 0010C3C0. It pushes width 4, the data pointer, and the independently read `ObjectID` literal at VA 0108920C; it dispatches at +90 and returns without popping its two cdecl arguments. Its native return is Xfer&, which the bank declares correctly and ignores. This establishes a four-byte ID representation, not an allocation-size guess.

The tree lookup route is ILT 0001F91F to 00226FA0. Its complete body reads the key at node+10 using signed comparisons, returns the mapped-field address at node+14, and returns with `ret 4` on both paths. The missing-key branch constructs a two-dword key/value input with zero mapped value and calls ILT 0000ED2C to 00224AD0. All fifteen exits of that complete insertion body use `ret 12`; the arguments are hidden iterator-result storage, a one-pointer hint iterator, and the value address. Its node-insertion route is ILT 00042DE8 to 00223D20. That complete body has `ret 20`, stores the parent and zero child pointers, rebalances, increments the receiver's node count, and passes node+10 plus the input value to ILT 00030788.

The actual copy helper reached by that last ILT is the complete 23-byte body at 00222520. It conditionally reads exactly source+0 and source+4 and writes exactly destination+0 and destination+4. There are no other value-field reads, writes, calls or cleanup paths. This establishes a four-byte signed key and one four-byte mapped field. The bank uses an integer representation for the mapped field without claiming its original enum or semantic meaning. No pointer payload, larger pair, nontrivial destructor or ownership is inferred from the allocation size or generated template name.

The existing `Rva00226FA0Less` map pin is reused. No STL ledger row or pin is added, changed or renamed. The old constructor's generated payload spelling is not independent type evidence and was not used to establish the value shape.

## Virtual argument and result contracts

The native Xfer table installed by the complete constructor at 007E7660 supplies the called slots. The storing and light-CRC base predicates have complete three-byte AL-return bodies. The complete +74 unsigned-int and +78 signed-int transfer implementations each take one reference, forward width 4 and return the receiver through EAX with `ret 4`. The +8C bool transfer forwards width 1 with the same reference-return convention.

The complete +28 version-transfer body reads only the two byte fields at +0 and +1, forwards the second byte, and checks its permitted range. Its successful return restores the receiver in EAX and uses `ret 4`; invalid-version paths terminate in the native throw call. Its complete source was checked rather than treating the earlier pair description as proof.

The enum transfer has four successful width arms, each returning the receiver with `ret 12`, and a terminating invalid-size throw arm. Its 196-byte code extent and separate sixteen-byte switch table were inspected together. The table's four entries target the decoded arm starts. The existing canonical header's separate +90/+94 issue is avoided by calling the already matched address-qualified ObjectID helper; no shared header is changed.

## Compiler experiments and remaining mismatch

Every trial and raw stdout/stderr is retained under `build/0024aba0/`. The finite scope search and compiler listing are also retained. The frame-family generator found no applicable scalar initialization to transform, so the scope alternatives were supplied explicitly to shape_search. The following table summarizes the useful and rejected shapes; these are diagnostic measurements rather than acceptance results.

| Trial | Source change | Compiler bytes | Non-relocation differences |
|---|---|---:|---:|
| 00 | Original preferred bank | 568 | 490 |
| 01 | Canonical headers, native lists/map and corrected complete branches | 559 | 26 |
| 02 | Separate version and object-ID scopes | 559 | 24 |
| 04 | Object-ID scope with function-scope version | 559 | 18 |
| 05 and 08 | Version constructor | 559 | 26 and 18 |
| 10 | Four-byte version storage | 559 | 18 |
| 11 | Visible native Version1 helper | 559 | 24 |
| 12 | Overlapping version and object-ID scopes | 559 | 16 |
| 19 | Empty version destructor | 559 | 18 |
| 21 | Enum ObjectID local and native enum ID list | 559 | 18 |
| 26 | Separate object-ID locals inside both loops | 559 | 14 |
| 28 | Temporary version object | 559 | 26 |
| 29 | Aggregate version/count local | 606 | 485 |
| 32 | Explicit local storage and placement pair construction | 559 | 27 |
| 33 | Explicit local storage with manual unlink | 561 | 325 |
| 34 and 35 | Move the map key or value outside its loop | 559 | 14 |

The preferred native source has no relocation-layout drift. Strict resolution finds no unresolved calls and agrees at every call/global operand. The remaining different byte offsets are +029, +02D, +031, +06A, +070, +10A, +12C, +170, +174, +1DA, +1E2, +1F3, +20D and +21F. They are displacement bytes only: the version occupies the incoming argument slot instead of the first local slot, the object-ID and load-key locals occupy another slot, and the count is four bytes below retail. Both emitted return paths and the frame size already agree.

Raw acceptance evidence is in `build/0024aba0/scoped-gate-final.log`; that gate fails the target byte comparison. The preferred bank was then reproduced at its final path, with the same result in `scoped-gate-bank.log` and `banked.probe.log`. `proof-bank.log` retains the strict resolved operand audit and passing string, constant and DIR32 checks. `pin-consistency.log` and `check-csv-after-bank.log` pass. The standalone class gate passes, and the direct `name_regression.regressions` comparison reports no descriptive-name downgrades. This checkout's name_regression command accepts Git revisions, so passing file paths to its CLI failed before the direct file comparison was used. No hook, baseline, ledger or pin was modified to make a check pass.

The remaining blocker is `stack-slot/frame-layout`. Reopening is justified by evidence for a different native local lifetime or representation that changes those exact slots. Repeating return-width, version-constructor, padding or unchanged register spelling trials is not justified by these results. All experiments remain uncollected under build; the better native body is preserved through the normal bank procedure.
