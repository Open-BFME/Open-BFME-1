# HordeAIUpdate destructor at RVA 0x002C4190 (49 bytes)
Old: `??1Rva002C4190FlatDtor@@UAE@XZ`
New: `??1HordeAIUpdate@@MAE@XZ`

The matched scalar deleting destructor ??_GHordeAIUpdate@@MAEPAXI@Z
(HordeAIUpdateDeletingDestructor.cpp, RVA 0x002C4450) calls this body through
ILT 0x00033A37, which symbols.csv pins as ??1HordeAIUpdate@@MAE@XZ.
tools/ilt_oracle.py check ??1HordeAIUpdate@@MAE@XZ 0x002C4190: CONFIRMED exact.
The body stores the six vftables VA 0x010C8398/82D0/82C0/82BC/82A0/8240 (at
+0x0/0xC/0x10/0x20/0x24/0x340) that the matched HordeAIUpdate constructor
(HordeAIUpdateCtorThunk.cpp) installs and that dir32_addresses.csv records as
??_7HordeAIUpdate@@6B...@, then tail-jumps through ILT 0x0001C774, pinned
??1AIUpdateInterface@@UAE@XZ. HordeWorkerAIUpdate's destructor (0x002C4980)
in turn tail-jumps to this one through ILT 0x00033A37.
