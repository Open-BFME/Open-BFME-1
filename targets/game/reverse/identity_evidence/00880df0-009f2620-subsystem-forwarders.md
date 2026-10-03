# Two subsystem slot-one forwarders

Both entries are five bytes, 8B01 FF6004 (MOV EAX,[ECX]; JMP[EAX+4]),
followed by eleven INT3 bytes. Ghidra read_memory and independent retail PE
reads agree. There are no direct calls for callees.py to name.

| Entry | Direct entry witness | Constructor table store | Destructor table store |
| --- | --- | --- | --- |
| 00880DF0 | VA01132B54 slot4 = VA00C80DF0 | 00880F3A in00880F00 | 00880FE0 in00880FC0 |
| 009F2620 | VA011457F8 slot4 = VA00DF2620 | 009F276D in009F2730 | 009F2820 in009F2800 |

Both constructors establish the SubsystemInterface receiver at offset zero
and their separate Snapshot base at+8. The table's slot1 is00881070 or
009F28B0 respectively. These existing82/67-byte native providers take no
explicit arguments and end at plain RET008810C1/009F28F2. Their work resets
owned data. That behavior alone is not used to invent either wrapper name.

The independently matched SubsystemInterfaceList::initSubsystem at009A20B0
calls [EAX+4] at009A211D for sys->init(), then [EDX+8] at009A2124 for
loadIniFilesFromLegend(). This is the slot-name/ABI witness. The existing
subsystem_interface.h has precisely the required virtual init() declaration
at slot1. Each local address-qualified derived view calls that inherited
virtual, preserving ECX and introducing no new covered-class declaration,
fields, pin, or semantic owner identity. No vtable is instantiated here;
no claim is made about the header's documented omitted later BFME slots.

The complete wrappers pass native byte gates with zero relocations. Both
original wrapper names remain unknown and retain address-derived spellings.
