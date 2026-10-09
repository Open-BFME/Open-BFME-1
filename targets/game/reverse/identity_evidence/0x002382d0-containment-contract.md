# Containment conversion at RVA 0x002382D0

This is a partial reconstruction, not an exact recovery. The tested base is `4b91c8621e9e1195de1a556cdb352500c02d364f`, and the assigned model is `gpt-6.1-sol`. The preferred candidate defines `?replace002382D0@ContainView002382D0@@UAEXPBVThingTemplate@@@Z`. The ledger continues to point at its generated assembly. No function ledger row, STL symbol pin, shared header or baseline was changed.

## Retry and refutation

The retry tested the current canonical Object layout, the landed object lookup and factory bodies, and native pointer-list algorithms. Earlier records describe an unresolved owner and layout, then a bank with a late EBX save. Complete decoded population and synchronization helpers now establish pointer payloads, and native `_STL::find` moves the EBX save to the prologue. The hypothesis that a caller-visible lookup or factory body would also fix the initial scheduling is refuted by the measured unchanged results. The factory copied into trial 10 independently reproduces its complete retail body; its visibility still does not improve this target.

## Boundary, receiver and cleanup

`build/rva002382d0/retail-decode.log` contains the complete target and the helpers used below, including bytes after each extent. Both target returns clean one four-byte stack argument. The early return is at RVA 0x00238358, and the final return is at RVA 0x002384EC through 0x002384EE. Padding starts at 0x002384EF. All target conditional branches remain within the extent, and the target has no tail jump. `build/rva002382d0/checked-target.log` records the checked call inventory.

HordeContain's decoded constructor stores VA 0x010AF048 at primary offset 0x20. Slot 26 of that table routes through ILT 0x00027831 to complete helper 0x00230730, which converts that receiver to the secondary interface at primary offset 0xE4. Its two return paths are decoded. The secondary tables VA 0x010AE230, VA 0x010AED58 and VA 0x010B07E0 all route slot 25 through ILT 0x0004B321 to the target. Secondary slot 122 routes to complete helper 0x00230830, which returns `this - 0xE4`. The owner object pointer read at secondary offset -0xDC consequently corresponds to primary offset 8, also written by the complete Object module-swap helper. The candidate retains address-qualified owner and method names. The aligned EA chain suggests `HordeContain::changeToFormation`, but it is not used as a new identity claim.

`build/rva002382d0/eh-target.log` records the two unwind states. State zero destroys the list at EBP-0x20 through cleanup 0x00C0DA70 and routes 0x00018949 -> 0x000D0020 -> 0x0000E68D -> 0x000CEBD0. State one restores the latch at EBP-0x18 through cleanup 0x00C0DA78 and ILT 0x00033C17 -> 0x0010D360. Complete LatchRestore boolean constructor, destructor and deleting destructor bodies establish the saved byte at +4 and destination pointer at +8. The target latches primary owner byte +0x210, and restores it on both normal exits from that nested scope. `Common/LatchRestore.h` supplies the same ownership and virtual destructor behavior. The list destructor walks links and deallocates nodes and sentinel without deleting the pointed-to Objects.

## Payload and outgoing ABI

Secondary slot 17 routes to the complete 413-byte helper at 0x00237FB0. Its first loop copies exactly one dword from source node +8 to new node +8 at 0x00238007 through 0x0023800A. The second loop obtains an Object pointer from a decoded object hash lookup and stores it to node +8 at 0x00238092. The final copy loop likewise reads and writes exactly node +8. No additional payload fields are copied. Secondary slot 29 routes to the complete 225-byte helper at 0x0023FDB0, which reads each payload at node +8 and dereferences Object fields +0x204 and +0x210. These complete helpers establish `list<Object *>`; allocation size and the prior `list<int>` destructor spelling do not establish its value type.

The direct newObject callee at 0x00138520 returns a full Object pointer in EAX and cleans four dword arguments. Its forwarding call shows template, team, status-address and extra arguments independently of the target's register choices. The target initializes three status words and forwards their address. The complete findObjectByID body at 0x0009A510 cleans one dword ID and returns the stored Object pointer from hash-node +8. Complete destroyObject at 0x0038B0C0 and Object module-swap at 0x001BF1E0 each clean one pointer argument. The allocator takes one cdecl size; the node deallocator takes a cdecl pointer followed by size. Their full decodes and checked inventories are retained.

Each target virtual call was traced through the installed tables and its callee decoded completely. Slot 81 is the one-dword setter at 0x00230790. Slots 111 and 112 route to complete no-stack-argument member walks at 0x00234090 and 0x002340E0. Slot 52 routes to complete no-stack-argument body 0x002377A0. Slot 28 routes to complete 1762-byte body 0x00245BF0, with three dword stack arguments, pointer dereferences for the first two, zero returns on rejection paths and the created Object pointer on success. The target ignores that return. The candidate declares its result as Object pointer. The bool argument occupies a dword stack slot, and the target pushes the literal one.

An incoming virtual caller tying this exact secondary slot to its use of the return register was not established. `build/rva002382d0/decoded-caller-screen.log` retains the only complete aligned body selected by the bounded opcode screen; its +0x64 call uses the primary +0x20 containment interface and is rejected as evidence for this target. The target's one-pointer input and thiscall cleanup are decoded. The incoming return contract is an unresolved acceptance blocker for any future exact candidate. The source uses void because neither return path prepares a common meaningful result. No exact ABI or caller identity is claimed.

## Measured compiler trials

The following values are parsed directly from the retained raw probes. Quality uses the repository finish-measure formula, including its penalty for a different emitted size. These are diagnostic relocation-masked measurements. Relocation layout drift remains, so quality is not byte verification. All sources and unedited outputs remain under `build/rva002382d0/`; the EH search also retains every source in `build/shape_search/8a37a6c7372e4902a321bafcf545837b/`.

| Raw probe basename | Emitted bytes | Masked differing bytes | First offset | Quality | Normalized instruction shape |
|---|---:|---:|---:|---:|---:|
| 01-saved-body | 543 | 199 | 0x18 | 0.6335 | 0.933 |
| 03-visible-lookup | 543 | 199 | 0x18 | 0.6335 | 0.933 |
| 04-typed-contain | 543 | 199 | 0x18 | 0.6335 | 0.933 |
| 05-object-list | 543 | 199 | 0x18 | 0.6335 | 0.933 |
| 06-factory-wrapper | 543 | 197 | 0x18 | 0.6372 | 0.916 |
| 07-module-conditional | 547 | 381 | 0x18 | 0.2836 | 0.910 |
| 08-status-lifetime | 543 | 209 | 0x17 | 0.6151 | 0.933 |
| 09-default-status | 543 | 199 | 0x18 | 0.6335 | 0.933 |
| 10-visible-factory | 543 | 199 | 0x18 | 0.6335 | 0.933 |
| 11-native-find | 543 | 163 | 0x18 | 0.6998 | 0.933 |
| 12-direct-native-find | 543 | 159 | 0x18 | 0.7072 | 0.949 |
| 13-native-ctor-find | 543 | 159 | 0x18 | 0.7072 | 0.949 |
| 14-native-status-find | 543 | 170 | 0x17 | 0.6869 | 0.949 |
| 15-native-contain-accessor | 547 | 266 | 0x18 | 0.4954 | 0.944 |
| 16-team-accessor | 543 | 162 | 0x18 | 0.7017 | 0.949 |
| 17-three-word-status | 547 | 279 | 0x18 | 0.4715 | 0.944 |
| 18-split-null-guards | 574 | 421 | 0x17 | 0.1105 | 0.861 |
| 19-short-circuit-guard | 582 | 421 | 0x17 | 0.0810 | 0.797 |
| 20-virtual-slot25 | 543 | 159 | 0x18 | 0.7072 | 0.949 |
| 21-inline-view | 547 | 266 | 0x18 | 0.4954 | 0.944 |
| 22-typed-owner | 543 | 159 | 0x18 | 0.7072 | 0.949 |
| final-probe | 543 | 159 | 0x18 | 0.7072 | 0.949 |

The EH sweep's eight finite choices have the saved instruction result. The non-EH family generator supplies no applicable source-level choices for the condensed body. Named status storage, a three-word explicit status constructor, native accessors, split and short-circuit guards, and an inline nullable-interface helper all fail to improve the preferred pointer-list find body. Changing only the virtual slot declaration or the typed owner view preserves its measured result. No unchanged register spelling sweep or x87 iteration was used.

## Remaining work and checks

The first divergence remains target +0x18: retail preloads the template argument into EDX before saving EBX, while the candidate starts with the register saves. The candidate later loads that argument into ECX and emits an additional `mov ecx,eax` before secondary-interface extraction. Those differences shift the first call and the early return by two bytes. Retail's loop padding begins at +0xEA with a six-byte `lea ebx,[ebx]`; the candidate's padding begins at +0xEC with a four-byte stack lea. From the comparison at +0xF0 onward the concrete instruction sequence aligns, including list unlink, ownership swap, latch, destruction and final epilogue. Reopening needs a supported native expression or declaration that changes the initial argument scheduling or removes the receiver copy, followed by an improved probe. New naming alone does not justify a retry.

`build/rva002382d0/final-strict-gate.log` is the scoped ordinary verifier result on the final source with an explicit in-memory target row. The immutable retail baseline passes, and the byte comparison fails. There is no unrelated gate failure to waive. `final-class-gate.log` passes, and `final-name-text-check.log` passes the repository's text comparison API. The name-regression CLI in this revision accepts Git revisions, so the requested two-path CLI form fails as retained in `final-name-regression.log`. `final-declared-check.log` refuses the unlanded main definition and reports zero matched rows, as expected for a bank; it was not whitelisted or represented as a production source. `handoff-check-csv.log` and `final-pin-consistency.log` pass. `banked-probe.log` reproduces the final source measurement after the repository banking tool writes the actual bank. `suffix.json` independently checks the existing compiler object and confirms the relocation-masked suffix equality from +0xF0. No full gate is required for these bank and evidence changes.
