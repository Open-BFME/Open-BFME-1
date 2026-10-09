# RVA 0x00743F80 camera callback

The recovered symbol is `?rva00743F80@W3DView@@UAEXXZ`. Its owner is W3DView, but its original method spelling remains unproven. The tested base revision is `dadca0aadeda7d0e7d4c6918a115c1b0dfe272c9`. This recovery replaces the generated 789-byte row and introduces no STL function claim or callee pin.

## Retry hypothesis and refutation

The earlier attempts tested the Zero Hour `updateView` wrapper and did not save a complete BFME reconstruction. The current ledger supplies the complete external ECX-reference `normAngle` declaration, matched W3DView camera bodies, the canonical Object layout and the canonical GameLogic lookup declaration. The hypothesis was that the remaining BFME operations could be reconstructed from complete decoding with those declarations. A mismatched receiver offset, helper route or complete call contract would refute it. Merely matching the donor wrapper could not address the missing BFME operations.

## Boundary and owner

The complete extent is RVA `0x00743F80` through `0x00744294`, inclusive. The final instruction is `ret`; the following bytes are alignment padding. All conditional branches remain inside the extent. The two other exits are the display-height virtual tail jump at `0x00744279` and the direct `setCameraTransform` tail jump through ILT `0x000312A0` at `0x0074428B`. All paths release the same frame and saved registers.

The W3DView primary table at VA `0x011217A0` contains VA `0x00415D7F` in slot 149. That complete five-byte ILT jumps to this target. The constructor at RVA `0x00745B10` installs the table into the primary receiver at `0x00745B5D`. Independently matched W3DView init, reset and deleting-destructor slots establish the owner. The new method retains its address because the shipped Zero Hour wrapper does not identify these additional BFME operations. A table route to a different target or a different primary receiver would refute the owner or slot claim.

## Complete call contracts

| Target or virtual slot | Decoded contract and source declaration |
|---|---|
| ILT `0x00022C96` to `0x00383480` | Complete seven-byte pause accessor reads one byte at receiver `+0x11C`, returns AL and uses plain RET. The caller supplies the GameLogic receiver without adjustment. Reuse `BfmeGameLogicPause::isGamePaused`. |
| `0x0073A900` | Complete 134-byte angle helper reads and writes the float addressed by ECX, has no stack argument, preserves EDX and ends with plain RET on both paths. Reuse the externally matched `void __fastcall normAngle(float &)`. |
| ILT `0x0001F253` to `0x0009A510` | Complete 82-byte lookup accepts one four-byte ID, returns the Object pointer in EAX and uses RET 4 on every return. It compares node `+4` with the ID and returns node `+8`; its bucket links are four-byte pointers. Reuse `GameLogicObjectLookup.h`, without adding any STL row or pin. |
| ILT `0x000312A0` to `0x007423B0` | Complete 679-byte camera-transform helper uses the unadjusted primary receiver, no stack arguments and plain RET. Reuse the existing private W3DView declaration for both the call and tail jump. |
| W3DView slot 114, `+0x1C8` | ILT `0x00026864` reaches the complete seven-byte body `0x00746080`. It returns receiver byte `+0x2439` in AL, uses no arguments and has plain RET. The opaque virtual declaration returns `unsigned char`. |
| W3DView slot 116, `+0x1D0` | ILT `0x0002F207` reaches the complete seven-byte body `0x0045BF80`. It returns receiver word `+0x88` in EAX with plain RET. The target pushes that word as the lookup ID. The declaration retains the body address. |
| W3DView slot 27, `+0x6C` | ILT `0x00039220` reaches complete 58-byte setter `0x0073D880`. It reads one four-byte argument and uses RET 4 on both exits. It writes receiver `+0x23BC` or dispatches that same value. The target passes zero with the original receiver. |
| Display slots 11 and 12 | Table VA `0x0111EDD0` routes through ILTs `0x00015CF8` and `0x00044206` to complete four-byte accessors `0x0040F520` and `0x0040F530`. They return receiver words `+8` and `+0xC` in EAX with plain RET. The target's signed FILD followed by the `2^32` correction proves unsigned conversion. The declarations match the reference Display width and height getters. |

The target consumes no incoming stack arguments or hidden result storage. Its early plain RET and the void camera-transform tail exit agree with the void callback declaration. The final Display getter result is incidental to that tail exit. An executable opcode screening for indirect calls through slot 149 found no hits, so no named caller is asserted. The method spelling is unresolved, rather than supplied by the probe.

## Layout and data evidence

The target directly reads Mouse signed coordinate words at `+0x4D10` and `+0x4D14`; each is converted with FILD without the unsigned correction. Object x and y come from the canonical Thing position at `+0x38` and `+0x3C`. The copied destination is the W3DView coordinate at `+0x0C`, `+0x10` and `+0x14`; z is set to float zero. The existing coordinate and Object headers are included.

The target reads and writes the heading float at receiver `+0x28` and the opaque float at `+0x70`. The latter is not named as a native pitch member. It clears the independently witnessed movement byte at `+0x1DC`, the scripted-lock byte at `+0x27D` and the opaque word at `+0x2354`. It compares the opaque word at `+0x2490` with four. The reference constructor and matched camera siblings support the known member names. Every other accessed member retains an offset or address identity.

Existing DIR32 names are reused for GameLogic, Display, Mouse, the flag at VA `0x012F9DB8` and `BfmeCameraGlobal12F9DBC`. Previously unrecorded settings and accumulator globals receive address-derived names whose exact operands are recorded in `dir32_addresses.csv`. Every new float datum is accessed with four-byte x87 instructions; the mode flag is read as one byte. The pointer global at VA `0x012F9E28` is only null-tested, dereferenced to write float one at `+0xB0`, then cleared. Its pointee uses an address-derived field view without asserting an owner or destructor.

There is no target exception handler, allocation, owning temporary or container construction. Constructor unwind and value-constructor checks therefore do not apply to this target. The shared lookup header is used only for an already independently verified callee declaration.

## Compiler experiments and retained evidence

The first complete trial emitted 760 bytes. Adding the decoded middle-region branch emitted the full extent. Copying the heading delta before clearing its global reproduced retail's store order. Scalar cursor locals still occupied separate stack storage. Reusing the same native `Coord3D` for cursor coordinates and the subsequent tracked position reproduced the frame overlap, including the float-to-integer conversion scratch slot. Adding a block around the late tracked-object local did not change that residue. The frame-family generator found no applicable transformation.

The exact body was recompiled after canonical GameLogic-header adoption and again at its final game source path. Raw, unedited output is retained under `build/target-00743f80/`: `probe01.txt`, `trial02.probe.txt` through `trial06.probe.txt`, `final-source.probe.txt`, the trial sources, `trial03.cod`, `decoded.txt`, `abi.txt`, `virtuals.txt`, `callers.txt`, the per-extent `checked-*.txt` inventories and `measurements.jsonl`. `decoded.txt` contains every target and direct helper instruction; `abi.txt` contains complete virtual helper bodies and constructor evidence. Display accessor checks use the four-byte extent through RET, excluding INT3 padding. The running measurement is in `build/verdict.txt`.

## Landing checks

The verified `add_match.py` transaction and a separate scoped `build.sh` run pass. Their unedited logs are `build/target-00743f80/add-match.txt` and `build/target-00743f80/scoped-gate-bash.txt`. Constant references, DIR32 references, source claims and the body guard pass. The declared-unmatched, pin-consistency, class and name-oracle checks also pass; their logs use the corresponding check names in the same directory. The unchanged DIR32 record guard accepts the working-tree additions against HEAD. The CRLF-aware diff check passes. No shared header or shim was edited, so the header-triggered full gate does not apply.

`check_csv.py` reports one collection blocker: the new source exists but is not tracked in the index. This worker is forbidden to write Git metadata, so the coordinator must stage the source and rerun `python tools/check_csv.py` before committing. The raw failure is retained in `build/target-00743f80/check-csv.txt`; it is not reported as a passing check. The unrelated hatch-baseline rewrite performed by `add_match.py` was restored to the exact base file.
