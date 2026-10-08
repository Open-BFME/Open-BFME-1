# 0x002D76F0 is ~ProductionSpeedBonusUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D76F0 was `?dup_002d76f0@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GProductionSpeedBonusUpgrade@@MAEPAXI@Z`
  (0x002D7860, ProductionSpeedBonusUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x00027A6B, and 0x00027A6B is `jmp 0x002D76F0`.
- `python3 tools/ilt_oracle.py check '??1ProductionSpeedBonusUpgrade@@MAE@XZ' 0x002D76F0`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
