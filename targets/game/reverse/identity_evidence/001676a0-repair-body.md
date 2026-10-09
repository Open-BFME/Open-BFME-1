# Repair body at RVA 0x001676A0

The recovered symbol is `?processRepair@Rva001676A0Owner@@QAEXXZ`. Its owner and original method name remain unproven. The Zero Hour `AIPlayer::updateBridgeRepair` body supplies the algorithm, and AIPlayer's independently identified virtual slots supply compatible calls, but neither establishes the identity of this receiver. The nearby row named `updateBridgeRepair` at RVA 0x00167930 is an assembly lift with a different body and is not identity evidence for this target. All descriptive names from the bank are retained.

## Boundary and ABI

The 521-byte retail extent starts at RVA 0x001676A0 and ends immediately after the `ret` at RVA 0x001678A8. Every conditional branch targets an instruction inside this extent. The returns at offsets 0xF9, 0x11B, 0x1EB and 0x208 restore the applicable register saves and the 0x18-byte local frame. There is no exception registration, cleanup state, outgoing conditional branch or external tail jump in this target.

The complete caller at RVA 0x001682F0 retains its receiver in ESI, restores ECX from ESI, pops ESI and tail-jumps through ILT RVA 0x000428AC to this body. It passes no stack arguments. The target uses ECX as its receiver and returns with a plain `ret`; its return value is unused. The caller's synthetic `BfmeThingCAA` identity is insufficient to name the target, so the source keeps the bank's address-derived owner.

The receiver fields observed by the complete target are the three-word base coordinate at 0x34, its one-byte validity flag at 0x40, the dword repair-ID array at 0x48, the dozer ID at 0x50, the three-word origin at 0x54, the signed queue count at 0x60, one-byte queued and repairing flags at 0x64 and 0x65, and the signed timer at 0x68. The two-element ID-array declaration follows the next independently accessed field at 0x50, rather than an allocation-size inference. Object position is three dwords at 0x38, ID is a dword at 0x74, body-module pointer is at 0x200, and AI-update pointer is at 0x204. The coordinate floats are independently established by the complete Pathfinder destination calculations.

## Direct calls and value copying

The decoded ILTs are RVA 0x0001F253 to 0x0009A510, RVA 0x00011252 to 0x003EAC80, RVA 0x0003436A to 0x000D86C0, and RVA 0x00029C08 to 0x00153D10. The complete destination bodies are 82, 1108, 219 and 203 bytes respectively. Their returns and all branch destinations were reviewed. `checked_callees.py` was run for the target and these four extents.

The lookup is `GameLogic::findObjectByID(int)`, a member call with one dword key and a pointer returned in EAX; all paths end in `ret 4`. Its complete decode reads bucket bounds at receiver offsets 0xB4 and 0xB8, follows each node's next pointer at 0, compares its dword key at 4 and returns its object pointer at 8. The source includes the existing `GameLogicObjectLookup.h` and its authentic visible, non-inlined definition. The emitted helper independently matches all 82 bytes, without relocations. No new STL ledger row or pin is required.

Pathfinder receives object, locomotor-set reference and writable destination in that order, consumes three dword stack arguments with `ret 0xC`, and returns a boolean in AL. Its complete body reads the locomotor surface word at offset 0x10 and reads and updates every destination coordinate. The source's local locomotor view includes that word. The repair and move calls each consume two dword arguments with `ret 8`. Their complete bodies copy the object pointer or the three position words into command parameters and dispatch through command-interface slot 0. The receiver adjustment in the target is AI-update plus 0x20. The source uses the existing `CommandSourceType` declaration and `CMD_FROM_AI`, preserving value 2, and typed member-pointer adapters to the existing ILT symbols. No callee pin was added or changed.

The source includes the existing method-capable `coord3d.h`; the generated three-float data-only header lacks the constructor and assignment declarations that the exported retail helpers prove. The complete 25-byte copy constructor at RVA 0x0005BC20 and 29-byte assignment at RVA 0x007E5990 each read and write exactly the three dwords at offsets 0, 4 and 8, return the destination in EAX, and consume one reference argument with `ret 4`. There are no ownership fields or cleanup calls. The fieldwise copy constructor and raw three-word assignment preserve these different compiler shapes. Separately emitted versions independently match all 25 constructor bytes and all 29 assignment bytes. The constructor trial adds `__declspec(noinline)` only to force emission. `checked_callees.py` was run for both helper extents.

## Indirect calls

The owner calls slots 0x50 and 0x54 with respectively one coordinate pointer and no arguments. The independently identified AIPlayer table at VA 0x010968B0 routes those slots through RVAs 0x0002CA57 and 0x00033802 to the complete `findDozer` and `queueDozer` bodies at RVAs 0x00165A50 and 0x001657E0. The first returns an object pointer and consumes its pointer argument; the second takes no stack arguments. These routes corroborate the call shapes without renaming this owner.

The body-module call is slot 0x20 with no stack arguments and a full-width damage-state value in EAX. The complete ActiveBody constructor installs its BodyModuleInterface table at VA 0x010A7718 in the facet at receiver offset 0x10. Facet slot 0x20 routes through ILT RVA 0x00039CB6 to the complete four-byte getter at RVA 0x0020E180, which reads the dword at facet offset 0x20 and returns with a plain `ret`. This is the primary object's damage-state word at offset 0x30. The primary ActiveBody table's slot 0x20 routes elsewhere and is not used as damage-state evidence. The independently landed GarrisonContain body uses the same object field and facet slot, and the original BodyModule declaration returns a damage-state enum by value from a const member. The local address-derived interface retains its integer representation and const declaration. `checked_callees.py` was run for the getter's complete extent.

The AI-update call at slot 0x13C takes no stack arguments and returns an interface pointer in EAX. The DozerAIUpdate constructor installs the main table at VA 0x010C6A90 and the interface table at VA 0x010C6920 at receiver offset 0x340. Main-table slot 0x13C routes through RVA 0x00019646 to the complete body at RVA 0x002B67F0, which returns receiver plus 0x340 or null. The returned interface's slot 0x20 routes through RVA 0x0003A0D0 to the complete 32-byte body at RVA 0x002B68D0; it takes no arguments and returns a boolean in AL. The target uses precisely the pointer from the first call as receiver of the second call. In particular, the target's null-interface return is preserved.

## Retry hypothesis and measurements

The new hypothesis was that an opaque lookup declaration concealed the real helper's read-only effects, preventing the compiler from retaining the queue count across that call. The complete lookup and the current shared visible-helper definition support this hypothesis. It would be refuted if the resulting caller still reloaded the count after the lookup or failed to improve the original loop. The experiment instead recovered the complete prologue and queue loop through offset 0x78.

The saved body also omitted the null-interface return at offset 0x12A and incorrectly returned when the bridge was damaged. Retail's nonzero damage-state branch at offset 0x14E reaches the repair block at offset 0x1EC. Both branches are corrected in the recovered source.

| Trial | Emitted size | Differing bytes reported by probe | First differing offset |
|---|---:|---:|---|
| Original bank | 521 | 384 | 0x23 |
| Corrected branches | 527 | 420 | 0x0D |
| Visible lookup and corrected branches | 521 | 272 | 0x88 |
| Restored Z-copy order | 521 | 254 | 0xA1 |
| Scalar coordinate assignment | 519 | 297 | 0x0D |
| Native copy constructor and scalar assignment | 518 | 297 | 0x0D |
| Native copy constructor and raw assignment | 521 | 0 | None |
| Typed ILT adapters and canonical command enum | 521 | 0 | None |

The shorter experiments additionally lack two and three retail bytes respectively. The scalar assignment hypothesis is rejected by the missing address-based copy instructions at offset 0xC6. Raw assignment reproduces those instructions and the base-coordinate copy while preserving all three words. No register-only search, flag sweep or new pin was needed.

The final source and every trial are retained with unedited probe output under `build/retry-001676a0/`. The final source probe is `probe-final-source.log`; independent helper probes are `probe-helper-lookup.log`, `probe-helper-copy-constructor.log` and `probe-helper-assignment.log`. Complete decodes and checked-callee reports are in the same directory. The `name_regression.py OLD NEW` CLI in this revision accepts Git revisions rather than filenames; the same module's `regressions` function was applied directly to the bank snapshot and final source and reported zero descriptive-to-placeholder regressions.

## Acceptance

Relocation-masked equality is established for the target, visible lookup and both emitted coordinate helpers. The final scoped gate passes strict function, string-reference, constant-reference, DIR32 and body-guard checks; its raw output is `build/retry-001676a0/scoped-byte-gate.log`. Declared-unmatched, class-gate, pin-consistency and name-regression checks pass in the adjacent raw logs. No shared header or shim changed, so the full gate is not required for this source-only recovery.

The direct `check_csv.py` invocation is blocked by the unstaged deletion of the bank: it obtains source inventory from the Git index, which still lists that deleted file and omits the new source. This worker's Git directory is read-only. Applying the checker's unchanged library checks to the exact prospective collection inventory reports zero problems in `build/retry-001676a0/collection-inventory.log`. The coordinator must stage the source addition, evidence addition and bank deletion before running the normal ledger check. This library result does not claim that the direct invocation passed.

An instruction outside the stated extent, a different ABI on one of the decoded routes, a mismatching emitted helper, or an unresolved strict relocation would refute acceptance. The original class and method identity remain unclaimed.
