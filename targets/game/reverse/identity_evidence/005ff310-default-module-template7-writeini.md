# Category-7 wind module template writeINI at 0x005FF310

The 767 bytes at 0x005FF310 were claimed as `?dup_005ff310@@YAXXZ` and proven
only by a `__declspec(naked)` `__emit` copy in
`game/GameEngine/Source/GameClient/System/ParticleSys.cpp`, filed under the
refuted identity `?update@ParticleSystem@@UAE_NH@Z` (vtable slot 4 of the
ParticleSystem table 0x0110FE48, which is 0x005D1140). The new name is
`?writeINI@?$DefaultModuleTemplate@$06@FXParticleSystem@@UBEXAAVFile@@I@Z`, i.e.
`FXParticleSystem::DefaultModuleTemplate<7>::writeINI(File &, unsigned int)
const`.

## The vtable slot

* The matched constructor `??0?$DefaultModuleTemplate@$06@FXParticleSystem@@QAE@XZ`
  (0x005DEA80, `DefaultModuleTemplate6CtorThunk.cpp`) stores three table anchors
  at `this+0/+4/+8`; the `+0` anchor is the `DefaultModuleTemplate6_vtbl0` pin at
  0x0111101C. Its slot 3 is 0x0003462B, a five-byte ILT thunk whose `jmp`
  displacement lands on 0x005FF310.
* Slot 3 is `writeINI(File &, unsigned int) const` in this family, and the
  ledger proves it on three sibling tables of the same shape (all
  `DefaultModuleTemplate<N>` primary tables, each installed by its own matched
  constructor):

  | table | class | slot 3 thunk | body | matched name |
  | --- | --- | --- | --- | --- |
  | 0x01110C50 | `DefaultModuleTemplate<2>` | 0x0001CE6D | 0x006000B0 | `?writeINI@?$DefaultModuleTemplate@$01@FXParticleSystem@@UBEXAAVFile@@I@Z` |
  | 0x011108B8 | `DefaultModuleTemplate<1>` | 0x0002E492 | 0x005EEF50 | `?writeINI@?$DefaultModuleTemplate@$00@FXParticleSystem@@UBEXAAVFile@@I@Z` |
  | 0x01110938 | `DefaultModuleTemplate<6>` | 0x0003B22D | 0x005F3870 | `?writeINI@?$DefaultModuleTemplate@$05@FXParticleSystem@@UBEXAAVFile@@I@Z` |

  The declared signature also matches: 0x005FF310 takes two stack arguments
  (`ret 8`) with `ecx` as `this` and addresses the second one (`&flags`) to
  write, which is the `UBEXAAVFile@@I@Z` shape.
* The concrete table 0x01111048 is the `+0` anchor of the matched
  `??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@...`
  constructor and its slot 3 is the same thunk 0x0003462B, so the template and
  the concrete template share this one body and there is no second identity.
* MSVC encodes the template argument as `value - 1`, so `$06` is
  `DefaultModuleTemplate<7>` (the same convention the matched
  `DefaultModuleTemplate6CtorThunk.cpp` file documents for its own `$06`). The
  template argument is the module category: the landed category-7 header writer
  at 0x005FF160 (`Rva005FF160WriteWindHeader.cpp`) carries
  `MODULE_CATEGORY_WIND = 7`, and 0x005FF310's first call is to it.

## The body agrees

Every key in the body is a retail string literal pushed beside the field it
guards: `WindMotion` (0x010891d8, valued through the `WindMotionNames` table at
0x01110244, which reads `NONE/Unused/PingPong/Circular` from the image), then
`WindStrength`, `WindFullStrengthDist`, `WindZeroStrengthDist`,
`WindAngleChangeMin`, `WindAngleChangeMax`, `WindPingPongStartAngleMin`,
`WindPingPongStartAngleMax`, `WindPingPongEndAngleMin`,
`WindPingPongEndAngleMax`, `TurbulenceAmplitude` and `TurbulenceFrequency` at
0x01114754..0x01114644. Each guarded value is compared against retail's
immediate default before being written, which is why the member names above are
read off the body rather than invented. The `Wind*`/`Turbulence*` names have no
Zero Hour source in the reference tree; nothing here claims one.

## Scope

The naked function is deleted from `ParticleSys.cpp` (the file's other bodies
stay) and the real C++ body lives with the rest of the family in
`FXParticleSystem/WindModuleTemplateWriteINI.cpp`. No inline assembly, no
`__emit`, no `__declspec(naked)`. The claimed range is unchanged at 767 bytes:
probe reports 767/767 with 28 relocation sites, exact outside the relocation
slots, and the scoped build byte-verifies the row.
