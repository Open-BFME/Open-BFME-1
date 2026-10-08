# 0x0020D930 is ~WargBehavior, not an anonymous multi-vptr tail destructor

The 18-byte row at 0x0020D930 was `??1Rva0020D930MultiTailDtor@@UAE@XZ`, an
address-derived placeholder in MultiVptrTailJumpDestructors.cpp whose identity
was never recovered.

- The matched protected scalar-deleting wrapper `??_GWargBehavior@@MAEPAXI@Z`
  (0x0020DA60, WargBehaviorDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x000299C9, pinned `??1WargBehavior@@MAE@XZ`, and
  0x000299C9 is `jmp 0x0020D930`.
- `python3 tools/ilt_oracle.py check '??1WargBehavior@@MAE@XZ' 0x0020D930`
  reports CONFIRMED (exact).
- The body stores the BehaviorModule vtables (0x0109CB5C at +0, 0x0109CA98 at
  +0xC) and tail-jumps to ILT 0x00047C53, the ObjectModule destructor: an
  empty derived destructor of a BehaviorModule, the same inner layer as
  ~DestroyDie (0ae2f2f642).
