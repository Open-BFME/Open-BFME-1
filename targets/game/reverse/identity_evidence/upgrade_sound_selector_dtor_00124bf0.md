# UpgradeSoundSelectorClientBehavior destructor at RVA 0x00124BF0 (11 bytes)
Old: `??1Rva00124BF0TailDtor@@UAE@XZ`
New: `??1UpgradeSoundSelectorClientBehavior@@UAE@XZ`

The matched scalar deleting destructor ??_GUpgradeSoundSelectorClientBehavior
(UpgradeSoundSelectorClientBehaviorDeletingDestructor.cpp, RVA 0x00124BC0)
calls this body through ILT 0x000369B7, which symbols.csv pins as
??1UpgradeSoundSelectorClientBehavior@@UAE@XZ.
tools/ilt_oracle.py check ??1UpgradeSoundSelectorClientBehavior@@UAE@XZ 0x00124BF0:
CONFIRMED exact.
The body stores the shared client-module base vftable VA 0x0108ACB8 (an inline
base destructor; the derived store is elided) and tail-jumps through ILT
0x0002B8C8, the same shape as RandomSoundSelectorClientBehavior (57e85e890e).
