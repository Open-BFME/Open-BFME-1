# Visibility_Check retry at RVA 0x00715DC0

No recovery landed. The existing bank `targets/game/reverse/attempts/0x00715dc0.cpp` remains byte-for-byte unchanged (SHA-256 `b9569bd49c23354cbf06940443f4e5844bceec30de7ab7f669cd788298fd21b6`). Its reproduced score is 0.3738: 1391 compiled bytes against 1391 retail bytes, 871 differing bytes outside the probe's relocation masks, and first differing byte at `+0xD5`. The probe also reports 26 displaced relocation sites, so its normalized instruction similarity is not evidence of acceptance.

The tested revision is `14ed81a25a35667b0e3131d82083b0fc0ec798dd`. All trial sources, native probe output, checked-callee output and gate output are retained under `build/visibility-00715dc0/`. `measurements.jsonl` records each measured trial and `run_probe.py` reproduces the target probes with an explicit 1391-byte extent. The active bank is the preferred body; the lower-scoring alternatives remain scratch evidence.

## Retry hypothesis and refutation

The current landed grid collector, recursive node builder, render-object headers and adjacent source were checked rather than assuming the earlier descriptions were correct. The hypothesis was that native payload declarations, accessor layers, iterator lifetimes or visible collector code would resolve the saved camera/list shape residue. A measured body that failed to improve the preferred bank refuted that particular trial. The results below do not improve it. Repeating camera pointer/reference/register spellings, initialization order, typed list parameters or the same accessor rewrites is not a justified next experiment.

The older layout blocker is narrowed by actual construction evidence: the candidate list contains complete RenderObjClass pointers, rather than spatial-cell receivers or small pairs. This does not resolve the remaining allocation of camera and iterator storage.

## Boundary, identity and caller ABI

`decode-primary.log`, `checked-target.log` and `target-flow.log` cover the complete target. Every decoded direct branch remains inside the extent and lands on an instruction boundary. The only return is `ret 4` at RVA `0x0071632C`; the following byte at `0x0071632F` is INT3. There is no tail jump outside the target.

The constructor-installed vtable at VA `0x01120BE0` has slot 27 at ILT RVA `0x00010DF7`, whose decoded jump reaches `0x00715DC0`. The complete 388-byte `SimpleSceneClass::Customized_Render` caller at `0x00943AD0` loads the camera pointer from the first RenderInfo field, pushes it, places the scene receiver in ECX and calls vtable offset `0x6C`. The target consumes one pointer-sized stack argument and returns no value. The GeneralsMD twin independently identifies the slot as Visibility_Check, although its flat scan is not the BFME body. These checks support the bank's existing RTS3DScene::Visibility_Check identity. Unknown grid/helper owners retain their existing address-derived names.

## Container and helper evidence

The complete 392-byte node builder at `0x009441D0` loads an intrusive-list object's pointer at node offset `+0xC`, subtracts the canonical RenderObjClass MultiListObject adjustment of eight bytes, and stores that pointer at new candidate-node offset `+4`. It initializes and links only the next pointer at candidate-node offset `+0`. This is a complete next-pointer plus RenderObjClass-pointer payload, not a conclusion from allocation size. The target's complete loops read that same value at `+4` and invoke the canonical RenderObj virtual slots. `checked-node-builder.log` and the full node-builder decode retain its three recursive calls and all return paths.

The complete 50-byte vector append helper at `0x00715D40` copies one DWORD through the caller's reference and advances the finish pointer by four bytes. The actual target passes the address of its current RenderObjClass pointer at `+0x390`, establishing the payload independently of the generated template name. The complete 265-byte overflow helper at `0x00715770` repeats one DWORD from the value reference, copies prefix/suffix byte ranges, updates start/finish/end and returns with 20-byte cleanup. It does not construct a pair or read a second element field. Its semantic template spelling and the typed overflow binding remain unverified; no STL row or pin was changed.

The collector at `0x00944430` uses ECX = scene + `0x34`, with head-address/camera/optional-float-padding arguments in that order, and returns with 12-byte cleanup. Its full 568-byte decode forwards to the complete 195-byte bounds collector and then the node builder. The donor's private layout calls its frustum ViewSpaceFrustum, but the actual corner accesses begin at camera + `0x194`; canonical Get_Frustum returns camera + `0x104` and canonical FrustumClass corners begin at `+0x90`. A visible collector using canonical world-frustum/math declarations preserves the target's score but does not independently match the collector itself (its helper probe emits 632 bytes). No helper recovery or identity correction is claimed from that trial.

`abi-eh-check.log` follows the primary RenderObjClass vtable's used slots through their ILTs and decodes complete base implementations. Slot 64 returns the sphere address in EAX, slots 70 and 24 return scalar floats in x87, slot 86 returns the user-data DWORD in EAX, slots 99 and 103 return full-width integer predicates, and slot 98 takes two DWORD arguments with `ret 8`. All list calls use the canonical RenderObjClass-to-MultiListObject receiver adjustment. RefCount Delete_This at slot 0 calls the deleting destructor at slot 1 with flag one. The complete Object controlling-player helper tail-jumps through `0x0002369B` to the complete Team accessor at `0x000EC8F0`; both return pointer-sized EAX values with no stack arguments.

The matched `Thing_isKindOf.cpp` BFME view agrees with the decoded template pointer at `+4`, next override at `+4`, and KindOf words starting at template `+0xC8`. The bank uses the native Thing and Overridable accessor layers but explicitly reads the BFME `+0xC8` word; the upstream ThingTemplate layout is not a BFME field witness. KindOf ordinals and unknown Drawable shroud fields retain the bank's existing spellings. No semantic enum names or new pins were invented.

## Exception cleanup

The target's handler at `0x00C4C948` names FuncInfo `0x00E3C428`. Its only state is 0, whose predecessor is -1 and whose cleanup action at `0x00C4C940` addresses `[ebp-0x30]` before jumping through `0x0002E866` to `0x00712E90`. The complete 44-byte cleanup releases each eight-byte node through the existing node allocator and clears the head; it does not release the RenderObj payloads.

The compiled bank has the same single-state cleanup receiver adjustment. `native-cleanup-byte-check.log` resolves its allocator relocation using the existing symbol map and compares all 44 bytes exactly with retail (`masked False`, no unresolved calls). This verifies this cleanup model separately from the failing main body. `retail-eh.log`, `native-cleanup-check.log` and `abi-eh-check.log` retain the raw metadata and emitted cleanup instructions.

## Measured experiments

Each row below is generated from the preserved probe receipt. Scores count absent retail bytes and excess compiled extent as incorrect. The EH generator's invalid local-variable throw specification and inconsistent method throw specification were excluded before compilation; the original generator output is preserved. The legal Reset_List throw specification, EH mode and nothrow array-delete choices were searched mechanically. The unrelated store-order choice contradicts retail's visible store order and was not tried.

| Trial source or family | Compiled bytes | Differing bytes | First differing byte | Score |
|---|---:|---:|---|---:|
| EH search (eight generated combinations) | 1391 | 871 | `+0xD5` | 0.3738 |
| Generated drawable/object assignment order (baseline and reordered trial) | 1391 | 871 | `+0xD5` | 0.3738 |
| `baseline.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `native-local-init.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `shared-iterator.cpp` | Compile failure | Not measured | Not measured | Not scored |
| `native-shared-init.cpp` | 1391 | 877 | `+0x9E` | 0.3695 |
| `mirror-accessor.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `native-accessors.cpp` | 1402 | 911 | `+0xD5` | 0.3424 |
| `visible-shader-helper.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `typed-list-pointer.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `typed-list-reference.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `pending-iterator-scope.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `shared-iterator-scope.cpp` | 1391 | 877 | `+0x9E` | 0.3695 |
| `reflection-conditional-draw.cpp` | 1400 | 934 | `+0xD5` | 0.3264 |
| `branch-local-draw.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `visible-collector.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `visible-world-frustum-collector.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `decoded-node-iteration.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |
| `existing-ilt-vector-call.cpp` | 1496 | 1033 | `+0x17` | 0.2393 |
| `0x00715dc0.cpp` | 1391 | 871 | `+0xD5` | 0.3738 |

The shared-iterator compile failure was preserved and corrected in the scoped variant; it is not a measured shape. The explicit existing-ILT vector adapter removed the unresolved call but made the main frame and loops worse. Neither that adapter nor the nonmatching visible collector is a production source.

## Checks and reopening condition

`check-csv-final.log` and `pin-consistency.log` pass. The scratch source's class gate passes. The declared-unmatched check fails because the scratch bank owns no production ledger row; no whitelist was added. The ordinary scoped byte-verifier core was called with one candidate row supplied in memory, preserving the ledger. `baseline-strict-gate.log` and `ilt-strict-gate.log` both fail byte equality. Full gating is not applicable to this evidence-only change, which edits no source, header, pin or matched row.

The preferred bank still requires `?push_back@?$vector@PAVRenderObjClass@@V?$allocator@PAVRenderObjClass@@@_STL@@@_STL@@QAEXABQAVRenderObjClass@@@Z`. Its visible helper is only relocation-masked exact; the typed _M_insert_overflow relocation is not independently bound. The STLport pause prevents adding those typed pins. No pin or alias was invented to make either gate pass.

The first main-body residue is the camera load at `+0xD4`: retail preloads EBP, while the bank uses EAX and later retains the camera in EBX. Reflection iteration uses the original argument's stack home in retail, while the bank uses a local home; normal iteration and the saved visible-list receiver also have different reload lifetimes. Reopening requires an independently supported declaration/helper or lifetime model that changes these emitted instructions and improves the measured preferred body while retaining the verified container and cleanup model. New STLport headers may provide such new context, but merely renaming the type or changing pointer spellings has been rejected by these measurements.
