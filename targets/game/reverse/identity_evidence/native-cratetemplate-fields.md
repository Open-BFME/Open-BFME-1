# CrateTemplate fields at compiler-measured BFME offsets

Matched CrateSystem::parseCrateTemplateDefinition RVA 0x0037A490 (232 bytes) initializes the CrateTemplate found/created through TheCrateSystem and directly pushes retail table RVA 0x00CEA270. Its KilledByType record points to +0x18 in that same object. The assignment RVA 0x0037A1A0 (109 bytes) copies the entire 24-byte aggregate at +0x18, not merely the first word of an array; the existing nested six-word representation remains unchanged.

The existing matched source views identify CrateTemplate; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(CrateTemplate, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/System/CrateSystem.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `CrateTemplateAssign` | `m_bfmeChances` | `0x18` | `m_killedByTypeKindof` | `KilledByType` |
