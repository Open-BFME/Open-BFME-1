# Recovery attempt at 0x002BAA40

The complete candidate remains a partial. It emits 353 bytes against 353 retail bytes and differs at 18 non-relocation bytes. The strict scoped gate resolves every relative call. Retail uses EBP for the owner and EDI for geometry; the candidate exchanges those roles. The bank keeps the earlier recorded symbol `?slot14@Rva002BAA40@@UAEXXZ` and the address-derived owner.

## Retry hypothesis and refutation

The current tree provides the complete non-retaining mask constructor, the linked-filter method, the typed closest-object pin and canonical Object, Thing and Coord3D headers. Native field stores, expression-temporary lifetimes and separate evaluation of the first kind test could address the earlier frame and control-flow drift. An experiment retaining the old broad drift would refute that hypothesis. Trial 007 instead reaches the retail size, frame, instruction sequence, relocation positions and exception states. A new register allocation hypothesis needs evidence beyond the exhausted pointer/reference and owner-const variants.

## Boundary and incoming ABI

The requested range is 0x002BAA40 through 0x002BABA0 inclusive. The entry installs an exception registration, its guard reaches the shared epilogue, every conditional target stays inside the range and the last instruction is a plain RET. The following bytes are INT3 padding. There is no outgoing jump, explicit argument load or hidden return pointer. ECX addresses the primary object and reads the owner at +0x08 and the four-byte ID guard at +0x94. The handler receives the unchanged saved primary receiver and one four-byte Object ID.

The matched FoundationAIUpdate constructor at 0x002BA040 installs VA 0x010C734C at this+0. That table's slot 14 contains VA 0x0044A72D, whose complete five-byte thunk jumps to this target. This proves table membership, not a semantic method name. No named direct caller was found. The current pin named UpdateModuleInterface::update routes through 0x00044B0C to the SpecialAbilityUpdate-specific body 0x002AA9D0, so it is not independent caller evidence for this target. A complete virtual caller and its return consumption remain unverified. The candidate's void return must be checked against such a caller before an exact recovery is claimed.

## Types and outgoing ABI

Object and Thing come from their shared headers. The decoded target obtains geometry at the final template's +0x60, position at Object+0x38 and orientation from Matrix3D at Object+0x08. The full eight-byte orientation helper reads floats at matrix+0x10 and +0x00 and returns in ST(0). The radius is the geometry float at +0x14 multiplied by the literal 1.1f. The four-argument query receives a Coord3D pointer, a four-byte float, the value 1 and a linked filter pointer, in that order; it cleans 16 bytes. Its complete inner query cleans 20 bytes and returns either zero or an accepted candidate pointer in EAX. The target null-tests that pointer and reads the resulting Object ID at +0x74.

The complete 102-byte mask constructor at 0x000C3DD0 reads all six dwords of each of two references, writes the first block at +0x08 through +0x1C and the second at +0x20 through +0x34, clears the next link at +0x04, installs the filter table and returns with RET 8. It retains neither source reference. The caller builds six-word BitFlags storage and sets bit 8 of word 3, which is index 104. This agrees with the STLport bitset constructor used by the native BitFlags wrapper; allocation size and donor naming are not the type evidence.

The inlined collision filter has a vptr at +0x00, a next link at +0x04, three position floats at +0x08 through +0x10, a borrowed geometry pointer at +0x14, the angle float at +0x18 and a byte at +0x1C. The complete related constructor at 0x000FBCB0 independently reads and writes all those fields and cleans four argument slots. Its geometry input is stored as a pointer, whereas its position input is copied. The complete filter-link method walks +0x04 links, appends its argument, returns the original head in EAX and cleans four bytes.

Both kind checks go through the independently decoded Thing helper, which extracts the indexed template bit and returns 0 or 1. The target consumes AL. The complete ID handler at 0x002BA240 compares and stores the four-byte ID at +0x94 and cleans four bytes on every return. The complete producer setter at 0x001BE450 accepts a const Object pointer and stores either its +0x74 ID or zero at receiver+0x78. Unknown kind semantics stay expressed by their numerical indices.

## Exception cleanup

Retail has state 0 to -1 for the collision temporary and state 1 to 0 for the kind filter. Cleanup actions at 0x00C13630 and 0x00C13638 use EBP-0x64 and EBP-0x44 respectively and jump through decoded thunks to 0x000FBD00 and 0x000C3E50. Both complete seven-byte destructors store the base table and return; they destroy no geometry or mask payload. The candidate has the same state predecessors and receiver adjustments. Its visible mask constructor and both cleanup destructors pass strict scoped comparisons (3/3). The target itself fails (1/1). These helper checks certify reused shapes, not new landed recoveries.

## Measured experiments

Every probe uses the independently reviewed retail size and retains its complete output under `build/002baa40/`. The initial source and all subsequent trial sources remain there.

| Trial | Hypothesis or correction | Emitted bytes | Non-relocation differences | First difference |
|---|---|---:|---:|---|
| 001 | Initial complete reconstruction with trivial coordinates and an early radius local | 347 | 214 | +0x26 |
| 002 | Canonical Object and Thing headers, explicit coordinate copy and typed floating query argument | 349 | 221 | +0x26 |
| 003 | Reverse the two kind-test operands | 349 | 221 | +0x26 |
| 004 | Use /G7 on trial 003 | 346 | 250 | +0x18 |
| 005 | Use the existing DistanceCalculationType query declaration | 349 | 221 | +0x26 |
| 006 | Canonical Coord3D header and scalar coordinate stores | 349 | 221 | +0x26 |
| 007 | Keep all collision fields in body store order and evaluate the found kind test separately | 353 | 18 | +0x2A |
| 008 | Represent the geometry local as a pointer | 353 | 18 | +0x2A |
| 009 | Make the owner local const | 353 | 18 | +0x2A |
| best | Correct the witnessed bounding-sphere member name and format the measured body | 353 | 18 | +0x2A |

The EH generator search is retained at `build/shape_search/8cf33b5a84fe40de82097a415c3ba16a/result.json`. Its five measured trials make no improvement to trial 001. They cover the STLport exception macro, nothrow delete[] declaration and the EH switch. The generator also offered a nothrow override accessor, but the plateau stopped before it was tested; it is not an exhausted experiment. The non-EH generator found no applicable source-level choice on either trial 002 or trial 007. Trial 008 and trial 009 produce the identical instruction/relocation result as trial 007. No further unchanged register experiment was started.

## Remaining mismatch and checks

The exact differing offsets are +0x02A, +0x02C, +0x02F, +0x042, +0x043, +0x045, +0x048, +0x054, +0x057, +0x05A, +0x05D, +0x081, +0x0C8, +0x12A, +0x143, +0x14B, +0x14C, +0x14E. All are the owner/geometry register exchange or the associated save/restore bytes. This assertion is derived from the strict gate's fully resolved bytes in `build/002baa40/best-measurement.json`, not a normalized similarity score.

Raw target and callee decodes are `build/002baa40/retail-decode.log`, `abi-evidence.log`, `collision-ctor-decode.log` and `inner-decode.log`. The `checked-*.log` files preserve complete extent inventories, including cleanup and mask helpers. Raw cleanup and strict byte comparison output is `build/002baa40/scoped-byte-gate-best.log`; the best complete probe is `build/002baa40/probe-best.log`.

Class adoption and the witnessed member names pass in `class-best.log` and `name-oracle-best.log`. Pin consistency passes in `pin-consistency.log`. The declaration gate reports that a scratch partial has no ledger row in `declarations-trial7.log`; this is not a source landing and no exemption was added. There are no shared header, pin or ledger changes, so a full gate is not required for this bank. Reopening requires a new evidenced type, visibility or expression hypothesis for the EBP/EDI exchange and complete caller evidence for the return convention. A semantic name is not required.

The saved bank at `targets/game/reverse/attempts/0x002baa40.cpp` was probed again at its final path. `build/002baa40/probe-bank.log` reproduces the same size and residue, and `scoped-byte-gate-bank.log` repeats the helper passes and target failure. `check-bank.log` proves that removing the bank's two metadata lines gives exactly the measured best source, with no name regressions. The same log verifies the float constant and all recorded DIR32 references. Final CSV validation passes in `check-csv-final.log`. Exactly one verdict row was written for this run.
