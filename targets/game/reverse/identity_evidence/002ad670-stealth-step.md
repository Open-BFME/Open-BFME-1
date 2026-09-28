# 0x002AD670 is a StealthUpdate helper, not StealthUpdate::update

- 0x002ADFB0 (302 B) is the real `StealthUpdate::update`. It is entered on the
  UpdateModule subobject: `this` is at +0x10 and it reads the owner through
  [this-8]. It runs the Zero Hour disguise-restore prologue: the
  m_xferRestoreDisguise byte at +0x43 (seen as +0x33 through the subobject),
  getDrawable, changeVisualDisguise through ILT 0x000378DF, and the hidden-state
  restore. It then calls 0x002AD670 as `lea ecx,[esi-0x10]; call ILT
  0x0002DA79` and continues with its own stealthed-status work.
- 0x002AD670 therefore takes the full StealthUpdate `this` and returns an
  UpdateSleepTime (`m_enabled ? 1 : 0x3FFFFFFF`). No caller names it, so the
  banked source calls it `StealthUpdate::rva002AD670`.
- The earlier bank's `RvaStealthUpdate::update` (virtual) was a guess. So were its
  shim types `RvaJ1166` and `RvaStealthUpdate`; the new source replaces them with
  the matched KindOfMask ctor pin (ILT 0x0000198D), the real StealthUpdate layout
  and PartitionFilter subclasses.
