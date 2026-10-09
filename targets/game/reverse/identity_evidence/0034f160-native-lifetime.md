# ScriptEngine::getTeamNamed at RVA 0034F160

## Result and reopening condition

This is a measured partial, not an exact recovery. The preferred body is `targets/game/reverse/attempts/0x0034f160.cpp`. The strict byte verifier rejects the final trial, and no function or symbol ledger row is changed. Reopen with evidence that changes the placement of the shared return block or explains the native warning-counter expression. Repeating the exhausted EH declaration variations, unchanged private layouts or unchanged helper visibility is not a justified experiment.

The tested base is `2bda6d63f1e99a4f5d22e17d6ebdb473e9f098b5`. The actual model is `gpt-6.1-sol`. All trial sources, original bank bytes, decoded retail instructions, compiled objects and unedited probe output remain under `build/f160/`. `build/verdict.txt` identifies the final body and the recorded single verdict.

## Measurements

These values are generated from the retained raw probe logs with `finish_measure.parse`, the repository's banking score implementation. Relocations are masked in this diagnostic; a score is not strict byte equality. Misaligned relocation sites prevent interpreting the reported byte count as a precise count of wrong source operations.

| Trial | Compiled bytes | Masked byte differences | First masked difference | Structural differences | Banking quality | Raw output |
| --- | ---: | ---: | --- | ---: | ---: | --- |
| Compilable saved body | 773 | 536 | +0x34 | 27 | 0.2183 | build/f160/00-baseline.probe.log |
| STLport selection | 766 | 517 | +0x34 | 13 | 0.2244 | build/f160/03-stlport.probe.log |
| Native bool accessors | 768 | 516 | +0x34 | 10 | 0.2304 | build/f160/05-native-accessors.probe.log |
| Native return lifetime | 833 | 476 | +0x4B | 2 | 0.4162 | build/f160/16-result-structure.probe.log |
| CPU preference | 830 | 466 | +0x4B | 5 | 0.4355 | build/f160/33-cpu-G7.probe.log |
| Size preference | 589 | 445 | +0x0 | 54 | 0.0000 | build/f160/35-native-size-preference.probe.log |
| Shared context return | 781 | 454 | +0x1C | 3 | 0.3366 | build/f160/38-shared-context-return-braced.probe.log |
| Shared returns throughout | 761 | 550 | +0x18 | 34 | 0.1725 | build/f160/39-shared-all-team-returns-braced.probe.log |
| Final preserved bank | 830 | 466 | +0x4B | 5 | 0.4355 | build/f160/43-final-native-flag-width.probe.log |

The final strict check uses `build.compile_function` and `build.verified_patch_eligible` with an in-memory row, the existing symbol map and the preserved compiled object. It changes no ledger. `build/f160/strict-byte-gate-43.log` records failure, no unresolved calls, and a claimed endpoint cutting the final `ret 8`. The final source and object are `build/f160/43-final-native-flag-width.cpp` and its `.obj`. The structurally closest default-CPU alternative is retained as `build/f160/16-result-structure.cpp` with its probe and object evidence.

## Identity and calling convention

The primary ScriptEngine vtable at VA 010E7A30 has `getTeamNamed` in slot 17, at byte offset 44 hexadecimal. The slot points to ILT RVA 00013692, whose complete five-byte jump reaches the assigned body. `build/f160/vtable.log` and `retail-00013692.txt` retain this route. The Zero Hour `GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h` places `getTeamNamed` between `runObjectScript` and `getSkirmishEnemyPlayer`. Its actual implementation contains the same THIS_TEAM path, context-team lookup, singleton handling, warning literal and team-list result. It supplies the semantic identity; its const-reference signature does not establish the BFME ABI.

The complete BFME caller at RVA 00329C20 constructs one four-byte AsciiString directly in the outgoing stack slot, pushes a false bool in a separate four-byte argument slot, and calls primary-vtable byte offset 44 hexadecimal without a receiver adjustment. It consumes EAX as a Team pointer. Every target return cleans eight bytes. The target compares the low byte of the second argument and destroys the by-value string on each return path. The declaration `virtual Team *getTeamNamed(AsciiString name, bool exact)` follows these decoded instructions. No hidden return pointer is used by this method. See `retail-00329c20.txt`, `checked_caller.log` and `retail-0034f160.txt`.

Vtable slot 44 decimal is a different method. Existing donors calling that slot are not identity evidence for this target.

## Boundary and callee coverage

The full assigned extent decodes through its last return. INT3 padding follows it. All conditional branch destinations are internal and instruction-aligned; there are no outgoing tail jumps or indirect calls in the target. `flow-audit-final.log` retains each return and all external branches for every investigated extent, rather than relying on an aligned endpoint alone.

`checked_target.log` inventories each real REL32 route. Complete decoded bodies and checked-callee logs are retained for the string comparisons, key construction and destruction, map lookup, mutable-name helper, team-ID lookup, prototype lookup, team creation, instance count, debug helper, string joining, string construction, string copying and buffer release. Raw `retail-XXXXXXXX.txt` files include lookahead past the proven returns. The external branches in unwind funclets and ILT bodies are followed through the actual thunks. There are no unresolved callee identities needed to compile or resolve the final main body.

The debug helper at RVA 0033C8E0 takes a string reference followed by a bool and returns with `ret 8`. Its dynamically resolved procedure call passes the character buffer as one cdecl stack argument, then cleans that argument itself; the procedure's return is unused. This indirect call is distinct from the target's direct call to the debug helper. The actual helper body, including the dynamic resolution path and return, is preserved.

## Container type and ownership

The team-reference map key has two AsciiString fields. The actual target's key constructor at RVA 00192D80 copies the first source reference into receiver offset 0 and the second into offset 4, both through the complete StringBase copy body at RVA 00887B60. That copy reads one source object dword, writes one receiver dword and increments the referenced buffer's count. The complete key destructor at RVA 000DFB20 releases offset 4 and then offset 0. Allocation size is not used as type evidence.

The related native `copyTeamReference` body at RVA 003455E0 reaches value construction at RVA 00194F60. The complete construction helper calls key copy through ILT 0001AB86 to RVA 00193760, which copies both string fields, and then reads exactly one payload dword and writes it at result offset 8. No other payload field is accessed. The complete reference-copy body transfers these fields into its insertion temporary and copies the source node's payload into destination node offset 18 hexadecimal.

The target reads that same node payload and passes it as one argument to `TeamFactory::findTeamByID`. The complete body at RVA 000EF060 compares it against Team offset 8 while traversing prototype instance lists. It returns a Team pointer or zero with `ret 4`. The landed Team constructor declares that field as unsigned `m_id`. This independent use establishes unsigned TeamID payload semantics. An existing insertion helper spelling using Team pointer payload does not establish this map's payload type and is not adopted.

The native `_M_find` implementation at RVA 003402A0 is decoded completely, including both returns. It compares the two string fields and returns the selected node or the sentinel. The native map layout places the team map at ScriptEngine offset 16064 hexadecimal; node value starts at offset 10 hexadecimal, followed by its payload at offset 18 hexadecimal. The adjacent landed `ScriptEngineCopyReferences.cpp` agrees with these accesses and supplies existing canonical STLport declarations and pins. No `_STL` row or pin is added or changed. The final trial emits its own non-matching map helper; no recovery of that helper is claimed.

## Native member and temporary lifetimes

Team name and owner resolve through its prototype pointer at offset 4. The prototype strings are at offsets 10 and 14 hexadecimal, its flags word is at 18 hexadecimal, and its instance-list head is at 274 hexadecimal. These accesses agree with the complete lookup and landed TeamPrototype constructor. Its entire retail body at RVA 000F3E40 is also decoded and checked; it writes the flags as one dword. The bank preserves its padding identifier as a flags-word union view. Team ID is a dword at offset 8; `m_active` and `m_created` are bool bytes at offsets 31 and 32 hexadecimal. The entire Team constructor at RVA 000F7790 is decoded and checked, including its ID dword and flag-byte stores. The active accessor explains the native AL test repeated before the activation stores. Native stores set created before active. These are member-access views; neither constructor nor ownership of unrelated padded members is claimed as a new recovery.

ScriptEngine context pointers are at offsets 1708C and 17094 hexadecimal. Its canonical-name fallback string is at offset 17088 hexadecimal. The actual mutable-name route is ILT 00036336 to `BfmeScriptEngineSlashName::bfmeName` at RVA 003398F0. It receives hidden result storage followed by a mutable AsciiString reference, reads the fallback at the stated offset, and returns with `ret 8`. Its complete cdecl helper at RVA 001945D0 constructs the prefix and can modify the supplied name. The canonical declaration is used at the call. The bank's descriptive `BFMEScriptEngineFlagLookup` and `canonicalFlagName` names remain as an unused declaration with corrected reference mutability, so no name correction or alias pin is invented.

The join helper at RVA 00195FC0 takes hidden AsciiString result storage and two references as cdecl stack arguments; the caller cleans three pointer slots. The created-team path uses the decoded factory argument order, canonical followed by the mutated name, and returns a pointer in EAX. Existing factory declarations and pins already resolve that call.

## Exception cleanup

The retail FuncInfo and all five unwind funclets are retained in `eh_retail.log` and complete decoded files. The final candidate's COFF FuncInfo and funclets are retained in `eh-43.log`. Their state predecessors, receiver adjustments and destructor targets agree:

| State | Predecessor | Frame receiver | Owned object |
| ---: | ---: | --- | --- |
| 0 | -1 | EBP + 4 | By-value argument string |
| 1 | 0 | EBP - 1C hexadecimal | Canonical string |
| 2 | 1 | EBP - 14 hexadecimal | Two-string key |
| 3 | 1 | EBP - 18 hexadecimal | Warning-string temporary |
| 4 | 1 | EBP - 18 hexadecimal | Joined-string temporary |

String cleanups reach ILT 0000D828, then the AsciiString destructor jump at RVA 0005EE90, then the full buffer release at RVA 00887940. Key cleanup reaches ILT 000444EA and the complete pair destructor. The key constructor, key copy and key destructor each have one unwind state. Their cleanup funclets load the saved receiver and follow that same AsciiString destructor route, protecting the first string while the second is constructed or destroyed. Their full state tables and funclets are retained in `helper-unwind.log`, with checked-callee logs for each cleanup.

The native EH ownership is thus established independently of the main byte comparison. Matching those states does not make the main body exact.

## Hypotheses and rejected experiments

The retry hypothesis was that landed neighbours and canonical helper declarations expose native types and temporary lifetimes missing from the saved body. It would be refuted if restoring those types and lifetimes produced no measured improvement over the compilable bank. The neighbour source actually selects STLport via its `// stlport` marker; the bank lacked that selection. Restoring it, using native bool accessors and retaining the created-team result restores much of the native instruction structure. The main hypothesis improves the diagnostic, but does not yield exact recovery.

The remaining return-layout hypothesis predicts the common EDI return block after the first context comparison. Retail places it at target offset CA hexadecimal; the closest default-CPU candidate places it at 288 hexadecimal, while the bank's CPU preference places it at 285 hexadecimal. The first masked difference is the branch displacement leading to that displaced block. The size preference and explicitly shared-return trials fail to improve the result. The CPU preference also changes the warning counter from native register load, increment and store into memory compare and increment instructions.

The finite EH generator tests callee exception specifications, EH mode and nothrow array delete. Its valid variations do not improve the saved instruction shape; a generated throw annotation on key construction is not valid evidence for the proposed native body. `mechanical.log`, `eh-choices.json`, `eh-results.json` and every raw source/probe are retained. The finite shape-family generator produces an adjacent-store-order choice. Reversing activation stores does not improve the result and contradicts native store order. See `family-search.log` and its preserved trials.

Making the ID lookup, mutable-name helper, instance count, createTeam and prototype lookup source-visible does not change the target's result. Const iterator, const map and const key views do not improve it. Polymorphic prefix views and native flags-word width do not change it. Explicit common return variables and corrected, braced goto forms do not improve the final candidate. Trials 36 and 37 contain unbraced multi-statement replacements and are rejected for altered control flow; their raw files remain preserved, and trials 38 and 39 are the meaningful corrected tests. Trial 40's forwarding wrapper is not inlined and creates an unresolved call; the final body calls the canonical helper directly and retains the old descriptive declaration without using it.

## Verification scope

The final strict byte gate fails for the assigned body, without unresolved symbols. The direct `name_regression.regressions` comparison against the exact original bank passes, as does `class_gate.py` on the final trial. Raw results are `names-43.log` and `class-43.log`. The checkout's name-regression CLI accepts Git revisions rather than two file paths, so the same underlying comparison is called directly with both complete texts, without Git writes.

`find_declared_unmatched.py --fail` on an unlanded scratch source rejects its zero owned ledger rows, as retained in `declared-final.log`; this is not a passing source-claim check or a reason to whitelist the partial. No game source or shared header changes, so no landing or full gate is claimed. Final ledger and pin checks are retained in `check-csv-final.log` and `pin-consistency-final.log`. The exact preferred bank has its own probe in `bank-final-probe.log`, object evidence, strict gate in `strict-byte-gate-bank.log`, and passing name/class results in `names-bank.log` and `class-bank.log`. All failed shapes and verifier output remain available to the coordinator.

The first banking call refused to measure the retained bank because its explicit AsciiString destructor duplicates the canonical header definition. It wrote no bank or verdict. The exact retained bytes were archived through `re_log.archive_attempt` before removing that duplicate declaration. The normal banking call then measured both bodies, archived the repaired baseline and incoming body, selected the improved body, and wrote exactly one partial verdict. `bank-failed-retained.log`, `repair-prior.log` and `bank-final.log` retain the operation results. No Git writes or synchronization were performed.
