# `?init@MainMenuMediumScaleUpTransition@@UAEXPAVGameWindow@@@Z` at 0x003A4C80 is a misnamed lift

The name on the 0x003A4C80 row arrived with the 2026-08-11 Open-BFME5
`__emit` lift (`MainMenuMediumScaleUpTransition_init_Thunk.cpp`), whose
`// readable body of` comment points at
`game/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp`. The
body contradicts that comment in five independent ways, so the row is retired
and the address is claimed under an address-keyed name.

* **The parameter is not a `GameWindow *`.** At +0x02 the body loads
  `[esp+0x0c]` into EDI and then runs `mov ecx,edi; call <thunk to
  StringBase<char>::compare>` three times against the literals `"Small"`
  (0x010EC730), `"Medium"` (0x01076BB4) and `"Large"` (0x010EC728) — the
  argument is the string receiver. The pointer is never dereferenced as a
  window: no `winGetSize`, `winGetScreenPosition`, `winHide`,
  `winGetInstanceData` or `TheWindowManager->winGetWindowFromId` appears
  anywhere in the 251 bytes, and every one of those calls IS in the real
  `init` bodies (`?init@MainMenuScaleUpTransition@@UAEXPAVGameWindow@@@Z`
  at 0x0059E4E0 and `MainMenuSmallScaleDownTransition::init` in
  `GameWindowTransitionsStyles.cpp`).
* **The receiver is not a transition.** The body touches exactly one field,
  `this+0x3c`, reading it as the old state and writing back the new one, and
  it passes `this` unchanged to the two landed bodies of one receiver:
  0x003A4BD0 (`?rva003A4BD0@Rva003A48B0Owner@@QAEXH@Z`, through ILT
  0x000394E6) and 0x003A48B0 (`?applyByName@Rva003A48B0Owner@@QAEXPBVAscii
  String@@DH@Z`, through ILT 0x00032010). Both are name selectors over
  `g_bfmeGameCW+0x188/+0x18c/+0x190`, which is what this body picks from too.
* **The address is not in the transition family.** The claimed class's other
  methods sit at 0x0059E0E0, 0x0059E010, 0x0059E110 and 0x0059E260, and
  `MainMenuScaleUpTransition::init` at 0x0059E4E0. 0x003A4C80 instead sits
  between 0x003A48B0, 0x003A4BD0 and 0x003A4DC0, contiguous with them.
* **No vtable reaches it.** `python3 tools/vtable_lookup.py --target
  0x003A4C80` reports no candidate installed table within the slot cap, and
  no emitter or Zero Hour twin exists for these bodies.
* **No caller names it.** A scan of every direct `call` in `.text` finds the
  ILT thunk 0x000394E6 reached from only two places: 0x003A4C9B inside this
  body and 0x003BECB1 inside `?finish@Rva003BEED0@@UAEXXZ` (0x003BEC30).
  Both names are themselves address-derived, so neither supplies a spelling
  for the method.

The owner class stays `Rva003A48B0Owner`, the address-derived key two landed
rows in the same neighbourhood already carry; only the method name changes, and
it keeps the address token. The successor body is clean C++ in
`game/GameEngine/Source/GameLogic/LivingWorld/Rva003A4C80NameSize.cpp` over
the same 251-byte range, and the naked lift file is deleted.
