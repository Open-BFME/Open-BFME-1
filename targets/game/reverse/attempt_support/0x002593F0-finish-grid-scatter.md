# 0x002593F0 Rva00259670Primary::finish (512 B, bank 0.992)

Session a1 s507, model claude-opus-5-5, VC7.1 `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS`.

Extent: the gen_small row stops at 496 B mid-instruction; the real body ends with `ret 4` at +0x1FD (512 B,
INT3 pad at +0x200), as the earlier 512 B verdict said. Caller 0x00259670 (Rva00259670Dispatch::run) reaches
it through ILT 0x00041A4C on this-0x10; the argument is unused. Owner identity is still unproven.

Body (BFME 1 target evidence): setWeather(4) on TheGlobalWeatherSystem; TerrainLogic slot 8 extent; module data
(this+4) +0x214 FXList played at the extent centre (bfmeIsBlocked guard, doFXPos), then a grid over the extent
with spacing +0x21C (> g_bfmeDefaultBU) spawning findTemplate(+0x218) via newObject + setPosition.

Bank `targets/game/reverse/attempts/0x002593f0.cpp`: 4 bytes left, two loads swapped at +0x130:
retail `mov eax,[y]; mov edx,[x]`, ours `mov edx,[x]; mov eax,[y]`. Shape 1.000.

Measured levers:
- center `(lo + hi) * 0.5f` (not hi + lo) gives retail's fld hi / fadd lo order.
- loading `data = m_data` before getExtent puts it before the call like retail.
- one `Coord3D pos` shared by the FX centre and the grid gives retail's slot sharing (0.912 -> 0.959).
- Plain Real loop vars: MSVC hoists y into EDI for the inner loop (third saved register, 77 diffs). Inert:
  while loops, function-scope x/y, struct {x,y}, Real[2], const-ref/by-value inline helpers, `continue`,
  name reference, `advance(Real&)` helpers, /Op, /Ob2.
- `volatile Real y` with loop reads through `*(Real *)&y` removes the hoist (13 B left, x arg forwarded from x).
- also `volatile Real x` the same way: 4 B left (the load order above, volatile reads follow source order).
  Reordering stores (`pos.y` first), temps (`Real cy = y` -> fld/fst), setXY helper, arg assignments: worse.

Next idea: a non-volatile shape that keeps x/y memory-only (address really escaping somewhere), or a
store/load scheduling lever that loads y before x with pos.x stored first.
