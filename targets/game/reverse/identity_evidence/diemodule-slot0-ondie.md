# DieModuleInterface slot 0 is onDie

Facts read from `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`
(image base 0x00400000) with pefile and capstone. Owners come from
`targets/game/reverse/module_registry.tsv` (string-literal registrations).

Each registered `*Die` module's constructor stores three vtables. The one at
+0x10 is a one-slot table: the next dword is either zero or the start of the
adjacent +0x0C table. Zero Hour's `DieModuleInterface`
(`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h:49`)
declares exactly one virtual, `onDie(const DamageInfo *damageInfo)`. So slot 0
of that table is the class's onDie. Zero Hour declares every override
`public: virtual void onDie(const DamageInfo *)`, which mangles
`?onDie@<Class>@@UAEXPBVDamageInfo@@@Z`. The matched rows CreateCrateDie
(0x00254400), CreateObjectDie (0x00254900), FXListDie (0x002554C0), RefundDie
(0x00255BE0) and SpecialPowerCompletionDie (0x00256070) already sit in that
slot.

| Owner (registry) | registered ctor | +0x10 table | slot-0 ILT (refs) | body | ledger name before |
|---|---|---|---|---|---|
| CrushDie | 0x00254B90 | 0x010B2BB8 | 0x00035A08 (1) | 0x00254CF0 | `?d_00254cf0@@YAXXZ` (dump, not converted) |
| DestroyDie | 0x00254F80 | 0x010B2D08 | 0x0001E718 (1) | 0x002550A0 | `?bfmeGo1025S@BfmeS1025@@QAEXH@Z` |
| HeroDie | 0x00255670 | 0x010B3064 | 0x00041CA9 (1) | 0x00255790 | `?bfmeGo926E@BfmeThing926E@@QAEXPAX@Z` |
| KeepObjectDie | 0x00255870 | 0x010B315C | 0x00045F3E (1) | 0x00255990 | `?run@Rva00255990Owner@@QAEXPAX@Z` |
| UpgradeDie | 0x002560E0 | 0x010B3444 | 0x0003CD35 (1) | 0x00256240 | `?d_00256240@@YAXXZ` (dump, not converted) |

Each ILT stub's VA appears once in the image, so each body is its class's
own override. The DestroyDie body is Zero Hour's
`DestroyDie::onDie`: `if (!isDieApplicable(damageInfo)) return;
TheGameLogic->destroyObject(getObject());` (the check is the module data's
+0x8 die-mux test, and the destroy call is a tail jump through
TheGameLogic 0x012F0898).
