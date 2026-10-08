# TransitionDamageFX element structs: FXDamage*Info ctors and dtors

TransitionDamageFXModuleData's ctor 0x002532B0 builds three 0x30-element
arrays (this+0x0C, +0x550, +0xA94) through the eh vector constructor iterator
with ctor ILTs 0x00007BAD, 0x000302D8, 0x00016158 and dtor ILTs 0x0001074E,
0x00015703, 0x0002E451 (dir32 records of the old anonymous-namespace names
placed them there). Those ILTs jump to 0x00252360, 0x00252380, 0x002523A0
(ctors, 10 bytes: AsciiString ctor of the +8 member) and 0x00252370,
0x00252390, 0x002523B0 (dtors, 8 bytes: add ecx,8; jmp AsciiString dtor).

Zero Hour's TransitionDamageFX.h declares exactly these element types:
FXDamageFXListInfo, FXDamageOCLInfo and FXDamageParticleSystemInfo, each a
pointer followed by FXLocInfo (locType, AsciiString boneName at +8,
randomBone, Coord3D loc) = 0x1C bytes, in that member order.

Retail's incremental-link thunk table confirms every decorated name exactly
(`python3 tools/ilt_oracle.py check NAME RVA`):

    ??0FXDamageFXListInfo@@QAE@XZ          0x00252360  CONFIRMED exact
    ??0FXDamageOCLInfo@@QAE@XZ             0x00252380  CONFIRMED exact
    ??0FXDamageParticleSystemInfo@@QAE@XZ  0x002523A0  CONFIRMED exact
    ??1FXDamageFXListInfo@@QAE@XZ          0x00252370  CONFIRMED exact
    ??1FXDamageOCLInfo@@QAE@XZ             0x00252390  CONFIRMED exact
    ??1FXDamageParticleSystemInfo@@QAE@XZ  0x002523B0  CONFIRMED exact

and contradicts each in any other slot, as well as the previous spellings
(??0TransitionDamageFXSlotA..C, ??1TransitionDamageFXSlotA,
??0PrereqUnitRec@ProductionPrerequisite, ??0TransitionDamageFXList/OCL/
ParticleSystem). This commit retires only the three dtor rows
(address-named offset tail thunks ?invoke@Rva00252370/90/B0). The three
ctor names stay claimed at 0x000E49D0, where the oracle contradicts them
(identity_baseline/ilt_contradicted_baseline list that over-claim); moving
them to 0x00252360/80/A0, which hold a ProductionPrerequisite gen-alias,
is a follow-up that also shrinks those baselines.
