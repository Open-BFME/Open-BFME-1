# HealContain destructor at RVA 0x00220240 (67 bytes)
Old: `??1Rva00220240FlatDtor@@UAE@XZ`
New: `??1HealContain@@MAE@XZ`

The matched scalar deleting destructor ??_GHealContain@@MAEPAXI@Z
(HealContainDeletingDestructor.cpp, RVA 0x00220350) calls this body through
ILT 0x0003A41D, which symbols.csv pins as ??1HealContain@@MAE@XZ.
tools/ilt_oracle.py check ??1HealContain@@MAE@XZ 0x00220240: CONFIRMED exact.
The body stores the nine vftables VA 0x010ABC78/BBB0/BBA0/B9F8/B9DC/B9D8/
B9C8/B98C/B97C that the matched HealContain constructor (HealContainCtorThunk.cpp)
installs and that dir32_addresses.csv records as ??_7HealContain@@6B...@,
then tail-jumps through ILT 0x00039D6A, pinned ??1OpenContain@@UAE@XZ
(Zero Hour: HealContain derives from OpenContain).
