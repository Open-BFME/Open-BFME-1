# ObjectHelper::sleepUntil at RVA 0x00256CD0

The 63-byte body at RVA 0x00256CD0 is `void ObjectHelper::sleepUntil(UnsignedInt when)`. The placeholder `?bfmeSetXW@BfmeHostXW@@QAEXH@Z` describes its arithmetic but has no independent class or member evidence. Only `game/GameEngine/Source/Common/BfmeConv2093.cpp` declares or defines that placeholder member. This correction preserves the existing start and extent and adds no byte coverage.

## Retail body and reference implementation

The baseline is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`. Disassembly of the complete body shows the following correspondence to `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Helper/ObjectHelper.cpp:52`.

| Retail RVA | Operation | Reference operation |
|---|---|---|
| 0x00256CD0 | Load the owning object from helper +8. | `getObject()` |
| 0x00256CD3 | Test bit 0 of the object's status at +0x90 and return when set. | Return for `OBJECT_STATUS_DESTROYED`. The BFME status layout differs from Zero Hour's enum numbering. |
| 0x00256CDC to 0x00256CE9 | Read the one 32-bit argument and compare it with zero and 0x3FFFFFFF. | Special-case `NEVER` and `FOREVER`. |
| 0x00256CEC to 0x00256CF2 | Read `TheGameLogic` at VA 0x012F0898 and subtract its frame at +0x3C. | `UPDATE_SLEEP(when - TheGameLogic->getFrame())` |
| 0x00256D00 | Select 0x3FFFFFFF for the special cases. | `UPDATE_SLEEP_FOREVER`, defined as 0x3FFFFFFF in `GameLogic/Module/UpdateModule.h`. |
| 0x00256CF8 and 0x00256D07 | Pass the object and delay to ILT 0x000157DA, retaining the helper as `this`. | `setWakeFrame(getObject(), wakeDelay)` |

The complete range ends with `ret 4` at 0x00256D0C and padding starts at 0x00256D0F. The entry is also preceded by INT3 padding. Ghidra and the existing matched ledger agree on the 63-byte extent.

ILT 0x000157DA reaches the independently matched `UpdateModule::setWakeFrame(Object *, UpdateSleepTime)` at RVA 0x002B2040. Its complete 30-byte body reads the same game frame, adds the delay, and calls ILT 0x00009944 with the object, helper and absolute wake frame. That ILT reaches the matched `GameLogic::friend_awakenUpdateModule` at RVA 0x0038D870. The scheduler clamps an excessive frame to 0x3FFFFFFF and stores the resulting wake frame at helper +0x14 (0x0038D959 to 0x0038D968). BFME stores the frame directly here; Zero Hour's `friend_setNextCallFrame` additionally packs the phase. The scheduling call chain, rather than a guessed direct store in `sleepUntil`, establishes the wake-frame operation.

## Complete caller inventory

A scan of every file-backed .text byte for E8 and E9 relative destinations equal to the body or any initial-ILT thunk reaching it yields exactly two candidates. Both are decoded instruction boundaries in both the ledger and Ghidra extents. The initial ILT contains exactly one thunk to this body, RVA 0x000159AB, with bytes `e9 20 13 24 00`. There are no direct calls to the body, no other relative call or jump sites to its thunk, and no HIGHLOW relocation references containing either address.

| Call or jump RVA | Destination RVA | Owner and meaning |
|---|---|---|
| 0x000159AB | 0x00256CD0 | The five-byte ILT thunk, not a second body. |
| 0x001C741B | 0x000159AB | Matched `Object::setStatus` at RVA 0x001C7370. It checks the newly set repulsor-status bit, loads `m_repulsorHelper` at Object +0x1D4, checks for null, and passes `TheGameLogic->m_frame + 10`. |

The independently matched C++ caller names this call `m_repulsorHelper->sleepUntil(TheGameLogic->m_frame + 10)` in `ObjectStatusBits.h:114`. Zero Hour's `Object::setStatus`, in `Source/GameLogic/Object/Object.cpp:989`, has the same repulsor-helper call context and calls `sleepUntil` with its frame-relative repulsion timeout. The timeout differs between the games; the helper, status transition and called operation agree. `symbols.csv` independently pins `?sleepUntil@ObjectHelper@@QAEXI@Z` at the same ILT with the note `Object::setStatus helper ILT`.

`Rva0017DD40Apply.cpp` also needs the name because its object emits the shared inline `Object::setStatus` copy. This is an additional compiled reference to the same source operation, not an additional retail call site. No retail caller supplies a competing identity. The reference twin alone would not prove a name, but its complete operation sequence agrees with the independently named matched retail caller and the existing pin.

## Reproduction

Raw session evidence is in `build/rlink/identity-audit.txt`, `build/rlink/retail-body.txt`, `build/rlink/retail-wake-frame.txt`, `build/rlink/retail-scheduler.txt`, `build/rlink/reference-audit-complete.txt`, and `build/rlink/pin-identity.txt`. `identity_audit.py` performs the complete relative-reference scan and instruction-boundary checks. `reference_audit.py` prints the reference source, ILT routes and entry/exit padding.

The source includes the existing `UpdateModule.h` and canonical `object.h`. Its TU-local `ObjectHelper` declaration inherits `UpdateModule` and calls the canonical protected `setWakeFrame` signature. An address-derived layout view reads the owning object at the proven +8 offset without emitting another out-of-line `ObjectModule::getObject` COMDAT. This is a field read, not an accessor or function alias. No shared header or caller source is changed.

Reproduce the body and scheduling chain with `python tools/dis_retail.py 0x00256CD0 63`, `python tools/dis_retail.py 0x002B2040 30`, and `python tools/dis_retail.py 0x0038D870 329`. The byte gate must verify the corrected C++ body and its named relocation targets before the correction is accepted.
