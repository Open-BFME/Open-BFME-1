# 0x002D3DA0 is ~CastleUpgrade, not an anonymous UpgradeModule teardown alias

The 32-byte row at 0x002D3DA0 was `?dup_002d3da0@@YAXXZ`, a gen-alias of the
DynamicPortalUpgradeModule destructor COMDAT emitted by
DynamicPortalBehaviourDestructorThunk.cpp. Retail links without
identical-COMDAT folding, so each derived class's inlined UpgradeModule
teardown is its own body.

- The matched protected scalar-deleting wrapper `??_GCastleUpgrade@@MAEPAXI@Z`
  (0x002D3F20, CastleUpgradeDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x00019AC4, and 0x00019AC4 is `jmp 0x002D3DA0`.
- `python3 tools/ilt_oracle.py check '??1CastleUpgrade@@MAE@XZ' 0x002D3DA0`
  reports CONFIRMED (exact).
- The body stores the UpgradeMux and UpgradeModuleInterface vtables
  (0x010A36E0 at +0x10, 0x010A36CC at +0x18), then the BehaviorModule ones
  (0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps to ILT 0x00047C53,
  the ObjectModule destructor: an empty derived destructor.
