# GettingBuiltBehavior helper at RVA 0x001FE970

The candidate is banked as `targets/game/reverse/attempts/0x001fe970.cpp`. It is a partial reconstruction, not a verified recovery. Reopen it only with a new explanation for the remaining scratch-register and call-order differences. The scoped byte gate fails. No function-ledger row or symbol pin changes are proposed.

## Retry and evidence

The tested checkout is `cbcb79d0784092768988547a74ad9640d84a4b42`. The previous receiver-layout report was checked against the complete retail decode and the landed neighbouring sources. Module data `+0x14` is a string field: the target reads its header's word at `+4`; the secondary helper at `0x001FF360` passes that same field by reference to `0x00137E80`; that complete callee reads character data at header `+8` and passes it to the imported narrow `strncmp`. It is not an OCL pointer. The canonical `AsciiString` header is included, with the existing `StringBase<char>::isEmpty` definition made visible in this TU.

The target uses owner `+0x28` through `fld`, `fcomp` and `fsub`, so the candidate declares it as a float. The constructor's zero store and the update helper's bitwise copy do not establish an unsigned scalar type. This experiment would be refuted by a complete decoded use requiring integer arithmetic at that field, or by a probe that still reproduced the old receiver/object register mirror. The new candidate reproduces retail's `ESI` receiver and `EBP` object.

## Boundary, identity and ABI

The target begins at `0x001FE970`, has returns at relative `+0x0F3` and `+0x152`, and is followed by INT3 padding at `+0x153`. Every conditional branch remains inside that extent. `retail-decode.log` retains the complete target, caller, constructor and direct callees. `checked-target.log` independently inventories the complete target. The dump row remains untouched.

The complete `GettingBuiltBehavior::update` caller enters on its update interface at primary `+0x10`, computes the primary receiver with `lea edi,[esi-0x10]`, and calls ILT `0x0002EA14` with that receiver in ECX and no stack arguments. The ILT jumps to this target. The caller does not consume a return value. The existing address-derived method pin and the constructor's four installed interface tables support the owner; no semantic method name is invented.

The direct routes are `0x0000E6E7 -> 0x0036BB10` (cdecl, one Object pointer, pointer result), `0x0004B015 -> 0x00372090` (thiscall, no stack arguments, AL flag result), `0x000402D2 -> 0x001BFF70` (const receiver, output dword pointer followed by a dword interval, AL flag result, `ret 8`) and `0x0001F253 -> 0x0009A510` (thiscall, dword ID, pointer result, `ret 4`). Every complete body and thunk route was decoded and each body has its own `checked-*.log`. The returned module's fields remain opaque; its `+0x14` value is tested only for zero and its `+0x24` field is read as a byte.

The owner secondary table at `0x010A45E0` is installed at `+0x20`. Its slot `+0x14` routes to `0x001FE4A0`, which returns byte `[secondary+0x12]` in AL and performs a plain `ret`. Slot `+0x04` routes to the complete `0x001FF360` body. That body forwards its sole stack dword to slot `+0x10`, whose route reaches the complete 718-byte `0x001FECD0` body. The latter reads only the argument's low byte into BL and ends with `ret 4`. This supports a boolean argument; the landed donor's `Object *` spelling is not used as type evidence and is not changed here. The target's `push 1` is retained. Both complete secondary helpers are preserved in the decode logs.

`body-slots.log` follows ActiveBody's body-interface table slots `+0x10` and `+0x18` through their ILTs to `0x0020E140` and `0x0020E190`. Each complete four-byte getter loads one float dword into ST0 and returns without stack cleanup. Their checked inventories are `checked-health.log` and `checked-initial-health.log`. This agrees with the target's two float calls. No container value type, constructor reconstruction or target unwind cleanup is claimed.

## Measured trials

All sources, raw outputs and COFF objects remain under `build/`. The measurements below are generated from the retained probe outputs, with the retail extent explicitly passed to every probe.

| Raw output under build/001fe970 | Hypothesis | Emitted bytes | Probe differences | First difference |
|---|---|---:|---:|---|
| probe01.log | Typed string field and float countdown; separate health and source locals | 339 | 25 | +0x002 |
| probe02.log | Preserve unordered float branches and narrow the health scope | 339 | 23 | +0x002 |
| probe03.log | Use the two virtual float calls directly in the comparison | 339 | 23 | +0x002 |
| probe04.log | Declare the source output before the object and data locals | 339 | 23 | +0x002 |
| probe05.log | Reuse the dead health storage through a POD union | 339 | 16 | +0x095 |
| probe06.log | Use the independently decoded boolean secondary argument | 339 | 16 | +0x095 |
| probe07.log | Use a member-pointer carrier for the recent-source thunk | 339 | 16 | +0x095 |
| probe08.log | Represent the secondary receiver through inheritance | 339 | 16 | +0x095 |
| probe10.log | Expose the existing noinline GameLogic lookup body | 339 | 16 | +0x095 |
| probe11.log | Correct the availability thunk declaration to an undecorated thiscall carrier | 339 | 16 | +0x095 |
| probe-bank-final.log | Relocate the verified candidate includes for the attempt bank | 339 | 16 | +0x095 |

The best candidate reproduces retail's eight-byte local frame by sharing the dead float temporary with the later source-output dword. Narrowing a C++ scope, declaring the source early, direct comparison expressions, inherited receiver layout, a recent-source member carrier and the visible lookup definition did not improve the banked result. The family generator reported no applicable source-level choice in `family-levers.log`; no additional register permutations were run.

The probe difference offsets are `+0x095`, `+0x098`, `+0x0AB`, `+0x0AF`, `+0x0C5`, `+0x0CD`, `+0x0E4`, `+0x0E5`, `+0x0E6`, `+0x0E7`, `+0x0E8`, `+0x0EA`, `+0x0F5`, `+0x0F7`, `+0x0F8` and `+0x0FD`. The GameLogic DIR32 operand is at candidate `+0x0F9` instead of retail `+0x0FA`, so the relocation-masked difference count and score are diagnostic rankings, not acceptance evidence. `measure-final.log` retains the object location, relocation list, source hash and baseline hash.

The first availability declaration acquired a fastcall `@4` suffix, which the scoped gate reported unresolved. The final source uses the actual thunk symbol through a thiscall member-pointer carrier, reproduces the same instructions and resolves all direct callees. No pin was added. The final bank was reprobed from its retained location in `probe-banked.log`; `scoped-gate-banked.log` retains its byte-gate failure without unresolved calls.

`check-csv-banked.log`, `pin-consistency.log` and `class-gate-banked.log` pass. `declared-final.log` rejects the candidate because it owns no matched row, as expected for a banked partial. No baseline, shared header, upstream tool or STL symbol row was modified. A full gate is not required for this evidence-only bank.
