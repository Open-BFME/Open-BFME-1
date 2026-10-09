# CommandButton fields at compiler-measured BFME offsets

The complete CommandButton constructor RVA 0x0049BBF0 (846 bytes), installed vtable 0x010FB5DC and matched ControlBar::newCommandButton allocation of 0x1D8 bytes identify this complete view. Matched INI::parseCommandButtonDefinition RVA 0x000B7F80 directly binds table RVA 0x00CFA3B8; UnitSpecificSound addresses +0xA8. This view holds the complete 12-byte vector there, matching the independently witnessed destructor view already named m_unitSpecificSound. No partial array element or padding-only view is renamed.

The existing matched source views identify CommandButton; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(CommandButton, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `CommandButtonConstructor` | `m_audio00` | `0xa8` | `m_unitSpecificSound` | `UnitSpecificSound` |
