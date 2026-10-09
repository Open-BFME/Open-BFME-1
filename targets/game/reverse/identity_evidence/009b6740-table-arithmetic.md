# 0x009B6740 table-builder reconstruction

## Result and next experiment

This is a partial reconstruction, not an exact recovery. The saved scalar body corrects the arithmetic errors in the earlier bank. Its strict scoped byte gate fails. Reopen only with a source-level explanation for the retail frame and pointer lifetimes, or independent original codec source. Repeating initialization-order permutations without new evidence is not justified.

The tested revision is `210b5e5782ac44724049860ccef50e43eda6d283`. The actual model is `gpt-6.1-sol`. The preferred candidate before preservation is `build/rva009b6740-run/best.cpp`. Its declaration names and the existing address-derived `Rva009B6740BuildTable` name are retained. No ledger row or symbol pin is added or changed.

## Boundary and ABI evidence

The complete decoded retail extent is `[0x009B6740, 0x009B6942)`. Its only return is the `ret` at `+0x201`, after restoring EDI, ESI, EBP and EBX and releasing the 0x50-byte frame. Every conditional branch and jump stays inside the extent; there are no direct or indirect calls, tail jumps, exception handlers, container helpers or unwind cleanups. The following bytes are alignment padding. `checked-target.log` retains the checked-callee result and `retail-decode.log` retains every instruction.

The entry reads one four-byte argument from entry ESP+4. The complete caller at `0x009B6A30` keeps its original context argument in EBX, pushes EBX at `0x009B6B97`, directly calls this body at `0x009B6B98`, and adds four to ESP afterward. The caller does not use EAX as a return value. This supports the existing `void __cdecl Rva009B6740BuildTable(unsigned char *ctx)` declaration, with no receiver adjustment or hidden return storage. The matched caller source and its passing scoped byte gate independently support the existing address-derived identity. They do not prove an original vendor function or class name.

The landed neighbours `Rva009B64A0BuildTone.cpp`, `Rva009B6950DecodeScale.cpp` and `Rva009B6A30LoadTables.cpp` were read. Their declarations and compiler flags supply no new class layout that resolves the previous register-allocation blocker. No named Zero Hour twin was found. The target has no callees from which further layout or type evidence could be obtained.

## Arithmetic and type evidence

All context inputs are zero-extended byte loads and all outputs are byte stores. The temporary weights occupy ten dwords and are multiplied by 100. The ratio uses signed division of promoted byte values; all nine branch-table quotients use unsigned dword division. The containing decoder class is unknown. `Rva009B6740Work` is an inherited local reconstruction type, not a claimed decoder layout. The unused declaration remains in the bank to preserve its established names.

For plane p and row j, the ten input weights come from `ctx[0x72C + 20*p + i]`, with weight j replaced by zero. Retail forms this address using ESI=`ctx+0x736+j+20*p` and EDX=`-10-j`. Its input region comprises three blocks of two ten-byte rows, also witnessed by the complete loader. The ratio destination is `ctx[0x77C + 10*p + j]`; the nine branch bytes begin at `ctx[0x7A4 + 90*p + 9*j]`. These byte-array views do not establish an owning class.

| Output | Decoded numerator before multiplying by 255 | Decoded denominator before adding 1 |
| --- | --- | --- |
| Branch 0 | w4 + w3 + w2 + w0 | sum of all ten weights |
| Branch 1 | w2 + w0 | w4 + w3 + w2 + w0 |
| Branch 2 | w7 + w1 | w8 + w9 + w6 + w5 + w7 + w1 |
| Branch 3 | w0 | w2 + w0 |
| Branch 4 | w3 | w4 + w3 |
| Branch 5 | w1 | w7 + w1 |
| Branch 6 | w6 + w5 | w8 + w9 + w6 + w5 |
| Branch 7 | w5 | w6 + w5 |
| Branch 8 | w8 | w8 + w9 |

Each branch stores the low byte of `1 + numerator*255/(denominator+1)`. The ratio stores `255 - history[0]*255/(history[0]+history[-10]+1)`. The earlier bank instead used its changing outer offset for the ratio, used the row index for two subtree divisors, and substituted w0 for w5 in the final branch pair. The corrected scalar body retains the weight-pair divisor from its decoded first use.

## Measurements and rejected shapes

Raw probe output is preserved unchanged under `build/rva009b6740-run/`. This table is generated from those logs. Overlap differences exclude missing or excess bytes, so the total mismatch column includes them. Quality is the repository finish_measure diagnostic, which additionally penalizes size drift; it is not acceptance.

| Trial | Emitted bytes | Overlap differences | Missing bytes | Excess bytes | Total mismatch | First difference | Quality |
| --- | ---: | ---: | ---: | ---: | ---: | --- | ---: |
| baseline | 467 | 438 | 47 | 0 | 485 | +0xA | 0.0000 |
| semantic | 478 | 441 | 36 | 0 | 477 | +0xB | 0.0019 |
| native-lifetimes | 538 | 472 | 0 | 24 | 496 | +0x2 | 0.0000 |
| scalars | 504 | 448 | 10 | 0 | 458 | +0x2 | 0.0895 |
| induction | 513 | 496 | 1 | 0 | 497 | +0x2 | 0.0311 |
| typed-view-v2 | 476 | 452 | 38 | 0 | 490 | +0x2 | 0.0000 |
| active-pointers | 490 | 461 | 24 | 0 | 485 | +0x2 | 0.0097 |
| parts | 522 | 469 | 0 | 8 | 477 | +0x2 | 0.0564 |
| parts-active | 491 | 469 | 23 | 0 | 492 | +0x2 | 0.0000 |
| generated-000 | 478 | 441 | 36 | 0 | 477 | +0xB | 0.0019 |
| generated-001 | 478 | 435 | 36 | 0 | 471 | +0xB | 0.0136 |
| generated-002 | 478 | 441 | 36 | 0 | 477 | +0xB | 0.0019 |
| generated-003 | 478 | 435 | 36 | 0 | 471 | +0xB | 0.0136 |

The scalar trial is selected by the repository measurement. Naming the decoded w3+w4 intermediate while retaining the full work record created extra spills. Flattening the corrected work record improved the measurement but retained a 0x4C frame, a rederived history pointer, and different output-pointer materialization. Deriving the negative offset from the row failed to improve it. An explicit decoder byte-array view, active-pointer snapshots, a contiguous subtree/weights record and their combination all failed to recover the retail shape. The four bounded generated store-order trials used corrected arithmetic and supplied no better candidate. Their complete sources and manifests are in `build/shape_search/e41c9fbd67004c21aa05600b586456e5/`.

The compiler listings `semantic.cod` and `scalars.cod` show that the earlier 0x50 frame came from allocating the entire artificial work record. The scalar listing instead has a 0x4C frame and weights at ESP+0x34, while retail uses weights at ESP+0x38. The candidate first differs in the frame-size byte at +0x2. This is still a frame and pointer-lifetime problem, not a near-exact register residue.

## Validation and limits

`scoped-byte-gate.log` records the normal strict build verifier failing the candidate through an in-memory scoped row, without changing the ledger. `caller-byte-gate-v2.log` records the matched loader passing the source, function, string, constant, DIR32 and body guards. `pin-consistency.log`, `name-regression-files.log` and `class-gate.log` pass. This revision of the name-regression CLI accepts revisions rather than file paths, so the explicit file-pair check invokes its unmodified `regressions` function. The failed file-path CLI invocation is retained in `name-regression.log`.

`declared-unmatched.log` refuses the scratch body because it owns no matched row. That is expected for a bank and is not bypassed or whitelisted. No game source, shared header or shim changes, so a full gate is not required for this bank.

`final-semantic-validation.log` records the retail instruction runner and the preservation candidate agreeing with the independently indexed arithmetic model for 100 seeded random contexts. `semantic-validation-v2.log` records the old bank failing all 100 cases while the corrected candidates pass. This is finite diagnostic evidence from a scratch instruction interpreter, not native execution or a byte-match certificate. The first model incorrectly started the input rows at 0x726; tracing exposed that subtraction error, which was corrected to 0x72C. Its unedited failing log and original model remain as `semantic-validation.log` and `emulate-model-v1.py`.

The retail bytes have SHA-256 `b188ce5514e9620c4c670ecb10defa5554693466c8fbd7ce547fb125bf68f5fc`. The pre-bank saved body has SHA-256 `80e5b165fb099ff9cbfe1258cdd253ceb019bc1b3e7972c6341fbcdba45afc4d`. The preservation candidate has SHA-256 `a57fe513ca6786a01b23f4d254f98cf4fcea7b7c8b0bb142a0365a1eb08a742f`.

The remaining blocker is `regalloc/frame-and-pointer-lifetimes`. No boundary, callee or argument ambiguity remains for the existing opaque identity. Original vendor ownership and the original declaration spelling remain unverified and are not used as real-name claims.

The repository banking tool selected `targets/game/reverse/attempts/0x009b6740.cpp` at measured quality 0.0895 and archived the original bank and the new submission. Exactly one partial verdict row was appended. The final bank probe reproduces 504 emitted bytes and 448 overlap differences at the proven 514-byte extent (`bank-probe.log`). The original bank CRLF line endings were restored after the tool generated its metadata; `final-audit.log` verifies them and confirms functions.csv, symbols.csv and deleted_rows.csv remain byte-identical to the tested revision. The final CSV check passes (`final-check-csv.log`), and the preserved bank passes the class gate (`bank-class-gate.log`). All named raw logs are under `build/rva009b6740-run/`.
