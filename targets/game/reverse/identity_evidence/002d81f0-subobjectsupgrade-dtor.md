# 0x002D81F0 is ~SubObjectsUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D81F0 was `?dup_002d81f0@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GSubObjectsUpgrade@@MAEPAXI@Z`
  (0x002D84B0, SubObjectsUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0000A466, and 0x0000A466 is `jmp 0x002D81F0`.
- `python3 tools/ilt_oracle.py check '??1SubObjectsUpgrade@@MAE@XZ' 0x002D81F0`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
