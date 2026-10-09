# OpenContainModuleData fields at compiler-measured BFME offsets

Constructor RVA 0x00227200 (398 bytes) installs OpenContain vtable 0x010AC338. Matched friend_newModuleData@OpenContain RVA 0x001159E0 allocates 0x168 and retains that vtable; the separate Cave constructor RVA 0x0012AB50 calls this base, installs a different vtable 0x0108F288 and writes its extra field at +0x168. The existing proof targets/game/reverse/identity_evidence/00227200-open-vs-cave-contain.md distinguishes the complete Open view from the derived Cave view. The five changed slots preserve their four-byte or one-byte storage and the existing object extent.

The existing matched source views identify OpenContainModuleData; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(OpenContainModuleData, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `OpenContainModuleDataCtorThunk` | `m_zero13C` | `0x13c` | `m_damagePercentageToUnits` | `DamagePercentToUnits` |
| `OpenContainModuleDataCtorThunk` | `m_flag14D` | `0x14d` | `m_allowAlliesInside` | `AllowAlliesInside` |
| `OpenContainModuleDataCtorThunk` | `m_flag14E` | `0x14e` | `m_allowEnemiesInside` | `AllowEnemiesInside` |
| `OpenContainModuleDataCtorThunk` | `m_flag14F` | `0x14f` | `m_allowNeutralInside` | `AllowNeutralInside` |
| `OpenContainModuleDataCtorThunk` | `m_flag155` | `0x155` | `m_passengersInTurret` | `PassengersInTurret` |
