# RVA 0x0078A7A0: scalar asset keys and caller ABI

## Result and reopening condition

This is a partial reconstruction of the 816-byte body at RVA 0x0078A7A0, tested against revision 8a5e04f6981802754159cb17b944588b25313b2d with MSVC 7.1 and model gpt-6.1-sol. No function, symbol pin or shared header is changed. The ledger still names the generated dump. The preferred bank is `targets/game/reverse/attempts/0x0078a7a0.cpp`, selected by the banking command after measuring both the new and previous bodies. Its body is identical to the probed `build/78a7a0/lod_level.cpp`. The measured score and immutable archive path are recorded in the single verdict row retained at `build/78a7a0/verdict-row.txt`. The scoped byte gate fails on this candidate's own differences. There is no exact recovery or EA class-name claim.

Reopening needs evidence that changes the early argument lifetime, stack-slot allocation or floating comparison shape. Repeating the flags and spellings below without such evidence is unjustified. The first divergence is the stack allocation at target offset 0x17: retail reserves 0x64 bytes and this candidate reserves 0x60. Retail saves ESI only around the bone loop; this candidate saves it before the optional asset-list block and caches the first argument there. The compiled constructor cleanup stores the allocated pointer in a dead incoming argument slot, whereas retail retains it in a local. Later differences include the floating comparison and argument reloads after `bfmeComputeQW`.

## Retry hypotheses and their refutation

The previous attempt cited missing owner layout and native Light setter visibility. Current landed constructor `Rva00789900Init.cpp`, destructor `Rva00789900Destructor.cpp`, scene initialization `Rva00789980SceneCameraInit.cpp`, viewport implementation `Rva00789900ViewportRender.cpp` and `W3DAptComponentView3D.cpp` establish an address-derived owner, the native headers and the animation-holder layout. Their source was read rather than accepted from the screening description. Selecting the native Light header, creating each color temporary immediately before its call, and using canonical native scene and render-object declarations improves the measured body. Those declarations also expose the prior wrong virtual name for slot 0x138: it is `Set_LOD_Level(0)`, not `Set_Animation_Hidden(0)`.

The complete caller suggests that the second argument is an AsciiString reference rather than an integer. The proposed refutation was unchanged frame and argument caching after correcting that declaration. The experiment does leave the bytes unchanged, so this ABI correction does not solve the frame mismatch. The pointer payload proposed by a matching donor and existing pins is independently refuted by the complete key lookup and insertion chain below. Correcting it to an opaque four-byte scalar descriptor also leaves the main body unchanged, but prevents a false type claim.

## Boundary, receiver and arguments

`build/78a7a0/audit/0078a7a0-decode.txt` contains every instruction in the target plus the following padding. The terminal `ret 0xC` occupies offsets 0x32D through 0x32F. All direct conditional and unconditional branch destinations remain within the decoded body, and the null-scene and null-render-object paths join its restored-stack return. The complete body and each audited helper were passed to the read-only `checked_callees.py`; the raw outputs are `build/78a7a0/audit/*-checked.log`. The jump table following `SceneClass::Register` is data rather than twenty additional instruction bytes; all five destinations in `scene-register-table.txt` point inside its 212-byte code extent.

The owner's table at VA 0x01126CCC has slot 3 routed through ILT RVA 0x0001647D to this target. The landed constructor at RVA 0x00789900 writes that table. The proposed owner remains `Rva00789900Init`, and the bank's descriptive method name `renderSetup` is retained without claiming its original EA spelling. The decoded method uses ECX without an entry receiver adjustment and returns no consumed result. Its three incoming stack words are removed by `ret 0xC`.

The complete caller is RVA 0x00462E80, 431 bytes, in `Rva00462E80RegisterNode.cpp`. Its decoded instructions push the address of the animation-mode string at offset 0x11E, the render-object string address at 0x123, and the hidden-return string storage from the slash-to-dot operation at 0x128, then call slot 0x0C at 0x130. Thus the first argument is the transformed path, the unused middle argument is an AsciiString reference, and the third argument is the animation-mode string. `AsciiString` uses the canonical header and one four-byte storage pointer. The candidate symbol is `?renderSetup@Rva00789900Init@@UAEXABVAsciiString@@00@Z`.

The native owner field offsets used here are scene 0x0C, selected render object 0x18, bone index 0x1C and animation holder 0x20. The holder has two reference fields at 0x20 and 0x24 and two integer fields at 0x28 and 0x2C, as independently shown by the landed bind and destruction siblings. No additional owner member meaning is inferred from padding.

## Scalar key evidence

Asset insertion at RVA 0x00141D00 obtains a dword from the actual call to RVA 0x009EC0B0 and forwards that value by address into the tree. RVA 0x009EC0B0 is a wrapper for the complete 200-byte lookup at RVA 0x009EED20. That function calls `NameKeyGenerator::nameToLowercaseKey` at RVA 0x009EDD70, saves EAX in EDI, and returns EDI on its successful map lookup. It does not return the map payload pointer. Failure paths return zero.

The complete 187-byte name-key helper reads the generator's counter at receiver offset 0x2BF40, stores it in a bucket at offset 4, increments the counter and returns that same offset-4 dword. Its found-name path returns the existing bucket's offset-4 dword; its null-input path returns zero. This provides integer key semantics independently of the pointer-shaped donor names.

The actual insert-unique chain reaches the complete 179-byte `_M_insert` body at RVA 0x0013F760. Both allocation arms contain the entire value copy inline: offsets 0x39 and 0x5F read `[esi]`, and offsets 0x3B and 0x61 write that single dword to new-node offset 0x10. There are no other value reads or writes and no call to another value constructor. The other writes set the node links and bookkeeping. Insert-unique at RVA 0x0013FA60 and `_M_insert` compare those keys with unsigned branches. The allocation's 0x14 size alone was not used as type evidence. The bank keeps `Gen_t_00140950_k4` with one unsigned dword as an opaque representation; it does not claim that the exact original C++ typedef is known.

The current pointer-named tree pins are misleading type evidence. The paused STLport lane is respected: no `_STL` ledger row or pin is added or changed. This partial compiles using the bank's existing opaque destructor binding. No new STL symbol is required for the bank. A future real identity correction for that container belongs to the resumed STLport lane and needs its own independent verification.

## Virtual calls, Light layout and ownership

The native declarations produce the observed virtual offsets: Get_Num_Bones 0xBC, Get_Bone_Name 0xC0, Add_Sub_Object_To_Bone 0x94, Get_Bounding_Sphere 0x100, Set_Transform 0x54 and Set_LOD_Level 0x138. The stack arguments are checked directly in the target: bone index is one dword; child attachment pushes a null translation pointer, the index and the child receiver; matrix assignment passes one 48-byte matrix address; LOD assignment passes integer zero. The sphere getter returns a pointer/reference in EAX, and the radius is read at offset 0x0C. Scene Register at offset 0x38 receives the light pointer and integer LIGHT value 1; Add_Render_Object at offset 0x08 receives the render object pointer. Concrete implementations and dispatch tables are retained under `build/78a7a0/audit` and `vtable_*.txt`.

Native `LightClass` has allocation size 0x124 and shadows byte offset 0xD0. The actual setter calls occur in Diffuse, Ambient, Specular order. Each complete 33-byte setter copies exactly three float fields into its corresponding native color vector. Creating three separate Vector3 temporaries at their call sites reproduces retail's store/call interleaving. The attenuation writes at offsets 0x104 and 0x108 use the radius and twice the radius. The selected camera bone adds a reference to the render object, conditionally releases the previous object through slot zero, writes the new pointer and writes the actual loop index.

The complete reference-delete helper at RVA 0x005F38C0 calls vtable offset 0x04 with flag 1. For Light's VA 0x0113CBB8 table this reaches RVA 0x0093BF90, which calls the complete destructor at RVA 0x0093BE00 and scalar delete at RVA 0x00881EB0. The destructor tail reaches the decoded RenderObj destructor at RVA 0x0091FC10. All reference increments and decrements used here are at offset 4. Allocation failure falls through to the same null-receiver use as retail; the reconstruction adds no fallback path.

## Exception cleanup evidence

`retail_eh.txt` records the target's two unwind states. State 0 transitions to -1 through cleanup RVA 0x00C51140, which forms ECX from EBP-0x50 and jumps through RVA 0x00141CC0 and ILT RVA 0x00015D7A to the complete tree destructor at RVA 0x00140950. Its erase helper at RVA 0x00134AA0 recursively deletes nodes and performs no value destructor. This is consistent with the scalar key representation. State 1 transitions to -1 through cleanup RVA 0x00C51148, which loads the allocated Light pointer from EBP-0x70 and calls scalar delete.

`final_eh.log` contains the candidate's unedited object unwind disassembly. State 0 uses the same -0x50 list-local adjustment. State 1 calls the canonical scalar delete but loads the pointer from EBP+4. This is an unresolved stack-storage shape, not evidence of a different deallocator. The complete Light constructor at RVA 0x0093BE90 has one unwind state whose cleanup RVA 0x00C5D540 loads its receiver from EBP-0x10 and tail-calls the RenderObj destructor. The bank is partial, so neither that correspondence nor its main-body compilation is asserted to be an exact cleanup recovery.

## Measured experiments

Each trial below has a complete source beside its unedited probe log in `build/78a7a0`. These are probes at the full retail extent, rather than estimates of normalized instruction similarity. The final bank score comes from `finish_measure`, which penalizes both differing bytes and size error; the normalized instruction score printed by `probe --shape` is not the bank score.

| Trial | Compiled bytes | Differing non-relocation bytes | Raw log |
| --- | ---: | ---: | --- |
| Saved body with current headers | 814 | 509 | `build/78a7a0/baseline_raw.log` |
| Native Light header | 814 | 507 | `build/78a7a0/native_light.log` |
| Color temporaries at call sites | 814 | 486 | `build/78a7a0/temps.log` |
| Canonical scene and render declarations | 817 | 449 | `build/78a7a0/full_native.log` |
| Three reference arguments | 817 | 449 | `build/78a7a0/three_refs.log` |
| Precise floating flag /Op | 820 | 680 | `build/78a7a0/precise.log` |
| Disabled global optimization /Og- | 1505 | 711 | `build/78a7a0/no_global_opt.log` |
| Size optimization /Os | 657 | 563 | `build/78a7a0/size_opt.log` |
| Optimization /O1 | 657 | 563 | `build/78a7a0/o1.log` |
| Processor selection /G7 | 810 | 578 | `build/78a7a0/g7.log` |
| Reversed positive comparison | 817 | 452 | `build/78a7a0/reverse_positive.log` |
| Literal double scale and zero | 815 | 515 | `build/78a7a0/literal_scale.log` |
| Float local after scaled integer | 815 | 515 | `build/78a7a0/scaled_float.log` |
| Positive block spelling | 817 | 449 | `build/78a7a0/positive_block.log` |
| Single loop condition | 803 | 606 | `build/78a7a0/plain_loop.log` |
| Direct render creation expression | 803 | 606 | `build/78a7a0/direct_create.log` |
| Nested scene condition | 817 | 449 | `build/78a7a0/nested_scene.log` |
| Nested render condition | 817 | 473 | `build/78a7a0/nested_render.log` |
| Number declaration at function scope | 817 | 449 | `build/78a7a0/top_number.log` |
| Light declaration at function scope | 817 | 449 | `build/78a7a0/top_light.log` |
| AssetList constructor view | 817 | 449 | `build/78a7a0/asset_owner.log` |
| Opaque scalar key representation | 817 | 449 | `build/78a7a0/scalar_key.log` |
| Address-derived virtual owner | 817 | 449 | `build/78a7a0/owner.log` |
| Portable include paths and complete holder | 817 | 449 | `build/78a7a0/portable.log` |
| Correct LOD virtual slot | 817 | 449 | `build/78a7a0/lod_level.log` |
| Frame array alternative | 820 | 514 | `build/78a7a0/frame_array_fixed.log` |

The mechanical EH generator was run before the body changes. All eight emitted trials left the baseline instruction/relocation result unchanged. Its raw run is `eh_search_raw.log` and its immutable trial receipts are in `build/shape_search/8124e2bb814a41c797a2b28e089d039f/result.json`. The generated frame-array search is recorded in `family_search.log` and `build/shape_search/2db0baf5adfc42028bb5cb16c3e8697e/result.json`; its candidate with a matching frame size worsened the byte distance. A copied trial initially failed on its relative include path; `frame_array_fixed.cpp` and its raw log retain the actual measured experiment after correcting only that path. The rejected free `__thiscall` setter cast is preserved in `out_of_line.cpp` and `out_of_line.log`, including its MSVC 7.1 compile rejection.

## Checks and preserved evidence

The raw final checks are `build/78a7a0/check_csv_final.log`, `class_gate.log`, `pin_consistency.log`, `final_eh.log` and `scoped_gate_best.log`; their exit codes and commands are retained in `final_checks.json`. CSV, class and pin checks pass. The scoped gate calls the repository verifier with one candidate row in memory and does not edit the ledger. It fails byte equality on the target. Its shifted-relocation diagnostics are not evidence for inventing additional pins. A full gate is not required for a bank with no promoted game source, shared header or pin change. `preservation_checks.json` verifies that precisely one verdict was appended, both old and new banks have exact immutable archives, the bank matches the probed body, and functions.csv and symbols.csv are byte-identical to HEAD. The post-bank CSV check also passes, with raw output at `check_csv_banked.log`. The old bank, every trial and raw output are retained for collection. No Git write or synchronization is performed.
