# Retained result

The retry at revision `def3563d64551eca2141799d381911b034a64936` does not recover the target exactly. The original bank remains preferred at `targets/game/reverse/attempts/0x0037c310.cpp`. Its actual definition is `?Rva0037C310@Rva0037C310Owner@@QAE_NHHPAVObject@@@Z`; the first bank comment still names the dump. No source, pin, shared declaration or function-ledger entry was changed.

## Boundary and ABI evidence

`build/0037c310-run/retail-decode.txt` contains the complete target, the matched caller at 0x00290990 and the direct helper extents. The target has false returns at +0x4F and +0x85, and its final `ret 12` occupies +0x1CE through +0x1D0. All target conditional branches and direct jumps stay within the extent. Padding follows the last return. There is no target exception frame or tail jump.

The complete matched caller sets ECX from its owner collection, pushes its target, its second dword weight and its first dword weight, calls ILT 0x000466B4 and tests AL. This supports the existing address-derived owner and three-argument member declaration. The retail target reads the two weights from the corresponding incoming stack slots and returns its predicate in AL. The EA evidence table supplies `EmotionNugget::CanBeActivatedFor` as a lead; this run does not rename the established bank or owner.

The primary Object layout comes from the existing `object.h`. Its ID at +0x74 and AI pointer at +0x204 agree with decoded accesses. The direct calls to 0x001BE410, 0x00098E50, 0x000A2CF0, 0x001BFE20, 0x001BFDB0 and 0x0026F8F0 follow verified ILT routes. The complete bonus tail at 0x00369460 returns AL, consumes two stack arguments and accumulates float values through the second argument. The override tail at 0x00087A80 returns the final pointer without consuming a stack argument. Their decoded bodies are retained separately.

The indirect calls at target +0x27 and +0x35 use the unadjusted AI receiver and consume AL. The indirect call at +0x173 uses the pointer returned by the containment query, takes no stack arguments and returns the Object pointer subsequently queried. This supports the bank's slot views and argument widths. It does not establish semantic names for the virtual slots or enumerate every possible dynamic implementation.

## Independent container evidence

The complete writer at 0x0037C600 accesses the same owner offsets. It passes the stored object key at +8 to the map at +0x14, passes the stored word template key at +0xC to the map at +0x20 and writes one current-frame-plus-delay dword to each returned payload address. The writer and both complete subscript bodies are retained under `build/0037c310-run/`.

The object subscript at 0x00228410 reaches hinted insertion at 0x00225FE0, which reaches insertion at 0x00224200 and the value construction helper at 0x00222590. That complete helper copies exactly the dword at value +0 and the dword at value +4, and returns without stack cleanup. The template subscript at 0x0037C560 reaches hinted insertion at 0x0037BC70, insertion at 0x0037B600 and the value construction helper at 0x0037B0B0. That complete helper copies a word at value +0 and a dword at value +4; it does not read or write the two padding bytes. Allocation size was not used to infer the payloads.

The complete find helpers compare signed dword object keys and unsigned word template keys. The object find writes an iterator through hidden return storage and consumes eight stack bytes. The template helper returns a node pointer and consumes four. Both complete erase helpers unlink the node, free it and decrement the count without invoking an element destructor. Together these observations support scalar frame payloads with no element ownership. They do not distinguish the original signed or unsigned payload spelling, or independently prove the payload-specific STL specialization names already in the ledger.

## Compiler experiments and refutation

The new hypothesis was that canonical ID and AI declarations, or visibility of an actual matched callee, could remove the inherited register allocation blocker. The hypothesis was refuted by the measured target output. The raw probes are `baseline-probe.txt`, `object-id-type-probe.txt`, `canonical-ai-overloads-probe.txt` and `visible-computer-query-probe.txt` in `build/0037c310-run/`. Every complete trial source remains beside its raw output. `measurements.json` records parsed measurements and source hashes.

All trials emit the same target shape: 468 bytes against 465 retail bytes, with 262 non-relocation differences beginning at +0x6 and 12 shifted relocation sites. The initial configuration pointer occupies ECX instead of EAX. The global load at retail +0xA9 consequently expands by one byte, and the late AI receiver sequence contains an extra transfer at compiled +0x1B3. The masked equality fraction is 203/468, reproducing the bank's recorded score. Instruction similarity is not acceptance evidence.

The copied computer-control query was marked inline and noinline to preserve an out-of-line call without adding a second strong definition. Its separate probe reproduces its 35-byte retail body modulo relocation slots. Its complete Team accessor was decoded independently. Visibility still leaves the target unchanged. No additional unchanged register spellings were pursued. The mechanical family generator offered a local declaration swap already covered by earlier family searches and a redundant pointer copy after the first mismatch; neither supplied a new supported experiment.

## Checks and reopening condition

The scoped strict byte gate fails in `build/0037c310-run/scoped-byte-gate.txt`. In addition to the byte mismatch, the bank's unsigned template-map find and erase specializations remain unresolved. The byte-divergent relocation diagnostics are not valid call-target measurements; use the complete decoded retail routes instead. This run adds no alias or pin to conceal either failure.

CSV validation, the repository-wide pin consistency check and the existing bank's class gate pass. Their raw outputs are `check_csv-after.txt`, `pin-consistency.txt` and `bank-class-gate.txt` in the task folder. Complete checked-callee outputs are retained there for the target, caller and the helpers used above. No full gate is required for this evidence-only change.

Reopen with independently supported configuration accessor or inline-helper structure that differs from the recorded experiments, or evidence that settles the payload-specific STL identities and motivates a different complete reconstruction. Further equivalent parameter copies, declaration ordering, compiler flags or unconstrained register spelling do not supply such evidence.
