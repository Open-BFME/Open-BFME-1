# AutoHealBehaviorModuleData fields at compiler-measured BFME offsets

Factory RVA 0x00129E40 allocates 0xA8 and calls the exact constructor RVA 0x00129D50 (180 bytes) through ILT 0x0001528A. Independently reading the factory bytes, its INI initialization passes callback VA 0x0043AF21: thunk RVA 0x0003AF21 (e97ae90e00) routes to builder RVA 0x001298A0, which adds retail table RVA 0x00C8EE60 with zero extra offset and its base table at +8. That table directly binds the six changed slots to the object this factory constructs. The unrelated named builder pin at RVA 0x00204F30 references a different Replenish table and was NOT used as ownership proof or modified.

The existing matched source views identify AutoHealBehaviorModuleData; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(AutoHealBehaviorModuleData, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `AutoHealBehaviorModuleDataCtor` | `m_x72` | `0x72` | `m_singleBurst` | `SingleBurst` |
| `AutoHealBehaviorModuleDataCtor` | `m_x74` | `0x74` | `m_healingAmount` | `HealingAmount` |
| `AutoHealBehaviorModuleDataCtor` | `m_x78` | `0x78` | `m_healingDelay` | `HealingDelay` |
| `AutoHealBehaviorModuleDataCtor` | `m_x7c` | `0x7c` | `m_startHealingDelay` | `StartHealingDelay` |
| `AutoHealBehaviorModuleDataCtor` | `m_x80` | `0x80` | `m_radius` | `Radius` |
| `AutoHealBehaviorModuleDataCtor` | `m_x84` | `0x84` | `m_affectsWholePlayer` | `AffectsWholePlayer` |
