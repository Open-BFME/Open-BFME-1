# 0x0044A6A0: InGameUI screen-animation owner

The owner is corroborated by an independently matched named caller's use of the
same global. The original method spelling remains unresolved; no rename is proposed.

## BFME owner witnesses

Addresses are retail RVAs except global/table values explicitly marked VA.
All instructions were checked with Capstone against the retail-1.03-unpacked PE.

* Independently matched `HideDisconnectWindow`, RVA `0x0050E5A0`, is clean C++ in
  `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/DisconnectWindow.cpp`.
  Its source names `TheInGameUI` and invokes `setQuitMenuVisible(false)` on it.
  The retail instruction at `0x0050E5C2` loads VA `0x012F148C` into ECX;
  `0x0050E5D6` invokes virtual slot `0x150` with zero. Thus the owner's global
  association is witnessed by a matched named source independently of the pin.
  The paired matched `ShowDisconnectWindow` at `0x0050E9A0` uses that same
  declaration and the native `DisconnectScreen.apt` literal.
* In the render-loop body at `0x006EB500`, instruction `0x006EB7C2` loads the same
  VA `0x012F148C` into ECX and `0x006EB7C8` calls ILT RVA `0x0001F8F2`.
  The stub's E9 reaches `0x0044A6A0`. This establishes the candidate's receiver
  as the object exposed by the independently witnessed InGameUI global.
* Matched `InGameUI::InGameUI` at `0x0044B800` has a complete BFME layout in
  `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`: it includes the
  list at `+0x12C4` and embedded `Rva00449790Owner` at `+0x12C8` used here.
  This is corroboration of the receiver layout, not a method-name witness.

## Extent and identity limits

The candidate ends with RET at `0x0044A803`, then INT3 at `0x0044A804`, proving
356 bytes. It walks the `+0x12C4` list, updates floating screen positions and
velocity, expires/fades Anim2D records, and calls their real-coordinate drawing
entry. It also calls the embedded owner at `+0x12C8` through ILT `0x00045570`.

The separately matched `InGameUI::updateAndDrawWorldAnimations` at `0x0043F640`
uses the world-animation list at `+0x12C0` and world projection/shroud checks.
Its name must not be reused for this body. There is no native method-name literal
or named clean caller for the screen-animation routine itself. Preserve the dump
identity until that spelling is established.
