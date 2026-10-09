# RVA 005F1370: Coord3D and virtual-owner retry

## Result and reopening condition

The target remains a partial. The retained candidate is `targets/game/reverse/attempts/0x005f1370.cpp`. No game source, function ledger row, symbol pin or shared declaration is changed. The tested base is `2083fb96b85ab35063653fad43e6a3bc68a9c892`; the actual model is `gpt-6.1-sol`. Raw trial sources, decoded instructions, probe outputs and gate outputs are preserved under `build/005f1370-retry/`.

The new hypothesis was that the bank's repeated Vector3 position access did not represent retail's single trivial coordinate snapshot. The complete target loads particle fields +0x1C, +0x20 and +0x24 once at RVA 0x005F1E33, using three integer MOV instructions, before reusing those values across all eight placements. The current checkout provides `game/Libraries/Include/Lib/Coord3D.h`, whose canonical representation is three float fields with no constructor. A single Coord3D snapshot improves the measured result. An unchanged or worse measured body, or decoded additional fields in that snapshot, would refute this experiment. It did improve the result, but did not explain retail's larger frame.

Reopen with evidence identifying the live native vector temporaries and their ownership or lifetime across the matrix transforms. Another spelling of the same register or x87 operations is insufficient. Exact cleanup-slot agreement and strict relocation resolution are also required before landing. The retained body does not establish the original method name or a complete semantic Particle class declaration.

## Boundary and control flow

The full ledger extent is 5096 bytes. Its executable portion is 5068 bytes, ending with RET 12 at RVA 0x005F2739 through 0x005F273B. The next 28 bytes hold seven switch targets, followed by INT3 padding at RVA 0x005F2758. Every switch target is an instruction start inside the decoded executable portion. The complete executable decode contains the visibility and culling exits, particle loop, empty-batch exit, renderer-null exit, all seven shader cases and the shared destructor and return. Its conditional branches stay inside that portion. The switch jump's seven destinations are checked explicitly. The target's ABI is a thiscall receiver and three four-byte stack arguments, with a four-byte EAX count result and RET 12.

The full-extent linear checker rejects the last table byte as an incomplete instruction. This is retained as `checked-target.txt`; it is not concealed by shortening the byte comparison. `checked-code.txt` checks the complete executable portion, while `boundary-summary.txt` and `005f1370-decoded.txt` retain the table and boundary evidence. All probes still compare against the full ledger size.

## Identity and field evidence

The ILT at RVA 0x0003EDBF tail-jumps to the target without adjusting ECX. Complete factory RVA 0x005E8930 and constructor RVA 0x005E5960 install the primary vtable at VA 0x01111E68. Slot +0x10 contains the ILT's address. The existing matched ButterflyDrawModule factory and constructor in `game/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp` independently associate that table with the butterfly draw module. The other two tables reported by vtable_lookup share this entry, but their ownership is not needed for this association. Raw candidate pointer searches were validated against decoded table entries and complete bodies. No direct E8 caller to the body or its ILT was found; this is a screening result, not a completeness claim about virtual callers. The bank keeps `Rva005F1370Owner::render` and its descriptive field names. A virtual declaration preserves the witnessed vptr at offset zero and the system pointer at +4 without changing the measured body.

The box argument supplies six consecutive float fields, matching canonical AABoxClass Center and Extent. The first argument is forwarded unchanged as one four-byte stack slot to RVA 0x0090FEE0; its semantic type is unresolved. The final argument is dereferenced for a four-byte count update. System fields read by the target are type +8, string +0x10, integer +0x7C, byte +0x80 and first-particle pointer +0xA0. Particle fields read are position floats +0x1C, +0x20 and +0x24, velocity floats +0x10 and +0x14, and next pointer +0x3C. This target does not read velocity +0x18. The earlier note's statement that all three velocity floats were consumed is therefore too strong.

The inspected Zero Hour donor `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h` uses Coord3D for ParticleInfo velocity and position. Its inheritance and remaining fields differ from this partial BFME view. The donor supports the coordinate hypothesis; the decoded BFME loads establish the actual field widths and offsets. No butterfly draw twin was found in that reference tree.

The actual color accessor returns one EAX-sized value. The target tests it against zero and reads only three float-sized fields at +0, +4 and +8, then writes alpha as a fourth float. The position output writes three float-sized fields per element with a 12-byte stride; the color output writes four fields per element with a 16-byte stride. These accesses support the retained buffer payload views independently of allocation sizes. No STL container type or allocation size is used as type evidence. RVA 0x0090F760 initializes index buffers, not the position or color payloads; the earlier note's description of it as a buffer initializer does not establish their value types.

## Complete callee and cleanup review

`helpers-summary.txt` and the corresponding `XXXXXXXX-checked.txt` and `XXXXXXXX-decoded.txt` files retain complete helper extents and checked_callees results. The visibility helper's 92-byte executable body has a separate inline table; the float helpers and the pointer dispatcher end at their independently decoded return or tail-jump boundaries. The renderer's complete 3619-byte body and each return path were inspected, but its semantic owner remains address-derived.

| Actual destination | Checked extent | Contract observed at this target and complete helper |
| --- | ---: | --- |
| 0x005CFF50, through ILT 0x00001B18 | 190 | Cdecl, no arguments, pointer-sized EAX result. |
| 0x005C31A0, through ILT 0x00038A5F | 92 code bytes | Niladic thiscall; boolean result consumed from AL. Internal virtual calls receive the system type as one four-byte argument. |
| 0x005C30A0, through ILT 0x000309F9 | 22 | Niladic thiscall; optional receiver +0x94, virtual slot +0x10, float ST0 result or zero. |
| 0x005C3120, through ILT 0x00022796 | 22 | Niladic thiscall; optional receiver +0x94, virtual slot +0x20, float ST0 result or zero. |
| 0x005C3160, through ILT 0x0001153B | 22 | Niladic thiscall; optional receiver +0x90, virtual slot +0x14, float ST0 result or zero. |
| 0x005C3180, through ILT 0x00037308 | 18 | Niladic thiscall; receiver +0x8C, tail virtual slot +0x14, EAX-sized result dereferenced as three floats by the target. |
| 0x009FB93B and initial dispatcher 0x009FB91F | 6 and 28 | Indirect runtime dispatch; output matrix pointer then float argument, RET 8, EAX result unused here. The initial dispatcher has both initialization and initialized paths. |
| 0x0090E910 | 309 | Cdecl, hidden four-byte handle result storage followed by char pointer and two four-byte integers; target caller cleans 16 bytes. The complete return copy reads and writes one pointer and increments its low WORD refcount at +4. |
| 0x0090F8C0 | 138 | Thiscall, integer count then four pointer arguments, RET 20; holder count at +0x10 and buffers at +0, +4, +8 and +0xC. Buffer refcounts use DWORD +4 and destructor virtual slot zero. |
| 0x0090FEE0 | 3619 | Thiscall, one forwarded four-byte argument, RET 4; EAX result unused by this target. |
| 0x009EB7A0 | 36 | Niladic thiscall; low WORD refcount decrement, conditional virtual tail dispatch at slot +0x20 with the original receiver, or RET. Two existing ledger identities share this address, so their names do not independently prove identity. |

`DX8Wrapper::Get_Transform` is inlined in retail. The adjacent matched RVA 0x005F0F00 and its owner `game/Libraries/Source/WWVegas/WW3D2/render2d.cpp` use the canonical Matrix4 declaration. The bank includes its canonical header and the scalar math headers. The generated family choices expose no frame or register alternative for this source; the actual generator outputs are retained rather than claiming those families were exhausted by manual edits.

Retail EH FuncInfo has exactly one unwind state, 0 to -1. Cleanup RVA 0x00C3C260 computes the handle receiver at [ebp-0x1DC], then jumps through ILT 0x00030652 to the complete 12-byte destructor at RVA 0x0005CC00. That destructor reads exactly one pointer at offset zero, skips a null pointer and otherwise tail-jumps to RVA 0x009EB7A0. The full texture factory and `game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp` support the four-byte owning handle and its hidden-return ABI. The candidate also has one state, but its cleanup receiver is [ebp-0xD8]. It therefore does not pass cleanup agreement. The trial with an invented owning base changes neither the measured body nor that cleanup slot and is rejected. The preferred body retains the original bank's handle declaration; exact recovery will need agreement with its canonical source inheritance as well as the decoded storage and ownership.

## Measured experiments

The unmodified old bank fails to compile against current headers with C2908 because it redundantly specializes StringBase<char>::str after the header has instantiated it. Trial 01 removes only that specialization and reproduces the earlier byte counts. Getter throw() and /EHsc alternatives were generated with eh_levers and measured through shape_search before hand iteration. All four combinations retain trial 01's size and difference count. Their immutable sources and unedited raw probe outputs are in `build/shape_search/dcaedff5c5e34ce6839c45a2b0cbf482/`. The finite frame and register choice request produces no applicable choices; its baseline-only result and raw probe are in `build/shape_search/bcb847e0128d4782af95692ce2a0c435/`.

The table is generated from the retained raw probe outputs. The banking score uses tools/finish_measure.py, including its double penalty for size error. Equal bytes and normalized instruction shape are separate diagnostics and are not exact acceptance.

| Trial | Changed hypothesis | Emitted bytes | Masked differences | Missing bytes | Equal bytes | Banking score |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `01-current-headers.cpp` | Remove the obsolete StringBase specialization | 4692 | 3962 | 404 | 730 | 0.0640 |
| `02-setter.cpp` | Write transformed coordinates with Vector3::Set | 4692 | 3961 | 404 | 731 | 0.0642 |
| `03-four-component-result.cpp` | Materialize the fourth transformed component | 4692 | 3976 | 404 | 716 | 0.0612 |
| `04-position-copy.cpp` | Snapshot the particle position once | 4724 | 3954 | 372 | 770 | 0.0781 |
| `05-vector-translation-setter.cpp` | Use Vector4::Set and a full transformed value | 4496 | 3818 | 600 | 678 | 0.0153 |
| `06-coord3d-position.cpp` | Use canonical Coord3D for the particle position snapshot | 4808 | 3999 | 288 | 809 | 0.1022 |
| `07-handle-base-cleanup.cpp` | Test a base-class cleanup shape; reject the invented inheritance | 4808 | 3999 | 288 | 809 | 0.1022 |
| `08-rotation-return-value.cpp` | Return the rotation result by value | 4808 | 4000 | 288 | 808 | 0.1020 |
| `09-position-return-value.cpp` | Return the position result by value | 4808 | 4000 | 288 | 808 | 0.1020 |
| `10-native-matrix-storage.cpp` | Use native Matrix4 storage for the D3DX output | 4808 | 3999 | 288 | 809 | 0.1022 |
| `11-virtual-owner.cpp` | Represent the independently witnessed virtual owner | 4808 | 3999 | 288 | 809 | 0.1022 |
| `12-portable-bank.cpp` | Use portable includes and preserve the supported virtual declaration | 4808 | 3999 | 288 | 809 | 0.1022 |

The retained body first differs at +0x17, inside the frame allocation instruction at +0x15. Its frame is 0x1B4, while retail uses 0x1D8. Register saves already differ at +0x1B. The emitted extent ends at +0x12C8, leaving retail bytes +0x12C8 through +0x13E7 absent. The raw comparison also reports 67 relocation positions displaced from retail operands. Its normalized instruction shape is diagnostic only. All alternatives and full unedited comparisons are preserved; no improvement is claimed from the unchanged native-matrix or virtual-owner trials.

## Verification and limits

`check-csv.txt`, `pin-consistency.txt`, `class-gate.txt` and `name-file-check.txt` record passing checks before banking. The checkout's name_regression CLI accepts Git revisions, so its prescribed file-to-file invocation fails; `name_file_check.py` calls that tool's actual regressions function on the unmodified old bank and candidate and returns no findings. No names are renamed. `declared-unmatched.txt` rejects the trial source because it has zero matched ledger rows. This is consistent with a banked partial, and no whitelist or fabricated absent-from-retail annotation is added.

`scoped-gate.txt` records strict selected-row byte verification without editing the ledger. It fails on bytes and the unresolved symbols `?render@Rva0090FEE0Renderer@@QAEXI@Z` and `_D3DXMatrixRotationZ@8`. These are target-specific failures. No pins are invented to suppress them. No full gate is required for a bank and evidence-only change, and none is claimed. Final checks of the preferred bank and the unchanged ledgers are retained with the `final-` prefix in the same scratch folder. No commit or synchronization is performed in the read-only Git sandbox.

The bank preserves the original CRLF convention, including the two metadata lines generated by re_log. Its normalized bytes have a separate immutable archive, while the initially generated bank and the original source remain archived. The final full probe is `0x005f1370-probe.txt`. That path was reused for the final CRLF verification, so the preceding bank verification's full output is not retained separately; its output prefix is preserved in `final-probe-wrapper.txt`. Every compiler-shape trial's source and complete raw output remains available. The local probe wrapper now allocates a separate path for repeated verification.
