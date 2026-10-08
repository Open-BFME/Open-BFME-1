# HordeWorkerAIUpdate destructor at RVA 0x002C4980 (49 bytes)
Old: `??1Rva002C4980FlatDtor@@UAE@XZ`
New: `??1HordeWorkerAIUpdate@@MAE@XZ`

The matched scalar deleting destructor ??_GHordeWorkerAIUpdate@@MAEPAXI@Z
(HordeWorkerAIUpdateDeletingDestructor.cpp, RVA 0x002C4B30) calls this body through
ILT 0x000369AD, which symbols.csv pins as ??1HordeWorkerAIUpdate@@MAE@XZ.
tools/ilt_oracle.py check ??1HordeWorkerAIUpdate@@MAE@XZ 0x002C4980: CONFIRMED exact.
The body stores the six vftables VA 0x010C8790/86C8/86B8/86B4/8698/8638 (at
+0x0/0xC/0x10/0x20/0x24/0x340) that the matched HordeWorkerAIUpdate constructor
(HordeWorkerAIUpdateCtorThunk.cpp) installs and that dir32_addresses.csv records as
??_7HordeWorkerAIUpdate@@6B...@, then tail-jumps through ILT 0x00033A37, pinned
??1HordeAIUpdate@@MAE@XZ (its base; that body is 0x002C4190).
