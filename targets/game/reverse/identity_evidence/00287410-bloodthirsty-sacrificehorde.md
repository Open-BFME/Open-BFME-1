# 0x00287410 is BloodthirstyUpdate::sacrificeHorde, not a destructor

Retail body 0x00287410, 346 B: SEH prologue, `sub esp,0x24`, ends `ret 8` at
+0x157 (two stack arguments). No vptr restore, no base/member destructor chain,
no operator delete. The two matched naked-lift names on this extent are wrong:

- `??1SmartBombTargetHomingUpdate@@UAE@XZ` (the destructor of the class whose
  primary vtable the 0x00286F80 constructor installs is the 32-byte 0x00286DC0)
- `??1PointDefenseLaserUpdate@@UAE@XZ`

## Identity (BFME 1 target evidence)

- `targets/game/reverse/ea_evidence.csv`: 0x00287410 name
  `BloodthirstyUpdate::sacrificeHorde` (route chain+direct, aligned), file
  `GameEngine/Source/GameLogic/Object/Update/BloodthirstyUpdate.cpp`; its
  neighbours 0x00287130/0x002871F0 are `BloodthirstyUpdate::isValidSacrifice`.
- `tools/ilt_oracle.py check '?sacrificeHorde@BloodthirstyUpdate@@UAEXPAVObject@@W4CommandSourceType@@@Z' 0x287410`:
  CONFIRMED (exact); an address-derived spelling is CONTRADICTED.
- `vtable_lookup.py --target 0x00287410`: slot 0 of vtable 0x010BC684, which the
  constructor 0x00286F80 stores at `[esi+0x20]`. module_registry.tsv registers
  BloodthirstyUpdate's factory 0x00114030 with constructor 0x00286F80;
  phantom_modules.tsv lists PointDefenseLaserUpdate and
  SmartBombTargetHomingUpdate as ABSENT from retail (no such strings in
  lotrbfme.exe), so `??0PointDefenseLaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z`
  at 0x00286F80 is retired with the destructor rows it leaned on.

## Shape (target evidence)

ECX is the +0x20 interface: the module's object is `[ecx-0x18]` (+0x08), the
stored target ID `[ecx+4]` (+0x24). Arguments: the victim `Object*` and a
`CommandSourceType` (passed through to `AICommandInterface::aiForceAttackObject`
with 0x7FFFFFFF shots). Voice message 0x7E9 via `pickAndPlayUnitVoiceResponse`.

## Donor (BFME 2, carried, not used as source)

open-bfme-2 reverse/functions.csv has the same +0x20 slot-0, RET 8,
victim/source body as its placeholder `?n@BloodthirstyUpdate@@UAEXPAVObject@@W4CommandSourceType@@@Z`
(0x0044E374, 309 B). The BFME 1 name comes from the EA evidence above.

The factory alias `?friend_newModuleInstance@PointDefenseLaserUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z`
(0x00113FB0, shared with the SmartBombTargetHomingUpdate spelling) is retired
too: its only callee spelling was the retired phantom constructor alias.
