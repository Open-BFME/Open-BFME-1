# Comparator at RVA 0x00752B80

This is a measured partial reconstruction, not a recovered source identity or an exact conversion. The tested revision is `20f64813a005b14e1c5326631287c2ea4bb1f878`. The model is `gpt-6.1-sol`. The existing generated ledger row and all symbol pins remain unchanged.

## Retry hypothesis

The previous verdicts treated an authentic comparator owner as a prerequisite and retained no body at this address. The current ledger supplies the clean 128-byte `Q4Sort00751F50Record::compare` helper and clean insertion and median callers. A complete decoded ABI permits an address-derived layout view even when the original owner is unknown. The experiment therefore reconstructs the field comparisons and tests parameter types, return widths, helper visibility and inline record comparison before treating register or x87 allocation as the remaining obstacle. This hypothesis would fail if the complete callers passed a different representation, the helper used different output widths, or a target branch reached code outside the claimed extent. Those checks did not refute the decoded ABI. None of the compiler trials recovered the retail bytes.

## Boundary and control flow

`build/target-00752b80/retail-target.txt` decodes the complete body and following padding from the retail baseline. The body starts at RVA 0x00752B80, and its final three-byte `ret 8` starts at RVA 0x00752D4E. Padding begins at RVA 0x00752D51. All twelve returns pop the two stack arguments. Every conditional or unconditional branch lands on an instruction inside the 465-byte body. There are no indirect calls, tail calls, exception-registration instructions or cleanup funclets in this target. The checked callee inventory is retained in `build/target-00752b80/checked-target.log`.

The branches at target offsets +0x8A and +0xAE jump directly into shared epilogues at +0x1C7 and +0x14E. They preserve flags from the preceding unsigned pointer comparison and signed output comparison, respectively. The +0x1C7 destination is after the final pointer comparison, rather than its beginning. Reading either destination as a new comparison would change the semantics. `build/target-00752b80/cfg-audit.json` retains every return and branch destination for the target, the helper, both helper callees and two complete callers.

## Argument and callee evidence

The entry reads the second stack word into EBX and the first into EBP, then dereferences each directly. Incoming ECX is overwritten before it can be read as a receiver. The observable ABI is two four-byte record pointers, callee cleanup of eight bytes and a result in AL. There is no hidden return storage or receiver adjustment. The complete 65-byte insertion caller at RVA 0x00753460 and 130-byte median caller at RVA 0x00753340 load four-byte array elements, push them as the two arguments, set ECX to their comparator storage, call ILT RVA 0x0002952D and test only AL. The decoded ILT jumps to this target. Their disassembly and checked inventories are retained as `retail-caller-insert.txt`, `retail-caller-median.txt`, `checked-caller-insert.log` and `checked-caller-median.log` in the same build folder. The median log includes padding beyond its independently checked 130-byte extent.

The target's sole direct call is through ILT RVA 0x0001938A to RVA 0x00751F50. The target passes its left nested record as ECX, its right nested record as the first stack argument, and addresses of two four-byte output slots as the remaining arguments. The complete helper clears both output integers, reads record pointers at +0x08 and +0x14, uses signed `idiv` results for the outputs and returns a normalized byte with `ret 12`. Its complete calls resolve through ILTs to `Drawable::getID` at RVA 0x004116B0 and `Rva00765AC0::ready` at RVA 0x00765AC0. The former returns the four-byte field at +0x100. The latter scans ten pointer slots at +0x04, checks the byte at +0x40 and bit 5 of the word at +0x38, and has two complete return paths. All helper bodies, ILTs and checked callee inventories are retained under `build/target-00752b80/`.

The reconstruction reuses the helper's existing class, member and declaration names. Trials 06 and 07 make its authentic definition visible as an inline, non-inlined member, rather than creating a second strong definition. `probe-visible-helper.log` independently verifies that visible helper's 128-byte masked instruction body. Its visibility does not change either target trial's emitted bytes. The final candidate declares the already-owned helper externally.

## Layout and identity limits

| View | Complete observed accesses |
|---|---|
| Outer record | Unsigned four-byte key at +0x00, nested record pointer at +0x04, signed four-byte ordering field at +0x08. A zero key bypasses all nested reads. |
| Nested record | Drawable pointer at +0x08, state pointer at +0x14, and two entries beginning at +0xDC with a stride of 28 bytes. |
| Each entry | Unsigned four-byte field at +0x00, float at +0x04, signed four-byte fields at +0x14 and +0x10 in that comparison order, and a byte at +0x18. The signed fields and byte are skipped when the first field is zero. |
| Drawable view | Float at +0x1F8, compared before the helper call. The name oracle has no witnessed member at that offset; `name-drawable.log` retains its answer. |

The float totals add the first entry's float to the second entry's float when the second entry's first field is nonzero, or to literal `0.0f` otherwise. The first float ordering and final float ordering both implement left less than right, including an unordered comparison returning false. Equal totals fall back to the nested record pointer order. The byte-field ordering returns whether the left byte is nonzero; declaring that field as a C++ `bool` omitted retail's normalization, so the retained view uses `unsigned char` with an explicit nonzero test.

These are offset and ABI views, not a proof of the native record class, pointer target identities for the entry keys, complete object sizes or ownership. Four-byte pointer array elements are proven by the complete callers and target dereferences; no aggregate STL payload type is inferred from an allocation or donor. There is no value constructor or exception cleanup used as evidence in this attempt. No authentic comparator class was found in the adjacent landed destructor or the inspected Zero Hour model-draw source. Existing comparator aliases disagree about argument spelling and do not prove the original declaration. The retained `Q4Sort00755050` name preserves the existing address-derived comparator name. Its unsigned-char return is an ABI-compatible source view; the caller evidence cannot distinguish native `bool` from `unsigned char`. No new pin or STL ledger claim is proposed.

## Measurements and remaining obstacle

Every trial source and its unedited probe output is retained under `build/target-00752b80/`. `measurements.jsonl` records the compiler measurements after the initial trial, and `probe-01.log` retains that initial measurement with its PowerShell stderr wrapper. Trial 28 is the final candidate with corrected symbol comments. It emits 448 bytes against the verified 465-byte retail extent. Probe reports 368 overlapping non-relocation differences starting at +0x00, and the candidate omits the last 17 retail bytes. The bank score uses the repository's measured quality formula, which penalizes size error twice; normalized instruction-shape similarity of 0.914 is a separate diagnostic, not a bank score.

The first raw mismatch is the callee-saved register choice and first argument load at +0x00. Retail keeps the parents in EBX and EBP; the candidate uses ESI and EDI. The normalized instruction stream agrees until retail +0xCE, where retail spills the right nested pointer into an argument home. The candidate keeps the nested records in registers. Other structural residues are the right entry cursor's construction at +0xD8, parent and second-entry reloads at +0x111, +0x119 and +0x173, and the final x87 exchange, comparison branch and pointer reload near +0x19E through +0x1C1. Three object relocation positions do not line up with retail instructions, so the raw differing-byte count is diagnostic rather than evidence that those relocation targets are wrong.

| Rejected hypothesis | Raw measurement |
|---|---|
| Existing bool return and integer parameters reproduce the body directly | Trial 03 emits 453 bytes with 426 overlapping differences. |
| Pentium 4 scheduling fixes the baseline | Trial 02 emits 443 bytes with 418 differences and a worse normalized instruction shape. |
| Reversing independent local declarations helps | Trial 04 duplicates trial 03's emitted result. |
| Pointer parameters alone fix the body | Trial 08 duplicates the unsigned-char integer-parameter trial 05's 434-byte result. |
| Visible authentic helper supplies missing memory-effect knowledge | Trials 06 and 07 duplicate their respective external-helper results; the visible helper itself matches. |
| Direct byte return is equivalent to retail's byte normalization | Trial 11's explicit normalization changes the body to 439 bytes and improves normalized shape, but is still unequal. |
| Disabling global optimization, optimizing for size, or assuming no aliasing fixes the shape | Trials 12, 13 and 20 emit 710, 378 and 432 bytes, respectively, and lose structural agreement. |
| Cursor loop is the original spelling | Indexed trial 17 improves on cursor trial 16 from 387 to 368 overlapping differences. Both emit 448 bytes. |
| Bool return remains equivalent for compiler shape after the layout corrections | Trial 18 emits 470 bytes with 427 differences; the bool wrapper around a byte-return inline body in trial 23 emits 492 bytes with 433 differences. |
| Float equality branch polarity is the remaining lever | Trial 21 emits 439 bytes with 409 differences. |
| Separate inline record comparison changes caller scheduling | Trial 22 retains the 448-byte body and improves normalized shape to 0.914, but does not reduce the 368 raw differences. |
| Separate float accumulation or reference views of entries recover the remaining reloads | Trials 25 and 26 duplicate trial 22's instruction and relocation result. |
| Nesting the signed fields and byte in a subrecord establishes the missing cursor shape | Trial 27 emits 448 bytes with 389 differences and worse normalized shape. No native nested type is claimed. |

`scoped-gate.log` retains the real scoped byte gate against an in-memory row, without changing the ledger. The retail baseline check passes; the assigned target fails byte comparison. No full gate is required for this unlanded bank and evidence-only change. The attempt should reopen on independent evidence for a native record accessor, parameter declaration or inline comparison that explains the retained parent lifetimes and spill. Repeating the same local ordering, visibility, float accumulation or reference spelling has no measured justification.

The repository bank tool measured and saved the candidate at `targets/game/reverse/attempts/0x00752b80.cpp` with quality 0.1355. Its retained archive is named by the source hash under `targets/game/reverse/attempt_history/0x00752b80/`. `probe-bank.log` independently rechecks the saved file at the explicit retail extent. `check-csv-after.log`, `pin-consistency.log` and `class-gate.log` pass. `declared-unmatched.log` fails because the partial bank defines the assigned comparator without a matched ledger row; the inline helper's absence marker is accepted. This source is retained evidence and must not be treated as a landed game translation unit. No whitelist, baseline, shared header or policy was changed to suppress that result.
