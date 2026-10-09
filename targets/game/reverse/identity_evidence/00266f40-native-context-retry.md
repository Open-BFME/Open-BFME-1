# RVA 00266F40: native context retry

## Result

The new declarations do not improve the existing reconstruction. Keep `targets/game/reverse/attempts/0x00266f40.cpp` as the preferred bank. This investigation does not recover any source bytes, change the assembly ledger row, introduce a pin or rename the bank. The tested base revision is `9d42fc335a1354469ab5d5358adda1a5eff834d3`; the actual model is `gpt-6.1-sol`.

## Hypotheses and evidence

The retry tests whether caller-visible accessors, the canonical GameLogic lookup, independently decoded helper parameter types or native multiple inheritance resolve the previous secondary-receiver and coordinate-lifetime blocker. Each hypothesis is refuted as an improvement when its complete compiled body scores no better than the saved body at the proven retail extent. Readable neighbouring sources were inspected directly: the SiegeDeploy constructor, state dispatcher, transition, status clearer, coordinate implementation and AI position commands. The matched BridgeBehavior donor uses an inline `memcpy` coordinate assignment; that implementation was tested rather than inferred from an earlier account.

The constructor at `00266240` installs the update-interface table at complete object offset `10`. Its slot zero goes through `00007DBA` to this target. The constructor places state, counter, target ID, position, toggle, delta and pending flag at complete object offsets `38`, `3C`, `40`, `54`, `60`, `64` and `70`. The target reads the object and module-data pointers at incoming receiver offsets `-8` and `-C`. The neighbouring transition reads state at complete object `38` and writes the same counter and target fields. The declarations retain the existing address-derived bank names. The EA name suggestion was not independently re-derived from the other game's binary.

The native inheritance trial receives the update interface, but an explicit complete-owner alias makes it retain an adjusted owner pointer and spill the incoming receiver. Removing that alias and using qualified member accesses recovers the original secondary-receiver shape. Neither that source nor the native UpdateSleepTime return enum fixes the register allocation. The target has no exception handler. Its stack coordinate constructors and destructors have no cleanup effects.

## Boundaries and contracts

The complete executable interval is `00266F40..002671E9`, followed by the three-byte alignment instruction and five-entry switch table ending at `00267200`. Every switch target is an instruction boundary inside the executable interval; every return and conditional destination was inspected. The following bytes are INT3 padding. The full ledger extent fails the helper's linear decoder because it includes table data, while `checked_callees.py` succeeds on the complete executable interval. No boundary correction is justified. Raw data and full decoding are retained under `build/266f40-retry/`.

`001F8AB0`, reached through `0002FC7A`, is a one-pointer cdecl lookup that returns a module pointer or null. Its stack argument, module walk at Object offset `1F0`, NameKey comparison and both returns were decoded. This is not evidence for the inherited WorkerAIUpdate or pool identity. `001F84C0`, through `0003C740`, takes only ECX, releases six owned pointer slots guarded by receiver offset `3C`, and returns without stack arguments. Calls remain address-qualified.

`001F9180`, through `0003BFF7`, consumes an optional twelve-byte coordinate output pointer and returns a Boolean in AL with `ret 4`. Its fallback copies every coordinate word from its owner's Object position. Its other path constructs sixteen coordinates, selects one from the indexed record, optionally writes all three words to the output, calls the ground predicate, destroys the array and returns that predicate's AL. The old bank's integer parameter therefore has the correct physical stack width but the wrong payload declaration. The pointer correction was measured and produces the same target bytes. The actual array callbacks reach the complete empty Coord3D constructor at `00083330` and destructor at `0005BC40`; the complete copy constructor at `0005BC20` copies all three words.

`001F1370`, through `0001336D`, takes ECX plus two dword arguments and returns with `ret 8` on both exits. It builds command `31`, copies the first argument to the payload word and the second to the command-source word, then dispatches through its receiver's slot zero. The target supplies AI plus `20`, zero and source value two. Its inherited destructor name is not used as ABI evidence. `002666A0`, through `00020455`, consumes hidden result storage followed by Object pointer, coordinate output pointer and Boolean pointer, writes every return-coordinate word, returns the storage pointer in EAX and finishes with `ret 10`. Its complete branches and exits were decoded.

The primary AI table installed by its constructor independently routes slot 96 through `000042BE` to `00278720`, slot 122 through `00021DFF` to `0026F590`, and slot 128 through `0000F17D` to `0027F460`. Their complete bodies support the idle Boolean, void goal-clearer and dword command-source return contracts used by the target. These are primary-table checks, not an audit of every derived override. The Object primary table routes slot 10 through `0002074D` to the complete seven-byte Drawable pointer getter at `001BE440`. Unknown slot names in the bank are retained.

The full AI position-command bodies at `000D86C0` and `00266A30` consume a coordinate pointer and command-source dword with `ret 8`, copy all three coordinate fields into their command payload and dispatch through the command receiver. The bank's class-key Coord3D command declarations are unresolved by the current symbol map, whose canonical command spellings use the struct key. Trial 19 calls the independently decoded existing ILT routes without adding a pin. Its scoped gate has no unresolved calls, but still fails byte comparison. This fixes a binding problem, not the reconstruction mismatch.

## Measurements and rejected shapes

Every measured source and unedited probe output is retained under `build/266f40-retry/`. Each listed trial has one probe measurement (n=1); the saved body was additionally rechecked by a second probe and the finite baseline search. `metrics.json` is generated from those logs with `finish_measure.parse`; missing bytes are penalized by that tool's size-error term. Scores are probe quality, not strict gate receipts. The family generator supplies no applicable edits for this bank; the finite search therefore measures only its unchanged baseline. The finite-search trial and result manifest are also retained under `build/shape_search/a3917517feb34c7bbd6bb44b1b593041/`.

| Trial source in `build/266f40-retry/` | Compiled bytes | Non-relocation differences | Measured quality |
|---|---:|---:|---:|
| `00-saved.cpp` | 700 | 468 | 0.3239 |
| `01-position-accessor.cpp` | 700 | 468 | 0.3239 |
| `02-native-accessors.cpp` | 700 | 468 | 0.3239 |
| `03-output-pointer.cpp` | 700 | 468 | 0.3239 |
| `04-visible-lookup.cpp` | 700 | 468 | 0.3239 |
| `06-const-module-input.cpp` | 700 | 468 | 0.3239 |
| `08-native-ai-bases.cpp` | 700 | 468 | 0.3239 |
| `09-neighbor-eh-flags.cpp` | 700 | 468 | 0.3239 |
| `10-base-copy.cpp` | 688 | 457 | 0.3054 |
| `11-direct-output-helper.cpp` | 700 | 468 | 0.3239 |
| `12-direct-command.cpp` | 700 | 468 | 0.3239 |
| `13-inline-base-copy.cpp` | 700 | 468 | 0.3239 |
| `14-native-owner-bases.cpp` | 740 | 461 | 0.2429 |
| `15-implicit-native-this.cpp` | Compile failure | Not measured | Not measured |
| `16-qualified-native-this.cpp` | 700 | 468 | 0.3239 |
| `17-donor-memcopy.cpp` | 700 | 468 | 0.3239 |
| `18-native-return-enum.cpp` | 700 | 468 | 0.3239 |
| `19-verified-command-routes.cpp` | 700 | 468 | 0.3239 |

## Remaining blocker and reopening condition

The first byte difference remains the saved-register choice at `+3`. Retail keeps the owner Object in EBP and the target Object in EBX; the bank mirrors those registers. That mirror removes the zero displacement on the first vptr load and shifts subsequent operands, branches, relocations and switch alignment. Retail also moves the module receiver into ECX before pushing the null output pointer; the bank pushes zero first. `normalized-residuals.json` compares the complete executable streams after explicitly swapping EBX and EBP and masking address operands; its remaining insertion/deletion is that push order. This normalization is diagnostic and proves neither byte equality nor identity.

Reopen only with a concrete source or compiler-context hypothesis that changes this allocation or call setup, or independently reconciles the coordinate command declarations. Repeating pointer declaration order, aggregate scope, accessor spelling, visible GameLogic lookup, native AI inheritance, direct helper declarations, neighbouring EH flags, base-copy delegation, donor memcpy assignment, complete-owner aliases or return-enum changes without new evidence is not justified. Preserve the existing bank and the binding-complete trial 19; neither is a recovery.

## Checks

The retail baseline, CSV integrity and pin consistency pass. Both scoped byte gates fail on the assigned body. The saved-bank gate also reports the two class-key coordinate command declarations unresolved; the trial-19 gate reports no unresolved calls. The raw receipts are `build/266f40-retry/scoped-gate.log`, `19-scoped-gate.log`, `check-csv.log`, `pin-consistency.log` and `checked-all.log`. No source, shared header, shim, function row or pin was changed, so no full gate is required.
