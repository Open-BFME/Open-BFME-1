# SelectionTranslator translation retry

The retry remains partial. The preferred body is banked at `targets/game/reverse/attempts/0x005b8520.cpp`, from `build/selection-005b8520/trial37.cpp`, and measured against the complete 4,578-byte retail extent. It emits 4,566 bytes, has 1,963 differences outside the probe's relocation mask and first differs at +0x34. The repository's size-penalized banking score is 0.5660. No source recovery, ledger change or pin change is claimed. The tested base revision is `1744eb8181af82b07e22687cd5d2993dbbbb8316`; the model is `gpt-6.1-sol`.

## New hypothesis and result

The earlier bank contains the Zero Hour body, which differs substantially from BFME. Current matched neighbors and callees provide BFME field offsets, virtual slots and helper signatures that the donor lacks. The retry hypothesis was that applying those independently checked declarations and BFME branches would improve the measured body. A complete reconstruction that did not improve the original bank's measurement would refute this hypothesis. Trial 00 remeasured the saved body at 4,190 bytes with 3,320 differences and score 0.1053. Trial 37 improves that measurement, but does not establish an exact recovery.

The landed SelectionTranslator constructor and destructor, SelectionInfo implementation, PickDrawableStruct constructor, selection callbacks and Squad compaction source were read directly. The BFME body adds lasso selection, deduplication through a hash table and object redirection. The Squad helper returns a pointer to its existing vector; the donor's vector returned by value is unsuitable. The mouse-release path clears the left-button flag and then enters hover handling. Both terrain-position uses reach the same retail stack storage. A shared position local reproduces that storage.

## Identity and boundary

The owning vtable at VA 0x0110F0E0 names SelectionTranslator. Slot 0 routes through ILT RVA 0x000208F1 to RVA 0x005B8520. The matched constructor at 0x005B7D70 and destructor at 0x005B7BE0 install that vtable. The target receives `this` in ECX, reads one message pointer from the caller's stack, switches on its field at +0x10 and returns with `ret 4`. These facts support `SelectionTranslator::translateGameMessage`; the erroneous addSkillPointsForKill identity is not reused.

The executable stream ends with the complete common epilogue and `ret 4` at 0x005B9638 through 0x005B963A. A nop follows. Thirteen jump-table entries occupy 0x005B963C through 0x005B966F; the 146-byte case-index table occupies 0x005B9670 through 0x005B9701. Int3 padding starts at 0x005B9702. This establishes the 4,578-byte code-and-table extent. `checked_callees.py` passes the 4,380-byte executable-plus-nop extent and reports no outgoing direct branch. Its rejection at the end of the full extent is caused by decoding the case-index data as instructions, not by an omitted epilogue. Raw results are `checked-code.log`, `checked-callees.log`, `decode-005b8520.txt` and `switch.txt` under the task's build folder.

## Container and cleanup evidence

The actual subscript route is ILT 0x00034FB3 to 0x005B7EB0. Its complete body compares a four-byte key at node +4, constructs a zero byte at pair +4 when inserting, and returns a reference to node +8. Its insert helper at 0x005B7CE0 calls ILT 0x00022499, which reaches the complete 23-byte copy helper at 0x005B7670. That helper reads and writes exactly a four-byte field at +0 and a byte at +4. It reads and writes no further payload fields. The allocation size is not used as type evidence. Together with caller object-ID reads at Object +0x74 and byte stores through subscript, this establishes a four-byte object-ID key and a one-byte Boolean payload. The exact C++ key declaration remains unsettled; allocation size and generated template names do not settle enum versus scalar spelling.

The find helper at 0x005B7980 writes a two-pointer iterator through hidden return storage and returns that storage in EAX with `ret 8`. The subscript and insert helpers use ECX receivers and `ret 4`. Their complete bodies and the value-copy helper are retained as decoded text; checked-callee outputs are retained for all 39 direct target helpers and the additional copy/insert extents. Successful decoding checks do not certify every declaration or indirect target.

Retail has two unwind states: state 0 destroys the list at frame offset -0xCC, and state 1 destroys the map at -0x58 before state 0. The compiled candidate has the same predecessors and local offsets. Retail list cleanup reaches 0x000FD1D0, which frees nodes and the sentinel without destroying Drawable pointees. Map cleanup reaches 0x005B7C40, which calls clear at 0x005B79D0 and frees bucket storage; clear frees nodes without a payload destructor. These bodies support nonowning pointer list elements and a trivial map payload. Raw retail and compiled unwind records are `eh-retail.log` and `compiled-unwind.log`. The graph and offsets match, but the compiled destructor symbols still require binding to the independently decoded retail routes.

## Measurements and rejected shapes

Every trial source and unedited probe output is retained in `build/selection-005b8520`. The complete measurement list is `measurement-summary.json`. Scores below use `finish_measure.parse`, including the penalty for extent differences; normalized instruction similarity is not the banking score.

| Trial | Experiment | Emitted bytes | Byte differences | Banking score |
| --- | --- | ---: | ---: | ---: |
| 00 | Saved donor bank | 4190 | 3320 | 0.1053 |
| 03 | Complete BFME reconstruction | 4550 | 3400 | 0.2451 |
| 15 | Shared disposition exit | 4474 | 3226 | 0.2499 |
| 23 | Coordinate conversion and original early return | 4594 | 2951 | 0.3484 |
| 27 | Direct nested member calls | 4582 | 2908 | 0.3630 |
| 29 | Nullable Squad expression | 4578 | 2143 | 0.5319 |
| 32 | Shared terrain-position local | 4566 | 1963 | 0.5660 |
| 37 | Preserve bank names through address-derived ABI views | 4566 | 1963 | 0.5660 |

The bounded EH search performed eight measurements. The non-EH family search performed five measurements and stopped on a plateau. Their original choices, sources and result receipts remain under `build/shape_search`, with paths recorded by `eh-search-path.txt` and `family17-search-path.txt`. Search output and raw family probes remain in the task's build folder. This was a bounded search, not exhaustion of every generated alternative. Changing `/EHsc`, disabling STL exceptions and changing `/Ob1` did not repair the BFME body. Case-local returns worsened its frame. A shared invalidation label, a combined null/assignment condition, an end iterator, altered key spelling and constructor/local-player order did not beat the preferred body. The final two register-lifetime experiments, iterator declaration scope and a member-based object-ID getter, produced unchanged measurements and were stopped.

## Remaining blockers and reopening

The first byte difference at +0x34 is a branch displacement caused by later layout drift. The first substantial normalized instruction discrepancy, excluding table relocations, is at +0x7F1: retail keeps the outgoing message in EBP and the list iterator on the stack, while the candidate spills the message and keeps the iterator in EBP. Additional differences occur in group invalidation, loop alignment and table placement. The candidate is 12 bytes short. Trial 37 and its `probe37.log` are the reproducible partial; trial 32 has the same measured result.

The coordinate conversion view reproduces more of retail's by-value construction, but its source-level type is unproven. The extended PickDrawableStruct storage view has the witnessed 56-byte extent, but is not a canonical BFME declaration. Indirect and virtual targets have not all been independently resolved and checked. These remain blockers to any exact claim even if a future probe matches.

The normal scoped byte verifier was run on a scratch row through `build.verify_functions`, without modifying the ledger. It fails with byte differences and unresolved hash-map constructor, hashtable destructor, subscript and `_Ht_iterator` find symbols, plus unresolved argument, Squad, lasso and terrain declarations. `scoped-gate-raw.log` and `scoped-gate-exit.json` retain the output and failing exit. No pin was invented. The STL symbols must wait for the paused STLport header transition and independent canonical binding. A retry is justified by those declarations, a proven coordinate value type, complete virtual-target evidence or a concrete map-loop lifetime hypothesis that changes the measured discrepancy. Repeating the unchanged register experiments is not justified.

The bank's descriptive names are retained. The repository's text comparison reports no name regressions for trial 37 and for the resulting bank, and the class gate passes for both. The declared-unmatched check rejects the scratch source because it owns no matched ledger row; this is consistent with a banked partial and prevents treating it as a landed source. CSV and pin-consistency checks pass, with raw results in `check-csv-final.log` and `pin-consistency-final.log`. No full gate is required by an evidence-and-bank-only change.

Exactly one verdict row was appended by `re_log.py`, recording 47 elapsed minutes. A subsequent raw probe of the bank repeats the preferred measurement; its output is `probe-banked-raw.log`. The immutable new attempt is `targets/game/reverse/attempt_history/0x005b8520/4b21c6cb3f59fbad6c5f733c06cb005f43efe5c735c83eb8ce874c96fe250498.json`. The original bank bytes are preserved in `targets/game/reverse/attempt_history/0x005b8520/abd4c001a145571f6ef8cc3aa5c4605ae650082c6ed8b9530e97d1403a9aa597.json`; both archive digests were checked against their source bytes. All experiments remain uncollected in the approved build locations.
