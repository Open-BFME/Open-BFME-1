# ProductionUpdateModuleData fields at compiler-measured BFME offsets

Matched friend_newModuleData@ProductionUpdate RVA 0x0011AC90 (107 bytes) independently names the module data and calls constructor RVA 0x0029FB70 (159 bytes). That constructor installs vtable 0x010C0F68 shared with the matched destructor RVA 0x0029E260; the vector at +0x1C, layout string at +0x40 and ref-counted holder at +0x44 agree in both lifetime bodies. No assumed Zero Hour base size or layout offset is used.

The existing matched source views identify ProductionUpdateModuleData; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(ProductionUpdateModuleData, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdate.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

Independent parser ownership check: the factory at RVA `0x0011AC90` passes
its newly constructed object and an executable callback to
`INI::initFromINIMultiProc`. Following the callback's actual retail ILT jump,
its builder directly adds table RVA `0x00CC1158`. Every renamed field's record
belongs to that table. This check follows bytes, not the callback's pinned name.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `ProductionUpdateModuleDataCtor` | `m_bfme08` | `0x8` | `m_numDoorAnimations` | `NumDoorAnimations` |
| `ProductionUpdateModuleDataCtor` | `m_bfme0c` | `0xc` | `m_doorOpeningTime` | `DoorOpeningTime` |
| `ProductionUpdateModuleDataCtor` | `m_bfme10` | `0x10` | `m_doorWaitOpenTime` | `DoorWaitOpenTime` |
| `ProductionUpdateModuleDataCtor` | `m_bfme14` | `0x14` | `m_doorClosingTime` | `DoorCloseTime` |
| `ProductionUpdateModuleDataCtor` | `m_bfme18` | `0x18` | `m_constructionCompleteDuration` | `ConstructionCompleteDuration` |
| `ProductionUpdateModuleDataCtor` | `m_bfme1c` | `0x1c` | `m_quantityModifiers` | `QuantityModifier` |
| `ProductionUpdateModuleDataCtor` | `m_bfme28` | `0x28` | `m_maxQueueEntries` | `MaxQueueEntries` |
| `ProductionUpdateModuleDataCtor` | `m_bfme2c` | `0x2c` | `m_disabledTypesToProcess` | `DisabledTypesToProcess` |
