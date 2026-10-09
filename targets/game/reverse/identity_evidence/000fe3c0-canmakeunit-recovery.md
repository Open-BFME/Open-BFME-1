# BuildAssistant::canMakeUnit recovery

The BFME body at RVA 0x000FE3C0 is `BuildAssistant::canMakeUnit(Object *, const ThingTemplate *, int) const`. The reconstructed source is `game/GameEngine/Source/Common/System/BuildAssistant_canMakeUnit.cpp`. Its scoped gate passes, including call relocation resolution, the callback address and the complete return boundary. The visible `ThingTemplate::isKindOf` helper independently reproduces its existing retail body. This recovery adds no symbol pin and changes no shared header.

## Identity and complete boundary

The constructor at 0x000FDA80 installs table VA 0x010860D8. Table slot 16 contains ILT 0x00047672, whose decoded jump reaches 0x000FE3C0. Slot 17 contains ILT 0x0004A692 to 0x000FDBF0; slot 18 contains the already recovered `BuildAssistant::sellObject`. The matched update and sell-list neighbours identify the same owning table. The existing `000fe3c0-buildassistant-canmakeunit.md` records the independent subsystem registration and Zero Hour twin evidence.

The complete target has no outgoing conditional branch or tail jump. Every exit cleans three stack slots with `ret 0x0C`; the last return is at +0x198, followed by INT3 at +0x19B. The target does not register an exception frame or construct an owning local. The complete Dozer caller at 0x002B7C80 and Worker caller at 0x002C96D0 dispatch slot +0x40 with object, template and signed sentinel -1, then test the dword return. The target forwards those same arguments to slot +0x44, whose complete body returns its boolean in AL and also cleans three slots. No hidden return storage or receiver adjustment occurs in either target call.

## Layout and callee contracts

Object uses the shared `object.h` definition. The target tests `m_scriptStatus` at +0x343. The two mask values are the shipped Zero Hour `OBJECT_STATUS_SCRIPT_DISABLED` and `OBJECT_STATUS_SCRIPT_UNPOWERED` values, and their OR is precisely the retail byte test. The inline accessor is absent as a separate retail body.

`Object::getProductionUpdateInterface` follows the behavior array at Object+0x1F0, adjusts each behavior receiver by +0x0C and calls slot +0x6C. ProductionUpdate's constructor installs its production interface table at primary+0x20. Interface slot 0 reaches 0x0029C2D0: it takes no stack argument, compares the queue count with module data and returns dword codes 0 or 4. The local interface declaration keeps the slot identity opaque.

`getControllingPlayer` follows Object+0x23C and tail-jumps through ILT 0x0002369B to the complete Team accessor at 0x000EC8F0. The target's money amount is the unsigned dword at Player+0x4C, represented by Money+0x04 inside Player+0x48. Its comparisons use unsigned `ja` and `jbe`.

The signed third argument selects the record receiver at Player+0x684. The existing `BfmeBuildIndexSetter::set` pin reaches 0x000F9570, whose complete body takes one stack dword and returns the result of the same two-argument build-cost routine used by the template path. ILT 0x00002135 reaches the complete pointer-returning resolver at 0x000F9670. The source uses a member-pointer ABI view of that existing thunk because MSVC 7.1 rejects a free `__thiscall` function-pointer declaration. This introduces no new pin or claim about the record owner's semantic identity.

The capacity receiver is Player+0x30. Its existing 0x000C7CD0 declaration returns a byte, cleans two stack dwords, reads the template's requirement at +0x4B4 and flag word at +0xD8, and compares receiver+0x08 plus requirement against receiver+0x04. The second argument is unused in its complete body. The limit field is the witnessed unsigned short `ThingTemplate::m_maxSimultaneousOfType` at +0x480.

## Callback contract

The callback's existing name and declarations remain unchanged. Its complete body at 0x000FC2A0 accepts two cdecl pointers, reads both words of `Rva000FC2A0Tally`, adds a dword result to `total` and returns the integer 1 on every path. The target stores the template pointer's bits in the existing integer `argument` field. This is pointer transport, not an integer record selector.

The callback's ILT 0x0000B6BD reaches the complete 0x0029C090 production-interface lookup. Its field accesses and slot +0x6C agree with the canonical Object behavior layout. Its interface call at +0x18 reaches 0x0029BF50 through table slot 6 and ILT 0x00027A93. That complete counter passes the transported pointer as the `ThingTemplate::isEquivalentTo` receiver and queue-entry+0x08 as its template argument for kind-1 entries. The full equivalence helper at 0x0013FE10 was decoded; it returns AL and cleans one argument. Interface slots 18 and 19 reach the complete queue getters at 0x0029CC40 and 0x0029CC50, which read interface+0x08 and node+0x3C respectively.

Player's void-typed iterator spelling reaches ILT 0x0002F1CB and the complete int-returning walk at 0x000CDCF0. Its complete inner walks at 0x000EE770 and 0x000EDAB0 consume the callback's dword return after cdecl cleanup. The existing `PlayerIterateObjects.cpp` already implements that checked callback cast. The conversion uses the same explicit function-pointer adaptation rather than changing a shared declaration or retyping the callback. Both arguments retain their pointer width and order.

`countObjectsByThingTemplate` takes five stack slots. Its retail body spans 90 bytes through `ret 0x14`, although its existing ledger row records 84. Both extents were inspected and the complete extent was checked. The count is written through the fourth argument; retail reuses the dead builder parameter slot for this local. The unrelated counter row is unchanged.

## Experiment and refutation evidence

The retry hypothesis was that current canonical Object layout and actual callback ABI remove the earlier declaration blockers, and that authentic callee visibility controls the remaining temporary lifetimes. The hypothesis would fail if the complete callback used another payload type or cleanup convention, or if compiling the real non-inlined helper failed to reproduce both bodies.

The first compiling body reproduced the frame and control flow but differed in scratch registers and disabled-return placement. Native separate script-status bit tests recovered the early bytes. Capturing money before the cost call recovered the unsigned comparison scheduling. Explicit template aliases, alias reassignment, scope splitting, money accessor visibility and reordered tally stores did not recover the complete target. The decisive experiment exposed the authentic `ThingTemplate::isKindOf` implementation while keeping its call out of line. That recovered the template reload, stack reuse, callback stores and remaining registers simultaneously. The helper's own complete body also matches; it is not a simplified side-effect substitute.

Local reproduction evidence is retained under `build/fe3c0/`: every trial source, unedited probe output, `measurements.jsonl`, complete decoded target and helpers, checked callee inventories and the strict `add-match.txt` gate. The final-source probe is `BuildAssistant_canMakeUnit.probe.txt`, and the independent helper probe is `helper-final-probe.txt`. These measurements are against base revision `3308e6e98b37d847e81639c1c375ba4c1a9b1ab4` and the retail 1.03 unpacked baseline. No remaining target identity, boundary or ABI check is unresolved.

## Verification and collection

The final scoped gate passes through `C:/Program Files/Git/bin/bash.exe build.sh game/GameEngine/Source/Common/System/BuildAssistant_canMakeUnit.cpp`; its raw output is `build/fe3c0/scoped-gate-bash.txt`. The Windows batch wrapper cannot locate its Python launcher in the worker sandbox; both failed wrapper outputs are retained separately. `find_declared_unmatched.py --fail`, `class_gate.py`, `pin_consistency.py --check` and `name_oracle.py --check` pass, with raw outputs in `declared-unmatched.txt`, `class-gate.txt`, `pin-consistency.txt` and `name-oracle.txt` respectively. No shared header or shim changed, so the documented full-gate trigger does not apply.

`check_csv.py` reports only that the new source exists but is not tracked. This worker cannot write `.git`; the coordinator must stage the new source and rerun that check. Its unchanged raw output is `build/fe3c0/check-csv.txt`. The final source probe was moved from the source directory to `build/fe3c0/BuildAssistant_canMakeUnit.probe.txt`; the last historical entry in `measurements.jsonl` retains its original path. `receipt.json` records this mapping, the source hash, the tested revision and the clock-based duration.
