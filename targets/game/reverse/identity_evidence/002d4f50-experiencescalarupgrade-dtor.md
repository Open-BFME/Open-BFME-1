# 0x002D4F50 is ~ExperienceScalarUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D4F50 was `?dup_002d4f50@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GExperienceScalarUpgrade@@MAEPAXI@Z`
  (0x002D50D0, ExperienceScalarUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x000423E3, and 0x000423E3 is `jmp 0x002D4F50`.
- `python3 tools/ilt_oracle.py check '??1ExperienceScalarUpgrade@@MAE@XZ' 0x002D4F50`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
