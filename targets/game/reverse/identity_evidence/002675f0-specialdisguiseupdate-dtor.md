# SpecialDisguiseUpdate destructor at RVA 0x002675F0 (42 bytes)
Old: `??1Rva002675F0FlatDtor@@UAE@XZ`
New: `??1SpecialDisguiseUpdate@@MAE@XZ`

The matched scalar deleting destructor ??_GSpecialDisguiseUpdate@@MAEPAXI@Z
(SpecialDisguiseUpdateDeletingDestructor.cpp, RVA 0x00267890) calls this body
through ILT 0x00008AE4, which symbols.csv pins as ??1SpecialDisguiseUpdate@@MAE@XZ.
tools/ilt_oracle.py check ??1SpecialDisguiseUpdate@@MAE@XZ 0x002675F0: CONFIRMED exact.
The body stores the five vftables VA 0x010B7708/7640/7630/7604/75F4 (at
+0x0/0xC/0x10/0x20/0xE8) that the matched SpecialDisguiseUpdate constructor
(SpecialDisguiseUpdateCtorThunk.cpp) installs and that dir32_addresses.csv
records as ??_7SpecialDisguiseUpdate@@6B...@, then tail-jumps through ILT
0x000243A7, pinned ??1SpecialAbilityUpdate@@UAE@XZ.
