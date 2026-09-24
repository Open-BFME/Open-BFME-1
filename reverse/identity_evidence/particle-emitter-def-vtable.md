# ParticleEmitterDefClass vtable 0x00D3F908

Slot 0 is `??_GParticleEmitterDefClass` and the table runs through
`Free_Props`; slot N is the dword at `0x00D3F908 + 4*N`. Its order is Zero
Hour's `part_ldr.h` declaration order with three BFME additions:
`Set_Future_Start_Time` after `Set_Vel_Inherit`, and
`Get_Blur_Time_Keyframes` / `Set_Blur_Time_Keyframes` after the frame
keyframe accessors. With those, all 35 slots the ledger had already named
agree with that order (none disagree), so the 12 unnamed or misnamed slots
between them are fixed by position:

| slot | body | stores | old row(s) | identity |
|---|---|---|---|---|
| 8 | `0x0098D2D0` | `+0x128` | `dup_0098d2d0`, `dup_98d2d0` | `Set_Emission_Rate` |
| 9 | `0x0098D2E0` | `+0x12C` | `AIUpdateInterface::setCompletedWaypoint` | `Set_Max_Emissions` |
| 11 | `0x0098D300` | `+0x13C` | `dup_0098d300`, `dup_98d300` | `Set_Gravity` |
| 12 | `0x0098D310` | `+0x140` | `dup_0098d310`, `dup_98d310` | `Set_Elasticity` |
| 15 | `0x0098D380` | `+0x164` | `Drawable::setFlashColor` | `Set_Burst_Size` |
| 36 | `0x0098D3F0` | `+0x0C` | `dup_0098d3f0` | `Set_User_Type` |
| 42 | `0x0098D4C0` | `+0x20C` | `dup_0098d4c0` | `Set_Subdivision_Level` |
| 43 | `0x0098D4D0` | `+0x210` | `dup_0098d4d0`, `dup_98d4d0` | `Set_Noise_Amplitude` |
| 44 | `0x0098D4E0` | `+0x214` | `dup_0098d4e0`, `dup_98d4e0` | `Set_Merge_Abort_Factor` |
| 45 | `0x0098D4F0` | `+0x218` | `dup_0098d4f0`, `dup_98d4f0` | `Set_Texture_Tile_Factor` |

The stores confirm the positions independently: slots 7 to 12 write
`+0x124`, `+0x128`, `+0x12C`, `+0x138`, `+0x13C`, `+0x140`, which is Zero
Hour's `W3dEmitterInfoStruct` order Lifetime, EmissionRate, MaxEmissions,
(two randomizer fields), FadeTime, Gravity, Elasticity.

Retail has no identical-COMDAT folding (`tiny-accessor-aliases.md`), so a
slot body is only the particle method. Retired as aliases of slot bodies:
`ThingTemplate::setReskinnedFrom` (slot 4), `GameWindow::setTooltipDelay`
(slot 5) and `Object::friend_setRadarData` (slot 16, contradicted as well
by `m_radarData` at `+0x20C` in `docs/object_layout.md`).

The same names had been claimed on eight other bodies with the same byte
shape and no named caller: `0x001065F0`, `0x0021A220`, `0x00253D20`,
`0x0026F930`, `0x002B6860`, `0x0035F090`, `0x005FC2D0`, `0x0077E040`, and
`Set_Noise_Amplitude` on `GameWindow::winSetLayout` at `0x00478E10`. None is
referenced from this vtable. Where the particle name was the only row, the
body keeps an address-derived name in `RvaUnnamedDwordSetters.cpp`;
`0x0026F930` is called on `Object->m_ai` from two path-state exits with the
argument 0.
