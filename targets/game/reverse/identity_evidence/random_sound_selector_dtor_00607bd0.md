# RandomSoundSelectorClientBehavior destructor at RVA 0x00607BD0 (11 bytes)
Old: `??1Rva00607BD0TailDtor@@UAE@XZ`
New: `??1RandomSoundSelectorClientBehavior@@UAE@XZ`

The matched scalar deleting destructor ??_GRandomSoundSelectorClientBehavior
(RandomSoundSelectorClientBehaviorDeletingDestructor.cpp, RVA 0x00607BA0) is
slot zero of the vftable the matched constructor 0x00607A30 installs, and calls
this body through ILT 0x0004374D, which symbols.csv pins as
??1RandomSoundSelectorClientBehavior@@UAE@XZ.
tools/ilt_oracle.py check ??1RandomSoundSelectorClientBehavior@@UAE@XZ 0x00607BD0:
CONFIRMED exact.
The body stores the shared client-module base vftable VA 0x0108ACB8 (an inline
base destructor; the derived store is elided) and tail-jumps through ILT
0x0002B8C8 (drawable/client module root base destructor).
