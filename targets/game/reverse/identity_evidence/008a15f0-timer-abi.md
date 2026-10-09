# RVA 008A15F0 timer ABI and measured retry

## Result

This is a partial reconstruction of `?tickIntervalTimers@Rva008A15F0Owner@@QAEXH@Z`, not an exact recovery. The tested base revision is `8f26c14f94d2b5c649632698b9c1fca730f4dccc`. The complete target occupies RVA `0x008A15F0` through `0x008A18BD` inclusive. The preferred source retains every established bank name. No function ledger row, pin, shared header or production source changes in this retry.

The measured saved body emits 721 bytes with 460 differing non-relocation bytes. The retained candidate emits 721 bytes with 404 differing non-relocation bytes. Its positional ranking score is 0.4290, calculated by `1 - (differing bytes + 2 * abs(candidate size - retail size)) / retail size`. Probe reports sixteen relocation operand alignment drifts and eighteen structural differences. These are positional diagnostics, not semantic coverage or byte equality. `build/008a15f0-retry/measurements.json` stores the measurements; each entry names its unedited probe log and immutable trial source.

The useful changes are an indexed active-member guard, an in-class record lookup returning a reference through integer byte-address arithmetic, and consumption of only the low byte of the existing predicate's canonical integer return. The guard restores retail's test-before-address sequence. The address expression restores the initial SIB operand order. The narrow predicate consumption agrees with retail without changing its canonical declaration.

## Retry hypothesis and prior blockers

The initial hypothesis was that the landed queue-flush and cleanup layouts, the existing opaque hub pin, and in-class timer/value accessors would remove the earlier layout/callee blockers and the function-pointer spill. It would be refuted as a useful retry if measured candidates addressing those contracts failed to improve on the independently reprobed saved body.

The saved body already uses the landed `Rva008A1940QueueFlush.cpp` stack model. Consequently, missing owner identity and an unmatched hub body do not make this target's physical call ABI ambiguous. The accessors did not improve the code. Indexed lvalues improved the measured body, so the retry was not wholly refuted. The remaining obstacle is compiler shape, principally the timer/function register roles and the method spill. No unresolved owner identity is used to justify a blocker or a new semantic name.

## Boundaries and control flow

`build/008a15f0-retry/retail-008a15f0.txt` preserves the complete retail decode, including following bytes. The target has one return instruction at `+0x2CB`, `ret 4`, after all four callee-saved register restores and release of its twelve-byte local frame. Two following `INT3` bytes precede the next aligned function. All direct conditional and unconditional branches remain inside the extent and land on decoded instruction starts. The negative-capacity path joins the epilogue after the EBX/EBP restores that are needed only on the entered-loop path. The active-count exit at `+0x2A2` reaches those restores. There is no outgoing tail jump and no EH frame in this target.

The complete extents independently decoded and passed through `checked_callees.py` are target `008A15F0/718`, caller `00892A70/258`, hub `008CF740/2353`, predicate `008A0F20/31`, diagnostic helper `008A0F40/170`, pop helper `008A0CF0/61`, release-all helper `008A1020/44`, and landed cleanup neighbour `008A1460/392`. Each has a raw `retail-<rva>.txt` and `callees-<rva>.log` under the task directory. All requested extents decode completely, and the branch checker reports no external branches. Complete decoding alone is not the boundary proof; the terminal returns, internal exits and following padding were also inspected.

## Calling convention and return evidence

The complete caller at `00892A70` loads the owner into ECX from the holder global, reads the elapsed step as a dword into ESI, pushes ESI at `+0x52`, and calls this target at `+0x53`. This matches an ordinary ECX receiver with one four-byte stack argument and `ret 4`. The caller's separate private EAX input convention does not extend into this call. Target `fild [esp+0x20]` interprets the elapsed dword as a signed integer when converting it to float. There is no receiver adjustment or hidden return storage at this call; the result register is not consumed.

The complete hub has ECX as the interpreter receiver, first stack argument as receiver value, second as callable value, and third as a signed count. Its entry takes the callable from `[esp+0x38]` after two register saves, corresponding to `[esp+0x40]` after all saves; the other arguments are `[esp+0x3C]` and `[esp+0x44]`. Its one common epilogue ends in `ret 0x0C` at `+0x92E`. The native branch at `+0x53` calls the callable's `+0x20` callback as cdecl with receiver/count, removes eight bytes, and places the returned value on the interpreter's primary stack. The scripted paths use callable fields `+0x28` and `+0x30`. The target's hub calls push count, function and receiver, then load the singleton interpreter address into ECX. The target receives the result through its value stack; it never consumes EAX. The canonical opaque `Rva008CF740::run` declaration and existing pin are retained. `pin-hub.log` independently reports the pin consistent with the actual hub extent.

The complete `008A0F20` predicate returns full EAX values zero and one on its two exits, with plain RET and no stack arguments. Retail target `+0x190` tests AL only. The source keeps canonical `int isKind13() const` and explicitly casts the consumed result to `unsigned char`. The complete `008A0F40` helper reads its text argument as a four-byte pointer, uses receiver `+0x7C`, and ends with `ret 4`; it takes no hidden return object. The complete `008A0CF0` helper takes a signed dword count, invokes release for each applicable primary-stack element and ends with `ret 4`. The complete `008A1020` release-all helper takes only ECX and ends with plain RET.

Indirect calls were checked separately. Primary-stack insertion and pop read the value's dword flags at `+4`, test bit 30, and conditionally call vtable slots `+0` and `+4` with ECX equal to that value and no stack arguments. The invalid-timer path releases its function unconditionally through slot `+4`. No virtual return is consumed. These are physical dispatch contracts; the original virtual method names are not independently proved by this retry.

## Records, argument payloads and ownership

Target accesses establish owner records at `+0x1230`, active count at `+0x1234`, and a thirty-two-byte record stride. Record `+0` is tested for zero and cleared on removal. `+4` supplies the callable pointer. `+8` and `+0x0C` are accessed through x87 single-precision loads/stores as period and remaining time. `+0x10` supplies the receiver value. `+0x14` is the signed count used in both reverse argument loops. `+0x1C` is the storage pointer; its elements are four-byte value pointers because each loaded element becomes the receiver of the flag read and retain call. The release-all helper independently uses record `+0x14` and `+0x1C`, releases the current last element and decrements the count. Its ECX is the record base, with no `+0x14` receiver adjustment. The complete cleanup neighbour corroborates the same owner, stride, callable and argument-release offsets.

No STL container value type is inferred here, and there is no allocation-size inference. The inherited `m_capacity` label at `+0x18` is not read by this target or its release-all helper, so its original meaning remains unproved. The inherited `m_active` pointer type also remains a view: this target establishes only its zero test and zero store. These inactive fields do not support a stronger original class claim. The value header's bit15 validity and bit30 permanence, and the callable's `+0x28/+0x30` extension, are witnessed by the complete target and hub; the base class name remains the established bank spelling.

The three data declarations used by the candidate already have DIR32 records: holder `g_bfmeHolderBU`, primary interpreter view `Rva01338748State`, and fallback value `g_bfmeFallbackDB`. The float zero is a literal. No image address appears as a source numeric literal and no new pin is introduced. The interpreter declaration is a partial view of the primary stack, not a claim that the landed interpreter has no further members.

## Identity and limits

The literal passed to the diagnostic helper at target `+0x241` is `tickIntervalTimers`; the existing EA chain names `AptAnimationPoolData::tickIntervalTimers`. This supports keeping the established method name, but does not prove the BFME1 owning class layout. `Rva008A15F0Owner` therefore remains address-derived. The caller proves physical ownership through the same holder receiver; it does not supply a semantic owner name. The hub's original method and class identity likewise remain unproved, so its address-derived canonical declaration stays unchanged.

Constructor unwind checks are not applicable to the target because it constructs no owning temporary and has no EH prologue. The diagnostic helper's existing owning-string cleanup remains in its landed TU and is not replaced in the retained candidate. No runtime or exact byte-match claim is made.

## Remaining mismatch and reopening condition

The first differing byte is `+0x16`: retail stores the active countdown in the earlier frame slot, while the candidate stores it four bytes later. The loop-index store at instruction `+0x21` uses another earlier slot. The first ordinary register-role difference is target `+0x58`, where retail retains the timer in EBX and the candidate retains it in EBP. Retail loads the callable into EBP at `+0x6C`; the candidate uses EDX and spills it at `+0x7A`, then reloads it after retain calls. Retail spills the indirect method at `+0x181`; the candidate keeps it in EBX. Argument-array address formation at `+0xAA/+0x1BA`, a redundant count reload before the script loop, and receiver fallback branch layout follow these differing lifetimes. The candidate is also three bytes longer. Reopening needs a new, independently grounded local/value lifetime or native accessor arrangement that changes these roles, not another unchanged pointer spelling or x87 subtraction variant.

The ordinary scoped byte gate fails on the preferred bank, as expected; the raw output is `build/008a15f0-retry/scoped-byte-gate-banked.log`. Its relocation diagnostic reads the shifted candidate's operands at retail offsets, so its nonsensical reported callee addresses are drift diagnostics, not grounds to add pins. CSV validation passes in `check_csv-banked.log`, and the full pin-consistency check passes in `pin-consistency.log`. Class gate passes in `class-gate-banked.log`. The file-to-file `name_regression.regressions` check passes in `name-regression-banked.log`; this revision's CLI accepts Git revisions rather than file paths, so its first file-path invocation failed and is retained separately. Declared-unmatched reports the target itself as unclaimed, which is the reason the source is banked rather than placed in `game/`. No full gate is required for a bank-only change.

The bank tool initially generated LF metadata ahead of a CRLF body. The original bank's CRLF terminators were restored after recording, and the normalized bank was archived with `re_log.archive_attempt`. `line-endings-receipt.json` proves that every source line is identical before and after that change. The verdict's alternative archive preserves the pre-normalized incoming snapshot; the additional archive preserves the exact preferred file. There is still exactly one verdict row for this retry. An ordinary `git diff --check` treats the tool's CRLF attempt-log terminator as trailing whitespace; the row has no trailing space and the log is left in the repository tool's framing.

Final source SHA-256 before stash metadata: `8a863fb62453e7dca1672384fc1882fa16d8f047494b3a1b0260c62c7000ef7a`.

## Measured experiments

Every row below is generated from the raw measurement manifest. Trial sources and unedited probe logs are retained under `build/008a15f0-retry/`. These include negative results and comments-only final verification. No unsuccessful trial remains in production source.

| Trial | Candidate bytes | Non-relocation differences | Ranking score | Hypothesis |
|---|---:|---:|---:|---|
| baseline-recheck | 721 | 460 | 0.3510 | Saved body reproduced at independently decoded 718-byte extent |
| al-result | 721 | 460 | 0.3510 | Retail consumes AL only after the canonical int predicate; cast preserves the declared ABI |
| getActive-value | 721 | 460 | 0.3510 | In-class value accessor for the witnessed timer m_active |
| getActive-reference | 721 | 460 | 0.3510 | In-class reference accessor for the witnessed timer m_active |
| getFunction-value | 721 | 460 | 0.3510 | In-class value accessor for the witnessed timer m_function |
| getFunction-reference | 721 | 460 | 0.3510 | In-class reference accessor for the witnessed timer m_function |
| getReceiver-value | 721 | 460 | 0.3510 | In-class value accessor for the witnessed timer m_receiver |
| getReceiver-reference | 721 | 460 | 0.3510 | In-class reference accessor for the witnessed timer m_receiver |
| getIndirectValue-value | 721 | 460 | 0.3510 | Callable field accessor preserving independently decoded offset m_indirectValue |
| getIndirectValue-reference | 721 | 460 | 0.3510 | Callable field accessor preserving independently decoded offset m_indirectValue |
| getField30-value | 721 | 460 | 0.3510 | Callable field accessor preserving independently decoded offset m_field30 |
| getField30-reference | 721 | 460 | 0.3510 | Callable field accessor preserving independently decoded offset m_field30 |
| timer-accessors-together | 721 | 460 | 0.3510 | Combine timer value accessors after individual measurements |
| timer-reference | 717 | 416 | 0.4178 | Use a record reference so the countdown and expiry guard expose native indexed lvalues |
| active-indexed | 721 | 410 | 0.4206 | Retail tests the indexed active member before computing the cached record address |
| indexed-countdown | 721 | 410 | 0.4206 | Separate countdown array access from the record view reloaded after the store |
| stack-store-increment | 721 | 460 | 0.3510 | Retail writes the pointer array then increments count as separate operations |
| embedded-arguments | 721 | 460 | 0.3510 | The decoded argument access forms record+14 then loads its count and pointer+8 |
| callable-derived-view | 721 | 460 | 0.3510 | Use a callable subtype while preserving every witnessed base and descriptor offset |
| indexed-countdown-stack | 721 | 410 | 0.4206 | Combine the separately measured indexed record and split stack store hypotheses |
| timer-reference-stack | 717 | 416 | 0.4178 | Combine the separately measured indexed record and split stack store hypotheses |
| family-0 | 721 | 410 | 0.4206 | Finite family source structure: frame/copy/loop/SIB |
| family-1 | 721 | 410 | 0.4206 | Finite family source structure: frame/copy/loop/SIB |
| index-address | 721 | 410 | 0.4206 | Native record lookup exposes the indexed address operation with m_records + i |
| index-integer-right | 721 | 404 | 0.4290 | Native record lookup exposes the indexed address operation with (Rva008A15F0Timer *)(i * sizeof(Rva008A15F0Timer) + (unsigned)m_records) |
| index-byte-pointer | 721 | 404 | 0.4290 | Native record lookup exposes the indexed address operation with (Rva008A15F0Timer *)((char *)m_records + i * sizeof(Rva008A15F0Timer)) |
| record-byte-offset | 721 | 410 | 0.4206 | Retail keeps a byte offset and a separate slot index, reloading record storage around calls |
| record-array-wrapper | 721 | 410 | 0.4206 | Array wrapper preserves pointer+1230 and count+1234 while exposing operator[] |
| method-stack-storage | 737 | 447 | 0.3245 | Retail explicitly spills the indirect method before the invalid test and retains that storage through the predicate call |
| timer-no-cache | 694 | 427 | 0.3384 | Limit the cached timer lifetime by using the independently witnessed record lookup for each access |
| timer-short-cache | 709 | 421 | 0.3886 | Record cached view is used only before each branch invokes its callee, allowing loop-counter reuse |
| method-outer-lifetime | 721 | 404 | 0.4290 | Place method storage in the outer lifetime that retail shares with its frame counters |
| method-stack-load-once | 737 | 447 | 0.3245 | Materialize the witnessed method stack store before reading the value flags |
| kind-return-int | 721 | 404 | 0.4290 | Native inline predicate representation returns int while retaining its byte flags expression |
| kind-return-unsigned-char | 721 | 404 | 0.4290 | Native inline predicate representation returns unsigned char while retaining its byte flags expression |
| dedicated-predicates | 721 | 404 | 0.4290 | Retail repeats complete kind and validity predicates rather than retaining one generic discriminator |
| separate-kind-validity | 735 | 470 | 0.2981 | Expose six-bit discriminator and bit15 validity as the two native accessor operations |
| selective-flags-reload | 721 | 404 | 0.4290 | Limit observed reload semantics to full kind predicates, leaving ownership flag reads ordinary |
| flag-width-locals | 721 | 404 | 0.4290 | Flags stay full-width storage but native validity and permanence results consume one byte |
| flags-nonvolatile | 735 | 481 | 0.2827 | Test whether native aliases and predicate visibility explain retail reloads without volatile storage |
| visible-kind13 | 689 | 408 | 0.3510 | Compile the complete canonical predicate beside its caller to test callee register-preservation visibility |
| visible-pop1232 | 721 | 404 | 0.4290 | Compile complete stack-pop code to expose its actual receiver and register clobbers |
| visible-releaseAll | 721 | 404 | 0.4290 | Compile the independently decoded release-all helper preserving its receiver adjustment and member offsets |
| visible-helpers-together | 689 | 408 | 0.3510 | Expose all complete non-EH helper bodies together while preserving their out-of-line calls |
| loop-refresh-script | 719 | 425 | 0.4053 | Retail reuses the cached count for the first loop test and reloads the live record count at the backedge |
| loop-refresh-native | 719 | 521 | 0.2716 | Retail reuses the cached count for the first loop test and reloads the live record count at the backedge |
| loop-refresh-both | 705 | 520 | 0.2396 | Retail reuses the cached count for the first loop test and reloads the live record count at the backedge |
| loops-cached-record-condition | 697 | 498 | 0.2479 | Distinguish cached-record conditions from owner-array reloads after virtual retention |
| loops-count-condition | 709 | 492 | 0.2897 | Check whether the current live record-count reload is essential rather than the initial argument count |
| stack-globals-False-True | 721 | 404 | 0.4290 | Singleton stack accesses use recorded global declarations for the decoded count and pointer-array words |
| stack-globals-True-False | 721 | 404 | 0.4290 | Singleton stack accesses use recorded global declarations for the decoded count and pointer-array words |
| stack-globals-True-True | 721 | 404 | 0.4290 | Singleton stack accesses use recorded global declarations for the decoded count and pointer-array words |
| stack-global-array-local | 721 | 404 | 0.4290 | The decoded push loads argument-array storage before the count; express that actual storage lifetime |
| stack-array-local | 721 | 404 | 0.4290 | Read the canonical stack array through its local pointer before assigning the retained value |
| stack-count-reload | 742 | 470 | 0.2786 | Test whether explicit singleton count access ordering accounts for the observed pointer-first stack update |
| typed-canonical-member-call | 721 | 404 | 0.4290 | Typed member-pointer view preserves the canonical external symbol and the decoded same-offset value pointer ABI |
| typed-call-forwarding | 721 | 404 | 0.4290 | In-class typed forwarding presents the decoded receiver/function/count ABI without changing the external declaration |
| countdown-memory-lifetime | 737 | 527 | 0.2131 | The complete target stores and reloads remaining time through record storage, not a surviving x87 value |
| record-storage-reload | 782 | 552 | 0.0529 | The target reloads owner record storage after countdown and every potentially relocating helper call |
| callable-specific-fields | 721 | 404 | 0.4290 | Complete hub decode assigns +28/+30 to script callable values, so separate that witnessed extension from base value flags |
| script-local-view | 721 | 404 | 0.4290 | Script-only pointer lifetime begins after the kind10 guard rather than extending the generic record view through both dispatch paths |
| callable-field-type | 721 | 404 | 0.4290 | Represent the record callable field with the decoded callable extension while receivers and argument values retain the generic base view |
| argument-array-operator | 721 | 404 | 0.4290 | The decoded +14 aggregate has count/capacity/pointer; expose its indexed value operation with operator[] |
| method-array-storage | 721 | 404 | 0.4290 | Retail has a dedicated method stack home across its complete predicate call; test an ordinary aggregate lifetime |
| method-aggregate-storage | 721 | 404 | 0.4290 | Retail has a dedicated method stack home across its complete predicate call; test an ordinary aggregate lifetime |
| frame-three-live-words | 733 | 579 | 0.1518 | The complete retail frame has left/index/method at successive offsets +10/+14/+18 |
| final | 721 | 404 | 0.4290 | Best measured indexed-record body with comments moved to its function evidence note |
