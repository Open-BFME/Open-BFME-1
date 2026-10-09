# 0058E390 complete drawing reconstruction

## Result and reopening condition

The complete HelpBoxText callback is banked as `Rva00592640Owner::rva0058E390`. Its measured body is 1810 bytes against 1810 retail bytes, with 34 non-relocation differences and measured bank quality 0.9812. The ordinary scoped byte verifier also finds 34 differing bytes and no unresolved calls. This is a partial, not a source recovery. The first differing byte is +0x0117. The authoritative byte list is `build/0058e390/strict-differences.json`; the untouched probe and gate outputs are `build/0058e390/probe-final.log` and `build/0058e390/scoped-gate.log`.

Reopen with evidence that changes the coordinate-copy lifetime, the centered-row temporary representation, or the instruction scheduling at +0x01BD and +0x0212. Repeating the indexed two-field assignment, an extra copy temporary, a separate imageSize2 local, or visibility of the draw helper has already failed to improve the preferred body. Original categories of the two unused callback words remain unresolved. A complete caller that forwards the target's actual four words would settle them; the unrelated dispatcher at 0046CF80 does not.

The tested revision is `91ced6e6f0a9d577b05b6c510820078adfe345c3`. The model is `gpt-6.1-sol`. No production source, ledger row, pin, shared header, baseline or policy changed in this run. The normal gate rejects the target and accepts the already-landed extents helper reproduced inside the candidate. No exact recovery is claimed for either a new identity or a new ABI.

## New hypothesis and refutation

The earlier identity and widget-layout blockers can be narrowed using the constructor bank at 00592640, its existing callback evidence, the matched forwarding invoker at 0058D210, and the landed extents and drawing helpers at 005890F0 and 00589040. They support an opaque receiver and a complete drawing reconstruction without inventing an authentic owner name. This hypothesis would be refuted by a constructor binding a different code address, a receiver adjustment not accounted for by the wrapper, a target exit consuming a different stack size, or virtual implementations reading different argument widths.

The supporting files were read directly: `targets/game/reverse/attempts/0x00592640.cpp`, `0058e390-helpboxtext-callback.md`, `00592640-palantir-base-member.md`, and `00592640-exact-constructor-bank.md` in this evidence directory. Neighboring landed rows at 0058DDD0, 0058E220 and 0058ECA0 were also checked against their source. Only the extents helper supplies directly applicable coordinate and image declarations. A donor name and allocation size are not used as payload-type proof.

The compiler-specific hypothesis is that the original translation unit exposed the extents helper's body while retaining a real call. A declaration-only helper can retain output addresses, preventing reuse of its second coordinate buffer. Copying the independently matched helper with `__declspec(noinline)` reduced the preferred probe's distance while preserving the call and the helper's own exact bytes. This hypothesis would have been refuted by an unchanged caller result or a helper that stopped matching. The measured results below support it for this compiler; they do not establish the original source spelling.

## Boundary, receiver and callback arguments

The complete target decode contains three RET 16 exits at +0x006A, +0x06F8 and +0x070F. All direct conditional and unconditional branches stay within the requested extent. The final return ends at 0058EAA2, followed by padding. `build/0058e390/audit.log` records complete decoded coverage and every return or outgoing jump for the target and the helpers used as ABI evidence.

Constructor 00592640 registers the HelpBoxText literal and ILT 0003524C, which decodes as a jump to 0058E390. Its callback wrapper stores the receiver at +8 and code at +C. The matched 0058D210 invoker loads ECX from wrapper+8 and tail-jumps through wrapper+C, preserving the incoming stack. The receiver belongs to the constructor's opaque owner, whose embedding at client+0x488 is documented by the existing evidence. There is no receiver adjustment inside the target.

The first stack word addresses a record read as floats at +0 and +4. The second addresses a float at +0; its complete record extent is not established by the target. The bank uses the same opaque point view for both, without claiming that the second record's unused +4 field is proved. The remaining two words are consumed but never read. The bank represents them as opaque unsigned words; their original pointer, integer or floating categories are not proved. There is no observed hidden result pointer. No verified caller establishes a return contract, and the target's distinct exits do not produce a common return value, so the reconstruction uses void. A complete forwarding caller is still required to settle that contract and the unused words before any exact ABI claim. Authentic callback spelling and complete owner identity remain unknown; address identities are retained.

## Observed member and value contracts

Receiver bytes +0 and +2 control display and wrap initialization. Signed receiver dword +4 is initialized from the second argument's first float plus one half through the actual __ftol2 import route. Receiver +C is an opaque data pointer. Native accesses and complete StringBase helpers establish one-pointer UnicodeString values at data+4 and data+8, with a two-byte flag at data+0x10. No container payload or semantic UpgradeMuxData identity is inferred from the neighboring destructor's name.

StringBase<unsigned short> copy 00888400 is decoded through its complete RET 4 path. It copies the one-pointer representation and retains the buffer. Release 008881D0 is decoded through its complete return and reference-count/free paths. Its buffer header has reference count at +0 and a two-byte length at +4. The bank includes the existing WWLib `unicode_string.h` and forwards the inline UnicodeString copy and destruction to the canonical StringBase operations. Emptiness checks the witnessed two-byte length rather than the incompatible private StringInline header.

Receiver +0x14, +0x18, +0x1C, +0x20 and +0x24 are display-string receivers. The constructor's five allocation calls and W3DDisplayString constructor 006F4DE0 establish the virtual receiver family. The actual vtable at VA 0111FEA8 routes +0x20 through ILT 000484E6 to 006F4B00, which accepts one signed word and returns RET 4. Slot +0x3C routes through 000401A6 to 006F49B0, which writes width to argument one and height to argument two and returns RET 8. Slot +0x34 routes through 0000FF42 to 006F4990, which forwards x, y and two zero words to +0x38 and returns RET 8. Slot +0x38 routes through 0000EB33 to the complete 448-byte 006F5170 body, whose four integer-coordinate words and RET 16 agree with that forwarding call.

The existing DisplayString header shims place getSize at +0x30 and omit these BFME-only slots. The candidate therefore retains an address-qualified virtual view. This is a declaration-adoption limitation for any future landing, even if the target bytes become equal. No shared header was edited. `class_gate.py` accepts the bank's class declarations, but that result alone does not certify their semantic identities.

Receiver +0x28 and +0x2C are image-like pointers. The actual extents helper 005890F0 reads their signed dimensions at pointee+0x24 and +0x28, multiplies them by the two float values returned by WindowManager slot +0x28, and writes both two-float extents plus their componentwise maximum. Both RET 12 paths were inspected. The bank preserves the existing BfmeCellEV, BfmeVec2EV and BfmeHostEV names and layout. It gives the helper its already-landed body, and that copy passes the strict byte verifier.

ILT 00024F41 routes to the complete 130-byte 00589040 helper. Its incoming stack contains one image word, two float coordinate words and two pointers to two-float extents. It uses Display slots +0xB0 and +0xD4, then tail-jumps through +0xDC. The existing scalar-argument declaration and mangled pin are preserved; the bank's call expression casts that function to the independently decoded two-float aggregate ABI. A nontrivial inline coordinate copy creates the native in-place eight-byte argument. Matching a template or donor would not prove this ABI; the actual incoming loads and caller stores do.

## Exception cleanup

The target handler at 00C374D0 loads FuncInfo VA 01226950 and tail-jumps to the C++ frame-handler import. Its two-state unwind map at VA 01226940 sends state 1 to state 0 and then to -1. Cleanup 00C374C8 takes the UnicodeString at EBP-0x50; cleanup 00C374C0 takes the one at EBP-0x54. Both jump through 0003B304 and 0005EEA0 to the complete releaseBuffer body at 008881D0. This proves two scoped string copies with reverse destruction. It does not make either image pointer an owning local.

The bank's normal path has the two copy calls, the corresponding state stores and two release calls in reverse order. No extra cleanup owner was invented. Mechanical EH variants were tried before manual shape iteration and did not improve the initial candidate. The unedited native metadata, complete cleanup decodes and checked-callee reports remain under `build/0058e390/`.

## Measured experiments

All rows below are generated from retained raw probe outputs. Quality uses `tools/finish_measure.py`'s byte-distance formula, including its size penalty; normalized instruction similarity is not a bank score. Failed compilations in trials 02 and 04 are retained but provide no shape evidence. The EH search receipt and candidate snapshots are retained under `build/shape_search/be6ffea983cf41b8886767efe7596c8c/`. The non-EH search refused the native rounding helper's inline assembly; its generated finite alternatives were then probed separately without modifying a verifier.

| Probe | Hypothesis | Bytes | Differing bytes | Quality | Raw output |
| --- | --- | ---: | ---: | ---: | --- |
| 01 | Complete initial body with truncation casts | 1671 | 1192 | 0.1878 | `build/0058e390/probe01-raw.log` |
| 03 | Native fld/fistp rounding primitive | 1808 | 1221 | 0.3232 | `build/0058e390/probe03.log` |
| 05 | Reuse first extents buffer | 1805 | 1288 | 0.2829 | `build/0058e390/probe05.log` |
| 06 | Nontrivial extents copy constructor | 1816 | 1336 | 0.2552 | `build/0058e390/probe06.log` |
| 07 | Nontrivial by-value point copy and maximum-width coordinate | 1822 | 863 | 0.5099 | `build/0058e390/probe07.log` |
| 08 | Explicit conversion ordering | 1788 | 799 | 0.5343 | `build/0058e390/probe08.log` |
| 09 | Conversion ordering plus buffer reuse | 1788 | 795 | 0.5365 | `build/0058e390/probe09.log` |
| 10 | Donor two-field assignment spelling | 1788 | 795 | 0.5365 | `build/0058e390/probe10.log` |
| 11 | Group width and height | 1788 | 794 | 0.537 | `build/0058e390/probe11.log` |
| 12 | Native rounding return spelled long | 1788 | 795 | 0.5365 | `build/0058e390/probe12.log` |
| 13 | Share point and extents type | 1788 | 795 | 0.5365 | `build/0058e390/probe13.log` |
| 14 | Reuse function-scope horizontal coordinate | 1788 | 795 | 0.5365 | `build/0058e390/probe14.log` |
| 15 | Keep third-row total width as a local | 1794 | 782 | 0.5503 | `build/0058e390/probe15.log` |
| 16 | Precise floating-point flag /Op | 1874 | 1233 | 0.2481 | `build/0058e390/probe16.log` |
| 17 | Decoded Y-before-X order for fallback and footer | 1810 | 220 | 0.8785 | `build/0058e390/probe17.log` |
| 18 | Separate second image extent in a nested scope | 1810 | 227 | 0.8746 | `build/0058e390/probe18.log` |
| 19 | Expose independently matched noinline extents helper | 1810 | 34 | 0.9812 | `build/0058e390/probe19.log` |
| 20 | Visible helper with scoped second image extent | 1810 | 197 | 0.8912 | `build/0058e390/probe20.log` |
| 21 | Visible helper with function-scope second image extent | 1810 | 197 | 0.8912 | `build/0058e390/probe21.log` |
| 22 | Indexed loop assignment | 1802 | 1236 | 0.3083 | `build/0058e390/probe22.log` |
| 23 | Indexed donor assignment with visible helper | 1810 | 34 | 0.9812 | `build/0058e390/probe23.log` |
| 24 | Expose the drawing helper too | 1810 | 34 | 0.9812 | `build/0058e390/probe24.log` |
| 25 | Materialize a second-coordinate copy temporary | 1810 | 34 | 0.9812 | `build/0058e390/probe25.log` |
| final | Portable final candidate with typed image pointers | 1810 | 34 | 0.9812 | `build/0058e390/probe-final.log` |
| family0 | Generated adjacent image-store order | 1788 | 820 | 0.5227 | `build/0058e390/family0.log` |
| family1 | Generated fallback height/coordinate store order | 1788 | 806 | 0.5304 | `build/0058e390/family1.log` |

The preferred body retains the native two-instruction rounding primitive. Direct C++ truncation casts emitted __ftol2 at sites where retail uses fld/fistp; /Op also worsened the result. The primitive is the only inline assembly in the candidate and is banked as an explicit x87 code-generation limitation.

The remaining regions are the coordinate-copy reads at +0x0114 and +0x011C, the member/text load versus fadd order at +0x01BD, the first-row height spill among outgoing pushes at +0x0212, and centered-row coordinate lifetimes around +0x0466 and +0x0576. Their exact differing byte offsets are in the JSON named above. All complete target paths have source; the unresolved result is byte equality and the declaration limits described above, not a missing body.

## Verification and handoff

`tools/check_csv.py` and `tools/pin_consistency.py --check` pass; their raw outputs are `build/0058e390/check-csv-final.log` and `build/0058e390/pin-consistency-final.log`. The target fails the scoped normal byte gate, and the copied extents helper passes, in `build/0058e390/scoped-gate.log`. The read-only invocation supplies explicit candidate rows to `build.verify_functions`; it does not alter functions.csv or grant a matching verdict.

`tools/class_gate.py` passes in `build/0058e390/class-gate-final.log`. `tools/find_declared_unmatched.py --fail` refuses the candidate because it has no matched ledger row, in `build/0058e390/declared-unmatched-final.log`; the target is marked present-unmatched and remains a bank. No whitelist was added. A full gate is not required for bank and evidence changes. No background process was left running.

Every trial source, compiler listing, decoded extent, raw probe and gate receipt remains in `build/0058e390/`. The final portable source is banked through re_log.py with exactly one verdict for this run. Git synchronization and Git writes were prohibited, so collection and any commit belong to the coordinator.
