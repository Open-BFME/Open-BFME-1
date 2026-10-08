# ModelConditionSoundSelectorClientBehavior destructor at RVA 0x00124B20 (11 bytes)
Old: `??1Rva00124B20TailDtor@@UAE@XZ`
New: `??1ModelConditionSoundSelectorClientBehavior@@UAE@XZ`

The matched scalar deleting destructor ??_GModelConditionSoundSelectorClientBehavior
(ModelConditionSoundSelectorClientBehaviorDeletingDestructor.cpp, RVA 0x00124AF0)
calls this body through ILT 0x00042758, which symbols.csv pins as
??1ModelConditionSoundSelectorClientBehavior@@UAE@XZ.
tools/ilt_oracle.py check ??1ModelConditionSoundSelectorClientBehavior@@UAE@XZ 0x00124B20:
CONFIRMED exact.
The body stores the shared client-module base vftable VA 0x0108ACB8 (an inline
base destructor; the derived store is elided) and tail-jumps through ILT
0x0002B8C8, the same shape as RandomSoundSelectorClientBehavior (57e85e890e).
