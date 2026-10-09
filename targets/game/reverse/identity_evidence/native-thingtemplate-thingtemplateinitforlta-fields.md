# ThingTemplate fields at compiler-measured BFME offsets

The matched ThingFactory::parseObjectDefinition RVA 0x00139D00 uses the MultiIniFieldParse builder at RVA 0x0013E170, whose actual retail body directly adds table RVA 0x00C910A0. That table binds StructureRubbleHeight to +0x497. The upstream declaration is Byte, not Real: the getter casts it to Real. This view also declares exactly one byte at +0x497, written by the matched ThingTemplate::initForLTA RVA 0x00147F10 (1334 bytes); the broader owner identity is independently established by matched ThingFactory template allocation and the 0x4D4 constructor/destructor views. No offset, byte width or code is inferred from the getter return type.

The existing matched source views identify ThingTemplate; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(ThingTemplate, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `ThingTemplateInitForLTA` | `m_bfme497` | `0x497` | `m_structureRubbleHeight` | `StructureRubbleHeight` |
