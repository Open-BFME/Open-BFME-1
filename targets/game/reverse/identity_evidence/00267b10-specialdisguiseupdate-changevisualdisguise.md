# 0x00267B10 SpecialDisguiseUpdate::changeVisualDisguise (390 B)

The row was the gen-dump scaffold `?d_00267b10@@YAXXZ` (game/gen_asm/d_00266ef0.asm).
The body is `?changeVisualDisguise@SpecialDisguiseUpdate@@QAEX_N@Z`.

## BFME 1 target evidence
- `ilt_oracle.py check ?changeVisualDisguise@SpecialDisguiseUpdate@@QAEX_N@Z 0x00267B10`:
  CONFIRMED (p_false 2.61e-04, exact). Contradicted: the `AAE`/`IAE` access
  spellings, the argument-less `QAEXXZ`, `StealthUpdate::changeVisualDisguise(bool)`,
  the earlier opaque `?m00267B10@Rva00267B10@@QAEXE@Z` and
  `?rva00267B10@SpecialDisguiseUpdate@@QAEX_N@Z`.
- Callers reach it through ILT 0x00020847 with ECX = the module and one byte
  argument: SpecialDisguiseUpdate::triggerAbilityEffect (0x00267D80, landed,
  twice), Rva00267D00 (0x00267D00) and Player::becomingLocalPlayer.
- Boundary: no SEH frame; RET 4 at +0x183; 390 bytes.
- Callees by ledger name: Object getDrawable (slot 10), notifyModelConditionChanged,
  AI slot 127, Gen001C9A10::handle(0x15), Rva001BEEE0GuardedVCall::forward(6),
  BfmeThingFactory::findTemplate (twice, module data +0x25C name),
  TheGameClient slot 24, Overridable::getFinalOverride (owner template),
  BFMEThingFactory::newDrawable(template, 0, -1), GameLogic::bindObjectAndDrawable,
  Drawable::setPosition, Thing::setOrientation, Object::clearModelConditionFlags
  and its ledgered set partner Object::bfmeClearYG (both on a 40-byte copy of
  Object+0x110), BfmeThingCF::bfmeSendCF (Drawable+0x3B8 value), TheInGameUI
  slot 56.

## Donor evidence (BFME 2, 59e3f8f825)
- `Code/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdate.cpp`
  `?rva004B04B2@SpecialDisguiseUpdate@@QAEX_N@Z` (BFME 2 0x004B04B2, 323 B,
  matched there, address-named), whose note cites WorldBuilder's debug body
  and Zero Hour's StealthUpdate::changeVisualDisguise for the shape: same
  statement sequence (selected flag; force-mounted disguised owner is
  mounted; disguise template check; copy conditions, keep a drawable value,
  destroy the drawable; two newDrawable calls for own/disguise template;
  bind, position, orientation, opacity; re-apply conditions; restore the
  value; reselect).
- The donor's out-of-line `rva004B031E` lookup (a local module-data pointer,
  then findTemplate) is inlined at both uses here; that exact spelling is what
  reproduces retail's register choice.
- Differences adapted from BFME 1 retail: condition words live at
  Object+0x110 (disguised bit 267 at +0x130, mounted bit 203 at +0x128), AI
  +0x204 slot 127, module data name +0x25C and flag +0x268, drawable selected
  +0x3AC and kept value +0x3B8, module opacity +0xEC; the mounted-armor step
  is the guarded forward(6) rather than setArmorSetFlag.

## Structural inference
- The method name comes from the ILT oracle and the Zero Hour counterpart;
  the bool's meaning (true = owner's own template) follows from the two
  branches.
