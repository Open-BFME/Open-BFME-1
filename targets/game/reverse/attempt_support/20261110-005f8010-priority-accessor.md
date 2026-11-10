# 0x005F8010 streak draw pass (976 B): EXACT

## Result

The best candidate is `build/wf/005f8010/best.cpp`. It defines
`?render@Rva005F8010@@QAEHAAVRenderInfoClass@@PBUBounds005F8010@@PAH@Z`, and
`probe.py` reports 976/976 B, 51 relocations, `result EXACT (modulo relocation slots)`.

- Compiler line (unchanged from the bank): `/DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2`.
  These are the same switches as the matched sibling `DefaultDrawModuleDraw_005F31A0.cpp`, which uses the same include roots plus two more.
- BFME 2 donor reviewed at 2bac16a65: `Code/GameEngine/Source/GameClient/System/FXParticleSystem/StreakDrawModuleDoParticles.cpp`, `?doParticles@StreakDrawModule@FXParticleSystem@@...` at BFME 2 0x0055FD6B, exact there under `/O1 /G7`.
  Its structure is the same, but the lever below did not come from it. Zero Hour's `W3DParticleSys.cpp` streak branch writes `sys->getPriority() == AREA_EFFECT`.

## The fix (one source line)

The bank had a 4-byte residue at +0x23B/+0x23F, the loop-exit reloads:
```
retail: mov ebp,[esp+0x10] ; mov edi,[esp+0x14]   (colour base, then this)
bank  : mov edi,[esp+0x14] ; mov ebp,[esp+0x10]
```
The fix reads the in-loop priority through an inline accessor instead of the raw field:
```cpp
int getPriority() const { return priority7C; }          // in System005F8010
*fieldCount+=(system()->getPriority()==11 && system()->ground80);
```
This changes no instruction elsewhere. It is the same lever as the documented 0x004AE080 case in `docs/shape_levers.md` ("an accessor the front end can inline is not a cast"): the callee-saved reload order at a loop edge follows front-end node numbering.
- How it was found: `system()` in the form `S *s=system04; if(!s) s=make(); return s;` flipped the order at every site (171 diffs, because the switch site lost retail's ternary arm shape).
  A 32-way per-site sweep (`gen13.py`) then showed that only in-loop sites 1 and 2 matter. Changing either one to the if-form gives EXACT, and the switch site must stay a ternary.
  The natural one-accessor spelling, `getPriority()`, gives the same result.
- `getPriority()` is not the only spelling that works: `system()->getPriority()==11 && system()->isGroundAligned()` is also EXACT (`v/f5.cpp`).

The remaining edits make the candidate landing-ready, and each one was re-probed EXACT (`v/s1..s7.cpp`):
- recorded global names (`g_vector3Buffer`, `g_vector4Buffer`, `g_floatBuffer`, `g_byteBuffer`, `g_rva005F7FA0Resource` typed `StreakLineClass*`, the ShaderClass presets, and `g_Va012D6E24/28/30/48` and `g_Va011135A8` as in the matched siblings);
- `ShareBufferClass` from `sharebuf.h`;
- `AsciiString::str()` (from `ascii_string.h`) for the texture name;
- `TextureClass::Release_Ref` from `texture.h`;
- `RenderInfoClass&` for the first parameter;
- the render slot moved onto `StreakLineClass` (slot 12, `Render`).

## Hypotheses tested and ruled out (all kept 4 diffs unless noted)

| Family | Change | Result |
|---|---|---|
| CF | `count++; if(count==512)`, `++count;`, `{ for }` block, `p` declared before loop, do-while, goto exit, `while`, `>=512` | 4 or worse; reload order never flipped |
| CF | `count<512` in loop condition | 585 diffs, order still this-first |
| lifetime | `self=this` at top/after arrays/after loop | 4 |
| lifetime | reference/pointer locals for `rgbaArray[count]` / `posArray[count]` | 4-10 |
| lifetime | second colour local (CSE), zeroing via alias, `->`, `Set()` | 4 |
| types | `void*` bounds + cast, `RenderInfoClass&`, virtual owner class, AsciiString name + `str()` | 4 |
| callee visibility | real member decls for particle getters, shader `set(ShaderClass)`, free fallback fn | 4 |
| callee visibility | DefaultDraw-style handle `operator->` | 11 (arm order) |
| accessor form | ternary arm swap / `if(x) return x;` | 4-11 |
| accessor form | `s=system04; if(!s) s=make();` at all sites | flips order, 171 diffs |
| accessor form | same, only at in-loop sites | **EXACT** |
| TU context | 1-12 preceding functions (global label counter) | 4 |
| flags | `flag_sweep.py`, 90 variants | best 4 |
| rotation | `rotation_sweep.py --pairs`, 251 toggles | best 4 |

The trial log is `build/wf/005f8010/trials.log`. The variants are under `build/wf/005f8010/v/`.

## Landing notes (read-only checks; nothing landed)

**(a) ILT oracle**

`ilt_oracle.py check` returns CONTRADICTED (p_false 1.6e-3) for the render name at 0x005F8010. The ILT for 0x005F8010 is 0x0003D541. Only the gen-thunk row `?j_0003d541@@YAXXZ` exists there, and symbols.csv has no address-derived pin at that ILT, so no better name is available.

The matched sibling `?method@Rva005F31A0@@...` is CONTRADICTED the same way. Keep the address-derived owner name.

**(b) Helper bodies the TU emits that have their own ledger rows**

Each emitted copy was probed against its retail row, and all are EXACT:
- `?Fabs@WWMath@@SAMM@Z` (0x003D5300)
- `?validate@?$StringBase@D@@ABEXXZ` (0x0005D790)
- `?peek@?$StringBase@D@@ABEPADXZ` (0x0005E5B0)
- `?str@?$StringBase@D@@QBEPBDXZ` and `?str@AsciiString@@QBEPBDXZ` (0x0005F270)

These copies are not link losers. The other inline COMDATs have no ledger rows, the same as in the sibling:
- `system()`
- `getPriority()`
- the `Get_Array` instantiations
- `??0ShaderClass@@QAE@ABV0@@Z`
- the handle destructor
- the `invoke005F8010` instances

Run `find_declared_unmatched.py` on the staged file anyway.

**(c) Callees: every call binds to a ledger name**

- ILT rows: `?j_00038a5f`, `?j_000309f9`, `?j_00037308`, `?j_0001153b`, `?j_00022796` and `?j_00001b18@@YAXXZ`. They are called through the bank's `invoke005F8010` helper and the function-pointer cast.
- `?BFMEGetWaterTrackTexture@@YA?AVBFMEWaterTrackTextureHandle@@PADHH@Z`
- `?bfmeGoDUC@BfmeThingDUC@@QAEXXZ`
- `?Set_Texture@StreakLineClass@@QAEXPAVTextureClass@@@Z`
- `?set@Rva00918DA0@@QAEXH@Z`, called through the bank's pointer-to-member union so that it takes the ShaderClass by value
- `?bfmeSetUGB@BfmeStreakUGB@@QAEXIPAX00H@Z`
- `?Release_Ref@TextureBaseClass@@QAEXXZ` (0x009EB7A0, a functions.csv row)
- `__ftol2`

**(c) Globals the body references by address**

| VA | Name | Recorded in |
|---|---|---|
| 0x012F6DC8 / DCC / DD0 / DD4 | `g_vector3Buffer` / `g_vector4Buffer` / `g_floatBuffer` / `g_byteBuffer` | dir32 |
| 0x012F6E30 | `?g_rva005F7FA0Resource@@3PAVStreakLineClass@@A` | data_rows and dir32 |
| 0x012D6E2C | `_PresetAdditiveSpriteShader` | data_rows |
| 0x012D6E34 | `_PresetAlphaSpriteShader` | dir32 |
| 0x012D6E60 | `_PresetMultiplicativeSpriteShader` | data_rows |
| 0x012D6E24 / 28 / 30 / 48 and 0x011135A8 | `g_Va012D6E24/28/30/48`, `g_Va011135A8` | not recorded; spellings already used by the matched `DefaultDrawModuleDraw_005F31A0.cpp` and `LightningDrawModuleDraw005F43B0.cpp` |
| 0x0107388B | `?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB` | dir32 has the AsciiString spelling; same as the sibling |

**(d) Home TU**

Use a new file, `game/GameEngine/Source/GameClient/System/FXParticleSystem/StreakDrawModuleDraw_005F8010.cpp`, next to the default-draw (0x005F31A0) and lightning-draw (0x005F43B0) siblings. Those siblings declare their own Particle and System views, so merging into one of them would create duplicate class views.

Land with `add_match.py --replace-rva 0x005F8010`. The ledger row is currently `?d_005f8010@@YAXXZ` and points at `game/gen_asm/d_004e8320.asm`.
