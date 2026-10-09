# 00896AF0 ownership retry

## Result and reopening condition

Tested base revision: 4d8c08e248d9a4d34fb6b2c39c1826804632d441. Model: gpt-6.1-sol. The complete candidate emits 1240 bytes against 1272 retail bytes, with 861 reported non-relocation differences and the first difference at +0x21. Its finish_measure quality is 0.2728. This is a partial reconstruction, with no source recovery or identity claim. The byte gate fails. Raw evidence and each unchanged trial source remain in build/896af0-retry/.

Reopen when independent source or compiler-context evidence explains the comparison Boolean spill and saved-receiver slot, or when the missing lookup and registration declarations have been independently established. The earlier register and temporary lifetime variants below should not be repeated unchanged. The top-level volatile input pointer is an experimental lifetime constraint, not a proven retail declaration. The compiled exception cleanup table has not been verified against every retail state and remains a landing blocker.

## New hypothesis and its test

The old blocker named the entry constructor ABI as wrong. The current ledger now supplies ??0Gen_00895670@@QAE@VBfmeRefVGO@@PAX@Z and game/GameEngine/Source/Common/BfmeHolder95670.cpp. Its independent evidence is targets/game/reverse/identity_evidence/0x00895670-byvalue-reference.md. The retry hypothesis was that this corrected by-value reference, together with the actual manager result width and unowned iterator, would permit a complete source body. It would be refuted by decoded helpers using different fields or cleanup, or by compiler experiments producing no improvement over the original once omitted bytes were penalized. The complete experiments improve that measured ranking; they do not match retail.

## Boundary, ABI and ownership evidence

The complete target decode is build/896af0-retry/target-disasm.txt. Its only return is ret 8 at +0x4F5, ending at +0x4F8. Its conditional branches stay inside the requested extent. checked-target.log retains the checked direct-call inventory. The full callers at 00891E70 (192 bytes) and 008AE600 (363 bytes) construct a four-byte refcounted string argument, push a separate string-wrapper pointer, and place the receiver in ECX before the aligned call. Their raw checked inventories and complete decodes are in helpers/. The function returns no value used by those callers.

The complete 00895670 constructor retains the pointer supplied by the by-value reference, writes the entry count at +0, owned object at +4, key at +8 and flag byte at +0xC, then destroys the argument reference before ret 8. The complete 00895260 destructor reads object kind at +8, dispatches ownership for fields +0xC, +0x10 and +0x14, and drops the pooled string at +4. The 00895A00 build helper constructs all six object DWORDs through +0x14 and writes only one DWORD to its hidden return buffer. Allocation sizes alone were not used as type evidence.

The complete 008951B0 find helper returns an unowned node through a hidden return pointer on both return paths. It traverses next at node +4 and compares the requested key with entry +8 after loading the entry pointer from node +0. The target subsequently retains that entry, not the iterator. The old bank incorrectly gave the iterator an owning destructor and treated the manager build result as sixteen bytes.

The complete 00895950 lookup uses the same four-byte owned-reference result convention and ret 8. The complete 00896390 registration consumes one four-byte owned reference and ends at its shared ret 4. The complete 0089D890 table helper takes the string-wrapper pointer and value pointer and ends at ret 8. All three remain generated ledger bodies; their names do not independently establish source ownership.

Virtual calls are separate from direct-call inference. The known BfmeNestedBE constructor installs vtable 01135DB0 and writes fields through +0x60. Slot 0 reaches 008C3E90 and increments the packed count; slot 1 reaches 008C3EC0 and decrements it with an OnZero virtual call. Slot 6 reaches 008C4200, reads receiver +0x50, returns the table view at +0x10 and takes no stack arguments on either return path. The two pushes preceding the slot-6 call remain for 0089D890. The old bank incorrectly assigned them to both calls. The provider view therefore places its field at +0x50 after a four-byte vptr. Existing bank spellings destroy and release are retained, without claiming those spellings describe semantic identities.

The target unwind map in eh-target.txt contains ten states. It distinguishes the incoming string, result reference, two manager temporaries, retained entry, clone allocation and the two final entry allocations. Clone failure frees 100 payload bytes through 00891650, whose complete body frees the eight-byte header too. Entry failure frees sixteen bytes through the six-byte 00894D50 import thunk to the sized-free slot. The candidate keeps these separate allocation contracts. Its entry-delete import declaration is provisional, and its emitted unwind helpers still require comparison before landing. The canonical direct cleanup declaration now uses Rva008C3F10Value::cleanup(char), as decoded in the complete 701-byte helper and declared in AptCIH.cpp.

Complete checked inventories and decoded instructions for 28 target helpers and four additional helper/caller extents are retained under helpers/. A successful checked_callees invocation alone is not a boundary or identity certificate. Source names remain those of the old bank or existing pinned declarations. The EA screening label AptLinker::Load was not independently established in this run; the address-derived tracker name remains.

## Measured experiments

The table is generated from unedited probe outputs using finish_measure.parse. Quality includes twice the size error. Normalized instruction similarity is a separate diagnostic and is not byte equality.

| Raw probe | Emitted bytes | Reported differences | First offset | Measured quality |
| --- | ---: | ---: | ---: | ---: |
| 00-original-raw.log | 831 | 672 | +0x17 | 0.0 |
| 01-complete-raw.log | 1310 | 1036 | +0x1C | 0.1258 |
| 02-probe.log | 1279 | 1029 | +0x1C | 0.18 |
| 03-probe.log | 1295 | 1024 | +0x1C | 0.1588 |
| 04-probe.log | 1252 | 1005 | +0x1C | 0.1785 |
| 05-probe.log | 1261 | 1018 | +0x1C | 0.1824 |
| 06-probe.log | 1254 | 919 | +0x21 | 0.2492 |
| 07-probe.log | 1255 | 932 | +0x17 | 0.2406 |
| 08-probe.log | 1283 | 1023 | +0x17 | 0.1785 |
| 09-probe.log | 1254 | 919 | +0x21 | 0.2492 |
| 10-probe.log | 1247 | 925 | +0x21 | 0.2335 |
| 11-probe.log | 1247 | 925 | +0x21 | 0.2335 |
| 12-probe.log | 1240 | 861 | +0x21 | 0.2728 |
| 13-probe.log | 1248 | 913 | +0x21 | 0.2445 |
| 14-probe.log | 1240 | 861 | +0x21 | 0.2728 |
| 15-probe.log | 1252 | 918 | +0x21 | 0.2469 |

The original bank omits the retag and registration tail. Trials add complete control flow, correct ownership and widths, common exit handling, complete string-header comparison, pointer lifetime variants, typed payload ownership, copy-contract changes and visible increment/decrement helpers. The best complete shape is retained rather than the smaller fragment. Trial 13 copies the exact matched counter source spelling and worsens the byte distance. Trial 14 uses the canonical cleanup declaration without changing the emitted body. Trial 15 forces allocation inlining, removes an unexplained allocator call, but worsens byte distance and is retained as an alternative.

EH search output is eh-search-raw.log, with eh-choices.json and eh-result.json. It tries throw specifications and EHsc; suppressing the manager-assignment temporary state is rejected because retail records that state. Copy and independent-store choices are retained in family-all-choices.json and family-safe-choices.json, with family-search-raw.log and family-result.json. The generated allocation/store swap was excluded because it writes through the old node before allocating the replacement. Accepted choices produced no byte improvement. All generated trial sources remain at the directories recorded in the search-result JSON files.

The scoped gate raw output is scoped-gate.log. It reports unresolved ??2BfmeNestedBE@@SAPAXI@Z, ?rva00895950@Rva00893030Manager@@QAE?AVBfmeRefVGO@@PAVBfmeStrVKI@@@Z and ?rva00896390@Rva00896AF0Tracker@@QAEXVBfmeRefVGO@@@Z, in addition to the byte mismatch. No pin was invented and no ledger or shared header was changed. The ordinary allocation helper exists in the candidate TU but retail inlines it; trial 15 shows the inline alternative. Class-gate passes for the candidate. Declared-unmatched correctly rejects using this unmatched scratch candidate as a source recovery. No full gate is required for bank and evidence changes.

Claim tools were not invoked because their claim operation writes Git refs and contacts the remote, both forbidden for this isolated worker. The coordinator assignment supplies the exclusive target scope. All Git operations in this run were read-only.

## Preserved bank and final checks

The repository banking tool selected targets/game/reverse/attempts/0x00896af0.cpp at its measured score and archived both the original bytes and the complete candidate. Exactly one partial verdict was appended. bank-record.log retains the tool output; record-receipt.json records the clock and model. The final candidate uses the retained m_bfmeNode spelling in its added reference wrappers. final-candidate-probe.log confirms that preserving that spelling leaves the measured output unchanged.

check-csv-final.log and pin-consistency.log pass. class-gate-bank.log has a successful exit with no findings. name-regression-body.log passes the repository's name_regression.regressions comparison of the exact original and new bodies. The revision-based CLI cannot inspect an unstaged working tree; the coordinator must run the normal hook comparison after staging. bank-scoped-gate.log fails on the saved bank with the same unresolved declarations and byte mismatch. The declared-unmatched check is retained as declared-unmatched.log and fails for the unlanded scratch body; it is not a claimed source recovery. No full gate was run because this change only banks an attempt and its evidence.
