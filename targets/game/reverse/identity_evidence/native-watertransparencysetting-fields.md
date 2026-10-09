# WaterTransparencySetting fields at compiler-measured BFME offsets

The retail INI block table binds WaterTransparency to matched INI::parseWaterTransparencyDefinition RVA 0x000C3A00 (287 bytes). Independently reading that parser shows table RVA 0x00CF6CD0, whose StandingWaterTexture entry addresses +0x30 of its created/overridden WaterTransparencySetting. The assignment RVA 0x000C3660 (113 bytes) copies the complete four-byte AsciiString at exactly +0x30 through its string assignment, corroborating both storage extent and semantic role.

The existing matched source views identify WaterTransparencySetting; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(WaterTransparencySetting, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Water.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `WaterTransparencySettingAssign` | `m_bfmeName` | `0x30` | `m_standingWaterTexture` | `StandingWaterTexture` |
