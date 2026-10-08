# 0x002D6320 is ~MaxHealthUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D6320 was `?dup_002d6320@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GMaxHealthUpgrade@@MAEPAXI@Z`
  (0x002D64A0, MaxHealthUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0001F8E8, and 0x0001F8E8 is `jmp 0x002D6320`.
- `python3 tools/ilt_oracle.py check '??1MaxHealthUpgrade@@MAE@XZ' 0x002D6320`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
- The Zero Hour MaxHealthUpgrade.cpp definition (unmatched, selected by the link over
  retail's) is removed; that TU now only declares it.
