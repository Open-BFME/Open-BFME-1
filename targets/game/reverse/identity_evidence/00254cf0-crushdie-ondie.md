# RVA 0x00254CF0 is CrushDie::onDie

All binary facts were read from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe` with pefile
and Capstone (image base 0x00400000); GhidraMCP's stub-pointer byte search
returned the same unique slot.

## An independently named owner installs the table

Matched constructor `??0CrushDie@@QAE@PAVThing@@PBVModuleData@@@Z` at
RVA 0x00254B90 (60 bytes) calls ObjectModule's constructor and then stores:

| Instruction VA | Object offset | Table VA |
| --- | --- | --- |
| 0x00654BB2 | +0 | 0x010B2C84 |
| 0x00654BB8 | +0x0C | 0x010B2BC0 |
| 0x00654BBF | **+0x10** | **0x010B2BB8** |

The primary table at 0x010B2C84 independently identifies the owner: slot 2
contains ILT 0x0043F2FB -> RVA 0x00254BE0, whose six-byte getter returns
retail's literal `CrushDie`. Slot 4 contains ILT 0x0042B1C5 -> matched
CrushDie::getClassMemoryPool at RVA 0x00254BF0. This owner proof does not
rely on the scalar-deleting destructor's proposed identity or on our body.

The secondary table at 0x010B2BB8 contains exactly one callable entry,
VA 0x00435A08. This E9 ILT at RVA 0x00035A08 targets body VA 0x00654CF0.
Searching the complete image for its little-endian VA (`08 5A 43 00`)
finds only 0x010B2BB8, as also confirmed by GhidraMCP.

## Named sibling proves the interface slot

Matched FXListDie constructor at RVA 0x00255360 has the same three-base
shape and stores primary table 0x010B2FDC, behavior table 0x010B2F18 at
+0x0C and table 0x010B2F10 at **+0x10**. The latter's sole callable slot
is ILT 0x00420C11 -> matched `FXListDie::onDie(const DamageInfo*)`,
RVA 0x002554C0. Both single-slot tables are followed by a zero dword.

GeneralsMD's DieModule.h declares DieModuleInterface with exactly one
virtual method, `onDie(const DamageInfo*)`; CrushDie.h declares its public
virtual override. The BFME sibling's named method and identical secondary
subobject placement prove that this is the die-interface slot, rather than
an inferred primary-table method.

## Extent and current conversion limit

The body begins at RVA 0x00254CF0 and ends with `ret 4` at +0x1E3; INT3
starts at +0x1E6. Thus its full extent is 486 bytes and its signature is
`?onDie@CrushDie@@UAEXPBVDamageInfo@@@Z`, with ECX pointing to the die
interface subobject, 0x10 bytes after the full object.

The previous attempt's fuzzy-twin-only identity verdict is superseded by
these constructor, literal-getter and named-sibling facts. The preserved
bank still needs a BFME-specific audio/object ABI reconstruction (482 bytes
versus 486 and 321 differing non-relocation bytes in prior measured probes).
This evidence-only session does not change source, pins or progress rows.
