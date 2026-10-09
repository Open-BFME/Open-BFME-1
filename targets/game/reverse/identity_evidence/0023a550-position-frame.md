# RVA 0x0023A550: position accumulation and frame mismatch

The complete standalone candidate remains a partial. It compiles to 379 bytes against a 383-byte retail extent. The scoped byte gate fails. No function or symbol ledger entry was changed. The tested base revision is `aee201bed1b9c208661a83d70fcc468576db5f57`, and the model is `gpt-6.1-sol`.

## New hypothesis and result

Current landed declarations remove the earlier dependence on including a callee provider translation unit. The candidate includes the canonical `Object`, `Coord3D`, and `GameLogicObjectLookup` headers and reuses the landed position accessor declaration. Decoding the actual index insertion chain establishes a single signed ObjectID value rather than inferring it from node allocation size or a donor name. The hypothesis was that correcting these declarations and using the native signed-ID set would restore the missing frame word. A compiler result retaining the count in the dead incoming argument slot would refute that hypothesis. Trial 15 retains exactly that slot and refutes it.

The previous records provide no saved source. Trial 00 therefore reconstructs a complete baseline before testing changes. Trial 02 improves the measured overlap from 90 differing bytes to 89 by initializing the count after obtaining the list iterator. This does not resolve the earlier frame blocker. Trial 15 has the same instruction and relocation shape as trial 02 while using the independently checked signed-ID set. It is the retained body.

## Boundary, receiver, and ABI

The complete target decode has two return paths, `ret 4` at offsets `+0x152` and `+0x17c`. The second return ends at `+0x17f`, followed by alignment padding. Every conditional branch and internal jump stays within the extent. There is no external tail jump, EH registration, constructor cleanup, hidden aggregate result, or owning-container mutation in this body. The sole stack argument is a four-byte address. The body writes three 32-bit floats at that address, preserves it in ESI, and returns false or true in AL. A pointer and a reference compile to the same observed ABI; the original parameter spelling is not independently established.

The HordeContain constructor at `0x0023EAF0` installs vtable `0x010AED58` at complete-object offset `+0xe4`. Slot 128, at table offset `+0x200`, reaches ILT `0x00021959`, which routes to this body. Thus the target receiver is the secondary interface at complete-object `+0xe4`. The active list at receiver `-0xac` is complete-object `+0x38`, and the index at receiver `+0x30` is complete-object `+0x114`. The constructor is used only for this vptr store and receiver offset; this note does not certify its unwind ownership. No complete caller of target slot 128 was identified. The method retains an address-derived identity, and the semantic method name remains unknown.

The target calls Object vtable slot 10 four times without receiver adjustment or stack arguments. The canonical Object declaration is `Drawable *getDrawable() const`. The Object table routes this slot through ILT `0x0002074D` to `0x001BE440`, whose complete seven-byte body returns `[ecx+0x80]` in EAX and uses plain `ret`. The target then uses that result as the position-accessor receiver without adjustment.

Both position calls go through ILT `0x0003EE55`, a complete five-byte jump to `0x0041D150`. The complete 164-byte accessor has plain returns at `+0x11` and `+0xa3`. It returns a pointer in EAX to three floats, either receiver `+0x38` or interpolation storage at `+0x230`. It takes no stack argument and has no hidden return storage. The candidate reuses the landed `BFMERopeDrawableGetPositionShim::getPositionLinear() const` declaration; no new pin is required.

The tree increment at `0x0082B870` is completely decoded through its plain return at `+0x68`. It accepts a node pointer on the stack, returns a node pointer in EAX, and the target removes its four-byte argument. Its traversal reads only parent `+4`, left `+8`, and right `+0xc`; it does not establish the value type. The existing STL symbol is reused without changing any STL ledger row or pin.

## Container evidence from complete value copies

The index registration body at `0x00236B10` (65 bytes) occupies slot 40 of the same HordeContain secondary interface. It reads Object `+0x74`, forms a key reference, and calls the insertion helper at receiver `+0x30` through ILT `0x000499F9` to `0x000EEC50`. That complete 145-byte helper uses signed comparisons against node `+0x10` and calls `0x000EE420` through ILT `0x0002ED39`. Its result is an iterator and success flag returned through caller-provided storage; it ends in `ret 8`.

The complete 179-byte node insertion at `0x000EE420` copies exactly one dword from the value reference to node `+0x10` on each allocation branch (`+0x39` through `+0x3b`, and `+0x5f` through `+0x61`). There is no second value field. Node linkage occupies parent `+4`, left `+8`, and right `+0xc`; insertion calls rebalance and increments the container count. The helper ends in `ret 0x14`, including its hidden iterator-result storage and four explicit arguments. This establishes a single signed ID value, independently of the 20-byte node allocation and the placeholder enum name in the existing pin. It supports canonical `ObjectID` representation, without proving the original typedef or enum spelling.

The complete 249-byte active-list drain at `0x00225960` accesses complete-object list `+0x38`. Its inline value construction writes the resolved Object pointer into node `+8` at `+0x6e`; next and previous links occupy `+0` and `+4`. No second value field is copied. Its normal return is at `+0xd8`; the final path ends in a call to the imported noreturn `_CxxThrowException`. The separate complete 82-byte list writer at `0x00226790` independently shows the same single pointer copy and link layout, but its receiver offset is not used to establish the target's complete-object offset.

The complete 38-byte `GameLogic::addObjectToLookupTable` at `0x0038E490` reads Object `+0x74`, calls the hash subscript at GameLogic `+0xb0`, and stores the original Object pointer through the returned mapped-value address. The actual chain is ILT `0x00005E11` to `0x0038B980` (99 bytes), then ILT `0x000169A5` to `0x00389A20` (111 bytes), then ILT `0x0002D074` to `0x00385E30` (23 bytes). The complete final copy helper reads source dwords `+0` and `+4` and writes destination dwords `+0` and `+4`, with no other value fields. The new node's next pointer is `+0`, the ID is `+4`, and the mapped Object pointer is `+8`. This supports the canonical hash of signed IDs to Object pointers. Existing misleading unsigned or integer-payload helper pins are not treated as type evidence and are not edited.

All listed evidence extents were decoded completely and checked with the coordinator's read-only `checked_callees.py`. Direct-call inventories alone are not treated as boundary or ABI proof. The raw inventories and decoded bodies are preserved under `build/worker-0023a550/`.

## Measurements and rejected shapes

| Trial | Change | Compiled size | Differing overlapping non-relocation bytes |
| --- | --- | ---: | ---: |
| 00 | Complete baseline with canonical Object and hash declarations | 379 | 90 |
| 01 | Reference output parameter | 379 | 90 |
| 02 | Initialize count after list begin | 379 | 89 |
| 03 | Separate list iterator scope | 379 | 90 |
| 04 | Single-field count object | 379 | 91 |
| 06 | Compiler listing of trial 02 | 379 | 89 |
| 07 | Count passed through an inline const reference | 379 | 89 |
| 08 | Canonical Coord3D zero, add, and scale inlines | 379 | 89 |
| 09 | Inverse through an inline const reference | 379 | 89 |
| 10 | Iterator conversion to const iterator | 379 | 91 |
| 11 | Const list and const iterator | 379 | 89 |
| 12 | Position call directly inside the Coord3D add inline | 379 | 91 |
| 13 | Virtual declaration with the same member offset | 379 | 89 |
| 14 | Disable global optimization with `/Og-` | 585 | 357 |
| 15 | Native signed ObjectID set | 379 | 89 |
| 16 | Native signed-ID set with separated list scope | 379 | 90 |
| 17 | Eliminate the named scale temporary | 379 | 93 |

Trial 05 did not compile because its canonical Coord3D include lacked the Lib include directory. Trial 08 corrects the include and supplies the actual measurement; the failed compile is not evidence against its shape. A bounded generated shape search tested the baseline and one bool constant-materialization choice. Both measured `0.7571801566579635` and produced the same masked instruction shape. The search stopped without an improving output. The source snapshots, choices, and unedited results remain under `build/shape_search/566e012395c44d34969161844dbe5fa0/`.

The retained probe is `build/worker-0023a550/probe-trial-15-native-idset.txt`. It reports 379 versus 383 bytes, 89 differing overlapping non-relocation bytes, eight relocations, and one relocated operand position that does not align with retail. There are four additional missing bytes. The bank quality is computed by the repository measurement tool; normalized instruction similarity of `0.971` is not a byte-match score. Relocation layout drift makes the overlapping byte count a diagnostic rather than proof that only those bytes remain to fix.

## Preservation and collection checks

The retained bank is `targets/game/reverse/attempts/0x0023a550.cpp`. `re_log.py` measures its quality and writes the immutable source archive named in the single new verdict row. `build/worker-0023a550/preservation-check.txt` verifies that removing only the two bank metadata lines produces the exact bytes of trial 15, that the archive agrees with the bank, that precisely one CRLF verdict row was appended, and that the function and symbol ledgers remain byte-identical to the tested revision. The original attempt-log bytes were preserved.

The ordinary CSV check passes after banking in `build/worker-0023a550/check-csv-after-bank.txt`. Since the Git index is read-only and the bank is untracked, the same checker also validates the new bank explicitly through `check_attempts`, with one bank and no problems, in `build/worker-0023a550/bank-hygiene.txt`. Pin consistency passes in `build/worker-0023a550/pin-check-final.txt`, and the bank class gate passes in `build/worker-0023a550/class-gate-bank.txt`. No shared header changed, and no full gate was needed for this bank.

`find_declared_unmatched.py --fail` reports the candidate as unclaimed because it has no landed source row. Its failed result is preserved in `build/worker-0023a550/declared-unmatched-best.txt`; this is not a passing source-landing check. There was no prior bank to convert, and no descriptive name was changed. The bank preserves the measured source exactly. All trials and unedited raw outputs remain under the task build directory for collection.

## Exact remaining blocker and reopening condition

Retail begins with `sub esp,8`; the candidate begins with `push ecx`. Retail's saved receiver is `[esp+0x14]` and count is `[esp+0x10]` after all four register saves. The candidate saves the receiver at `[esp+0x10]` and places the count in the dead incoming argument slot `[esp+0x18]`. The compiler listing of trial 06 explicitly overlays `_count$` and `_position$` at stack offset 8. This difference affects target instructions at `+0x08`, `+0x21`, `+0x25`, `+0x68`, `+0x72`, `+0x10e`, `+0x118`, `+0x122`, `+0x13c`, and the division home at `+0x15c`. Initial instruction lengths and loop padding differ; each frame-removal instruction at `+0x14f` and `+0x179` is two bytes shorter in the candidate, shifting the final block and constant relocation.

The strict scoped candidate gate fails in `build/worker-0023a550/scoped-gate-best.txt`. No subsequent string, constant, or DIR32 gate success is claimed because the byte comparison stops that run. Reopening requires new evidence for a source lifetime or compiler setting that reserves the extra frame word without changing the established call sequence and x87 accumulation. Repeating signedness, allocation-size guesses, coordinate spelling, iterator scopes, count-reference inlines, or the already tried volatile and one-element-array count shapes does not supply a new hypothesis. A future exact candidate would still need an identified virtual caller or equivalent independent ABI evidence before claiming all caller checks complete.
