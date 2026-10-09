# Numeric stack conversion at 0x008C9650

The recovery remains partial. The saved candidate has a corrected two-pointer calling convention and scalar pool declarations, but its stack frame, state reloads, first unwind cleanup and replacement tail still differ. Reopening requires evidence for a native lifetime that keeps the loop length in EDI while placing the first string at the retail local offset. A named owner or another unchanged register spelling does not address that mismatch.

## Revision and new hypothesis

The tested checkout base is `9eb87483f6942fe8e40cae32a4e6d0d3343d5dc9`. The target remains the generated row in `game/gen_asm/d_008c39e0.asm`; no ledger row or pin changed. Neighbours `LessThan008C8840.cpp`, `Rva008C9B70StackString.cpp` and `Bfme5DuplicateStackTop.cpp`, the saved body and all four earlier verdicts were read before experiments. The historical near-shape alternative was extracted from immutable JSON and compiled, rather than accepted from its description.

The new hypothesis was that the now-landed scalar constructors, string conversion helpers, canonical globals and indirect interpreter dispatcher establish declarations missing from earlier retries, and that correcting those contracts might restore native lifetimes. The refutation test was a complete compiled body measured at the retail extent. Correcting the ABI and declarations did not restore the frame or unwind offset. A direct initial stack load made a small byte improvement; the remaining type and lifetime alternatives did not improve it. Earlier exhausted EH and family searches were not repeated. `eh_levers.py` output is retained as `build/worker-008c9650/eh-choices.json`; it supplied no untried declaration relevant to the decoded discrepancy.

## Boundary and calling convention

`retail-008c9650.txt` decodes the whole target and the following padding/prologue. The shared plain RET is at target +0x517; padding starts at +0x518 and the next function starts at +0x520. Every direct conditional branch stays in the target; there is no outgoing direct tail jump. The early numeric-type paths join the epilogue before the later register pushes need unwinding. `checked-008c9650.log` passed for the complete assigned extent.

Table VA 0x012D5A68 has target VA 0x00CC9650 in opcode slot 0x4A, at RVA 0x00ED5B90. Adjacent slots independently identify the already-landed handlers for 0x44, 0x4B and 0x4D. The complete dispatcher at RVA 0x008CCED0 loads the opcode and performs the indirect call at RVA 0x008CCF8B. Immediately before that call it pushes the address of its local context at 0x008CCF89 and its unchanged interpreter receiver at 0x008CCF8A. The following `add esp,8` at 0x008CCF95 proves caller cleanup of two four-byte arguments. The target reads the first incoming stack argument, makes no receiver adjustment, never reads the second argument, has no hidden return storage and leaves no result consumed by this dispatcher. The reconstruction therefore uses a cdecl handler taking the address-derived stack view and an opaque context pointer. The old one-argument declaration is incomplete even though adding the unused argument leaves its bytes unchanged. This ABI inference would be refuted by a decoded dispatch path with a different table target or argument order; the raw table hits alone were not used as proof. `dispatch-table.log`, `retail-008cced0.txt` and `checked-008cced0.log` retain the table and complete caller evidence.

The descriptive name `stackNumber008C9650` retains the address. No independent native method or complete owner identity was established, and none is claimed. The proposed stack prefix is witnessed by target accesses to signed count +0 and the pointer array +8; the intervening four bytes are unused by this target. The context's layout is unclaimed.

## Types, callees and ownership

The complete base constructor 0x00899560 was decoded through its three return paths, and scalar constructors 0x008A4C00 and 0x008A1110 through both return paths each. The base reads/writes flags +4, installs the base vptr at +0 and registers the object through root-list capacity +0, count +4 and item array +8. Each scalar constructor also installs its derived vptr and writes one four-byte payload at object +8. The actual target's float path receives ST0 from `AptValue::toNumber`, spills it as a float and writes that payload; its integer path receives EAX from `AptValue::toInteger` and writes the integer payload. These complete conversion and constructor paths establish scalar types independently of the twelve-byte allocation request. Pool link helpers 0x008D29B0 and 0x008D2A20 both store the previous head pointer at object +8. The final candidate models the reused integer slot as an integer/pointer union, as the float view already did. No STL value type or STL pin is involved.

The target's direct call contracts were checked against complete callees: `getName` has an ECX receiver and one four-byte output-string argument with RET 4; `find0089FF80` takes the character pointer and signed start index with RET 8 and returns EAX; `toNumber` returns in ST0; `toInteger` returns in EAX and its float arm tail-jumps to the fully decoded CRT `__ftol2`. `AptGetSwfVersion` is the canonical unsigned EAX getter. The six-byte CRT import thunks resolve through the PE's MSVCR71.dll imports to `isdigit` and `strtol`; actual target push/cleanup sequences establish their one-int and three-argument cdecl contracts, including the four-byte end-pointer output. No new callee pin was invented.

`getName` was inspected through every switch arm. Its string paths read the handle at receiver +8 or the indirect owner at +0x20, increment the new header's ushort reference count, decrement/free the old one and replace the output's one pointer. The string header has ushort reference count +0 and length +2; character bytes start at +8. The full `getName`, `toInteger` and `toNumber` extents include embedded switch tables. Linear inventory over those data bytes correctly failed, so code-only extents were checked separately and the table destinations were enumerated. The positive logs are `checked-code-008985c0.log`, `checked-code-00898300.log` and `checked-code-008983d0.log`; the original negative logs remain alongside them. The ledger's 13-byte extent for the integer pool link truncates its six-byte store. Its separately decoded complete 15-byte body ends at RET +0x0E, and `checked-008d2a20-complete.log` passes. This adjacent ledger issue was not edited as part of the target assignment.

Indirect retain/release calls use vtable slots +0 and +4 with ECX holding the value pointer and no stack arguments or receiver adjustment. The base, float and integer tables point to 0x008991B0 and 0x008991E0 in these slots. Both complete helpers were decoded; release has two returns and a tail jump through slot +8 when the root list is full. Float and integer slot +8 link to their independently decoded free-list helpers. Thus the proposed first two virtual slots are methods, not a guessed deleting destructor. The rest of the class hierarchy is not claimed. `indirect-evidence.log`, `checked-008991b0.log`, `checked-008991e0.log`, `checked-008d29b0.log` and the `retail-*-code.txt` files retain these checks.

Canonical unsigned SWF getter, empty-string data, root-list and scalar free-head declarations were taken from the actual landed donor sources. Their opaque global types are retained at the interface and cast to the witnessed local views. No shared header or donor was edited.

## Exception cleanup

Retail FuncInfo at RVA 0x00E48F08 has two states, each returning to state -1. State 0 cleanup at 0x00C59EF0 destroys the string at `[ebp-0x20]`; state 1 at 0x00C59EF8 destroys `[ebp-0x14]`. Both tail-jump to the complete 22-byte refcount destructor at 0x00891B80. Its ECX receiver, ushort decrement, conditional pool free and plain RET were decoded. The landed identity evidence `00891b80-eastring-return-cleanup.md` independently identifies EAStringC's destructor. There are no element-array or constructed-value cleanup states in this target.

The final object has the same two state transitions and the same address-view string destructor at both states, but state 0 uses `[ebp+4]`, the reused incoming argument slot. State 1 uses the retail `[ebp-0x14]`. The first cleanup offset is therefore still a blocker; matching state counts would not establish correct cleanup. `eh-info.log` and `pooled-union-evidence.log` retain the retail/object comparison.

## Measured alternatives

These rows are generated from retained raw probe outputs using `finish_measure.parse`; normalized shape is diagnostic and is not byte equality. Each trial is one compiler invocation (n=1). Sources with the corresponding descriptive names, scripts, disassemblies, compiler objects and unedited outputs remain under `build/worker-008c9650/` and `build/experiments/`.

| Raw probe log | Compiled bytes | Non-relocation differences | Diagnostic quality | Normalized shape | Structural differences |
| --- | ---: | ---: | ---: | ---: | ---: |
| `probe-baseline.log` | 1278 | 556 | 0.5337 | 0.966 | 8 |
| `probe-canonical-contracts.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |
| `probe-canonical-getter.log` | 1278 | 556 | 0.5337 | 0.966 | 8 |
| `probe-direct-load.log` | 1282 | 1046 | 0.1641 | 0.966 | 12 |
| `probe-final-bank.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |
| `probe-history-best-shape.log` | 1295 | 1056 | 0.1764 | 0.997 | 1 |
| `probe-inverse-one-argument.log` | 1302 | 1018 | 0.2163 | 0.930 | 18 |
| `probe-inverse-predicate.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |
| `probe-length-inner-live.log` | 1278 | 556 | 0.5337 | 0.966 | 8 |
| `probe-length-reference.log` | 1298 | 1066 | 0.1733 | 0.985 | 3 |
| `probe-member-predicate.log` | 1280 | 1065 | 0.1465 | 0.959 | 21 |
| `probe-native-length.log` | 1285 | 694 | 0.4387 | 0.959 | 12 |
| `probe-pooled-integer-union.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |
| `probe-predicate-int.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |
| `probe-result-lifetime.log` | 1282 | 1048 | 0.1626 | 0.964 | 14 |
| `probe-template-string.log` | 1278 | 556 | 0.5337 | 0.966 | 8 |
| `probe-two-arguments-direct.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |
| `probe-two-arguments.log` | 1278 | 556 | 0.5337 | 0.966 | 8 |
| `probe-value-virtual-interface.log` | 1278 | 553 | 0.5360 | 0.969 | 6 |

The historical cached-length candidate preserves the larger frame but omits retail's length reload at +0x272 and swaps the whole-body EBP/EDI allocation. It is not a better byte reconstruction. An unsigned-short length accessor introduces unsigned loop branches contrary to retail's signed comparison. A reference to the header length introduces a field-address LEA. A native member predicate and a predicate without the preserved-value spill change the EH prologue or inlining/register shape. Moving result lifetime alone changes many more bytes. Predicate return-width and inversion changes, the template string view and the two corrected virtual method declarations do not repair the remaining mismatch.

The retained candidate still allocates frame 0x10 instead of 0x14, omits state-pointer reloads at +0x27F, +0x2A9 and +0x4C7, and merges the special replacement tail that retail emits separately at +0x2E0 through +0x2F5. Those are specific source-lifetime/control-flow residues. Repeating unchanged register or x87 experiments is not a justified next step.

## Verification and handoff

`pooled-union-gate.json` and its raw `.log` record the scoped repository byte resolver applied to the complete candidate without mutating the ledger: FAIL, with all strict difference offsets retained and no unresolved symbols. The strict comparison resolves relocations and includes missing tail bytes, so its difference count is distinct from probe's non-relocation count. `check-csv-final.log`, `pin-consistency-final.log` and `class-gate-final.log` passed. No full gate is required for a bank/evidence-only change.

The bank was probed again at its final path under `?stackNumber008C9650@@YAXPAUStack008C9650@@PAX@Z`, and its strict candidate gate was repeated after banking. `probe-final-bank.log` retains the probe; `final-bank-gate.json` and `.log` retain the unchanged strict failure. The bank's class check passes in `final-bank-class.log`.

The prescribed file-pair `name_regression.py` invocation fails because this revision's CLI takes Git revisions. Its existing pure `regressions(old_text,new_text)` function was run on the original bank and candidate and reports zero descriptive-to-placeholder regressions, retained in `pooled-union-evidence.log`. `find_declared_unmatched.py --fail` on the unlanded trial reports its unmatched definitions, as expected; `declared-unmatched.log` retains that failure. No unmatched source was promoted into `game/`, and no declaration was marked absent from retail without proof.

One partial verdict banks the complete candidate under the corrected symbol. The diagnostic score is measured from bytes, not copied from normalized shape. No exact recovery, new progress bytes, complete native owner identity, source landing or commit is claimed. No Git write or synchronization command was used.
