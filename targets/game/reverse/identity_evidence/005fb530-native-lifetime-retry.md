# Partial reconstruction of RVA 0x005FB530

The target remains a generated dump. No recovery, ledger replacement or new pin is claimed. The preferred reconstruction is banked in `targets/game/reverse/attempts/0x005fb530.cpp` under `?method@Rva005FB530@FXParticleSystem@@UAE?AVCoord3D@@IMHH@Z`. Its first argument is an opaque four-byte value, not a recovered original C++ type. The tested base is `8a5e04f6981802754159cb17b944588b25313b2d`; the model is `gpt-6.1-sol`. All trial sources and unedited probe outputs are retained in `build/005fb530-retry/`.

## Hypothesis and refutation

The native handle-return declaration already present in `symbols.csv`, the landed module constructor and the canonical coordinate and matrix declarations address the earlier ownership and layout blockers. The hypothesis was that restoring native handle lifetime, the index-zero generation guard, complete random-record semantics and the canonical matrix helpers would improve the saved body. It would be refuted if complete measured bodies using that evidence failed to improve the saved reconstruction. The old body reproduces at 972 bytes with 766 differing bytes and first divergence at zero. The new body measures 1,345 bytes with 600 differing bytes, 21 missing bytes and first divergence at decimal 23 (`+0x17`). The hypothesis improved the reconstruction but did not produce byte equality.

The repository's `finish_measure.parse` quality is `1 - (diffs + 2 * abs(size difference)) / retail size`, floored at zero. It ranks the preserved body at 0.5300 and the earlier bank at 0.0000. This is a diagnostic score, not an acceptance result. Raw measurements and their parsed scores are in `31-preserve-opaque-probe.log`, `00-original-repeat-probe.log` and `score-evidence.log` within the scratch directory. The `finish_measure.py --one` command refuses a reusable receipt because the compiler dependency receipt is unavailable; its raw failures are retained in `31-official-score.log` and `00-official-score.log`. Direct probes and the banking tool's fresh measurement remain usable.

## Boundary, calls and identity

The complete target is `[0x005FB530, 0x005FBA86)`. Its sole return is at `0x005FBA83` and pops 20 bytes. All decoded conditional branches and ordinary jumps stay inside the extent and land on instruction boundaries. The extent contains the cache return path, the invalid-count path, both matrix paths, the generation loop and normal handle destruction. `target-decoded.log`, `checked-target.log` and `flow-evidence.log` retain the complete decoded evidence and branch checks.

The primary vtable installed by the landed constructor at `0x005FBBE0` is VA `0x011132F0`. Slot six names ILT `0x000285CE`, whose complete five-byte body jumps to this target without receiver adjustment. This supports a primary virtual emission-module operation. It does not independently prove the previous bank's `getPosition` spelling. `vtable-011132f0.log`, `constructor-support-decoded.log` and `static-cleanup-routes-decoded.log` retain those measurements. The Zero Hour particle-system donor was inspected; it contains no equivalent lightning-module body to transplant.

| Actual target route | Complete decoded body | Observed ABI and use |
| --- | --- | --- |
| ILT `0x000438F6` to `0x005FB4D0` | 75 bytes; three `ret 4` paths | ECX owner, hidden output pointer, EAX output pointer; a native 12-byte tracking handle. |
| ILT `0x00013994` to `0x001DA440` | 81 bytes; two return paths | ECX handle destructor; clears both link fields and repairs the host list. |
| ILT `0x00001B18` to `0x005CFF50` | 190 bytes; one return | No stack arguments; returns the fallback system pointer. The target retains three distinct fallback sites. |
| ILT `0x0000D7B5` to `0x00096F60` | 123 bytes; three returns | Const ECX receiver; floating result in ST0; reads distribution at zero, minimum at four and maximum at eight. |
| ILT `0x0002BD82` to `0x000FB930` | 79 bytes; two returns | ECX coordinate; no stack arguments; modifies all three floats during normalization. |
| `0x009F6EE4` | 74 bytes; `ret 20` | Constructs 30 elements of 12 bytes using the supplied thiscall constructor and destructor callbacks. |
| `0x009F6E26` | 18 bytes; ordinary return | Registers the static-array destructor; caller removes its four-byte argument. |

`helpers-decoded.log`, `constructor-support-decoded.log`, `static-cleanup-routes-decoded.log` and the corresponding `checked-*.log` files contain the complete helper instructions and checked-callee results. The handle declaration uses the existing independently documented `makeHandle` pin. The neighboring landed `link` source was inspected: its explicit output and volatile guard are an ABI view, not a reason to repeat manual lifetime management.

## Layout and values

The constructor's receiver has a 0x1c-byte primary module portion and a 0x8c-byte emission-info portion. The shared `fx_particle_system.h` is included. The complete 271-byte info copy helper at `0x005D6780` copies the flag at info offset four and eleven three-word records from info offsets eight through 0x88. The target's actual reads distinguish two coordinate endpoints at receiver offsets 0x24 and 0x30 from nine random-variable records at 0x3c, 0x48, 0x54, 0x60, 0x6c, 0x78, 0x84, 0x90 and 0x9c. The full random helper reads the distribution and both floating bounds in every record. These reads establish the records' meaning; the 0xa8 size check and donor names do not. `info-copy-decoded.log`, `checked-info-copy.log` and `checked-random.log` preserve that evidence. There is no STL container in this reconstruction.

The full 25-byte coordinate copy constructor at `0x0005BC20` copies exactly three words, returns ECX through EAX and pops four bytes. The empty default constructor at `0x00083330` and empty destructor at `0x0005BC40` are decoded completely. This justifies raw coordinate copies and a native static coordinate array. The host matrix occupies offsets 0xc0 through 0xef; the anchor consists of floats at 0x18c, 0x190 and 0x194; the condition reads one byte at 0x198. Those fields are established by the target's decoded loads, not by a host-size guess.

Generation occurs only when index is zero. The target keeps the first resolved system's matrix for both inverse transforms, while separately resolving the anchor owner. It preserves the unnormalized endpoint difference for interpolation, draws all nine random values before normalization and normalizes a separate coordinate copy. The three wave groups use amplitude, frequency and phase records `(0,1,2)`, `(3,4,5)` and `(6,7,8)`. The envelope uses the float sign-bit mask, and the canonical `WWMath::Sin` donor supplies the rounded input and output around `fsin`. The lateral vector is the cross product of the upward axis and normalized direction. The previous bank lacked the generation guard, collapsed the matrix owner, used the normalized difference for interpolation and mixed the wave groups and return coordinates. These are rejected body hypotheses, not merely register choices.

## Calling convention and exception lifetime

The complete 133-byte caller at `0x005FAE40` forwards four four-byte arguments and a hidden 12-byte result buffer to primary virtual slot six, with no receiver adjustment. It scales and copies all three returned floats and pops 20 bytes. The complete 91-byte forwarder at `0x005C36C0` gets that module receiver from offset 0x1c4, forwards the first word from offset 0x180, constructs the second argument with floating arithmetic and forwards its two incoming words last. Its two return paths pop 12 bytes. The complete 844-byte `generateParticleInfo` caller forwards particle number and count to this chain before velocity calculation. These bodies and their checked-callee reports are retained in `slot-wrapper-decoded.log`, `forward-decoded.log`, `generate-info-decoded.log`, `checked-slot-wrapper.log`, `checked-forward.log` and `checked-generate-info.log`. The target's signed count comparisons and integer loop support signed final arguments. The original type of the ignored first word remains unresolved. The preserved declaration uses an unsigned four-byte view and does not claim its original type.

The target's handler is at `0x00C3C886` and its FuncInfo is at `0x00E2C39C`. Unwind state zero clears static guard mask `0x1` through the complete 14-byte helper at `0x00C3C870`. State one destroys the handle through the complete eight-byte tail helper at `0x00C3C87E`, adjusting ECX to `[ebp-0x50]` and jumping through ILT `0x00013994`. Normal destruction occurs at the end of the generation block, before cache selection. Static teardown at `0x00C70890` passes the same 30-element, 12-byte array and empty coordinate destructor to the complete 72-byte CRT destructor iterator. The array-construction unwind helper at `0x009F6F2E` was decoded in full. `target-eh.log`, `helpers-decoded.log`, `static-cleanup-routes-decoded.log`, `checked-array-helper.log`, `checked-array-destructor.log` and `checked-array-unwind.log` retain these checks. Candidate unwind metadata is not claimed exact while the frame and byte gate remain wrong.

## Experiments and remaining blocker

Every trial source and its original probe log remain in the task's scratch directory. The useful type and lifetime experiments are summarized here; the raw outputs are authoritative.

| Trial | Size | Differing bytes | Result |
| --- | --- | --- | --- |
| `00-original` | 972 | 766 | Reproduced the saved body's early divergence and missing lifetime structure. |
| `05-canonical-info` | 1284 | 902 | Included the canonical shared emission-info declaration. |
| `13-precise-output` | 1450 | 1134 | `/Op` failed to reproduce the retail arithmetic shape. |
| `20-native-raw-copy` | 1345 | 866 | Native three-word coordinate copies improved endpoint and result handling. |
| `24-vector-coordinate-conversion` | 1345 | 600 | Scalar float conversion from native matrix temporaries was the best measured body. |
| `26-canonical-copy-ctor` | 1337 | 601 | Float copy construction was worse under the repository score. |
| `27-vector-point-expression` | 1574 | 656 | Native vector-expression temporaries substantially enlarged the function. |
| `28-visible-normalize` | 1317 | 586 | A visible, non-inlined helper restored the retail 0x88 frame, but lost more target bytes. |
| `31-preserve-opaque` | 1345 | 600 | Removed the unsupported method spelling and first-argument float claim without changing the measured shape. |

The visible normalization helper independently reproduces all 79 bytes and passes the scoped strict byte gate, string references, constant references and two DIR32 address checks. It is already landed elsewhere; no new helper recovery is claimed. `28-normalize-helper-probe.log` and `28-normalize-scoped-gate.log` retain that result. Moving native local declarations and endpoint lifetimes around this helper did not improve its target result. The EH generator's two `/EHsc` variants also gave identical bytes, recorded in `eh-search-raw.log`; the loop and frame generator found no applicable source-level choices, recorded in `family-generator.log`.

The preserved target still allocates 0x94 rather than 0x88 bytes at `+0x15`, with the first differing byte at `+0x17`. Its first structural difference is at `+0x14c` in the inverse-matrix accumulation, and its wave expression factors the three lateral products differently from retail. Thirteen relocation sites do not align; gate diagnostics at those wrong offsets are not independent missing-callee evidence. The scoped byte gate fails in `32-scoped-byte-gate.log`; the layout gate passes in `32-class-gate.log`. The final `32-bank-ready.cpp` fixes the unused handle link-field labels to match the decoded list and has the same measured instructions as trial 31, retained in `32-bank-ready-probe.log`. The target is a partial with blocker `stack-slot/native-coordinate-temporaries` and unresolved x87 accumulation and wave order. Exact unwind metadata and original method identity remain unverified.

Reopen with independently supported coordinate-conversion or temporary-lifetime source that restores the frame without losing the best body's matrix and return shape, or with a donor that explains the separate wave products. A new spelling of an unchanged register or arithmetic experiment is insufficient. No shared header, policy, tool, symbol pin or ledger row was changed, and no full gate is required for this bank and evidence change.
