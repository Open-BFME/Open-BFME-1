# RVA 0x00363050 string and pair update

The retry improves the saved reconstruction but does not recover an exact body. The preferred bank keeps the address-derived owner and the saved operation and field names. The remaining blockers are the pair temporary lifetime and the scale's DIR32 binding. Reopen with evidence for the native pair storage or a source shape that retains its two stack writes without adding a call; repeat both strict byte and reference verification.

## Hypothesis and independent evidence

The current landed lookup at RVA 0x00363360 supplies the same record stride, field+0x10 getter and length-aware ASCII comparison. Unlike the old bank, its source uses the native vector access expressions and reads the other string first. The hypothesis was that these access expressions and the condition temporary's lifetime caused the saved frame and comparison mismatch. It would be refuted if the measured shape stayed unchanged. Trials 01, 03 and 07 changed it; splitting the comparison overload alone did not. Donor files read directly were Rva00363360LivingWorldEntryFind.cpp, Rva003631D0LivingWorldEntryFind.cpp, NetworkStringGetterIdentities.cpp and BfmeOwnVUM_ctor.cpp. The Zero Hour AsciiString comparison uses strcmp and is not the BFME length-aware implementation, so no Zero Hour identity is claimed.

`tools/eligibility.py` identifies the current 307-byte gen-dump row as open work. The row and all explicit attempt records are retained in `build/rva00363050/session_target.log`. The four earlier verdicts include two copies of the same partial evidence. No reservation or synchronization was performed by this worker.

## Boundary and ABI

The complete target at 0x00363050 ends at 0x00363183 with `ret 0x10` at +0x130; the following bytes are INT3 padding. Every conditional branch stays within the extent. The zero-count branch joins the epilogue at +0x12B, the nonmatching-string branch goes to the next-iteration block at +0xFC, and the back edge returns to +0x30. There is no outgoing tail jump, indirect call, virtual call or exception-registration frame in the target. Its ECX receiver and four stack slots are a name reference, signed 32-bit duration, reference to an eight-byte value, and a flag whose low byte is copied. It returns no observed value. The exact boundary and complete helper exits are in `boundary_checks.log` and the full instructions are in `decode_complete.log`, both under `build/rva00363050/`.

The raw caller screening hit was checked on an instruction boundary within the completely decoded 300-byte caller at 0x003C2100. Its call at 0x003C21D2 reaches ILT 0x000191E1, wrapper 0x003838A0 (adds 0x170 to ECX), ILT 0x0002A419, then the target. The earlier push before 0x003A3E90 belongs to the following selector call, not a hidden return argument to that niladic helper. The selector at 0x003C1EE0 returns a signed selection in EAX and fills a two-word output. Its complete 432-byte body includes the null-candidate output bits 1.0f and 0.0f. Its actual pair-filling helper at 0x003BEF70 was decoded over all 120 bytes: it reads both returned words and performs x87 subtraction and single-precision stores to output offsets 0 and 4. This independently establishes two float payloads. The original integer pair is replaced with the canonical Coord2D layout, retaining Rva00363050Pair as a source alias. This is an ABI view; it does not prove the original nominal class spelling. Full caller, selector and value-helper evidence is in `caller_evidence.log`, `select_decode.log`, `pair_decode.log` and their checked-callees logs.

The target's range is read at receiver offsets 0x18 and 0x1C and divided by the witnessed 0x58 stride. No record allocation, insertion, record construction or whole-record copy occurs here. The declaration is a partial record view of the accessed fields, not a claim to have reconstructed all record ownership. The comparison getter uses ILT 0x0001897B to 0x00361960. Its complete 32-byte body copies only the handle at record+0x10 through 0x00887B60 and returns hidden storage in EAX with `ret 4`. The complete 121-byte sharing constructor reads the source handle, writes the receiver handle and increments the referenced count. The complete 134-byte release helper decrements that count, frees the buffer at zero and clears the handle. The target reads the unsigned-short length at buffer+4 and text at buffer+8. The canonical StringBase header supplies the same layout. No scalar-versus-pair conclusion was taken from an allocation size or donor name.

The matching-name arm clears record+0x20, multiplies the signed duration by the float at VA 0x010E8F14, converts through the complete 117-byte __ftol2 body and stores the low 32-bit result at +0x24. It copies the two payload words to +0x3C and +0x40, writes them again to stack+0x1C and +0x20, then copies the flag to record+0x4C. All those writes are retained in the decoded evidence. The unknown owner remains Rva00363050Owner; the zero-argument Gen00363050::handle pin is not used as ABI evidence.

## Measurements and rejected shapes

The table is generated from the unedited probe outputs at retail size 307. Score is tools/finish_measure.py's size-penalized quality, not instruction similarity or a hand estimate. Each variant is a compiler experiment, not a runtime test. `measurements.json` also retains the preferred source SHA-256, relocations and every differing offset, including bytes absent from the shorter body.

| Probe log under build/rva00363050 | Emitted bytes | Non-relocation differences | First difference | Bank quality |
|---|---:|---:|---:|---:|
| probe00_saved.log | 294 | 251 | +0x2 | 0.0977 |
| probe01_donor_compare.log | 286 | 232 | +0x2 | 0.1075 |
| probe02_pair_return.log | 287 | 234 | +0x2 | 0.1075 |
| probe03_vector.log | 288 | 192 | +0x2 | 0.2508 |
| probe04_split_compare.log | 288 | 192 | +0x2 | 0.2508 |
| probe05_pair_copy.log | 288 | 192 | +0x2 | 0.2508 |
| probe06_inline_setters.log | 289 | 199 | +0x2 | 0.2345 |
| probe07_expression.log | 299 | 78 | +0x2 | 0.6938 |
| probe08_pair_lifetime.log | 299 | 78 | +0x2 | 0.6938 |
| probe09_float_pair.log | 299 | 78 | +0x2 | 0.6938 |
| probe10_canonical_string.log | 299 | 78 | +0x2 | 0.6938 |
| probe11_return_setter.log | 299 | 85 | +0x2 | 0.671 |
| probe12_addressed_pair.log | 299 | 78 | +0x2 | 0.6938 |
| probe13_pair_object.log | 318 | 88 | +0x2 | 0.6417 |
| probe14_pair_return_lifetime.log | 301 | 85 | +0x2 | 0.684 |
| probe15_named_return.log | 299 | 78 | +0x2 | 0.6938 |
| probe16_witnessed_spill.log | 312 | 92 | +0x2 | 0.6678 |
| probe17_outer_pair.log | 299 | 78 | +0x2 | 0.6938 |
| probe18_raw_snapshot.log | 312 | 92 | +0x2 | 0.6678 |
| probe19_snapshot_lifetime.log | 303 | 86 | +0x2 | 0.6938 |
| probe20_pair_temporary.log | 299 | 78 | +0x2 | 0.6938 |
| probe21_trivial_dtor_return.log | 300 | 91 | +0x2 | 0.658 |
| probe22_bound_scale.log | 299 | 84 | +0x2 | 0.6743 |
| probe23_scale_lifetime.log | 299 | 84 | +0x2 | 0.6743 |
| probe24_native_duration.log | 299 | 84 | +0x2 | 0.6743 |
| probe_best.log | 299 | 78 | +0x2 | 0.6938 |

The preferred measured body is `build/rva00363050/best.cpp`. Its comparison instruction sequence now agrees through the release call, apart from incoming stack displacements and the frame. Retail reserves 0x14 bytes; it reserves 0x0C. The first additional instruction-structure difference is at +0xD2, where the by-value pair setter lets the compiler prepare the pair load before the duration-result store. The two retail snapshot stores at +0xEC and +0xF4 are absent. The shifted loop and epilogue then account for much of the byte-distance total. There is no unresolved direct call in the strict scoped comparison.

Rejected pair hypotheses were a value-return assignment, nontrivial copy construction, by-value setters with nontrivial copies, an addressed block local, a function-scope local, a named return value, an explicit argument temporary, and returned assignment values with trivial and nontrivial destruction. Nontrivial destruction introduced an extra call that retail does not have. Volatile pair snapshots were diagnostic controls and were worse; they are not in the preferred bank. The generated frame-array family alternative also regressed. `family_search.log` and `compiler_search.log` preserve the bounded searches and their raw manifests remain under `build/shape_search/95150c83da9d456f80348d818dabf3ae/` and `build/shape_search/eed4520135894b9691e2fc3d828896b1/`. /Ob1 reproduced the same body; /Og- and /O1 regressed. No assembly, new pin, new STL ledger row or baseline change was used.

## Reference binding and gates

The preferred literal scale has an independent binding failure: DIR32 +0xC9 emits __real@40a00000, which the current tree records at VA 0x01075344 rather than the target's VA 0x010E8F14. The float bytes at the target address are 0000A040. The existing pin and DIR32 record name that address g_bfmeKUKC, and the landed duration helper 0x003609C0 in BfmeConv1335.cpp reads that name. Its complete body was independently decoded and checked. Trial 22 uses the existing float declaration and passes the string, constant, DIR32 address and DIR32 consistency checks. It has a slightly worse FILD/receiver-load schedule. An explicit float local and inclusion of the landed helper in trials 23 and 24 both reproduce that result. Keep this correctly bound alternative in `build/rva00363050/trial22_bound_scale.cpp` when reopening; a literal-only byte result cannot pass the reference gate.

Tested revision: c5c53d331c52664b4e2a4440f1d1ad603549e958 plus the retained candidate. `check_csv_initial.log` and the final check_csv log pass. `pin_consistency.log` and `class_gate.log` pass. The direct file comparison through name_regression.regressions reports no descriptive-to-placeholder regression in `bank_names.log`; the requested two-file CLI spelling fails because this version expects revision arguments, and that raw failure is retained in `name_regression.log`. The declared-source gate refuses the unmatched candidate, as expected for a bank with no matched row, in `declared_unmatched.log`. Both strict scoped byte gates fail and retain their real output in `scoped_gate.log` and `scoped_gate_bound_scale.log`. `reference_gate.log` records the literal binding failure; `reference_gate_bound_scale.log` passes. A full gate was not run because no source recovery, shared header or ledger change is proposed.

The result is a partial bank, not an exact recovery. The main routine is not a constructor, so constructor unwind ownership is not an applicable check here. Record and owner identity remain intentionally address-derived. The pair temporary lifetime and binding-safe FILD schedule remain unresolved.

The final bank preserves CRLF line endings. Its exact source snapshot is archived as `targets/game/reverse/attempt_history/0x00363050/4c8a9daad9826d11782cef06ba44b7142024e8e53884e29b6f77f10058443ded.json`. Final-path verification reproduces the preferred measurement in `build/rva00363050/probe_bank_crlf.log`; the strict gate remains red in `scoped_gate_bank_crlf.log`. Only one verdict row was appended, with all prior log bytes unchanged.
