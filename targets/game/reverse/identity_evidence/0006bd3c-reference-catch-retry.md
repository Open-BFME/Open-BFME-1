# Retry of engine continuation 0x0006BD3C

The assigned 611-byte row remains an interior continuation of the complete 959-byte body at RVA 0x0006BBE0. This run preserved a corrected complete-parent reconstruction in `targets/game/reverse/attempt_history/0x0006bbe0/f1c4b9ad266cf84e945109c0d0d9892139695a5712fbcf8dff24f4d8bdce88eb.json`. It did not land a function, repoint a ledger row, add a pin, or certify the archived source for production. The tested revision is `e082f8cba2b8244952bf93de9ad343f95f83db26` and the model is `gpt-6.1-sol`.

## Hypothesis and falsification

New landed context provides readable implementations for Watchdog update and stop, the pause-aware clock, ScriptEngine isTimeFast, and GlobalLanguage onGameEngineExit. The hypothesis was that checking their real ABI and the parent exception metadata, then using canonical calls or the visible matched clock, could improve the old parent draft without inventing a standalone entry for the continuation. It would be refuted as a byte-progress hypothesis if complete-parent probes and normal relocation resolution retained the old mismatch or worsened it. That is what the measurements show. The exception declaration nonetheless required a semantic correction independently of byte progress.

## Complete extent and receiver

The full retail decode is retained in `build/target-0006bd3c/parent-retail.disasm.txt`. Entry RVA 0x0006BBE0 establishes EBP and the FS registration, saves EBX/ESI/EDI, transfers ECX to EBX, and saves the receiver at EBP-0x1C. RVA 0x0006BC39 branches over the catch handlers to the assigned start. RVA 0x0006BED9 branches outside the assigned fragment to 0x0006BC20 and RVA 0x0006BEE4 jumps to 0x0006BC19. The common exit at 0x0006BF8E restores the original FS/stack/register state and returns at 0x0006BF9E; padding starts at 0x0006BF9F. The complete parent has no outgoing conditional branch or tail jump. The fragment cannot be reconstructed or renamed as an independently called method. A decoded endpoint at 0x0006BF9F does not fix its interior start.

The working identity `GameEngine::execute` is retained from the archives. The decoded ILT at 0x000173E6 targets 0x0006BBE0, and pointer tables at VA 0x01075BD8 and 0x0111C9B8 place that ILT at slot +0x18 beside thunks to already named FPS and quitting accessors. These observations corroborate the family and virtual slot; this run did not independently recover each table's concrete dynamic owner or decode every virtual target. The inherited receiver layout agrees with the landed GameEngine update and pacing sources at +0x08, +0x0C and +0x30. No shared GameEngine header is registered in the current canonical class table.

## Exception evidence

Retail handler RVA 0x00BF2AF0 loads FuncInfo VA 0x011E00E0. Its unwind states are 0 to -1, 1 to -1, 2 to 1 and 3 to 1, all without a cleanup action. Try map entry 0 covers state 2 and catches everything at RVA 0x0006BD33. Entry 1 covers state 0 and has an INIException handler at RVA 0x0006BC3E plus the catch-all at 0x0006BCB9. The typed entry has adjective 8, the class descriptor `.?AVINIException@@`, and catch displacement -32. The nested catch-all returns the address of 0x0006BCED; both main catches resume via 0x0006BD39. Thus the getter-looking neighbouring six-byte row is a nested catch handler within this parent, not independent ownership evidence.

The archived pointer catch emits adjective 0 and `??_R0PAVINIException@@@8`. Replacing it with `catch (INIException &e)` emits adjective 8 and `??_R0?AVINIException@@@8`, matching retail's class-reference metadata. This correction does not change the parent instruction stream. Its generated catch displacement is still -24 rather than retail's -32. Raw metadata is in `build/target-0006bd3c/retail-eh.txt`, `object-eh.log` and `eh-best-canonical-calls.log` in that task directory. The four unwind predecessor values and the two try-map ranges agree with retail; there is no catch-owned destructor or other parent cleanup to reconstruct.

The complete INIException constructor at RVA 0x00850600 writes the message pointer at +0 and count at +4. The complete copy constructor at 0x00061BB0 invokes the 106-byte assignment helper at 0x00850670, which reads and writes both +0 and +4, handles self assignment and null text, and copies the owned message. The destructor at 0x00061BD0 reads +0 and calls array deletion. All these extents and return paths were decoded and passed checked_callees inventory. They support the existing two-field BFME exception declaration in `inputs/reference/shims/iniexception/Common/INIException.h`; the four-byte Zero Hour donor is insufficient. Their raw decode is retained in `build/target-0006bd3c/exception-and-shutdown-retail.disasm.txt`.

## Callee and ABI checks

Every direct parent target was followed through its decoded ILT, and checked_callees was run for the complete parent, fragment, Watchdog update/stop, clock, ScriptEngine, language exit, recorder mode/multiplayer/cleanup, debug callsite helper and ftol2. Complete decoded helper bodies are in `build/target-0006bd3c/helpers-retail.disasm.txt`. Watchdog update takes ECX with no stack arguments, compares the parent thread at +0x50, and writes the heartbeat at +0x54. Stop consumes the owned lock at +0x90, clears it, and tail-jumps to the complete 35-byte ThreadClass stop body. The clock has no arguments, returns EAX on both paths, and reads/writes both dwords of the elapsed time. ftol2 consumes the x87 value and produces EDX:EAX; the parent uses its low dword for the frame limit. Recorder mode returns a dword, multiplayer returns AL, and cleanup is a one-byte return. The reference catch has no hidden return storage or exception copy call.

The parent independently witnesses no-argument virtual calls through ECX, dword results for view multiplier, frame headroom/status/player count and client frame, and an AL test for packet-router status. The crash-report chain passes two zero pointer slots to +0x6C, one text pointer to +0x38, and a four-byte slot containing one to +0x4C; pointer results flow through EAX. Independent complete dynamic-target verification of these virtual slots remains unresolved. Existing bank names are retained as inherited names, not promoted to independently proved identities.

## Measured experiments

All source snapshots and unedited subprocess output remain under `build/target-0006bd3c/`. The old archived draft was restored with current include paths before its first probe. Every new experiment checked `build/STOP_WORKER`. No register or x87 spelling sweep was performed.

| Source snapshot | Explicit retail extent | Compiler result | Raw probe output |
|---|---:|---|---|
| baseline.cpp | 959 | 959 bytes; 3 differences | probe-baseline-raw.log |
| catch-reference.cpp | 959 | 959 bytes; same 3 differences; correct reference type metadata | probe-catch-reference.log |
| symbolic-globals.cpp | 959 | 945 bytes; probe reports 569 differences and 81 relocation-site alignment failures | probe-symbolic-globals.log |
| canonical-callees.cpp | 959 | Same 945-byte symbolic-global result | probe-canonical-callees.log |
| visible-clock.cpp (parent) | 959 | Same 945-byte symbolic-global result | probe-visible-clock-parent.log |
| visible-clock.cpp (clock helper) | 49 | 49 bytes exact modulo relocations, single probe | probe-visible-clock-helper.log |
| best-canonical-calls.cpp | 959 | 959 bytes; 3 differences; no unresolved calls after normal resolution | probe-best-canonical-calls.log |
| preserved-parent.cpp | 959 | 959 bytes; same 3 differences after archive formatting | probe-preserved-parent.log |

The 945-byte candidates omit 14 bytes as well as the reported diagnostic differences. Their relocated operand positions drift, so those masked difference totals are diagnostic lower bounds, not a trustworthy exact quality score. They were rejected and did not replace the better draft. A static noinline copy of the actual matched clock has the same 49-byte shape and avoids a second strong definition, but its visibility does not improve the parent. The corrected best draft keeps the archived Watchdog method names as inline forwarders to the already landed update and stop methods, resolving their calls without a new pin.

Normal repository relocation resolution of the best complete parent has no unresolved calls and differs at +0x60 (retail E0, ours E8), +0x1B9 (retail E8, ours E0), and +0x285 (retail E8, ours E0). These are the catch-pointer load and oldScale store/load displacements. The assigned 611-byte continuation slice of that compiled parent differs at +0x5D and +0x129. This slice comparison is not a standalone function probe or an ABI claim. Its authoritative raw output is `build/target-0006bd3c/measurement-raw.log` and parsed measurement is `measurement.json` in that directory.

## Preservation and gates

The complete corrected draft is preserved with repository `re_log.archive_attempt` as `targets/game/reverse/attempt_history/0x0006bbe0/f1c4b9ad266cf84e945109c0d0d9892139695a5712fbcf8dff24f4d8bdce88eb.json`, using normal resolved-byte quality at the explicit 959-byte extent. The old archives remain intact. No preferred stash was created: re_log stash measurement would incorrectly use the current 94-byte parent ledger row, and banking this body under the 611-byte continuation would misrepresent both start and extent. The archive retains its inherited numeric global expressions solely as failed reconstruction evidence. Production source still requires recorded symbolic globals and ordinary constants.

`build/target-0006bd3c/gate-best-canonical-calls.log` contains the repository scoped byte gate using an in-memory candidate row at the independently decoded parent extent. It fails exactly the three displacement bytes and has no unresolved calls. `gate-best-parent.log` preserves the earlier failure with unresolved inherited Watchdog spellings. Pin consistency passed in `pin-consistency.log`. CSV validation passed initially and is rerun before handoff. Class gate passed for the preserved draft. The name_regression file comparison API reports no descriptive-name regression in `name-regression-file-api.log`; the checkout CLI accepts revisions rather than the file arguments its documentation advertises, so the initial invocation failure is retained separately in `name-regression.log`. No game source, ledger, symbol table, shared header, policy or tooling was changed. No full gate is required for this evidence-only outcome.

## Reopening condition

Reopen only with an authorized consolidation of the complete parent and its embedded catches, a new source-context hypothesis that can move the catch and oldScale slots without repeating the recorded type/order/lifetime sweeps, and independently checked virtual declarations. A complete landing must also eliminate inherited numeric image expressions and verify the generated EH metadata, not just parent bytes. The standalone assigned boundary is refuted by decoded backward control flow and its dependency on the enclosing frame; new proof of a separate ABI entry would have to explain those edges and the shared FS/EBP epilogue.
