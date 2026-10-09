# StealthUpdate::update at RVA 0x002ADFB0

The target is the virtual `StealthUpdate::update` override, emitted as `?update@StealthUpdate@@UAE?AW4UpdateSleepTime@@XZ`. Its complete extent is 302 bytes. The tested base revision is `4d57d7b43ad3bca49d8af536b2d1f0b4c09cf405`. The reconstruction lives in `game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_update.cpp`.

## Retry hypothesis and refutation

No saved reconstruction existed for this target. Earlier attempts compiled the combined Zero Hour update rather than the BFME wrapper and reported a missing helper pin. The current landed `StealthUpdateChangeVisualDisguise.cpp`, `StealthUpdate_markAsDetected.cpp`, and `StealthUpdateModuleDataConstructor.cpp` provide independently checked BFME member offsets, the Object drawable virtual slot, and the four FX fields. The new hypothesis is a secondary-interface update wrapper that restores a disguise, calls the separate address-derived stealth step, and then processes FX transitions. A different interface receiver, a helper with stack arguments or hidden return storage, an outgoing branch beyond the proposed extent, or different FX-field offsets would refute it.

## Identity, boundary and caller ABI

The constructor at RVA 0x002ACB70 installs StealthUpdate's primary, behavior-interface, and update-interface tables at offsets 0, 0x0C, and 0x10. Primary table VA 0x010C457C slot two routes through ILT 0x00002810 to the complete six-byte getter at 0x002ACD40, which returns the retail literal `StealthUpdate`. Its slot three reaches the independently landed StealthUpdate::xfer, and slot four reaches the StealthUpdate pool getter. This establishes the owner independently of the wrapper's bytes. The update-interface table at VA 0x010C44AC has slot zero pointing through ILT 0x00010659 directly to 0x002ADFB0, without a receiver adjustment. Slot one points through ILT 0x00036084 to 0x002ACD80. The complete 13-byte second body writes mask 8 through the hidden result pointer, returns that pointer in EAX, and uses `ret 4`. This agrees with the shared `UpdateModuleInterface` declaration ordering update before getDisabledTypesToProcess.

The complete scheduler code at RVA 0x0038DA10 occupies 2129 bytes, including its final `ret 4` at 0x0038E25E. Its four-entry switch table at 0x0038E264 points only inside that code. At 0x0038DFD9 it loads the interface table from module+0x10, puts module+0x10 in ECX, calls slot zero without stack arguments, and consumes full EAX as the signed sleep interval. Thus the target receives the secondary interface pointer and returns a dword with no hidden result storage.

The target has returns at offsets 0xCE and 0x12D. Both restore EDI, ESI and EBP; the conditional EBX save in the restore-disguise block is balanced before that block exits. Every direct conditional branch and direct jump stays inside the 302-byte extent. The final return is at RVA 0x002AE0DD, followed immediately by INT3 padding. There are no outgoing tail jumps, exception registrations, unwind states, constructor cleanups, allocations, container construction or element destruction in this wrapper.

## Layout and call contracts

The source includes the shared game Module and UpdateModule headers, the shared BFME Object header, the shared FXListRetail header, and the native BitFlags declaration. The reference StealthUpdate declaration does not contain BFME's additional flag bytes or four FX fields, so the target-specific StealthUpdate declaration uses the offsets verified by the landed siblings and decoded constructor. The target does not construct or destroy this class.

Relative to the primary module pointer, ModuleData is at +4, Object at +8, the existing bank's `m_restoring2D` byte at +0x2D, and the three address-derived wrapper flags at +0x2E, +0x2F and +0x30. Their meanings are observed state, previous +0x2D state, and first-update FX suppression, respectively. They retain address tokens because no witnessed member names exist. The disguise fields at +0x34 through +0x43 agree with the landed disguise body; the wrapper reads the restore flag at primary+0x43, which is interface+0x33.

The FieldParse table at VA 0x010C41C0 independently names BecomeStealthedFX at +0x40, ExitStealthFX at +0x44, BecomeStealthedOneRingFX at +0x48, and ExitStealthOneRingFX at +0x4C. All four use the same FXList parser. `build/stealth-wrapper/field_parse.txt` retains the raw table words and decoded strings. The wrapper tests Object status bit 15 in the first word at Object+0x90; it does not infer a container payload from allocation size.

| Actual ILT | Complete body | Contract checked |
| --- | --- | --- |
| 0x00012E3B | 0x00410BA0, 29 bytes | Reads drawable bytes +0x3AD and +0x3AE; both returns define full EAX as 0 or 1. The wrapper consumes AL through its existing char-return pin. No arguments or receiver adjustment. |
| 0x000378DF | 0x002AC620, 1085 bytes | Existing protected StealthUpdate::changeVisualDisguise declaration; primary receiver, no explicit arguments, plain return. The wrapper reloads Object and the drawable after this call. |
| 0x00008337 | 0x00411DD0, 26 bytes | Existing Gen_00411DD0::bfmeSet(bool); reads the low byte of its sole stack argument, updates drawable+0x3AD when changed, and uses ret 4 on both paths. |
| 0x0002DA79 | 0x002AD670, 1885 bytes | Opaque rva002AD670 method described below; primary receiver, zero explicit arguments, full dword result. |
| 0x0001253F | 0x00065DE0, 39 bytes | Existing static FXList::doFXObj(const FXList*, const Object*, const Object*); three ordered stack pointers, plain return and caller cleanup. Null FX is handled by the callee. |

The indirect drawable calls use Object's primary vtable slot +0x28 with the Object pointer in ECX and no stack arguments. Object's established slot reaches ILT 0x0002074D and the complete 7-byte Object::getDrawable body at 0x001BE440, which returns Object+0x80 in EAX. This is verified separately from the direct-call inventory.

## Address-derived helper pin

The source preserves the saved helper bank's method name `?rva002AD670@StealthUpdate@@QAE?AW4UpdateSleepTime@@XZ`. Its new pin is at the real body RVA 0x002AD670; the resolver discovers ILT 0x0002DA79 from that body. The complete helper decode reaches the plain return at +0x75C followed by INT3, and checked_callees reports no outgoing branches. The caller explicitly subtracts 0x10 from its interface receiver. The helper then reads ModuleData at receiver+4, Object at receiver+8, enabled at +0x2C, and restoring at +0x2D. All normal exit paths either return 0x3FFFFFFF directly or derive a full dword sleep value from enabled, and share the correctly restored exception frame. It has no incoming stack argument or hidden return slot.

This pin asserts the independently decoded owner and ABI while retaining the address because the helper's original semantic method name is unproven. It does not claim that the helper's bank is exact or recover the helper's 1885 bytes. The existing helper bank and its container and exception-cleanup reconstruction remain outside this target's conversion. The pin would be refuted by a complete caller using another receiver or explicit argument, by a target different from 0x002AD670 after following the actual thunk, or by an unreviewed helper return path with a different result or stack contract.

## Compiler experiments and retained raw evidence

All trials and unedited probe logs are retained under `build/stealth-wrapper/`. Trial01 used raw status words and emitted 301 bytes with 136 non-relocation overlap differences. Trial02 retained the native bitset test and emitted 301 bytes with 113 overlap differences; its first residual was the branch displacement at +0x6A caused by the final flag-update ordering. Trial03 materialized the new status in a local and emitted 303 bytes with 107 overlap differences and an extra register copy. Trial04 evaluated and assigned status before copying +0x2D, recovering all 302 bytes outside relocation operands. The finite store-order generator and two-trial search independently selected that same ordering; its receipt is `build/shape_search/58ac1e370b4043f29786cf968bfe40cd/result.json`.

Trial05 tested shared Module and UpdateModule adoption but failed to compile on duplicate placement-array operators. Trial06 added the established `__PLACEMENT_VEC_NEW_INLINE` definition and again matched all 302 bytes outside relocations. Trial07 also adopted native BitFlags<86> and retained the exact result. The final source at its game path is reprobed in `build/stealth-wrapper/probe_final_source.log`. The compile failures and rejected shapes are preserved; no shared header was changed.

`retail_decode.txt`, `decode_0038da10.txt`, `decode_001be440.txt`, `decode_002acd80.txt`, `abi_routes.log`, and every `checked_*.log` retain complete decoded bodies, call inventories, return paths, caller setup and thunk routes. `decode.py` and `verify_abi.py` reproduce those reads against the repository's verified retail baseline. Byte equality and the shape-search receipt alone are not acceptance; the strict add_match and scoped gate logs supply relocation verification.

## Verification and collection

`build/stealth-wrapper/add_match.log` and `build/stealth-wrapper/scoped_gate_bash.log` both pass the strict one-function byte gate, including all eight relocation sites. `pin_consistency_final.log`, `declared_unmatched.log`, `class_gate.log`, and `name_oracle_check.log` pass. The name oracle has no StealthUpdate class witness, so its absence of conflicts is not used as positive layout evidence. No target bank was promoted, so comparison against an old wrapper bank is inapplicable. No shared header or shim was changed, so this isolated source change does not require a full gate.

`build/stealth-wrapper/check_csv.log` reports exactly one problem: the new source exists but is not Git-tracked. The checkout forbids Git writes, so the coordinator must stage this source and rerun check_csv before committing. The initial check_csv passed. No baseline was broadened; incidental stale allowance removals made by add_match were preserved in scratch and restored outside the assigned scope. The scoped gate was invoked with the explicit Git Bash executable after a cmd invocation failed to resolve build.cmd; both raw logs remain available.
