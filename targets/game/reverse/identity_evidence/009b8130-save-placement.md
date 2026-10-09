# Save-placement retry at 0x009B8130

The complete preferred body in `targets/game/reverse/attempts/0x009b8130.cpp` is retained without a source change. No body was landed. The ordinary scoped byte gate still fails with 39 differences, and independent binding of the four named globals gives 43 differences. All remaining independently bound differences occupy +0x1C through +0x46. Every byte from +0x47 through the final RET at +0x15C3 agrees. The tested revision is `2b87b58ecac3d0d06f19adfa6e9636ada74abccc`. This retry used gpt-6.1-sol and measured 9.01 minutes through preservation. Its raw compiler experiments and verifier outputs are retained under `build/target-009b8130-retry/`.

## Hypothesis and stopping observation

The Open BFME 2 donor is `Code/GameEngine/Source/Common/Rva001CA000Vp6WideAccum.cpp` at game.dat RVA 0x001CA000. It is a structural near twin already used by the prior attempt, rather than new identity evidence in this retry. The landed BFME 1 sibling `Rva009B9700Vp6Reconstruct.cpp` supplies the proven aligned-frame recipe and canonical data declarations. The current ledger supplies no new callee or native context declaration that resolves the save-placement blocker. Both donors' actual sources were read before these experiments.

The retry hypothesis was that a native C++ prefix and an explicit end-value lifetime could delay ESI and EDI saves to retail's +0x45 and +0x46 while leaving EAX equal to the range end at pointer setup. A different save position or a different live EAX refutes that shape. The inline edge accessor and moving the range-input definitions before the edge lookup repeat the earlier stale-EAX stream, exhausting the two unchanged register experiments. Computing the end before the broadcast instead leaves the edge value in EAX at the unchanged assembly consumer. A C++ byte-index assignment keeps the end in EAX, but compiles to a seven-byte LEA instead of the three-byte SHL and lengthens the function. Explicit native source and stride locals do not remove that length difference. No new frame padding, pin or compiler flag was used to disguise a mismatch.

## Measurements

Every source below contains the complete target body and was probed at the independently checked retail extent. Exact source hashes are recorded in `build/target-009b8130-retry/summary.json`. Each corresponding `*-probe.log` contains the unedited probe output. Compiled bytes, relocations and independently bound disassembly are retained beside each source.

| Complete trial | Compiled bytes | Probe differences | Independently bound differences |
|---|---:|---:|---:|
| `inline-edge` | 5572 | 33 | 37 |
| `end-before-broadcast` | 5572 | 35 | 39 |
| `native-end-consumer` | 5576 | 4848 | 4908 |
| `native-pointer-setup` | 5576 | 4846 | 4906 |
| `range-inputs-first` | 5572 | 33 | 37 |

The C++ prefix trials with smaller difference counts are rejected because they compute the wrong byte index. `verify.py` interprets the decoded scalar prefix, rather than C++ source, and reads its frame state. Two nonempty cases and two empty or wrapping cases were checked for each trial. The preferred bank passes all four prefix cases. The inline accessor and reordered range-input shapes produce four times the starting fragment instead of four times the end. The end-before-broadcast shape produces four times the edge value. The two C++ end consumers pass these limited prefix checks but emit longer bodies. These probes do not constitute a runtime test of the full MMX algorithm. The raw states are in `scoped-gate-raw.log`; the ordinary bank byte gate exits unsuccessfully in `scoped-byte-gate-v2.log`.

## Boundary, ABI and data checks

The fresh complete target decode is `retail-009b8130.log`, with branch and endpoint assertions in `decode-audit.log`. The extent has one plain RET, twelve INT3 bytes on each side, no direct or indirect CALL, and no external conditional branch or tail jump. Its empty-range branch reaches the epilogue. Its fragment guard skips the second island on the first iteration, and the common latch returns to the loop header. No exception-handling cleanup or container-value helper applies to this target.

The complete caller at 0x009AEEE0 reads the selected callback from VA 0x01356E94 and pushes seven dwords: context, source pointer, destination pointer, stride, width, fragment index and table pointer. Both indirect sites clean 28 stack bytes and ignore the result. The complete installer at 0x009B0D60 stores the target VA into that slot. Fresh `checked-target.log`, `checked-caller.log` and `checked-installer.log` cover these extents; the complete caller and installer listings are retained beside them. The body accesses arguments through EBX and returns with plain RET, with no receiver adjustment or hidden return storage. These facts support the retained address identity and cdecl ABI. They establish no native owner name.

The target reads the context index at +0xC and four-byte element pointers at +0x24 and +0x28. The first quantizer selection uses the end-based byte index, and the second uses the current fragment. The accumulator stores are four bytes. The result reductions read eight unsigned words, agreeing with the retained bank rather than the donor's byte reductions. The bank keeps all inherited descriptive identifiers. A future landing still needs the independently proven eight-byte data row for `Rva009B8130Const86C0`; no data row or pin was changed in this retry.

`check-csv-final.log`, `class-gate-bank.log` and `pin-consistency.log` pass. No shared header or shim was edited and no full gate was required. The body remains a partial. Reopen it only with a demonstrated prefix that preserves both the end-based byte index and retail's save placement without changing the complete extent. Repeating the rejected register spellings or claiming the stale-EAX shape from its masked score does not justify reopening.
