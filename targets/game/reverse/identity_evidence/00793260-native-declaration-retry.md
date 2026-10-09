# W3DGadgetProgressBarDraw native declaration retry

The preferred reconstruction remains `targets/game/reverse/attempts/0x00793260.cpp`. This retry did not recover the target. Canonical declarations reproduced its existing shape, and exposing independently verified getters produced a worse shape. Reopening requires evidence for a different native local lifetime or visibility arrangement that removes the progress spill without changing the verified helper bodies. More declaration permutations alone are unsupported.

## Revision and experiment hypothesis

The tested revision is `15a1fd0d72d6f1eb0fbbc1cd0ec1e959c005748e`. The actual model is `gpt-6.1-sol`. The complete address-specific attempt history was retrieved before implementation; raw retrieval is retained in `build/00793260-retry/session-target.log`. The saved bank was probed at the independently checked retail extent before changing its declarations.

The hypothesis was that the bank's private GUI declarations, or missing visibility of the already recovered getter bodies, caused its progress register assignment and extra spill. Supporting context was the reconstructed BFME `inputs/reference/shims/gamewindow/GameClient/GameWindow.h`, the BFME manager shim, and the four getter definitions in `game/GameEngine/Source/GameClient/GUI/GameWindow.cpp`. Refutation was an unchanged first divergence and mismatch count with canonical declarations, or a worse shape with byte-identical visible getter bodies.

The nearest useful landed drawing source is `W3DPushButtonDraw_Thunk.cpp`; its ABI view agrees with the draw-data displacement and manager slots. The adjacent progress-bar image callback at RVA `0x00793A60` is only a return instruction, so it supplies no implementation layout or compiler-shape evidence. The target ledger still points to the original dump. The real getter rows exist at the destinations of all four calls. No new pin, header change or ledger row was needed.

## Complete boundary, identity and ABI evidence

The complete target decode contains 175 instructions from RVA `0x00793260` through the return at `0x00793488`. It allocates a `0x24` local frame, saves EBX, EBP, ESI and EDI, restores them on the sole return path, and is followed by interrupt padding. All direct conditional branches and jumps stay inside this extent. There is no exception handler or owning container in this function. The decoded target and every direct getter and thunk have retained `*-decode.log` and `*-checked.log` files under `build/00793260-retry/`.

The FunctionLexicon entry at VA `0x012BA520` contains the string pointer to `W3DGadgetProgressBarDraw`, the thunk VA `0x0040CF45`, and a zero word. That thunk jumps directly to RVA `0x00793260`. Raw table bytes and the pointed-to string are retained in `00eba520-data.log`. The complete caller at RVA `0x00793A70` pushes its stack argument, then ECX, calls the same thunk, removes eight argument bytes, returns one, and executes `ret 4`. Together these establish a void cdecl callback with `GameWindow *` first and `WinInstanceData *` second. The donor implementation in the GeneralsMD `W3DProgressBar.cpp` supports the callback's source owner.

The four actual direct call destinations are `winGetUserData` at `0x00478C70`, `winGetScreenPosition` at `0x004781D0`, `winGetSize` at `0x004782A0`, and `winGetStatus` at `0x00478480`, reached through their decoded ILT jumps. User data and status return a dword in EAX without stack arguments; their field offsets are `0x2C` and `0x08`. Screen position receives x then y pointers, reads the region origin at `0x14` and `0x18`, follows parent at `0x200`, returns zero and executes `ret 8`. Size receives width then height pointers, reads `0x0C` and `0x10`, and executes `ret 8` on both the successful and null-output paths. Its error return is minus three. The exposed definitions independently reproduce all four complete retail bodies with no relocations. Their compiler output and byte comparisons are retained in `helpers.log`.

The target's inlined color reads agree with the canonical BFME window shim and the complete donor accessors: draw-data bases are `0x48`, `0xB4` and `0x120`; each entry contains an image pointer, a color and a border color. Index zero supplies the background and index four supplies the bar. The separate instance-data argument supplies the state byte at offset eight. Progress is used with signed multiplication and signed division by one hundred; the incoming pointer bits are cast to the native `Int`, not converted through floating point.

The manager vtable at VA `0x01126ED0` routes slots `0xF8`, `0xFC` and `0x100` through decoded thunks to complete bodies at `0x00479ED0`, `0x00479F60` and `0x00479FF0`. Each has a complete `ret 0x18` epilogue and no outgoing direct branch. The target passes six four-byte stack arguments, with the canonical width argument represented by the `1.0f` bit pattern, and prepares ECX without receiver adjustment. These three implementations do not read the incoming receiver; they load TheDisplay instead. Their existing all-integer helper declarations preserve raw stack bits but are not independent evidence for the semantic type of the width argument. The fill body ignores width; the outline and line bodies forward that argument's bits. No return value is used by the target. Complete virtual-call evidence is retained in `manager-vtable-complete.log`, the three `*-virtual-decode.log` files and `checked-virtual-*.log`. Their existing opaque helper identities were left unchanged.

## Measurements and rejected shapes

All target probes used an explicit retail extent of 553 bytes. The difference column counts only overlapping bytes, as printed by `probe.py`; absent trailing bytes are counted separately. The raw logs are unedited subprocess output, and each trial source is retained beside its log.

| Trial | Emitted bytes | Overlap differences | Missing bytes | First differing byte | Raw probe |
|---|---:|---:|---:|---:|---|
| Original bank | 552 | 350 | 1 | `0x13` | `build/00793260-retry/baseline-probe.log` |
| Canonical window and progress accessors | 552 | 350 | 1 | `0x13` | `build/00793260-retry/native-probe.log` |
| Canonical manager added | 552 | 350 | 1 | `0x13` | `build/00793260-retry/native-manager-probe.log` |
| All four visible getters, corrected layout | 521 | 407 | 32 | `0x02` | `build/00793260-retry/visible-getters-corrected-probe.log` |

The baseline's diagnostic equality fraction is `(553 - 350 - 1) / 553`, approximately `0.3653`. Its inherited score label is an author estimate and was not rewritten. This fraction is not a byte-verification or semantic acceptance result, particularly because eight object relocation sites do not line up with retail operands.

The first differing instruction begins at `0x12`: retail moves EAX to EBX, whereas the bank moves it to EBP. The bank adds a progress spill at `0x20` before the screen-position call. Its background color remains in EBX across the first drawing calls, whereas retail spills that color and retains progress in EBX. The native declaration trials reproduced the original instruction and relocation result. The visible-getter trial has a smaller frame and moves progress onto the stack; the independently exact helpers therefore refute missing callee-body visibility as a sufficient fix.

The first visible-getter trial had an incorrect parent displacement because its padding was computed from an incomplete size calculation. Its source and raw output remain as `visible-getters.cpp` and `visible-getters-probe.log`; it is excluded from valid type evidence. The corrected trial uses the complete `WinInstanceData` size and puts parent at `0x200`. It reproduces the same target instruction shape while all four helper bodies independently match. Canonical declarations were tested in two unchanged register experiments; no further permutation was run after the assigned limit was reached. The earlier volatile-color, color-order, aggregate-color and generated spelling experiments were not repeated.

## Checks and preservation

The strict byte gate was run on an in-memory row pointing to the original bank, without changing the ledger. Baseline validation passed, and the scoped function comparison failed as expected. Its raw output is `build/00793260-retry/scoped-gate.log`; the reproducible invocation is in `scoped_gate.py`. This is a reconstruction mismatch, not an unrelated gate failure. `check_csv.py` and `pin_consistency.py --check` passed, with raw output in `check-csv.log` and `pin-consistency.log`.

No production source, generated dump, shared header or symbol pin changed. The original preferred bank is retained byte for byte. Trial sources, compiler experiment objects, receipts, complete decodes and raw checks remain under `build/`. There is no full-gate requirement from this evidence-only change, and no background task was left running. Exactly one verdict is appended for this retry.
