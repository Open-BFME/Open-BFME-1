# BfmeGiantBirdFollowThruState::onEnter

The recovered symbol is `?onEnter@BfmeGiantBirdFollowThruState@@UAE?AW4StateReturnType@@XZ` at RVA `0x002C3B90`. Verification used the working tree based on `fad1d1f6adffda051d9ed01e9258d95426a384aa` and the repository's unpacked retail baseline. The implementation includes the shared Object, Coord3D and GameLogic lookup declarations. No symbols.csv pin, shared header or STL ledger identity is added or changed.

## Identity and refutation

The complete constructor at `0x002BEC00` passes the literal `BfmeGiantBirdFollowThruState` at VA `0x010C79BC` to the state constructor, installs vtable `0x010C7968`, stores its byte argument at `+0x24` and zeroes the counter at `+0x28`. The table's name getter also returns that exact literal. Slot 4 contains VA `0x00435346`; decoding that thunk gives a jump to this target. Slots 5 and 6 reach the already recovered `BfmeGiantBirdFollowThruState::onExit` and `update`. The constructor source is `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdStateConstructors.cpp`.

The complete StateMachine caller at `0x000A1360` loads the current state's primary vptr and calls slot `+0x10` with ECX equal to the state pointer and no stack arguments. It consumes EAX as a signed state result. The target returns either zero or minus two, with an ordinary RET and no hidden result buffer. This agrees with the StateReturnType declarations and onEnter slot order in the Zero Hour StateMachine header. There is no Zero Hour GiantBird implementation used as a donor.

The identity would be refuted by a different self-name in the installing constructor, a thunk that routes to a different body, or a slot-4 caller whose receiver, arguments or return consumption differ. Raw evidence is retained in `build/rva002c3b90/retail-identity.log`, `vtable-owner.log`, `retail-caller-terrain.log` and `indirect-slots.log`. Contrary to the old screening description, `0x002C3550` is the swoop state's slot-6 update and has no direct call to this target. It is not the identity witness for this recovery.

## Complete boundary and types

The target ends at the RET at `0x002C3D7B`, followed by INT3 padding. Its three return blocks are at `0x002C3BDE`, `0x002C3C01` and `0x002C3D72`. All direct conditional branches and jumps stay inside the extent. The target has no exception registration, constructor cleanup or owned container temporary. The canonical coordinate has three float fields and no destructor.

The receiver's machine pointer is at `+0x1C`; the machine's owner is at `+0x10`. Object's shared layout places the position at `+0x38`, the complete ten-word model-condition field at `+0x110`, AI pointer at `+0x204` and private-status byte at `+0x344`. The accessed condition words at `+0x120` and `+0x118` belong to that field. Their bit indices are 145 and 71. The AI and locomotor views keep address-derived type names; the observed float at locomotor `+0x44` has no asserted semantic name.

The complete helper at `0x002C3E00` takes explicit `(Coord3D *output, bool *result, bool enabled)` arguments on the stack, receives the same state in ECX and executes RET 12. It reads the enabled argument's low byte, writes a single byte through the result pointer and writes all three output fields at offsets 0, 4 and 8. Its loop, fallback and single return are included in the decode. No helper return register is consumed by the target. The declaration makes no claim about the helper's original name. Its height-clearance call reaches the landed `0x002C3FE0` body. This target introduces no inferred STL value type; the existing canonical GameLogic lookup declaration supplies its hash-map types.

## Callee and virtual-call ABI

| Target call | Verified route and contract |
| --- | --- |
| ILT `0x0002191D` | `Object::notifyModelConditionChanged`, body `0x001BE1C0`, ECX receiver and no arguments; complete decode includes its conditional tail jump. |
| ILT `0x00033A87` | `0x002C3E00`, state receiver and the three output/input arguments described above; the call uses the existing thunk and adds no pin. |
| ILT `0x0000314D` | `StateMachine::setGoalPosition`, body `0x000A0880`, one coordinate pointer, RET 4; the complete body copies all three words if unlocked and non-null. |
| ILT `0x0000795A` | `Rva002BC260Owner::run`, body `0x002BC260`, four ordered pointer-width slots and RET 16. The last two values are zero and one. |
| ILT `0x0001F253` | `GameLogic::findObjectByID`, body `0x0009A510`, a dword ID and RET 4, pointer result consumed as Object; its existing visible implementation remains an inline COMDAT. |
| AI vtable `+0x1FC` | GiantBirdAIUpdate table `0x010C7F40` routes through `0x000111C1`, `0x002BC3A0` and `0x000289B1` to `AIUpdateInterface::chooseLocomotorSet` at `0x00272ED0`. The complete body reads one dword enum, returns a bool in AL and executes RET 4. The target ignores that result. |
| Terrain vtable `+0x18` | Three ordered slots `(float x, float y, Coord3D *normal)` and float result in ST0. The base body at `0x001A2D80` ends with RET 12. W3D table `0x0111D090` routes through `0x000445CB` to `0x006BE250`, which initializes a requested normal and either returns zero or tail-jumps to height-map slot `+0x248` with the same arguments. HeightMap table `0x0111DC88` routes that slot through `0x0003065C` to the complete `0x006CBB50` body. Its decoded x/y loads, normal writes, x87 return paths and RET 12 confirm the float contract. |

Every body used directly as identity or ABI evidence has a complete decode and checked-callees output under `build/rva002c3b90/`. The decoded height-map and terrain routes include their indirect tail jumps. No receiver adjustment is present at these two virtual calls.

## Experiments and acceptance

There was no saved reconstruction at dispatch. The first complete trial supplied the verified helper arguments and emitted a 493-byte body. Native masked-word condition accessors recovered the retail register allocation and final flag update. Changing the lower clamp from `desired < minimum` to `!(desired > minimum)` recovered retail's equality and unordered comparison behavior. Separating the null-AI return from the later owner-status return recovered the early epilogue and both short branches. Canonical Object adoption and the proven virtual method declaration retained equality.

The visible lookup alone did not change the bytes. Initialization reordering alone did not resolve the early return. Those hypotheses are rejected as complete fixes. The trial sources, unedited full probe output and measurements are preserved under `build/rva002c3b90/`. Probe instruction-shape scores are diagnostic and are not byte-match scores.

The final source passes the relocation-aware scoped byte gate, including all direct call targets, float constants and DIR32 references. The goal-mode pointers reference the separately owned `g_012F02D4` and `g_012F02D8` objects directly. Retail pushes VA `0x012F02D4` at RVA `0x002C3CED` and VA `0x012F02D8` at RVA `0x002C3CFD`; the latter reference no longer identifies the second object through a four-byte addend to the first. Raw gate output for the original recovery is `build/rva002c3b90/scoped-byte-gate-bash.log`; add_match's independent gate output is `add-match-gate.log`. Declaration, class, name and pin checks pass in their corresponding logs. No shared header or shim changed, so this isolated conversion requires no full gate.

Collection still requires the coordinator to stage the new source and run check_csv with the normal commit hooks. This seat's post-landing check_csv reports only that the source is untracked, and its Git directory is read-only. The initial check_csv passed. The Windows build.cmd launcher could not see an installed Python in the sandbox; the explicit Git Bash build.sh invocation passed. These raw outputs are retained alongside the scoped gate. The result is uncommitted.

The owner is named with the stand-in BfmeGiantBirdFollowThruState because retail's incremental-link thunk table contradicts the landed AIGiantBird family names, including the constructors and deleting destructors; the vtable slot and ABI evidence above do not depend on that name.
