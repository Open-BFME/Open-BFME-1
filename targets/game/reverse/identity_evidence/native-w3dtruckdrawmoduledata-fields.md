# W3DTruckDrawModuleData fields at compiler-measured BFME offsets

Matched friend_newModuleData<W3DTruckDraw> RVA 0x006BF4F0 allocates 0x1C4 bytes and constructs through RVA 0x0077F830; the factory registration string independently names the module. Complete destructor RVA 0x0077F920 (405 bytes) reverses the same 21 string subobjects at +0x15C through +0x1AC. Its constructor-owned vtable routes through ILT 0x0001810B to the deleting wrapper RVA 0x007814F0 (30 bytes).

The existing matched source views identify W3DTruckDrawModuleData; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(W3DTruckDrawModuleData, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDraw.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

Independent parser ownership check: the factory at RVA `0x006BF4F0` passes
its newly constructed object and an executable callback to
`INI::initFromINIMultiProc`. Following the callback's actual retail ILT jump,
its builder directly adds table RVA `0x00D26280`. Every renamed field's record
belongs to that table. This check follows bytes, not the callback's pinned name.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `W3DTruckDrawModuleDataDestructor` | `m_string00` | `0x15c` | `m_dustEffectName` | `Dust` |
| `W3DTruckDrawModuleDataDestructor` | `m_string01` | `0x160` | `m_dirtEffectName` | `DirtSpray` |
| `W3DTruckDrawModuleDataDestructor` | `m_string02` | `0x164` | `m_powerslideEffectName` | `PowerslideSpray` |
| `W3DTruckDrawModuleDataDestructor` | `m_string03` | `0x168` | `m_frontLeftTireBoneName` | `LeftFrontTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string04` | `0x16c` | `m_frontRightTireBoneName` | `RightFrontTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string05` | `0x170` | `m_rearLeftTireBoneName` | `LeftRearTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string06` | `0x174` | `m_rearRightTireBoneName` | `RightRearTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string07` | `0x178` | `m_midFrontLeftTireBoneName` | `MidLeftFrontTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string08` | `0x17c` | `m_midFrontRightTireBoneName` | `MidRightFrontTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string09` | `0x180` | `m_midRearLeftTireBoneName` | `MidLeftRearTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string10` | `0x184` | `m_midRearRightTireBoneName` | `MidRightRearTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string11` | `0x188` | `m_midMidLeftTireBoneName` | `MidLeftMidTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string12` | `0x18c` | `m_midMidRightTireBoneName` | `MidRightMidTireBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string19` | `0x1a8` | `m_cabBoneName` | `CabBone` |
| `W3DTruckDrawModuleDataDestructor` | `m_string20` | `0x1ac` | `m_trailerBoneName` | `TrailerBone` |
