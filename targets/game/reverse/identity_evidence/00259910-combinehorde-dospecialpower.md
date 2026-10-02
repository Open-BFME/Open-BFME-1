# RVA 0x00259910 is CombineHordeSpecialPower::doSpecialPower

The 440-byte generated body at RVA 0x00259910 has a native class and virtual
method identity: `CombineHordeSpecialPower::doSpecialPower(unsigned int)`,
`?doSpecialPower@CombineHordeSpecialPower@@UAEXI@Z`.
This finding does not claim a C++ byte conversion.

All binary facts below were checked against
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe` (image base
0x00400000) with pefile and capstone. GhidraMCP independently finds
`9B EE 43 00` at VA 0x010B3D84, reads the same 100 table bytes at VA
0x010B3D58, and creates a 440-byte function at VA 0x00659910.

## Constructor proves the owner and receiver adjustment

The matched constructor
`??0CombineHordeSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z`
at RVA 0x002596F0 calls the SpecialPowerModule constructor and stores:

    00659704  mov dword ptr [esi],      010B3E94h
    0065970A  mov dword ptr [esi+0Ch],  010B3DD0h
    00659711  mov dword ptr [esi+10h],  010B3D58h

Thus VA 0x010B3D58 is the SpecialPowerModuleInterface table at complete-object
+0x10. Slot 11, at VA 0x010B3D84, contains ILT VA 0x0043EE9B. The E9 at
that stub targets VA 0x00659910. It is the sole absolute pointer to the stub
in the retail image. The body itself reads its Object pointer from
`[ecx-8]` and module data from `[ecx-0xC]`, consistent with that interface
receiver: complete-object+8 and complete-object+4 respectively.

## Slot identity is witnessed by BFME dispatch

The already matched `Object::doSpecialPower` at RVA 0x001C3790 obtains the
special-power interface, pushes its one unsigned command-options argument,
and executes `call [edx+0x2C]` at RVA 0x001C37D0. This is slot 11.
Its named clean C++ caller supplies the method spelling independently of
this generated body and of a decompiler's inferred names.

The table's neighbouring methods also identify the interface:

| Slot | Stub RVA | Body RVA | Independently established method |
|---|---|---|---|
| 2 | 0x0001E835 | 0x00268A90 | SpecialPowerModule::getPercentReady |
| 10 | 0x00022FD4 | 0x00267FF0 | SpecialPowerModule::pauseCountdown |
| **11** | **0x0003EE9B** | **0x00259910** | **This override of doSpecialPower** |
| 12 | 0x00015EE7 | 0x00259770 | Two-argument wrapper forwarding arg 2 to slot 11 |
| 13 | 0x00008887 | 0x00259760 | Two-argument wrapper forwarding arg 2 to slot 11 |
| 14 | 0x0002A6DF | 0x0026A690 | SpecialPowerModuleInterface::doSpecialPowerUsingWaypoints |
| 16 | 0x0000DC5B | 0x00268BA0 | startPowerRecharge |

The matched CloudBreakSpecialPower constructor at RVA 0x00259010 stores its
corresponding interface table VA 0x010B3B68 at `[esi+0x10]`. Slots 0-10 and
14-16 route to the same bodies as CombineHordeSpecialPower. Its slots 11-13
are class-specific replacements. Other named BFME overrides
`PlayerUpgradeSpecialPower::doSpecialPower` (0x00264100) and
`ProductionSpeedBonus::doSpecialPower` (0x002645D0) also occupy slot 11.

Zero Hour's `GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h`
declares doSpecialPower after pauseCountdown, then doSpecialPowerAtObject,
doSpecialPowerAtLocation and doSpecialPowerUsingWaypoints. This agrees with
the native BFME anchors; it is supporting evidence, not the owner proof.

## Body facts agree with the specific operation

The body returns with `ret 4` at RVA 0x00259AC5 and INT3 begins at
0x00259AC8, proving the 440-byte extent and one stack argument. It does not
read the command-options value. An Object disabled-mask guard at +0x1A4
precedes a virtual slot-16 call (+0x40), consistent with startPowerRecharge.
It builds filters, obtains candidate objects and queries each candidate's
containment module through matched Object::unidentified_001BFE20. It calls
that module's slot +0x6C with the acting Object, and on success submits the
candidate through the matched AICommandInterface::aiBfmeCommand45 at
RVA 0x00152C20 with command source 2. These are BFME-native horde-combination
facts; no guessed name for the containment slot or command is required.

## Conversion remains open

The old bank is a 96-byte scaffold that omits the real exception frame,
four filter layouts, filter linkage, iterator refcounting and allocator
cleanup. Its old anonymous owner is no longer an identity blocker. Exact
filter/iterator contracts and clean C++ code generation remain to be
recovered before repointing the ledger from its generated dump.
