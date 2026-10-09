# RVA 0x002666A0: storage lifetime retry

This is an improved unmatched bank. No source recovery, new pin or original method identity is claimed. The owner remains `Rva002666A0`, and every existing bank identifier is retained. The tested base is `f40013bd9f458e42de838ba3083b616b3ff5edc0`. All trial sources and unedited probe outputs are retained under `build/002666a0-retry/`.

## Retry hypothesis and refutation

The current ledger supplies the coordinate-copy helpers and neighbouring Object layouts used by the earlier bank. Their presence alone does not resolve its frame or type blockers. Independent decoding shows that the status mask and both helper results occupy the same three-word buffer in retail. The first hypothesis was that empty return-type destructors would shorten temporary lifetimes. Its refutation condition was an unchanged frame; that experiment and a native return-type call view both retained the old frame and bytes.

The successful hypothesis explicitly shares the witnessed storage, while preserving the existing helper symbol references through member-pointer ABI views. An inline object accessor restores the early receiver and position register roles. Both changes are reconstruction choices, not claims that EA used those source expressions. An unchanged frame or unchanged first divergence would refute their usefulness.

## Extent, callers and exception state

The complete target starts at `0x002666A0`, reaches its common epilogue at `0x00266948`, and ends after `ret 0x10` at `0x00266972`. The following bytes are INT3 padding. Every direct conditional branch and jump remains inside this extent. `checked-target.txt`, `decode-002666a0.txt` and `routes-and-boundaries.txt` retain the instructions and thunk routes.

Caller `0x002672B0` is completely decoded through its `ret 0x14`. Caller `0x00266F40` has executable code ending after the return at `0x002671E8`, followed by alignment and a five-entry switch table. A linear decode of its ledger extent fails because it includes table data. `checked-caller-code.txt` checks the executable extent, and `routes-and-boundaries.txt` independently validates every switch destination on a decoded instruction boundary. The actual calls at `0x0026713F` and `0x00267442` go through ILT `0x00020455`. Both push the Bool output, coordinate output, Object input and hidden coordinate result, in that order. Both copy all three returned words through EAX and consume the Bool as a byte. This establishes the machine ABI; it does not name the method or prove a class-key spelling.

Retail FuncInfo `0x00DFED70` has one state whose cleanup clears the initialization guard bit at VA `0x012EFD38`. The complete cleanup at `0x00C0FC50` returns normally. The selected compiled FuncInfo also has one state, predecessor -1, and the same three-instruction guard clear followed by RET. No coordinate or BitFlags cleanup appears in either map. Raw evidence is in `eh-retail.txt`, `checked-cleanup.txt` and `compiled-unwind.txt`.

## Callee and value evidence

All eight direct callees were decoded at their ledger extents and checked with `checked_callees.py`. The `decode-*.txt` and `checked-*.txt` pairs cover the NameKey generator, Object module lookup, whole-mask and individual-bit status updates, both coordinate copies, vector adjustment and ground predicate. The adjustment helper's final instruction is a backward jump into its own body; all return paths and later branches were inspected. None of these helper extents has an outgoing conditional branch or tail jump.

Both coordinate helpers copy every word at offsets 0, 4 and 8 into hidden storage, return its address in EAX and pop two stack words. The first selects the entry at module+0x24 using the extent at +0x28, then reads entry+8 through +0x10; the second reads entry+0x14 through +0x1C. Both fallback paths read the triple at the module-data pointer's +0x38. The first triple is independently consumed as floats by the docking index helper and by this target's subtraction and normalization. The second is a complete coordinate output consumed by the decoded callers. The return classes remain address-derived three-word views; their existing names do not independently prove an EA type.

The module constructor at `0x002062C0` installs secondary vtable VA `0x010A626C` at +0x20. Its slot 2 jumps through `0x0003D6D6` to the complete `0x00206B40` body. That body receives an ObjectID stack word, adjusts the receiver by -0x20 for an outgoing call, returns a signed index or -1, and pops four bytes on both return paths. The target passes Object+0x74 and uses a signed-negative test. This resolves the earlier docking-slot ABI concern without naming the method.

`Object` uses the shared header, including the witnessed cached position at +0x38 and ID at +0x74. The matched adjustment source declares `Object003E3B20` as a struct, which corrects the bank's class-key binding. The complete ground predicate observes its Bool through AL and pops eight bytes. Its existing symbol uses a struct coordinate, while the bank's native coordinate class has different mangling. The inline facade therefore calls the independently decoded ILT `j_0003ce25` through the witnessed two-argument member ABI. No alias or pin is introduced. The singleton still uses the existing `AI *TheAI` declaration and the observed pathfinder pointer at +0x0C.

The Zero Hour tree supplies `Thing::getPosition` and `AI::pathfinder` accessors, but contains no SiegeDeploy or SiegeDocking twin in the inspected SpecialPower source. The bank's native coordinate header has a nontrivial copy view; the canonical data-only Coord3D header does not reproduce this body's shape. Canonical coordinate-view reconciliation remains an acceptance blocker. No shared header was changed.

## Measurements and rejected shapes

The table is generated from each raw probe using `finish_measure.parse`, with the independently checked retail extent passed explicitly. Quality includes the size penalty and is not instruction similarity. No trial is an exact recovery.

| Trial | Emitted bytes | Differing non-relocation bytes | First difference | Measured quality |
|---|---:|---:|---|---:|
| `baseline.cpp` | 724 | 369 | `+0x17` | 0.4883 |
| `empty-return-destructors.cpp` | 724 | 369 | `+0x17` | 0.4883 |
| `native-return-call-view.cpp` | 724 | 369 | `+0x17` | 0.4883 |
| `explicit-output-storage.cpp` | 724 | 370 | `+0x17` | 0.4869 |
| `shared-mask-return-storage.cpp` | 724 | 359 | `+0x27` | 0.5021 |
| `position-accessor-lifetime.cpp` | 724 | 359 | `+0x27` | 0.5021 |
| `native-object-accessor.cpp` | 724 | 294 | `+0xCD` | 0.5917 |
| `coordinate-output-view.cpp` | 724 | 294 | `+0xCD` | 0.5917 |
| `native-pathfinder-accessor.cpp` | 724 | 294 | `+0xCD` | 0.5917 |
| `placement-return-storage.cpp` | 772 | 523 | `+0x17` | 0.1490 |
| `canonical-coord3d.cpp` | 758 | 569 | `+0x20` | 0.1241 |
| `float-return-payloads.cpp` | 724 | 303 | `+0x17` | 0.5793 |
| `verified-callee-bindings.cpp` | 724 | 294 | `+0xCD` | 0.5917 |
| `native-coordinate-assignment.cpp` | 724 | 294 | `+0xCD` | 0.5917 |
| `fieldwise-coordinate-assignment.cpp` | 709 | 529 | `+0x1A` | 0.2262 |

The EH generator tested six finite variants involving nothrow declarations, exception mode and delete[] declarations. None changed the emitted target bytes. The non-EH generator produced a scalar-to-array frame choice; both its starting body and changed body retained the same bytes. Sources and raw probe outputs are retained as `eh-00.cpp` through `eh-05.cpp` and `shape_family-00.cpp` through `shape_family-01.cpp`; the search manifests are referenced by `eh-search-path.txt` and `shape_family-search-path.txt`. Float payload declarations on ordinary hidden-return calls, placement construction, the canonical POD coordinate and field-wise assignment all worsened the measured result. Further unchanged register or x87 spelling experiments were stopped.

## Remaining blocker and reopening condition

The selected body is one byte short. Its frame matches retail and its first differing byte is in the first coordinate helper's output-address register, followed by different copy scheduling and the pathfinder call schedule. Nine relocation sites still drift because later instruction offsets differ. `scoped-gate.txt` records the failing relocation-resolved byte check; no unresolved callee remains in that result. This gate failure is the target's mismatch, not an unrelated failure.

Reopen only with independently justified compiler context for the hidden-return copies or native coordinate declaration that addresses the first divergence while preserving shared storage. Exact bytes would still require canonical coordinate reconciliation and the complete ABI and unwind checks above. The method's original name remains unknown and is intentionally address-derived; that is not itself a blocker. No new STL row or pin is needed or added.
