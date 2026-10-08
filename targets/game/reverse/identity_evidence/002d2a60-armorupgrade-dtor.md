# 0x002D2A60 is ~ArmorUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D2A60 was `?dup_002d2a60@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GArmorUpgrade@@MAEPAXI@Z`
  (0x002D2BB0, ArmorUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x00010118, and 0x00010118 is `jmp 0x002D2A60`.
- `python3 tools/ilt_oracle.py check '??1ArmorUpgrade@@MAE@XZ' 0x002D2A60`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
