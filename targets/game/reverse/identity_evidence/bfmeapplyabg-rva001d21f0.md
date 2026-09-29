# 0x001D21F0 is `BfmeK1094::bfmeApplyABG`

Boundary: 0x001D21F0 .. 0x001D228E, 159 bytes, the two `ret 8` exits at +0x87
and +0x9C are the only returns (`python3 tools/dis_retail.py 0x001D21F0 159`).

Identity evidence, independent of the byte match:

* The matched caller `?bfmeVisitABG@BfmeHostABG@@QAEXPAX0@Z` is a `matched`
  row at 0x00151560 (`targets/game/reverse/functions.csv`,
  `game/GameEngine/Source/Common/BfmeConv2130.cpp`). Its single call site
  reaches this body through ILT 0x00006DE8.
* `symbols.csv` carries `?bfmeApplyABG@BfmeK1094@@QAEXPAX0@Z` at 0x00006DE8,
  and `tools/pin_consistency.py --symbol '?bfmeApplyABG@BfmeK1094@@QAEXPAX0@Z'`
  reports `0x00006DE8 -> 0x001D21F0 extent=159 (matched)` with verdict
  `consistent`, so the ILT thunk and this body are one identity.
* The caller's own TU declares the receiver class `BfmeK1094` and its method
  `void bfmeApplyABG(void *, void *)` (two `void *` stack arguments, `ret 8`),
  which is the arity the retail body has.
* The body's own four callees are named and pinned: 0x000022BB ->
  `Overridable::getFinalOverride`, 0x00048CCA ->
  `ControlBar::findCommandSet`, 0x00003F80 ->
  `CommandSet::getCommandButton`, 0x000063CF ->
  `BfmeObjectDoCommandButton::doCommandButton`
  (`tools/pin_consistency.py --symbol '?doCommandButton@BfmeObjectDoCommandButton@@QAEXPBVCommandButton@@HH@Z'`
  reports `0x000063CF -> 0x001D1020 extent=2501 (matched)`, verdict
  `consistent`).

The dumped name `?d_001d21f0@@YAXXZ` (`game/gen_asm/d_001d1020.asm`, a
`gen-dump` scaffold row) is retired by the landing; the ASHR mapping here is
`?bfmeApplyABG@BfmeK1094@@QAEXPAX0@Z`.

No new class or member name is invented by the source: `BfmeK1094` comes from
the matched caller's declaration, `BfmeObjectDoCommandButton` is the pinned
three-argument `doCommandButton` view already used by
`ScriptActions_doTeamPartialUseCommandButton.cpp`, and the `Object` fields at
+0x04, +0x328 and +0x32c are the layout witnesses shared with
`ObjectDoCommandButtonAtObject.cpp`.
