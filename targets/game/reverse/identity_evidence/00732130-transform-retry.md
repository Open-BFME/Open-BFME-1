# addFactionBib at 0x00732130: verified ABI and rejected transform forms

The retry at revision `aee201bed1b9c208661a83d70fcc468576db5f57` did not recover an exact body. The preferred bank at `targets/game/reverse/attempts/0x00732130.cpp` remains unchanged. Its SHA-256 is `7885c2f6e70aee96a3ba08a822bf2fbaee1fac4f503e66f5f4415e8688fb67a2`. Trial sources, full probe output, byte-gate output, decoded instructions and measurement hashes are retained in `build/target-00732130/`.

## Boundary, identity and calling convention

The complete decoded body occupies `[0x00732130, 0x007323D0)`. The null-map branch at `+0x23` reaches the common epilogue at `+0x288`; the non-null path alone saves and restores ESI. Both paths reach `ret 12` at `+0x29D`. No conditional branch or tail jump leaves this extent. The map guard reads owner `+0x18`; the render call reads owner `+0x10`. Object accesses are template `+0x04`, matrix `+0x08`, ID `+0x74` and GeometryInfo `+0xAC`.

The named constructor at `0x007304E0` installs the primary table at VA `0x011212F0`. Slot 23 contains ILT `0x00008F3F`, whose complete five-byte jump reaches the target. The complete matched `BuildAssistant::addBibs` caller at `0x000FF290` pushes zero, one and the Object pointer before the virtual call through table offset `+0x5C` at `+0x158`. This independently agrees with the target's Object pointer, Bool and float argument order. The target reads the extra argument with x87 `fadd`, so its width and floating representation are established even though this caller passes zero. The target has no hidden return-storage argument and its callers discard any result.

The render chain is `0x0000A704 -> 0x006C8D40 -> 0x0003CAC4 -> 0x006D7090`. The middle body replaces ECX with the pointer at receiver `+0x30A0`. The complete `W3DBibBuffer::addBib` body at the endpoint reads a pointer to twelve scalar words, a four-byte ObjectID and the low byte of the third stack argument, then returns with `ret 12`. Both outgoing paths reach that same return. The ledger's no-argument `Rva006C8D40::invoke` declaration does not describe the forwarded arguments. The scratch member-pointer adapter uses the existing ILT symbol and the decoded three-argument signature, with no new pin.

## Geometry ownership and cleanup

The complete copy constructor at `0x000FFD10` copies the byte at `+0x04`, scalar words at `+0x08..+0x28`, vector members at `+0x2C` and `+0x38`, and cached words at `+0x44..+0x58`. It returns the receiver in EAX and uses `ret 4`. The two actual vector-copy helpers were decoded completely. The first copies words at element offsets `+0x00..+0x18`, calls the reference-counted pointer copy at `+0x1C` and copies the enabled byte at `+0x20`; its stride is `0x24`. The second copies words at `+0x00`, `+0x04` and `+0x08`, calls that pointer copy at `+0x0C` and advances by `0x10`. These are field observations, not payload identities inferred from allocation sizes. The bank retains opaque vector storage and introduces no STL value-type claim.

The target's unwind map has one state, active only after copying its local GeometryInfo. Cleanup at `0x00C4D4E0` adjusts to `[ebp-0x68]` and jumps through `0x000309F4` to `0x000FFCA0`. Normal cleanup uses the same receiver and route. The complete destructor destroys the record vector at `+0x38`, then the shape vector at `+0x2C`, and restores the Snapshot table. The copy constructor's state 0 cleans up Snapshot; state 1 destroys the constructed shape vector before reaching state 0 if later copying fails. The complete vector destructors call the pointer release helper at `0x00887940` at element offsets `+0x0C` and `+0x1C`, respectively, before freeing their allocations. The full pointer copy and release bodies establish reference-count increment, decrement and final free. The vector constructors' partial-construction cleanup maps were retrieved, but their allocation-base and iterator-range cleanup callees were not independently audited in this retry. No new STL row or pin was added.

## Experiments and refutation

The current destructor pin and shared Object header address the old unresolved destructor declaration and private Object layout concerns. They do not address the reported x87 ordering directly. The new hypotheses were that a value-returning transform or scalar input parameters could change evaluation order while preserving the independently verified field layout. A hypothesis required a measured reduction in byte distance and progress at the first transform divergence; none produced either.

| Complete source trial | Emitted bytes | Non-relocation differences | Unemitted retail bytes | Difference count including unemitted bytes |
|---|---:|---:|---:|---:|
| Saved bank | 668 | 347 | 4 | 351 |
| Value-returning transform using Vector3::Set | 664 | 446 | 8 | 454 |
| Existing ILT through a typed member-pointer call | 668 | 347 | 4 | 351 |
| Shared Object and Thing layout plus that call | 668 | 347 | 4 | 351 |
| Scalar transform parameters in Y, X, Z order | 666 | 355 | 6 | 361 |
| Scalar transform parameters in X, Y, Z order | 666 | 355 | 6 | 361 |

Each probe explicitly requested the verified retail extent. Every result has fourteen relocations. The saved bank's measured masked equality is `321/672`, approximately `0.477679`. The first unequal byte is `+0x25`, inside the branch displacement at `+0x23`. The first differing arithmetic instruction is `+0x10C`: retail loads corner Y before multiplying corner X; the bank multiplies X first. The value-returning form first changes the frame immediate at `+0x17`. Both scalar parameter orders produce the same instruction and relocation result. The new ABI and shared-layout forms preserve the baseline arithmetic shape. No improving candidate replaced the bank.

The generated EH choices are preserved as `build/target-00732130/eh.choices.json`. The attempt history already records thirty-three EH trials and unchanged matrix spellings; those choices were not rerun. Unused local counts, declaration-order permutations and arithmetic-term permutations were also excluded because prior records already reject them.

## Checks and reopening condition

The standard `build.verify_functions` scoped verifier, given the explicit candidate row without changing the ledger, fails the complete shared-layout body. Raw output is `build/target-00732130/standard-gate.raw.txt`. The core byte gate also fails the saved bank and shared-layout body; the former still names an unresolved three-argument invoke overload, while the latter has no unresolved symbol. Byte equality has not been established. Relocation resolutions printed after instruction drift do not identify new call targets.

`check_csv.py`, `pin_consistency.py --check`, and the scratch candidate's class gate pass. `find_declared_unmatched.py --fail` rejects that scratch candidate because it has no claimed row; it is not a landed source. Checked callee inventories and full instruction logs are retained separately. No full gate is required for the evidence-only change, and none was run.

The measured blocker is `float/x87-add-chain-order`. Acceptance also remains blocked until the candidate's emitted unwind metadata is compared with retail and the delegated vector partial-construction cleanup callees are independently audited. Reopening requires independent evidence for a different inline transform or input-copy declaration that changes the first arithmetic divergence, or a measured compiler reproducer that controls this scheduling without dummy locals. The verified identity and forwarded ABI do not justify repeating arithmetic spellings or scalar parameter permutations.
