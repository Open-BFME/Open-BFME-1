# Container DieModuleInterface slot 0: OpenContain and TunnelContain onDie

Retail lotrbfme.exe SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
All addresses below are RVAs except explicitly marked VAs. Facts were read
with pefile and Capstone directly from that baseline.

## Owner and slot

The registered TunnelContain factory 00116530 calls ILT 00002450 at
0011656E to constructor 0022EE70. The independent primary getter and
registration proof is recorded in containmodule-slot0-asopencontain.md.
The constructor calls OpenContain through ILT 00036E49 at 0022EE7F,
then installs primary table VA 010ADDB8 at 0022EE84 and the +0x28
DieModuleInterface table VA 010ADB14 at 0022EEA6.
Its sole slot is ILT VA 0040A9C0, a five-byte E9 to body 0022F300.
A whole-image aligned/un-aligned little-endian search finds this ILT VA
exactly once, at VA 010ADB14. This is TunnelContain's own override,
not an inherited shared implementation. The base OpenContain constructor
installs a different die table, VA 010AC014, whose sole slot reaches
00222640. The sixteen registered contain constructor census is in
damagemodule-slots0-1-callbacks.md; every table at +0x28 has this same
single-method interface role.

## Lexical twin and ABI

GeneralsMD GameEngine/Include/GameLogic/Module/TunnelContain.h:120-121
explicitly overrides public virtual `void onDie(const DamageInfo*)`,
with the comment that it overrides OpenContain's method.
GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp:350 supplies
its body: DieMux applicability, registration flag, controlling player,
player tunnel tracker, onTunnelDestroyed, and clearing registration.
DieModuleInterface declares precisely this one virtual method. Thus the
full class and method names have a direct Zero Hour twin, and the public
virtual pointer-to-const ABI is `?onDie@TunnelContain@@UAEXPBVDamageInfo@@@Z`.

Retail agrees: ECX is the die subobject at complete-object +0x28; module
data and Object are loaded at ECX-0x24 and ECX-0x20. It calls DieMux
through ILT 000357D8 at 0022F312, checks flag at ECX+0xAD, calls
getControllingPlayer through ILT 00020824 at 0022F328, loads tracker at
player+0x22C, calls ILT 000304E0 at 0022F341, and clears the same flag.
The body ends with `pop esi; ret 4` at 0022F34D..0022F350, followed by
INT3 at 0022F351, proving the 81-byte extent. The old matched opaque
BfmeThing300::bfmeGo body is the same implementation, not another identity.

## Source and validation

The unmodified Zero Hour body reproduces the 81-byte instruction shape but
reads its own layout (Object at die-0x1C, registration at die+0x671,
tracker at player+0x15C). The local game TunnelContain.cpp uses the real
headers and a four-byte shifted view solely for the inline module-data and
Object accessors; its declaration's die base is +0x28. Explicit retail reads
use complete-object+0xD5 for registration (die+0xAD) and player+0x22C for
the tracker. No virtual call receives the shifted view and no header changes
or invented field names are needed. Address-qualified inline tracker access
preserves the native source's evaluation shape. tools/probe.py reports
81/81 EXACT modulo its three relocations; add_match performs the actual
callee binding check. The three semantic callees already have matched
rows: DieMuxData::isDieApplicable 002551F0, Object::getControllingPlayer
001BE3F0, and TunnelTracker::onTunnelDestroyed 000F8C20. No pins are added.

## OpenContain introduces the shared slot-0 implementation at 00222640

OpenContain's registered factory/primary getter chain is independently proved
in containmodule-slot0-asopencontain.md. Its constructor 002277A0 calls
ObjectModule at 002277CC, installs primary VA 010AC2B8 at 00227817,
and installs die table VA 010AC014 at complete-object +0x28 at 00227839.
The table contains ILT VA 0043F044 -> body 00222640. This is the same
one-method die interface as TunnelContain, not a primary destructor slot.

The full constructor census resolves slot 0 as follows (table addresses VAs):

| Constructor owner | Die table VA | Body RVA |
|---|---|---|
| AODHordeContain | 010AE4FC | 00222640 |
| CaveContain | 010AAD60 | 0021A080 |
| ContestableContain | 010AB120 | 00249820 |
| GarrisonContain | 010AB574 | 00222640 |
| HealContain | 010AB9D8 | 00222640 |
| HordeContain | 010AF024 | 00222640 |
| HordeGarrisonContain | 010AFB20 | 00249820 |
| HordeSiegeEngineContain | 010B0004 | 0024CEE0 |
| HordeTransportContain | 010B03E8 | 0024CEE0 |
| HorseHordeContain | 010B0AAC | 00222640 |
| OpenContain | 010AC014 | 00222640 |
| RiderChangeContain | 010AC850 | 00222640 |
| SiegeEngineContain | 010ACDE4 | 00222640 |
| SlaughterHordeContain | 010B0F1C | 0024EB00 |
| TransportContain | 010AD248 | 00222640 |
| TunnelContain | 010ADB14 | 0022F300 |

Whole-image ILT-VA search gives exactly nine hits, each once at the nine
tables pointing to 00222640. The constructor base-call graph in
damagemodule-slots0-1-callbacks.md proves that every such owner derives
through OpenContain. OpenContain introduces the body; do not claim nine
separate identities. Other bodies above are outside this correction.

GeneralsMD OpenContain.h:105 explicitly declares public virtual
`void onDie(const DamageInfo*)`. Its source twin implements die applicability
and passenger death/exit behavior. Retail 00222640 sets a death-state byte,
calls the same DieMux predicate and handles two passenger branches. It
ends at 002226F8 with RET 4, with INT3 immediately after 002226FA. The 187-byte
extent, one pointer argument and void return agree with the public virtual
`?onDie@OpenContain@@UAEXPBVDamageInfo@@@Z` declaration.

This is an identity-only correction to an already byte-matched clean C++
body, not a new reconstruction. The existing source's address-qualified
layout view and COFF emission label are retained via explicit
`object-symbol=?dispatch@Rva00222640Owner@@QAEXPBVDamageInfo@@@Z` metadata.
That label describes the existing implementation view, not a second retail
identity. Its one-pointer thiscall ABI is identical; virtual/public naming
comes from the independent interface and lexical twin above. No speculative
field names, new header declarations, source bytes or callee pins are added.
