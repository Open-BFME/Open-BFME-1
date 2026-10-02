# RVA 0x0076B6E0: W3DScriptedModelDraw primary slot 20

Owner proof only. The original BFME method spelling is not established; keep
an address-qualified method name if this body is converted. All addresses
were cross-checked against the unpacked retail executable with pefile and
capstone, image base 0x00400000. Ghidra byte searches independently confirm
the table installer references described below.

## Independently named base owner

The native string `W3DScriptedModelDraw` at VA 0x0111D2C0 is referenced in
matched clean C++ `W3DModuleFactory::init`, RVA 0x006BFFE0 (push immediate
at 0x006C0088). Its registration pairs the name with the independently
matched factory `W3DScriptedModelDraw::friend_newModuleInstance`, RVA
0x006BF040. That factory allocates 0x27C bytes and at 0x006BF07E calls
ILT 0x000285EC -> constructor RVA 0x00773360.

The constructor calls matched `DrawableModule::DrawableModule` through ILT
0x00002874 at 0x0077338A, then installs the primary table VA 0x01123D38
at `[esi]` (0x00773398) and final secondary table VA 0x01123C68 at `[esi+0x0C]`
(0x0077339E). Before those derived stores, the constructor briefly writes
the abstract base interface table 0x01123848 at +0x0C (0x0077338F). The constructor's independent name is supplied by the native
factory registration, not a presumed destructor identity. The existing
`getModuleNameKey@W3DScriptedModelDraw` body at 0x00773950 also uses the
same native module-name string.

Primary slot **20**, offset **+0x50**, VA **0x01123D88**, contains ILT VA
**0x00402180**, which jumps to the 231-byte body at RVA **0x0076B6E0**.
This is the complete object's primary table, not its +0x0C interface.

## The repeated tables are genuine derived owners

The same slot is inherited by these primary tables, all installed at object
+0 by independently matched named constructors:

| Class | Primary table VA | Constructor RVA |
|---|---|---|
| W3DHordeModelDraw | 0x01122470 | 0x00751CF0 |
| W3DQuadrupedDraw | 0x01123390 | 0x00759730 |
| W3DSupplyDraw | 0x011256D0 | 0x0077DB70 |
| W3DTankDraw | 0x01125AB0 | 0x0077F050 |
| W3DTruckDraw | 0x011265B0 | 0x0077FB20 |

Ghidra's search for the little-endian primary-table value 0x01122470 returns
VA 0x00B51D1A in the Horde constructor and VA 0x00B51E82 in its destructor.
The retail constructor stores the secondary table 0x011223A0 separately at
+0x0C. These are not arbitrary repeated dispatch arrays. A seventh copy,
0x01122EA8, is installed by the W3DPoliceCarDraw-related constructor whose
native file literal identifies that source, but that constructor retains an
opaque ledger name and is not required for the owner proof.

## Body operation and remaining limits

The body accepts one stack pointer and, if nonnull, assigns the pointed-to
record into this+0x188 through ILT 0x00015744 -> RVA 0x00458450. It then
examines the module's Drawable at +8 and Drawable's Object at +0xFC and
conditionally uses primary slot +0x60 to enable or disable decal state.
This slot sits among independently matched terrain-decal methods in all the
same primary tables: the earlier slot reaching 0x00763230 is setTerrainDecal,
and the immediately preceding slot reaches setTerrainDecalOpacity at
0x0075BDD0. This supports radius-decal configuration behavior. It does not
prove a BFME method spelling or all fields of the incoming record.

The sole input pointer and `ret 4` at 0x0076B7C4, followed by INT3 at
0x0076B7C7, establish the 231-byte extent and one-stack-slot member ABI.
There are no direct callers beyond the ILT and no absolute pointer to the
body; the seven table pointers refer to the stub.

Conversion is deferred: 0x00458450 currently has an address-derived assignment
identity, and the Object routes through ILTs 0x0002CA61 and 0x0000FAA6
retain unproved callee declarations. Several independent contracts would
need repair; they cannot be replaced with guessed types or names. The ledger
is unchanged. The honest future floor is W3DScriptedModelDraw with an
address-preserving method, rather than a guessed setRadiusDecal name.
