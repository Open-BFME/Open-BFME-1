# RVA 00969C00: GridWSClassicEnvironmentMapperClass constructor

The Zero Hour twin is in
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.cpp:1214`.
It takes `(float fps, unsigned gridwidth_log2, unsigned last_frame,
unsigned offset, AxisType axis, unsigned stage)` and delegates to
`GridWSEnvMapperClass` with those six arguments. The canonical BFME header
already declares this overload.

Retail has the same complete initialization chain: RefCountClass's count
at +4 becomes one; TextureMapperClass installs VA0113BFB4 and clamps stage
at +8 to one; GridTextureMapperClass writes LastFrame/Offset at +1C/+20,
installs VA0113E594 and calls its already-matched `initialize(float,unsigned)`
at RVA00964930; the derived axis goes to +30 and the final vptr is VA0113E630.
RET24 confirms six stack arguments. No new pin or local class layout is used.

The final table is independently shared by the existing strict-matched
INI/copy constructors at 00969CA0/00969CD0 and Clone at 0096A580. For this
family, slot0 is RefCountClass::Delete_This, slot1 is the deleting destructor,
slot2 is Mapper_ID, slot3 is Clone. Its slot2 points to 00969C60, whose actual
six bytes return 0x15, the ZH MAPPER_ID_GRID_WS_CLASSIC_ENVIRONMENT value.
The old unrelated RingRenderObjClass alias at that address is not identity
evidence and is not propagated here. The final table binding already exists
in dir32_addresses.csv as `??_7GridWSClassicEnvironmentMapperClass@@6B@`.

Boundary: the preceding routine ends RET4 at 00969BFC followed by INT3 at
00969BFF. This aligned constructor starts 00969C00, has a self-contained
88-byte extent ending RET24 at 00969C55, and is followed by eight INT3 bytes.
Ghidra raw memory agrees with the baseline, and creating its function yields
88 bytes with the same initialization chain. No incoming standalone caller
was found; the explicit constructor twin, distinct final table and complete
retail boundary establish this identity without inventing one from adjacency.
