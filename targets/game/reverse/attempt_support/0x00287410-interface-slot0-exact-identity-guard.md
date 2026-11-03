# 0x00287410 (346 B): exact C++ banked; landing blocked by identity_guard on 0x00286F80

Session a1 s547 (2026-11-03), model claude-opus-5-5. No donor source used.

## Body (exact)

Bank: `targets/game/reverse/attempts/0x00287410.cpp`, probe `EXACT (modulo
relocation slots)` and `add_match` scoped build verified OK (346/346, 15 relocs).
Intended home `game/GameEngine/Source/GameLogic/Object/Update/Rva00287410SmartBombInterface.cpp`,
name `?method@Rva00287410Owner@@UAEXPAVObject@@W4CommandSourceType@@@Z`.

Identity (BFME 1 target evidence): slot 0 of vtable 0x010BC684, which the
constructor at 0x00286F80 installs at `[this+0x20]`; ECX is that interface,
`[ecx-0x18]` is the module's object, `[ecx+4]` (+0x24) a stored target ID; two
stack args, `ret 8`, no teardown. So the two matched naked-lift names on this
extent, `??1SmartBombTargetHomingUpdate@@UAE@XZ` and
`??1PointDefenseLaserUpdate@@UAE@XZ`, are both wrong (the real dtor is
`??1SmartBombTargetHomingUpdate@@MAE@XZ` 0x00286DC0). Method name unproven.
Note: neither "SmartBombTargetHomingUpdate" nor "PointDefenseLaserUpdate" occurs
in lotrbfme.exe; "BloodthirstyUpdate" does. The 0x00286F80 constructor carries
all three names (one_identity surplus); the owner is most likely BloodthirstyUpdate.

## Blocker

Landing = manual tombstone of the `??1PointDefenseLaserUpdate` row + `add_match
--replace-rva 0x00287410 --correct-identity ??1SmartBombTargetHomingUpdate@@UAE@XZ
--identity-evidence ...` + delete both lift TUs + drop their two hatch_baseline
lines. Everything verifies, but pre-commit identity_guard fails:
`ctor_vtable.contradicted: 0x00286F80 ??0PointDefenseLaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z`
-- that ctor name's only support was the wrong dtor row in slot 0 of 0x010BC684.
Retiring the ctor row empties `PointDefenseLaserUpdateCtorThunk.cpp` (zero-row
TU is refused) and ZH `ModuleFactory.cpp` still `addModule(PointDefenseLaserUpdate)`
(friend_newModuleInstance row 0x00113FB0, also two names), so the repair spreads
into ZH-only module registration.

Next step: whoever retires the ZH-only PointDefenseLaserUpdate names
(0x00286F80 ctor, 0x00113FB0 factory, the ctor TU) can land this bank in the same
commit with the recipe above.

## Levers found (measured on this body)

- Early returns + info/list at function scope: frame 0x28 (no slot sharing).
- `{}` block for info+list after the last use of `target`: frame 0x24 but list in
  target's dead arg home, temp in the second arg's.
- Block (here `if (ai) { ... }`) opened BEFORE `aiForceAttackObject(target, ...)`:
  list in the frame sharing the spilled-`this` slot, temps in arg1 home: exact.
- `Int id = object->m_id; iface->set(id);` and `Int parentID = parent->m_id;
  m_targetID = parentID;` fixed an eax/ecx/edx rotation.
