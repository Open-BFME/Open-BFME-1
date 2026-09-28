# RVA 0x00415260 is not Animatable3DObjClass::Set_HTree

The old row covers only 32 bytes, ending at 0x00415280 immediately after
loading `[this+0xfc]` into EDI. That is a common SEH prologue, not identity proof.
The complete body returns at 0x004154F8, followed by 167 int3 bytes.

Its actual call contracts establish battle-plan icon drawing:

- Object::getControllingPlayer, ILT 0x00020824 -> 0x001BE3F0.
- Player::doesObjectQualifyForBattlePlan, ILT 0x0000CF54 -> 0x000C9AB0.
- The active-plan getter, ILT 0x0000105A -> 0x000C9B10, for 1/2/3.
- Drawable::getIconInfo, ILT 0x000102A8 -> 0x00410F10, repeatedly.
- Anim2D constructor, frame width/height and draw methods, through the
  ILTs listed by tools/callees.py 0x00415260 665.
- The three icon pointers occupy slots 7/8/9. Their template source is the
  established Drawable::s_animationTemplates global at VA 0x012F12EC.

The reference Drawable::drawBattlePlans algorithm has the same three arms.
BFME reads the screen location from owner offsets 0x3c4/0x3c8 and returns
without argument cleanup; the ZH reference takes a health-bar region pointer.
The reconstruction retains an address-qualified owner identity rather than
asserting that the historical method decoration is known.

Rva00415260BattlePlans.cpp compiles to the complete 665-byte body exactly.
The equal-range correction is refused because the old end is nonterminal.
A rollback-protected two-step transaction first verifies the complete extent
using an explicit object-symbol, then corrects the name at that same extent.
Both steps use add_match.py scoped verification.
