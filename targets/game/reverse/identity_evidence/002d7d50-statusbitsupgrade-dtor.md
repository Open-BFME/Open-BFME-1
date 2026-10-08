# 0x002D7D50 is ~StatusBitsUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D7D50 was `?dup_002d7d50@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GStatusBitsUpgrade@@MAEPAXI@Z`
  (0x002D7ED0, StatusBitsUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x000168B0, and 0x000168B0 is `jmp 0x002D7D50`.
- `python3 tools/ilt_oracle.py check '??1StatusBitsUpgrade@@MAE@XZ' 0x002D7D50`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
- The Zero Hour StatusBitsUpgrade.cpp definition (unmatched, selected by the link over
  retail's) is removed; that TU now only declares it.
