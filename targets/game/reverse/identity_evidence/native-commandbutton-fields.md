# CommandButton fields at compiler-measured BFME offsets

The matched CommandButton constructor RVA 0x0049BBF0 (846 bytes) is called by ControlBar::newCommandButton through retail ILT 0x00016F18; its allocation is 472 bytes and it installs vtable 0x010FB5DC. That vtable selects the deleting wrapper RVA 0x0049C560 (30 bytes), which calls the complete destructor RVA 0x0049C020 (556 bytes) through ILT 0x0001AE1A. The same 26 destructible subobjects fix this view; the opaque helper type identities are intentionally unchanged.

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

Independent parser ownership check: retail `INI::parseCommandButtonDefinition`
at RVA `0x000B7F80` pushes table VA `0x010FA3B8` (RVA `0x00CFA3B8`).
Every renamed field's table record belongs to that table, which initializes the
CommandButton returned by the ControlBar create/override path.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `CommandButtonDestructors` | `m_str3c` | `0x3c` | `m_cursorName` | `CursorName` |
| `CommandButtonDestructors` | `m_str40` | `0x40` | `m_invalidCursorName` | `InvalidCursorName` |
| `CommandButtonDestructors` | `m_b44` | `0x44` | `m_textLabel` | `TextLabel` |
| `CommandButtonDestructors` | `m_b50` | `0x50` | `m_descriptionLabel` | `DescriptLabel` |
| `CommandButtonDestructors` | `m_str5c` | `0x5c` | `m_purchasedLabel` | `PurchasedLabel` |
| `CommandButtonDestructors` | `m_str60` | `0x60` | `m_conflictingLabel` | `ConflictingLabel` |
| `CommandButtonDestructors` | `m_vec84` | `0x84` | `m_science` | `Science` |
| `CommandButtonDestructors` | `m_90` | `0x90` | `m_commandButtonBorder` | `ButtonBorderType` |
| `CommandButtonDestructors` | `m_b94` | `0x94` | `m_buttonImageName` | `ButtonImage` |
| `CommandButtonDestructors` | `m_a0` | `0xa8` | `m_unitSpecificSound` | `UnitSpecificSound` |
