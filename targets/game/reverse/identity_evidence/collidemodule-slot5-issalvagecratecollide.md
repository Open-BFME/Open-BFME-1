# CollideModuleInterface slot 5: SalvageCrateCollide::isSalvageCrateCollide

All binary observations below are direct pefile/Capstone reads of retail
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs unless marked VA.

## Independent owner proof

The registered SalvageCrateCollide factory is 0011F190 (module_registry.tsv).
At 0011F1CB it calls ILT 00038668 -> constructor 00218030. That constructor
calls its CrateCollide base through 0002AC43, then installs:

| Store RVA | Object offset | Table VA |
|---|---|---|
| 00218044 | 0 | 010AA8CC |
| 0021804A | 0x0C | 010AA808 |
| 00218051 | 0x10 | 010AA7E8 |

Primary-table slot 2 is ILT 0003DFD7 -> getter 00218070, returning the literal
VA 0108FBD4 `SalvageCrateCollide`. This proves ownership without relying on
an inferred deleting-destructor name.

## Mechanical family enumeration

The first five Collide entries of the concrete crate table are the ILT VAs
0043FE63, 004068F2, 004209CD, 0040C004, 00411D29. Searching the complete
mapped image for that five-dword sequence yields exactly seven starts:

| Table VA | Slot-5 ILT RVA | Body RVA |
|---|---|---|
| 010AA24C | 00022629 | 00216210 |
| 010AA598 | 00022629 | 00216210 |
| 010AA6B8 | 00022629 | 00216210 |
| 010AA7E8 | **000215FD** | **00218080** |
| 010AA988 | 00022629 | 00216210 |
| 010AAAAC | 00022629 | 00216210 |
| 010AABCC | 00022629 | 00216210 |

The common slot 0 resolves to matched CrateCollide::onCollide (00217730).
The unique slot-5 ILT 000215FD is E9 directly to 00218080; its VA appears
exactly once as a dword in the mapped image, at VA 010AA7FC. The table has
six callable entries, then zero padding. This is a class-specific override.
The inherited false body is deliberately not assigned an owner here.

## Direct BFME call anchors the slot spelling

Matched Object::isSalvageCrate at 001BE9F0 (57 bytes), in Object.cpp, loops
over its modules. Its call at 001BEA05 uses behavior interface slot 1 (+4)
to obtain CollideModuleInterface; the call at 001BEA10 uses **+0x14**, slot 5,
and tests AL. The matched source names that predicate isSalvageCrateCollide.
This is an actual BFME virtual call, not an assumption that the whole ZH
interface has identical slots: ZH has seven methods, BFME only six here.

GeneralsMD `Code/GameEngine/Include/GameLogic/Module/SalvageCrateCollide.h:93`
explicitly defines the public virtual const override
`Bool isSalvageCrateCollide() const { return true; }`. The class-specific ZH
twin and BFME caller independently agree on the full name and signature.
Retail 00218080 is `B0 01 C3` (`mov al,1; ret`), followed immediately by
INT3 at 00218083, proving the three-byte extent and bool return ABI. The
mangling is `?isSalvageCrateCollide@SalvageCrateCollide@@UBE_NXZ`.

Replace the old free-function placeholder `?Rva00218080@@YA_NXZ` at the same
extent with the inline method emitted by the existing official-header TU
`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/SalvageCrateCollide.cpp`.
Remove only the retired placeholder from Rva00213D40To0021B820TinyBodies.cpp.
